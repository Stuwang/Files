package util

import (
	"strings"
	"os/exec"
	"fmt"
	"io/ioutil"
)

func GetAllHeaderFiles(file string,flags string)([]string,error){
	return nil, nil
}

func execCommand(f ...string)(string,error){
	cmd := exec.Command(f[0],f[1:len(f)]...)
	fmt.Println(strings.Join(cmd.Args," "))
	stdout, err := cmd.StdoutPipe()
	if err != nil {
		return "",err
	}
	if err := cmd.Start(); err != nil {
		return "",err
	}

	s,err := ioutil.ReadAll(stdout)
	if err != nil {
		return "",err
	}

	if err := cmd.Wait();err != nil{
		return "",err
	}

	return string(s), nil
}

func parseHeaderFiles(files string)([]string,error){
	sps := strings.Split(files,":")
	filesStr := sps[1]

	arr := strings.Split(strings.Replace(filesStr,"\\\n","",-1)," ")
	i := 0
	for j := 0; j < len(arr); j++{
		if i != j{
			arr[i] = arr[j]
		}
		if strings.TrimSpace(arr[j]) != ""{
			i++
		}
	}
	arr = arr[0:i]
	if len(arr) > 0 {
		arr = arr[1:len(arr)]
	}
	return arr, nil
}

func filterFlags(flags string)([]string,error){
	splitArray := strings.Split(flags," ")

	newArray := make([]string,0)
	for i := 0; i< len(splitArray); {
		v := splitArray[i]
		switch v {
		case "-c":
		case "-o":
			// skip -c output file
			i++
		default:
			newArray = append(newArray,v)
		}
		i++
	}
	newArray = append(newArray,"-MM")

	return newArray, nil
}