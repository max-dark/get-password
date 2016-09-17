#include "library.h"

library::library(HMODULE instance) : m_instance(instance) {
}

library::pointer library::load(const string &file_name) {
    HMODULE instance = LoadLibraryA(file_name.c_str());
    if (!instance) {
        throw LoadFailException(file_name);
    }
    return pointer(new library(instance));
}

HMODULE library::module() const { return m_instance; }

library::~library() {
    FreeLibrary(m_instance);
}

library::LoadFailException::LoadFailException(const string &message) : std::runtime_error(message + " load failed") {
}

library::MethodNotFoundException::MethodNotFoundException(const string &message) : std::runtime_error(
        "Method [" + message + "] not found") {
}
