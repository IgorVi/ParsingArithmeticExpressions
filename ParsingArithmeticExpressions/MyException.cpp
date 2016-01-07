
#include<Windows.h>

#include "MyException.h"

static HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

MyException::MyException() :
InformingAboutError(nullptr),
Expression(nullptr),
PointerToError(nullptr)
{
}

MyException::MyException(const char* InformingAboutError, const char* PointerToError, const char* Expression) : 
InformingAboutError(InformingAboutError),
PointerToError(PointerToError),
Expression(Expression)
{
}

const char * MyException::what() const
{
	return InformingAboutError;
}

void MyException::ConsoleShow() const
{
	for (unsigned int i = 0; i < strlen(Expression); ++i){
		if ((Expression + i) == PointerToError){
			SetConsoleTextAttribute(h, 0xC);
			if (Expression[i] == ' ') putchar(17);
			else {
				putchar(Expression[i]);
				++i;
			}
			SetConsoleTextAttribute(h, 0x7);
		}
		putchar(Expression[i]);
	}
	putchar('\n');
}