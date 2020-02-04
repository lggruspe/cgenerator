#include "generator.h"
#include <stdio.h>
#include <unistd.h>

typedef void* Coroutine(Iterator*);

Coroutine pong;

GENERATOR(void *, ping)
{
    for (;;) {
        printf("ping\n");
        sleep(1);
        yield(pong);
    }
    stop_generator();
}

GENERATOR(void *, pong)
{
    for (;;) {
        printf("pong\n");
        sleep(1);
        yield(ping);
    }
    stop_generator();
}

void run_coroutine(Coroutine coroutine)
{
    Iterator it = create_iterator();
    while (!it.done) {
        coroutine = coroutine(&it);
    }
}

int main()
{
    run_coroutine(ping);
}
