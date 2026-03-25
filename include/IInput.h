#pragma once
#include "EInputErrorCodes.h"
namespace Input
{
class IInput
{
  public:
    virtual ~IInput() = default;

    /**
     * @brief Retrives a char from the terminal input.
     *
     * @param o_character - the output paramater for the character inputed.
     *
     * @returns The appropriate error code.
     */
    virtual EInputErrorCodes get_char(unsigned char &o_character) const = 0;
};

}; // namespace Input