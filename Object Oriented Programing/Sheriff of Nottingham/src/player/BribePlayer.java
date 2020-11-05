// Copyright Robert Lica robertlica21@gmail.com
package com.tema1.player;

import com.tema1.common.Constants;
import com.tema1.goods.GoodsFactory;
import com.tema1.goods.GoodsType;
import com.tema1.player.inventory.Cards;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;

public final class BribePlayer extends AbstractPlayer {
    private AbstractPlayer leftControl;
    private AbstractPlayer rightControl;

    public BribePlayer() {
        super();
    }

    @Override
    public void setBribeTargets(final AbstractPlayer left, final AbstractPlayer right) {
        if (left == right) {
            leftControl = left;
            rightControl = null;
        }
        leftControl = left;
        rightControl = right;
    }

    @Override
    public void prepareBag(final ArrayList<Integer> hand) {
        this.makeHand(hand);
        this.makeCards();
        this.setDeclaredGoodId(this.selectGoods());
        redoBribe();
    }

    private Integer selectGoods() {
        Collections.sort(this.getBag(), new BribeComparator());
        if (this.getBag().get(0).getType().equals(GoodsType.Illegal)
                && this.getMoney() > Constants.getMinimumMoneyForBribeToPlayIllegal()) {
            ArrayList<Integer> toPut = new ArrayList<Integer>();
            int debt = 0;
            toPut.add(this.getBag().get(0).getId());
            this.getBag().get(0).setNumber(this.getBag().get(0).getNumber() - 1); // --
            if (this.getBag().get(0).getNumber() == 0) {
                this.getBag().remove(0);
            }
            this.setBribe(Constants.getBribeFirstRank());
            this.addMoney((-1) * Constants.getBribeFirstRank());
            debt += GoodsFactory.ILLEGAL_PENALTY;

            while (this.getBag().get(0).getType().equals(GoodsType.Illegal)
                    && toPut.size() < Constants.getMaximumNumberOfCardsInBag()) {
                if (this.getMoney() + this.getBribe() - debt > GoodsFactory.ILLEGAL_PENALTY) {
                    toPut.add(this.getBag().get(0).getId());
                    this.getBag().get(0).setNumber(this.getBag().get(0).getNumber() - 1); // --
                    if (this.getBag().get(0).getNumber() == 0) {
                        this.getBag().remove(0);
                    }
                    debt += GoodsFactory.ILLEGAL_PENALTY;
                } else { // if it has money only for one legal from now on
                    if (this.getMoney() + this.getBribe() - debt > GoodsFactory.LEGAL_PENALTY) {
                        for (Cards c : this.getBag()) {
                            if (c.getType().equals(GoodsType.Legal)) {
                                toPut.add(c.getId());
                                debt += GoodsFactory.LEGAL_PENALTY;
                                break;
                            }
                        }
                    }

                    this.getBag().clear();
                    this.makeCards(toPut);
                    return GoodsFactory.LegalGoodsIds.APPLE;
                }
                // we increase the bribe
                if (this.getBribe() == Constants.getBribeFirstRank()
                        && toPut.size() == 2) { // the second check should be useless
                    if (this.getMoney() + this.getBribe() >= Constants.getBribeSecondRank()) {
                        this.setBribe(Constants.getBribeSecondRank());
                        this.addMoney((-1)
                                * (Constants.getBribeSecondRank() - Constants.getBribeFirstRank()));
                    } else {
                        break;
                    }
                }
            }

            while (this.getBag().size() > 0
                    && this.getBag().get(0).getType().equals(GoodsType.Illegal)) {
                this.getBag().remove(0);
            }

            while (toPut.size() < Constants.getMaximumNumberOfCardsInBag()
                    && this.getMoney() + this.getBribe() - debt > GoodsFactory.LEGAL_PENALTY) {
                toPut.add(this.getBag().get(0).getId());
                this.getBag().get(0).setNumber(this.getBag().get(0).getNumber() - 1); // --
                if (this.getBag().get(0).getNumber() == 0) {
                    this.getBag().remove(0);
                }
                debt += GoodsFactory.LEGAL_PENALTY;
            }
            this.getBag().clear();
            this.makeCards(toPut);
            return GoodsFactory.LegalGoodsIds.APPLE;
        } else {
            Collections.sort(this.getBag(), new BasicComparator());
            this.getBag().subList(1, this.getBag().size()).clear();
            if (this.getBag().get(0).getNumber() > Constants.getMaximumNumberOfCardsInBag()) {
                this.getBag().get(0).setNumber(Constants.getMaximumNumberOfCardsInBag());
            }
            if (this.getBag().get(0).getType().equals(GoodsType.Legal)) {
                return this.getBag().get(0).getId();
            } else {
                this.getBag().get(0).setNumber(1);
                return GoodsFactory.LegalGoodsIds.APPLE;
            }
        }
    }

