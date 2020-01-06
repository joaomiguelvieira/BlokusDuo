package com.joaomiguelvieira;

public class Position {
    private int x, y;

    public Position(int x, int y) {
        this.x = x;
        this.y = y;
    }

    public Position(Position position) {
        this.x = position.x;
        this.y = position.y;
    }

    public int getX() {
        return x;
    }

    public int getY() {
        return y;
    }

    public void transform(int[][] transformation) {
        int newX = x * transformation[0][0] + y * transformation[0][1];
        int newY = x * transformation[1][0] + y * transformation[1][1];

        x = newX;
        y = newY;
    }

    public void subtract(Position position) {
        x -= position.x;
        y -= position.y;
    }
}
