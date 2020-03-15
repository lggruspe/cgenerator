#include "generator2.h"
#include <assert.h>
#include <stdio.h>

int odd(Iterator *it)
{
    restore(it, resume);
    static int i;
    i = 1;
    for (;;) {
        return yield(it, "resume"), i;
        checkpoint(resume);
        i += 2;
    }
}

int even(Iterator *it)
{
    restore(it, resume);
    static int i;
    i = 0;
    for (;;) {
        return yield(it, "resume"), i;
        checkpoint(resume);
        i += 2;
    }
}

int integer(Iterator *it)
{
    restore(it, even);
    restore(it, odd);
    static Iterator a, b;
    a = ready_iterator();
    b = ready_iterator();
    for (;;) {
        return yield(it, "odd"), even(&a);
        checkpoint(odd);
        return yield(it, "even"), odd(&b);
        checkpoint(even);
    }
}

char hello(Iterator *it)
{
    restore_inactive(it, lc);
    restore(it, l1);
    restore(it, l2);
    restore(it, l3);
    restore(it, l4);
    restore(it, l5);
    restore(it, l6);
    restore(it, l7);
    restore(it, l8);
    restore(it, l9);
    restore(it, l0);
    restore(it, la);
    restore(it, lb);
    restore(it, lc);
    return yield(it, "l1"), 'h';
l1: return yield(it, "l2"), 'e';
l2: return yield(it, "l3"), 'l';
l3: return yield(it, "l4"), 'l';
l4: return yield(it, "l5"), 'o';
l5: return yield(it, "l6"), ',';
l6: return yield(it, "l7"), ' ';
l7: return yield(it, "l8"), 'w';
l8: return yield(it, "l9"), 'o';
l9: return yield(it, "l0"), 'r';
l0: return yield(it, "la"), 'l';
la: return yield(it, "lb"), 'd';
lb: return yield(it, "lc"), '!';
lc: return yield(it, NULL), '\n';
}

void *none(Iterator *it)
{
    restore_inactive(it, done);
    restore(it, resume);
    static int i;
    for (i = 0; i < 10; ++i) {
        return yield(it, "resume"), NULL;
        checkpoint(resume);
    }
    checkpoint(done);
    return yield(it, NULL), NULL;
}

int repeat(Iterator *it, int val)
{
    restore(it, resume);
    for (;;) {
        return yield(it, "resume"), val;
        checkpoint(resume);
    }
}

int repeat42(Iterator *it)
{
    restore(it, resume);
    static Iterator jt;
    jt = ready_iterator();
    for (;;) {
        return yield(it, "resume"), repeat(&jt, 42);
        checkpoint(resume);
    }
}

void test_hello()
{
    char helloworld[] = "hello, world!\n";
    int i = 0;
    Iterator it = ready_iterator();
    for (char c = hello(&it); it.active; c = hello(&it)) {
        assert(c == helloworld[i]);
        ++i;
    }
}

void test_integers()
{
    int N = 20;
    Iterator it = ready_iterator();
    for (int i = 0; i < N; ++i) {
        int n = integer(&it);
        assert(i == n);
    }
}

void test_yield_none()
{
    int count = 0;
    Iterator it = ready_iterator();
    none(&it);
    while (it.active) {
        ++count;
        none(&it);
    }
    assert(count == 10);
}

void test_parameterized()
{
    Iterator it = ready_iterator();
    for (int i = 0; i < 10; ++i) {
        assert(it.active);
        int val = repeat42(&it);
        assert(val == 42);
    }
}

int main()
{
    test_hello();
    test_integers();
    test_yield_none();
    test_parameterized();
    printf("Test passed\n");
}
