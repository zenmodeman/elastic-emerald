#ifndef GUARD_CONSTANTS_TMS_HMS_H
#define GUARD_CONSTANTS_TMS_HMS_H

// Priority candidates in off_type_moves.md, plus Power Split and Lucky Chant.
#define FOREACH_TM(F) \
    F(DRAGON_CLAW) \
    F(CHILLING_WATER) \
    F(LOW_KICK) \
    F(HELPING_HAND) \
    F(ICE_BEAM) \
    F(LIGHT_SCREEN) \
    F(SOLAR_BEAM) \
    F(THUNDERBOLT) \
    F(EARTHQUAKE) \
    F(RETURN) \
    F(PSYCHIC) \
    F(SHADOW_BALL) \
    F(BRICK_BREAK) \
    F(REFLECT) \
    F(FLAMETHROWER) \
    F(SLUDGE_BOMB) \
    F(ROCK_TOMB) \
    F(SECRET_POWER) \
    F(REST) \
    F(SNARL) \
    F(STEEL_WING) \
    F(THROAT_CHOP) \
    F(HARD_PRESS) \
    F(POWER_SPLIT) \
    F(SURF) \
    F(TERA_BLAST) \
    F(BODY_SLAM) \
    F(BULLDOZE) \
    F(ROCK_SLIDE) \
    F(STOMPING_TANTRUM) \
    F(ICY_WIND) \
    F(DOUBLE_EDGE) \
    F(GRASS_KNOT) \
    F(THUNDER_WAVE) \
    F(PAYBACK) \
    F(SHADOW_CLAW) \
    F(IRON_HEAD) \
    F(THUNDER_PUNCH) \
    F(ICE_PUNCH) \
    F(ZEN_HEADBUTT) \
    F(ENDEAVOR) \
    F(FIRE_PUNCH) \
    F(WEATHER_BALL) \
    F(ENERGY_BALL) \
    F(U_TURN) \
    F(POISON_JAB) \
    F(MUD_SHOT) \
    F(HYPER_VOICE) \
    F(DAZZLING_GLEAM) \
    F(ACROBATICS) \
    F(DARK_PULSE) \
    F(FLASH_CANNON) \
    F(LOW_SWEEP) \
    F(EARTH_POWER) \
    F(PAIN_SPLIT) \
    F(SEED_BOMB) \
    F(ALLY_SWITCH) \
    F(AVALANCHE) \
    F(RECYCLE) \
    F(WILD_CHARGE) \
    F(X_SCISSOR) \
    F(HEX) \
    F(ICE_SPINNER) \
    F(VENOSHOCK) \
    F(DRAGON_PULSE) \
    F(LIQUIDATION) \
    F(POUNCE) \
    F(POLLEN_PUFF) \
    F(PLAY_ROUGH) \
    F(PSYCHIC_NOISE) \
    F(ELECTROWEB) \
    F(PSYSHOCK) \
    F(REVENGE) \
    F(TEMPER_FLARE) \
    F(POWER_GEM) \
    F(LUCKY_CHANT)

#define FOREACH_HM(F) \
    F(CUT) \
    F(FLASH) \
    F(ROCK_SMASH)

#define FOREACH_TMHM(F) \
    FOREACH_TM(F) \
    FOREACH_HM(F)

#endif
