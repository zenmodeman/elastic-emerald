#include "global.h"
#include "item.h"
#include "test/test.h"

TEST("Zenmodeman: Comet Shards retain their custom sixty thousand price")
{
    EXPECT_EQ(GetItemPrice(ITEM_COMET_SHARD), 60000);
}
