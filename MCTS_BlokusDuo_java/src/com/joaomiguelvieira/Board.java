package com.joaomiguelvieira;

import java.awt.desktop.SystemHotkey;
import java.lang.reflect.Array;
import java.util.ArrayList;
import java.util.Arrays;

public class Board {
    private static final int DEFAULT_BOARD_SIZE = 14;

    private byte[][] board;

    public Board() {
        board = new byte[DEFAULT_BOARD_SIZE][DEFAULT_BOARD_SIZE];
        for (byte[] bytes : board) Arrays.fill(bytes, (byte) 0);
    }

    public byte[][] getBoard() {
        return board;
    }

    public ArrayList<Position> getAllAnchors(int playerId) {
        ArrayList<Position> anchors = new ArrayList<>();

        for (int i = 0; i < board.length; i++)
            for (int j = 0; j < board.length; j++)
                if (board[i][j] == 0 && hasCornerContact(i, j, playerId) && !hasEdgeContact(i, j, playerId))
                    anchors.add(new Position(i, j));

        return anchors;
    }

    private boolean isOccupied(int x, int y) {
        return board[x][y] != 0;
    }

    private boolean respectsBoundaries(int x, int y) {
        return x >= 0 && x < board.length && y >= 0 && y < board.length;
    }

    private boolean hasCornerContact(int x, int y, int playerId) {
        return (x - 1 >= 0 && y - 1 >= 0 && board[x - 1][y - 1] == playerId) ||
                (x - 1 >= 0 && y + 1 < board.length && board[x - 1][y + 1] == playerId) ||
                (x + 1 < board.length && y - 1 >= 0 && board[x + 1][y - 1] == playerId) ||
                (x + 1 < board.length && y + 1 < board.length && board[x + 1][y + 1] == playerId);
    }

    private boolean hasEdgeContact(int x, int y, int playerId) {
        return (x - 1 >= 0 && board[x - 1][y] == playerId) || (x + 1 < board.length && board[x + 1][y] == playerId) ||
                (y - 1 >= 0 && board[x][y - 1] == playerId) || (y + 1 < board.length && board[x][y + 1] == playerId);
    }

    public void printBoard() {
        char[] axis = {'1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e'};
        System.out.print("    ");
        for (char tick : axis)
            System.out.print(tick + " ");
        System.out.println();
        System.out.println("  + + + + + + + + + + + + + + + +");
        for (int i = 0; i < board.length; i++) {
            System.out.print(axis[i] + " + ");
            for (byte[] bytes : board) {
                if (bytes[i] == 0)
                    System.out.print("  ");
                else
                    System.out.print(bytes[i] + " ");
            }
            System.out.println("+");
        }
        System.out.println("  + + + + + + + + + + + + + + + +");
    }

    public Board(Board board) {
        this.board = new byte[DEFAULT_BOARD_SIZE][DEFAULT_BOARD_SIZE];
        for (int i = 0; i < board.board.length; i++)
            System.arraycopy(board.board[i], 0, this.board[i], 0, board.board.length);
    }

    public void performMove(Player player, Move move) {
        for (Position square : move.getGamePiece().getSquares())
            board[square.getX() + move.getCenter().getX()][square.getY() + move.getCenter().getY()] = player.getPlayerId();
    }

    public boolean checkValidMove(Player player, GamePiece gamePiece, Position center) {
        for (Position square : gamePiece.getSquares()) {
            int x = square.getX() + center.getX();
            int y = square.getY() + center.getY();

            // check for board limits
            if (x < 0 || x >= board.length || y < 0 || y >= board.length)
                return false;

            // check for overlap
            if (board[x][y] != 0)
                return false;

            // check for edge contact
            if (hasEdgeContact(x, y, player.getPlayerId()))
                return false;
        }

        return true;
    }

