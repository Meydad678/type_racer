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
    mutable struct termios m_old_terminal_io_settings;

    /**
     * @brief enables instant key input from the terminal.
     */
    void enable_instant_key_input() const;

    /**
     * @brief disables instant key input from the terminal.
     */
    void disable_instant_key_input() const;

    /**
     * @brief clears stdin.
     */
    void clear_stdin() const;

  public:
    /**
     * @brief This c'tor enables us to recive the keys as soon as they are pressed.
     * It keeps the old terminal io settings in a member.
     */
    TerminalInput();

    /**
     * @brief This d'tor disables the reciving of keys as soon as they are pressed.
     */
    ~TerminalInput();

    /**
     * @brief Retrives a char from the terminal input instantly.
     *
     * @param o_character - the output paramater for the character inputed.
     *
     * @returns The appropriate error code.
     */
    EInputErrorCodes get_char(unsigned char &o_character) const override;

    /**
     * @brief Retrives a char from the terminal input after ENTER was pressed.
     *
     * @param o_character - the output paramater for the character inputed.
     *
     * @returns The appropriate error code.
     */
    EInputErrorCodes get_confirmed_char(unsigned char &o_character) const override;
};
}; // namespace Input