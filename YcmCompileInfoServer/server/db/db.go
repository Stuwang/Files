package db

type Db struct{
	Files map[string][]string
}

func NewDb()*DB{
	return &Db{
		Files:make(map[string][]string),
	}
}

func (self *Db)Merge(o map[string][]string){
	m := self.Files
	for k, v := range o {
		if l,ok :=m[k];ok{
			m[k] = append(l,v...)
		}else{
			m[k] = v
		}
	}
	self.Files = m
}
