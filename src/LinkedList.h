#ifndef LinkedList_H
#define LinkedList_H

#include "TimeTabling.h"

typedef struct Item Item;

struct Item {
  Item *next;
	Population *population;
};

typedef struct LinkedList LinkedList;

struct LinkedList {
  Item *head;
  Item *tail;
};

LinkedList *create_linkedList();
void addLinkedList(LinkedList *list, Item *data);
void *removeFromHeadLinkedList(LinkedList *list);


#endif // LinkedList_H