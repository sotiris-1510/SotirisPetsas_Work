# ConcurrencyMonitors

Two C exercises implementing classic synchronization problems with POSIX threads (`pthread`) and monitor-style condition variables.

## ex1 — Restaurant queue (producer/consumer)

Simulates a single server (employee) handling a queue of arriving customers.

- Each customer is a thread that `enter()`s a shared queue and waits its turn.
- The server thread repeatedly calls `service()`, which blocks (via a condition variable) until a customer is waiting, then serves them in FIFO order.
- The queue has a fixed capacity (`MAX_CAPACITY`); a full queue rejects new customers.
- Synchronization is handled with one mutex, a condition variable for the server, and a per-customer condition variable array so each customer wakes only when it's their turn.

**Run:**
```bash
./ex1/ex1 <number_of_customers>
```

## ex2 — Eaters and fillers

A bounded-buffer style problem: some threads ("fillers") prepare plates, others ("eaters") consume them, sharing a plate count capped at 5.

- Each thread is randomly assigned as an eater (10% chance) or a filler (90% chance).
- Fillers block while the plate count is at capacity; eaters block while there are no plates ready.
- Threads give up gracefully (rather than deadlocking) if there's no one left on the other side to make progress — e.g. an eater exits if all fillers are done and no plates remain.

**Run:**
```bash
./ex2/ex2 <number_of_people>
```

## Building

A `Makefile` is included:

```bash
make        # builds ex1/ex1 and ex2/ex2
make clean  # removes the built binaries
```

Or compile each manually:
```bash
gcc -pthread -Wall -o ex1/ex1 ex1/ex1.c
gcc -pthread -Wall -o ex2/ex2 ex2/ex2.c
```

Note: each `.c` file `#include`s its corresponding `_monitor.c` directly rather than linking against it separately, so only the top-level `ex1.c` / `ex2.c` need to be compiled — the header files are kept for documentation/interface reference.
