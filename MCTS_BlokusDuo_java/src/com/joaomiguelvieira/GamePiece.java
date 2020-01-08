package com.joaomiguelvieira;

import java.lang.reflect.Array;
import java.util.*;

public class GamePiece {
    private static final int DEFAULT_MAX_SQUARES = 5;
    private static final int[][][] transformations = {
            {{ 1,  0}, { 0,  1}},
            {{-1,  0}, { 0,  1}},
            {{ 0, -1}, { 1,  0}},
            {{ 0,  1}, { 1,  0}},
            {{-1,  0}, { 0, -1}},
            {{ 1,  0}, { 0, -1}},
            {{ 0,  1}, {-1,  0}},
            {{ 0, -1}, {-1,  0}}
    };

    private char codeName;
    private int transformation;
    private Position[] squares, anchors;

    public GamePiece(char codeName, int[][] squares, int[][] anchors) {
        this.codeName = codeName;
        this.transformation = 0;

        this.squares = new Position[squares.length];
        for (int i = 0; i < squares.length; i++)
            this.squares[i] = new Position(squares[i][0], squares[i][1]);

        this.anchors = new Position[anchors.length];
        for (int i = 0; i < anchors.length; i++)
            this.anchors[i] = new Position(anchors[i][0], anchors[i][1]);
    }

