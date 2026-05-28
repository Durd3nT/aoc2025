use pyo3::prelude::*;
use std::fs::File;
use std::io::{BufRead, BufReader};

#[pyfunction]
pub fn read_input(filepath: &str) -> Vec<i32> {
    let file = File::open(filepath).expect("could not open file");
    let reader = BufReader::new(file);

    let mut data: Vec<i32> = Vec::new();

    for line in reader.lines() {
        match line {
            Ok(val) => {
                let dir = &val[0..1];
                let num: i32 = val[1..].parse().expect("could not parse number");

                if dir == "R" {
                    data.push(num);
                } else if dir == "L" {
                    data.push(-num);
                }
            }
            Err(e) => {
                println!("Error reading line: {}", e);
            }
        }
    }

    data
}

#[pyfunction]
pub fn count_zeros(clicks: Vec<i32>) -> (usize, usize) {
    let mut dial = 50;
    let mut zero_cnt = 0;
    let mut zero_passed_cnt = 0;

    for c in clicks {
        let new_dial = (dial + c).rem_euclid(100); // true modulo (for negative numbers)
        let full_rotations = (c.abs() / 100) as usize;
        zero_passed_cnt += full_rotations;

        if ((new_dial > dial && c < 0) || (new_dial < dial && c > 0)) && new_dial != 0 && dial != 0
        {
            zero_passed_cnt += 1;
        }

        dial = new_dial;
        if dial == 0 {
            zero_cnt += 1;
        }
    }

    (zero_cnt, zero_passed_cnt)
}
