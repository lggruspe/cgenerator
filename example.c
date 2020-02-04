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

int main()
{
    test_hello();
    test_integers();
    printf("Test passed\n");
}
