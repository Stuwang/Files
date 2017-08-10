package main

import (
	// "fmt"
	"io"
	"log"
	"net/http"
	"os"
	"regexp"
	"time"
)

func main() {

	log.SetFlags(log.Lshortfile | log.Flags())

	serveMux := http.NewServeMux()
	serveMux.HandleFunc("/", StaticServer)
	serveMux.HandleFunc("/bye", SayBye)
	serveMux.HandleFunc("/ha", func(w http.ResponseWriter, r *http.Request) {
		w.Write([]byte("hahahha,funny"))
	})
	// serveMux.HandleFunc("/static", StaticServer)

	server := http.Server{
		Addr:        ":8080",
		Handler:     serveMux,
		ReadTimeout: 5 * time.Second,
	}

	// log.Info("http server start,port is ", 8080)
	log.Println("http server start,port is ", 8080)
	err := server.ListenAndServe()
	if err != nil {
		log.Fatal(err)
	}

	log.SetFlags(log.Ltime)

	log.Println("haahahah")

}

func SayHello(w http.ResponseWriter, r *http.Request) {
	if ok, _ := regexp.MatchString("/static/", r.URL.String()); ok {
		StaticServer(w, r)
		return
	} else {
		const a = "{\"name\":\"wangyuan\",\"age\":23}"
		io.WriteString(w, a)
	}
}

func SayBye(w http.ResponseWriter, r *http.Request) {
	io.WriteString(w, "Byebye")
}

func StaticServer(w http.ResponseWriter, r *http.Request) {
	wd, err := os.Getwd()
	if err != nil {
		log.Fatal(err)
	}
	log.Println("request file " + r.RequestURI)
	http.StripPrefix("/",
		http.FileServer(http.Dir(wd))).ServeHTTP(w, r)

}
