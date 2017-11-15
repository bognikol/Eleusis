#include "gtest/gtest.h"

#include "01_vectoring/Region.h"

#include <algorithm>

using namespace std;
using namespace Eleusis;
using namespace ::testing;

class RegionTest : public Test
{
protected:
    Region region;

    bool containsRect(Rect r)
    {
        return find(region.getRects().begin(), region.getRects().end(), r) != region.getRects().end();
    }
};

TEST_F(RegionTest, getExtent_noRects)
{
    EXPECT_EQ(region.getExtent(), Rect());
}

TEST_F(RegionTest, getExtent_onlyEmptyRect)
{
    region += Rect();

    EXPECT_EQ(region.getExtent(), Rect());
}

TEST_F(RegionTest, getExtent_singleRect)
{
    region += Rect({ 20, 30 }, { 40, 50 });

    EXPECT_EQ(region.getExtent(), Rect({ 20, 30 }, { 40, 50 }));
}

TEST_F(RegionTest, getExtent_multipleRects)
{
    region += Rect({ 10, 20 }, { 79, 33 });
    region += Rect({ 18, 44 }, { 111, 25 });
    region += Rect({ 77, 80 }, { 50, 88 });
    region += Rect({ 30, 75 }, { 40, 20 });
    region += Rect({ 90, 20 }, { 30, 40 });
    region += Rect({ 110, 18 }, { 30, 40 });

    EXPECT_EQ(region.getExtent(), Rect({ 10, 18 }, {111, 88 }));
}

TEST_F(RegionTest, getExtent_multipleRectsWithEmptyRect)
{
    region += Rect();
    region += Rect({ 10, 20 }, { 79, 33 });
    region += Rect({ 18, 44 }, { 111, 25 });
    region += Rect({ 77, 80 }, { 50, 88 });
    region += Rect({ 30, 75 }, { 40, 20 });
    region += Rect({ 90, 20 }, { 30, 40 });
    region += Rect({ 110, 18 }, { 30, 40 });

    EXPECT_EQ(region.getExtent(), Rect({ 0, 0 }, { 111, 88 }));
}

TEST_F(RegionTest, normalize_noRects)
{
    region.normalize();

    EXPECT_TRUE(region.getRects().empty());
}

TEST_F(RegionTest, normalize_emptyRect)
{
    region += Rect();

    region.normalize();

    EXPECT_TRUE(containsRect(Rect()));
    EXPECT_EQ(region.getRects().size(), 1);
}

TEST_F(RegionTest, normalize_singleRect)
{
    region += Rect(50, 80, 125, 95);

    region.normalize();

    EXPECT_TRUE(containsRect(Rect(50, 80, 125, 95)));
    EXPECT_EQ(region.getRects().size(), 1);
}

TEST_F(RegionTest, normalize_multypleNonIntersectingRectanlges)
{
    region += Rect(280, 30, 340, 150);
    region += Rect(10, 170, 330, 230);
    region += Rect(360, 140, 390, 520);
    region += Rect(410, 80, 740, 230);
    region += Rect(140, 250, 260, 680);
    region += Rect(60, 490, 130, 780);
    region += Rect(140, 690, 260, 750);
    region += Rect(270, 530, 710, 590);

    region.normalize();

    EXPECT_TRUE(containsRect(Rect(280, 30, 341, 151)));
    EXPECT_TRUE(containsRect(Rect(10, 170, 331, 231)));
    EXPECT_TRUE(containsRect(Rect(360, 140, 391, 521)));
    EXPECT_TRUE(containsRect(Rect(410, 80, 741, 231)));
    EXPECT_TRUE(containsRect(Rect(140, 250, 261, 681)));
    EXPECT_TRUE(containsRect(Rect(60, 490, 131, 781)));
    EXPECT_TRUE(containsRect(Rect(140, 690, 261, 751)));
    EXPECT_TRUE(containsRect(Rect(270, 530, 711, 591)));

    EXPECT_EQ(region.getRects().size(), 8);
}

TEST_F(RegionTest, normalize_twoIntersectingRects)
{
    region += Rect(50, 80, 125, 170);
    region += Rect(90, 90, 180, 150);

    region.normalize();

    EXPECT_TRUE(containsRect(Rect(50, 80, 181, 171)));
    EXPECT_EQ(region.getRects().size(), 1);
}

TEST_F(RegionTest, normalize_multyRects_1)
{
    region += Rect(550, 550, 670, 610);
    region += Rect(530, 130, 650, 330);
    region += Rect(80, 170, 200, 370);
    region += Rect(220, 330, 340, 480);
    region += Rect(170, 870, 760, 930);
    region += Rect(50, 70, 250, 180);
    region += Rect(700, 450, 740, 770);
    region += Rect(305, 710, 425, 770);
    region += Rect(170, 130, 290, 250);
    region += Rect(530, 754, 720, 814);
    region += Rect(60, 610, 240, 720);
    region += Rect(470, 100, 590, 160);
    region += Rect(20, 450, 140, 510);

    region.normalize();

    EXPECT_TRUE(containsRect(Rect(20, 70, 341, 511)));
    EXPECT_TRUE(containsRect(Rect(470, 100, 651, 331)));
    EXPECT_TRUE(containsRect(Rect(530, 450, 741, 815)));
    EXPECT_TRUE(containsRect(Rect(60, 610, 241, 721)));
    EXPECT_TRUE(containsRect(Rect(305, 710, 426, 771)));
    EXPECT_TRUE(containsRect(Rect(170, 870, 761, 931)));

    EXPECT_EQ(region.getRects().size(), 6);
}

TEST_F(RegionTest, normalize_multyRects_2)
{
    region += Rect(410, 550, 720, 710);
    region += Rect(490, 480, 610, 800);
    region += Rect(450, 50, 650, 410);
    region += Rect(420, 460, 710, 500);
    region += Rect(30, 630, 280, 830);
    region += Rect(30, 30, 380, 80);
    region += Rect(240, 50, 360, 420);
    region += Rect(60, 360, 110, 600);
    region += Rect(300, 320, 350, 370);
    region += Rect(30, 850, 150, 910);
    region += Rect(80, 520, 180, 580);
    region += Rect(50, 890, 120, 1000);
    region += Rect(545, 660, 690, 780);
    region += Rect(450, 520, 570, 580);

    region.normalize();

    EXPECT_TRUE(containsRect(Rect(450, 50, 651, 411)));
    EXPECT_TRUE(containsRect(Rect(30, 850, 151, 1001)));
    EXPECT_TRUE(containsRect(Rect(30, 630, 281, 831)));
    EXPECT_TRUE(containsRect(Rect(30, 30, 381, 601)));
    EXPECT_TRUE(containsRect(Rect(410, 460, 721, 801)));

    EXPECT_EQ(region.getRects().size(), 5);
}