from ply import lex

# 空格 制表符 回车这些不可见符号都忽略
t_ignore = ' \t\r'

# 解析错误的时候直接抛出异常
def t_error(t):
    raise Exception('error {} at line {}'.format(t.value[0], t.lineno))

# 记录行号，方便出错定位
def t_newline(t):
    r'\n+'
    t.lexer.lineno += len(t.value)

# 支持c++风格的\\注释
def t_ignore_COMMENT(t):
    r'\/\/[^\n]*'

# 变量的命令规则
def t_VARIABLE(t):
    r'[a-z]+'
    return t

# 常数命令规则
def t_CONSTANT(t):
    r'[+-]?\d+(\.\d+)?'
    t.value = float(t.value)
    return t

# 输入中支持的符号头token，当然也支持t_PLUS = r'\+'的方式将加号定义为token
literals = '+-,;='
tokens = ('VARIABLE', 'CONSTANT')


if __name__ == '__main__':
    data = '''
    -x -2.4y + z = 0; //this is a comment
    9y - z + 7.2x = -1;
    y - z + x = 8
    '''

    lexer = lex.lex()
    lexer.input(data)
    while True:
        tok = lexer.token()
        if not tok:
            break
        print(tok)