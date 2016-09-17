#include "hook.h"

hook::hook(library::pointer &&lib, method init, method release)
        : m_library(std::move(lib)), m_init(init), m_release(release), m_initialized(false) {
}

void hook::initialize() {
    if (!m_initialized) {
        m_init(m_library->module());
        m_initialized = true;
    }
}


hook::pointer hook::load(const string &file_name) {
    method init, release;
    library::pointer lib = library::load(file_name);
    init = lib->get<method>("Init");
    release = lib->get<method>("Release");
    return pointer(new hook(std::move(lib), init, release));
}

hook::~hook() {
    release();
}

void hook::release() {
    if (m_initialized) {
        m_release(m_library->module());
        m_initialized = false;
    }
}

bool hook::is_initialized() const { return m_initialized; }
