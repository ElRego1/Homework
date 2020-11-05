// Copyright Robert Lica robertlica21@gmail.com
package com.tema1.gameLogic;

import com.tema1.common.Constants;
import com.tema1.goods.GoodsFactory;
import com.tema1.goods.GoodsType;
import com.tema1.main.GameInput;
import com.tema1.player.AbstractPlayer;
import com.tema1.player.BasicPlayer;
import com.tema1.player.BribePlayer;
import com.tema1.player.GreedyPlayer;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;

public final class Game {
    private static Game instance = null;
    private int noRounds;
    private int round;
    private ArrayList<Integer> cards;
    private ArrayList<String> playersRoles;
    private ArrayList<AbstractPlayer> players;

    static {
        instance = new Game();
    }
    private Game() { }

    public void setGame(final GameInput gameInput) {
        this.noRounds = gameInput.getRounds();
        this.cards = new ArrayList<Integer>();
        cards.addAll(gameInput.getAssetIds());
        round = 0;
        this.playersRoles = (ArrayList<String>) gameInput.getPlayerNames();
        players = new ArrayList<AbstractPlayer>();
        for (String s : playersRoles) {
            if (s.equalsIgnoreCase("basic")) {
                players.add(new BasicPlayer());
            } else if (s.equalsIgnoreCase("greedy")) {
                players.add(new GreedyPlayer());
            } else if (s.equalsIgnoreCase("bribed")) {
//                if (playersRoles.size() == 2) {
                    players.add(new BribePlayer());
//                }
            } else {
                System.out.println("ERROR: Invalid input, a role hasn't been recognized");
            }
        }
        for (int i = 0; i < players.size(); ++i) {
            players.get(i).setBribeTargets(players.get((i + players.size() - 1) % players.size()),
                    players.get((i + players.size() + 1) % players.size()));
        }
    }

    public void play() {
        // round
        for (int i = 0; i < noRounds; ++i) {
            round = i + 1;
            // sub-round
            for (AbstractPlayer serif : players) {
                // prepare traders
                for (AbstractPlayer player : players) {
                    if (player == serif) {
                        continue;
                    }
                    ArrayList<Integer> tempCardDeck = new ArrayList<Integer>();
                    tempCardDeck.addAll(cards.subList(0, Constants.getCardNumberToExtract()));
                    player.prepareBag(tempCardDeck);
                    cards.subList(0, Constants.getCardNumberToExtract()).clear();
                }
                serif.inspect(players, cards);
                for (AbstractPlayer player : players) {
                    if (player == serif) {
                        continue;
                    }
                    player.putOnTheStall();
                }
            }
        }

        // add illegal bonus
        for (AbstractPlayer player : players) {
            ArrayList<Integer> bonuses = new ArrayList<Integer>();
            for (Integer i : player.getStall()) {
                if (GoodsFactory.getInstance().getGoodsById(i).getType().
                        equals(GoodsType.Illegal)) {
                    if (i.equals(GoodsFactory.IllegalGoodsIds.SILK)) {
                        bonuses.add(GoodsFactory.LegalGoodsIds.CHEESE);
                        bonuses.add(GoodsFactory.LegalGoodsIds.CHEESE);
                        bonuses.add(GoodsFactory.LegalGoodsIds.CHEESE);
                    } else if (i.equals(GoodsFactory.IllegalGoodsIds.PEPPER)) {
                        bonuses.add(GoodsFactory.LegalGoodsIds.CHICKEN);
                        bonuses.add(GoodsFactory.LegalGoodsIds.CHICKEN);
                    } else if (i.equals(GoodsFactory.IllegalGoodsIds.BARREL)) {
                        bonuses.add(GoodsFactory.LegalGoodsIds.BREAD);
                        bonuses.add(GoodsFactory.LegalGoodsIds.BREAD);
                    } else if (i.equals(GoodsFactory.IllegalGoodsIds.BEER)) {
                        bonuses.add(GoodsFactory.LegalGoodsIds.WINE);
                        bonuses.add(GoodsFactory.LegalGoodsIds.WINE);
                        bonuses.add(GoodsFactory.LegalGoodsIds.WINE);
                        bonuses.add(GoodsFactory.LegalGoodsIds.WINE);
                    } else if (i.equals(GoodsFactory.IllegalGoodsIds.SEAFOOD)) {
                        bonuses.add(GoodsFactory.LegalGoodsIds.TOMATO);
                        bonuses.add(GoodsFactory.LegalGoodsIds.TOMATO);

                        bonuses.add(GoodsFactory.LegalGoodsIds.POTATO);
                        bonuses.add(GoodsFactory.LegalGoodsIds.POTATO);
                        bonuses.add(GoodsFactory.LegalGoodsIds.POTATO);

                        bonuses.add(GoodsFactory.LegalGoodsIds.CHICKEN);
                    } else {
                        System.out.println("ERROR: Nu trebuia sa ajunga"
                                + " aici. Nu am gasit id-ul unui bun ilegal la bonusuri");
                    }
                }
            }
            player.getStall().addAll(bonuses);
        }

        addProfit();

        makeKingAndQueen();

        printResults();
    }

