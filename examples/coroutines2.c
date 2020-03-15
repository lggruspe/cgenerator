#include "generator2.h"
#include <stdio.h>
#include <unistd.h>

typedef void* Coroutine(Iterator*);

Coroutine ping, pong;

void *ping(Iterator *it)
{
    restore(it, resume);
    for (;;) {
        printf("ping\n");
        sleep(1);
        return yield(it, "resume"), pong;
        checkpoint(resume);
    }
}

void *pong(Iterator *it)
{
    restore(it, resume);
    for (;;) {
        printf("pong\n");
        sleep(1);
        return yield(it, "resume"), ping;
        checkpoint(resume);
    }
}

void run_coroutine(Coroutine coroutine)
{
    Iterator it = ready_iterator();    // ping
    Iterator jt = ready_iterator();    // pong
    while (it.active) {
        coroutine = coroutine == ping
            ? coroutine(&it)
            : coroutine(&jt);
    }
}

int main()
{
    run_coroutine(ping);
}
