#!/usr/bin/python3

import sys;
import ply.lex as lex
import ply.yacc as yacc


import func_token;

# yacc
# 语法分析部分

# precedence = (
#     ('left',','),
#     ('left',':'),
#   ('left',';'),
#     )

class Type:
    def __init__(self):
        self.is_base_type = True;
        self.type_name = "";
        # if is base type, this is None
        self.fieldS = None;
        # storge size
        self.size = 0;
        # 
        self.inv_type = None;


class Param:
    def __init(self):
        self.name = "";
        self.type = None;

class FuncDef:
    def __init__(self):
        self.ret_type = None;
        self.params = [];
        self.name = "";

def MyYacc(tokens = None):

    def p_all(p):
        ' all : all define '

    def p_all_define(p):
        ' all : define '

    def p_define_function(p):
        'define : function'

    def p_define_struct(p):
        'define : struct'
         
    def p_struct(p):
        "struct : TYPE_DEFINE NAME STRUCT '{' s_member_list '}' "
        print("struct :",p[2]);

    def p_s_member_list(p):
        ''' s_member_list : param s_member_list 
                        | param 
        '''

    # function decl
    def p_function(p):
        "function : FUNC NAME '(' paramlist ')' return "
        print("function name :",p[2]);

    def p_paramlist(p):
        " paramlist : paramlist ',' param "

    def p_paramlist_none(p):
        " paramlist : "

    def p_paramlist_last(p):
        " paramlist : param "
        
    def p_param(p):
        " param : NAME ':' TYPE "
        print("name:",p[1],"type:",p[3]);

    def p_return(p):
        "return : TYPE"
        print("return type :",p[1]);

    def p_return_none(p):
        "return : "
        print("no return type :");

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

type MyType struct {
    a:int
    c:string
    d:double
    e:bin
}
''')

my_lex = func_token.lexer;

PrintTokens = True
my_lex.input(data)
if PrintTokens == True :
    my_lex.input(data)
    while True:
        tok = my_lex.token()
        if not tok:
            print("error occr")
            break
        print(tok)
    print("token parse ok!");


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