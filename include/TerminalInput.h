#pragma once
#include "EInputErrorCodes.h"
#include "IInput.h"
#include <iostream>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
namespace Input
{
class TerminalInput : public IInput
{
  private:
    struct termios m_old_terminal_io_settings;

  public:
    /**
     * @brief This c'tor enables us to recive the keys as soon as they are pressed.
     * It keeps the old
     */
    TerminalInput();

    /**
     * @brief This d'tor disables the reciving of keys as soon as they are pressed.
     */
    ~TerminalInput();

    /**
     * @brief Retrives a char from the terminal input.
     *
     * @param o_character - the output paramater for the character inputed.
     *
     * @returns The appropriate error code.
     */
    EInputErrorCodes get_char(unsigned char &o_character) const override;
};
}; // namespace Input