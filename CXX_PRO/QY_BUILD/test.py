import time;  # 引入time模块
from util import  Stack;

import subprocess as SubPro;

def GetDependsOfFile(filename):
	status,output = SubPro.getstatusoutput('gcc -MM '+filename)
	if status != 0:
		raise Exception("error , run ");
	SourceFile,DependFiles = output.split(":");
	ret = [];
	for i in DependFiles.split(" "):
		if i.lstrip() != "":
			ret.append(i.lstrip());

	return ret;


def study_subprocess():
    filename = '../ProjectExp/main.cpp'

    print("the depends of ")
    for x in GetDependsOfFile(filename):
        print(x);


def study_date_time():
    ticks_1 = time.time();
    time.sleep(1);
    ticks_2 = time.time();
    time.sleep(1);
    ticks_3 = time.time();
    print(ticks_1)
    print(ticks_2)
    print(ticks_3)
    print(ticks_1 >= ticks_2)
    pass

class DependObj:
    def __init__(self,obj):
        self.obj = obj;
        self.depend = [];
        self.depended = [];

    def add_depend(self,l):
        if type(l) == type([]):
            self.depend.extend(l);
        else:
            self.depend.append(l);

    def add_depended(self,l):
        if type(l) == type([]):
            self.depended.extend(l);
        else:
            self.depended.append(l);

    def Do(self,func):
        func(self);

def map_search():
    node_1 = DependObj(1);
    node_2 = DependObj(2);
    node_3 = DependObj(3);
    node_4 = DependObj(4);
    node_5 = DependObj(5);

    node_1.add_depend([node_2,node_3]);
    node_2.add_depend([node_4]);
    node_3.add_depend([node_4, node_5]);

    s = Stack();
    s.push(node_1);

    while(not s.empty()):
        head = s.pop();
        for i in head.depend:
            i.add_depended(head);
            s.push(i);
            pass

    s.push(node_1)
    desc = set();
    while(not s.empty()):
        head = s.pop();
        for i in head.depend:
            desc.add((head.obj,'->',i.obj));
            desc.add((i.obj, '=>', head.obj));
            s.push(i);

    # print("->  ======================")
    # for i in desc:
    #     if i[1] == "->":
    #         print(i[0],i[1],i[2]);
    # print("=>  ======================")
    # for i in desc:
    #     if i[1] == "=>":
    #         print(i[0],i[1],i[2]);
    #
    # print("==========================")

    def Print(s):
        print("build ",s.obj);

    s.push(node_1)
    while(not s.empty()):
        head = s.top();
        if len(head.depend) == 0:
            head.Do(Print);
            for i in head.depended:
                i.depend.remove(head);
            s.pop();
        else:
            for i in head.depend:
                s.push(i);





def test():
    map_search();
    print((1,1) == (1,1))
    # study_date_time();
    pass;


# print("this is a string print from test")