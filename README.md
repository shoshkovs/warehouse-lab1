# Warehouse Lab 1

A C++17 object-oriented warehouse project.

## Features

- Three product categories and six concrete product classes.
- Validated `Price`, `Quantity`, and `Weight` value classes.
- Product factories and polymorphic cloning.
- Warehouse capacity limits, search, removal, and product transfer.
- Deep copying, move operations, and mutable/const iterators.
- Five demonstration scenarios and automated tests.

## Build and run

Requires CMake 3.16 or newer and a C++17 compiler.

```sh
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
./build/warehouse_demo
```

## Sanitizers

```sh
cmake -S . -B build-sanitize -DENABLE_SANITIZERS=ON
cmake --build build-sanitize
ctest --test-dir build-sanitize --output-on-failure
```

## Structure

- `include/`: class declarations.
- `src/`: implementations and demonstration entry point.
- `tests/`: class tests and logging checks.
- `docs/warehouse.puml`: UML source.
