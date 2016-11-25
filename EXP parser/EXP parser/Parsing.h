#include <iostream>
#include <string>
#include <sstream>

using namespace std;

enum TokenType
{
	Error, Plus, Minus, Mul, Div, EOT, LeftP, RightP, Number
};

class Token
{
public:
	TokenType type;
	double value;
	char symbol;
	Token();
};

class Parser
{
	Token m_crtToken;
	const char* m_Text;
	size_t m_Index;
	void Expression();
	void Expression1();
	void Term();
	void Term1();
	void Factor();
	void Match(char);
	void SkipSpaces();
	void GetNextToken();
	double GetNumber();
public:
	void Parse(const char *);
};

class ParserException : public exception
{
	int m_pos;
public:
	ParserException(const std::string& message, int pos) :
		std::exception(message.c_str()),
		m_pos(pos)
	{
	}
};

void Test(const char*);