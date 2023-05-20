#include "Chess/Defines.hpp"

namespace Chess
{
    const char* excLogicalError::what() const noexcept
    {
        return "Detecting a logical error in code";
    }
}
