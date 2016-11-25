#include "Parsing.h"

Token::Token()
{
	type = Error, value = 0, symbol = 0;
}

void Parser::Expression()
{
	Term();
	Expression1();
}

void Parser::Expression1()
{
	switch (m_crtToken.type)
	{
	case Plus:
		GetNextToken();
		Term();
		Expression1();
		break;
	case Minus:
		GetNextToken();
		Term();
		Expression1();
		break;
	}
}

void Parser::Term()
{
	Factor();
	Term1();
}

void Parser::Term1()
{
	switch (m_crtToken.type)
	{
	case Mul:
		GetNextToken();
		Factor();
		Term1();
		break;

	case Div:
		GetNextToken();
		Factor();
		Term1();
		break;
	}
}

void Parser::Factor()
{
	switch (m_crtToken.type)
	{
	case LeftP:
		GetNextToken();
		Expression();
		Match(')');
		break;

	case Minus:
		GetNextToken();
		Factor();
		break;

	case Number:
		GetNextToken();
		break;

	default:
	{
		std::stringstream sstr;
		sstr << "Unexpected token '" << m_crtToken.symbol << "' at position " << m_Index;
		throw ParserException(sstr.str(), m_Index);
	}
	}
}

void Parser::Match(char expected)
{
	if (m_Text[m_Index - 1] == expected)
		GetNextToken();
	else
	{
		std::stringstream sstr;
		sstr << "Expected token '" << expected << "' at position " << m_Index;
		throw ParserException(sstr.str(), m_Index);
	}
}

void Parser::SkipSpaces()
{
	while (isspace(m_Text[m_Index]))
		m_Index++;
}

void Parser::GetNextToken()
{
	SkipSpaces();
	m_crtToken.value = 0, m_crtToken.symbol = 0;
	if (m_Text[m_Index] == 0)
	{
		m_crtToken.type = EOT;
		return;
	}
	if (isdigit(m_Text[m_Index]))
	{
		m_crtToken.type = Number;
		m_crtToken.value = GetNumber();
		return;
	}
	m_crtToken.type = Error;
	switch (m_Text[m_Index])
	{
	case '+':
		m_crtToken.type = Plus;
		break;
	case '-':
		m_crtToken.type = Minus;
		break;
	case '*':
		m_crtToken.type = Mul;
		break;
	case '/':
		m_crtToken.type = Div;
		break;
	case '(':
		m_crtToken.type = LeftP;
		break;
	case ')':
		m_crtToken.type = RightP;
		break;
	}
	if (m_crtToken.type != Error)
	{
		m_crtToken.symbol = m_Text[m_Index];
		m_Index++;
	}
	else
	{
		std::stringstream sstr;
		sstr << "Unexpected token '" << m_Text[m_Index] << "' at position " << m_Index;
		throw ParserException(sstr.str(), m_Index);
	}
}

double Parser::GetNumber()
{
	SkipSpaces();
	int index = m_Index;
	while (isdigit(m_Text[m_Index]))
		m_Index++;
	if (m_Text[m_Index] == '.')
		m_Index++;
	while (isdigit(m_Text[m_Index]))
		m_Index++;
	if (m_Index - index == 0)
		throw ParserException("Number expected but not found!", m_Index);
	char buffer[32] = { 0 };
	memcpy(buffer, &m_Text[index], m_Index - index);
	return atof(buffer);
}

void Parser::Parse(const char* text)
{
	m_Text = text, m_Index = 0;
	GetNextToken();
	Expression();
}

void Test(const char* text)
{
	Parser parser;
	try
	{
		parser.Parse(text);
		cout << '"' << text << '"' << "\t OK\n";
	}
	catch (const std::exception& ex)
	{
		cout << '"' << text << '"' << "\t" << ex.what() << endl;
	}
}