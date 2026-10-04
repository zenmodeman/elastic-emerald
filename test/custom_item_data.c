#include "global.h"
#include "item.h"
#include "test/test.h"

TEST("Elastic-tests: Comet Shards retain their custom sixty thousand price")
{
    EXPECT_EQ(GetItemPrice(ITEM_COMET_SHARD), 60000);
}
