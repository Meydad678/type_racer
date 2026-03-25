#include "Color.h"
#include "ColorCodes.h"
#include "TerminalInput.h"
#include "TerminalOutput.h"
#include <chrono>
#include <iostream>
#include <stdio.h>
#include <termios.h>
#include <thread>
#include <unistd.h>
#include "SentenceFetcher.h"

constexpr uint16_t GAME_SESSION_DURATION_IN_SECONDS = 5;
constexpr uint16_t LOOP_SLEEP_DURATION_IN_MILLISECONDS = 5;
constexpr uint16_t NUMBER_OF_CHARS_IN_ONE_LETTER = 1;
constexpr unsigned char DEFAULT_INPUT_CHAR = EOF;

int main()
{
    unsigned char input_char = DEFAULT_INPUT_CHAR;
    Input::EInputErrorCodes error_code = Input::EInputErrorCodes::FAILURE;

    const Output::IOutput &outout = Output::TerminalOutput();
    const Input::IInput &input = Input::TerminalInput();
    Colors::ColorCodes color_codes;
    Colors::Color red_color = Colors::Color(color_codes.RED);

    Sentences::SentenceFetcher sentence_fetcher;
    std::string target_sentence {};
    sentence_fetcher.get_sentence(target_sentence);
    std::cout << "Try to write: " << target_sentence << std::endl;

    const std::chrono::seconds duration(GAME_SESSION_DURATION_IN_SECONDS);
    std::chrono::steady_clock::time_point start_time = std::chrono::steady_clock::now();
    while (std::chrono::steady_clock::now() - start_time < duration)
    {
        error_code = input.get_char(input_char);
        if (error_code != Input::EInputErrorCodes::SUCCESS)
        {
            return EXIT_FAILURE;
        }
        std::string input_char_string(NUMBER_OF_CHARS_IN_ONE_LETTER, input_char);
        outout.render(input_char_string, red_color);

        std::this_thread::sleep_for(std::chrono::milliseconds(LOOP_SLEEP_DURATION_IN_MILLISECONDS));
    }

    std::cout << "Loop finished after time duration." << std::endl;
    return EXIT_SUCCESS;
}