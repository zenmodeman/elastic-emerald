#include "global.h"
#include "test/test.h"

extern const u16 gTechTutorAlways[51];
extern const u16 gTechTutor1Badge[2];

TEST("Zenmodeman: Roar Whirlwind and Upper Hand retain their custom Tech Tutor tiers")
{
    EXPECT_EQ(gTechTutorAlways[ARRAY_COUNT(gTechTutorAlways) - 2], MOVE_ROAR);
    EXPECT_EQ(gTechTutorAlways[ARRAY_COUNT(gTechTutorAlways) - 1], MOVE_WHIRLWIND);
    EXPECT_EQ(gTechTutor1Badge[0], MOVE_UPPER_HAND);
}

TEST("Zenmodeman: Twister retains its later one-badge Tech Tutor placement")
{
    EXPECT_EQ(gTechTutor1Badge[1], MOVE_TWISTER);
}
