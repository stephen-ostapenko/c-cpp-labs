#include <stdlib.h>
#include "clist.h"

struct intrusive_list* init_list(struct intrusive_list *list) {
	list->head = NULL;

	return list;
}

struct intrusive_node* init_node(struct intrusive_node *node) {
	node->prev = node->next = NULL;
	
	return node;
}

struct intrusive_list* add_node(struct intrusive_list *list, struct intrusive_node *node) {
	node->next = list->head;
	
	if (list->head) {
		list->head->prev = node;
	}
	
	list->head = node;
	
	return list;
}

struct intrusive_list* remove_node(struct intrusive_list *list, struct intrusive_node *node) {
	if (node->prev) {
		node->prev->next = node->next;
	} else {
		list->head = node->next;
	}

	if (node->next) {
		node->next->prev = node->prev;
	}

	return list;
}

int get_length(struct intrusive_list *list) {
	int result = 0;
	struct intrusive_node *list_iter = list->head;
	
	while (list_iter) {
		list_iter = list_iter->next;
		result++;
	}

	return result;
}