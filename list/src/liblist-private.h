#pragma once

#include <stdbool.h>
#include "liblist.h"


static int
_list_extend_alloc_size(struct list *lst);

// true if allocated size of mem is full
static bool
_list_requires_realloc(struct list *lst);

static void * 
_list_logical_end(struct list *lst);
