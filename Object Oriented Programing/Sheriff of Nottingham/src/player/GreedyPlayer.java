// Copyright Robert Lica robertlica21@gmail.com
package com.tema1.player;

import com.tema1.common.Constants;
import com.tema1.gameLogic.Game;
import com.tema1.goods.GoodsFactory;
import com.tema1.goods.GoodsType;
import com.tema1.player.inventory.Cards;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;

public final class GreedyPlayer extends AbstractPlayer {

    public GreedyPlayer() {
        super();
    }

    @Override
    public void prepareBag(final ArrayList<Integer> hand) {
        this.makeHand(hand);
        this.makeCards();
        this.setDeclaredGoodId(this.selectGoods());
    }


    private Integer selectGoods() {
        Collections.sort(this.getBag(), new GreedyComparator());
        // when he wants to put a legal good and we don't have 8 legals goods
        if (Game.getInstance().getRound() % 2 != 0 || this.getBag().get(0).getNumber()
                >= Constants.getMaximumNumberOfCardsInBag()) {
            if (this.getBag().get(0).getType().equals(GoodsType.Legal)) {
                this.getBag().subList(1, this.getBag().size()).clear();
                if (this.getBag().get(0).getNumber() > Constants.getMaximumNumberOfCardsInBag()) {
                    this.getBag().get(0).setNumber(Constants.getMaximumNumberOfCardsInBag());
                }
                return this.getBag().get(0).getId();
            } else {
                this.getBag().subList(1, this.getBag().size()).clear();
                this.getBag().get(0).setNumber(1);
                return GoodsFactory.LegalGoodsIds.APPLE;
            }
        }  else { // when he wants to put an illegal good
            if (this.getBag().get(0).getType().equals(GoodsType.Legal)) {
                int index = -1;
                boolean flag = false;
                for (Cards c : this.getBag()) {
                    ++index;
                    if (c.getType().equals(GoodsType.Illegal)) {
                        flag = true;
                        break;
                    }
                }
                if (flag) {
                    if (this.getMoney()
                            - GoodsFactory.getInstance().
                            getGoodsById(this.getBag().get(index).getId())
                                    .getPenalty() >= 0) {
                        this.getBag().subList(index + 1, this.getBag().size()).clear();
                        this.getBag().subList(1, index).clear();
                        this.getBag().get(1).setNumber(1);
                    } else {
                        this.getBag().subList(1, this.getBag().size()).clear();
                    }
                } else {
                    this.getBag().subList(1, this.getBag().size()).clear();
                }
                return this.getBag().get(0).getId();
            } else {
                // if even round and only illegals in hand
                if (this.getBag().get(0).getNumber() >= 2) {
                    this.getBag().subList(1, this.getBag().size()).clear();
                    this.getBag().get(0).setNumber(2);
                } else {
                    this.getBag().subList(2, this.getBag().size()).clear();
                    this.getBag().get(1).setNumber(1);
                }
                return GoodsFactory.LegalGoodsIds.APPLE;
            }
        }
    }

    @Override
    public void inspect(final ArrayList<AbstractPlayer> players, final List<Integer> cardsDeck) {
        boolean hasLied;
        for (AbstractPlayer player : players) {
            if (player == this) {
                continue;
            }
            if (this.getMoney() >= Constants.getMinimumMoneyToInspect()) {
                if (player.getBribe() > 0) {
                    this.addMoney(player.getBribe());
                    player.setBribe(0);
                    continue;
                }
                hasLied = false;
                for (Cards c : player.getBag()) {
                    if (!player.getDeclaredGoodId().equals(c.getId())) {
                        hasLied = true;
                        break;
                    }
                }
                if (hasLied) {
                    this.addMoney(player.caught(cardsDeck));
                } else {
                    this.addMoney(player.innocentAccused());
                }
            } else {
                break;
            }
        }
    }

    @Override
    public int caught(final List<Integer> cardsDeck) {
        // returns a positive value so the serif adds it to its money
        int sum = 0;
        for (Cards c : this.getBag()) {
            if (!this.getDeclaredGoodId().equals(c.getId())) {
                sum += c.getNumber() * GoodsFactory.getInstance().
                        getGoodsById(c.getId()).getPenalty();
            }
        }
        this.addMoney((-1) * sum);


        if (this.getBag().size() == 1) {
            cardsDeck.add(this.getBag().get(0).getId());
            this.getBag().remove(0);
        } else {
            cardsDeck.add(this.getBag().get(1).getId());
        }

        ArrayList<Cards> temp = new ArrayList<Cards>();
        for (Cards c : this.getBag()) {
            if (this.getDeclaredGoodId().equals(c.getId())) {
                temp.add(c);
            }
        }
        this.getBag().clear();
        this.getBag().addAll(temp);
        return sum;
    }

    @Override
    public int innocentAccused() {
        // returns a negative value so the serifs subtracts its penalty
        int sum = this.getBag().get(0).getNumber()
                * GoodsFactory.getInstance().
                getGoodsById(this.getBag().get(0).getId()).getPenalty();
        this.addMoney(sum);
        return (-1) * sum;
    }

    @Override
    public String getRole() {
        return "GREEDY";
    }

    private static class GreedyComparator implements Comparator<Cards> {
        @Override
        public int compare(final Cards a, final Cards b) {
            if (a.getType().equals(GoodsType.Legal)
                    && b.getType().equals(GoodsType.Illegal)) {
                return -1;
            } else if (a.getType().equals(GoodsType.Illegal)
                    && b.getType().equals(GoodsType.Legal)) {
                return 1;
            } else if (a.getType().equals(GoodsType.Illegal)
                    && b.getType().equals(GoodsType.Illegal)) {
                // We put the illegal good with the higher profitin front of the other
                // illegal goods
                if (GoodsFactory.getInstance().getGoodsById(a.getId()).getProfit()
                        > GoodsFactory.getInstance().getGoodsById(b.getId()).getProfit()) {
                    return -1;
                } else if (GoodsFactory.getInstance().getGoodsById(a.getId()).getProfit()
                        < GoodsFactory.getInstance().getGoodsById(b.getId()).getProfit()) {
                    return 1;
                } else {
                    System.out.println("\t***ERROR!!!***\n\rNu trebuia sa existe bunuri"
                            + "ilegale cu acelasi profit");
                    System.exit(-1);
                    return 0;
                }
            } else {
                // we check for the higher frequency
                if (a.getNumber() > b.getNumber()) {
                    return -1;
                } else if (a.getNumber() < b.getNumber()) {
                    return 1;
                } else {
                    // we check fot the higher value
                    if (GoodsFactory.getInstance().getGoodsById(a.getId()).getProfit()
                            > GoodsFactory.getInstance().getGoodsById(b.getId()).getProfit()) {
                        return -1;
                    } else if (GoodsFactory.getInstance().getGoodsById(a.getId()).getProfit()
                            < GoodsFactory.getInstance().getGoodsById(b.getId()).getProfit()) {
                        return 1;
                    } else {
                        // we check for the bigger id
                        if (a.getId() > b.getId()) {
                            return -1;
                        } else {
                            return 1;
                        }
                    }
                }
            }
        }
    }
}
