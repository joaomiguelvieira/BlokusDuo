package com.joaomiguelvieira;

import java.util.ArrayList;
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

            if (move.equals("hint"))
                mcts.printValidMoves();
            else if (move.equals("simulate"))
                System.out.println(mcts.findNextMove());
            else if (move.equals("last"))
                System.out.println("Last move was " + last_move);
            else if (mcts.performNextMove(move) == 0)
                last_move = move;
        }
    }

    public static void main(String[] args) {
        playGame();
    }
}
