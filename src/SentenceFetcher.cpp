#include "SentenceFetcher.h"

Sentences::SentenceFetcher::SentenceFetcher()
    : sentences({"The quick brown fox jumps over the lazy dog.", "Wait, is it 2026 already?",
                 "Data structures are the foundation of software."}),
      index(DEFAULT_INDEX)
{
}

Sentences::SentenceFetcherError Sentences::SentenceFetcher::get_sentence(std::string &o_sentence)
{
    if (sentences.empty())
    {
        return SentenceFetcherError::EMPTY_DATABASE;
    }
    if (index >= sentences.size())
    {
        return SentenceFetcherError::INDEX_OUT_OF_BOUNDS;
    }
    o_sentence = this->sentences[this->index];
    update_index();
    return Sentences::SentenceFetcherError::SUCCESS;
}

void Sentences::SentenceFetcher::update_index()
{
    if (sentences.empty())
    {
        this->index = 0;
        return;
    }
    this->index = (this->index + 1) % sentences.size();
}
