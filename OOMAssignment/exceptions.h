#pragma once


class MapException
{
private:
	char* detail;
public:
	MapException()
	{
		detail = "";
	}

	MapException(char* newDetail)
	{
		detail = newDetail;
	}

	~MapException() {}

	char* what() const
	{
		return detail;
	}
};

class OutOfRangeException : public MapException
{
public:
	OutOfRangeException() {}
	OutOfRangeException(char* detail) : MapException(detail) {}
};

class UserComparisonFunctionException : public MapException
{
public:
	UserComparisonFunctionException() {}
	UserComparisonFunctionException(char* detail) : MapException(detail) {}
};