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

    if s.is_empty() || len_s < len_max_int {
        println!(
            "integer string s is empty or len_max_int ({}) larger than s ({})",
            len_max_int, len_s
        );
        return 0;
    }

    let digits_vec: Vec<char> = s.chars().collect();

    let mut max_digits: Vec<char> = vec!['0'; len_max_int];
    let mut max_idx: Vec<usize> = vec![0; len_max_int];

    for k in 0..len_max_int {
        let start: usize = if k == 0 { 0 } else { max_idx[k - 1] + 1 };

        for i in start..(len_s - len_max_int + k + 1) {
            if digits_vec[i] > max_digits[k] {
                max_digits[k] = digits_vec[i];
                max_idx[k] = i;
            }
        }
    }

    // fold() collects elements from iter() based on an initial value and a lambda for combining elements
    let max_int: i64 = max_digits
        .iter()
        .fold(0i64, |tot, &c| tot * 10 + (c as i64 - '0' as i64));

    max_int
}

#[pyfunction]
pub fn total_jolts(data: Vec<String>, len_max_int: usize) -> i64 {
    if len_max_int > 18 {
        println!("len_max_int too large for return type i64");
        return 0;
    }

    let jolts: i64 = data
        .iter()
        .map(|s| max_digit_from_string(s, len_max_int))
        .sum();

    jolts
}
