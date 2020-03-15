#pragma once
#include <string.h>

#define restore_inactive(Iterator, Label) do { \
    if (!(Iterator)->active) { \
        goto Label; \
    } \
} while (0)

#define restore(Iterator, Label) do { \
    if (strcmp((Iterator)->active, #Label) == 0) { \
        goto Label; \
    } \
} while (0)

#define checkpoint(Label) Label:

typedef struct {
    char const* active;
} Iterator;

static inline Iterator ready_iterator()
{
    return (Iterator){.active = ""};
}

static inline int yield(Iterator *it, char const *label)
{
    it->active = label;
    return 0;
}
