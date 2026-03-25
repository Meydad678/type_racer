#include "TerminalInput.h"
#include "EInputErrorCodes.h"
Input::TerminalInput::TerminalInput()
{
    struct termios old_terminal_io_settings, new_terminal_io_settings;

    /* get the terminal settings for stdin */
    tcgetattr(STDIN_FILENO, &old_terminal_io_settings);

    /* we want to keep the old setting to restore them a the end */
    new_terminal_io_settings = old_terminal_io_settings;

    /* disable canonical mode (buffered i/o) and local echo */
    new_terminal_io_settings.c_lflag &= (~ICANON & ~ECHO);

    /* set the new settings immediately */
    tcsetattr(STDIN_FILENO, TCSANOW, &new_terminal_io_settings);

    m_old_terminal_io_settings = old_terminal_io_settings;
}

Input::TerminalInput::~TerminalInput()
{
    /* Restore the terminal settings to the regular ones.*/
    tcsetattr(STDIN_FILENO, TCSANOW, &m_old_terminal_io_settings);
}

Input::EInputErrorCodes Input::TerminalInput::get_char(unsigned char &o_character) const
{
    o_character = getchar();
    if (o_character == EOF)
    {
        return Input::EInputErrorCodes::FAILURE;
    }
    return Input::EInputErrorCodes::SUCCESS;
}