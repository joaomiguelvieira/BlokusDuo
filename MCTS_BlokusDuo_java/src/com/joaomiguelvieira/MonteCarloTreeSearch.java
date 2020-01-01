package com.joaomiguelvieira;

import java.util.ArrayList;
import java.util.stream.Collectors;

public class MonteCarloTreeSearch {
    private static final int WIN_SCORE = 10;
    private static final int DEFAULT_DURATION_MILLIS = 1000;

    private int moveDurationMillis = DEFAULT_DURATION_MILLIS;
    private Tree gameTree;
    private ArrayList<ArrayList<GamePiece>> gamePieceSet1, gamePieceSet2;

    public MonteCarloTreeSearch() {
        gameTree = new Tree();
        gamePieceSet1 = GamePiece.getInitialSetOfGamePieces();
        gameTree.getRoot().getState().setOpponent(new Player(gamePieceSet1));
        gamePieceSet2 = GamePiece.getInitialSetOfGamePieces();
        gameTree.getRoot().getState().setPlayer(new Player(gamePieceSet2));
    }

    public int checkStatus() {
        return gameTree.getRoot().getState().checkStatus();
    }

    public String findNextMove() {
        long start = System.currentTimeMillis();
        long end = start + moveDurationMillis;

        while (System.currentTimeMillis() < end) {
            // selection
            Node promisingNode = selectPromisingNode(gameTree.getRoot());

            // expansion
            if (promisingNode.getState().checkStatus() == State.IN_PROGRESS)
                expandNode(promisingNode);

            // simulation
            Node nodeToExplore = promisingNode;
            if (!promisingNode.getChildArray().isEmpty())
                nodeToExplore = promisingNode.getRandomChildNode();

            int[] playoutResult = simulateRandomPlayout(nodeToExplore);

            // update
            backPropagation(nodeToExplore, playoutResult[0], playoutResult[1]);
        }

        //System.out.println("Simulations: " + gameTree.getRoot().getState().getVisitCount());

        Node winnerNode = gameTree.getRoot().getChildWithMaxScore();
        return Move.moveToString(winnerNode.getState().getMove());
    }

    private Node selectPromisingNode(Node rootNode) {
        Node node = rootNode;
        while (!node.getChildArray().isEmpty()) {
            node = UCT.findBestNodeWithUCT(node);
        }

        return node;
    }

    private void expandNode(Node node) {
        ArrayList<State> possibleStates = node.getState().getAllPossibleStates();

        for (State possibleState : possibleStates) {
            Node newNode = new Node(possibleState);
            newNode.setParent(node);
            node.getChildArray().add(newNode);
        }
    }

    private int[] simulateRandomPlayout(Node node) {
        Node tempNode = new Node(node);
        State tempState = tempNode.getState();
        int status = tempState.checkStatus();

        Player opponent = gameTree.getRoot().getState().getPlayer();
        if (status == opponent.getPlayerId()) {
            tempNode.getParent().getState().setWinScore(-Double.MAX_VALUE);
            return new int[]{status, tempState.getScore()};
        }
        while (status == State.IN_PROGRESS) {
            tempState.togglePlayer();
            tempState.randomPlay();
            status = tempState.checkStatus();
        }

        return new int[]{status, tempState.getScore()};
    }

    private void backPropagation(Node nodeToExplore, int playerId, int winScore) {
        Node tempNode = nodeToExplore;
        while (tempNode != null) {
            tempNode.getState().incrementVisit();
            if (tempNode.getState().getPlayer().getPlayerId() == playerId) {
                tempNode.getState().addScore(winScore);
                tempNode.getState().incrementWinCount();
            }
            tempNode = tempNode.getParent();
        }
    }

    public int performNextMove(String move) {
        if (gameTree.getRoot().getChildArray().isEmpty())
            expandNode(gameTree.getRoot());

        for (Node child : gameTree.getRoot().getChildArray()) {
            if (Move.moveToString(child.getState().getMove()).equals(move)) {
                gameTree.setRoot(child);

                return 0;
            }
        }

        System.out.println("Error! Move could not be predicted! Doing Nothing!");
        return -1;
    }

    public void printValidMoves() {
        if (gameTree.getRoot().getChildArray().isEmpty())
            expandNode(gameTree.getRoot());

        System.out.print("Here's all valid moves: ");
        for (Node child : gameTree.getRoot().getChildArray())
            System.out.println(Move.moveToString(child.getState().getMove()));
        System.out.println();
    }

    public void printStatus() {
        State actualState = gameTree.getRoot().getState();

        Player player1 = actualState.getPlayer().getPlayerId() == 1 ? actualState.getPlayer() : actualState.getOpponent();
        Player player2 = actualState.getPlayer().getPlayerId() == 2 ? actualState.getPlayer() : actualState.getOpponent();

        System.out.println("----------------- Available Tiles -----------------");

        char[] allGamePieces = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u'};
        System.out.print("          ");
        for (char gamePiece : allGamePieces)
            System.out.print(gamePiece + " ");
        System.out.println();

        for (char gamePiece : allGamePieces) {
            if (player1.getRemainingGamePieces().stream().noneMatch(p -> p.get(0).getCodeName() == gamePiece))
                System.out.print("0 ");
            else
                System.out.print("1 ");
        }
        System.out.println();

        for (char gamePiece : allGamePieces) {
            if (player2.getRemainingGamePieces().stream().noneMatch(p -> p.get(0).getCodeName() == gamePiece))
                System.out.print("0 ");
            else
                System.out.print("1 ");
        }
        System.out.println();

        System.out.println("---------------------------------------------------");

        if (player1.getScore() > player2.getScore())
            System.out.println("Player 2 is winning!");
        else if (player1.getScore() < player2.getScore())
            System.out.println("Player 1 is winning!");
        else
            System.out.println("Game is a draw!");

        System.out.println("---------------------- Board ----------------------");
        actualState.getBoard().printBoard();
        System.out.println("---------------------------------------------------");

        System.out.println("Player " + actualState.getOpponent().getPlayerId() + ": ");
    }

    public void printMove() {
        State actualState = gameTree.getRoot().getState();
        String move = Move.moveToString(actualState.getMove());
        if (!move.equals("0000"))
            System.out.println(move);
    }
}
