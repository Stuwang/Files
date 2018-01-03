#!/usr/bin/python3

import sys;
import ply.lex as lex
import ply.yacc as yacc

import func_token;

# this is a function to debug
def PrintTokens(data,lex = lex.lexer):
    print("======== start print token  ========")
    PrintTokens = True
    lex.input(data)
    if PrintTokens == True :
        lex.input(data)
        while True:
            tok = lex.token()
            if not tok:
                print("error occr")
                break
            print(tok)
        print("token parse ok!");
    print("======== end print token ===========")

class Type:
    def __init__(self,name = "",is_base = True):
        self.is_base_type = is_base;
        self.type_name = name;

NullType = Type("void");

class Param:
    def __init(self):
        self.name = "";
        self.type = None;

class FuncDef:
    def __init__(self):
        self.ret_type = None;
        self.params = [];
        self.name = "";
        self.flag = "function";

    def get_user_types(self):
        ret = [];
        for t in self.params:
            if t.type.is_base_type == False:
                ret.append(t.type.type_name);
        return ret;

    def print(self):
        print("==========================");
        print("   this is a function ")
        print("function name : ",self.name)

        return_name = None;
        if self.ret_type != None:
            return_name = self.ret_type.type_name;

        print("return type   : ",return_name);
        print("param size    : ",len(self.params));
        for index in range(0,len(self.params)):
            p = self.params[index];
            print("---------")
            print("index : ",index);
            print("name  : ",p.name);
            print("type  : ",p.type.type_name);
            print("---------")
            
        print("");

class StructDef:
    def __init__(self):
        self.name = "";
        self.members = [];
        self.flag = "struct";

    def get_user_types(self):
        ret = [];
        for t in self.members:
            if t.type.is_base_type == False:
                ret.append(t.type.type_name);
        return ret;

    def print(self):
        print("==========================");
        print("   this is a struct ")
        print("function name : ",self.name)

        print("member size   : ",len(self.members));
        for index in range(0,len(self.members)):
            p = self.members[index];
            print("---------")
            print("index : ",index);
            print("name  : ",p.name);
            print("type  : ",p.type.type_name);
            print("---------");
            
        print("");       

class Program:
    def __init__(self):
        self.types = [];
        self.functions = [];
        # self.init_base_type();
        pass

    def add_type(self,t):
        self.types.append(t);

    def add_function(self,func):
        self.functions.append(func);

    def find_type(self,type_name):
        for x in self.types:
            if x.type_name == type_name:
                return x;
        return None;

    def init_base_type(self):
        self.add_type(Type("int"));
        self.add_type(Type("double"));
        self.add_type(Type("string"));
        self.add_type(Type("bin"));

    def Check():
        
        return "";

    def GenCode(self,writer):
        # no check
        writer.write("#ifndef _GEN_H_\n");
        writer.write("#define _GEN_H_\n");
        writer.write("\n");
        writer.write("\n");
        writer.write("\n");

        KIndextFlag = "\t";

        for t in self.types:
            writer.write("struct " + t.name + "{\n");
            for i in range(0,len(t.members)):
                m = t.members[i];
                endFlag = ";";
                writer.write(KIndextFlag + m.type.type_name + " " + m.name + endFlag + "\n");
            writer.write("};\n");
            writer.write("\n");
            writer.write("\n");

        for f in self.functions:
            writer.write(f.ret_type.type_name + " " + f.name + "(");
            for index in range(0,len(f.params)):
                p_name = "param_" + str(index);
                SplitFlag = ",";
                if index == ( len(f.params) - 1 ):
                    SplitFlag = "";
                p = f.params[index];
                writer.write(p.type.type_name + " " + p.name + SplitFlag);
            writer.write(");");
            writer.write("\n");
            writer.write("\n");

        writer.write("#endif //_GEN_H_\n");
        


def MyYacc(tokens = None):

    def p_all(p):
        ' all : all define '
        pro = p[1];
        if p[2].flag == "struct":
            pro.add_type(p[2]);
        elif p[2].flag == "function":
            pro.add_function(p[2]);
        else:
            raise Exception("error , unknow flag " + p[2].flag);

        p[0] = pro;

    def p_all_define(p):
        ' all : define '
        # this is first
        pro = Program();
        if p[1].flag == "struct":
            pro.add_type(p[1]);
        elif p[1].flag == "function":
            pro.add_function(p[1]);
        else:
            raise Exception("error , unknow flag " + p[1].flag);

        p[0] = pro;
        

    def p_define_function(p):
        'define : function'
        p[1].print();
        p[0] = p[1];

    def p_define_struct(p):
        'define : struct'
        p[1].print();
        p[0] = p[1];
         
    def p_struct(p):
        "struct : TYPE_DEFINE NAME STRUCT '{' members '}' "
        s = StructDef()
        s.name = p[2];
        s.members = p[5];
        p[0] = s;

    def p_members(p):
        ' members : members param '
        p[1].append(p[2]);
        p[0] = p[1];

    def p_member_param(p):
        ' members : param '
        if p[1] != None:
            p[0] = [p[1]];
        else:
            p[0] = [];

    # function decl
    def p_function(p):
        "function : FUNC NAME '(' paramlist ')' return "
        func = FuncDef();
        func.name = p[2];
        func.params = p[4];
        func.ret_type = p[6];
        p[0] = func;


    def p_paramlist(p):
        " paramlist : paramlist ',' param "
        p[1].append(p[3]);
        p[0] = p[1];

    def p_paramlist_last(p):
        " paramlist : param "
        if p[1] != None:
            p[0] = [p[1]];
        else:
            p[0] = [];
        
    def p_param(p):
        " param : NAME ':' type "
        param = Param();
        param.type = p[3];
        param.name = p[1];

        p[0] = param;

    def p_param_none(p):
        " param : "
        p[0] = None;

    def p_return(p):
        "return : type"
        p[0] =p[1];

    def p_return_none(p):
        "return : "
        p[0] = NullType;

    def p_type_base(p):
        'type : TYPE'
        t = Type();
        t.type_name = p[1];
        p[0] = t;

    def p_type_userdefine(p):
        'type : NAME '
        t = Type();
        t.type_name = p[1];
        t.is_base_type = False;
        p[0] = t;

    # error handle
    def p_error(p):
        if p:
            print("Syntax error at '%s'" % p.value)
            print(p);
        else:
            print("Syntax error at EOF")

    return yacc.yacc(debug=True,optimize=1);

data =(
'''
func fun(a:int) int

func functin1(
    a:int,
    b:char,
    c:string,
    d:double,
    e:bin) char 

func Function2(a:int) int 

func Function3(a:int) int 

func Function4(a:int) int 

func Function5()

type MyType struct {
    a :int
    c :string
    d :double
    e :bin
}

type  MyType1 struct{
    a :int
    b :string
}

func Function4(a:MyType) MyType1 

''')

my_lex = func_token.lexer;

# PrintTokens(data,my_lex);

import logging
logging.basicConfig(
    level = logging.DEBUG,
    filename = "parselog.txt",
    filemode = "w",
    format = "%(message)s"
)
log = logging.getLogger()

parser = MyYacc(func_token.tokens);
a = parser.parse(data,lexer=my_lex,debug=log)

file_object = open('testfile.h', 'w')
a.GenCode(file_object);
file_object.close();
# parser.parse(data,debug=log)

# while 1:
#     try:
#         s = input('calc > ')
#     except EOFError:
#         break
#     if not s: continue
#     yacc.parse(s)