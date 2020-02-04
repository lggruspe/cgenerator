#pragma once
#include <stdbool.h>
#include <stddef.h>

#define CONCAT_IMPL(x, y) x##y
#define CONCAT(x, y) CONCAT_IMPL(x, y)

typedef struct {
    void *label;
    bool done;
} Iterator;

#define Generator(Type, Name, ...) \
Type Name(Iterator *prev, ##__VA_ARGS__) \
{ \
    struct { Type garbage; void *null; } impl = { .null = NULL }; \
    if (prev->done) { \
        goto end; \
    } \
    if (prev->label) { \
        goto *(prev->label); \
    }

#define yield(Value) \
        set_yield_label((Value), CONCAT(l, __COUNTER__))

#define set_yield_label(Value, Label) \
        prev->label = &&Label; \
        return (Value); \
    Label:

#define stop() \
    end: \
        prev->done = true; \
        return impl.garbage; \
}

static inline Iterator begin()
{
    return (Iterator){ .done = false, .label = NULL };
}
