#include "GameSession.h"

namespace Game
{
GameSession::GameSession(const Output::IOutput &output, const Input::IInput &input,
                         const Assessment::IRuleAssessor &assessor,
                         Sentences::SentenceFetcher &sentence_fetcher, uint16_t session_duration)
    : m_output{output}, m_input{input}, m_assessor{assessor}, m_sentence_fetcher{sentence_fetcher},
      m_session_duration{session_duration}
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

    const std::chrono::seconds duration(m_session_duration);
    std::chrono::steady_clock::time_point start_time = std::chrono::steady_clock::now();
    uint16_t target_sentence_index = 0;
    uint16_t reality_sentence_index = 0;
    bool is_currently_extra = false;

    m_output.clear_screen();

    while (std::chrono::steady_clock::now() - start_time < duration)
    {
        m_output.clear_screen();

        if (is_fully_typed(letters))
        {
            initialize_new_sentence(previous_sentence, letters, target_sentence,
                                    target_sentence_index, reality_sentence_index);
        }

        render_letters(previous_sentence);
        m_output.make_new_line();
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

    m_output.render("\nTime is up!\n", DEFAULT_COLOR);
    return EGameSessionErrorCode::SUCCESS;
}

void GameSession::initialize_new_sentence(std::vector<Letters::Letter> &previous_sentence,
                                          std::vector<Letters::Letter> &letters,
                                          std::string &target_sentence,
                                          uint16_t &target_sentence_index,
                                          uint16_t &reality_sentence_index)
{
    previous_sentence = letters;
    m_sentence_fetcher.get_sentence(target_sentence);
    letters = initialize_letters_vector(target_sentence);
    target_sentence_index = 0;
    reality_sentence_index = 0;
}

inline void GameSession::advance_indexes(uint16_t &target, uint16_t &reality)
{
    target++;
    reality++;
}

EGameSessionErrorCode GameSession::update_letters(Letters::Letter entered_letter,
                                                  uint16_t &target_sentence_index,
                                                  uint16_t &reality_sentece_index,
                                                  std::vector<Letters::Letter> &letters)
{
    if (entered_letter.state == Assessment::LetterState::ERROR)
    {
        return EGameSessionErrorCode::FAILURE;
    }
    if (!is_legal_character(entered_letter.character))
    {
        return EGameSessionErrorCode::SUCCESS;
    }

    if (entered_letter.character == UNDO_LAST_ACTION_1 ||
        entered_letter.character == UNDO_LAST_ACTION_2)
    {
        // TODO make it able to go back sentences
        if (reality_sentece_index > 0 && target_sentence_index > 0)
        {
            target_sentence_index--;
            reality_sentece_index--;
            letters[reality_sentece_index].state = Assessment::LetterState::UNTYPED;
        }
        return EGameSessionErrorCode::SUCCESS;
    }
    switch (entered_letter.state)
    {
    case Assessment::LetterState::CORRECT:
        letters[reality_sentece_index] = entered_letter;
        advance_indexes(target_sentence_index, reality_sentece_index);
        break;

    case Assessment::LetterState::INCORRECT:
        letters[reality_sentece_index] = entered_letter;
        advance_indexes(target_sentence_index, reality_sentece_index);
        break;

    case Assessment::LetterState::EXTRA:
        letters.insert(letters.begin() + reality_sentece_index, entered_letter);
        reality_sentece_index++;
        break;
    case Assessment::LetterState::SKIPPED:
        for (uint16_t i = reality_sentece_index; i < letters.size(); i++)
        {
            letters[i].state = Assessment::LetterState::SKIPPED;
            if (letters[i].character == BLANK_SPACE)
            {
                break;
            }
            advance_indexes(target_sentence_index, reality_sentece_index);
        }
        advance_indexes(target_sentence_index, reality_sentece_index);
        break;
    default:
        break;
    }
    return EGameSessionErrorCode::SUCCESS;
}

bool GameSession::is_legal_character(char character) { return (character != ILLEGAL_CHARACTER); }

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

EGameSessionErrorCode GameSession::render_letters(std::vector<Letters::Letter> letters) const
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
