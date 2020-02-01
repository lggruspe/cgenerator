#include "generator.h"
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
    static Iter(odd) it;
    static Iter(even) jt;
    it = begin(odd);
    jt = begin(even);
    for (;;) {
        yield(jt.value);
        jt = next(even, jt);
        yield(it.value);
        it = next(odd, it);
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

int main()
{
    for (Iter(hello) it = begin(hello); !it.done; it = next(hello, it)) {
        printf("%c", it.value);
    }

    int N = 20;
    Iter(integer) it = begin(integer);
    for (int i = 0; i < N; ++i) {
        printf("%d\n", it.value);
        it = next(integer, it);
    }
}
