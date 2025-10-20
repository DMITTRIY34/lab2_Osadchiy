#pragma once
#include <iostream>

class redirect_output_wrapper
{
	std::istream& stream;
	std::streambuf* const old_buf;
public:
	redirect_output_wrapper(std::istream& src)
		:old_buf(src.rdbuf()), stream(src)
	{
	}

	~redirect_output_wrapper();

	void redirect(std::istream&);


};