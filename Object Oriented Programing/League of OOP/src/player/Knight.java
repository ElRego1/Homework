// Copyright Robert Lica robertlica21@gmail.com
package player;

import common.Constants;
import map.Enviroments;

public final class Knight extends AbstractPlayer {

    public Knight() {
        super(Constants.KNIGHT_INITIAL_HP);
    }

    @Override
    public void attack(final Pyromancer defender) {
        if (defender.getHpBeforeBattle() < Math.min(Constants.KNIGHT_EXECUTE_HP_LIMIT
                        + Constants.KNIGHT_EXECUTE_HP_LIMIT_LVUP * this.getLvl(),
                Constants.KNIGHT_EXECUTE_HP_LIMIT_MAX) * defender.getMaxHp()) {
            defender.setHp(0);
            defender.setStatusEffectTimeRemaining(0);
            defender.setStatusEffectDMG(0);
            defender.setImmobilizedTime(0);
            return;
        }
        int damageExecute = this.calculateDamage(Constants.KNIGHT_EXECUTE_DMG,
                Constants.KNIGHT_EXECUTE_DMG_LVUP);
        int damageSlam = this.calculateDamage(Constants.KNIGHT_SLAM_DMG,
                Constants.KNIGHT_SLAM_DMG_LVUP);
        defender.setImmobilizedTime(Constants.KNIGHT_SLAM_STATUS_ROUNDS);
        defender.setStatusEffectTimeRemaining(0);
        defender.setStatusEffectDMG(0);
        defender.getDamage(this.applyModifiers(damageExecute,
                Constants.KNIGHT_EXECUTE_PYROMANCER)
                + this.applyModifiers(damageSlam, Constants.KNIGHT_SLAM_PYROMANCER));
    }
    @Override
    public void attack(final Knight defender) {
        if (defender.getHpBeforeBattle() < Math.min(Constants.KNIGHT_EXECUTE_HP_LIMIT
                        + Constants.KNIGHT_EXECUTE_HP_LIMIT_LVUP * this.getLvl(),
                Constants.KNIGHT_EXECUTE_HP_LIMIT_MAX) * defender.getMaxHp()) {
            defender.setHp(0);
            defender.setStatusEffectTimeRemaining(0);
            defender.setStatusEffectDMG(0);
            defender.setImmobilizedTime(0);
            return;
        }
        int damageExecute = this.calculateDamage(Constants.KNIGHT_EXECUTE_DMG,
                Constants.KNIGHT_EXECUTE_DMG_LVUP);
        int damageSlam = this.calculateDamage(Constants.KNIGHT_SLAM_DMG,
                Constants.KNIGHT_SLAM_DMG_LVUP);
        defender.setImmobilizedTime(Constants.KNIGHT_SLAM_STATUS_ROUNDS);
        defender.setStatusEffectTimeRemaining(0);
        defender.setStatusEffectDMG(0);
        defender.getDamage(this.applyModifiers(damageExecute,
                Constants.KNIGHT_EXECUTE_KNIGHT)
                + this.applyModifiers(damageSlam, Constants.KNIGHT_SLAM_KNIGHT));
    }
    @Override
    public void attack(final Wizard defender) {
        if (defender.getHpBeforeBattle() < Math.min(Constants.KNIGHT_EXECUTE_HP_LIMIT
                        + Constants.KNIGHT_EXECUTE_HP_LIMIT_LVUP * this.getLvl(),
                Constants.KNIGHT_EXECUTE_HP_LIMIT_MAX) * defender.getMaxHp()) {
            defender.setHp(0);
            defender.setStatusEffectTimeRemaining(0);
            defender.setStatusEffectDMG(0);
            defender.setImmobilizedTime(0);
            return;
        }
        int damageExecute = this.calculateDamage(Constants.KNIGHT_EXECUTE_DMG,
                Constants.KNIGHT_EXECUTE_DMG_LVUP);
        int damageSlam = this.calculateDamage(Constants.KNIGHT_SLAM_DMG,
                Constants.KNIGHT_SLAM_DMG_LVUP);
        defender.setImmobilizedTime(Constants.KNIGHT_SLAM_STATUS_ROUNDS);
        defender.setStatusEffectTimeRemaining(0);
        defender.setStatusEffectDMG(0);
        defender.getDamage(this.applyModifiers(damageExecute,
                Constants.KNIGHT_EXECUTE_WIZARD)
                + this.applyModifiers(damageSlam, Constants.KNIGHT_SLAM_WIZARD));
        int damageDeflect = this.calculateDeflectedDamage(damageExecute, damageSlam, defender);
        this.getDamage(damageDeflect);
    }
    @Override
    public void attack(final Rogue defender) {
        if (defender.getHpBeforeBattle() < Math.min(Constants.KNIGHT_EXECUTE_HP_LIMIT
                        + Constants.KNIGHT_EXECUTE_HP_LIMIT_LVUP * this.getLvl(),
                Constants.KNIGHT_EXECUTE_HP_LIMIT_MAX) * defender.getMaxHp()) {
            defender.setHp(0);
            defender.setStatusEffectTimeRemaining(0);
            defender.setStatusEffectDMG(0);
            defender.setImmobilizedTime(0);
            return;
        }
        int damageExecute = this.calculateDamage(Constants.KNIGHT_EXECUTE_DMG,
                Constants.KNIGHT_EXECUTE_DMG_LVUP);
        int damageSlam = this.calculateDamage(Constants.KNIGHT_SLAM_DMG,
                Constants.KNIGHT_SLAM_DMG_LVUP);
        defender.setImmobilizedTime(Constants.KNIGHT_SLAM_STATUS_ROUNDS);
        defender.setStatusEffectTimeRemaining(0);
        defender.setStatusEffectDMG(0);
        defender.getDamage(this.applyModifiers(damageExecute,
                Constants.KNIGHT_EXECUTE_ROGUE)
                + this.applyModifiers(damageSlam, Constants.KNIGHT_SLAM_ROGUE));
    }

    @Override
    public void attackedBy(final AbstractPlayer aggressor) {
        aggressor.attack(this);
    }


    @Override
    public void updateMaxHp() {
        int newMaxHP = Constants.KNIGHT_INITIAL_HP + this.getLvl() * Constants.KNIGHT_HP_LVUP;
        if (newMaxHP != this.getMaxHp()) {
            this.setMaxHp(newMaxHP);
        }
    }

    @Override
    public String getInitialOfClass() {
        return Constants.KNIGHT_DECLARATION_CHAR;
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
    // it can not be in AbstractPlayer with "final" because we would lose
    // the meaning to "this" (no longer Knight)
    @Override
    public int calculateDeflectedDamage(final int baseValue1, final int baseValue2,
                                        final Wizard defender) {
        return Math.round(
                (Math.round(baseValue1 * Enviroments.getEnvironmentModifier(this))
                        + Math.round(baseValue2 * Enviroments.getEnvironmentModifier(this)))
                        * Math.min(Constants.WIZARD_DEFLECT_DMG + Constants.WIZARD_DEFLECT_DMG_LVUP
                        * defender.getLvl(), Constants.WIZARD_DEFLECT_DMG_MAX)
                        * Enviroments.getEnvironmentModifier(defender)
                        * Constants.WIZARD_DEFLECT_KNIGHT);
    }
}
