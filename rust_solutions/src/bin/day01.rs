use rust_solutions::day01;
use std::path::Path;

fn main() {
    let filepath = "../input/input01.txt";
    println!("{:?}", Path::new(filepath).canonicalize());
    
    let data = day01::read_input(filepath);

    let (zero_cnt, zero_passed_cnt) = day01::count_zeros(&data);

    println!("Dial landed on / passed zero: {} / {}", zero_cnt, zero_passed_cnt);
    println!("Total: {}", zero_cnt + zero_passed_cnt);
}