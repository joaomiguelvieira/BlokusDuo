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

    public byte getPlayerId() {
        return playerId;
    }

    public ArrayList<ArrayList<GamePiece>> getRemainingGamePieces() {
        return remainingGamePieces;
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

    public Player(ArrayList<ArrayList<GamePiece>> remainingGamePieces) {
        playerId = ++idCount;
        this.remainingGamePieces = new ArrayList<>();
        this.remainingGamePieces.addAll(remainingGamePieces);
    }
}
