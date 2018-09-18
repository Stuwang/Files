package main

import (
	"google.golang.org/grpc"
	pb "yuan/YcmCompileInfoServer/proto"
	"log"
	context "golang.org/x/net/context"
	"flag"
	"fmt"
)

var(
	file string
)

func main() {

	flag.StringVar(&file,"file","","")
	flag.Parse()

	conn,err := grpc.Dial("localhost:5005")
	if err != nil {
		log.Fatal(err)
	}

	client := pb.NewCompileOptionServerClient(conn)
	rsp,err := client.QueryFileFlags(context.Background(),&pb.QueryFileFlagsReq{File:file})
	if err != nil {
		log.Fatal(err)
	}
	if rsp.Status != 0{
		log.Fatal(rsp.Status,rsp.Msg)
	}
	fmt.Println(rsp.Flags)

}
