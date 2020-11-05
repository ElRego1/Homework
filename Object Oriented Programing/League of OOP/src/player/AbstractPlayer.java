// Copyright Robert Lica robertlica21@gmail.com
package player;

import common.Constants;
import map.Cell;

import java.beans.PropertyChangeEvent;
import java.beans.PropertyChangeListener;

public abstract class AbstractPlayer implements PropertyChangeListener {
    private int exp, lvl;
    private int hp;
    private int maxHp;
    private int round;
    private int hpBeforeBattle;
    private int statusEffectDMG;
    private int statusEffectTimeRemaining;
    private int immobilizedTime;
    private Cell currentCell;

    AbstractPlayer(final int maxHp) {
        this.maxHp = maxHp;
        this.hp = this.maxHp;
        currentCell = new Cell(-1, -1, "D");
    }

    public abstract void attackedBy(AbstractPlayer aggressor);

    public abstract void attack(Pyromancer defender);

    public abstract void attack(Knight defender);

    public abstract void attack(Wizard defender);

    public abstract void attack(Rogue defender);

    public abstract void updateMaxHp();

    public abstract String getInitialOfClass();

    public final int getExp() {
        return exp;
    }

    public final int getLvl() {
        return lvl;
    }

    public final int getHp() {
        return hp;
    }

    public final int getMaxHp() {
        return maxHp;
    }

    public final int getRound() {
        return round;
    }

    public final int getHpBeforeBattle() {
        return hpBeforeBattle;
    }

    public final int getImmobilizedTime() {
        return immobilizedTime;
    }

    public final Cell getCurrentCell() {
        return currentCell;
    }

    public final void setHp(final int hp) {
        this.hp = hp;
    }

    final void setMaxHp(final int maxHp) {
        this.maxHp = maxHp;
    }

    public final void setRound(final int round) {
        this.round = round;
    }

    public final void setHpBeforeBattle(final int hpBeforeBattle) {
        this.hpBeforeBattle = hpBeforeBattle;
    }

    public final void setStatusEffectDMG(final int statusEffectDMG) {
        this.statusEffectDMG = statusEffectDMG;
    }

    public final void setStatusEffectTimeRemaining(final int statusEffectTimeRemaining) {
        this.statusEffectTimeRemaining = statusEffectTimeRemaining;
    }

    public final void setImmobilizedTime(final int immobilizedTime) {
        this.immobilizedTime = immobilizedTime;
    }

    public final void setCurrentCell(final Cell c) {
        this.currentCell.removePlayerFromCell(this);
        this.currentCell = c;
        this.currentCell.enterPlayerInCell(this);
    }

    public final void getDamage(final int value) {
        this.hp -= value;
    }

    public final void addExp(final int value) {
        this.exp += value;
        this.updateLevel();
    }

    private void updateLevel() {
        int temp = (this.exp - Constants.BASE_NEEDED_EXP_LVUP)
                / Constants.BASE_NEEDED_EXP_LVUP_ON_LV
                + 1;
        if (temp > this.lvl) {
            this.lvl = temp;
            if (this.hp > 0) {
                this.updateMaxHp();
                this.hp = this.maxHp;
            }
        }
    }

    final int calculateDamage(final int baseValue, final int valueOnLvl) {
        return baseValue + valueOnLvl * this.lvl;
    }

    /**
     * Method called at a state change by an event.
     * @param evt is a property change event imported from the "PropertyChangeListener" interface.
     */

    public final void propertyChange(final PropertyChangeEvent evt) {
        if (this.immobilizedTime > 0) {
            --this.immobilizedTime;
        }
        if (this.statusEffectTimeRemaining > 0) {
            this.getDamage(this.statusEffectDMG);
            --this.statusEffectTimeRemaining;
            if (this.hp <= 0) {
                this.hp = 0;
                this.currentCell.removePlayerFromCell(this);
                // when he dies we remove all the status effects, even if we don't
                // know if at respawn he keeps them
                this.statusEffectTimeRemaining = 0;
            }
        }
    }

    public abstract int applyModifiers(int baseDamage, float raceModifier);
    public abstract int calculateFinalDamage(int baseValue, int valueOnLvl, float raceModifier);
    public abstract int calculateDeflectedDamage(int baseValue1, int baseValue2, Wizard defender);
}
