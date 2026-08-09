#include "global.h"
#include "clock.h"
#include "fake_rtc.h"
#include "test/test.h"

TEST("Zenmodeman: Pokemon Center rest advances fake time by eight hours")
{
    struct SiiRtcInfo *rtc;

    FakeRtc_ManuallySetTime(3, 7, 25, 40);
    NpcAdvanceTime();
    rtc = FakeRtc_GetCurrentTime();

    EXPECT_EQ(rtc->day, 4);
    EXPECT_EQ(rtc->hour, 15);
    EXPECT_EQ(rtc->minute, 25);
    EXPECT_EQ(rtc->second, 40);
}

TEST("Zenmodeman: Pokemon Center rest carries across midnight")
{
    struct SiiRtcInfo *rtc;

    FakeRtc_ManuallySetTime(0, 20, 0, 0);
    NpcAdvanceTime();
    rtc = FakeRtc_GetCurrentTime();

    EXPECT_EQ(rtc->day, 2);
    EXPECT_EQ(rtc->hour, 4);
}
