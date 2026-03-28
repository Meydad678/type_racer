#include "GameSession.h"

namespace Game
{
GameSession::GameSession(const Output::IOutput &output, const Input::IInput &input,
                         const Assessment::IRuleAssessor &assessor,
                         Sentences::SentenceFetcher &sentence_fetcher)
    : m_output{output}, m_input{input}, m_assessor{assessor}, m_sentence_fetcher{sentence_fetcher}
{
}

GameSession::~GameSession() {}

EGameSessionErrorCode GameSession::run()
{
    unsigned char input_char = DEFAULT_INPUT_CHAR;
    Input::EInputErrorCodes input_error_code = Input::EInputErrorCodes::FAILURE;
    Game::EGameSessionErrorCode session_error_code = Game::EGameSessionErrorCode::FAILURE;

    std::string target_sentence{};
    m_sentence_fetcher.get_sentence(target_sentence);

    std::vector<Letters::Letter> letters = initialize_letters_vector(target_sentence);
    std::vector<Letters::Letter> previous_sentence{};

    // const std::chrono::seconds duration(GAME_SESSION_DURATION_IN_SECONDS);
    const std::chrono::seconds duration(40);
    std::chrono::steady_clock::time_point start_time = std::chrono::steady_clock::now();
    uint16_t target_sentence_index = 0;
    uint16_t reality_sentence_index = 0;
    bool is_currently_extra = false;

    m_output.clear_screen();

    while (std::chrono::steady_clock::now() - start_time < duration)
    {
        // m_output.clear_screen();

        if (is_fully_typed(letters))
        {
            previous_sentence = letters;
            m_sentence_fetcher.get_sentence(target_sentence);
            letters = initialize_letters_vector(target_sentence);
            target_sentence_index = 0;
            reality_sentence_index = 0;
        }

        render_letters(previous_sentence);
        std::cout << std::endl; // todo output.newline()
        render_letters(letters);

        input_error_code = m_input.get_char(input_char);
        if (input_error_code != Input::EInputErrorCodes::SUCCESS)
        {
            return EGameSessionErrorCode::FAILURE;
        }

        unsigned char expected_char = target_sentence[target_sentence_index];
        Assessment::LetterState state = m_assessor.assess(expected_char, input_char);

        session_error_code = update_letters({state, input_char}, target_sentence_index,
                                            reality_sentence_index, letters);
        if (session_error_code != Game::EGameSessionErrorCode::SUCCESS)
        {
            return session_error_code;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(LOOP_SLEEP_DURATION_IN_MILLISECONDS));
    }

    m_output.render("\nTime is up!", DEFAULT_COLOR);
    return EGameSessionErrorCode::SUCCESS;
}

EGameSessionErrorCode GameSession::update_letters(Letters::Letter letter,
                                                  uint16_t &target_sentence_index,
                                                  uint16_t &reality_sentece_index,
                                                  std::vector<Letters::Letter> &letters)
{
    printf("\nstate: %d\n", letter.state);
    switch (letter.state)
    {
    case Assessment::LetterState::ERROR:
        return EGameSessionErrorCode::FAILURE;
    case Assessment::LetterState::CORRECT:
        letters[reality_sentece_index] = letter;
        target_sentence_index++;
        reality_sentece_index++;
        break;

    case Assessment::LetterState::INCORRECT:
        letters[reality_sentece_index] = letter;
        target_sentence_index++;
        reality_sentece_index++;
        break;

    case Assessment::LetterState::EXTRA:
        letters.insert(letters.begin() + reality_sentece_index, letter);
        reality_sentece_index++;
        break;
    case Assessment::LetterState::SKIPPED:
        // TODO
        break;
    default:
        break;
    }
    return EGameSessionErrorCode::SUCCESS;
}
std::vector<Letters::Letter> GameSession::initialize_letters_vector(std::string &sentence)
{
    std::vector<Letters::Letter> letters = {};
    letters.reserve(sentence.size());
    for (unsigned char character : sentence)
    {
        letters.push_back({DEFAULT_LETTER_STATE, character});
    }
    return letters;
}

bool GameSession::is_fully_typed(std::vector<Letters::Letter> &letters)
{
    for (Letters::Letter letter : letters)
    {
        if (letter.state == Assessment::LetterState::UNTYPED)
        {
            return false;
        }
    }
    return true;
}

EGameSessionErrorCode GameSession::render_letters(std::vector<Letters::Letter> letters)
{
    Colors::Color color = DEFAULT_COLOR;
    for (Letters::Letter letter : letters)
    {
        if (m_assessor.state_to_color(letter.state, color) != true)
        {
            return EGameSessionErrorCode::FAILURE;
        }
        m_output.render(std::string(NUMBER_OF_CHARS_IN_ONE_LETTER, letter.character), color);
    }
    return EGameSessionErrorCode::SUCCESS;
}

} // namespace Game
