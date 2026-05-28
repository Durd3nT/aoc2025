use pyo3::prelude::*;
use std::fs::File;
use std::io::{BufRead, BufReader};

/// Reads the input file and returns a vector of strings of long integers.
///
/// @param filepath: path to the input file containing long integers, one per line
///
/// @return a vector of strings of long integers
#[pyfunction]
pub fn read_input(filepath: &str) -> Vec<String> {
    let file = File::open(filepath).expect("could not open file");
    let reader = BufReader::new(file);

    let mut data: Vec<String> = Vec::new();

    for line in reader.lines() {
        match line {
            Ok(val) => {
                data.push(val);
            }
            Err(e) => {
                println!("Error reading line: {}", e);
            }
        }
    }

    data
}

/// Finds the maximum integer of length `len_max_int` in the given string s of digits.
/// Importantly, digits within s cannot be rearranged to form max_int, but do not have
/// to be consecutive in s.
///
/// @param s: the string of digits to search through
/// @param len_max_int: length of max_int
///
/// @return the maximum integer of length `len_max_int` that can be formed from digits in s
#[pyfunction]
pub fn max_digit_from_string(s: &str, len_max_int: usize) -> i64 {
    let len_s = s.len();

    let mut max_digit: i64 = 0;

    max_digit
}
