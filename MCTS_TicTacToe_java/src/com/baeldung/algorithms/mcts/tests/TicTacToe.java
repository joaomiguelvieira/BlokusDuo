package com.baeldung.algorithms.mcts.tests;

import com.baeldung.algorithms.mcts.montecarlo.MonteCarloTreeSearch;
import com.baeldung.algorithms.mcts.tictactoe.Board;

public class TicTacToe {
    public static void main(String[] args) {
        MonteCarloTreeSearch mcts = new MonteCarloTreeSearch();
        Board board = new Board();

        int player = Board.P1;
        int totalMoves = Board.DEFAULT_BOARD_SIZE * Board.DEFAULT_BOARD_SIZE;
        for (int i = 0; i < totalMoves; i++) {
            board = mcts.findNextMove(board, player);

            //System.out.println("Player: " + player);
            //board.printBoard();

            if (board.checkStatus() != -1) {
                break;
            }
            player = 3 - player;
        }
        int winStatus = board.checkStatus();

        System.out.println(winStatus);
    }
}
