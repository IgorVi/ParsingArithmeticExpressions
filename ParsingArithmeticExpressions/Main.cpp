#include<typeinfo>
#include<iostream>
#include<Windows.h>

#include"ParsingArithmeticExpressions.h"

int main()
{
	setlocale(LC_ALL, "Russian");

	ParsingArithmeticExpressions tmp;

	double rez = 0.0;
	char *sPtr = " ( - 4,5) -(3-(+ 2 *  6) / 3 + 10 )  + 5  ";//" 1+ 4 / (2 * 5  ) -2 ";//" (5- ( (-3) ^ 2 )) ";//"(-6787)-(78-68)";//" 4 -  (-2/ (2 *  4)) + 3 ";//
	std::cout << sPtr << std::endl;

	try{
		rez = tmp(sPtr);
	}catch (std::exception & exception){
		if (typeid(exception) == typeid(MyException)){
			system("cls");
			MyException & my_exception = dynamic_cast<MyException &>(exception);
			my_exception.ConsoleShow();
		}

		HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(h, 0xC);
		std::cout << exception.what() << std::endl;
		SetConsoleTextAttribute(h, 0x7);
	}

	std::cout << tmp.GetExpression() << std::endl;
	std::cout << rez << std::endl;
}