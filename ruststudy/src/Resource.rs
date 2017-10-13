
struct Droppable {
    name: String,
}

// 这个简单的 `drop` 实现添加了打印到控制台的功能。
impl Drop for Droppable {
    fn drop(&mut self) {
        println!("> Dropping self.name is {}", self.name);
    }
}

impl Droppable {
    fn printName(&self) {
        println!("MyName is {}", self.name);
    }

    fn setName(&mut self, name: String) {
        self.name = name
    }

    fn setNameFromStr(&mut self, name: &'static str) {
        self.name = name.to_string()
    }
}

pub fn UseAutoDes() {
    // 在堆上分配一个整型数据
    let mut box1 = Box::new(Droppable { name: "a".to_string() });

    {
        let box2 = &mut box1;

        box2.printName();

        box2.setName("wangyuan".to_string());

        box2.printName();

        box2.setNameFromStr("fuck !");
    }

    box1.printName();

    let b3 = &box1;

    b3.printName();

    println!("===============");
    // `_box1` 在这里销毁，而且内存得到释放
}







pub mod refTest {


    #[derive(Clone, Copy)]
    struct Point {
        x: i32,
        y: i32,
    }

    fn main() {
        let c = 'Q';

        // 赋值语句中左边的 `ref` 关键字等价右边的 `&` 符号。
        let ref ref_c1 = c;
        let ref_c2 = &c;

        println!("ref_c1 equals ref_c2: {}", *ref_c1 == *ref_c2);

        let point = Point { x: 0, y: 0 };

        // 在解构一个结构体时 `ref` 同样有效。
        let _copy_of_x = {
            // `ref_to_x` 是一个指向 `point` 的 `x` 字段的引用。
            let Point {
                x: ref ref_to_x,
                y: _,
            } = point;

            // 返回一个 `point` 的 `x` 字段的拷贝。
            *ref_to_x
        };

        // `point` 的可变拷贝
        let mut mutable_point = point;

        {
            // `ref` 可以结合 `mut` 来接受可变引用。
            let Point {
                x: _,
                y: ref mut mut_ref_to_y,
            } = mutable_point;

            // 通过可变引用来改变 `mutable_point` 的字段 `y`。
            *mut_ref_to_y = 1;
        }

        println!("point is ({}, {})", point.x, point.y);
        println!("mutable_point is ({}, {})",
                 mutable_point.x,
                 mutable_point.y);

        // 包含一个指针的可变元组
        let mut mutable_tuple = (Box::new(5u32), 3u32);

        {
            // 解构 `mutable_tuple` 来改变 `last` 的值。
            let (_, ref mut last) = mutable_tuple;
            *last = 2u32;
        }

        println!("tuple is {:?}", mutable_tuple);
    }


}
