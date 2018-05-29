#!/usr/bin/python3

import sys;
import ply.lex as lex

# 解析函数表达式，RPC IDL语言自定义


# 词法分析部分

# TOKEN 类型
tokens = ['NAME','FUNC','TYPE','STRUCT','TYPE_DEFINE'];

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

literals = ['(',')',':',',','{','}',';','='];

# 定义规则，同时做特殊处理
def t_NAME(t):
    r'[a-zA-Z][a-zA-Z0-9_]*'
    t.type = reserved.get(t.value,'NAME') 
    return t;

t_ignore = " \t"

def t_newline(t):
    r'\n+'
    t.lexer.lineno += t.value.count("\n")
    
def t_error(t):
    print("Illegal character '%s'" % t.value[0])
    t.lexer.skip(1)

lexer = lex.lex(optimize=1)