    @Override
    public void inspect(final ArrayList<AbstractPlayer> players, final List<Integer> cardsDeck) {
        // cerinta neclara daca bribe-ul verifica inainte stangul si apoi dreptul si abia apoi pe
        // restul s-ar putea sa nu conteze
        if (this.getMoney() >= Constants.getMinimumMoneyToInspect()) {
            checkSpecial(leftControl, cardsDeck);
        }
        if (this.getMoney() >= Constants.getMinimumMoneyToInspect()
                && rightControl != leftControl) {
            checkSpecial(rightControl, cardsDeck);
        }
        for (AbstractPlayer player : players) {
            if (this == player || player == leftControl || player == rightControl) {
                continue;
            }
            if (player.getBribe() > 0) {
                this.addMoney(player.getBribe());
                player.setBribe(0);
            }
        }
    }

    private void checkSpecial(final AbstractPlayer player, final List<Integer> cardsDeck) {
        if (player == null) {
            return;
        }
        for (Cards c : player.getBag()) {
            if (!c.getId().equals(player.getDeclaredGoodId())) {
                this.addMoney(player.caught(cardsDeck));
                return;
            }
        }
        this.addMoney(player.innocentAccused());
    }


    @Override
    public int caught(final List<Integer> cardsDeck) {
        // returns a positive value so the serif adds it to its money
        int sum = 0;
        ArrayList<Integer> backToIntegers = new ArrayList<Integer>();
        for (Cards c : this.getBag()) {
            for (int i = 0; i < c.getNumber(); ++i) {
                backToIntegers.add(c.getId());
            }
        }

        for (Integer i : this.getHand()) {
            if (backToIntegers.indexOf(i) >= 0 && !i.equals(this.getDeclaredGoodId())) {
                cardsDeck.add(i);
                backToIntegers.remove(i);
            }
        }

        ArrayList<Cards> remainingBag = new ArrayList<Cards>();
        for (Cards c : this.getBag()) {
            if (c.getId().equals(this.getDeclaredGoodId())) {
                remainingBag.add(c);
            } else {
                sum += c.getNumber() * GoodsFactory.getInstance().
                        getGoodsById(c.getId()).getPenalty();
            }
        }
        this.addMoney((-1) * sum);

        this.getBag().clear();
        this.getBag().addAll(remainingBag);
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
        return "BRIBED";
    }

    private void redoBribe() {
        int counter = 0;
        for (Cards c : this.getBag()) {
            if (c.getType().equals(GoodsType.Illegal)) {
                counter += c.getNumber();
            }
        }

        if (counter <= 2 && this.getBribe() == Constants.getBribeSecondRank()) {
            this.addMoney(Constants.getBribeFirstRank());
            this.setBribe(Constants.getBribeFirstRank());
        }
    }

    private class BribeComparator implements Comparator<Cards> {
        @Override
        public final int compare(final Cards a, final Cards b) {
            // we check if it's legal or not
            if (a.getType().equals(GoodsType.Illegal)
                    && b.getType().equals(GoodsType.Legal)) {
                return -1;
            } else if (a.getType().equals(GoodsType.Legal)
                    && b.getType().equals(GoodsType.Illegal)) {
                return 1;
            } else if (a.getType().equals(GoodsType.Illegal)
                    && b.getType().equals(GoodsType.Illegal)) {
                if (GoodsFactory.getInstance().getGoodsById(a.getId()).getProfit()
                        > GoodsFactory.getInstance().getGoodsById(b.getId()).getProfit()) {
                    return -1;
                } else if (GoodsFactory.getInstance().getGoodsById(a.getId()).getProfit()
                        < GoodsFactory.getInstance().getGoodsById(b.getId()).getProfit()) {
                    return 1;
                } else {
                    return 0;
                }
            } else if (a.getType().equals(GoodsType.Legal) && b.getType().equals(GoodsType.Legal)) {
                if (GoodsFactory.getInstance().getGoodsById(a.getId()).getProfit()
                        > GoodsFactory.getInstance().getGoodsById(b.getId()).getProfit()) {
                    return -1;
                } else if (GoodsFactory.getInstance().getGoodsById(a.getId()).getProfit()
                        < GoodsFactory.getInstance().getGoodsById(b.getId()).getProfit()) {
                    return 1;
                } else {
                    if (a.getId() > b.getId()) {
                        return -1;
                    } else if (a.getId() < b.getId()) {
                        return 1;
                    } else {
                        return 0;
                    }
                }
            }
            System.out.println("ERROR: Nu trebuia sa se ajunga aici: " + this
                    + "\t ID-urile nu trebuiau sa fie egale in logica mea, ID-urile sunt: a:"
                    + a.getId() + " b: " + b.getId());
            return 0;
        }
    }
}
