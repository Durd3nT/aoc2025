use rust_solutions::day07;
use std::path::Path;

fn main() {
    let filepath = "../input/input07.txt";
    println!("{:?}", Path::new(filepath).canonicalize());

    let grid: day07::Grid = day07::read_input(filepath);
    let beam_splits = day07::count_beam_splits(grid);
    println!("Number of total beam splits {}", beam_splits);
}
