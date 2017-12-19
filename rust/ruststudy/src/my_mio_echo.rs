extern crate mio;

use self::mio::*;
use self::mio::net::{TcpListener, TcpStream};

use std::net::Shutdown;
use std::collections::BTreeMap;
use std::error::Error;

fn try_main() -> Result<(), Box<Error>> {
    use self::mio::{Events, Ready, Poll, PollOpt, Token};
    use self::mio::net::TcpListener;

    use std::thread;
    use std::io::{self, Read, Write};
    use std::collections::HashMap;
    use std::str;

    // Pick a token that will not be used by any other socket and use that one
    // for the listener.
    const LISTENER: Token = Token(0);

    // Used to store the sockets.
    let mut sockets = HashMap::new();

    // This is used to generate a unique token for a socket
    let mut next_socket_index = 1;

    // The `Poll` instance
    let poll = Poll::new()?;

    let addr = "127.0.0.1:8080".parse()?;
    println!("addr is {}", &addr);

    // Tcp listener
    let listener = TcpListener::bind(&addr)?;

    // Register the listener
    poll.register(&listener, LISTENER, Ready::readable(), PollOpt::edge())?;

    // Spawn a thread that will connect a bunch of sockets then close them
    let addr = listener.local_addr()?;
    // thread::spawn(move || {
    //     use std::net::TcpStream;

    //     // +1 here is to connect an extra socket to signal the socket to close
    //     for _ in 0..(MAX_SOCKETS + 1) {
    //         // Connect then drop the socket
    //         let _ = TcpStream::connect(&addr).unwrap();
    //     }
    // });

    // Event storage
    let mut events = Events::with_capacity(1024);

    // Read buffer, this will never actually get filled
    let mut buf = [0; 256];

    // The main event loop
    loop {
        // Wait for events
        poll.poll(&mut events, None)?;

        for event in &events {
            match event.token() {
                LISTENER => {
                    // Perform operations in a loop until `WouldBlock` is
                    // encountered.
                    loop {
                        match listener.accept() {
                            Ok((socket, addr)) => {
                                // Get the token for the socket
                                let token = Token(next_socket_index);
                                next_socket_index += 1;

                                println!("accept new socket addr {:?} token {:?}", addr, token.0);

                                // Register the new socket w/ poll
                                poll.register(&socket, token, Ready::readable(), PollOpt::edge())?;

                                // Store the socket
                                sockets.insert(token, socket);
                            }
                            Err(ref e) if e.kind() == io::ErrorKind::WouldBlock => {
                                // Socket is not ready anymore, stop accepting
                                break;
                            }
                            e => panic!("err={:?}", e), // Unexpected error
                        }
                    }
                }
                token => {
                    // Always operate in a loop
                    loop {
                        match sockets.get_mut(&token).unwrap().read(&mut buf) {
                            Ok(0) => {
                                // Socket is closed, remove it from the map
                                let addr = sockets.get(&token).unwrap().peer_addr();
                                println!("addr {:?},token {:?} closed ", addr, token.0);
                                sockets.remove(&token);
                                break;
                            }
                            // Data is not actually sent in this example
                            Ok(size) => {
                                // println!("recv {:?} bytes data",
                                //          str::from_utf8(&buf[0..size]).unwrap());
                                println!("recv {:?} bytes data",
                                         match str::from_utf8(&buf[0..size]) {
                                             Ok(data) => data,
                                             Err(err) => "error",
                                         });

                                match sockets.get_mut(&token).unwrap().write(&buf[0..size]) {
                                    Ok(write_size) => {
                                        if (size == write_size) {
                                            println!("write {:?} size", size);
                                        } else {
                                            println!("write error");
                                        }
                                    }
                                    Err(_) => println!("error occr"),
                                }
                                // println!("recv {} datas", size);
                                // println!("");
                            }
                            Err(ref e) if e.kind() == io::ErrorKind::WouldBlock => {
                                // Socket is not ready anymore, stop reading
                                break;
                            }
                            e => panic!("err={:?}", e), // Unexpected error
                        }
                    }
                }
            }
        }
    }
   	Ok(())
}

pub fn echo_main() {
    try_main().unwrap();
}
