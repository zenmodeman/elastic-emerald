#include "global.h"
#include "move.h"
#include "test/test.h"

TEST("Zenmodeman: Present Air Cutter and Snarl retain their custom perfect accuracy")
{
    EXPECT_EQ(GetMoveAccuracy(MOVE_PRESENT), 100);
    EXPECT_EQ(GetMoveAccuracy(MOVE_AIR_CUTTER), 100);
    EXPECT_EQ(GetMoveAccuracy(MOVE_SNARL), 100);
}

TEST("Zenmodeman: Fire Spin Arm Thrust and Trop Kick retain their early custom move data")
{
    EXPECT_EQ(GetMovePower(MOVE_FIRE_SPIN), 35);
    EXPECT_EQ(GetMoveAccuracy(MOVE_FIRE_SPIN), 95);
    EXPECT_EQ(GetMovePower(MOVE_ARM_THRUST), 25);
    EXPECT_EQ(GetMovePower(MOVE_TROP_KICK), 80);
}

TEST("Zenmodeman: Mud Sport and Water Sport retain their custom priority")
{
    EXPECT_EQ(GetMovePriority(MOVE_MUD_SPORT), 1);
    EXPECT_EQ(GetMovePriority(MOVE_WATER_SPORT), 1);
}

TEST("Zenmodeman: Rock Throw retains its custom perfect accuracy")
{
    EXPECT_EQ(GetMoveAccuracy(MOVE_ROCK_THROW), 100);
}

TEST("Zenmodeman: illuminating moves retain their complete custom flag set")
{
    static const enum Move moves[] = {
        MOVE_SOLAR_BEAM, MOVE_CONFUSE_RAY, MOVE_LIGHT_SCREEN, MOVE_FLASH,
        MOVE_SPARK, MOVE_MORNING_SUN, MOVE_MOONLIGHT, MOVE_TAIL_GLOW,
        MOVE_LUSTER_PURGE, MOVE_VOLT_TACKLE, MOVE_SHOCK_WAVE,
        MOVE_FLASH_CANNON, MOVE_ION_DELUGE, MOVE_DAZZLING_GLEAM,
        MOVE_SPOTLIGHT, MOVE_STEEL_BEAM,
    };

    for (u32 i = 0; i < ARRAY_COUNT(moves); i++)
        EXPECT(IsIlluminatingMove(moves[i]));
    EXPECT(!IsIlluminatingMove(MOVE_REFLECT));
}

TEST("Zenmodeman: enticing moves retain their complete custom flag set")
{
    static const enum Move moves[] = {
        MOVE_CHARM, MOVE_FAKE_TEARS, MOVE_CAPTIVATE, MOVE_PLAY_NICE,
        MOVE_CONFIDE, MOVE_BABY_DOLL_EYES, MOVE_TEARFUL_LOOK,
    };

    for (u32 i = 0; i < ARRAY_COUNT(moves); i++)
        EXPECT(IsEnticingMove(moves[i]));
    EXPECT(!IsEnticingMove(MOVE_GROWL));
}

TEST("Zenmodeman: item-interacting moves retain their complete custom flag set")
{
    static const enum Move moves[] = {
        MOVE_THIEF, MOVE_TRICK, MOVE_KNOCK_OFF, MOVE_COVET, MOVE_EMBARGO,
        MOVE_SWITCHEROO, MOVE_BUG_BITE, MOVE_INCINERATE, MOVE_POLTERGEIST,
    };

    for (u32 i = 0; i < ARRAY_COUNT(moves); i++)
        EXPECT(IsItemInteractingMove(moves[i]));
    EXPECT(!IsItemInteractingMove(MOVE_TACKLE));
}
