package com.joaomiguelvieira;

import java.util.Scanner;

public class Main {
    public static void playGame() {
        MonteCarloTreeSearch mcts = new MonteCarloTreeSearch();

        while (mcts.checkStatus() == State.IN_PROGRESS) {
            String bestMove = mcts.findNextMove();
            mcts.performNextMove(bestMove);
            mcts.printMove();
        }
    }

    public static void interactiveGame() {
        MonteCarloTreeSearch mcts = new MonteCarloTreeSearch();

        String last_move = "";
        Scanner scanner = new Scanner(System.in);
        while (mcts.checkStatus() == State.IN_PROGRESS) {
            mcts.printStatus();
            String move = scanner.nextLine();

            if (move.equals("hint") || move.equals("h"))
                mcts.printValidMoves();
            else if (move.equals("simulate") || move.equals("s"))
                System.out.println("Simulated move is " + mcts.findNextMove());
            else if (move.equals("simulate and play") || move.equals("sp")) {
                String nextMove = mcts.findNextMove();
                System.out.println("Simulated move is " + nextMove);
                mcts.performNextMove(nextMove);
            }
            else if (move.equals("last") || move.equals("l"))
                System.out.println("Last move was " + last_move);
            else if (mcts.performNextMove(move) == 0)
                last_move = move;
        }
    }

    public static void main(String[] args) {
        if (args.length > 0) {
            if (args[0].equals("interactive"))
                interactiveGame();
            else if (args[0].equals("auto"))
                playGame();
            else
                System.out.println("Option not recognized... exiting");
        }
        else
            playGame();
    }
}
