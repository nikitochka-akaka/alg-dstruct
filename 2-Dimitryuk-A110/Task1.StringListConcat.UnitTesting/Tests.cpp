#include "gtest/gtest.h"

extern "C"
{
#include <stdlib.h>
#include "StringListConcat.h"
}

TEST(StringListConcatTesting, NullPointer_NULL)
{
	StringList* _emptyList = NULL;

	ASSERT_EQ(NULL, StringListConcat(_emptyList));
}

TEST(StringListConcatTesting, ListWithNoData_NULL)
{
    StringList _node1 = { NULL, NULL };
    StringList _list = { &_node1, NULL };

    ASSERT_EQ(NULL, StringListConcat(&_list));
}

TEST(StringListConcatTesting, NormalList_HelloWorld)
{
    StringList _node2 = { NULL, "World!" };
    StringList _node1 = { &_node2, ", " };
    StringList _list = { &_node1, "Hello" };

    ASSERT_STREQ("Hello, World!", StringListConcat(&_list));
}

TEST(StringListConcatTesting, ListWithGap_HelloMyIsRobot)
{
    StringList _node4 = { NULL, "Robot!" };
    StringList _node3 = { &_node4, "is " };
    StringList _node2 = { &_node3, NULL };    // Gap "name"
    StringList _node1 = { &_node2, ", my " };
    StringList _list = { &_node1, "Hello" };

    ASSERT_STREQ("Hello, my is Robot!", StringListConcat(&_list));
}
