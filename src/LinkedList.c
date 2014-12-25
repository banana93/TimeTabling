#include "LinkedList.h"
#include <stdio.h>
#include "malloc.h"


LinkedList *create_linkedList(){
		LinkedList *list = malloc(sizeof(LinkedList));
		list->head = NULL;
		list->tail = NULL;
		
		return list;
}

void addLinkedList(LinkedList *list, Item *data){
  Item *itemPointer = list->head;
  Item *previousItem;
	
	if(list->head == NULL && list->tail == NULL){
		list->head = data;
		list->tail = data;
	}
	else{
		while(1){
			if(itemPointer == NULL){
				list->tail = data;
				previousItem->next = data;
				break;
			}
			else{
				previousItem = itemPointer;
				itemPointer = itemPointer->next;
			}
		}
	}
}

void *removeFromHeadPriorityLinkedList(LinkedList *list) {
  Item *itemPointer = list->head;
  if(itemPointer != NULL) {
    list->head = itemPointer->next;
    if(itemPointer->next == NULL)
      list->tail = NULL;
  }
  return itemPointer;
}