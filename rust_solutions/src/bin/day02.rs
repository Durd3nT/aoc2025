use rust_solutions::day02;
use std::path::Path;

fn main() {
    let filepath = "../input/test02.txt";
    println!("{:?}", Path::new(filepath).canonicalize());
    
    let data = day02::read_input(filepath);

    // cannot pass by reference if we want to interface with Python.
    // Hence need to clone data to reuse it again below
    let result1 = day02::find_repeated_patterns(data.clone(), 2);
    println!("Sum of IDs with only double repeated patterns: {}", result1);

    let result2 = day02::find_repeated_patterns(data, -1);
    println!("Sum of IDs with any repeated patterns: {}", result2);
}