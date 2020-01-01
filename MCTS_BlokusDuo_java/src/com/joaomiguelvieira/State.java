package com.joaomiguelvieira;

import java.util.ArrayList;

public class State {
    private Board board;
    private Player player, opponent;
    private Move move;
    private int visitCount = 0;
    private double winScore = 0;
    private int winCount = 0;

    public static final int IN_PROGRESS = -1;
    public static final int DRAW = 0;

    public State() {
        board = new Board();
    }

    public State(State state) {
        board = new Board(state.board);
        player = new Player(state.player);
        opponent = new Player(state.opponent);
        visitCount = state.visitCount;
        winScore = state.winScore;
        winCount = state.winCount;
    }

    public State(Board board) {
        this.board = new Board(board);
    }

    public void setBoard(Board board) {
        this.board = board;
    }

    public int getVisitCount() {
        return visitCount;
    }

    public Board getBoard() {
        return board;
    }

    public double getWinScore() {
        return winScore;
    }

    public Player getPlayer() {
        return player;
    }

    public void setWinScore(double winScore) {
        this.winScore = winScore;
    }

    public void incrementVisit() {
        visitCount++;
    }

    public void addScore(double score) {
        if (winScore != -Double.MAX_VALUE)
            winScore += score;
    }

    public void setOpponent(Player opponent) {
        this.opponent = opponent;
    }

    public void togglePlayer() {
        Player tempPlayer = player;
        player = opponent;
        opponent = tempPlayer;
    }

    public Player getOpponent() {
        return opponent;
    }

    public ArrayList<State> getAllPossibleStates() {
        ArrayList<State> possibleStates = new ArrayList<>();

        if (!opponent.getQuited()) {
            ArrayList<Move> possibleMoves = board.getAllValidMoves(opponent);
            for (Move possibleMove : possibleMoves) {
                State newState = new State(board);
                newState.setPlayer(new Player(opponent, possibleMove.getGamePiece()));
                newState.setOpponent(new Player(player));
                newState.setMove(possibleMove);
                newState.getBoard().performMove(newState.player, possibleMove);
                possibleStates.add(newState);
            }
        }

        State newState = new State(board);
        newState.setPlayer(new Player(opponent));
        newState.setOpponent(new Player(player));
        newState.getPlayer().setQuited(true);
        possibleStates.add(newState);

        return possibleStates;
    }

    public Move getMove() {
        return move;
    }

    public void setMove(Move move) {
        this.move = move;
    }

    public void setPlayer(Player player) {
        this.player = player;
    }

    public int checkStatus() {
        if (player.getQuited() && opponent.getQuited()) {
            double scoreDiff = player.getScore() - opponent.getScore();

            if (scoreDiff < 0)
                return player.getPlayerId();
            else if (scoreDiff > 0)
                return opponent.getPlayerId();
            else
                return DRAW;
        }

        return IN_PROGRESS;
    }

    public void randomPlay() {
        ArrayList<Move> possibleMoves = board.getAllValidMoves(player);
        int totalPossibilities = possibleMoves.size();

        if (totalPossibilities == 0) {
            player.setQuited(true);
            return;
        }

        int selectRandom = (int) (Math.random() * totalPossibilities);
        Move moveToPerform = possibleMoves.get(selectRandom);
        board.performMove(player, moveToPerform);
        GamePiece pieceToRemove = moveToPerform.getGamePiece();
        player.getRemainingGamePieces().removeIf(gamePiece -> gamePiece.get(0).getCodeName() == pieceToRemove.getCodeName());
    }

    public double getStateViability() {
        if (Move.moveToString(move).equals("0000"))
            return -Double.MAX_VALUE;

        // proximity to diagonal
        double distanceDiag = 0.7 * Math.abs(move.getCenter().getX() + move.getCenter().getY() - 13);
        double proximityDiag = 9.1 - distanceDiag;
        double proximityDiagContribution = 0;
        if (proximityDiag > 0)
            proximityDiagContribution = proximityDiag / 9.9;

        // number of visits
        double visitsContribution = 0;
        if (visitCount > 10)
            visitsContribution = Math.pow(2, -1.0 / visitCount);

        // number of squares
        double squaresContribution = move.getGamePiece().getSquares().length;
        squaresContribution /= 5;

        return 8 * visitsContribution +
                2 * squaresContribution +
                proximityDiagContribution;
    }

    public void incrementWinCount() {
        winCount++;
    }

    public int getWinCount() {
        return winCount;
    }

    public int getScore() {
        return Math.abs(player.getScore() - opponent.getScore());
    }
}
