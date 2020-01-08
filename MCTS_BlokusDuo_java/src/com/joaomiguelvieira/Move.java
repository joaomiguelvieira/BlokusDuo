package com.joaomiguelvieira;

import java.util.Objects;

public class Move {
    private GamePiece gamePiece;
    private Position center;

    public Move(GamePiece gamePiece, Position center) {
        this.gamePiece = gamePiece;
        this.center = new Position(center);
    }

    public GamePiece getGamePiece() {
        return gamePiece;
    }

    public Position getCenter() {
        return center;
    }

    public static String moveToString(Move move) {
        if (move == null)
            return "0000";

        String string = "";
        string += Integer.toHexString(move.center.getX() + 1);
        string += Integer.toHexString(move.center.getY() + 1);
        string += move.gamePiece.getCodeName();
        string += move.gamePiece.getTransformation();

        return string;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Move move = (Move) o;
        return gamePiece.equals(move.gamePiece) &&
                center.equals(move.center);
    }

    @Override
    public int hashCode() {
        return Objects.hash(gamePiece, center);
    }
}
