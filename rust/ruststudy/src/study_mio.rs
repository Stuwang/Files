extern crate mio;

use self::mio::*;
use self::mio::net::{TcpListener, TcpStream};
use std::net::Shutdown;
use std::collections::BTreeMap;

// I will use Rust to build a echo server
pub fn use_mio() {

    // Setup some tokens to allow us to identify which event is
    // for which socket.
    const SERVER: Token = Token(0);

    // the connection index , start with 1
    let mut index = 1;

    let addr = "127.0.0.1:8080".parse().unwrap();

    // Setup the server socket
    let server = TcpListener::bind(&addr).unwrap();

    println!("listen at {:?}", addr);

    // Create a poll instance
    let poll = Poll::new().unwrap();

    // Start listening for incoming connections
    poll.register(&server, SERVER, Ready::readable(), PollOpt::level())
        .unwrap();


    let mut connctions = BTreeMap::new();

    loop {
        // Create storage for events
        let mut events = Events::with_capacity(1024);

        // poll it
        poll.poll(&mut events, None).unwrap();

        for event in events.iter() {
            match event.token() {
                SERVER => {
                    // Accept and drop the socket immediately, this will close
                    // the socket and notify the client of the EOF.
                    let (conn, addr) = server.accept().unwrap();
                    println!("the remote addr is {:?}", addr);
                    poll.reregister(&conn, Token(index), Ready::all(), PollOpt::level());
                    connctions.insert(index, conn);
                    index += 1;
                }
                Token(index) => {
                    println!("event is reatched");
                }
                _ => unreachable!(),
            }
        }
    }

}
