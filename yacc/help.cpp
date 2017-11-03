// #define DEFINE_ID_HANDLE(name)	void name()
// #define DEFINE_KEYWORDS_HANDLE(name)	void name()

#define DEFINE_ID_HANDLE(name)	{name}
#define DEFINE_KEYWORDS_HANDLE(name)	#name

// end

void space_function()
{ /* this is no used , but space for sublime  */ }

template<class Function>
std::string GetDoc(const char* start, Function input_function) {
	std::string parsed(start);
	int state = 0;  // 0 = normal, 1 = "*" seen, "*/" seen
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

/* do nothing */
DEFINE_ID_HANDLE(whitespace) {}
DEFINE_ID_HANDLE(commant) {}
DEFINE_ID_HANDLE(unixcomment) {}

DEFINE_ID_HANDLE(multicm_begin) {
	std::string parsed = GetDoc("/**", yyinput);
	std::cout << parsed << std::endl;
}

DEFINE_ID_HANDLE(identifier) {
	std::cout << "identify : " << yytext << std::endl;
}

DEFINE_ID_HANDLE(intconstant) {
	long value = strtoll(yytext, NULL, 10);
	std::cout << "const int : " << value << std::endl;
}

DEFINE_ID_HANDLE(symbol) {
	std::cout << "get a symbol : " << yytext[0] << std::endl;
}

DEFINE_KEYWORDS_HANDLE(func) {
	std::cout << "key word : ""func" << std::endl;
}

DEFINE_KEYWORDS_HANDLE(int) {
	std::cout << "base type : ""int" << std::endl;
}

DEFINE_KEYWORDS_HANDLE(char) {
	std::cout << "base type : ""char" << std::endl;
}

DEFINE_KEYWORDS_HANDLE(string) {
	std::cout << "base type : ""string" << std::endl
}

DEFINE_KEYWORDS_HANDLE(double) {
	std::cout << "base type : ""double" << std::endl;
}

DEFINE_KEYWORDS_HANDLE(bin) {
	std::cout << "base type : ""bin" << std::endl;
}

DEFINE_KEYWORDS_HANDLE(struct) {
	std::cout << "key word : ""struct" << std::endl;
}

DEFINE_KEYWORDS_HANDLE(type) {
	std::cout << "key word : ""type" << std::endl;
}



