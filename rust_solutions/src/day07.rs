use pyo3::prelude::*;
use std::fs::File;
use std::io::{BufRead, BufReader};

#[derive(Clone)]
pub struct Grid {
    splitter_coords: Vec<(usize, Vec<usize>)>,
    init_beam: usize,
    xdim: usize,
    ydim: usize,
}

/// Reads the input file and returns a vector of strings of long integers.
///
/// @param filepath: path to the input file containing long integers, one per line
///
/// @return an instance of Grid
pub fn read_input(filepath: &str) -> Grid {
    let file = File::open(filepath).expect("could not open file");
    let reader = BufReader::new(file);

    let mut splitter_coords: Vec<(usize, Vec<usize>)> = Vec::new();
    let mut init_beam: usize = 0;
    let mut xdim: usize = 0;
    let mut ydim: usize = 0;

    for (y, line) in reader.lines().enumerate() {
        let val = line.expect("Error reading line");

        if y == 0 {
            init_beam = val.find('S').expect("No char 'S' in first line");
            xdim = val.len();
        } else {
            let x_coords: Vec<usize> = val
                .char_indices()
                .filter_map(|(i, c)| (c == '^').then_some(i))
                .collect();

            // only store coords of splitters if there are any.
            // Don't store empty vecs for rows without splitters
            if !x_coords.is_empty() {
                splitter_coords.push((y, x_coords));
            }
        }
        ydim += 1;
    }

    Grid {
        splitter_coords,
        init_beam,
        xdim,
        ydim,
    }
}

// For part 1: Could also come the other way around and loop through all x-coords of previous beam
// (initialized with the first entering beam) and then check if the x-coords are in the
// next row of beam splitter coords

// For part 2: Use dynamic programming to count how many possible paths the initial beam
// could take through all splitters (see example below)
pub fn count_beam_splits(grid_data: Grid) -> (usize, usize) {
    let mut cnt: usize = 0;
    let xdim = grid_data.xdim;

    let mut beam_x_coords: Vec<bool> = vec![false; xdim];
    beam_x_coords[grid_data.init_beam] = true;

    // DP array to keep track of possible beam paths. initially there is one beam
    let mut dp_timelines: Vec<usize> = vec![0; xdim];
    dp_timelines[grid_data.init_beam] = 1;

    for (_y, x_coords) in &grid_data.splitter_coords {
        for &x in x_coords {
            if x > 0 && x < xdim - 1 && beam_x_coords[x] {
                // x - 1 < 0 not possible due to type usize
                beam_x_coords[x - 1] = true;
                beam_x_coords[x + 1] = true;
                beam_x_coords[x] = false;

                let dp_val = dp_timelines[x];
                dp_timelines[x-1] += dp_val;
                dp_timelines[x+1] += dp_val;
                dp_timelines[x] = 0;

                cnt += 1;
            }
        }
    }

    (cnt, dp_timelines.iter().sum())
}



// Example DP for counting possible all beam paths:
// .......S.......
// .......|.......
// ......1^1......
// ......|.|......
// .....1^2^2.....
// .....|.|.|.....
// ....1^3^3^1....
// ....|.|.|.|....
// ...1^4^331^1...
// ...|.|.|||.|...
// ..1^5^434^2^1..
// ..|.|.|||.|.|..
// .1^154^74.21^1.
// .|.|||.||.||.|.
// 1^2^a^b^b^211^1  a = 10, b = 11
// |.|.|.|.|.|||.|
// 
// Total: 1 + 2 + 10 + 11 + 11 + 2 + 1 + 1 + 1 = 40
