# 

import sys;
import ply.lex as lex
import ply.yacc as yacc


# 解析函数表达式，RPC IDL语言自定义


# 词法分析部分

# TOKEN 类型
tokens = ['NAME','FUNC','TYPE','STRUCT','TYPE_DEFINE'];

def MyLexBuild():

    # 特殊的字符，从标识符中区分
    reserved = {
    # key word
       'func' : 'FUNC',
    # base type
       'int' : 'TYPE',
       'char' : 'TYPE',
       'string' : 'TYPE',
       'double' : 'TYPE',
       'bin' : 'TYPE',
    # struct
       'struct': "STRUCT",
    # type
       'type': "TYPE_DEFINE"
    }

    # 字面值？。 忽略
    literals = ['(',')',':',',','{','}',';','=']

    # Tokens
    # t_FUNC   = r'func'
    # t_TYPE   = r'int|char|string|double|bin|void'
    # t_NAME   = r'[a-zA-Z][a-zA-Z0-9_]*'

    # 定义规则，同时做特殊处理
    def t_NAME(t):
        r'[a-zA-Z][a-zA-Z0-9_]*'
        t.type = reserved.get(t.value,'NAME') 
        return t;

    # manul s
    t_ignore = " \t"

    def t_newline(t):
        r'\n+'
        t.lexer.lineno += t.value.count("\n")
        
    def t_error(t):
        print("Illegal character '%s'" % t.value[0])
        t.lexer.skip(1)

    return lex.lex(optimize=1)

# yacc
# 语法分析部分

# precedence = (
#     ('left',','),
#     ('left',':'),
#   ('left',';'),
#     )

def MyYacc(tokens = None):
    def p_all(p):
        ''' all : define 
                | define all 
        '''

    def p_define(p):
        '''define : function
                    | structexpr
         '''
         
    def p_struct(p):
        "structexpr : TYPE_DEFINE NAME STRUCT '{' s_member_list '}' "
        print("struct :",p[2]);

    def p_s_member_list(p):
        ''' s_member_list : param s_member_list 
                        | param 
        '''
    # function decl
    def p_func_binop(p):
        "function : FUNC NAME '(' paramlist ')' returnexpr "
        print("function name :",p[2]);

    def p_paramlist(p):
        " paramlist : param ',' paramlist "

    def p_noparamlist(p):
        " paramlist : "

    def p_paramlist_last(p):
        " paramlist : param "
        
    def p_param(p):
        " param : NAME ':' TYPE "
        print("name:",p[1],"type:",p[3]);

    def p_returnexpr(p):
        "returnexpr : TYPE"
        print("return type :",p[1]);

    def p_no_returnexpr(p):
        "returnexpr : "
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


my_lex = MyLexBuild();

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

parser = MyYacc(tokens);
parser.parse(data,lexer=my_lex,debug=log)
# parser.parse(data,debug=log)

# while 1:
#     try:
#         s = input('calc > ')
#     except EOFError:
#         break
#     if not s: continue
#     yacc.parse(s)