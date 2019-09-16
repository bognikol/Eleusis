#include "gtest/gtest.h"
#include "02_geometry/Geometry.h"
#include <string>
#include <iostream>
#include <limits>

#include "cairo.h"

using namespace std;
using namespace Eleusis;
using namespace ::testing;

class GeometryTest : public Test
{
protected:

    Geometry* _geometry;

     GeometryTest() { }
    ~GeometryTest() { }

    void SetUp()
    {
        _geometry = new Geometry();
    }

    void TearDown()
    {
        delete _geometry;
    }

    void CHECK_QUADRILATERAL(
        double x1, double y1,
        double x2, double y2,
        double x3, double y3,
        double x4, double y4,
        bool checkOriginalPath = false)
    {
        cairo_path_data_t* data;

        if (checkOriginalPath)
            data = _geometry->getOriginalCairoPath()->data;
        else
            data = _geometry->getCairoPath()->data;
        

        EXPECT_EQ(data[1].point.x, x1);
        EXPECT_EQ(data[1].point.y, y1);
        EXPECT_EQ(data[3].point.x, x2);
        EXPECT_EQ(data[3].point.y, y2);
        EXPECT_EQ(data[5].point.x, x3);
        EXPECT_EQ(data[5].point.y, y3);
        EXPECT_EQ(data[7].point.x, x4);
        EXPECT_EQ(data[7].point.y, y4);
    }

	void CHECK_RECTANGLE(
		double x_low, double y_low,
		double x_high, double y_high,
		bool checkOriginalPath = false)
	{
		CHECK_QUADRILATERAL(x_low, y_low, x_low, y_high, x_high, y_high, x_high, y_low, checkOriginalPath);
	}

    void CHECK_EXTENT(
        double x1, double y1,
        double x2, double y2)
    {
        EXPECT_EQ(_geometry->getExtent().lowVector.X, x1);
        EXPECT_EQ(_geometry->getExtent().lowVector.Y, y1);
        EXPECT_EQ(_geometry->getExtent().highVector.X, x2);
        EXPECT_EQ(_geometry->getExtent().highVector.Y, y2);
    }
};

TEST_F(GeometryTest, setAffineTransformation)
{
    _geometry->addRectangle(50, 20, 100, 80, 0);

    EXPECT_EQ(_geometry->getCairoPath()->status, CAIRO_STATUS_SUCCESS);
    EXPECT_EQ(_geometry->getCairoPath()->num_data, 9);

	CHECK_QUADRILATERAL(50, 20, 50, 80, 100, 80, 100, 20);

    AffineTransformation transformation;
    transformation.applyTranslation({ 40, 30 });
    _geometry->setAffineTransformation(&transformation);

    CHECK_QUADRILATERAL(90, 50, 90, 110, 140, 110, 140, 50);
    CHECK_EXTENT(90, 50, 140, 110);

    transformation.setAffineMatrixToIdentity();
    transformation.applyScale({ 2, 2 });
    _geometry->setAffineTransformation(&transformation);

    CHECK_QUADRILATERAL(100, 40, 100, 160, 200, 160, 200, 40);

    transformation.setAffineMatrixToIdentity();
    transformation.applyScale({ 0.5, 0.5 });
    _geometry->multiplyAffineTransformation(&transformation);

    CHECK_QUADRILATERAL(50, 20, 50, 80, 100, 80, 100, 20);

    transformation.setAffineMatrixToIdentity();
    transformation.applyScale({ 2.0, 4.0 });
    transformation.applyScale({ 0.5, 0.25 });
    _geometry->setAffineTransformation(&transformation);

    CHECK_QUADRILATERAL(50, 20, 50, 80, 100, 80, 100, 20);

    transformation.setAffineMatrixToIdentity();
    transformation.applyTranslation({ 100, 100 });
    _geometry->multiplyAffineTransformation(&transformation);

    CHECK_QUADRILATERAL(150, 120, 150, 180, 200, 180, 200, 120);

    transformation.setAffineMatrixToIdentity();
    transformation.applyTranslation({ 100, 100 });
    transformation.applyScale({ 2.0, 2.0 });
    transformation.applyTranslation({ -40, -40 });
    _geometry->setAffineTransformation(&transformation);

    CHECK_QUADRILATERAL(120, 60, 120, 180, 220, 180, 220, 60);

    CHECK_QUADRILATERAL(50, 20, 50, 80, 100, 80, 100, 20, true);
}

TEST_F(GeometryTest, updatePoint)
{
    _geometry->addRectangle(50, 20, 100, 80,0);

    cairo_path_t* path;
    cairo_path_data_t* data;

    path = _geometry->getCairoPath();
    data = path->data;

    EXPECT_EQ(path->status, CAIRO_STATUS_SUCCESS);
    EXPECT_EQ(path->num_data, 9);

    CHECK_QUADRILATERAL(50, 20, 50, 80, 100, 80, 100, 20);

    _geometry->updatePoint(1, 80, 40);
    _geometry->updatePoint(3, 55, 25);
    _geometry->updatePoint(5, 75, 30);
    _geometry->updatePoint(7, 65, 15);

    CHECK_QUADRILATERAL(80, 40, 55, 25, 75, 30, 65, 15);

    AffineTransformation transformation;
    transformation.setAffineMatrixToIdentity();
    transformation.applyTranslation({ 100, 100 });
    transformation.applyScale({ 2.0, 2.0 });
    transformation.applyTranslation({ -40, -40 });
    _geometry->setAffineTransformation(&transformation);

    CHECK_QUADRILATERAL(180, 100, 130, 70, 170, 80, 150, 50);

    CHECK_QUADRILATERAL(80, 40, 55, 25, 75, 30, 65, 15, true);

    transformation.setAffineMatrixToIdentity();
    transformation.applyTranslation({ 10, 10 });
    _geometry->multiplyAffineTransformation(&transformation);

    CHECK_QUADRILATERAL(200, 120, 150, 90, 190, 100, 170, 70);

    CHECK_QUADRILATERAL(80, 40, 55, 25, 75, 30, 65, 15, true);
}
