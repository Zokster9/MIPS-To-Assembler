#include "SyntaxAnalysis.h"
#include "Constants.h"
#include <iostream>
#include <iomanip>

using namespace std;

SyntaxAnalysis::SyntaxAnalysis(LexicalAnalysis& lex, Function& function) : lexicalAnalysis(lex), f(function), 
errorFound(false), tokenIterator(lexicalAnalysis.getTokenList().begin()) 
{
}

Token SyntaxAnalysis::getNextToken()
{
	if (tokenIterator == lexicalAnalysis.getTokenList().end())
		throw std::runtime_error("End of input file reached");
	return *tokenIterator++;
}

bool SyntaxAnalysis::Do()
{
	currentToken = getNextToken();

	Q();

	return !errorFound;
}

void SyntaxAnalysis::printSyntaxError(Token token)
{
	cout << "Syntax error! Token: " << token.getValue() << " unexpected" << endl;
}

void SyntaxAnalysis::printTokenInfo(Token token)
{
	std::cout << setw(LEFT_ALIGN) << left << token.tokenTypeToString(token.getType());
	cout << setw(RIGHT_ALIGN) << right << token.getValue() << endl;
}

void SyntaxAnalysis::eat(TokenType t)
{
	if (errorFound == false)
	{
		if (currentToken.getType() == t)
		{
			cout << currentToken.getValue() << endl;
			if (t == T_FUNC)
			{
				currentToken = getNextToken();
				f.set_name(currentToken.getValue());
			}
			else if (t != T_END_OF_FILE)
			{
				currentToken = getNextToken();
			}

		}
		else
		{
			printSyntaxError(currentToken);
			errorFound = true;
		}
	}
}

void SyntaxAnalysis::Q()
{
	if (!errorFound)
	{
		S();
		eat(T_SEMI_COL);
		L();
	}
}

void SyntaxAnalysis::S()
{
	if (!errorFound)
	{
		switch (currentToken.getType())
		{
		case T_MEM:
			eat(T_MEM);
			eat(T_M_ID);
			eat(T_NUM);
			break;
		case T_REG:
			eat(T_REG);
			eat(T_R_ID);
			break;
		case T_FUNC:
			eat(T_FUNC);
			eat(T_ID);
			break;
		case T_ID:
			eat(T_ID);
			eat(T_COL);
			E();
			break;
		default:
			E();
			break;
		}
	}
}

void SyntaxAnalysis::L()
{
	if (!errorFound)
	{
		if (currentToken.getType() == T_END_OF_FILE)
			eat(T_END_OF_FILE);
		else
			Q();
	}
}

void SyntaxAnalysis::E()
{
	if (!errorFound)
	{
		switch (currentToken.getType())
		{
		case T_ADD:
			eat(T_ADD);
			eat(T_R_ID);
			eat(T_COMMA);
			eat(T_R_ID);
			eat(T_COMMA);
			eat(T_R_ID);
			break;
		case T_ADDI:
			eat(T_ADDI);
			eat(T_R_ID);
			eat(T_COMMA);
			eat(T_R_ID);
			eat(T_COMMA);
			eat(T_NUM);
			break;
		case T_SUB:
			eat(T_SUB);
			eat(T_R_ID);
			eat(T_COMMA);
			eat(T_R_ID);
			eat(T_COMMA);
			eat(T_R_ID);
			break;
		case T_LA:
			eat(T_LA);
			eat(T_R_ID);
			eat(T_COMMA);
			eat(T_M_ID);
			break;
		case T_LW:
			eat(T_LW);
			eat(T_R_ID);
			eat(T_COMMA);
			eat(T_NUM);
			eat(T_L_PARENT);
			eat(T_R_ID);
			eat(T_R_PARENT);
			break;
		case T_LI:
			eat(T_LI);
			eat(T_R_ID);
			eat(T_COMMA);
			eat(T_NUM);
			break;
		case T_SW:
			eat(T_SW);
			eat(T_R_ID);
			eat(T_COMMA);
			eat(T_NUM);
			eat(T_L_PARENT);
			eat(T_R_ID);
			eat(T_R_PARENT);
			break;
		case T_B:
			eat(T_B);
			eat(T_ID);
			break;
		case T_BLTZ:
			eat(T_BLTZ);
			eat(T_R_ID);
			eat(T_COMMA);
			eat(T_ID);
			break;
		default:
			eat(T_NOP);
			break;
		}
	}
}
