use std;

macro_rules! create_function {
    // 此宏接受一个 `ident` 指示符参数，并创建一个名为 `$func_name`
    // 的函数。
    // `ident` 指示符用于变量名或函数名
    ($func_name:ident) => (
        fn $func_name() {
            // `stringify!` 宏把 `ident` 转换成字符串。
            println!("You called {:?}()",
                     stringify!($func_name))
        }
    )
}


// 借助上述宏来创建名为 `foo` 和 `bar` 的函数。
create_function!(foo);
create_function!(bar);

macro_rules! print_result {
    // 此宏接受一个 `expr` 类型的表达式，将它转换成一个字符串，
    // 并伴随着表达式的结果。
    // `expr` 指示符用于表达式。
    ($expression:expr) => (
        // `stringify!` 把表达式转换成一个字符串，正如 stringify
        // （意思为“字符串化”） 所表达的意思那样。
        println!("{:?} = {:?}",
                 stringify!($expression),
                 $expression)
    )
}

// `min!` 将求出任意数量的参数的最小值。
macro_rules! find_min {
    // 基本情形：
    ($x:expr) => ($x);
    // `$x` 后面跟着至少一个 `$y,`
    ($x:expr, $($y:expr),+) => (
        // 对尾部的 `$y` 调用 `find_min!` 
        std::cmp::min($x, find_min!($($y),+))
    )
}


pub fn example() {

    foo();
    bar();

    print_result!(1u32 + 1);

    // 回想一下，代码块也是表达式！
    print_result!({
        let x = 1u32;

        x * x + 2 * x - 1
    });

    {
        println!("{}", find_min!(1u32));
        println!("{}", find_min!(1u32 + 2, 2u32));
        println!("{}", find_min!(5u32, 2u32 * 3, 4u32));
        println!("{}", find_min!(5u32, 2u32 * 3, 4u32));
        println!("{}", find_min!(5u32, 2u32 * 3, 4u32));
        println!("{}", find_min!(5u32, 2u32 * 3, 4u32));
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test() {
        example();
    }
}
