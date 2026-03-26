#include "Color.h"
#include "ColorCodes.h"
#include "EGameSessionErrorCode.h"
#include "GameSession.h"
#include "SentenceFetcher.h"
#include "TerminalInput.h"
#include "TerminalOutput.h"
#include <chrono>
#include <iostream>
#include <stdio.h>
#include <termios.h>
#include <thread>
#include <unistd.h>


int main()
{

    const Output::IOutput &output = Output::TerminalOutput();
    const Input::IInput &input = Input::TerminalInput();
    const Assessment::IRuleAssessor &assessor = Assessment::LetterAssessor{};
    Sentences::SentenceFetcher sentence_fetcher;

    Game::EGameSessionErrorCode error_code_session = Game::EGameSessionErrorCode::FAILURE;
    Game::GameSession session{output, input, assessor, sentence_fetcher};
    error_code_session = session.run();

    // From here it should be refactored
    return EXIT_SUCCESS;
}
