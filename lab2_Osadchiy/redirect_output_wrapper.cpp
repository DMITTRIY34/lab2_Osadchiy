#include "redirect_output_wrapper.h"

redirect_output_wrapper::~redirect_output_wrapper()
{
	stream.rdbuf(old_buf);
}

void redirect_output_wrapper::redirect(std::istream& dest)
{
	stream.rdbuf(dest.rdbuf());
}