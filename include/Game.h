#include "Color.h"
#include "ColorCodes.h"
#include "EGameErrorCode.h"
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
namespace Game
{
class Game
{
  private:
    static constexpr uint16_t GAME_SESSION_DURATION_IN_SECONDS = 25;
    static constexpr unsigned char DEFAULT_INPUT_CHAR = EOF;
    static constexpr unsigned char USER_WISHES_TO_CONTINUE_CHARACTER = 'Y';
    std::string DOES_USER_WISH_TO_START_SESSION_MESSAGE =
        "Do you wish to start a game session?\n Enter Y if yes.\n if not enter anything else.";
    std::string USER_WISH_TO_NOT_START_SESSION_MESSAGE =
        "User doesn't wish to start a session. Terminating program.";

    Colors::ColorCodes color_codes;
    Colors::Color DEFAULT_COLOR{color_codes.RESET};

  public:
    Game();
    ~Game();

    /**
     * @brief runs the typeracer game. Calls a session upon request. when a session ends you may
     * call another one.
     */
    EGameErrorCode run();
};
} // namespace Game
