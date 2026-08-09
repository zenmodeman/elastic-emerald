#include "global.h"
#include "caps.h"
#include "test/test.h"

TEST("Zenmodeman: split Exp scales from ordinary sharing to full rewards across badges")
{
    EXPECT_EQ(GetSplitExpProgressionValue(800, 2, 0), 400);
    EXPECT_EQ(GetSplitExpProgressionValue(800, 2, 2), 500);
    EXPECT_EQ(GetSplitExpProgressionValue(800, 2, 4), 600);
    EXPECT_EQ(GetSplitExpProgressionValue(800, 2, 6), 700);
    EXPECT_EQ(GetSplitExpProgressionValue(800, 2, 8), 800);
}

TEST("Zenmodeman: split Exp progression accounts for every participant")
{
    EXPECT_EQ(GetSplitExpProgressionValue(800, 4, 0), 200);
    EXPECT_EQ(GetSplitExpProgressionValue(800, 4, 4), 500);
    EXPECT_EQ(GetSplitExpProgressionValue(800, 4, 8), 800);
}

TEST("Zenmodeman: a sole participant always receives full Exp")
{
    EXPECT_EQ(GetSplitExpProgressionValue(800, 1, 0), 800);
    EXPECT_EQ(GetSplitExpProgressionValue(800, 1, 4), 800);
    EXPECT_EQ(GetSplitExpProgressionValue(800, 1, 8), 800);
}
