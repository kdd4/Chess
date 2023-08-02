#pragma once

#include <exception>

namespace Chess
{
    struct excLogicalError : public std::exception
    {
        const char* what() const noexcept override;
    };
}

