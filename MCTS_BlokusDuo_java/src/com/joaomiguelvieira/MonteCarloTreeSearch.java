package com.joaomiguelvieira;

import java.util.ArrayList;

public class MonteCarloTreeSearch {
    private static final int DEFAULT_DURATION_MILLIS = 1000;

    private Tree gameTree;

    public MonteCarloTreeSearch() {
        gameTree = new Tree();
        gameTree.getRoot().getState().setOpponent(new Player());
        gameTree.getRoot().getState().setPlayer(new Player());
    }

    public int checkStatus() {
        return gameTree.getRoot().getState().checkStatus();
    }

    public String findNextMove() {
        long start = System.currentTimeMillis();
        long end = start + DEFAULT_DURATION_MILLIS;

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

            int[] playoutResult = simulateRandomPlay(nodeToExplore);

            // update
            backPropagation(nodeToExplore, playoutResult[0], playoutResult[1]);
        }

        System.out.println("Round " + gameTree.getRoot().getState().getMovesPlayed() + " -> " + gameTree.getRoot().getState().getVisitCount() + " simulations");

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
        if (!node.getState().getOpponent().getQuited()) {
            // calculate all valid moves
            ArrayList<Move> possibleMoves;

            if (node.getState().getMovesPlayed() < 4)
                possibleMoves = node.getState().getBoard().getAllValidMoves(node.getState().getOpponent());
            else
                possibleMoves = node.getState().getBoard().getAllValidMoves(node.getState().getOpponent(),
                        node.getParent().getParent().getState().getPossibleMoves(),
                        node.getParent().getState().getMove(),
                        node.getParent().getParent().getState().getBoard());

            node.getState().setPossibleMoves(possibleMoves);

            for (Move possibleMove : possibleMoves) {
                // create new state for each valid move
                State newState = new State(node.getState().getBoard());
                newState.setPlayer(new Player(node.getState().getOpponent(), possibleMove.getGamePiece()));
                newState.setOpponent(new Player(node.getState().getPlayer()));
                newState.setMove(possibleMove);
                newState.getBoard().performMove(newState.getPlayer(), possibleMove);
                newState.setMovesPlayed(node.getState().getMovesPlayed() + 1);

                Node newNode = new Node(newState);
                newNode.setParent(node);
                node.getChildArray().add(newNode);
            }
        }

        // create quit state
        State newState = new State(node.getState().getBoard());
        newState.setPlayer(new Player(node.getState().getOpponent()));
        newState.setOpponent(new Player(node.getState().getPlayer()));
        newState.getPlayer().setQuited(true);
        newState.setMovesPlayed(node.getState().getMovesPlayed() + 1);

        Node newNode = new Node(newState);
        newNode.setParent(node);
        node.getChildArray().add(newNode);
    }

    private int[] simulateRandomPlay(Node node) {
        Node actualNode = node;
        int status = actualNode.getState().checkStatus();

        if (status == gameTree.getRoot().getState().getPlayer().getPlayerId()) {
            actualNode.getParent().getState().setWinScore(-Double.MAX_VALUE);
            return new int[]{status, actualNode.getState().getScore()};
        }

        while (status == State.IN_PROGRESS) {
            Node newNode = new Node(new State(actualNode.getState().getBoard()));
            newNode.getState().setMovesPlayed(actualNode.getState().getMovesPlayed() + 1);
            newNode.getState().setOpponent(new Player(actualNode.getState().getPlayer()));
            newNode.setParent(actualNode);

            ArrayList<Move> possibleMoves;
            if (actualNode.getState().getMovesPlayed() < 4)
                possibleMoves = actualNode.getState().getBoard().getAllValidMoves(actualNode.getState().getOpponent());
            else
                possibleMoves = actualNode.getState().getBoard().getAllValidMoves(actualNode.getState().getOpponent(),
                        actualNode.getParent().getParent().getState().getPossibleMoves(),
                        actualNode.getParent().getState().getMove(),
                        actualNode.getParent().getParent().getState().getBoard());

            actualNode.getState().setPossibleMoves(possibleMoves);

            if (possibleMoves.isEmpty()) {
                newNode.getState().setPlayer(new Player(actualNode.getState().getOpponent()));
                newNode.getState().getPlayer().setQuited(true);
            }
            else {
                Move moveToPerform = possibleMoves.get((int) (Math.random() * possibleMoves.size()));
                newNode.getState().setPlayer(new Player(actualNode.getState().getOpponent(), moveToPerform.getGamePiece()));
                newNode.getState().getBoard().performMove(newNode.getState().getPlayer(), moveToPerform);
                newNode.getState().setMove(moveToPerform);
            }

            status = newNode.getState().checkStatus();
            actualNode = newNode;
        }

        return new int[]{status, actualNode.getState().getScore()};
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
        Node node = gameTree.getRoot();

        ArrayList<Move> possibleMoves;

        if (node.getState().getMovesPlayed() < 4)
            possibleMoves = node.getState().getBoard().getAllValidMoves(node.getState().getOpponent());
        else
            possibleMoves = node.getState().getBoard().getAllValidMoves(node.getState().getOpponent(),
                    node.getParent().getParent().getState().getPossibleMoves(),
                    node.getParent().getState().getMove(),
                    node.getParent().getParent().getState().getBoard());

        System.out.print("Here's all valid moves: ");
        for (Move validMove : possibleMoves)
            System.out.print(Move.moveToString(validMove) + " ");
        System.out.println();
    }

    public void printStatus() {
        State actualState = gameTree.getRoot().getState();

        Player player1 = actualState.getPlayer().getPlayerId() == 1 ? actualState.getPlayer() : actualState.getOpponent();
        Player player2 = actualState.getPlayer().getPlayerId() == 2 ? actualState.getPlayer() : actualState.getOpponent();

        System.out.println("----------------- Available Tiles -----------------");

        System.out.println(player1);
        System.out.println(player2);

        System.out.println("---------------------- Board ----------------------");
        System.out.println(actualState.getBoard());
        System.out.println("---------------------------------------------------");

        System.out.println("Round " + gameTree.getRoot().getState().getMovesPlayed());
        System.out.print("Player " + actualState.getOpponent().getPlayerId() + ": ");
    }

    public void printMove() {
        State actualState = gameTree.getRoot().getState();
        String move = Move.moveToString(actualState.getMove());
        if (!move.equals("0000"))
            System.out.println(move);
    }
}
