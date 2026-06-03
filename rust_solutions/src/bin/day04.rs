use rust_solutions::day04;
use std::path::Path;

fn main() {
    let filepath = "../input/test04.txt";
    println!("{:?}", Path::new(filepath).canonicalize());

    let grid: day04::Grid = day04::read_input(filepath);
    // let result1 = day03::total_jolts(data.clone(), 2);
    // println!("Maximum integer of length 2: {}", result1);
}
