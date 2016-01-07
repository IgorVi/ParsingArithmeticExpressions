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

	void Involution();	//	возведение в степень
	void Calculation();	//	вычисление
	void Number();				//	считывает число из выражения
	void MultiplicationDivision();		//	Умножение и деление
	void AdditionSubtraction(); //	вычитание и сложение
	void RemovingGapsSyntaxChecking(const char * s);// удаление пробелов проверка синтаксиса
	bool TokenTypeNumber(const char&) const;		//	тип лексемы число
	bool TokenTypeOperator(const char&) const;		//	тип лексемы оператор
};