    public ArrayList<Move> getAllValidMoves(Player player) {
        ArrayList<Move> validMoves = new ArrayList<>();

        // all valid moves cover 5, 5
        if (board[4][4] == 0) {
            for (ArrayList<GamePiece> gamePiece : player.getRemainingGamePieces()) {
                for (GamePiece variant : gamePiece) {
                    for (Position square : variant.getSquares()) {
                        Position center = new Position(4, 4);
                        center.subtract(square);

                        validMoves.add(new Move(variant, center));
                    }
                }
            }

            return validMoves;
        }

        // all valid moves cover a, a
        if (board[9][9] == 0) {
            for (ArrayList<GamePiece> gamePiece : player.getRemainingGamePieces()) {
                for (GamePiece variant : gamePiece) {
                    for (Position square : variant.getSquares()) {
                        Position center = new Position(9, 9);
                        center.subtract(square);

                        validMoves.add(new Move(variant, center));
                    }
                }
            }

            return validMoves;
        }

        ArrayList<Position> boardAnchors = getAllAnchors(player.getPlayerId());
        for (Position boardAnchor : boardAnchors) {
            for (ArrayList<GamePiece> gamePiece : player.getRemainingGamePieces()) {
                for (GamePiece variant : gamePiece) {
                    for (Position anchor : variant.getAnchors()) {
                        Position center = new Position(boardAnchor);
                        center.subtract(anchor);

                        if (checkValidMove(player, variant, center))
                        validMoves.add(new Move(variant, center));
                    }
                }
            }
        }

        return validMoves;
    }

    private boolean isAnchor(int x, int y, int playerId) {
        return respectsBoundaries(x, y) && !isOccupied(x, y) && hasCornerContact(x, y, playerId) && !hasEdgeContact(x, y, playerId);
    }

    public ArrayList<Move> getAllValidMoves(Player player, ArrayList<Move> previouslyValidMoves,
                                            Move previouslyPlayedMove, Board previousBoard) {
        ArrayList<Move> validMoves = new ArrayList<>();

        // delete obsolete moves
        for (Move previouslyValidMove : previouslyValidMoves)
            if (previouslyValidMove.getGamePiece().getCodeName() != previouslyPlayedMove.getGamePiece().getCodeName() &&
            checkValidMove(player, previouslyPlayedMove.getGamePiece(), previouslyPlayedMove.getCenter()))
                validMoves.add(previouslyValidMove);

        // calculate new anchors
        ArrayList<Position> newAnchors = new ArrayList<>();
        for (Position possibleAnchorSource : previouslyPlayedMove.getGamePiece().getAnchors()) {
            int x = possibleAnchorSource.getX() + previouslyPlayedMove.getCenter().getX();
            int y = possibleAnchorSource.getY() + previouslyPlayedMove.getCenter().getY();

            if (isAnchor(x - 1, y - 1, player.getPlayerId()) &&
                    !previousBoard.isAnchor(x - 1, y - 1, player.getPlayerId()))
                newAnchors.add(new Position(x - 1, y - 1));

            if (isAnchor(x + 1, y - 1, player.getPlayerId()) &&
                    !previousBoard.isAnchor(x + 1, y - 1, player.getPlayerId()))
                newAnchors.add(new Position(x + 1, y - 1));

            if (isAnchor(x - 1, y + 1, player.getPlayerId()) &&
                    !previousBoard.isAnchor(x - 1, y + 1, player.getPlayerId()))
                newAnchors.add(new Position(x - 1, y + 1));

            if (isAnchor(x + 1, y + 1, player.getPlayerId()) &&
                    !previousBoard.isAnchor(x + 1, y + 1, player.getPlayerId()))
                newAnchors.add(new Position(x + 1, y + 1));
        }

        // get valid moves from new anchors only
        for (Position boardAnchor : newAnchors) {
            for (ArrayList<GamePiece> gamePiece : player.getRemainingGamePieces()) {
                for (GamePiece variant : gamePiece) {
                    for (Position anchor : variant.getAnchors()) {
                        Position center = new Position(boardAnchor);
                        center.subtract(anchor);

                        if (checkValidMove(player, variant, center))
                            validMoves.add(new Move(variant, center));
                    }
                }
            }
        }

        return validMoves;
    }
}
