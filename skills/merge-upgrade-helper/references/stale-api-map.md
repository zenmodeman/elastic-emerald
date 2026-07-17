# Stale API Map

Use this as a starting map, not a blind rewrite list.

## Battle Volatiles

Common stale patterns:

- `gBattleMons[b].status2 & STATUS2_CONFUSION` -> `gBattleMons[b].volatiles.confusionTurns > 0`
- `STATUS2_TORMENT` -> `volatiles.torment`
- `STATUS2_CURSED` -> `volatiles.cursed`
- `STATUS2_WRAPPED` -> `volatiles.wrapped`
- `STATUS2_ESCAPE_PREVENTION` -> `volatiles.escapePrevention`
- `STATUS2_FORESIGHT` -> `volatiles.foresight`
- `STATUS2_DEFENSE_CURL` -> `volatiles.defenseCurl`
- `STATUS2_INFATUATION` -> `volatiles.infatuation`
- `gStatuses3[b] & STATUS3_ROOTED` -> `volatiles.root`
- `STATUS3_LEECHSEED` -> `volatiles.leechSeed`
- `STATUS3_GASTRO_ACID` -> `volatiles.gastroAcid`
- `STATUS3_EMBARGO` -> `volatiles.embargo`
- `STATUS3_PERISH_SONG` -> `volatiles.perishSong`
- semi-invulnerable `STATUS3_*` flags -> `volatiles.semiInvulnerable == STATE_*`
- sport status globals -> relevant `volatiles.mudSport` / `volatiles.waterSport` or current field/side status convention.

## AI Speed Helpers

Old:

```c
AI_IsFaster(battlerAtk, battlerDef, move)
AI_IsSlower(battlerAtk, battlerDef, move)
AI_WhoStrikesFirst(battlerAtk, battlerDef, move)
```

Current pattern:

```c
AI_IsFaster(battlerAtk, battlerDef, move, predictedMoveSpeedCheck, CONSIDER_PRIORITY)
AI_IsSlower(battlerAtk, battlerDef, move, predictedMoveSpeedCheck, CONSIDER_PRIORITY)
AI_IsFaster(battlerAtk, battlerDef, MOVE_NONE, MOVE_NONE, DONT_CONSIDER_PRIORITY)
```

Use `GetIncomingMoveSpeedCheck(..., gAiLogicData)` where move priority matters. Use `MOVE_NONE, MOVE_NONE, DONT_CONSIDER_PRIORITY` for raw speed relationship checks.

## Damage And Type Effectiveness

Old direct type-effectiveness calls with many scalar args are stale when `CalcTypeEffectivenessMultiplier` expects `struct DamageContext *`.

Prefer:

- `AI_GetMoveEffectiveness(move, battlerAtk, battlerDef)` for known moves.
- A small helper that multiplies `GetTypeModifier(type, defenderType)` when only raw type-vs-battler typing is needed.
- `struct DamageContext ctx = {0}; ... CalcTypeEffectivenessMultiplier(&ctx);` for full move/ability/item interactions.

## Move Effects And Additional Effects

Check renamed/removed effects before preserving local cases:

- `EFFECT_FIXED_DAMAGE_ARG` often maps to `EFFECT_FIXED_PERCENT_DAMAGE` or `EFFECT_FIXED_HP_DAMAGE`.
- `MOVE_EFFECT_STEAL_ITEM` is usually now a battle move effect such as `EFFECT_STEAL_ITEM`.
- Hazard effects may be represented by `EFFECT_SPIKES`, `EFFECT_STEALTH_ROCK`, `EFFECT_STICKY_WEB`, `EFFECT_TOXIC_SPIKES`, `EFFECT_STONE_AXE`, or `EFFECT_CEASELESS_EDGE`.

When `enum` switches compile with `-Werror=switch`, add `default: break;` for intentionally partial switches.
