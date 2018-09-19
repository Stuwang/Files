package util

import (
	"testing"
	"strings"
	"fmt"
	"os/exec"
	"io/ioutil"
)

func Test_filterFlags(t *testing.T){
	flags := `/usr/bin/c++ -I/home/vim/test/fly/fly -std=c++11 -Werror -Wall -O2 -pthread -o CMakeFiles/fly.dir/base/LogStream.cpp.o -c /home/vim/test/fly/fly/base/LogStream.cpp`
	splitArray := strings.Split(flags," ")

	filterMap := map[string]bool{
		"-c":true,
	}

	newArray := make([]string,0)
	for i := 0; i< len(splitArray); {
		v := splitArray[i]

		if v == "-o"{
			// skip output file
			i++
		}else{
			if !filterMap[v]{
				newArray = append(newArray,v)
			}
		}

		i++
	}

	newArray = append(newArray,"-MM")

	fmt.Println(newArray)
}

func Test_parseHeaderFiles(t* testing.T){
	s := `LogStream.o: /home/vim/test/fly/fly/base/LogStream.cpp \
 /home/vim/test/fly/fly/base/LogStream.h \
 /home/vim/test/fly/fly/base/Types.h /home/vim/test/fly/fly/Config.h \
 /home/vim/test/fly/fly/base/StringView.h`

	arr,err := parseHeaderFiles(s)
	if err != nil {
		t.Fatal(err)
	}

 	fmt.Println(len(arr))
 	fmt.Println(arr)
}

func Test_execCommand(t*testing.T){
	flags := `/usr/bin/c++ -I/home/vim/test/fly/fly -std=c++11 -Werror -Wall -O2 -pthread -o CMakeFiles/fly.dir/base/LogStream.cpp.o -c /home/vim/test/fly/fly/base/LogStream.cpp`
	f ,err := filterFlags(flags)
	if err != nil {
		t.Fatal(err)
	}
	cmd := exec.Command(f[0],f[1:len(f)]...)
	fmt.Println(strings.Join(cmd.Args," "))
	stdout, err := cmd.StdoutPipe()
	if err != nil {
		t.Fatal(err)
	}
	if err := cmd.Start(); err != nil {
		t.Fatal(err)
	}

	s,err := ioutil.ReadAll(stdout)
	if err != nil {
		t.Fatal(err)
	}

	if err := cmd.Wait();err != nil{
		t.Fatal(err)
	}

	fmt.Println(string(s))
}