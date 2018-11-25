#pragma once

#include <stdbool.h>

#include <list.h>

int
list_extend_alloc_size(struct list *lst);

// true if allocated size of mem is full
bool
list_requires_realloc(struct list *lst);

void *
list_logical_end(struct list *lst);
