// Copyright Robert Lica robertlica21@gmail.com
package com.tema1.main;

import com.tema1.gameLogic.Game;

public final class Main {
    private Main() {
        // just to trick checkstyle
    }

    public static void main(final String[] args) {
        GameInputLoader gameInputLoader = new GameInputLoader(args[0], args[1]);
        GameInput gameInput = gameInputLoader.load();
        //TODO implement homework logic
        Game.getInstance().setGame(gameInput);
        Game.getInstance().play();
    }
}
