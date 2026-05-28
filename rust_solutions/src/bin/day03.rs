use rust_solutions::day03;
use std::path::Path;

fn main() {
    let filepath = "../input/test03.txt";
    println!("{:?}", Path::new(filepath).canonicalize());
    
    let data = day03::read_input(filepath);
    let result = day03::max_digit_from_string(&data[0], 2);
    println!("Maximum integer of length 2: {}", result);

    // let result1 = day03::find_repeated_patterns(data.clone(), 2);
    // println!("Sum of IDs with only double repeated patterns: {}", result1);
}

