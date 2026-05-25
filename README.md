### Advent of Code 2025

My solutions to [Advent of Code 2025](https://adventofcode.com/2025) - in Rust, Python, and C++.
In some cases, the Python code is used to prototype and get a result simply by solving the puzzle, without too much code optimization.

#### Rust:
To compile and run all rust binaries, use `cargo run` from the root of `rust_solutions`. For individual binaries, run `cargo run --bin DAYXX` replacing `DAYXX` with, e.g., `day01`.

Tests for the Rust solutions are implemented in Python in order to keep tests concise. To test Rust files in Python `maturin` has to be installed via `pip`. After, first `cargo build`, then `maturin develop` to build the Rust-Python interface. Now, Python tests can be run normally (see below).

#### Python:
Run tests for each day's functions using `python -m unittest test_DAYXX.py` replacing `DAYXX` with, e.g., `day01`.

#### C++:
To compile and run, run `make` include the number of the day as a command line argument, e.g., `make run NUM="02"` for day 2.

**NOTE:** the input is user-/account-dependent.