    private void printResults() {
        ArrayList<PrintPlayer> vector = new ArrayList<PrintPlayer>();
        for (int i = 0; i < players.size(); ++i) {
            vector.add(new PrintPlayer(i, players.get(i).getMoney(), players.get(i)));
        }
        Collections.sort(vector, new PrintPlayerComparator());
        for (PrintPlayer p : vector) {
            System.out.println(p);
        }
    }

    private void makeKingAndQueen() {
        for (int i = 0; i < Constants.getNumberOfLegalGoodsTypes(); ++i) {
            ArrayList<KingAndQueen> bonus = new ArrayList<KingAndQueen>();
            for (int j = 0; j < players.size(); ++j) {
                int counter  = 0;
                for (Integer k : players.get(j).getStall()) {
                    if (k == i) {
                        ++counter;
                    }
                }
                if (counter != 0) {
                    bonus.add(new KingAndQueen(players.get(j), j, counter));
                }
            }
            Collections.sort(bonus, new KingAndQueenComparator());
            if (bonus.size() >= 2) {
                bonus.get(0).player.addMoney(GoodsFactory.getInstance().
                        getGoodsById(i).getKingBonus());
                bonus.get(1).player.addMoney(GoodsFactory.getInstance().
                        getGoodsById(i).getQueenBonus());
            } else if (bonus.size() == 1) {
                bonus.get(0).player.addMoney(GoodsFactory.getInstance().
                        getGoodsById(i).getKingBonus());
            }
        }
    }

    private void addProfit() {
        for (AbstractPlayer player : players) {
            for (Integer i : player.getStall()) {
                player.addMoney(GoodsFactory.getInstance().getGoodsById(i).getProfit());
            }
        }
    }

    public int getRound() {
        return round;
    }

    public static Game getInstance() {
        return instance;
    }

    private class PrintPlayer {
        private int playerID;
        private String nameToPrint;
        private int points;

        PrintPlayer(final int playerID, final int points, final AbstractPlayer player) {
            this.playerID = playerID;
            this.points = points;
            nameToPrint = player.getRole();
        }

        public int getPlayerID() {
            return playerID;
        }

        public int getPoints() {
            return points;
        }

        @Override
        public String toString() {
            return playerID + " " + nameToPrint + " " + points;
        }
    }
    private class PrintPlayerComparator implements Comparator<PrintPlayer> {
        @Override
        public final int compare(final PrintPlayer a, final PrintPlayer b) {
            if (a.getPoints() > b.getPoints()) {
                return -1;
            } else if (a.getPoints() < b.getPoints()) {
                return 1;
            } else {
                if (a.getPlayerID() < b.getPlayerID()) {
                    return -1;
                } else {
                    return 1;
                }
            }
        }
    }
    private class KingAndQueen {
        private AbstractPlayer player;
        private Integer playerID;
        private int number;

        KingAndQueen(final AbstractPlayer player, final Integer playerID, final int number) {
            this.player = player;
            this.playerID = playerID;
            this.number = number;
        }

        public AbstractPlayer getPlayer() {
            return player;
        }

        public Integer getPlayerID() {
            return playerID;
        }

        public int getNumber() {
            return number;
        }
    }
    private class KingAndQueenComparator implements Comparator<KingAndQueen> {
        @Override
        public final int compare(final KingAndQueen a, final KingAndQueen b) {
            if (a.getNumber() > b.getNumber()) {
                return -1;
            } else if (a.getNumber() < b.getNumber()) {
                return 1;
            } else {
                if (a.getPlayerID() < b.getPlayerID()) {
                    return -1;
                } else {
                    return 1;
                }
            }
        }
    }
}
