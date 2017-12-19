use std::sync::mpsc::{Sender, Receiver};
use std::sync::mpsc;
use std::thread;
use std::path::Path;

use std::error::Error;
use std::io::prelude::*;
use std::process::{Command, Stdio};

use std::fs::File;
use std::env;


// 这是主（`main`）线程
pub fn RunThread() {
    // 提供一个 vector 来存放所创建的子线程（children）。
    let mut children = vec![];

    for i in 0..10 {
        // 启动（spin up）另一个线程
        children.push(thread::spawn(
            move || println!("this is thread number {}", i),
        ));
    }


    for child in children {
        // 等待线程到结束。返回一个结果。
        let _ = child.join();
    }
}

pub fn UseSc() {
    // 通道有两个端点：`Sender<T>` 和 `Receiver<T>`，其中 `T` 是要发送
    // 消息的类型（类型标注是可有可无的）
    // let (tx, rx): (Sender<i32>, Receiver<i32>) = mpsc::channel();
    let (tx, rx) = mpsc::channel();

    static NTHREADS: i32 = 3;
    let mut children = vec![];

    for id in 0..NTHREADS {
        // sender 发送端可被复制
        let thread_tx = tx.clone();

        // 每个线程都将通过通道来发送它的 id
        let t = thread::spawn(move || {

            // 发送是一个非阻塞操作，线程将在发送完消息后继续进行
            println!("thread {} finished", id);

            // 此线程取得 `thread_tx` 所有权
            // 每个线程都在通道中排队列出消息
            // （原文：The thread takes ownership over `thread_tx`
            // Each thread queues a message in the channel）
            thread_tx.send(id).unwrap();

        });

        children.push(t);
    }

    // 所有消息都在此处被收集
    let mut ids = Vec::with_capacity(NTHREADS as usize);
    for _ in 0..NTHREADS {
        // `recv` 方法从通道中拿到一个消息
        // 若无可用消息的话，`recv` 将阻止当前线程
        ids.push(rx.recv());
    }

    for child in children {
        // 等待线程到结束。返回一个结果。
        let _ = child.join();
    }

    // 显示已发送消息的次序
    println!("{:?}", ids);
}


pub fn UsePath() {
    // 从 `&'static str` 创建一个 `Path`
    let path = Path::new(".");

    // `display` 方法返回一个可显示（showable）的结构体
    // #![allow(dead_code)]
    let display = path.display();

    // `join` 使用操作系统的特定分隔符来合并路径，并返回新的路径
    let new_path = path.join("a").join("b").join("c");

    // 将路径转换成一个字符串 slice
    match new_path.to_str() {
        None => panic!("new path is not a valid UTF-8 sequence"),
        Some(s) => println!("new path is {}", s),
    }
}

pub fn UseCommand() {
    let output = Command::new("rustc")
        .arg("--version")
        .output()
        .unwrap_or_else(|e| panic!("failed to execute process: {}", e));

    if output.status.success() {
        let s = String::from_utf8_lossy(&output.stdout);

        print!("rustc succeeded and stdout was:\n{}", s);
    } else {
        let s = String::from_utf8_lossy(&output.stderr);

        print!("rustc failed and stderr was:\n{}", s);
    }
}




pub fn UseCommandProcess() {
    // 触发 `wc` 命令（原文：Spawn the `wc` command）
    let process = match Command::new("wc")
        .stdin(Stdio::piped())
        .stdout(Stdio::piped())
        .spawn() {
        Err(why) => panic!("couldn't spawn wc: {}", why.description()),
        Ok(process) => process,
    };

    // 将字符串写入 `wc` 的 `stdin`。
    //
    // `stdin` 拥有 `Option<ChildStdin>` 类型，不过既然我们已经知道这个实例
    // 只能拥有一个，那么我们可以直接解包（`unwrap`）它。
    // （原文：`stdin` has type `Option<ChildStdin>`, but since we know this instance
    // must have one, we can directly `unwrap` it.）

    static PANGRAM: &'static str = "the quick brown fox jumped over the lazy dog\n";

    match process.stdin.unwrap().write_all(PANGRAM.as_bytes()) {
        Err(why) => panic!("couldn't write to wc stdin: {}", why.description()),
        Ok(_) => println!("sent pangram to wc"),
    }

    // 因为 `stdin` 在上面调用后就不再存活，所以它被销毁了，且管道被关闭。
    //
    // 这点非常重要，否则 `wc` 不会开始处理我们刚刚发送的输入。

    // `stdout` 域也拥有 `Option<ChildStdout>` 类型，所以必需解包。
    let mut s = String::new();
    match process.stdout.unwrap().read_to_string(&mut s) {
        Err(why) => panic!("couldn't read wc stdout: {}", why.description()),
        Ok(_) => print!("wc responded with:\n{}", s),
    }
}

pub fn WaitProcess() {
    // let mut child = Command::new("dir").arg("5").spawn().unwrap();
    let mut child = Command::new("dir").spawn().unwrap();

    let result = child.wait().unwrap();

    println!("end of this at {}:{}", file!(), line!());
}




pub fn OpenFile() {
    // 给所需的文件创建一个路径
    let path = Path::new("hello.txt");
    let display = path.display();

    // 以只读方式打开路径，返回 `io::Result<File>`
    let mut file = match File::open(&path) {
        // `io::Error` 的 `description` 方法返回一个描述错误的字符串。
        Err(why) => panic!("couldn't open {}: {}", path.display(), why.description()),
        Ok(file) => file,
    };

    // 读取文件内容到一个字符串，返回 `io::Result<usize>`
    let mut s = String::new();
    match file.read_to_string(&mut s) {
        Err(why) => panic!("couldn't read {}: {}", display, why.description()),
        Ok(_) => print!("{} contains:\n{}", display, s),
    }

    // `file` 离开作用域，并且 `hello.txt` 文件将被关闭。
}

static LOREM_IPSUM: &'static str = "Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod
tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam,
quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo
consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse
cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non
proident, sunt in culpa qui officia deserunt mollit anim id est laborum.
";


pub fn CreateFile() {
    let path = Path::new("lorem_ipsum.txt");
    let display = path.display();

    // 以只写模式打开文件，返回 `io::Result<File>`
    let mut file = match File::create(&path) {
        Err(why) => panic!("couldn't create {}: {}", display, why.description()),
        Ok(file) => file,
    };

    // 将 `LOREM_IPSUM` 字符串写进 `file`，返回 `io::Result<()>`
    match file.write_all(LOREM_IPSUM.as_bytes()) {
        Err(why) => panic!("couldn't write to {}: {}", display, why.description()),
        Ok(_) => println!("successfully wrote to {}", display),
    }
}


pub fn UseArgs() {
    let args: Vec<String> = env::args().collect();

    // 第一个参数是调用本程序的路径
    println!("My path is {}.\n", args[0]);

    // 其余的参数充当一般的命令行参量。
    // 调用程序方式如下：
    //   $ ./args arg1 arg2
    println!("I got {:?} arguments: {:?}.", args.len() - 1, &args[1..]);
}


#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn name() {
        RunThread();
        UseSc();
        UsePath();
        UseCommand();
        CreateFile();
        UseArgs()
    }

    #[test]
    #[should_panic]
    fn test_error() {
        UseCommandProcess();
    }

    #[test]
    #[should_panic]
    fn test_error2() {
        OpenFile();
    }

    #[test]
    #[should_panic]
    fn test_error3() {
        WaitProcess();
    }
}
