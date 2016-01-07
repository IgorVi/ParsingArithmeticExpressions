#include<iostream>
#include<cmath>

#include "ParsingArithmeticExpressions.h"


ParsingArithmeticExpressions::ParsingArithmeticExpressions()
{
	myPtr = nullptr;
	Expression = nullptr;
}

ParsingArithmeticExpressions::~ParsingArithmeticExpressions()
{
	if (Expression != nullptr){
		delete[] Expression;
	}
}

void ParsingArithmeticExpressions::Number()
{
	if (TokenTypeNumber(*myPtr)){
		double rez = 0.0;
		int index = 0;

		bool flag = false;
		while (*myPtr && (TokenTypeNumber(*myPtr))){
			if (*myPtr == ','){
				if (flag) throw MyException("������. ������������ ������ ���������� �����.", myPtr, Expression + 1); // ���� ��� �������
				flag = true;
			}
			myPtr--;
		}
		rez = atof(myPtr + 1);

		stDou.Push(rez);
	}
}

double ParsingArithmeticExpressions::operator()(const char* str)
{
	if (!stDou.IsEmpty())
		stDou.Clear();

	if (!stChar.IsEmpty())
		stChar.Clear();

	if (Expression != nullptr){
		delete[] Expression;
	}

	RemovingGapsSyntaxChecking(str);

	Calculation();
	
	double rez = 0.0;

	if (!stDou.IsEmpty())
		rez = stDou.Pop();

	return rez;
}

void ParsingArithmeticExpressions::Calculation()
{
	while (*myPtr)
	{
		if (*myPtr == ')'){
			stChar.Push(*myPtr);
			--myPtr;
			Calculation();
		}
		else if (*myPtr == '('){
			--myPtr;
			break;
		}
		else if (TokenTypeNumber(*myPtr)){
			Number();
			if (!TokenTypeOperator(*myPtr)){
				if (stChar.Peek() == ')') throw MyException("������. ����� ����������� � ����������� ������� ����������� ���������.", myPtr, Expression + 1);
				else throw MyException("������. ����������� ���������.", nullptr, Expression + 1);
			}
		}

		else if (*myPtr == '+' || *myPtr == '-'){
			MultiplicationDivision();
			stChar.Push(*myPtr);
			--myPtr;
			Number();
		}

		else if (*myPtr == '*' || *myPtr == '/' || *myPtr == '^'){
			stChar.Push(*myPtr);
			--myPtr;
			Number();
		}
	}
	MultiplicationDivision();
	AdditionSubtraction();
}

void ParsingArithmeticExpressions::MultiplicationDivision()
{
	double tmp1 = 0.0;
	double tmp2 = 0.0;

	while (stChar.Peek() == '*' || stChar.Peek() == '/' || stChar.Peek() == '^'){
		switch (stChar.Pop()){
		case'/':
			tmp1 = stDou.Pop();
			tmp2 = stDou.Pop();
			if (tmp2 == 0) throw MyException("������. ������� �� ����.", myPtr + 1, Expression + 1);
			stDou.Push(tmp1 / tmp2);
			break;
		case'*':
			tmp1 = stDou.Pop();
			tmp2 = stDou.Pop();
			stDou.Push(tmp1 * tmp2);
			break;
		case '^':
			Involution();
			break;
		}
	}
}

void ParsingArithmeticExpressions::AdditionSubtraction()
{
	double tmp = 0.0;
	while(!stChar.IsEmpty()){
		switch (stChar.Pop())
		{
			case '+':
				stDou.Push(stDou.Pop() + stDou.Pop());
			break;
			case '-':
				tmp = stDou.Pop();
				stDou.Push(tmp - stDou.Pop());
				break;
			case ')':
				return;
		}			
	}
}

