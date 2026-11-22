/**
 * @file bitprocessor.h
 * @brief Описание класса BitProcessor для побитовой обработки и сохранения данных.
 */

#ifndef BITPROCESSOR_H
#define BITPROCESSOR_H

#include <stdint.h>
#include <string>
#include <vector>

#include "numstr.h"

/**
 * @class BitProcessor
 * @brief Класс для перевода структуры в массив байтов, инверсии чётных битов и записи в файл.
 */
class BitProcessor
{
public:
    /**
     * @brief Преобразует структуру NumStr в массив байтов.
     * @param data Заполненная структура NumStr.
     * @return Массив байтов размером sizeof(NumStr).
     */
    std::vector<uint8_t> toByteArray(const NumStr &data);

    /**
     * @brief Инвертирует каждый чётный бит массива (биты 0, 2, 4, 6 в каждом байте).
     * @param bytes Массив байтов для обработки.
     */
    void invertEvenBits(std::vector<uint8_t> &bytes);

    /**
     * @brief Записывает каждый бит массива в файл (по одному числу 0 или 1 на строку).
     * @param bytes Массив байтов после обработки.
     * @param filePath Путь к файлу для сохранения.
     * @return 1 при успешной записи, 0 при ошибке.
     */
    uint8_t saveBitsToFile(const std::vector<uint8_t> &bytes, const std::string &filePath);
};

#endif // BITPROCESSOR_H