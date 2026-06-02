use rust_solutions::day03;
use std::path::Path;

fn main() {
    let filepath = "../input/input03.txt";
    println!("{:?}", Path::new(filepath).canonicalize());

    let data = day03::read_input(filepath);
    let result1 = day03::total_jolts(data.clone(), 2);
    println!("Maximum integer of length 2: {}", result1);

    let result2 = day03::total_jolts(data, 12);
    println!("Maximum integer of length 2: {}", result2);
}
