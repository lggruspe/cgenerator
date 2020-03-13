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
    Iterator it = create_iterator();    // ping
    Iterator jt = create_iterator();    // pong
    while (!it.done) {
        coroutine = coroutine == ping
            ? coroutine(&it)
            : coroutine(&jt);
    }
}

int main()
{
    run_coroutine(ping);
}
