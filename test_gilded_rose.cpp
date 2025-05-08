#include <gmock/gmock.h>

#include "gilded_rose.h"

class GildedRoseTest : public ::testing::Test {
protected:
    GildedRose inn;
};

TEST_F(GildedRoseTest, StandardItemQualityDecreasesByOneEachDay)
{
    inn.add_item("Milk", 10, 10);
    inn.update_quality();

    EXPECT_EQ(inn.items.at(0)->quality, 9);
}

TEST_F(GildedRoseTest, StandardItemQualityDecreasesTwiceAsFastAfterSellByDate)
{
    inn.add_item("Milk", 0, 3);
    inn.update_quality();

    EXPECT_EQ(inn.items.at(0)->quality, 1);
}

TEST_F(GildedRoseTest, StandardItemQualityIsNeverNegative)
{
    inn.add_item("Milk", 0, 0);
    inn.update_quality();

    EXPECT_EQ(inn.items.at(0)->quality, 0);
}

TEST_F(GildedRoseTest, AgedBrieQualityIncreasesByOneEachDay)
{
    inn.add_item("Aged Brie", 10, 10);
    inn.update_quality();

    EXPECT_EQ(inn.items.at(0)->quality, 11);
}

TEST_F(GildedRoseTest, AgedBrieQualityIsNeverAbove50)
{
    inn.add_item("Aged Brie", 8, 50);
    inn.update_quality();

    EXPECT_EQ(inn.items.at(0)->quality, 50);
}

TEST_F(GildedRoseTest, BackstagePassesQualityIncreasesByOneEachDay)
{
    inn.add_item("Backstage passes to a TAFKAL80ETC concert", 15, 20);
    inn.update_quality();

    EXPECT_EQ(inn.items.at(0)->quality, 21);
}

TEST_F(GildedRoseTest, BackstagePassesQualityIncreasesByTwoWhenSellInTenOrLess)
{
    inn.add_item("Backstage passes to a TAFKAL80ETC concert", 10, 24);
    inn.update_quality();

    EXPECT_EQ(inn.items.at(0)->quality, 26);
}

TEST_F(GildedRoseTest, BackstagePassesQualityIncreasesByThreeWhenSellInFiveOrLess)
{
    inn.add_item("Backstage passes to a TAFKAL80ETC concert", 5, 33);
    inn.update_quality();

    EXPECT_EQ(inn.items.at(0)->quality, 36);
}

TEST_F(GildedRoseTest, BackstagePassesQualityIsZeroAfterSellInDate)
{
    inn.add_item("Backstage passes to a TAFKAL80ETC concert", 0, 45);
    inn.update_quality();

    EXPECT_EQ(inn.items.at(0)->quality, 0);
}

TEST_F(GildedRoseTest, SulfurasQualityAndSellInNeverChange)
{
    inn.add_item("Sulfuras, Hand of Ragnaros", 10, 80);
    inn.update_quality();

    EXPECT_EQ(inn.items.at(0)->sell_in, 10);
    EXPECT_EQ(inn.items.at(0)->quality, 80);
}

TEST_F(GildedRoseTest, QualityOfItemNeverExceeds50)
{
    inn.add_item("Aged Brie", 10, 50);
    inn.add_item("Backstage passes to a TAFKAL80ETC concert", 5, 49);
    inn.update_quality();

    EXPECT_EQ(inn.items.at(0)->quality, 50);
    EXPECT_EQ(inn.items.at(1)->quality, 50);
}