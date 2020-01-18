#pragma once
#include <exception>

using std::exception;

struct ExceptionX : public exception
{
	const char *what() const throw()
	{
		return "X of point was out of screen";
	}
};

struct ExceptionY : public exception
{
	const char *what() const throw()
	{
		return "Y of point was out of screen";
	}
};

struct ExceptionPoint : public exception
{
	const char *what() const throw()
	{
		return "Point was out of screen";
	}
};

struct ExceptionShape : public exception
{
	const char *what() const throw()
	{
		return "Wrong input of shape";
	}
};

