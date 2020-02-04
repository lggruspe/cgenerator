#include "generator.h"
#include <assert.h>
#include <stdio.h>

Generator(int, odd)
{
    static int i;
    i = 1;
    for (;;) {
        yield(i);
        i += 2;
    }
    stop();
}

Generator(int, even)
{
    static int i;
    i = 0;
    for (;;) {
        yield(i);
        i += 2;
    }
    stop();
}

Generator(int, integer)
{
    static Iterator it, jt;
    it = begin();   // odd
    jt = begin();   // even
    for (;;) {
        yield(even(&it));
        yield(odd(&jt));
    }
    stop();
}

Generator(char, hello)
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
    stop();
}

Generator(void*, none)
{
    static int i;
    for (i = 0; i < 10; ++i) {
        yield(NULL);
    }
    stop();
}

Generator(int, repeat, int val)
{
    for (;;) {
        yield(val);
    }
    stop();
}

Generator(int, repeat42)
{
    static Iterator it;
    it = begin();
    for (;;) {
        yield(repeat(&it, 42));
    }
    stop();
}

void test_hello()
{
    char helloworld[] = "hello, world!\n";
    int i = 0;
    Iterator it = begin();
    for (char c = hello(&it); !it.done; c = hello(&it)) {
        assert(c == helloworld[i]);
        ++i;
    }
}

void test_integers()
{
    int N = 20;
    Iterator it = begin();
    for (int i = 0; i < N; ++i) {
        int n = integer(&it);
        assert(i == n);
    }
}

void test_yield_none()
{
    int count = 0;
    Iterator it = begin();
    none(&it);
    while (!it.done) {
        ++count;
        none(&it);
    }
    assert(count == 10);
}

void test_parameterized()
{
    Iterator it = begin();
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
