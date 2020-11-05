// Copyright Robert Lica robertlica21@gmail.com
package common;

import map.Enviroments;

public final class Constants {
    public static final String DEAD_STATUS_PRINT = "dead";

    // EXP
    public static final int BASE_NEEDED_EXP_LVUP = 250;
    public static final int BASE_NEEDED_EXP_LVUP_ON_LV = 50;
    public static final int EXP_INFERIOR_LIMIT = 200;
    public static final int EXP_GAIN_MODIF = 40;

    // PYROMANCER
    public static final int PYROMANCER_INITIAL_HP = 500;
    public static final int PYROMANCER_HP_LVUP = 50;
    public static final float PYROMANCER_TERRAIN_DMG_MODIF = 1.25f;
    public static final Enviroments PYROMANCER_TERRAIN_BONUS = Enviroments.Volcanic;
    public static final String PYROMANCER_DECLARATION_CHAR = "P";
    // PYROMANCER FIREBLAST
    public static final int PYROMANCER_FIREBLAST_DMG = 350;
    public static final int PYROMANCER_FIREBLAST_DMG_LVUP = 50;
    public static final float PYROMANCER_FIREBLAST_ROGUE = 0.8f;
    public static final float PYROMANCER_FIREBLAST_KNIGHT = 1.2f;
    public static final float PYROMANCER_FIREBLAST_PYROMANCER = 0.9f;
    public static final float PYROMANCER_FIREBLAST_WIZARD = 1.05f;
    // PYROMANCER IGNITE
    public static final int PYROMANCER_IGNITE_DMG = 150;
    public static final int PYROMANCER_IGNITE_DMG_LVUP = 20;
    public static final int PYROMANCER_IGNITE_STATUS_DMG = 50;
    public static final int PYROMANCER_IGNITE_STATUS_DMG_LVUP = 30;
    public static final int PYROMANCER_IGNITE_STATUS_ROUNDS = 2;
    public static final float PYROMANCER_IGNITE_ROGUE = 0.8f;
    public static final float PYROMANCER_IGNITE_KNIGHT = 1.2f;
    public static final float PYROMANCER_IGNITE_PYROMANCER = 0.9f;
    public static final float PYROMANCER_IGNITE_WIZARD = 1.05f;

    // KNIGHT
    public static final int KNIGHT_INITIAL_HP = 900;
    public static final int KNIGHT_HP_LVUP = 80;
    public static final float KNIGHT_TERRAIN_DMG_MODIF = 1.15f;
    public static final Enviroments KNIGHT_TERRAIN_BONUS = Enviroments.Land;
    public static final String KNIGHT_DECLARATION_CHAR = "K";
    // KNIGHT EXECUTE
    public static final int KNIGHT_EXECUTE_DMG = 200;
    public static final int KNIGHT_EXECUTE_DMG_LVUP = 30;
    public static final float KNIGHT_EXECUTE_HP_LIMIT = 0.2f;
    public static final float KNIGHT_EXECUTE_HP_LIMIT_LVUP = 0.01f;
    public static final float KNIGHT_EXECUTE_HP_LIMIT_MAX = 0.4f;
    public static final float KNIGHT_EXECUTE_ROGUE = 1.15f;
    public static final float KNIGHT_EXECUTE_KNIGHT = 1.0f;
    public static final float KNIGHT_EXECUTE_PYROMANCER = 1.1f;
    public static final float KNIGHT_EXECUTE_WIZARD = 0.8f;
    // KNIGHT SLAM
    public static final int KNIGHT_SLAM_DMG = 100;
    public static final int KNIGHT_SLAM_DMG_LVUP = 40;
    public static final int KNIGHT_SLAM_STATUS_ROUNDS = 1;
    public static final float KNIGHT_SLAM_ROGUE = 0.8f;
    public static final float KNIGHT_SLAM_KNIGHT = 1.2f;
    public static final float KNIGHT_SLAM_PYROMANCER = 0.9f;
    public static final float KNIGHT_SLAM_WIZARD = 1.05f;

    // WIZARD
    public static final int WIZARD_INITIAL_HP = 400;
    public static final int WIZARD_HP_LVUP = 30;
    public static final float WIZARD_TERRAIN_DMG_MODIF = 1.1f;
    public static final Enviroments WIZARD_TERRAIN_BONUS = Enviroments.Desert;
    public static final String WIZARD_DECLARATION_CHAR = "W";
    // WIZARD DRAIN
    public static final float WIZARD_DRAIN_HP = 0.2f;
    public static final float WIZARD_DRAIN_HP_LVUP = 0.05f;
    public static final float WIZARD_DRAIN_MAXHP_MODIF = 0.3f;
    public static final float WIZARD_DRAIN_ROGUE = 0.8f;
    public static final float WIZARD_DRAIN_KNIGHT = 1.2f;
    public static final float WIZARD_DRAIN_PYROMANCER = 0.9f;
    public static final float WIZARD_DRAIN_WIZARD = 1.05f;
    // WIZARD DEFLECT
    public static final float WIZARD_DEFLECT_DMG = .35f;
    public static final float WIZARD_DEFLECT_DMG_LVUP = 0.02f;
    public static final float WIZARD_DEFLECT_DMG_MAX = 0.7f;
    public static final float WIZARD_DEFLECT_ROGUE = 1.2f;
    public static final float WIZARD_DEFLECT_KNIGHT = 1.4f;
    public static final float WIZARD_DEFLECT_PYROMANCER = 1.3f;
    public static final float WIZARD_DEFLECT_WIZARD = 0.0f;

    // ROGUE
    public static final int ROGUE_INITIAL_HP = 600;
    public static final int ROGUE_HP_LVUP = 40;
    public static final float ROGUE_TERRAIN_DMG_MODIF = 1.15f;
    public static final Enviroments ROGUE_TERRAIN_BONUS = Enviroments.Woods;
    public static final String ROGUE_DECLARATION_CHAR = "R";
    // ROGUE BACKSTAB
    public static final int ROGUE_CRIT_NO_ROUNDS = 3;
    public static final int ROGUE_BACKSTAB_DMG = 200;
    public static final int ROGUE_BACKSTAB_DMG_LVUP = 20;
    public static final float ROGUE_BACKSTAB_CRIT_MODIF = 1.5f;
    public static final Enviroments ROGUE_BACKSTAB_CRIT_TERRAIN = Enviroments.Woods;
    public static final float ROGUE_BACKSTAB_ROGUE = 1.2f;
    public static final float ROGUE_BACKSTAB_KNIGHT = 0.9f;
    public static final float ROGUE_BACKSTAB_PYROMANCER = 1.25f;
    public static final float ROGUE_BACKSTAB_WIZARD = 1.25f;
    // ROGUE PARALYSIS
    public static final int ROGUE_PARALYSIS_STATUS_DMG = 40;
    public static final int ROGUE_PARALYSIS_STATUS_DMG_LVUP = 10;
    public static final int ROGUE_PARALYSIS_STATUS_ROUNDS = 3;
    public static final int ROGUE_PARALYSIS_STATUS_ROUNDS_TERRAIN_MODIF = 6;
    public static final float ROGUE_PARALYSIS_ROGUE = 0.9f;
    public static final float ROGUE_PARALYSIS_KNIGHT = 0.8f;
    public static final float ROGUE_PARALYSIS_PYROMANCER = 1.2f;
    public static final float ROGUE_PARALYSIS_WIZARD = 1.25f;

    private Constants() { }
}
