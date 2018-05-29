fn factory1() -> Box<Fn(i32) -> i32> {
    let num = 5;

    Box::new(move |x| x + num)
}

fn add_f(num: i32) -> i32 {
    return num + 1;
}

fn factory2() -> Box<Fn(i32) -> i32> {
    // let num = 5;
    return Box::new(add_f);
}

pub fn test1() {
    // let f = factory();
    println!("{}", factory1()(1));
    println!("{}", factory2()(1));
}

pub fn test2() {
    let a = vec![1, 2, 3, 4];
    let get = |i| return a[i];
    println!("{}", get(1));
    println!("{}", get(2));
    println!("{}", get(3));

    let mut vector = vec![1, 2, 3];
    // let mut closure = |x: usize| return vector.get_mut(x);
    println!("{}", "what the fuck!");
}
