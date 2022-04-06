#ifndef _CLIST_H_
#define _CLIST_H_

#include <stddef.h>

struct intrusive_node {
	struct intrusive_node *next, *prev;
};

struct intrusive_list {
	struct intrusive_node *head, *tail;
};

#define container_of(ptr, type, member) (type*)((char*)(ptr) - (offsetof(type, member)))

struct intrusive_list* init_list(struct intrusive_list *list);

struct intrusive_node* init_node(struct intrusive_node *node);

struct intrusive_list* add_node(struct intrusive_list *list, struct intrusive_node *node);

struct intrusive_list* remove_node(struct intrusive_list *list, struct intrusive_node *node);

int get_length(struct intrusive_list *list);

void apply(struct intrusive_list *list, void (*op)(struct intrusive_node *node, void *data), void *data);

#endif
