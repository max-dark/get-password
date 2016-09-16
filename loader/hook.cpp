#include "hook.h"



hook::hook(library::pointer&& lib, method init, method release)
	:m_library(std::move(lib)),m_init(init), m_release(release)
{
	m_init(m_library->module());
}


hook::pointer hook::setup(const string & file_name)
{
	method init, release;
	library::pointer lib = library::load(file_name);
	init = lib->get<method>("Init");
	release = lib->get<method>("Release");
	return pointer(new hook(std::move(lib), init, release));
}

hook::~hook()
{
	m_release(m_library->module());
}
