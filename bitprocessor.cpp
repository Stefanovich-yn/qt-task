/**
 * @file bitprocessor.cpp
 * @brief Реализация методов класса BitProcessor.
 */

#include "bitprocessor.h"

#include <cstring>
#include <vector>

std::vector<uint8_t> BitProcessor::toByteArray(const NumStr &data)
{
    std::vector<uint8_t> bytes(sizeof(NumStr));
    std::memcpy(bytes.data(), &data, sizeof(NumStr));
    return bytes;
}

void BitProcessor::invertEvenBits(std::vector<uint8_t> &bytes)
{
    for (uint32_t i = 0; i < bytes.size(); ++i)
    {
        for (uint8_t j = 0; j < 8; ++j)
        {
            if (j % 2 == 0)
            {
                bytes[i] ^= (1U << j);
            }
        }
    }
}

std::vector<uint8_t> BitProcessor::extractBits(const std::vector<uint8_t> &bytes)
{
    std::vector<uint8_t> bits;
    bits.reserve(bytes.size() * 8U);

    for (uint32_t i = 0; i < bytes.size(); ++i)
    {
        for (uint8_t j = 0; j < 8; ++j)
        {
            uint8_t bit = (bytes[i] >> j) & 1U;
            bits.push_back(bit);
        }
    }

    return bits;
}