#ifndef _POINT_LIST_H_
#define _POINT_LIST_H_

#include "clist.h"

struct point {
	int x, y;
	struct intrusive_node node;
};

struct intrusive_list* add_point(struct intrusive_list *list, int x, int y);

struct intrusive_list* remove_point(struct intrusive_list *list, int x, int y);

struct intrusive_list* show_all_points(struct intrusive_list *list);

struct intrusive_list* remove_all_points(struct intrusive_list *list);

void print(struct intrusive_node *node, void *fmt);

void count(struct intrusive_node *node, void *result);

#endif