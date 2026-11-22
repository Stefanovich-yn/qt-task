/**
 * @file bitprocessor.cpp
 * @brief Реализация методов класса BitProcessor.
 */

#include "bitprocessor.h"

#include <cstring>
#include <fstream>
#include <vector>

std::vector<uint8_t> BitProcessor::toByteArray(const NumStr &data)
{
    std::vector<uint8_t> bytes(sizeof(NumStr));
    std::memcpy(bytes.data(), &data, sizeof(NumStr));
    return bytes;
}

void BitProcessor::invertEvenBits(std::vector<uint8_t> &bytes)
{
    for (uint8_t i = 0; i < bytes.size(); ++i)
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

uint8_t BitProcessor::saveBitsToFile(const std::vector<uint8_t> &bytes, const std::string &filePath)
{
    std::ofstream outFile(filePath);
    if (!outFile.is_open())
    {
        return 0;
    }

    for (uint8_t i = 0; i < bytes.size(); ++i)
    {
        for (uint8_t j = 0; j < 8; ++j)
        {
            uint8_t bit = (bytes[i] >> j) & 1U;
            if (bit == 1)
            {
                outFile << "1\n";
            }
            else
            {
                outFile << "0\n";
            }
        }
    }

    outFile.close();
    if (outFile.fail())
    {
        return 0;
    }

    return 1;
}