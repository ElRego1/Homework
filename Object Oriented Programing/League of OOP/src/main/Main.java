// Copyright Robert Lica robertlica21@gmail.com
package main;

import game.Game;

public final class Main {
    private Main() {
        // to trick the checkstyle as I'se see in the model for homework 1
    }
    public static void main(final String[] args) {
        Game firstGame = new Game(args[0], args[1]);
        firstGame.playGame();
        firstGame.endGame();
    }
}
