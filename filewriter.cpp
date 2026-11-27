/**
 * @file filewriter.cpp
 * @brief Реализация методов класса FileWriter.
 */

#include "filewriter.h"

#include <fstream>

uint8_t FileWriter::saveBitsToFile(const std::vector<uint8_t> &bits, const std::string &filePath)
{
    std::ofstream outFile(filePath);
    if (!outFile.is_open())
    {
        return 0;
    }

    for (uint32_t i = 0; i < bits.size(); ++i)
    {
        if (bits[i] == 1)
        {
            outFile << "1\n";
        }
        else
        {
            outFile << "0\n";
        }
    }

    outFile.close();
    if (outFile.fail())
    {
        return 0;
    }

    return 1;
}