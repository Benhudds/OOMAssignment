#pragma once


class map_exception
{
private:
	char* detail;
public:
	map_exception()
	{
		detail = "";
	}

	explicit map_exception(char* newDetail)
	{
		detail = newDetail;
	}

	~map_exception() {}

	char* what() const
	{
		return detail;
	}
};

class out_of_range_exception : public map_exception
{
public:
	out_of_range_exception() {}
	explicit out_of_range_exception(char* detail) : map_exception(detail) {}
};

class user_comparison_function_exception : public map_exception
{
public:
	user_comparison_function_exception() {}
	explicit user_comparison_function_exception(char* detail) : map_exception(detail) {}
};