use pyo3::prelude::*;

pub mod day01;

#[pymodule]
fn rust_solutions(m: &Bound<'_, PyModule>) -> PyResult<()> {
    let day01_module = PyModule::new(m.py(), "day01")?;

    day01_module.add_function(wrap_pyfunction!(day01::read_input, &day01_module)?)?;
    day01_module.add_function(wrap_pyfunction!(day01::count_zeros, &day01_module)?)?;

    m.add_submodule(&day01_module)?;

    Ok(())
}
