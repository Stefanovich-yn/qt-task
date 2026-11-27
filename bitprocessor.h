/**
 * @file bitprocessor.h
 * @brief Описание класса BitProcessor для побитовой обработки структуры NumStr.
 */

#ifndef BITPROCESSOR_H
#define BITPROCESSOR_H

#include <stdint.h>
#include <vector>

#include "numstr.h"

/**
 * @class BitProcessor
 * @brief Класс, отвечающий за преобразование структуры в байты и операции с битами.
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
     * @brief Извлекает последовательность отдельных битов (0 или 1) из массива байтов.
     * @param bytes Массив байтов.
     * @return Вектор значений 0 и 1 (по 8 элементов на каждый байт).
     */
    std::vector<uint8_t> extractBits(const std::vector<uint8_t> &bytes);
};

#endif // BITPROCESSOR_H