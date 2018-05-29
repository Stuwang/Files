use std::result::Result;

fn return_result(i: i32) -> Result<i32, &'static str> {
    match i {
        0 => Ok(1),
        _ => Err("error"),
    }
}

fn wrap_result_calls() -> Result<(), &'static str> {
    let re = return_result(1)?;
    println!("{:?}", re);
    Ok(())
}

pub fn use_result() {
    let re = wrap_result_calls();
    println!("{:?}", re);
}
