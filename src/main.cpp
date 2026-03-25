#include "TerminalInput.h"
#include <chrono>
#include <iostream>
#include <stdio.h>
#include <termios.h>
#include <thread>
#include <unistd.h>
#
constexpr uint16_t GAME_SESSION_DURATION_IN_SECONDS = 5;
constexpr uint16_t LOOP_SLEEP_DURATION_IN_MILLISECONDS = 5;
constexpr unsigned char DEFAULT_INPUT_CHAR = EOF;

int main()
{
    const std::chrono::seconds duration(GAME_SESSION_DURATION_IN_SECONDS);
    unsigned char input_char = DEFAULT_INPUT_CHAR;
    Input::EInputErrorCodes error_code = Input::EInputErrorCodes::FAILURE;

    const Input::IInput &input = Input::TerminalInput();

    std::chrono::steady_clock::time_point start_time = std::chrono::steady_clock::now();
    while (std::chrono::steady_clock::now() - start_time < duration)
    {
        error_code = input.get_char(input_char);
        if (error_code != Input::EInputErrorCodes::SUCCESS)
        {
            return EXIT_FAILURE;
        }
        printf("%c ", input_char);

        std::this_thread::sleep_for(std::chrono::milliseconds(LOOP_SLEEP_DURATION_IN_MILLISECONDS));
    }

    std::cout << "Loop finished after time duration." << std::endl;

    return EXIT_SUCCESS;
}