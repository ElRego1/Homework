// Copyright Robert Lica robertlica21@gmail.com
package map;

import common.Constants;
import player.Knight;
import player.Pyromancer;
import player.Rogue;
import player.Wizard;

public enum Enviroments {
    Land,
    Volcanic,
    Desert,
    Woods;
    public static Enviroments getAdvantageEnvironment(final Pyromancer player) {
        return Constants.PYROMANCER_TERRAIN_BONUS;
    }
    public static Enviroments getAdvantageEnvironment(final Knight player) {
        return Constants.KNIGHT_TERRAIN_BONUS;
    }
    public static Enviroments getAdvantageEnvironment(final Wizard player) {
        return Constants.WIZARD_TERRAIN_BONUS;
    }
    public static Enviroments getAdvantageEnvironment(final Rogue player) {
        return Constants.ROGUE_TERRAIN_BONUS;
    }
    public static float getEnvironmentModifier(final Pyromancer player) {
        if (player.getCurrentCell().getType().equals(Enviroments.getAdvantageEnvironment(player))) {
            return Constants.PYROMANCER_TERRAIN_DMG_MODIF;
        }
        return 1.0f;
    }
    public static float getEnvironmentModifier(final Knight player) {
        if (player.getCurrentCell().getType().equals(Enviroments.getAdvantageEnvironment(player))) {
            return Constants.KNIGHT_TERRAIN_DMG_MODIF;
        }
        return 1.0f;
    }
    public static float getEnvironmentModifier(final Wizard player) {
        if (player.getCurrentCell().getType().equals(Enviroments.getAdvantageEnvironment(player))) {
            return Constants.WIZARD_TERRAIN_DMG_MODIF;
        }
        return 1.0f;
    }
    public static float getEnvironmentModifier(final Rogue player) {
        if (player.getCurrentCell().getType().equals(Enviroments.getAdvantageEnvironment(player))) {
            return Constants.ROGUE_TERRAIN_DMG_MODIF;
        }
        return 1.0f;
    }
}
