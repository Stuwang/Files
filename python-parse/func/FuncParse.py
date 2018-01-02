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
    def __init__(self):
        self.is_base_type = True;
        self.type_name = "";

NullType = Type();

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

    def print(self):
        print("==========================");
        print("   this is a struct ")
        print("function name : ",self.name)

        print("member size   : ",len(self.members));
        for index in range(0,len(self.members)):
            p = self.members[index];
            print("index : ",index);
            print("name  : ",p.name);
            print("type  : ",p.type.type_name);
            print("---------")
            
        print("");        

class Program:
    def __init__(self):
        self.types = [];
        self.functions = [];
        pass

    def add_type(t):
        self.types.append(t);

    def add_function(func):
        self.functions.append(func);

    def find_type(type_name):
        pass

    def init_base_type():
        pass


def MyYacc(tokens = None):

    def p_all(p):
        ' all : all define '

    def p_all_define(p):
        ' all : define '
        # this is first
        

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
parser.parse(data,lexer=my_lex,debug=log)
# parser.parse(data,debug=log)

# while 1:
#     try:
#         s = input('calc > ')
#     except EOFError:
#         break
#     if not s: continue
#     yacc.parse(s)