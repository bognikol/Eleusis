#include "gtest/gtest.h"
#include "Node.h"
#include "01_vectoring/Vector.h"
#include <string>
#include <iostream>
#include <limits>

using namespace std;
using namespace Eleusis;
using namespace ::testing;

class NodeTestImpl : public Node
{
public:
    virtual void _layout() {};
    virtual void _render() {};
    virtual void _render(Region* region) {};
    virtual void _finalizeModel() {};
    virtual Rect getFullExtent() { return Rect(); };
};

class NodeTest : public Test
{
protected:
    NodeTestImpl* root1;
    NodeTestImpl* root2;
    NodeTestImpl* root3;
    NodeTestImpl* node1;
    NodeTestImpl* node2;
    NodeTestImpl* node3;

protected:
    NodeTest() {}
    ~NodeTest() {}
    void SetUp()
    {
        root1 = new NodeTestImpl();
        root2 = new NodeTestImpl();
        root3 = new NodeTestImpl();
        node1 = new NodeTestImpl();
        node2 = new NodeTestImpl();
        node3 = new NodeTestImpl();
    }

    void TearDown()
    {
    }

    void DeleteRoot()
    {
        if (root1) delete root1;
    }

    void DeleteRoot1()
    {
        if (root1) delete root1;
    }

    void DeleteRoot2()
    {
        if (root2) delete root2;
    }

    void DeleteRoot3()
    {
        if (root3) delete root3;
    }

    void DeleteNodes()
    {
        if (node1) delete node1;
        if (node2) delete node2;
        if (node3) delete node3;
    }
};

#define nulln nullptr

void CHECKNODE
(
    Node* node, 
    Node* previous_, 
    Node* previousSibling_,
    Node* parent_, 
    Node* firstChild_, 
    Node* nextSibling_,
    Node* next_, 
    Node* lastChild_, 
    Node* lastDescendant_
)
{
    EXPECT_EQ(node->previous(),         previous_)          << "\t\t---------> " << node << "\n";
    EXPECT_EQ(node->previousSibling(),  previousSibling_)   << "\t\t---------> " << node << "\n";
    EXPECT_EQ(node->parent(),           parent_)            << "\t\t---------> " << node << "\n";
    EXPECT_EQ(node->firstChild(),       firstChild_)        << "\t\t---------> " << node << "\n"; 
    EXPECT_EQ(node->nextSibling(),      nextSibling_)       << "\t\t---------> " << node << "\n";
    EXPECT_EQ(node->next(),             next_)              << "\t\t---------> " << node << "\n";
    EXPECT_EQ(node->lastChild(),        lastChild_)         << "\t\t---------> " << node << "\n";
    EXPECT_EQ(node->lastDescendant(),   lastDescendant_)    << "\t\t---------> " << node << "\n";
}


#define CHECKZ_EQ(node1_, node2_) \
    EXPECT_EQ(node1_->zCoordinate_get(), node2_->zCoordinate_get());

#define CHECKZ_LE(node1_, node2_) \
    EXPECT_LE(node1_->zCoordinate_get(), node2_->zCoordinate_get());

#define CHECKZ_LT(node1_, node2_) \
    EXPECT_LT(node1_->zCoordinate_get(), node2_->zCoordinate_get());

// GRAPH_1
// |node1|-->|node2|

#define CHECK_GRAPH_1 \
    CHECKNODE(node1, nulln, nulln, nulln, nulln, node2, node2, nulln, nulln); \
    CHECKNODE(node2, node1, node1, nulln, nulln, nulln, nulln, nulln, nulln); \
    CHECKZ_LE(node1, node2);

// GRAPH_2
//  |node1|-->|node2|-->|node3|

#define CHECK_GRAPH_2 \
    CHECKNODE(node1, nulln, nulln, nulln, nulln, node2, node2, nulln, nulln); \
    CHECKNODE(node2, node1, node1, nulln, nulln, node3, node3, nulln, nulln); \
    CHECKNODE(node3, node2, node2, nulln, nulln, nulln, nulln, nulln, nulln); \
    CHECKZ_LE(node1, node2); \
    CHECKZ_LE(node2, node3);

// GRAPH_3
//  |root1|-->|root2|
//     |
//    \/
//  |node1|-->|node2|-->|node3|

