use std::boxed::Box;

// #[test]
pub fn test() {
    let v = vec![1, 2, 3, 4];

    let nums = (1..100).collect::<Vec<i32>>();

    for num in nums.iter() {
        println!("{}", num);
    }
}
