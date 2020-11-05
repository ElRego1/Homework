// Copyright Robert Lica robertlica21@gmail.com
package player;

import common.Constants;
import map.Enviroments;

public final class Rogue extends AbstractPlayer {

    private int hits;

    public Rogue() {
        super(Constants.ROGUE_INITIAL_HP);
    }

    @Override
    public void attack(final Pyromancer defender) {
        int damageBackstab = this.calculateDamage(Constants.ROGUE_BACKSTAB_DMG,
                Constants.ROGUE_BACKSTAB_DMG_LVUP);
        int damageParalysis = this.calculateDamage(Constants.ROGUE_PARALYSIS_STATUS_DMG,
                Constants.ROGUE_PARALYSIS_STATUS_DMG_LVUP);
        if (this.hits % Constants.ROGUE_CRIT_NO_ROUNDS == 0 && this.getCurrentCell().getType().
                equals(Constants.ROGUE_BACKSTAB_CRIT_TERRAIN)) {
            damageBackstab = applyModifiersWithCritical(damageBackstab,
                    Constants.ROGUE_BACKSTAB_PYROMANCER);
        } else {
            damageBackstab = applyModifiers(damageBackstab, Constants.ROGUE_BACKSTAB_PYROMANCER);
        }
        damageParalysis = this.applyModifiers(damageParalysis,
                Constants.ROGUE_PARALYSIS_PYROMANCER);
        defender.setStatusEffectDMG(damageParalysis);
        if (this.getCurrentCell().getType().equals(Enviroments.getAdvantageEnvironment(this))) {
            defender.setStatusEffectTimeRemaining(
                    Constants.ROGUE_PARALYSIS_STATUS_ROUNDS_TERRAIN_MODIF);
            defender.setImmobilizedTime(Constants.ROGUE_PARALYSIS_STATUS_ROUNDS_TERRAIN_MODIF);
        } else {
            defender.setStatusEffectTimeRemaining(Constants.ROGUE_PARALYSIS_STATUS_ROUNDS);
            defender.setImmobilizedTime(Constants.ROGUE_PARALYSIS_STATUS_ROUNDS);
        }
        defender.getDamage(damageBackstab + damageParalysis);
        ++this.hits;
    }
    @Override
    public void attack(final Knight defender) {
        int damageBackstab = this.calculateDamage(Constants.ROGUE_BACKSTAB_DMG,
                Constants.ROGUE_BACKSTAB_DMG_LVUP);
        int damageParalysis = this.calculateDamage(Constants.ROGUE_PARALYSIS_STATUS_DMG,
                Constants.ROGUE_PARALYSIS_STATUS_DMG_LVUP);
        if (this.hits % Constants.ROGUE_CRIT_NO_ROUNDS == 0 && this.getCurrentCell().getType().
                equals(Constants.ROGUE_BACKSTAB_CRIT_TERRAIN)) {
            damageBackstab = applyModifiersWithCritical(damageBackstab,
                    Constants.ROGUE_BACKSTAB_KNIGHT);
        } else {
            damageBackstab = applyModifiers(damageBackstab, Constants.ROGUE_BACKSTAB_KNIGHT);
        }
        damageParalysis = this.applyModifiers(damageParalysis, Constants.ROGUE_PARALYSIS_KNIGHT);
        defender.setStatusEffectDMG(damageParalysis);
        if (this.getCurrentCell().getType().equals(Enviroments.getAdvantageEnvironment(this))) {
            defender.setStatusEffectTimeRemaining(
                    Constants.ROGUE_PARALYSIS_STATUS_ROUNDS_TERRAIN_MODIF);
            defender.setImmobilizedTime(Constants.ROGUE_PARALYSIS_STATUS_ROUNDS_TERRAIN_MODIF);
        } else {
            defender.setStatusEffectTimeRemaining(Constants.ROGUE_PARALYSIS_STATUS_ROUNDS);
            defender.setImmobilizedTime(Constants.ROGUE_PARALYSIS_STATUS_ROUNDS);
        }
        defender.getDamage(damageBackstab + damageParalysis);
        ++this.hits;
    }
    @Override
    public void attack(final Wizard defender) {
        int damageBackstab = this.calculateDamage(Constants.ROGUE_BACKSTAB_DMG,
                Constants.ROGUE_BACKSTAB_DMG_LVUP);
        int damageParalysis = this.calculateDamage(Constants.ROGUE_PARALYSIS_STATUS_DMG,
                Constants.ROGUE_PARALYSIS_STATUS_DMG_LVUP);
        // in the method I treat the critical modifier
        int damageDeflacted = this.calculateDeflectedDamage(damageBackstab,
                damageParalysis, defender);
        if (this.hits % Constants.ROGUE_CRIT_NO_ROUNDS == 0 && this.getCurrentCell().getType().
                equals(Constants.ROGUE_BACKSTAB_CRIT_TERRAIN)) {
            damageBackstab = applyModifiersWithCritical(damageBackstab,
                    Constants.ROGUE_BACKSTAB_WIZARD);
        } else {
            damageBackstab = applyModifiers(damageBackstab, Constants.ROGUE_BACKSTAB_WIZARD);
        }
        damageParalysis = this.applyModifiers(damageParalysis, Constants.ROGUE_PARALYSIS_WIZARD);
        defender.setStatusEffectDMG(damageParalysis);
        if (this.getCurrentCell().getType().equals(Enviroments.getAdvantageEnvironment(this))) {
            defender.setStatusEffectTimeRemaining(
                    Constants.ROGUE_PARALYSIS_STATUS_ROUNDS_TERRAIN_MODIF);
            defender.setImmobilizedTime(Constants.ROGUE_PARALYSIS_STATUS_ROUNDS_TERRAIN_MODIF);
        } else {
            defender.setStatusEffectTimeRemaining(Constants.ROGUE_PARALYSIS_STATUS_ROUNDS);
            defender.setImmobilizedTime(Constants.ROGUE_PARALYSIS_STATUS_ROUNDS);
        }
        defender.getDamage(damageBackstab + damageParalysis);
        this.getDamage(damageDeflacted);
        ++this.hits;
    }
    @Override
    public void attack(final Rogue defender) {
        int damageBackstab = this.calculateDamage(Constants.ROGUE_BACKSTAB_DMG,
                Constants.ROGUE_BACKSTAB_DMG_LVUP);
        int damageParalysis = this.calculateDamage(Constants.ROGUE_PARALYSIS_STATUS_DMG,
                Constants.ROGUE_PARALYSIS_STATUS_DMG_LVUP);
        // apply critical if needed if needed
        if (this.hits % Constants.ROGUE_CRIT_NO_ROUNDS == 0 && this.getCurrentCell().getType().
                equals(Constants.ROGUE_BACKSTAB_CRIT_TERRAIN)) {
            damageBackstab = applyModifiersWithCritical(damageBackstab,
                    Constants.ROGUE_BACKSTAB_ROGUE);
        } else {
            damageBackstab = applyModifiers(damageBackstab, Constants.ROGUE_BACKSTAB_ROGUE);
        }
        damageParalysis = this.applyModifiers(damageParalysis, Constants.ROGUE_PARALYSIS_ROGUE);
        defender.setStatusEffectDMG(damageParalysis);
        if (this.getCurrentCell().getType().equals(Enviroments.getAdvantageEnvironment(this))) {
            defender.setStatusEffectTimeRemaining(
                    Constants.ROGUE_PARALYSIS_STATUS_ROUNDS_TERRAIN_MODIF);
            defender.setImmobilizedTime(Constants.ROGUE_PARALYSIS_STATUS_ROUNDS_TERRAIN_MODIF);
        } else {
            defender.setStatusEffectTimeRemaining(Constants.ROGUE_PARALYSIS_STATUS_ROUNDS);
            defender.setImmobilizedTime(Constants.ROGUE_PARALYSIS_STATUS_ROUNDS);
        }
        defender.getDamage(damageBackstab + damageParalysis);
        ++this.hits;
    }

