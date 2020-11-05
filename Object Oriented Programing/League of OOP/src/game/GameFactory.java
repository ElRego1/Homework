// Copyright Robert Lica robertlica21@gmail.com
package game;

import common.Constants;
import fileio.FileSystem;
import java.io.IOException;
import java.util.ArrayList;
import map.Map;
import player.AbstractPlayer;
import player.Pyromancer;
import player.Knight;
import player.Wizard;
import player.Rogue;


public final class GameFactory {
    private static final GameFactory INSTANCE;
    private ArrayList<AbstractPlayer> players;
    private Map map;

    static {
        INSTANCE = new GameFactory();
    }

    private GameFactory() { }

    FileSystem loadGame(final String loadFile, final String saveFile) throws IOException {
        FileSystem fs = new FileSystem(loadFile, saveFile);
        map = new Map();
        map.createMap(fs.nextInt(), fs.nextInt());
        map.setTerrain(fs);
        this.makePlayers(fs);
        return fs;
    }

    private void makePlayers(final FileSystem fs) throws IOException {
        this.players = new ArrayList<AbstractPlayer>();
        int n = fs.nextInt();
        for (int i = n; i > 0; --i) {
            String s = fs.nextWord();
            switch (s) {
                case Constants.PYROMANCER_DECLARATION_CHAR:
                    players.add(new Pyromancer());
                    break;
                case Constants.KNIGHT_DECLARATION_CHAR:
                    players.add(new Knight());
                    break;
                case Constants.WIZARD_DECLARATION_CHAR:
                    players.add(new Wizard());
                    break;
                case Constants.ROGUE_DECLARATION_CHAR:
                    players.add(new Rogue());
                    break;
                default:
                    System.out.println("\t\t*****ERROR: Invalid Hero Definition!!!");
            }
            players.get(players.size() - 1).setCurrentCell(map.getCell(fs.nextInt(), fs.nextInt()));
        }
    }

    public ArrayList<AbstractPlayer> getPlayers() {
        return players;
    }

    public Map getMap() {
        return map;
    }

    public static GameFactory getInstance() {
        return INSTANCE;
    }
}
