#pragma once

#include<iostream>

class MyException : public std::exception
{
	const char* InformingAboutError;
	const char* PointerToError;
	const char* Expression;
	MyException();
public:
	MyException(const char* InformingAboutError, const char* PointerToError, const char* Expression);
	void ConsoleShow() const;
	const char * what() const;
};