    @Override
    public void attackedBy(final AbstractPlayer aggressor) {
        aggressor.attack(this);
    }


    @Override
    public void updateMaxHp() {
        int newMaxHP = Constants.ROGUE_INITIAL_HP + this.getLvl() * Constants.ROGUE_HP_LVUP;
        if (newMaxHP != this.getMaxHp()) {
            this.setMaxHp(newMaxHP);
        }
    }

    @Override
    public String getInitialOfClass() {
        return Constants.ROGUE_DECLARATION_CHAR;
    }
    // it can not be in AbstractPlayer with "final" because we would lose
    // the meaning to "this" (no longer Rogue)
    @Override
    public int applyModifiers(final int baseDamage, final float raceModifier) {
        return Math.round(baseDamage * Enviroments.getEnvironmentModifier(this) * raceModifier);
    }
    private int applyModifiersWithCritical(final int baseDamage, final float raceModifier) {
        return Math.round(Math.round(baseDamage * Constants.ROGUE_BACKSTAB_CRIT_MODIF
                * Enviroments.getEnvironmentModifier(this)) * raceModifier);
    }
    // it can not be in AbstractPlayer with "final" because we would lose
    // the meaning to "this" (no longer Rogue)
    @Override
    public int calculateFinalDamage(final int baseValue, final int valueOnLvl,
                                    final float raceModifier) {
        return Math.round((baseValue + valueOnLvl * this.getLvl())
                * Enviroments.getEnvironmentModifier(this) * raceModifier);
    }
    // it can not be in AbstractPlayer with "final" because we would lose
    // the meaning to "this" (no longer Rogue)
    @Override
    public int calculateDeflectedDamage(final int baseValue1, final int baseValue2,
                                        final Wizard defender) {
        if (this.hits % Constants.ROGUE_CRIT_NO_ROUNDS == 0 && this.getCurrentCell().getType().
                equals(Constants.ROGUE_BACKSTAB_CRIT_TERRAIN)) {
            return Math.round(
                    (Math.round(baseValue1 * Enviroments.getEnvironmentModifier(this)
                            * Constants.ROGUE_BACKSTAB_CRIT_MODIF)
                            + Math.round(baseValue2 * Enviroments.getEnvironmentModifier(this)))
                            * Math.min(Constants.WIZARD_DEFLECT_DMG
                            + Constants.WIZARD_DEFLECT_DMG_LVUP * defender.getLvl(),
                            Constants.WIZARD_DEFLECT_DMG_MAX)
                            * Constants.WIZARD_DEFLECT_ROGUE);
        } else {
            return Math.round(
                    (Math.round(baseValue1 * Enviroments.getEnvironmentModifier(this))
                            + Math.round(baseValue2 * Enviroments.getEnvironmentModifier(this)))
                            * Math.min(Constants.WIZARD_DEFLECT_DMG
                            + Constants.WIZARD_DEFLECT_DMG_LVUP * defender.getLvl(),
                            Constants.WIZARD_DEFLECT_DMG_MAX)
                            * Enviroments.getEnvironmentModifier(defender)
                            * Constants.WIZARD_DEFLECT_ROGUE);
        }
    }
}
