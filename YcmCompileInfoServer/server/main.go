package main

import (
	pb "yuan/YcmCompileInfoServer/proto"
	context "golang.org/x/net/context"
	"google.golang.org/grpc"
	"net"
	"log"
	"yuan/YcmCompileInfoServer/server/db"
	"yuan/YcmCompileInfoServer/server/util"
)

type CompileServer struct{
	db *db.Db
}

func(self *CompileServer)QueryFileFlags(ctx context.Context, in *pb.QueryFileFlagsReq) (*pb.QueryFileFlagsRep, error){
	result := &pb.QueryFileFlagsRep{}
	if arr,e := self.db.Files[in.File];e && len(arr) >= 1{
		result.Status = 0
		result.Flags = arr[0]
		return result,nil
	}
	result.Status = 1
	result.Msg = "找不到"
	return result, nil
}



func (self *CompileServer)AddCompileDb(ctx context.Context,in *pb.AddCompileDbReq) (*pb.AddCompileDbRep, error){
	result := &pb.AddCompileDbRep{}
	f,err := util.ParseCmakeDbFile([]byte(in.Content))
	if err != nil {
		log.Println(err)
		result.Status = 1
		result.Msg = err.Error()
		return result,nil
	}

	self.db.Merge(f)

	return result, nil
}

func main() {

	grpcServer :=  grpc.NewServer()
	server := &CompileServer{db.NewDb()}
	pb.RegisterCompileOptionServerServer(grpcServer,server)

	lis, err := net.Listen("tcp", ":5005")
	if err != nil {
		log.Fatalf("failed to listen: %v", err)
	}

	if err := grpcServer.Serve(lis);err != nil{
		log.Fatal(err)
	}
}