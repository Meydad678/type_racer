#pragma once

#include "Color.h"
#include "ColorCodes.h"
#include "EGameSessionErrorCode.h"
#include "GameSession.h"
#include "Letter.h"
#include "LetterAssessor.h"
#include "SentenceFetcher.h"
#include "TerminalInput.h"
#include "TerminalOutput.h"
#include <chrono>
#include <iostream>
#include <stdio.h>
#include <termios.h>
#include <thread>
#include <unistd.h>

namespace Game
{

class GameSession
{
  private:
    static constexpr uint16_t GAME_SESSION_DURATION_IN_SECONDS = 5;
    static constexpr uint16_t LOOP_SLEEP_DURATION_IN_MILLISECONDS = 5;
    static constexpr uint16_t NUMBER_OF_CHARS_IN_ONE_LETTER = 1;
    static constexpr unsigned char DEFAULT_INPUT_CHAR = EOF;
    static constexpr Assessment::LetterState DEFAULT_LETTER_STATE =
        Assessment::LetterState::UNTYPED;
    Colors::ColorCodes color_codes;
    Colors::Color DEFAULT_COLOR{color_codes.RESET};

    const Output::IOutput &m_output;
    const Input::IInput &m_input;
    const Assessment::IRuleAssessor &m_assessor;
    Sentences::SentenceFetcher m_sentence_fetcher;

    /**
     * @brief This function initializes the letters vector.
     * It pushes in the vector the characters of the string, with the default state.
     *
     * @param sentence - the string we push into the letters vector.
     *
     * @returns the letters vector.
     */
    std::vector<Letters::Letter> initialize_letters_vector(std::string &sentence);

    /**
     * @brief iterates over the vector and returns if one of the letters' state is UNTYPED.
     */
    bool is_fully_typed(std::vector<Letters::Letter> &letters);

    /**
     * @brief this function iterates over the vector and renders the letters.
     *
     * @return the appropiate error code.
     */
    EGameSessionErrorCode render_letters(std::vector<Letters::Letter> letters);

  public:
    GameSession(const Output::IOutput &output, const Input::IInput &input,
                const Assessment::IRuleAssessor &assessor,
                Sentences::SentenceFetcher &sentence_fetcher);
    ~GameSession();

    /**
     * @brief runs the game session. Goes in a loop for time. fetches sentences, recives input,
     * assesses states and renders output.
     *
     * @returns the appropiate error code.
     */
    EGameSessionErrorCode run();
};
} // namespace Game