void ParsingArithmeticExpressions::RemovingGapsSyntaxChecking(const char * s)	// �������� �������� �������� ����������
{
	if (!*s) throw MyException("������, ��������� ������.", nullptr, ""); // ���� ������ �����

	int size = strlen(s);
	
	Expression = new char[size + 2 + size / 4];

	Expression[0] = '\0';
	int i, j;
	for (i = 0, j = 1; i < size; ++i, ++j){
		if (s[i] == ' ') {
			--j;
			if (TokenTypeNumber(Expression[j]) && TokenTypeNumber(s[i + 1])){
				throw MyException("������. ����������� ���� ��������.", s + i, s);
			}
			continue;
		}
		
		if (s[i] == '('){
			stChar.Push(s[i]);
		}
		else if (s[i] == ')'){
			if (!stChar.IsEmpty())	stChar.Pop();
			else if (j != 1) throw MyException("������. � ��������� ���������� ����������� ������.", s + i, s);
		}

		if (Expression[j - 1] == '('){
			if (s[i] == '-'){
				Expression[j] = '0';
				i--;
				continue;
			}
			else if (s[i] == '+'){ ++i; --j; continue; }
		}
		Expression[j] = s[i];

		if (Expression[j - 1] == '(' && s[i] == ')'){
			throw MyException("������. ����������� ���������.", s + i, s);
		}

		if (Expression[j - 1] == ')' && s[i] == '('){
			throw MyException("������. ����������� ���� �������� ��������.", s + i, s);
		}

		if (Expression[1] == ')'){
			throw MyException("������. ��������� ���������� � ����������� ������.", s + i, s);
		}

		if (TokenTypeNumber(Expression[j]) && Expression[j - 1] == ')'){
			throw MyException("������. ����� ����������� ������� � ������ ����������� ���� �������� ��������.", s + i, s);
		}

		if (TokenTypeNumber(Expression[j - 1]) && Expression[j] == '('){
				throw MyException("������. ����� ������ � ����������� ������� ����������� ���� ��������.", s + i, s);
		}

		
		if (!TokenTypeNumber(Expression[j])){
			if (Expression[j] != '('){
				if (!TokenTypeOperator(Expression[j]) && Expression[j] != ')'){
					throw MyException("������. ������������ ������ � ���������.", s + i, s);
				}

				if (Expression[j - 1] == '(' && Expression[j] != '-' && Expression[j] != '+'){
					throw MyException("������. ����� ����������� ������ ������� ���� ���� �������� ��������.", s + i, s);
				}
			}
		}

		if (!TokenTypeNumber(Expression[j - 1])){
			if (Expression[j - 1] != ')'){
				if (Expression[j] == ')'){
					throw MyException("������. ���� ����������� ������� ������� ���� ���� �������� ��������.", s + i - 1, s);
				}
				if (TokenTypeOperator(Expression[j]))
					if (Expression[j - 1] != '(' && j != 1){
					throw MyException("������. � ��������� ������ ���� ��� ����� ��������.", s + i, s);
					}
			}
		}

		/*
		if (Expression[1] == ')') throw MyException("������. ��������� ���������� � ����������� ������.", s + i, s);

		if (TokenTypeNumber(Expression[j]) && Expression[j - 1] == ')') throw MyException("������. ����� ����������� ������� � ������ ����������� ���� �������� ��������..", s + i, s);

		if (TokenTypeNumber(Expression[j - 1]) && Expression[j] == '(') throw MyException("������. ����� ������ � ����������� ������� ����������� ���� ��������.", s + i, s);

		if (!TokenTypeNumber(Expression[j]) && !TokenTypeOperator(Expression[j]) && Expression[j] != '(' && Expression[j] != ')') throw MyException("������. ������������ ������ � ���������.", s + i, s);

		if (Expression[j - 1] == '('&& Expression[j] != '(' && Expression[j] != '-' && Expression[j] != '+' && !TokenTypeNumber(Expression[j])) throw MyException("������. ����� ����������� ������ ������� ���� ���� �������� ��������.", s + i, s);

		if (Expression[j] == ')' && Expression[j - 1] != ')' && !TokenTypeNumber(Expression[j - 1])) throw MyException("������. ���� ����������� ������� ������� ���� ���� �������� ��������.", s + i - 1, s);

		if (TokenTypeOperator(Expression[j]))
			if (Expression[j - 1] != ')' && Expression[j - 1] != '(' && !TokenTypeNumber(Expression[j - 1]) && j != 1)	throw MyException("������. � ��������� ������ ���� ��� ����� ��������.", s + i, s);
*/
	}

	Expression[j] = '\0';
	myPtr = &Expression[j - 1];

	if (Expression == nullptr || Expression[1] == '\0'){
		throw MyException("������. ��������� ������.", nullptr, "");
	}

	if (!TokenTypeNumber(Expression[1]) && Expression[1] != '('){
		throw MyException("������. ��������� ���������� �� ����� �������� ��������.", Expression + 1, Expression + 1);
	}

	if (!TokenTypeNumber(Expression[j - 1]) && Expression[j - 1] != ')'){
		throw MyException("������. ��������� ������������� ������ �������� ��������.", (s + i - 1), s);
	}

	if (!stChar.IsEmpty()){
		throw MyException("������. ���������� ����������� ������.", s + i - 1, s);
	}
}

char* ParsingArithmeticExpressions::GetExpression()
{
	if (Expression == nullptr)
		return "";

	return &Expression[1];
}

bool ParsingArithmeticExpressions::TokenTypeNumber(const char& character) const
{
	return (character >= '0' && character <= '9' || character == ',');
}

bool ParsingArithmeticExpressions::TokenTypeOperator(const char& character) const
{
	return (character == '+' || character == '-' || character == '*' || character == '/' || character == '^');
}

void ParsingArithmeticExpressions::Involution()
{
	double tmp1 = stDou.Pop(), tmp2 = stDou.Pop(), rez = 0.0;

	if (tmp2 < 0) throw MyException("������. ����������� � ������� �������������� �����.", nullptr, Expression + 1);

	if (tmp2 == 0) stDou.Push(1);

	stDou.Push(pow(tmp1, tmp2));
}