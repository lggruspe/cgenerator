#include "generator.h"
#include <assert.h>
#include <stdio.h>

GENERATOR(int, odd)
{
    static int i;
    i = 1;
    for (;;) {
        yield(i);
        i += 2;
    }
    stop_generator();
}

GENERATOR(int, even)
{
    static int i;
    i = 0;
    for (;;) {
        yield(i);
        i += 2;
    }
    stop_generator();
}

GENERATOR(int, integer)
{
    static Iterator it, jt;
    it = create_iterator();   // odd
    jt = create_iterator();   // even
    for (;;) {
        yield(even(&it));
        yield(odd(&jt));
    }
    stop_generator();
}

GENERATOR(char, hello)
{
    yield('h');
    yield('e');
    yield('l');
    yield('l');
    yield('o');
    yield(',');
    yield(' ');
    yield('w');
    yield('o');
    yield('r');
    yield('l');
    yield('d');
    yield('!');
    yield('\n');
    stop_generator();
}

GENERATOR(void*, none)
{
    static int i;
    for (i = 0; i < 10; ++i) {
        yield(NULL);
    }
    stop_generator();
}

GENERATOR(int, repeat, int val)
{
    for (;;) {
        yield(val);
    }
    stop_generator();
}

GENERATOR(int, repeat42)
{
    static Iterator it;
    it = create_iterator();
    for (;;) {
        yield(repeat(&it, 42));
    }
    stop_generator();
}

void test_hello()
{
    char helloworld[] = "hello, world!\n";
    int i = 0;
    Iterator it = create_iterator();
    for (char c = hello(&it); !it.done; c = hello(&it)) {
        assert(c == helloworld[i]);
        ++i;
    }
}

void test_integers()
{
    int N = 20;
    Iterator it = create_iterator();
    for (int i = 0; i < N; ++i) {
        int n = integer(&it);
        assert(i == n);
    }
}

void test_yield_none()
{
    int count = 0;
    Iterator it = create_iterator();
    none(&it);
    while (!it.done) {
        ++count;
        none(&it);
    }
    assert(count == 10);
}

void test_parameterized()
{
    Iterator it = create_iterator();
    for (int i = 0; i < 10; ++i) {
        assert(!it.done);
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
