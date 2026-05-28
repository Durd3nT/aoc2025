use pyo3::prelude::*;
use std::fs::File;
use std::io::{BufRead, BufReader};

/// Precomputed powers of 10 for efficient digit extraction
const POW10: [i64; 19] = [
    1,
    10,
    100,
    1_000,
    10_000,
    100_000,
    1_000_000,
    10_000_000,
    100_000_000,
    1_000_000_000,
    10_000_000_000,
    100_000_000_000,
    1_000_000_000_000,
    10_000_000_000_000,
    100_000_000_000_000,
    1_000_000_000_000_000,
    10_000_000_000_000_000,
    100_000_000_000_000_000,
    1_000_000_000_000_000_000,
];

/// Reads the input file and returns a vector of [start, end] pairs of ID ranges.
///
/// @param filepath: path to the input file containing ID ranges in the format
///     "start-end,start-end,..."
///
/// @return a vector of [start, end] pairs of ID ranges
#[pyfunction]
pub fn read_input(filepath: &str) -> Vec<Vec<i64>> {
    let file = File::open(filepath).expect("could not open file");
    let reader = BufReader::new(file);

    let mut data: Vec<Vec<i64>> = Vec::new();

    for line in reader.lines() {
        match line {
            Ok(val) => {
                for r in val.split(',') {
                    let mut parts = r.split('-'); // split() returns an iterator, use next() to get elements
                    let start: i64 = parts.next().unwrap().parse().unwrap();
                    let end: i64 = parts.next().unwrap().parse().unwrap();
                    data.push(vec![start, end]);
                }
            }
            Err(e) => {
                println!("Error reading line: {}", e);
            }
        }
    }

    data
}

/// Counts the number of digits in the given integer.
///
/// @param number: the integer to count digits of
///
/// @return the number of digits in the integer
#[pyfunction]
pub fn digit_count(mut number: i64) -> i32 {
    let mut count = 0;
    while number > 0 {
        number /= 10;
        count += 1;
    }
    count
}

/// Checks if the given number has a repeated pattern of digits with up to max_repeats repeats.
/// For example, 123123 has a repeated pattern of "123" repeated twice.
///
/// @param number: the number to check for repeated patterns
/// @param max_repeats: maximum number of repeats to check for (e.g., 2 for patterns repeated twice)
///     for negative values (-1), check for any patterns
///
/// @return true if the number has a repeated pattern, false otherwise
#[pyfunction]
pub fn is_repeated_pattern(number: i64, max_repeats: i32) -> bool {
    let len = digit_count(number);
    let num_repeats = if max_repeats > len || max_repeats < 0 {
        len
    } else {
        max_repeats
    };

    for k in 2..=num_repeats {
        if len % k != 0 {
            continue;
        }

        let block_len = len / k;
        let block = number / POW10[(len - block_len) as usize];
        let block_pow = POW10[block_len as usize];

        let mut rebuilt_number = 0;
        for _ in 0..k {
            rebuilt_number = rebuilt_number * block_pow + block;
        }

        if rebuilt_number == number {
            return true;
        }
    }

    false
}

/// Returns the sum of IDs within ranges that have repeated patterns
/// with max_repeats setting the maximum number of repeats to check for.
///
/// Note: cannot pass by reference if we want to interface with Python.
///
/// @param ranges: list of [start, end] pairs of ID ranges to check
/// @param max_repeats: maximum number of repeats to check for (e.g., 2 for patterns repeated twice)
///     for negative values (-1), check for any patterns
///
/// @return sum of IDs that have repeated patterns
#[pyfunction]
pub fn find_repeated_patterns(ranges: Vec<Vec<i64>>, max_repeats: i32) -> i64 {
    let mut tot_sum = 0;
    for range in ranges {
        for number in range[0]..=range[1] {
            if is_repeated_pattern(number, max_repeats) {
                tot_sum += number;
            }
        }
    }
    tot_sum
}
