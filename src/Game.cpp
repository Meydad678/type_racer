#include "Game.h"

namespace Game
{
Game::Game() {}

Game::~Game() {}

EGameErrorCode Game::run()
{

    const Output::IOutput &output = Output::TerminalOutput();
    const Input::IInput &input = Input::TerminalInput();

    const Assessment::IRuleAssessor &assessor = Assessment::LetterAssessor{};
    Sentences::SentenceFetcher sentence_fetcher;

    Input::EInputErrorCodes input_error_code = Input::EInputErrorCodes::FAILURE;
    EGameSessionErrorCode error_code_session = EGameSessionErrorCode::FAILURE;

    GameSession session{output, input, assessor, sentence_fetcher, GAME_SESSION_DURATION_IN_SECONDS};
    bool another_game = false;
    unsigned char input_char = DEFAULT_INPUT_CHAR;

    while (true)
    {
        output.render(DOES_USER_WISH_TO_START_SESSION_MESSAGE, DEFAULT_COLOR);
        input_error_code = input.get_confirmed_char(input_char);
        if (input_error_code != Input::EInputErrorCodes::SUCCESS)
        {
            return EGameErrorCode::FAILURE;
        }
        if (input_char != USER_WISHES_TO_CONTINUE_CHARACTER)
        {
            output.render(USER_WISH_TO_NOT_START_SESSION_MESSAGE, DEFAULT_COLOR);
            break;
        }

        error_code_session = session.run();
        if (error_code_session == EGameSessionErrorCode::FAILURE)
        {
            return EGameErrorCode::FAILURE;
        }
    }
    return EGameErrorCode::SUCCESS;
}
} // namespace Game