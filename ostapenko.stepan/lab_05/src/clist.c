#include "clist.h"

struct intrusive_list* init_list(struct intrusive_list *list) {
	list->head = list->tail = NULL;

	return list;
}

struct intrusive_node* init_node(struct intrusive_node *node) {
	node->prev = node->next = NULL;
	
	return node;
}

struct intrusive_list* add_node(struct intrusive_list *list, struct intrusive_node *node) {
	node->prev = list->tail;
	
	if (list->tail) {
		list->tail->next = node;
	}
	
	list->tail = node;
	if (!list->head) {
		list->head = node;
	}
	
	return list;
}

struct intrusive_list* remove_node(struct intrusive_list *list, struct intrusive_node *node) {
	if (node->prev) {
		node->prev->next = node->next;
	}
	if (node->next) {
		node->next->prev = node->prev;
	}

	if (!node->prev) {
		list->head = node->next;
	}
	if (!node->next) {
		list->tail = node->prev;
	}

	return list;
}

int get_length(struct intrusive_list *list) {
	int result = 0;
	struct intrusive_node *list_iter = list->head;
	
	while (list_iter) {
		result++;

		list_iter = list_iter->next;
	}

	return result;
}

void apply(struct intrusive_list *list, void (*op)(struct intrusive_node *node, void *data), void *data) {
	struct intrusive_node *list_iter = list->head;

	while (list_iter) {
		op(list_iter, data);

		list_iter = list_iter->next;
	}
}