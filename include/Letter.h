#pragma once
#include "LetterState.h"

namespace Letters
{
struct Letter
{
    Assessment::LetterState state;
    unsigned char character;
};

}; // namespace Letters