#define CHECK_GRAPH_3 \
    CHECKNODE(root1, nulln, nulln, nulln, node1, root2, node1, node3, node3); \
    CHECKNODE(root2, node3, root1, nulln, nulln, nulln, nulln, nulln, nulln); \
    CHECKNODE(node1, root1, nulln, root1, nulln, node2, node2, nulln, nulln); \
    CHECKNODE(node2, node1, node1, root1, nulln, node3, node3, nulln, nulln); \
    CHECKNODE(node3, node2, node2, root1, nulln, nulln, root2, nulln, nulln); \
    CHECKZ_LE(root1, root2); \
    CHECKZ_LE(node1, node2); \
    CHECKZ_LE(node2, node3);  

// GRAPH_3P
//  |root1|
//     |
//    \/
//  |node1|-->|node2|-->|node3|

#define CHECK_GRAPH_3P \
    CHECKNODE(root1, nulln, nulln, nulln, node1, nulln, node1, node3, node3); \
    CHECKNODE(node1, root1, nulln, root1, nulln, node2, node2, nulln, nulln); \
    CHECKNODE(node2, node1, node1, root1, nulln, node3, node3, nulln, nulln); \
    CHECKNODE(node3, node2, node2, root1, nulln, nulln, nulln, nulln, nulln); \
    CHECKZ_LE(node1, node2); \
    CHECKZ_LE(node2, node3); 

// GRAPH_4
//  |root1|
//     |
//    \/
//  |node1|

#define CHECK_GRAPH_4 \
    CHECKNODE(root1, nulln, nulln, nulln, node1, nulln, node1, node1, node1); \
    CHECKNODE(node1, root1, nulln, root1, nulln, nulln, nulln, nulln, nulln);

// GRAPH_5
//  |root1|
//     |
//    \/
//  |node1|
//     |
//    \/
//  |node2|

#define CHECK_GRAPH_5 \
    CHECKNODE(root1, nulln, nulln, nulln, node1, nulln, node1, node1, node2); \
    CHECKNODE(node1, root1, nulln, root1, node2, nulln, node2, node2, node2); \
    CHECKNODE(node2, node1, nulln, node1, nulln, nulln, nulln, nulln, nulln); 

// GRAPH_6
//  |root1|-->|root3|
//     |
//    \/
//  |root2|
//     |
//    \/
//  |node1|-->|node2|
//     |
//    \/
//  |node3|

#define CHECK_GRAPH_6 \
    CHECKNODE(root1, nulln, nulln, nulln, root2, root3, root2, root2, node2); \
    CHECKNODE(root2, root1, nulln, root1, node1, nulln, node1, node2, node2); \
    CHECKNODE(root3, node2, root1, nulln, nulln, nulln, nulln, nulln, nulln); \
    CHECKNODE(node1, root2, nulln, root2, node3, node2, node3, node3, node3); \
    CHECKNODE(node2, node3, node1, root2, nulln, nulln, root3, nulln, nulln); \
    CHECKNODE(node3, node1, nulln, node1, nulln, nulln, node2, nulln, nulln); \
    CHECKZ_LE(root1, root3); \
    CHECKZ_LE(node1, node2);

// GRAPH_7
//  |root1|-->|root2|-->|root3|
//                |
//               \/
//            |node1|-->|node2|
//                |
//               \/
//            |node3|

#define CHECK_GRAPH_7 \
    CHECKNODE(root1, nulln, nulln, nulln, nulln, root2, root2, nulln, nulln); \
    CHECKNODE(root2, root1, root1, nulln, node1, root3, node1, node2, node2); \
    CHECKNODE(root3, node2, root2, nulln, nulln, nulln, nulln, nulln, nulln); \
    CHECKNODE(node1, root2, nulln, root2, node3, node2, node3, node3, node3); \
    CHECKNODE(node2, node3, node1, root2, nulln, nulln, root3, nulln, nulln); \
    CHECKNODE(node3, node1, nulln, node1, nulln, nulln, node2, nulln, nulln); \
    CHECKZ_LE(root1, root2); \
    CHECKZ_LE(root2, root3); \
    CHECKZ_LE(node1, node2);

// GRAPH_8
//  |root1|
//      |
//     \/
//  |root2|-->|node1|-->|root3|
//               |
//              \/
//            |node2|-->|node3|

