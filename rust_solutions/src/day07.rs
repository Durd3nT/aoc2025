use pyo3::prelude::*;
use std::collections::{HashMap, HashSet};
use std::fs::File;
use std::io::{BufRead, BufReader};

#[pyclass]
pub struct Grid {
    // OPTIONS: HashSet{(x, y)} or HashMap {y_coord: Vec[x_coords]}
    splitter_coords: HashMap<usize, Vec<usize>>,
    init_beam: usize,
    xdim: usize,
    ydim: usize,
}

/// Reads the input file and returns a vector of strings of long integers.
///
/// @param filepath: path to the input file containing long integers, one per line
///
/// @return an instance of Grid
#[pyfunction]
pub fn read_input(filepath: &str) -> Grid {
    let file = File::open(filepath).expect("could not open file");
    let reader = BufReader::new(file);

    let mut splitter_coords: HashMap<usize, Vec<usize>> = HashMap::new();
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
                splitter_coords.insert(y, x_coords);
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

// Could also come the other way around and loop through all x-coords of previous beam
// (initialized with the first entering beam) and then check if the x-coords are in the
// next row of beam splitter coords
pub fn count_beam_splits(grid_data: Grid) -> usize {
    let mut cnt: usize = 0;

    let mut prev_beam_x: HashSet<usize> = HashSet::new();
    let mut new_beam_x: HashSet<usize> = HashSet::new();

    prev_beam_x.insert(grid_data.init_beam);

    for y in 1..grid_data.ydim {
        let Some(x_coords) = grid_data.splitter_coords.get(&y) else {
            continue;
        };
        for &x in x_coords {
            if !(x == 0) && !(x == grid_data.xdim) && prev_beam_x.contains(&x) {
                // x - 1 < 0 not possible due to type usize
                new_beam_x.insert(x - 1);
                new_beam_x.insert(x + 1);
                prev_beam_x.remove(&x);
                cnt += 1;
            }
        }
        prev_beam_x.extend(&new_beam_x);
        new_beam_x.clear();
    }

    cnt
}
