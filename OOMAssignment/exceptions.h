#pragma once

// Map exception base class
class map_exception
{
private:
	// Exception details
	char* detail;
public:
	// Default constructor
	map_exception()
	{
		detail = "";
	}

	// Constructor taking char* detail
	explicit map_exception(char* newDetail)
	{
		detail = newDetail;
	}

	// Destructor
	~map_exception() {}

	// Accessor for exception detail
	char* what() const
	{
		return detail;
	}
};

// Out of range exception class
// Inherits from map exception
class out_of_range_exception : public map_exception
{
public:
	// Default constructor
	out_of_range_exception() {}

	// Constructor taking char* detail
	explicit out_of_range_exception(char* detail) : map_exception(detail) {}
};

// User comparison function exception
// Inherits from map exception
class user_comparison_function_exception : public map_exception
{
public:
	// Default constructor
	user_comparison_function_exception() {}

	// Constructor taking char* detail
	explicit user_comparison_function_exception(char* detail) : map_exception(detail) {}
};

// Bad allocation exception
// Inherits from map exception
class bad_allocation_exception : public map_exception
{
public:
	// Default constructor
	bad_allocation_exception() {}

	// Constructor taking char* detail
	explicit bad_allocation_exception(char* detail) : map_exception(detail) {}
};

// Bad deallocation exception
// Inherits from map exception
class bad_deallocation_exception : public map_exception
{
public:
	// Default constructor
	bad_deallocation_exception() {}

	// Constructor taking char* detail
	explicit bad_deallocation_exception(char* detail) : map_exception(detail) {}
};