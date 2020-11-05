// Copyright Robert Lica robertlica21@gmail.com
package com.tema1.common;

public final class Constants {
    private static Constants instance = new Constants();

    private static final int CARD_NUMBER_TO_EXTRACT = 10;
    private static final int NUMBER_OF_LEGAL_GOODS_TYPES = 10;
    private static final int STARTING_MONEY = 80;
    private static final int MAXIMUM_NUMBER_OF_CARDS_IN_BAG = 8;
    private static final int MINIMUM_MONEY_TO_INSPECT = 16;
    private static final int MINIMUM_MONEY_FOR_BRIBE_TO_PLAY_ILLEGAL = 5;
    private static final int BRIBE_FIRST_RANK = 5;
    private static final int BRIBE_SECOND_RANK = 10;

    private Constants() { }

    public Constants getInstance() {
        return instance;
    }

    public static int getCardNumberToExtract() {
        return CARD_NUMBER_TO_EXTRACT;
    }

    public static int getNumberOfLegalGoodsTypes() {
        return NUMBER_OF_LEGAL_GOODS_TYPES;
    }

    public static int getStartingMoney() {
        return STARTING_MONEY;
    }

    public static int getMaximumNumberOfCardsInBag() {
        return MAXIMUM_NUMBER_OF_CARDS_IN_BAG;
    }

    public static int getMinimumMoneyToInspect() {
        return MINIMUM_MONEY_TO_INSPECT;
    }

    public static int getMinimumMoneyForBribeToPlayIllegal() {
        return MINIMUM_MONEY_FOR_BRIBE_TO_PLAY_ILLEGAL;
    }

    public static int getBribeFirstRank() {
        return BRIBE_FIRST_RANK;
    }

    public static int getBribeSecondRank() {
        return BRIBE_SECOND_RANK;
    }
}
