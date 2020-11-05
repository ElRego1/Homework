// Copyright Robert Lica robertlica21@gmail.com
package com.tema1.player.inventory;

import com.tema1.goods.GoodsType;

public final class Cards {
    private Integer id;
    private int number;
    private GoodsType type;

    public Cards(final Integer id, final int number, final GoodsType type) {
        this.id = id;
        this.number = number;
        this.type = type;
    }

    public Integer getId() {
        return id;
    }

    public int getNumber() {
        return number;
    }
    public void setNumber(final int number) {
        this.number = number;
    }

    public GoodsType getType() {
        return type;
    }

    @Override
    public String toString() {
        return "[" + id + ":" + number + ":" + type + "] ";
    }
}