#define CHECK_GRAPH_8 \
    CHECKNODE(root1, nulln, nulln, nulln, root2, nulln, root2, root3, root3); \
    CHECKNODE(root2, root1, nulln, root1, nulln, node1, node1, nulln, nulln); \
    CHECKNODE(root3, node3, node1, root1, nulln, nulln, nulln, nulln, nulln); \
    CHECKNODE(node1, root2, root2, root1, node2, root3, node2, node3, node3); \
    CHECKNODE(node2, node1, nulln, node1, nulln, node3, node3, nulln, nulln); \
    CHECKNODE(node3, node2, node2, node1, nulln, nulln, root3, nulln, nulln); \
    CHECKZ_LE(root2, node1); \
    CHECKZ_LE(node1, root3); \
    CHECKZ_LE(node2, node3);




TEST_F(NodeTest, constructor)
{
    CHECKNODE(node1, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
    EXPECT_EQ(node1->zCoordinate_get(), 0);

    DeleteNodes();
}

TEST_F(NodeTest, insertAfter_TEST_1)
{
    //TEST 1:
    //Condition: node_2 inserted after node_1; node_1 does not have parent; node_1 does not have explicitelly set z_Coordinate

    node1->insertAfter(node2);

    CHECK_GRAPH_1;

    CHECKZ_LT(node1, node2);

    DeleteNodes();
}
TEST_F(NodeTest, insertAfter_TEST_1_1)
{
    //TEST 1_1:
    //Condition: node_2 inserted after node_1; node_1 does not have parent; node_1 has explicitelly set z_Coordinate to UINT_MAX

    node1->zCoordinate_set(UINT_MAX);
    node1->insertAfter(node2);

    CHECK_GRAPH_1;

    CHECKZ_EQ(node1, node2);

    DeleteNodes();
}
TEST_F(NodeTest, insertAfter_TEST_2)
{
    //TEST 2:
    //Condition: node_3 inserted after node_1; node_2 inserted after node_1; node_1 does not have parent; node_1 does not have explicitelly set z_Coordinate

    root1->insertChild(node2);
    root1->insertChild(node3);

    node1->insertAfter(node3);
    node1->insertAfter(node2);

    CHECK_GRAPH_2;

    CHECKZ_LT(node1, node2);
    CHECKZ_EQ(node2, node3);

    DeleteNodes();
}
TEST_F(NodeTest, insertAfter_TEST_3)
{
    //TEST 3:
    //Condition: node_1 has set parent; node_3 inserted after node_1; node_2 inserted after node_1; node_1 does not have explicitelly set z_Coordinate

    root2->insertBefore(root1);
    root1->insertChild(node1);
    node1->insertAfter(node3);
    node1->insertAfter(node2);

    CHECK_GRAPH_3;

    CHECKZ_LT(node1, node2);
    CHECKZ_EQ(node2, node3);

    DeleteRoot();
}
TEST_F(NodeTest, insertAfter_TEST_4)
{
    //TEST 4:
    //Condition: node_1 has set parent; node_2 inserted after node_1; node_3 inserted after node_2; node_1 does not have explicitelly set z_Coordinate

    root1->insertChild(node1);
    node1->insertAfter(node2);
    node2->insertAfter(node3);
    root2->insertBefore(root1);

    CHECK_GRAPH_3;

    CHECKZ_LT(node1, node2);
    CHECKZ_LT(node2, node3);

    DeleteRoot();
}
TEST_F(NodeTest, insertAfter_TEST_5)
{
    //TEST 5:
    //Condition: node_1 is parented to root; root_sibling is inserted after root; node_2 inserted after node_1; node_3 inserted after node_2; node_1 does not have explicitelly set z_Coordinate

    root1->insertChild(node1);
    root1->insertAfter(root2);
    node1->insertAfter(node2);
    node2->insertAfter(node3);

    CHECK_GRAPH_3;

    CHECKZ_LT(root1, root2);
    CHECKZ_LT(node1, node2);
    CHECKZ_LT(node2, node3);

    DeleteRoot();
}
TEST_F(NodeTest, insertAfter_TEST_6)
{
    //TEST 6:
    //Condition: node_1 is parented to root; root_sibling is inserted after root; node_2 inserted after node_1; node_3 inserted after node_2; all nodes have explicitelly set zCoordinate

    root1->zCoordinate_set(200);
    node1->zCoordinate_set(100);
    node2->zCoordinate_set(50);
    node3->zCoordinate_set(75);

    root1->insertChild(node1);
    root1->insertAfter(root2);
    node1->insertAfter(node2);
    node2->insertAfter(node3);

    CHECK_GRAPH_3;

    CHECKZ_LT(root1, root2);
    CHECKZ_LT(node1, node2);
    CHECKZ_LT(node2, node3);

    DeleteRoot();
}

TEST_F(NodeTest, insertBefore_TEST_1)
{
    //TEST 1:
    //Condition: node_1 inserted before node_2; node_2 does not have parent; node_1 does not have explicitelly set z_Coordinate

    node2->insertBefore(node1);

    CHECK_GRAPH_1;

    CHECKZ_EQ(node1, node2);

    DeleteNodes();
}
TEST_F(NodeTest, insertBefore_TEST_1_1)
{
    //TEST 1_1:
    //Condition: node_1 inserted before node_2; node_2 does not have parent; node_2 has explicitelly set z_Coordinate

    root1->insertChild(node1);

    node2->zCoordinate_set(50);
    node2->insertBefore(node1);

    CHECK_GRAPH_1;

    CHECKZ_LT(node1, node2);

    DeleteNodes();
}
TEST_F(NodeTest, inserBefore_TEST_2)
{
    //TEST 2:
    //Condition: node_1 inserted before node3; node_2 inserted before node_3; node_1 does not have parent; node_3 do not have explicitelly set z_Coordinate
    
    root1->insertChild(node1);
    root1->insertChild(node2);

    node3->insertBefore(node1);
    node3->insertBefore(node2);

    CHECK_GRAPH_2;

    CHECKZ_EQ(node1, node2);
    CHECKZ_EQ(node2, node3);

    DeleteNodes();
}
TEST_F(NodeTest, insertBefore_TEST_3)
{

    //TEST 3:
    //Condition: node_2 inserted before node3; node_1 inserted before node_2; node_1 does not have parent; node_3 do not have explicitelly set z_Coordinate

    node3->insertBefore(node2);
    node2->insertBefore(node1);

    CHECK_GRAPH_2;

    CHECKZ_EQ(node1, node2);
    CHECKZ_EQ(node2, node3);

    DeleteNodes();

}
TEST_F(NodeTest, insertBefore_TEST_4)
{
    //TEST 4:
    //Condition: node_3 has set parent; node_1 inserted before node_3; node_2 inserted before node_3; node_3 does not have explicitelly set z_Coordinate

    root1->insertChild(node3);
    node3->insertBefore(node1);
    node3->insertBefore(node2);
    root2->insertBefore(root1);

    CHECK_GRAPH_3;

    CHECKZ_EQ(root1, root2);
    CHECKZ_EQ(node1, node2);
    CHECKZ_EQ(node2, node3);

    DeleteRoot();
}
TEST_F(NodeTest, insertBefore_TEST_5)
{
    //TEST 5:
    //Condition: node_3 is parented to root; root_sibling is inserted before root; node_1inserted before node_3; node_2 inserted after node_3; node_3 does not have explicitelly set z_Coordinate

    root2->insertBefore(root1);
    root1->insertChild(node3);
    node3->insertBefore(node1);
    node3->insertBefore(node2);

    CHECK_GRAPH_3;

    CHECKZ_EQ(root1, root2);
    CHECKZ_EQ(node1, node2);
    CHECKZ_EQ(node2, node3);

    DeleteRoot();
}
TEST_F(NodeTest, insertBefore_TEST_6)
{
    //TEST 6:
    //Condition: node_3 is parented to root; root_sibling is inserted before root; node_1inserted before node_3; node_2 inserted after node_3; all nodes have explicitelly set z_Coordinate

    root1->zCoordinate_set(200);
    node1->zCoordinate_set(100);
    node2->zCoordinate_set(50);
    node3->zCoordinate_set(75);

    root2->insertBefore(root1);
    root1->insertChild(node3);
    node3->insertBefore(node1);
    node3->insertBefore(node2);

    CHECK_GRAPH_3;

    CHECKZ_EQ(root1, root2);
    CHECKZ_EQ(node1, node2);
    CHECKZ_LT(node2, node3);

    DeleteRoot();
}

TEST_F(NodeTest, insertChild_overload_1_TEST_1)
{
    root1->insertChild(node1);

    CHECK_GRAPH_4;
   
    DeleteRoot();
}

TEST_F(NodeTest, insertChild_overload_1_TEST_2)
{
    root1->insertChild(node1);
    root1->insertChild(node2);
    root1->insertChild(node3);
    root1->insertAfter(root2);

    CHECK_GRAPH_3;

	EXPECT_LE(node1->zCoordinate_get(), node2->zCoordinate_get());

    DeleteRoot();
}
TEST_F(NodeTest, insertChild_overload_1_TEST_2P)
{
    root1->insertChild(node1);
    root1->insertChild(node2);
    root1->insertChild(node3);

    CHECK_GRAPH_3P;

    DeleteRoot1();
    DeleteRoot3();
}
TEST_F(NodeTest, insertChild_overload_1_TEST_3)
{
    root1->insertChild(root2);
    root2->insertChild(node1);
    node1->insertChild(node3);
    root3->insertBefore(root1);
    node1->insertAfter(node2);

    CHECK_GRAPH_6;

    root1->insertAfter(root2);

    CHECK_GRAPH_7;

    DeleteRoot1();
    DeleteRoot3();
}
TEST_F(NodeTest, insertChild_overload_1_TEST_4)
{
    root2->insertBefore(root1);
    root2->insertAfter(root3);
    node1->insertChild(node3);
    root2->insertChild(node1);
    root2->insertChild(node2);

    CHECK_GRAPH_7;

    root1->insertChild(root2);

    CHECK_GRAPH_6;

    DeleteRoot1();
    DeleteRoot3();
}

TEST_F(NodeTest, insertChild_overload_2_TEST_1)
{
    root1->insertChild(node1, 100);

    CHECK_GRAPH_4;

    DeleteRoot1();
}
TEST_F(NodeTest, insertChild_overload_2_TEST_2_1)
{
    root1->insertChild(node1, 50);
    node1->insertChild(node2, 25);

    CHECK_GRAPH_5;

    DeleteRoot1();
}
TEST_F(NodeTest, insertChild_overload_2_TEST_2_2)
{
    root1->insertChild(node3, 75);
    root1->insertChild(node2, 50);
    root1->insertChild(node1, 25);

    CHECK_GRAPH_3P;

    DeleteRoot1();
}
TEST_F(NodeTest, insertChild_overload_2_TEST_2_3)
{
    root1->insertChild(node1, 25);
    root1->insertChild(node2, 50);
    root1->insertChild(node3, 75);

    CHECK_GRAPH_3P;

    DeleteRoot1();
}
TEST_F(NodeTest, insertChild_overload_2_TEST_2_4)
{
    root1->insertChild(node1, 25);
    root1->insertChild(node2, 50);
    root1->insertChild(node3, 75);

    CHECK_GRAPH_3P;

    DeleteRoot1();
}
TEST_F(NodeTest, insertChild_overload_2_TEST_3_1)
{
    root1->insertChild(node1, 25);
    root1->insertChild(node2, 50);
    root1->insertChild(node3, 75);
    root2->insertBefore(root1);

    CHECK_GRAPH_3;

    DeleteRoot1();
    DeleteRoot2();
}
TEST_F(NodeTest, insertChild_overload_2_TEST_3_2)
{
    root1->insertChild(node1, 25);
    root1->insertChild(node3, 75);
    root1->insertChild(node2, 50);
    root2->insertBefore(root1);

    CHECK_GRAPH_3;

    DeleteRoot1();
}
TEST_F(NodeTest, insertChild_overload_2_TEST_3_3)
{
    root1->insertChild(node3, 75);
    root1->insertChild(node2, 50);
    root1->insertChild(node1, 25);
    root2->insertBefore(root1);

    CHECK_GRAPH_3;

    DeleteRoot1();
}
TEST_F(NodeTest, insertChild_overload_2_TEST_3_4)
{
    root1->insertChild(node1, 25);
    root1->insertChild(node2, 25);
    root1->insertChild(node3, 25);
    root2->insertBefore(root1);

    CHECK_GRAPH_3;

    DeleteRoot1();
}
TEST_F(NodeTest, insertChild_overload_2_TEST_4)
{
    root3->insertBefore(root2);
    root2->insertBefore(root1);
    node1->insertChild(node3, 75);
    root2->insertChild(node1, 50);
    root2->insertChild(node2, 75);

    CHECK_GRAPH_7;

    root1->insertChild(root2, 10);

    CHECK_GRAPH_6;

    DeleteRoot1();
    DeleteRoot3();
}

TEST_F(NodeTest, remove_TEST_1)
{
    root1->insertAfter(root2);
    root2->insertAfter(root3);
    root2->insertChild(node1);
    node1->insertAfter(node2);
    node1->insertChild(node3);
    
    CHECK_GRAPH_7;

    node1->remove();

    CHECKNODE(root1, nulln, nulln, nulln, nulln, root2, root2, nulln, nulln);
    CHECKNODE(root2, root1, root1, nulln, node2, root3, node2, node2, node2);
    CHECKNODE(root3, node2, root2, nulln, nulln, nulln, nulln, nulln, nulln);
    CHECKNODE(node2, root2, nulln, root2, nulln, nulln, root3, nulln, nulln);

    CHECKNODE(node1, nulln, nulln, nulln, node3, nulln, node3, node3, node3);
    CHECKNODE(node3, node1, nulln, node1, nulln, nulln, nulln, nulln, nulln);
}
TEST_F(NodeTest, remove_TEST_2)
{
    root1->insertAfter(root2);
    root2->insertAfter(root3);
    root2->insertChild(node1);
    node1->insertAfter(node2);
    node1->insertChild(node3);

    CHECK_GRAPH_7;

    root2->remove();

    CHECKNODE(root1, nulln, nulln, nulln, nulln, root3, root3, nulln, nulln);
    CHECKNODE(root3, root1, root1, nulln, nulln, nulln, nulln, nulln, nulln);
    
    CHECKNODE(root2, nulln, nulln, nulln, node1, nulln, node1, node2, node2);
    CHECKNODE(node1, root2, nulln, root2, node3, node2, node3, node3, node3);
    CHECKNODE(node2, node3, node1, root2, nulln, nulln, nulln, nulln, nulln);
    CHECKNODE(node3, node1, nulln, node1, nulln, nulln, node2, nulln, nulln);
}
TEST_F(NodeTest, remove_TEST_3)
{
    root1->insertChild(node1);
    node1->insertAfter(root3);
    node1->insertBefore(root2);
    node1->insertChild(node2);
    node1->insertChild(node3);

    CHECK_GRAPH_8;

    node1->remove();

    CHECKNODE(root1, nulln, nulln, nulln, root2, nulln, root2, root3, root3);
    CHECKNODE(root2, root1, nulln, root1, nulln, root3, root3, nulln, nulln);
    CHECKNODE(root3, root2, root2, root1, nulln, nulln, nulln, nulln, nulln);

    CHECKNODE(node1, nulln, nulln, nulln, node2, nulln, node2, node3, node3);
    CHECKNODE(node2, node1, nulln, node1, nulln, node3, node3, nulln, nulln);
    CHECKNODE(node3, node2, node2, node1, nulln, nulln, nulln, nulln, nulln);
}

TEST_F(NodeTest, removeChild_TEST_1)
{
    root1->insertAfter(root2);
    root2->insertAfter(root3);
    root2->insertChild(node1);
    node1->insertAfter(node2);
    node1->insertChild(node3);

    CHECK_GRAPH_7;

    root2->removeChild(node1);

    CHECKNODE(root1, nulln, nulln, nulln, nulln, root2, root2, nulln, nulln);
    CHECKNODE(root2, root1, root1, nulln, node2, root3, node2, node2, node2);
    CHECKNODE(root3, node2, root2, nulln, nulln, nulln, nulln, nulln, nulln);
    CHECKNODE(node2, root2, nulln, root2, nulln, nulln, root3, nulln, nulln);

    CHECKNODE(node1, nulln, nulln, nulln, node3, nulln, node3, node3, node3);
    CHECKNODE(node3, node1, nulln, node1, nulln, nulln, nulln, nulln, nulln);
}
TEST_F(NodeTest, removeChild_TEST_2)
{
    root1->insertAfter(root2);
    root2->insertAfter(root3);
    root2->insertChild(node1);
    node1->insertAfter(node2);
    node1->insertChild(node3);

    CHECK_GRAPH_7;

    root2->removeChild(node2);

    CHECKNODE(root1, nulln, nulln, nulln, nulln, root2, root2, nulln, nulln);
    CHECKNODE(root2, root1, root1, nulln, node1, root3, node1, node1, node3);
    CHECKNODE(root3, node3, root2, nulln, nulln, nulln, nulln, nulln, nulln);
    CHECKNODE(node1, root2, nulln, root2, node3, nulln, node3, node3, node3);
    CHECKNODE(node3, node1, nulln, node1, nulln, nulln, root3, nulln, nulln);

    CHECKNODE(node2, nulln, nulln, nulln, nulln, nulln, nulln, nulln, nulln);
}
TEST_F(NodeTest, removeChild_TEST_3)
{
    root1->insertChild(node1);
    node1->insertAfter(root3);
    node1->insertBefore(root2);
    node1->insertChild(node2);
    node1->insertChild(node3);

    CHECK_GRAPH_8;

    root1->removeChild(node1);

    CHECKNODE(root1, nulln, nulln, nulln, root2, nulln, root2, root3, root3);
    CHECKNODE(root2, root1, nulln, root1, nulln, root3, root3, nulln, nulln);
    CHECKNODE(root3, root2, root2, root1, nulln, nulln, nulln, nulln, nulln);

    CHECKNODE(node1, nulln, nulln, nulln, node2, nulln, node2, node3, node3);
    CHECKNODE(node2, node1, nulln, node1, nulln, node3, node3, nulln, nulln);
    CHECKNODE(node3, node2, node2, node1, nulln, nulln, nulln, nulln, nulln);
}

TEST_F(NodeTest, zCoordinate_set_TEST_1)
{
    root1->insertChild(node1, 25);
    root1->insertChild(node2, 50);
    root1->insertChild(node3, 75);

    CHECK_GRAPH_3P;

    node1->zCoordinate_set(65);

    CHECKNODE(root1, nulln, nulln, nulln, node2, nulln, node2, node3, node3);
    CHECKNODE(node2, root1, nulln, root1, nulln, node1, node1, nulln, nulln);
    CHECKNODE(node1, node2, node2, root1, nulln, node3, node3, nulln, nulln);
    CHECKNODE(node3, node1, node1, root1, nulln, nulln, nulln, nulln, nulln);

    DeleteRoot1();
}
TEST_F(NodeTest, zCoordinate_set_TEST_2)
{
    root1->insertChild(node1, 25);
    root1->insertChild(node2, 50);
    root1->insertChild(node3, 75);

    CHECK_GRAPH_3P;

    node1->zCoordinate_set(100);

    CHECKNODE(root1, nulln, nulln, nulln, node2, nulln, node2, node1, node1);
    CHECKNODE(node2, root1, nulln, root1, nulln, node3, node3, nulln, nulln);
    CHECKNODE(node3, node2, node2, root1, nulln, node1, node1, nulln, nulln);
    CHECKNODE(node1, node3, node3, root1, nulln, nulln, nulln, nulln, nulln);

    DeleteRoot1();
}
TEST_F(NodeTest, zCoordinate_set_TEST_3)
{
    root1->insertChild(node1, 25);
    root1->insertChild(node2, 50);
    root1->insertChild(node3, 75);

    CHECK_GRAPH_3P;

    node2->zCoordinate_set(100);

    CHECKNODE(root1, nulln, nulln, nulln, node1, nulln, node1, node2, node2);
    CHECKNODE(node1, root1, nulln, root1, nulln, node3, node3, nulln, nulln);
    CHECKNODE(node3, node1, node1, root1, nulln, node2, node2, nulln, nulln);
    CHECKNODE(node2, node3, node3, root1, nulln, nulln, nulln, nulln, nulln);

    DeleteRoot1();
}
TEST_F(NodeTest, zCoordinate_set_TEST_4)
{
    root1->insertChild(node1, 25);
    root1->insertChild(node2, 50);
    root1->insertChild(node3, 75);

    CHECK_GRAPH_3P;

    node2->zCoordinate_set(10);

    CHECKNODE(root1, nulln, nulln, nulln, node2, nulln, node2, node3, node3);
    CHECKNODE(node2, root1, nulln, root1, nulln, node1, node1, nulln, nulln);
    CHECKNODE(node1, node2, node2, root1, nulln, node3, node3, nulln, nulln);
    CHECKNODE(node3, node1, node1, root1, nulln, nulln, nulln, nulln, nulln);

    DeleteRoot1();
}
TEST_F(NodeTest, zCoordinate_set_TEST_5)
{
    root1->insertChild(node1, 25);
    root1->insertChild(node2, 50);
    root1->insertChild(node3, 75);

    CHECK_GRAPH_3P;

    node3->zCoordinate_set(35);

    CHECKNODE(root1, nulln, nulln, nulln, node1, nulln, node1, node2, node2);
    CHECKNODE(node1, root1, nulln, root1, nulln, node3, node3, nulln, nulln);
    CHECKNODE(node3, node1, node1, root1, nulln, node2, node2, nulln, nulln);
    CHECKNODE(node2, node3, node3, root1, nulln, nulln, nulln, nulln, nulln);

    DeleteRoot1();
}
TEST_F(NodeTest, zCoordinate_set_TEST_6)
{
    root1->insertChild(node1, 25);
    root1->insertChild(node2, 50);
    root1->insertChild(node3, 75);

    CHECK_GRAPH_3P;

    node3->zCoordinate_set(10);

    CHECKNODE(root1, nulln, nulln, nulln, node3, nulln, node3, node2, node2);
    CHECKNODE(node3, root1, nulln, root1, nulln, node1, node1, nulln, nulln);
    CHECKNODE(node1, node3, node3, root1, nulln, node2, node2, nulln, nulln);
    CHECKNODE(node2, node1, node1, root1, nulln, nulln, nulln, nulln, nulln);

    DeleteRoot1();
}
TEST_F(NodeTest, youngestCommonAncestor)
{
    // GRAPH_7
    //  |root1|-->|root2|-->|root3|
    //                |
    //               \/
    //            |node1|-->|node2|
    //                |
    //               \/
    //            |node3|

    root2->insertBefore(root1);
    root2->insertAfter(root3);
    node1->insertChild(node3);
    root2->insertChild(node1);
    root2->insertChild(node2);

    CHECK_GRAPH_7;

    EXPECT_EQ(root2, Node::youngestCommonAncestor(node2, node3));
    EXPECT_EQ(root2, Node::youngestCommonAncestor(node1, node2));
    EXPECT_EQ(node1, Node::youngestCommonAncestor(node1, node3));
    EXPECT_EQ(root2, Node::youngestCommonAncestor(root2, node3));
    EXPECT_EQ(Node::youngestCommonAncestor(root1, root2), Node::youngestCommonAncestor(root2, root3));
    EXPECT_EQ(Node::youngestCommonAncestor(root1, root2), Node::youngestCommonAncestor(node3, root3));

}


//TEST_F(NodeTest, clone_TEST_1)
//{
//    root1->insertChild(node1);
//    node1->insertAfter(root3);
//    node1->insertBefore(root2);
//    node1->insertChild(node2);
//    node1->insertChild(node3);
//
//    CHECK_GRAPH_8;
//
//    NodeTestImpl* aClone = nullptr;
//
//    root1->clone(aClone);
//
//    NodeTestImpl* aClone_root1 = aClone;
//    NodeTestImpl* aClone_root2 = aClone->firstChild();
//    NodeTestImpl* aClone_node1 = aClone_root2->nextSibling();
//    NodeTestImpl* aClone_root3 = aClone_node1->nextSibling();
//    NodeTestImpl* aClone_node2 = aClone_node1->firstChild();
//    NodeTestImpl* aClone_node3 = aClone_node2->nextSibling();
//
//    CHECKNODE(aClone_root1, nulln, nulln, nulln, aClone_root2, nulln, aClone_root2);
//    CHECKNODE(aClone_root2, aClone_root1, nulln, aClone_root1, nulln, aClone_node1, aClone_node1);
//    CHECKNODE(aClone_root3, aClone_node3, aClone_node1, aClone_root1, nulln, nulln, nulln);
//    CHECKNODE(aClone_node1, aClone_root2, aClone_root2, aClone_root1, aClone_node2, aClone_root3, aClone_node2);
//    CHECKNODE(aClone_node2, aClone_node1, nulln, aClone_node1, nulln, aClone_node3, aClone_node3);
//    CHECKNODE(aClone_node3, aClone_node2, aClone_node2, aClone_node1, nulln, nulln, aClone_root3);
//}
//TEST_F(NodeTest, clone_TEST_2)
//{
//    root1->insertChild(root2);
//    root2->insertChild(node1);
//    node1->insertChild(node3);
//    root3->insertBefore(root1);
//    node1->insertAfter(node2);
//    root1->insertAfter(root2);
//
//    CHECK_GRAPH_7;
//
//    NodeTestImpl* aClone = nullptr;
//
//    root2->clone(aClone);
//
//    NodeTestImpl* aClone_root2 = aClone;
//    NodeTestImpl* aClone_node1 = aClone_root2->firstChild();
//    NodeTestImpl* aClone_node2 = aClone_node1->nextSibling();
//    NodeTestImpl* aClone_node3 = aClone_node1->firstChild();
//
//    CHECKNODE(aClone_root2, nulln, nulln, nulln, aClone_node1, nulln, aClone_node1);
//    CHECKNODE(aClone_node1, aClone_root2, nulln, aClone_root2, aClone_node3, aClone_node2, aClone_node3);
//    CHECKNODE(aClone_node2, aClone_node3, aClone_node1, aClone_root2, nulln, nulln, nulln);
//    CHECKNODE(aClone_node3, aClone_node1, nulln, aClone_node1, nulln, nulln, aClone_node2);
//}