    public static ArrayList<ArrayList<GamePiece>> getInitialSetOfGamePieces () {
        ArrayList<ArrayList<GamePiece>> initialSetOfGamePieces = new ArrayList<>();

        class DefaultGamePiece {
            public char codeName;
            public int[][] squares;
            public int[][] anchors;
            public int[] variants;

            DefaultGamePiece(char codeName, int[][] squares, int[][] anchors, int[] variants) {
                this.codeName = codeName;
                this.squares = squares;
                this.anchors = anchors;
                this.variants = variants;
            }
        }

        DefaultGamePiece[] defaultGamePieces = {
                new DefaultGamePiece('a', new int[][]{{ 0,  0}},                                         new int[][]{{ 0,  0}}                                        , new int[]{0}),
                new DefaultGamePiece('b', new int[][]{{ 0,  0}, { 0,  1}},                               new int[][]{{ 0,  0}, { 0,  1}}                              , new int[]{0, 2}),
                new DefaultGamePiece('c', new int[][]{{ 0,  0}, { 0,  1}, { 0, -1}},                     new int[][]{{ 0,  1}, { 0, -1}, { 0,  0}}                    , new int[]{0, 2}),
                new DefaultGamePiece('d', new int[][]{{ 0,  0}, { 0, -1}, { 1,  0}},                     new int[][]{{ 0,  0}, { 0, -1}, { 1,  0}}                    , new int[]{0, 1, 2, 3}),
                new DefaultGamePiece('e', new int[][]{{ 0,  0}, { 0,  1}, { 0,  2}, { 0, -1}},           new int[][]{{ 0,  2}, { 0, -1}, { 0,  0}, { 0,  0}}          , new int[]{0, 2}),
                new DefaultGamePiece('f', new int[][]{{ 0,  0}, { 0,  1}, {-1,  1}, { 0, -1}},           new int[][]{{ 0,  1}, {-1,  1}, { 0, -1}, { 0,  0}}          , new int[]{0, 1, 2, 3, 4, 5, 6, 7}),
                new DefaultGamePiece('g', new int[][]{{ 0,  0}, { 0,  1}, { 0, -1}, { 1,  0}},           new int[][]{{ 0,  1}, { 1,  0}, { 0, -1}, { 0,  0}}          , new int[]{0, 1, 2, 6}),
                new DefaultGamePiece('h', new int[][]{{ 0,  0}, { 1,  0}, { 0,  1}, { 1,  1}},           new int[][]{{ 0,  0}, { 1,  0}, { 0,  1}, { 1,  1}}          , new int[]{0}),
                new DefaultGamePiece('i', new int[][]{{ 0,  0}, {-1,  0}, { 0,  1}, { 1,  1}},           new int[][]{{ 0,  0}, {-1,  0}, { 0,  1}, { 1,  1}}          , new int[]{0, 1, 2, 3}),
                new DefaultGamePiece('j', new int[][]{{ 0,  0}, { 0, -1}, { 0, -2}, { 0,  1}, { 0,  2}}, new int[][]{{ 0, -2}, { 0,  2}, { 0,  0}, { 0,  0}, { 0,  0}}, new int[]{0, 2}),
                new DefaultGamePiece('k', new int[][]{{ 0,  0}, { 0, -1}, { 0, -2}, { 0,  1}, {-1,  1}}, new int[][]{{ 0, -2}, { 0,  1}, {-1,  1}, { 0,  0}, { 0,  0}}, new int[]{0, 1, 2, 3, 4, 5, 6, 7}),
                new DefaultGamePiece('l', new int[][]{{ 0,  0}, { 0, -1}, { 0, -2}, {-1,  0}, {-1,  1}}, new int[][]{{ 0, -2}, {-1,  0}, {-1,  1}, { 0,  0}, { 0,  0}}, new int[]{0, 1, 2, 3, 4, 5, 6, 7}),
                new DefaultGamePiece('m', new int[][]{{ 0,  0}, { 0, -1}, { 0,  1}, {-1,  0}, {-1,  1}}, new int[][]{{ 0, -1}, {-1,  0}, {-1,  1}, { 0,  1}, { 0,  0}}, new int[]{0, 1, 2, 3, 4, 5, 6, 7}),
                new DefaultGamePiece('n', new int[][]{{ 0,  0}, { 0, -1}, { 0,  1}, {-1, -1}, {-1,  1}}, new int[][]{{-1, -1}, { 0, -1}, {-1,  1}, { 0,  1}, { 0,  0}}, new int[]{0, 1, 2, 6}),
                new DefaultGamePiece('o', new int[][]{{ 0,  0}, { 0, -1}, { 1,  0}, { 0,  1}, { 0,  2}}, new int[][]{{ 0,  2}, { 1,  0}, { 0, -1}, { 0,  0}, { 0,  0}}, new int[]{0, 1, 2, 3, 4, 5, 6, 7}),
                new DefaultGamePiece('p', new int[][]{{ 0,  0}, { 0, -1}, { 0,  1}, {-1,  1}, { 1,  1}}, new int[][]{{ 0, -1}, {-1,  1}, { 1,  1}, { 0,  0}, { 0,  0}}, new int[]{0, 2, 3, 4}),
                new DefaultGamePiece('q', new int[][]{{ 0,  0}, { 0, -1}, { 0, -2}, { 1,  0}, { 2,  0}}, new int[][]{{ 0,  0}, { 0, -2}, { 2,  0}, { 0,  0}, { 0,  0}}, new int[]{0, 1, 2, 3}),
                new DefaultGamePiece('r', new int[][]{{ 0,  0}, { 0, -1}, {-1, -1}, { 1,  0}, { 1,  1}}, new int[][]{{ 0,  0}, { 0, -1}, {-1, -1}, { 1,  0}, { 1,  1}}, new int[]{0, 1, 2, 3}),
                new DefaultGamePiece('s', new int[][]{{ 0,  0}, { 1,  0}, { 1,  1}, {-1,  0}, {-1, -1}}, new int[][]{{ 1,  0}, { 1,  1}, {-1,  0}, {-1, -1}, { 0,  0}}, new int[]{0, 1, 2, 3}),
                new DefaultGamePiece('t', new int[][]{{ 0,  0}, { 1,  0}, { 0,  1}, {-1,  0}, {-1, -1}}, new int[][]{{ 1,  0}, { 0,  1}, {-1,  0}, {-1, -1}, { 0,  0}}, new int[]{0, 1, 2, 3, 4, 5, 6, 7}),
                new DefaultGamePiece('u', new int[][]{{ 0,  0}, { 1,  0}, { 0,  1}, {-1,  0}, { 0, -1}}, new int[][]{{ 1,  0}, { 0,  1}, {-1,  0}, { 0, -1}, { 0,  0}}, new int[]{0})
        };

        for (DefaultGamePiece defaultGamePiece : defaultGamePieces) {
            ArrayList<GamePiece> newDefaultGamePiece = new ArrayList<>();

            for (int variant : defaultGamePiece.variants) {
                GamePiece newVariant = new GamePiece(defaultGamePiece.codeName, defaultGamePiece.squares, defaultGamePiece.anchors);
                newVariant.transformPiece(variant);
                newDefaultGamePiece.add(newVariant);
            }

            initialSetOfGamePieces.add(newDefaultGamePiece);
        }


        return initialSetOfGamePieces;
    }

    public char getCodeName() {
        return codeName;
    }

    public void transformPiece(int transformation) {
        this.transformation = transformation;

        for (Position square : squares)
            square.transform(transformations[transformation]);

        for (Position anchor : anchors)
            anchor.transform(transformations[transformation]);
    }

    public Position[] getSquares() {
        return squares;
    }

    public Position[] getAnchors() {
        return anchors;
    }

    public int getTransformation() {
        return transformation;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        GamePiece gamePiece = (GamePiece) o;
        return codeName == gamePiece.codeName &&
                transformation == gamePiece.transformation;
    }

    @Override
    public int hashCode() {
        return Objects.hash(codeName, transformation);
    }
}
