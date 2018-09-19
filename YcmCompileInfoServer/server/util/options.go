package util

import "encoding/json"

type CMakeOptions struct{
	Dir string `json:"directory"`
	Cmd string `json:"command"`
	File string `json:"file"`
}

func ParseCmakeDbFile(s []byte)(map[string][]string,error){
	var list []*CMakeOptions
	err := json.Unmarshal(s,&list)
	if err != nil {
		return nil, err
	}

	result := make(map[string][]string)
	for _, v := range list {
		fs,err := filterFlags(v.Cmd)
		if err != nil {
			return nil,err
		}

		hs,err := execCommand(fs...)
		if err != nil {
			return nil,err
		}

		hss,err := parseHeaderFiles(hs)
		if err != nil {
			return nil,err
		}
		for _, headFile := range hss {
			if l,ok := result[headFile];ok{
				result[headFile] = append(l,v.Cmd)
			}else{
				result[headFile] = []string{v.Cmd}
			}
		}
		if l,ok := result[v.File];ok{
			result[v.File] = append(l,v.Cmd)
		}else{
			result[v.File] = []string{v.Cmd}
		}
	}
	return result,nil
}
