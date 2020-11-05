// Copyright Robert Lica robertlica21@gmail.com
package game;

import common.Constants;
import fileio.FileSystem;
import map.Cell;
import map.Map;
import player.AbstractPlayer;

import java.beans.PropertyChangeListener;
import java.beans.PropertyChangeSupport;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Arrays;

public final class Game {
    private PropertyChangeSupport support;
    private FileSystem fs;
    private ArrayList<AbstractPlayer> players;
    private Map map;
    private ArrayList<Cell> combatCells;

    public Game(final String inputFile, final String outputFile) {
        try {
            this.support = new PropertyChangeSupport(this);
            this.fs = GameFactory.getInstance().loadGame(inputFile, outputFile);
            this.players = GameFactory.getInstance().getPlayers();
            this.players.forEach(this::addPropertyChangeListener);
            this.map = GameFactory.getInstance().getMap();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void playGame() {
        try {
            int rounds = fs.nextInt();
            for (int i = 1; i <= rounds; ++i) {
                combatCells = new ArrayList<>();
                // make the movement
                makeMoves(i);
                // take into account the status effects
                this.giveStatusEffects(i);
                // battle
                combatCells.forEach(this::battle);
                // if we have a dead player, do not notify him of status
                // effects and remove him from the list
                Arrays.stream(support.getPropertyChangeListeners()).forEach(player -> {
                    if (((AbstractPlayer) player).getHp() <= 0) {
                        this.removePropertyChangeListener(player);
                    }
                });
            }
            this.makeOutput();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void endGame() {
        try {
            fs.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private void makeOutput() {
        players.forEach(player -> {
            try {
                this.fs.writeWord(player.getInitialOfClass() + " ");
                if (player.getHp() <= 0) {
                    this.fs.writeWord(Constants.DEAD_STATUS_PRINT);
                    this.fs.writeNewLine();
                } else {
                    this.fs.writeWord(player.getLvl() + " " + player.getExp() + " "
                            + player.getHp() + " " + player.getCurrentCell().getX() + " "
                            + player.getCurrentCell().getY());
                    this.fs.writeNewLine();
                }
            } catch (IOException e) {
                e.printStackTrace();
            }
        });
    }

    private void battle(final Cell battleground) {
        if (battleground.getPlayersInCell().size() > 2) {
            System.out.println("\t\t***CEVA Nu este bine ca in battle sunt mai mult de 2 -> "
                    + battleground.getPlayersInCell().size());
        } else if (battleground.getPlayersInCell().size() == 2) {
            AbstractPlayer player0 = battleground.getPlayersInCell().get(0);
            AbstractPlayer player1 = battleground.getPlayersInCell().get(1);
            player0.setHpBeforeBattle(player0.getHp());
            player1.setHpBeforeBattle(player1.getHp());
            // 1 attacks 0
            player0.attackedBy(player1);
            // 0 attacks 1
            player1.attackedBy(player0);
            giveExpAndMakeDead(battleground, player1, player0);
            giveExpAndMakeDead(battleground, player0, player1);
        }
    }

    private void giveExpAndMakeDead(final Cell battleground,
                                    final AbstractPlayer player0, final AbstractPlayer player1) {
        if (player1.getHp() <= 0) {
            support.removePropertyChangeListener(player1);
            player1.setHp(0);
            player0.addExp(Math.max(0, Constants.EXP_INFERIOR_LIMIT
                    - (player0.getLvl() - player1.getLvl()) * Constants.EXP_GAIN_MODIF));
            battleground.getPlayersInCell().remove(player1);
        }
    }

    private void makeMoves(final int round) throws IOException {
        String move = fs.nextWord();
        for (AbstractPlayer player : players) {
            if (player.getHp() > 0) {
                if (player.getImmobilizedTime() <= 0) {
                    switch (move.substring(0, 1)) {
                        case "U":
                            player.setCurrentCell(map.getCell(player.getCurrentCell().getX() - 1,
                                    player.getCurrentCell().getY()));
                            break;
                        case "D":
                            player.setCurrentCell(map.getCell(player.getCurrentCell().getX() + 1,
                                    player.getCurrentCell().getY()));
                            break;
                        case "L":
                            player.setCurrentCell(map.getCell(player.getCurrentCell().getX(),
                                    player.getCurrentCell().getY() - 1));
                            break;
                        case "R":
                            player.setCurrentCell(map.getCell(player.getCurrentCell().getX(),
                                    player.getCurrentCell().getY() + 1));
                            break;
                        case "_":
                            break;
                        default:
                            System.out.println("\t\t*****ERROR: Invalid Movement Input!!!");
                    }
                }
                if (player.getCurrentCell().getPlayersInCell().stream().
                        anyMatch(playerInCell -> playerInCell.getRound() == round)) {
                    combatCells.add(player.getCurrentCell());
                }
                player.setRound(round);
            }
            move = move.substring(1);
        }
    }

    // add observers
    private void addPropertyChangeListener(final PropertyChangeListener pcl) {
        support.addPropertyChangeListener(pcl);
    }

    // remove observers
    private void removePropertyChangeListener(final PropertyChangeListener pcl) {
        support.removePropertyChangeListener(pcl);
    }

    private void giveStatusEffects(final int round) {
        support.firePropertyChange("Check Status Effects", round - 1, round);
    }

}
