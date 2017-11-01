# 

import sys;
import ply.lex as lex
import ply.yacc as yacc


# 解析函数表达式，RPC IDL语言自定义


# 词法分析部分

# 特殊的字符，从标识符中区分
reserved = {
   'func' : 'FUNC',
   'int' : 'TYPE',
   'char' : 'TYPE',
   'string' : 'TYPE',
   'double' : 'TYPE',
   'bin' : 'TYPE',
   'struct': "STRUCT",
   'type': "TYPE_DEFINE"
}

# TOKEN 类型
tokens = [
    'NAME','FUNC','TYPE','STRUCT','TYPE_DEFINE'
    ];

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
t_ignore = " ;\t"

def t_newline(t):
    r'\n+'
    t.lexer.lineno += t.value.count("\n")
    
def t_error(t):
    print("Illegal character '%s'" % t.value[0])
    t.lexer.skip(1)

lexer = lex.lex()

# yacc
# 语法分析部分

# precedence = (
#     ('left',','),
#     ('left',':'),
# 	('left',';'),
#     )

def all(p):
	''' all : define
 			| define ';' all
	 '''

def define(p):
	"define :  function "

# def p_struct(p):
# 	"structexpr : TYPE_DEFINE NAME STRUCT '{' s_member_list '}' "
# 	print("struct :",p[2]);

# def p_s_member_list(p):
# 	''' s_member_list : param  s_member_list 
# 					| param 
# 	'''

# function decl
def p_func_binop(p):
    "function : FUNC  NAME '(' paramlist ')' returnexpr "
    print("function name :",p[2]);

def p_func_noreturn_binop(p):
    "function : FUNC  NAME '(' paramlist ')'"
    print("function name :",p[2]);

def p_func_noarg_binop(p):
    "function : FUNC  NAME '(' ')' ':' returnexpr "
    print("function name :",p[2]);

def p_func_noreturn_and_noarg_binop(p):
    "function : FUNC  NAME '(' ')'"
    print("noreturn_and_noar")

def p_paramlist(p):
	" paramlist : param ',' paramlist "

def p_paramlist_last(p):
	" paramlist : param "
	
def p_param(p):
	" param : NAME ':' TYPE "
	print("name:",p[1],"type:",p[3]);

def p_returnexpr(p):
	"returnexpr : TYPE"
	print("return type :",p[1]);

# function decl end

def p_error(p):
    if p:
        print("Syntax error at '%s'" % p.value)
    else:
        print("Syntax error at EOF")


yacc.yacc()


data = '''

func functin1(
	a:int,
	b:char,
	c:string,
	d:double,
	e:bin) int ;


func functin2( 
	a:int,
	b:char,
	c:string,
	d:double,
	e:bin) int;
 
func functin3(
	a:int,
	b:char,
	c:string,
	d:double,
	e:bin) int

'''

# data = '''


# type MyType struct {
# 	a:int
# 	b:char
# 	c:string
# 	d:double
# 	e:bin
# }
# '''

PrintTokens = False
lexer.input(data)
if PrintTokens == True :
	lexer.input(data)
	while True:
	    tok = lexer.token()
	    if not tok:
	        break
	    print(tok)
	print("token parse ok!");

yacc.parse(data)

# while 1:
#     try:
#         s = input('calc > ')
#     except EOFError:
#         break
#     if not s: continue
#     yacc.parse(s)