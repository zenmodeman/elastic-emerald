#ifndef GUARD_FISHING_H
#define GUARD_FISHING_H

void StartFishing(u8 rod);
void UpdateChainFishingStreak();
u32 CalculateChainFishingShinyRolls(void);
bool32 ShouldUseFishingEnvironmentInBattle();
bool32 CanPlayerGetSuctionCupsFishingItem(void);
u8 GetFishingMinRoundsRange(u8 rod);
u8 GetFishingReelTimeout(u8 rod);
u8 GetFishingMoreDotsChance(u8 rod, u8 stage);
bool32 ShouldForgiveFishingEarlyPress(u8 roundsPlayed, u8 numDots, u8 dotsRequired, u8 roll);

#endif // GUARD_FISHING_H
