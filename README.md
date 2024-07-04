# 42 Philosophers Project

## Overview
Philosophers project is an implementation of the classic Dining Philosophers problem in computer science. This project aims to demonstrate solutions to problems of concurrency, synchronization, and resource sharing among processes or threads, specifically focusing on avoiding deadlocks and ensuring fair access to resources.

## Problem Statement
The Dining Philosophers problem involves a scenario where a certain number of philosophers are sitting around a circular table with one fork between each pair. A philosopher can only eat when they have both the fork to their left and the fork to their right. The challenge is to design a simulation that allows all philosophers to eat without getting into a deadlock (where everyone is holding one fork and waiting indefinitely for the other) or starving any philosopher (not getting enough chance to eat).

## Implementation
This project is implemented in C and uses POSIX threads (pthreads) and mutexes for synchronization. The key features include:

- **Philosophers as Threads**: Each philosopher is represented by a thread that performs cycles of eating, thinking, and sleeping.
- **Mutexes for Forks**: Each fork is protected by a mutex to ensure that only one philosopher can hold it at a time.
- **Deadlock Avoidance**: Implements strategies to avoid deadlock, ensuring that all philosophers can eventually eat.
- **Starvation Prevention**: Ensures that no philosopher will starve by implementing fairness in acquiring forks.

## Getting Started

### Prerequisites
- GCC compiler
- POSIX threads library (usually included in standard Linux distributions)

### Compilation
Compile the project using the following command:
  - make
   Or use : gcc -Wall -Wextra -Werror -pthread *.c -o philosophers


### HOW TO USE
 ./philo (number of philosophers) (time to die in ms) (time to eat in ms) (time to think in ms) (optional argument: number of times to eat)
