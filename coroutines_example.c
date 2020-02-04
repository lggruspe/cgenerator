#include "generator.h"
#include <stdio.h>
#include <unistd.h>

typedef void* Coroutine(Iterator*);

Coroutine pong;

Generator(void *, ping)
{
    for (;;) {
        printf("ping\n");
        sleep(1);
        yield(pong);
    }
    stop();
}

Generator(void *, pong)
{
    for (;;) {
        printf("pong\n");
        sleep(1);
        yield(ping);
    }
    stop();
}

void run_coroutine(Coroutine coroutine)
{
    Iterator it = begin();
    while (!it.done) {
        coroutine = coroutine(&it);
    }
}

int main()
{
    run_coroutine(ping);
}
