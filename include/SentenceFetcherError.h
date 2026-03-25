#pragma once

#include <string>
#include <vector>
namespace Sentences
{
enum class SentenceFetcherError
{
    SUCCESS,
    EMPTY_DATABASE,
    INDEX_OUT_OF_BOUNDS
};
}; // namespace Sentences