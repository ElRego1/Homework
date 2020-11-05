// Copyright Robert Lica robertlica21@gmail.com
package player;

import common.Constants;
import map.Enviroments;

public final class Pyromancer extends AbstractPlayer {

    public Pyromancer() {
        super(Constants.PYROMANCER_INITIAL_HP);
    }

    @Override
    public void attack(final Pyromancer defender) {
        int damageFireblast = this.calculateDamage(Constants.PYROMANCER_FIREBLAST_DMG,
                Constants.PYROMANCER_FIREBLAST_DMG_LVUP);
        int damageIgnite = this.calculateDamage(Constants.PYROMANCER_IGNITE_DMG,
                Constants.PYROMANCER_IGNITE_DMG_LVUP);
        defender.setStatusEffectDMG(this.calculateFinalDamage(
                Constants.PYROMANCER_IGNITE_STATUS_DMG, Constants.PYROMANCER_IGNITE_STATUS_DMG_LVUP,
                Constants.PYROMANCER_IGNITE_PYROMANCER));
        defender.setStatusEffectTimeRemaining(Constants.PYROMANCER_IGNITE_STATUS_ROUNDS);
        defender.getDamage(this.applyModifiers(damageFireblast,
                Constants.PYROMANCER_FIREBLAST_PYROMANCER) + this.applyModifiers(damageIgnite,
                Constants.PYROMANCER_IGNITE_PYROMANCER));
        defender.setImmobilizedTime(0);
    }
    @Override
    public void attack(final Knight defender) {
        int damageFireblast = this.calculateDamage(Constants.PYROMANCER_FIREBLAST_DMG,
                Constants.PYROMANCER_FIREBLAST_DMG_LVUP);
        int damageIgnite = this.calculateDamage(Constants.PYROMANCER_IGNITE_DMG,
                Constants.PYROMANCER_IGNITE_DMG_LVUP);
        defender.setStatusEffectDMG(this.calculateFinalDamage(
                Constants.PYROMANCER_IGNITE_STATUS_DMG, Constants.PYROMANCER_IGNITE_STATUS_DMG_LVUP,
                Constants.PYROMANCER_IGNITE_KNIGHT));
        defender.setStatusEffectTimeRemaining(Constants.PYROMANCER_IGNITE_STATUS_ROUNDS);
        defender.getDamage(this.applyModifiers(damageFireblast,
                Constants.PYROMANCER_FIREBLAST_KNIGHT) + this.applyModifiers(damageIgnite,
                Constants.PYROMANCER_IGNITE_KNIGHT));
        defender.setImmobilizedTime(0);
    }
    @Override
    public void attack(final Wizard defender) {
        int damageFireblast = this.calculateDamage(Constants.PYROMANCER_FIREBLAST_DMG,
                Constants.PYROMANCER_FIREBLAST_DMG_LVUP);
        int damageIgnite = this.calculateDamage(Constants.PYROMANCER_IGNITE_DMG,
                Constants.PYROMANCER_IGNITE_DMG_LVUP);
        defender.setStatusEffectDMG(this.calculateFinalDamage(
                Constants.PYROMANCER_IGNITE_STATUS_DMG, Constants.PYROMANCER_IGNITE_STATUS_DMG_LVUP,
                Constants.PYROMANCER_IGNITE_WIZARD));
        defender.setStatusEffectTimeRemaining(Constants.PYROMANCER_IGNITE_STATUS_ROUNDS);
        defender.getDamage(this.applyModifiers(damageFireblast,
                Constants.PYROMANCER_FIREBLAST_WIZARD) + this.applyModifiers(damageIgnite,
                Constants.PYROMANCER_IGNITE_WIZARD));
        defender.setImmobilizedTime(0);
        int damageDeflect = this.calculateDeflectedDamage(damageFireblast, damageIgnite, defender);
        this.getDamage(damageDeflect);
    }
    @Override
    public void attack(final Rogue defender) {
        int damageFireblast = this.calculateDamage(Constants.PYROMANCER_FIREBLAST_DMG,
                Constants.PYROMANCER_FIREBLAST_DMG_LVUP);
        int damageIgnite = this.calculateDamage(Constants.PYROMANCER_IGNITE_DMG,
                Constants.PYROMANCER_IGNITE_DMG_LVUP);
        defender.setStatusEffectDMG(this.calculateFinalDamage(
                Constants.PYROMANCER_IGNITE_STATUS_DMG, Constants.PYROMANCER_IGNITE_STATUS_DMG_LVUP,
                Constants.PYROMANCER_IGNITE_ROGUE));
        defender.setStatusEffectTimeRemaining(Constants.PYROMANCER_IGNITE_STATUS_ROUNDS);
        defender.getDamage(this.applyModifiers(damageFireblast,
                Constants.PYROMANCER_FIREBLAST_ROGUE) + this.applyModifiers(damageIgnite,
                Constants.PYROMANCER_IGNITE_ROGUE));
        defender.setImmobilizedTime(0);
    }

    @Override
    public void attackedBy(final AbstractPlayer aggressor) {
        aggressor.attack(this);
    }

    @Override
    public void updateMaxHp() {
        int newMaxHP = Constants.PYROMANCER_INITIAL_HP
                + this.getLvl() * Constants.PYROMANCER_HP_LVUP;
        if (newMaxHP != this.getMaxHp()) {
            this.setMaxHp(newMaxHP);
        }
    }

    @Override
    public String getInitialOfClass() {
        return Constants.PYROMANCER_DECLARATION_CHAR;
    }
    // it can not be in AbstractPlayer with "final" because we would lose
    // the meaning to "this" (no longer Pyromancer)
    @Override
    public int applyModifiers(final int baseDamage, final float raceModifier) {
        return Math.round(baseDamage * Enviroments.getEnvironmentModifier(this) * raceModifier);
    }
    // it can not be in AbstractPlayer with "final" because we would lose
    // the meaning to "this" (no longer Pyromancer)
    @Override
    public int calculateFinalDamage(final int baseValue, final int valueOnLvl,
                                    final float raceModifier) {
        return Math.round((baseValue + valueOnLvl * this.getLvl())
                * Enviroments.getEnvironmentModifier(this) * raceModifier);
    }
    // it can not be in AbstractPlayer with "final" because we would lose
    // the meaning to "this" (no longer Pyromancer)
    @Override
    public int calculateDeflectedDamage(final int baseValue1, final int baseValue2,
                                        final Wizard defender) {
        return Math.round(
                (Math.round(baseValue1 * Enviroments.getEnvironmentModifier(this))
                        + Math.round(baseValue2 * Enviroments.getEnvironmentModifier(this)))
                        * Math.min(Constants.WIZARD_DEFLECT_DMG + Constants.WIZARD_DEFLECT_DMG_LVUP
                        * defender.getLvl(), Constants.WIZARD_DEFLECT_DMG_MAX)
                        * Enviroments.getEnvironmentModifier(defender)
                        * Constants.WIZARD_DEFLECT_PYROMANCER);
    }
}
