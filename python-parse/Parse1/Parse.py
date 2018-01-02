import ply.yacc as yacc
import logging;

# Get the token map from the lexer.  This is required.
from calc_token import *;
import calc_token;

# this is a function to debug
def PrintTokens(data,lex ):
    PrintTokens = True
    lex.input(data)
    if PrintTokens == True :
        lex.input(data)
        errorOccr = False;
        while True:
            tok = lex.token()
            if not tok:
                errorOccr = False;
                print("error occr")
                break
            print(tok)
        if errorOccr:
            print("token parse ok!");
    print("============================")

# dictionary of names
names = { }

def p_statement_assign(p):
    'statement : NAME ASSIGN expression'
    names[p[1]] = p[3]
    p[0] = p[3];
    # print(p[3]);

def p_statement_expr(p):
    'statement : expression'
    # print(p[1])
    # return p[1];
    p[0] = p[1];

def p_expression_plus(p):
    'expression : expression PLUS term'
    p[0] = p[1] + p[3]

def p_expression_minus(p):
    'expression : expression MINUS term'
    p[0] = p[1] - p[3]

def p_expression_term(p):
    'expression : term'
    p[0] = p[1]

def p_term_times(p):
    'term : term TIMES factor'
    p[0] = p[1] * p[3]

def p_term_div(p):
    'term : term DIVIDE factor'
    p[0] = p[1] / p[3]

def p_term_factor(p):
    'term : factor'
    p[0] = p[1]

def p_factor_num(p):
    'factor : NUMBER'
    p[0] = p[1]

def p_factor_expr(p):
    'factor : LPAREN expression RPAREN'
    p[0] = p[2]

def p_expression_name(p):
    "factor : NAME"
    try:
        p[0] = names[p[1]]
    except LookupError:
        print("Undefined name '%s'" % p[1])
        p[0] = 0

# Error rule for syntax errors
def p_error(p):
    print("Syntax error in input!")

# Build the parser
parser = yacc.yacc()

log = logging.getLogger()

data = '''
1 + 1
'''

PrintTokens(data,calc_token.lexer);

# result = parser.parse(data,debug=log)
# print(result)

while 1:
    try:
        s = input('calc > ')
    except EOFError:
        break
    if not s: continue
    result = yacc.parse(s,debug=log)
    print(result);