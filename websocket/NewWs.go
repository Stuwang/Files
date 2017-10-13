package main

import (
	"flag"
	"log"
	"net/http"

	"github.com/gorilla/websocket"
)

var upgrader = websocket.Upgrader{
	CheckOrigin: func(r *http.Request) bool { return true },
} // use default options

func echo(w http.ResponseWriter, r *http.Request) {
	c, err := upgrader.Upgrade(w, r, nil)
	if err != nil {
		log.Print("upgrade:", err)
		return
	}
	defer c.Close()
	for {
		_, message, err := c.ReadMessage()
		if err != nil {
			log.Println("read:", err)
			break
		}
		log.Printf("recv: %s", message)
		err = c.WriteMessage(websocket.BinaryMessage, message)
		if err != nil {
			log.Println("write:", err)
			break
		}
	}
}

func main() {
	log.SetFlags(0)
	http.HandleFunc("/echo", echo)

	var addr = flag.String("addr", "localhost:8080", "http service address")

	http.Handle("/",
		http.StripPrefix("/", http.FileServer(http.Dir(".\\out\\"))))

	log.Fatal(http.ListenAndServe(*addr, nil))
}
