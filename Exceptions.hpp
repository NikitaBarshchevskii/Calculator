#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include <exception>

class StackOverflow : public std::exception
{
public:
	StackOverflow() :
		reason_("Stack Overflow")
	{
	}
	const char* what() const noexcept override
	{
		return reason_;
	}
private:
	const char* reason_;
};

class StackUnderflow : public std::exception
{
public:
	StackUnderflow() :
		reason_("Stack Underflow")
	{
	}
	const char* what() const noexcept override
	{
		return reason_;
	}
private:
	const char* reason_;
};

class WrongStackSize : public std::exception
{
public:
	WrongStackSize() :
		reason_("Wrong stack size")
	{
	}
	const char* what() const noexcept override
	{
		return reason_;
	}
private:
	const char* reason_;
};
#endif

