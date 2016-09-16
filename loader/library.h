#pragma once

#include <windows.h>
#include <string>
#include <memory>

class library {
    library() = delete;

    library(const library &) = delete;

    library(library &&) = delete;

protected:
    library(HMODULE);

public:
    class LoadFailException;

    class MethodNotFoundException;

    using string = std::string;
    using pointer = std::unique_ptr<library>;

    static pointer load(const string &);

    ~library();

    template<class type>
    type get(const string &name) {
        type ptr = reinterpret_cast<type>(
                GetProcAddress(m_instance, name.c_str())
        );
        if (nullptr == ptr) {
            throw MethodNotFoundException(name);
        }
        return ptr;
    }

    HMODULE module() const { return m_instance; }

private:
    HMODULE m_instance;
};

class library::LoadFailException : public std::runtime_error {
public:
    LoadFailException(const string &message);
};

class library::MethodNotFoundException : public std::runtime_error {
public:
    MethodNotFoundException(const string &message);
};

