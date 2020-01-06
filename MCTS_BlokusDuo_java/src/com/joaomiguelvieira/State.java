package com.joaomiguelvieira;

import java.util.ArrayList;

public class State {
    private Board board;
    private Player player, opponent;
    private Move move;
    private ArrayList<Move> possibleMoves;
    private int visitCount = 0;
    private double winScore = 0;
    private int winCount = 0;
    private int movesPlayed = 0;

    public static final int IN_PROGRESS = -1;
    public static final int DRAW = 0;

    public State() {
        board = new Board();
    }

    public State(Board board) {
        this.board = new Board(board);
    }

    public int getVisitCount() {
        return visitCount;
    }

    public Board getBoard() {
        return board;
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

    public Player getOpponent() {
        return opponent;
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

    public int getMovesPlayed() {
        return movesPlayed;
    }

    public void setMovesPlayed(int movesPlayed) {
        this.movesPlayed = movesPlayed;
    }

    public void setPossibleMoves(ArrayList<Move> possibleMoves) {
        this.possibleMoves = possibleMoves;
    }
}
