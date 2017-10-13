pub fn UsePanic(gift: Option<&str>) {

    match gift {
        Some("snake") => println!("this is a snake"),
        Some(s) => println!("this is a {}", s),
        None => println!("None"),
    }
}

pub fn UseOption() {
    let food = Some("chicken");
    let snake = Some("snake");
    let void = None;

    UsePanic(food);
    UsePanic(snake);
    UsePanic(void);
}

pub fn UseResult() {
    // let num = "2".parse::<i32>().unwrap();
    let num = "t".parse::<i32>().unwrap();
    println!("num is {}", num);
}
