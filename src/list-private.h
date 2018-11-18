#pragma once

#include <stdbool.h>

#include <list.h>

static int
list_extend_alloc_size(struct list *lst);

// true if allocated size of mem is full
static bool
list_requires_realloc(struct list *lst);

static void *
list_logical_end(struct list *lst);
