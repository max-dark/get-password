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

    static pointer load(const string &);

    ~hook();

    void initialize();

    void release();

    bool is_initialized() const;

private:
    library::pointer m_library;
    method m_init;
    method m_release;
    bool m_initialized;
};

