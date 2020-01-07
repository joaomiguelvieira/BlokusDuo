package com.joaomiguelvieira;

import java.lang.reflect.Array;
import java.util.ArrayList;
import java.util.List;

public class Player {
    private static byte idCount = 0;

    private byte playerId;
    private boolean quited = false;
    private ArrayList<ArrayList<GamePiece>> remainingGamePieces;

    public Player() {
        playerId = ++idCount;
        remainingGamePieces = GamePiece.getInitialSetOfGamePieces();
    }

    public Player(Player player, GamePiece removePiece) {
        playerId = player.playerId;

        remainingGamePieces = new ArrayList<>();
        for (ArrayList<GamePiece> gamePiece : player.remainingGamePieces)
            if (gamePiece.get(0).getCodeName() != removePiece.getCodeName())
                remainingGamePieces.add(gamePiece);

        quited = player.quited;
    }

    public Player(Player player) {
        playerId = player.playerId;

        remainingGamePieces = new ArrayList<>();
        remainingGamePieces.addAll(player.remainingGamePieces);

        quited = player.quited;
    }

    public byte getPlayerId() {
        return playerId;
    }

    public ArrayList<ArrayList<GamePiece>> getRemainingGamePieces() {
        return remainingGamePieces;
    }

    public boolean getQuited() {
        return quited;
    }

    public int getScore() {
        int score = 0;

        for (ArrayList<GamePiece> gamePiece : remainingGamePieces)
            score += gamePiece.get(0).getSquares().length;

        return score;
    }

    public void setQuited(boolean quited) {
        this.quited = quited;
    }

    @Override
    public String toString() {
        StringBuilder text = new StringBuilder();

        text.append("Player ").append(playerId).append(": { ");

        text.append("quited: ").append(quited ? "true; " : "false; ");
        text.append("score: ").append(getScore()).append("; ");
        text.append("remaining pieces: ");
        for (ArrayList<GamePiece> gamePiece : remainingGamePieces)
            text.append(gamePiece.get(0).getCodeName()).append(" ");

        text.append("}");

        return text.toString();
    }
}
