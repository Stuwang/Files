use std::sync::{Arc, Mutex, Condvar};
use std::thread;
use std::time::Duration;

pub fn study_mutex_cond() {
    let pair = Arc::new((Mutex::new(false), Condvar::new()));
    let pair2 = pair.clone();



    thread::spawn(move || {
                      thread::sleep_ms(80);
                      let &(ref lock, ref cvar) = &*pair2;
                      let mut started = lock.lock().unwrap();
                      *started = true;
                      println!("ok, set started = true");
                      cvar.notify_all();
                  });

    let &(ref lock, ref cvar) = &*pair;
    let mut started = lock.lock().unwrap();

    loop {
        let result = cvar.wait_timeout(started, Duration::from_millis(10))
            .unwrap();
        println!("10 milliseconds have passed, or maybe the value changed!", );

        started = result.0;
        if *started == true {

            println!("ok, started is true");
            break;
        }
    }
}

pub fn study_env() {
    let path: &'static str = env!("PATH");
    println!("the $PATH variable at the time of compiling was: {}", path);
}
