#ifndef _CustomAssertions_H_
#define _CustomAssertions_H_

#include "Node.h"

#define TEST_ASSERT_EQUAL_NODE(left, right, color, actualNode) assertNode(left, right, color, actualNode, __LINE__)

void assertNode(Node *left, Node *right, char color, Node *actualNode, int lineNumber);

#endif // _CustomAssertions_H_