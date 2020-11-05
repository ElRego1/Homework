// Copyright Robert Lica robertlica21@gmail.com
package com.tema1.player;

import com.tema1.common.Constants;
import com.tema1.goods.GoodsFactory;
import com.tema1.goods.GoodsType;
import com.tema1.player.inventory.Cards;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public final class BasicPlayer extends AbstractPlayer {
    public BasicPlayer() {
        super();
    }
    @Override
    public void prepareBag(final ArrayList<Integer> hand) {
        this.makeHand(hand);
        this.makeCards();
        this.setDeclaredGoodId(this.selectGoods());
    }

    private Integer selectGoods() {
        Collections.sort(this.getBag(), new BasicComparator());
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
    }

    @Override
    public void inspect(final ArrayList<AbstractPlayer> players, final List<Integer> cardsDeck) {
        boolean hasLied;
        for (AbstractPlayer player : players) {
            if (player == this) {
                continue;
            }
            if (this.getMoney() >= Constants.getMinimumMoneyToInspect()) {
                hasLied = false;
                for (Cards c : player.getBag()) {
                    if (!player.getDeclaredGoodId().equals(c.getId())) {
                        hasLied = true;
                        break;
                    }
                }
                if (hasLied) { // if the player it inspected lied
                    this.addMoney(player.caught(cardsDeck));
                } else { // if it inspected an honest player
                    this.addMoney(player.innocentAccused());
                }
            }
        }
    }

    @Override
    public int caught(final List<Integer> cardsDeck) {
        // returns a positive value so the serif adds it to its money
        int sum = GoodsFactory.
                getInstance().getGoodsById(this.getBag().get(0).getId()).getPenalty();
        this.addMoney((-1) * sum);
        cardsDeck.add(this.getBag().get(0).getId());
        this.getBag().clear();
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
        return "BASIC";
    }


}



