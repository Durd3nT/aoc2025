use rust_solutions::day07;
use std::path::Path;

fn main() {
    let filepath = "../input/test07.txt";
    println!("{:?}", Path::new(filepath).canonicalize());

    let grid: day07::Grid = day07::read_input(filepath);
    let (num_beam_splits, num_timelines) = day07::count_beam_splits(grid.clone());
    println!("Number of total beam splits {}", num_beam_splits);
    println!("Number of total beam splits {}", num_timelines);
}
