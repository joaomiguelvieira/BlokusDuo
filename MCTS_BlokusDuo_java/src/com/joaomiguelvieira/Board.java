package com.joaomiguelvieira;

import java.util.ArrayList;
import java.util.Arrays;

public class Board {
    private static final int DEFAULT_BOARD_SIZE = 14;

    private byte[][] board;

    public Board() {
        board = new byte[DEFAULT_BOARD_SIZE][DEFAULT_BOARD_SIZE];
        for (byte[] bytes : board) Arrays.fill(bytes, (byte) 0);
    }

    public Board(Board board) {
        this.board = new byte[DEFAULT_BOARD_SIZE][DEFAULT_BOARD_SIZE];
        for (int i = 0; i < board.board.length; i++)
            System.arraycopy(board.board[i], 0, this.board[i], 0, board.board.length);
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

    private boolean isAnchor(int x, int y, int playerId) {
        return respectsBoundaries(x, y) && !isOccupied(x, y) && hasCornerContact(x, y, playerId) && !hasEdgeContact(x, y, playerId);
    }

    private ArrayList<Position> getAllAnchors(int playerId) {
        ArrayList<Position> anchors = new ArrayList<>();

        for (int i = 0; i < board.length; i++)
            for (int j = 0; j < board.length; j++)
                if (isAnchor(i, j, playerId))
                    anchors.add(new Position(i, j));

        return anchors;
    }

    @Override
    public String toString() {
        StringBuilder text = new StringBuilder("    ");
        char[] axis = {'1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e'};
        for (char tick : axis)
            text.append(tick).append(" ");
        text.append("\n");
        text.append("  + + + + + + + + + + + + + + + +\n");
        for (int i = 0; i < board.length; i++) {
            text.append(axis[i]).append(" + ");
            for (byte[] bytes : board) {
                if (bytes[i] == 0)
                    text.append("  ");
                else
                    text.append(bytes[i]).append(" ");
            }
            text.append("+\n");
        }
        text.append("  + + + + + + + + + + + + + + + +");

        return text.toString();
    }

    public void performMove(Player player, Move move) {
        for (Position square : move.getGamePiece().getSquares())
            board[square.getX() + move.getCenter().getX()][square.getY() + move.getCenter().getY()] = player.getPlayerId();
    }

    private boolean checkValidMove(Player player, GamePiece gamePiece, Position center) {
        for (Position square : gamePiece.getSquares()) {
            int x = square.getX() + center.getX();
            int y = square.getY() + center.getY();

            if (!respectsBoundaries(x, y) || isOccupied(x, y) || hasEdgeContact(x, y, player.getPlayerId()))
                return false;
        }

        return true;
    }

    private ArrayList<Move> getMovesFromAnchors(Player player, ArrayList<Position> boardAnchors) {
        ArrayList<Move> validMoves = new ArrayList<>();

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

    private ArrayList<Move> getMovesCoveringPosition(Player player, int x, int y) {
        ArrayList<Move> validMoves = new ArrayList<>();

        for (ArrayList<GamePiece> gamePiece : player.getRemainingGamePieces()) {
            for (GamePiece variant : gamePiece) {
                for (Position square : variant.getSquares()) {
                    Position center = new Position(x, y);
                    center.subtract(square);

                    validMoves.add(new Move(variant, center));
                }
            }
        }

        return validMoves;
    }

    public ArrayList<Move> getAllValidMoves(Player player) {
        // all valid moves cover 5, 5
        if (board[4][4] == 0)
            return getMovesCoveringPosition(player, 4, 4);
        // all valid moves cover a, a
        else if (board[9][9] == 0)
            return getMovesCoveringPosition(player, 9, 9);
        // valid moves are attached to anchors
        else
            return getMovesFromAnchors(player, getAllAnchors(player.getPlayerId()));
    }

    public ArrayList<Move> getAllValidMoves(Player player, ArrayList<Move> previouslyValidMoves,
                                            Move previouslyPlayedMove, Board previousBoard) {
        ArrayList<Move> validMoves = new ArrayList<>();

        // in case the player has quited return empty list
        if (player.getQuited())
            return validMoves;

        // delete obsolete moves
        for (Move previouslyValidMove : previouslyValidMoves) {
            if (previouslyValidMove.getGamePiece().getCodeName() != previouslyPlayedMove.getGamePiece().getCodeName() &&
                    checkValidMove(player, previouslyValidMove.getGamePiece(), previouslyValidMove.getCenter()))
                validMoves.add(previouslyValidMove);
        }

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
        validMoves.addAll(getMovesFromAnchors(player, newAnchors));

        return validMoves;
    }
}
