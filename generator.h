#pragma once
#include <stdbool.h>

#define CONCAT_IMPL(x, y) x##y
#define CONCAT(x, y) CONCAT_IMPL(x, y)

#define Iter(Name) struct Name##_iter

#define Generator(Type, Name) \
Iter(Name) { \
    void *label; \
    Type value; \
    bool done; \
}; \
 \
Iter(Name) Name##_impl(Iter(Name) prev) \
{ \
    Iter(Name) next = {.done = false}; \
    if (prev.done) { \
        goto end; \
    } \
    if (prev.label) { \
        goto *(prev.label); \
    }

#define yield(Value) \
        next.value = (Value); \
        set_yield_label(CONCAT(l, __COUNTER__))

#define set_yield_label(Label) \
        next.label = &&Label; \
        return next; \
    Label:

#define stop() \
    end: \
        next.done = true; \
        return next; \
}

#define begin(Name) (Name##_impl)((Iter(Name)){ .done = false, .label = NULL })

#define next(Name, Iterator) (Name##_impl)(Iterator)
