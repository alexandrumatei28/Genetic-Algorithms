# Genetic Algorithm Optimization

## Overview
This project implements a genetic algorithm in C++ to optimize a quadratic function of the form `f(x) = ax² + bx + c` within a specified domain. The algorithm uses binary chromosome representation, selection, crossover, mutation, and elitism to evolve a population over multiple generations, aiming to maximize the function's value. Input parameters are read from a file, and the program outputs the evolution of the population, including the best solutions and average fitness per generation.

## Features
- **Input Handling**: Reads parameters from `date.in` (e.g., number of chromosomes, domain `[c1, c2]`, function coefficients `a`, `b`, `c`, precision, crossover/mutation probabilities, generations).
- **Chromosome Encoding**: Converts real numbers to binary strings using a precision-based discretization formula, with length `l` calculated as `ceil(log2((c2-c1)*10^precizia))`.
- **Genetic Operations**:
  - **Selection**: Uses roulette wheel selection based on fitness probabilities.
  - **Crossover**: Performs two-point crossover with a specified probability (`probIncrucisare`), swapping bits at a random point.
  - **Mutation**: Applies bit-flip mutation with a given probability (`probMutatie`) per gene.
  - **Elitism**: Replaces the weakest chromosome with the best one in each generation.
- **Fitness Calculation**: Evaluates `f(x) = ax² + bx + c` for each chromosome’s decoded `x` value.
- **Output**: Displays initial population, steps for the first generation (selection, crossover, mutation), and evolution metrics (best `x`, maximum fitness, average fitness) for all generations.

## Technologies Used
- **C++**: Core language for implementation, leveraging STL (`vector`, `iostream`, `fstream`, etc.).
- **Random Number Generation**: Uses `srand` and `rand` seeded with `time` for stochastic operations.
- **File I/O**: Reads configuration from `date.in` using `ifstream`.

## Purpose
This project was developed to explore genetic algorithms as an optimization technique, focusing on maximizing a quadratic function. It demonstrates key concepts like binary encoding, population evolution, and stochastic operations, providing a practical introduction to evolutionary computing in C++.

## Notes
- The algorithm assumes `date.in` is correctly formatted; missing or invalid data may cause runtime errors.
- Output for intermediate steps (selection, crossover, mutation) is detailed only for the first generation to avoid clutter; evolution metrics are shown for all generations.
- The quadratic function `f(x) = ax² + bx + c` can yield negative values depending on `a`, `b`, `c`, affecting selection probabilities (fitness is not normalized to positive values).
