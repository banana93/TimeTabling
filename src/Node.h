#ifndef Node_H
#define Node_H

#include "TimeTabling.h"
typedef struct Node Node;
struct Node {
	Node *left;
	Node *right;
	char color; // 'b' or 'r'(black or red)
	Population *data;
};

#endif // Node_H
