#ifndef GUARD_CONSTANTS_TMS_HMS_H
#define GUARD_CONSTANTS_TMS_HMS_H

// Priority candidates in off_type_moves.md, plus Power Split and Lucky Chant.
// Keep retained TM numbers fixed; fill retired slots before appending additions.
#define FOREACH_TM(F) \
    F(TERA_BLAST) \
    F(DRAGON_CLAW) \
    F(CHILLING_WATER) \
    F(BODY_SLAM) \
    F(BULLDOZE) \
    F(ROCK_SLIDE) \
    F(STOMPING_TANTRUM) \
    F(LOW_KICK) \
    F(HELPING_HAND) \
    F(ICY_WIND) \
    F(DOUBLE_EDGE) \
    F(GRASS_KNOT) \
    F(ICE_BEAM) \
    F(THUNDER_WAVE) \
    F(PAYBACK) \
    F(LIGHT_SCREEN) \
    F(SHADOW_CLAW) \
    F(IRON_HEAD) \
    F(THUNDER_PUNCH) \
    F(ICE_PUNCH) \
    F(ZEN_HEADBUTT) \
    F(SOLAR_BEAM) \
    F(ENDEAVOR) \
    F(THUNDERBOLT) \
    F(FIRE_PUNCH) \
    F(EARTHQUAKE) \
    F(RETURN) \
    F(WEATHER_BALL) \
    F(PSYCHIC) \
    F(SHADOW_BALL) \
    F(BRICK_BREAK) \
    F(ENERGY_BALL) \
    F(REFLECT) \
    F(U_TURN) \
    F(FLAMETHROWER) \
    F(SLUDGE_BOMB) \
    F(POISON_JAB) \
    F(MUD_SHOT) \
    F(ROCK_TOMB) \
    F(HYPER_VOICE) \
    F(DAZZLING_GLEAM) \
    F(ACROBATICS) \
    F(SECRET_POWER) \
    F(REST) \
    F(DARK_PULSE) \
    F(SNARL) \
    F(STEEL_WING) \
    F(FLASH_CANNON) \
    F(LOW_SWEEP) \
    F(EARTH_POWER) \
    F(THROAT_CHOP) \
    F(PAIN_SPLIT) \
    F(HARD_PRESS) \
    F(SEED_BOMB) \
    F(POWER_SPLIT) \
    F(ALLY_SWITCH) \
    F(AVALANCHE) \
    F(RECYCLE) \
    F(SURF) \
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
