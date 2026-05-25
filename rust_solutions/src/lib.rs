use pyo3::prelude::*;

pub mod day01;
pub mod day02;

#[pymodule]
fn rust_solutions(m: &Bound<'_, PyModule>) -> PyResult<()> {
    // day01 module
    let day01_module = PyModule::new(m.py(), "day01")?;
    
    day01_module.add_function(wrap_pyfunction!(day01::read_input, &day01_module)?)?;
    day01_module.add_function(wrap_pyfunction!(day01::count_zeros, &day01_module)?)?;
    
    m.add_submodule(&day01_module)?;

    // day02 module
    let day02_module = PyModule::new(m.py(), "day02")?;
    
    day02_module.add_function(wrap_pyfunction!(day02::read_input, &day02_module)?)?;
    day02_module.add_function(wrap_pyfunction!(day02::digit_count, &day02_module)?)?;
    day02_module.add_function(wrap_pyfunction!(day02::is_repeated_pattern, &day02_module)?)?;
    day02_module.add_function(wrap_pyfunction!(day02::find_repeated_patterns, &day02_module)?)?;

    m.add_submodule(&day02_module)?;

    //
    Ok(())
}
