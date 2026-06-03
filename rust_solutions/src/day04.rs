use pyo3::prelude::*;
use std::fs::File;
use std::io::{BufRead, BufReader};

#[pyclass]
pub struct Grid {
    pub data: Vec<bool>,
    pub xlen: usize,
    pub ylen: usize,
}

/// Reads the input file and returns a vector of strings of long integers.
///
/// @param filepath: path to the input file containing long integers, one per line
///
/// @return a vector of strings of long integers
#[pyfunction]
pub fn read_input(filepath: &str) -> Grid {
    let file = File::open(filepath).expect("could not open file");
    let reader = BufReader::new(file);

    let mut data: Vec<bool> = Vec::new();
    let mut xlen: usize = 0;
    let mut ylen: usize = 0;

    for line in reader.lines() {
        match line {
            Ok(val) => {
                xlen = val.len();
                data.reserve(xlen * (ylen + 1));
                data.extend(val.bytes().map(|b| b == b'@'));
                ylen += 1;
            }
            Err(e) => {
                println!("Error reading line: {}", e);
            }
        }
    }

    Grid { data, xlen, ylen }
}

#[pyfunction]
pub fn find_remove_rolls(grid: &Grid) -> (i32, i32) {
    let mut roll_cnts: Vec<i32> = vec![0];

    let tot_roll_cnts: i32 = roll_cnts.iter().sum();

    (roll_cnts[0], tot_roll_cnts)
}
