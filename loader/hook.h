#pragma once

#include <windows.h>
#include <memory>
#include <string>
#include "library.h"

class hook {
    using method = void (*)(HINSTANCE);

    hook() = delete;

    hook(library::pointer &&, method init, method release);

public:
    using pointer = std::shared_ptr<hook>;
    using string = std::string;

    pointer setup(const string &);

    ~hook();

private:
    library::pointer m_library;
    method m_init, m_release;
};

