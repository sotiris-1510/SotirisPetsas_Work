# HW3

Two Java concurrency exercises using threads, monitors, and semaphores.

## hw3ask1 — Clock ticks monitor

A shared clock implemented with `wait()`/`notifyAll()`, where multiple client threads sleep for a random number of "ticks" until a daemon thread advances the clock.

- `ClockMonitor` — interface for the shared clock (`tick()`, `sleepTicks(int)`)
- `ClockMonitorImpl` — synchronized implementation using an internal tick counter and `wait`/`notifyAll`
- `DaemonThread` — a daemon thread that calls `tick()` at a fixed interval
- `ClientThread` — repeatedly asks the monitor to sleep for a random number of ticks
- `ClockTicksMain` — starts one daemon thread and 10 client threads

**Run:**
```bash
java hw3ask1.ClockTicksMain
```

## hw3ask2 — Restaurant (cigarette-smokers-style problem)

A waiter repeatedly places two random ingredients on the table; each customer only needs the one ingredient they're missing, and grabs it (and finishes their dish) once it's available — a classic instance of the "cigarette smokers" synchronization problem, using semaphores instead of monitors.

- `WaiterThread` — picks two of three ingredients (PITA, KREAS, LAXANIKA) at random and signals whichever customer needs the third
- `CustomerThread` — waits on its own semaphore, "eats" once it can, then signals the waiter it's ready for more
- `RestaurantMain` — sets up the semaphores and starts one waiter and three customer threads

**Run:**
```bash
java hw3ask2.RestaurantMain
```

## Building

This started as an Eclipse project, organized as packages under `src/`. To compile and run from the command line:

```bash
javac -d bin src/hw3ask1/*.java src/hw3ask2/*.java
cd bin
java hw3ask1.ClockTicksMain
# or
java hw3ask2.RestaurantMain
```

Both programs run indefinitely (they loop forever) — stop them with Ctrl+C.
