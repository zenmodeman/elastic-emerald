#ifndef GUARD_BATTLE_DEBUG_H
#define GUARD_BATTLE_DEBUG_H

void CB2_BattleDebugMenu(void);

#if TESTING
bool32 Test_BattleInfoDamageWindowFitsVram(void);
struct SimulatedDamage;
struct SimulatedDamage Test_BattleInfoCalcPlayerDamage(u32 move, u32 battlerAtk, u32 battlerDef, bool32 critical);
struct SimulatedDamage Test_BattleInfoCalcAiDamage(u32 move, u32 battlerAtk, u32 battlerDef, enum Ability abilityDef, bool32 critical);
#endif

#endif // GUARD_BATTLE_DEBUG_H
