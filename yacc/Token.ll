%{
/**
 * this is c files
 */
#include <iostream>
#include <string>
#include <fstream>

template<class Function>
std::string GetDoc(const char* start, Function input_function) {
    std::string parsed(start);
    int state = 0;
    while (state < 2)
    {
        int ch = input_function();
        parsed.push_back(ch);
        switch (ch) {
        case EOF:
            std::cerr << ("Unexpected end of file in doc-comment at ") << yylineno;
            exit(1);
        case '*':
            state = 1;
            break;
        case '/':
            state = (state == 1) ? 2 : 0;
            break;
        default:
            state = 0;
            break;
        }
    }
    return parsed;
}


bool ReadFile(const char* filename,std::string* out, std::string* error) {
    std::ifstream f;
    f.open(filename, std::ios::binary);
    if (!f.good()) {
        error->append("open file error.");
        return false;
    }
    f.seekg(0, std::ifstream::end);
    size_t size = (size_t)f.tellg();
    f.seekg(0, std::ifstream::beg);
    
    out->resize(size);
    auto &ref = *out;
    f.read(&ref[0], size);
    return true;
};


int yylex();

int main(int argc, char const *argv[])
{
    yylex();
    return 0;
}

%}


/**
 * Provides the yylineno global, useful for debugging output
 */
%option lex-compat

/**
 * Our inputs are all single files, so no need for yywrap
 */
%option noyywrap

/**
 * We don't use it, and it fires up warnings at -Wall
 */
%option nounput


/**
 * Helper definitions, comments, constants, and whatnot
 */

/* const values */
intconstant   ([+-]?[0-9]+)

/* identify */
identifier    ([a-zA-Z_](\.[a-zA-Z_0-9]|[a-zA-Z_0-9])*)
 
whitespace    ([ \t\r\n]*)

multicm_begin ("/*")
comment       ("//"[^\n]*)
unixcomment   ("#"[^\n]*)

symbol        ([\(\):;,=\{\}])

%%

{whitespace} {}
{comment} {}
{unixcomment} {}

{multicm_begin} {
    std::string parsed = GetDoc("/**", yyinput);
    std::cout << "document : " << parsed << std::endl;
}


{intconstant} {
    long value = strtoll(yytext, NULL, 10);
    std::cout << "const int : " << value << std::endl;
}

{symbol} {
    std::cout << "get a symbol : " << yytext[0] << std::endl;
}

"func" {
    std::cout << "key word : ""func" << std::endl;
}

"int" {
    std::cout << "base type : ""int" << std::endl;
}

"char" {
    std::cout << "base type : ""char" << std::endl;
}

"string" {
    std::cout << "base type : ""string" << std::endl;
}

"double" {
    std::cout << "base type : ""double" << std::endl;
}

"bin" {
    std::cout << "base type : ""bin" << std::endl;
}

"struct" {
    std::cout << "key word : ""struct" << std::endl;
}

"type" {
    std::cout << "key word : ""type" << std::endl;
}

{identifier} {
    std::cout << "identify : " << yytext << std::endl;
}

%%
