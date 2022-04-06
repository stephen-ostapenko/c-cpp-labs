#include <stdlib.h>
#include <stdio.h>
#include "point_list.h"

struct intrusive_list* add_point(struct intrusive_list *list, int x, int y) {
	struct point *new_point = malloc(sizeof(struct point));
	new_point->x = x; new_point->y = y;
	init_node(&(new_point->node));

	add_node(list, &new_point->node);

	return list;
}

struct intrusive_list* remove_point(struct intrusive_list *list, int x, int y) {
	struct intrusive_node *list_iter = list->head;

	while (list_iter) {
		struct point *current_point = container_of(list_iter, struct point, node);
		struct intrusive_node *next_iter = list_iter->next;

		if (current_point->x == x && current_point->y == y) {
			remove_node(list, list_iter);
			free(current_point);
		}

		list_iter = next_iter;
	}

	return list;
}

struct intrusive_list* show_all_points(struct intrusive_list *list) {
	struct intrusive_node *list_iter = list->head;

	while (list_iter) {
		struct point *current_point = container_of(list_iter, struct point, node);

		printf("(%d %d)", current_point->x, current_point->y);
		if (list_iter->next) {
			printf(" ");
		}

		list_iter = list_iter->next;
	}

	printf("\n");

	return list;
}

struct intrusive_list* remove_all_points(struct intrusive_list *list) {
	struct intrusive_node *list_iter = list->head;	

	while (list_iter) {
		struct point *current_point = container_of(list_iter, struct point, node);
		struct intrusive_node *next_iter = list_iter->next;

		remove_node(list, list_iter);
		free(current_point);

		list_iter = next_iter;
	}

	return list;
}

void print(struct intrusive_node *node, void *fmt) {
	struct point *current_point = container_of(node, struct point, node);
	int x = current_point->x, y = current_point->y;

	printf((char*)fmt, x, y);
}

void count(struct intrusive_node *node, void *result) {
	(void)node; (*(size_t*)result)++;
}