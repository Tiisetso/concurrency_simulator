# Concurrency Simulator
A small implementation of the Dining Philosophers problem using POSIX threads. The program simulates philosophers taking forks (mutexes), eating, sleeping, and thinking while avoiding deadlocks and ensuring proper cleanup.

## Description
Each philosopher runs in its own thread and needs two forks to eat. The program manages deadlocks and data races by systematically locking and unlocking mutexes where required.

## AI Declaration
ChatGPT and Gemini were used to:
- search comprehensively for resources.
- review minor syntax challenges.
- assist creation of the bash test script.
- assist in creation of README.md

## Requirements
- Linux (POSIX)
- GCC or clang
- make
- pthreads
- Optional: `valgrind` for memory checks, `helgrind` tool for data race checks.

## Build
```bash
make        # builds ./philo
make clean  # removes object files
make fclean # removes binary as well
make re     # recompiles
```

## Usage
```
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```
- `number_of_philosophers` — positive integer
- `time_to_die` — milliseconds before a philosopher dies if not eating
- `time_to_eat` — milliseconds spent eating
- `time_to_sleep` — milliseconds spent sleeping
- Optional: `number_of_times_each_philosopher_must_eat` — program exits once each philosopher has eaten at least that many times

### Example
```bash
./philo 5 800 200 200
./philo 4 410 200 200 7
```

## Notes
- Output events are timestamped and synchronized: `has taken a fork`, `is eating`, `is sleeping`, `is thinking`, `died`.
- Single-philosopher edge case is handled (one philosopher picks a fork and may die if unable to eat).
- Ensure `printf`/logging is synchronized to avoid interleaved lines.

## Tests & Debugging
### Run edge cases
  - `./philo 200 130 60 60` Philosophers should survive
  - `./philo 10 100 2000 100` Philosophers should die and end quickly

### Automated tester (philotest.sh)
A helper script `philotest.sh` runs multiple scenarios automatically and categorizes them into "SHOULD LIVE" and "SHOULD DIE". Usage:
```bash
# run each test 3 times (repeat count) and append servings=5
./philotest.sh 3 5

# run in infinite mode (no servings) - you'll be prompted for duration
./philotest.sh 1
```
The script logs to `test_output.log` and prints a summary for each run.

### Memory checking example:
```bash
valgrind --leak-check=full --show-leak-kinds=all ./philo 5 800 200 200
```
### Data race checking example:
```bash
valgrind --tool=helgrind ./philo 5 800 200 200
```

## Project Structure
```
philo/
├── Makefile
├── philo                # binary (after build)
├── include/
│   └── philo.h
├── src/
│   ├── philo.c
│   ├── routine.c
│   ├── time.c
│   └── ...
└── obj/
```