// Copyright Robert Lica robertlica21@gmail.com
package com.tema1.player;

import com.tema1.common.Constants;
import com.tema1.goods.GoodsFactory;
import com.tema1.player.inventory.Cards;

import java.util.ArrayList;
import java.util.List;

public abstract class AbstractPlayer {
    private int money = Constants.getStartingMoney();
    private int bribe = 0;
    private ArrayList<Integer> hand;
    private ArrayList<Cards> bag;
    private Integer declaredGoodId;
    private ArrayList<Integer> stall;

    AbstractPlayer() {
        hand = new ArrayList<Integer>();
        bag = new ArrayList<Cards>();
        declaredGoodId = -1;
        stall = new ArrayList<Integer>();
    }

    public void setBribeTargets(final AbstractPlayer left, final AbstractPlayer right) { }

    final ArrayList<Cards> getBag() {
        return bag;
    }

    final ArrayList<Integer> getHand() {
        return hand;
    }

    // the preparing part
    public abstract void prepareBag(ArrayList<Integer> localHand);
    final void makeHand(final ArrayList<Integer> localHand) {
        this.hand.clear();
        this.hand.addAll(localHand);
    }

    final void makeCards() {
        ArrayList<Integer> copyHand = new ArrayList<Integer>(hand);
        while (!copyHand.isEmpty()) {
            Integer temp = copyHand.get(0);
            int counter = 1;
            copyHand.remove(0);
            while (copyHand.remove(temp)) {
                ++counter;
            }
            bag.add(new Cards(temp, counter, GoodsFactory.
                    getInstance().getGoodsById(temp).getType()));
        }
    }

    final void makeCards(final ArrayList<Integer> arr) {
        ArrayList<Integer> copyHand = new ArrayList<Integer>(arr);
        while (!copyHand.isEmpty()) {
            Integer temp = copyHand.get(0);
            int counter = 1;
            copyHand.remove(0);
            while (copyHand.remove(temp)) {
                ++counter;
            }
            bag.add(new Cards(temp, counter, GoodsFactory.
                    getInstance().getGoodsById(temp).getType()));
        }
    }

    // the game part
    public abstract void inspect(ArrayList<AbstractPlayer> players, List<Integer> cardsDeck);
    public abstract int caught(List<Integer> cardsDeck);
    public abstract int innocentAccused();
    private void clearHand() {
        this.hand.clear();
    }
    public final void putOnTheStall() {
        money += bribe;
        bribe = 0;
        for (Cards c : bag) {
            for (int i = 0; i < c.getNumber(); ++i) {
                stall.add(c.getId());
            }
        }
        this.bag.clear();
        this.declaredGoodId = -1;
        this.clearHand();
    }
    public abstract String getRole();
    public final ArrayList<Integer> getStall() {
        return stall;
    }
    public final int getMoney() {
        return money;
    }
    public final void addMoney(final int sum) {
        money += sum;
    }
    final Integer getDeclaredGoodId() {
        return declaredGoodId;
    }
    final void setDeclaredGoodId(final Integer i) {
        this.declaredGoodId = i;
    }
    final int getBribe() {
        return bribe;
    }
    final void setBribe(final int bribe) {
        this.bribe = bribe;
    }
}
