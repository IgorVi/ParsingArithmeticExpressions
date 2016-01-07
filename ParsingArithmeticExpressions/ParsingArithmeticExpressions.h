#pragma once

#include"Stack.h"
#include "MyException.h"

class ParsingArithmeticExpressions
{
public:
	double operator()(const char*);
	char* GetExpression();
	ParsingArithmeticExpressions();
	~ParsingArithmeticExpressions();
private:
	char *Expression;
	char *myPtr;
	Stack<char> stChar;
	Stack<double> stDou;

	void Involution();	//	���������� � �������
	void Calculation();	//	����������
	void Number();				//	��������� ����� �� ���������
	void MultiplicationDivision();		//	��������� � �������
	void AdditionSubtraction(); //	��������� � ��������
	void RemovingGapsSyntaxChecking(const char * s);// �������� �������� �������� ����������
	bool TokenTypeNumber(const char&) const;		//	��� ������� �����
	bool TokenTypeOperator(const char&) const;		//	��� ������� ��������
};

