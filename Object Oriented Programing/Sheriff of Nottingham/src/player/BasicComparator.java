// Copyright Robert Lica robertlica21@gmail.com
package com.tema1.player;

import com.tema1.goods.GoodsFactory;
import com.tema1.goods.GoodsType;
import com.tema1.player.inventory.Cards;

import java.util.Comparator;

public final class BasicComparator implements Comparator<Cards> {
    @Override
    public int compare(final Cards a, final Cards b) {
        // we check if it's legal or not
        if (a.getType().equals(GoodsType.Legal) && b.getType().equals(GoodsType.Illegal)) {
            return -1;
        } else if (a.getType().equals(GoodsType.Illegal) && b.getType().equals(GoodsType.Legal)) {
            return 1;
        } else if (a.getType().equals(GoodsType.Illegal) && b.getType().equals(GoodsType.Illegal)) {
            // we put the illegal good with the higher profit in front of the other illegal goods
            if (GoodsFactory.getInstance().getGoodsById(a.getId()).getProfit()
                    > GoodsFactory.getInstance().getGoodsById(b.getId()).getProfit()) {
                return -1;
            } else if (GoodsFactory.getInstance().getGoodsById(a.getId()).getProfit()
                    < GoodsFactory.getInstance().getGoodsById(b.getId()).getProfit()) {
                return 1;
            } else {
                System.out.println("\t***ERROR!!!***\n\rNu trebuia sa "
                        + "existe bunuri ilegale cu acelasi profit");
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
