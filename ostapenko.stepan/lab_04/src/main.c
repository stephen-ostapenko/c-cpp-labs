#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include "clist.h"

const int BUF_SIZE = 240;

struct point {
	int x, y;
	struct intrusive_node node;
};

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

int main() {
	char q[BUF_SIZE];
	struct intrusive_list list;
	init_list(&list);

	while (1) {
		scanf("%239s", q);

		if (!strcmp(q, "add")) {
			int x, y;
			scanf("%11d %11d", &x, &y);

			add_point(&list, x, y);

			continue;
		}

		if (!strcmp(q, "rm")) {
			int x, y;
			scanf("%11d %11d", &x, &y);

			remove_point(&list, x, y);

			continue;
		}

		if (!strcmp(q, "print")) {
			show_all_points(&list);

			continue;
		}

		if (!strcmp(q, "rma")) {
			remove_all_points(&list);

			continue;
		}

		if (!strcmp(q, "len")) {
			printf("%d\n", get_length(&list));

			continue;
		}

		if (!strcmp(q, "exit")) {
			remove_all_points(&list);
			exit(0);
		}

		printf("Unknown command\n");
	}

	remove_all_points(&list);

	return 0;
}
