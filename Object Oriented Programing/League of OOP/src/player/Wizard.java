// Copyright Robert Lica robertlica21@gmail.com
package player;

import common.Constants;
import map.Enviroments;

public final class Wizard extends AbstractPlayer {

    public Wizard() {
        super(Constants.WIZARD_INITIAL_HP);
    }

    @Override
    public void attack(final Pyromancer defender) {
        float percentDrain = (Constants.WIZARD_DRAIN_HP
                + Constants.WIZARD_DRAIN_HP_LVUP * this.getLvl())
                * Constants.WIZARD_DRAIN_PYROMANCER;
        int damageDrain = Math.round(percentDrain * Math.min(Constants.WIZARD_DRAIN_MAXHP_MODIF
                        * defender.getMaxHp(), defender.getHpBeforeBattle())
                * Enviroments.getEnvironmentModifier(this));
        defender.getDamage(damageDrain);
    }
    @Override
    public void attack(final Knight defender) {
        float percentDrain = (Constants.WIZARD_DRAIN_HP
                + Constants.WIZARD_DRAIN_HP_LVUP * this.getLvl())
                * Constants.WIZARD_DRAIN_KNIGHT;
        int damageDrain = Math.round(percentDrain * Math.min(Constants.WIZARD_DRAIN_MAXHP_MODIF
                        * defender.getMaxHp(), defender.getHpBeforeBattle())
                * Enviroments.getEnvironmentModifier(this));
        defender.getDamage(damageDrain);
    }
    @Override
    public void attack(final Wizard defender) {
        float percentDrain = (Constants.WIZARD_DRAIN_HP
                + Constants.WIZARD_DRAIN_HP_LVUP * this.getLvl()) * Constants.WIZARD_DRAIN_WIZARD;
        int damageDrain = Math.round(percentDrain * Math.min(Constants.WIZARD_DRAIN_MAXHP_MODIF
                        * defender.getMaxHp(), defender.getHpBeforeBattle())
                * Enviroments.getEnvironmentModifier(this));
        defender.getDamage(damageDrain);
    }
    @Override
    public void attack(final Rogue defender) {
        float percentDrain = (Constants.WIZARD_DRAIN_HP
                + Constants.WIZARD_DRAIN_HP_LVUP * this.getLvl()) * Constants.WIZARD_DRAIN_ROGUE;
        int damageDrain = Math.round(percentDrain * Math.min(Constants.WIZARD_DRAIN_MAXHP_MODIF
                        * defender.getMaxHp(), defender.getHpBeforeBattle())
                * Enviroments.getEnvironmentModifier(this));
        defender.getDamage(damageDrain);
    }

    @Override
    public void attackedBy(final AbstractPlayer aggressor) {
        aggressor.attack(this);
    }

    @Override
    public void updateMaxHp() {
        int newMaxHP = Constants.WIZARD_INITIAL_HP + this.getLvl() * Constants.WIZARD_HP_LVUP;
        if (newMaxHP != this.getMaxHp()) {
            this.setMaxHp(newMaxHP);
        }
    }
    // it can not be in AbstractPlayer with "final" because we would lose
    // the meaning to "this" (no longer Knight)
    @Override
    public String getInitialOfClass() {
        return Constants.WIZARD_DECLARATION_CHAR;
    }
    // it can not be in AbstractPlayer with "final" because we would lose
    // the meaning to "this" (no longer Knight)
    @Override
    public int applyModifiers(final int baseDamage, final float raceModifier) {
        return Math.round(baseDamage * Enviroments.getEnvironmentModifier(this) * raceModifier);
    }
    // it can not be in AbstractPlayer with "final" because we would lose
    // the meaning to "this" (no longer Knight)
    @Override
    public int calculateFinalDamage(final int baseValue, final int valueOnLvl,
                                    final float raceModifier) {
        return Math.round((baseValue + valueOnLvl * this.getLvl())
                * Enviroments.getEnvironmentModifier(this) * raceModifier);
    }

    @Override
    public int calculateDeflectedDamage(final int baseValue1, final int baseValue2,
                                        final Wizard defender) {
        return 0;
    }
}
