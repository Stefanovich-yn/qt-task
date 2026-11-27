/**
 * @file mainwindow.cpp
 * @brief Реализация методов главного окна MainWindow.
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <string>
#include <vector>

#include <QFileDialog>
#include <QIntValidator>
#include <QMessageBox>
#include <QPushButton>

#include "bitprocessor.h"
#include "filewriter.h"
#include "numstr.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupInputFields();

    connect(ui->pushButtonRun, &QPushButton::clicked, this, &MainWindow::onRunClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupInputFields()
{
    // Ограничение ввода только целыми числами
    ui->lineEditA->setValidator(new QIntValidator(0, 256, this));
    ui->lineEditB->setValidator(new QIntValidator(0, 1, this));
    ui->lineEditC->setValidator(new QIntValidator(-3, 60, this));
    ui->lineEditD->setValidator(new QIntValidator(10, 12345678, this));

    // Значения по умолчанию
    ui->lineEditA->setText("0");
    ui->lineEditB->setText("0");
    ui->lineEditC->setText("0");
    ui->lineEditD->setText("10");

    // Подсказки внутри пустых полей
    ui->lineEditA->setPlaceholderText("Введите целое число");
    ui->lineEditB->setPlaceholderText("Введите целое число");
    ui->lineEditC->setPlaceholderText("Введите целое число");
    ui->lineEditD->setPlaceholderText("Введите целое число");

    // Всплывающие подсказки при наведении курсора
    ui->lineEditA->setToolTip("Введите целое число A от 0 до 256");
    ui->lineEditB->setToolTip("Введите целое число B от 0 до 1");
    ui->lineEditC->setToolTip("Введите целое число C от -3 до 60");
    ui->lineEditD->setToolTip("Введите целое число D от 10 до 12345678");
    ui->pushButtonRun->setToolTip("Упаковать числа, инвертировать чётные биты и сохранить в файл");
}

uint8_t MainWindow::tryParseInRange(const QString &text, int32_t minVal, int32_t maxVal, int32_t &outValue)
{
    const std::string str = text.trimmed().toStdString();
    if (str.empty())
    {
        return 0;
    }

    uint32_t index = 0;
    int8_t sign = 1;
    if (str[0] == '-')
    {
        sign = -1;
        index = 1;
    }
    else if (str[0] == '+')
    {
        index = 1;
    }

    if (index >= str.size())
    {
        return 0;
    }

    int64_t result = 0;
    for (; index < str.size(); ++index)
    {
        if (str[index] < '0' || str[index] > '9')
        {
            return 0;
        }
        result = result * 10 + (str[index] - '0');

        if (sign == 1 && result > maxVal)
        {
            return 0;
        }
        if (sign == -1 && (-result) < minVal)
        {
            return 0;
        }
    }

    result *= sign;
    if (result < minVal || result > maxVal)
    {
        return 0;
    }

    outValue = static_cast<int32_t>(result);
    return 1;
}

void MainWindow::onRunClicked()
{
    int32_t valueA = 0;
    int32_t valueB = 0;
    int32_t valueC = 0;
    int32_t valueD = 0;

    if (tryParseInRange(ui->lineEditA->text(), 0, 256, valueA) == 0)
    {
        QMessageBox::warning(this, "Некорректный ввод", "Поле A должно содержать целое число от 0 до 256.");
        ui->lineEditA->setFocus();
        return;
    }
    if (tryParseInRange(ui->lineEditB->text(), 0, 1, valueB) == 0)
    {
        QMessageBox::warning(this, "Некорректный ввод", "Поле B должно содержать целое число от 0 до 1.");
        ui->lineEditB->setFocus();
        return;
    }
    if (tryParseInRange(ui->lineEditC->text(), -3, 60, valueC) == 0)
    {
        QMessageBox::warning(this, "Некорректный ввод", "Поле C должно содержать целое число от -3 до 60.");
        ui->lineEditC->setFocus();
        return;
    }
    if (tryParseInRange(ui->lineEditD->text(), 10, 12345678, valueD) == 0)
    {
        QMessageBox::warning(this, "Некорректный ввод", "Поле D должно содержать целое число от 10 до 12345678.");
        ui->lineEditD->setFocus();
        return;
    }

    // Заполняем структуру NumStr
    const int8_t cOffset = 3;
    NumStr data{};
    data.A = static_cast<uint16_t>(valueA);
    data.B = static_cast<uint8_t>(valueB);
    data.C = static_cast<uint8_t>(valueC + cOffset);
    data.D = static_cast<uint32_t>(valueD);

    // Запрашиваем у пользователя имя файла для сохранения
    QString filePath = QFileDialog::getSaveFileName(
        this,
        "Сохранить результат",
        "result.txt",
        "Текстовые файлы (*.txt);;Все файлы (*)"
        );

    if (filePath.isEmpty())
    {
        return;
    }

    // Побитовая обработка
    BitProcessor processor;
    std::vector<uint8_t> bytes = processor.toByteArray(data);
    processor.invertEvenBits(bytes);
    std::vector<uint8_t> bits = processor.extractBits(bytes);

    // Запись в файл
    FileWriter writer;
    uint8_t isSaved = writer.saveBitsToFile(bits, filePath.toLocal8Bit().toStdString());

    if (isSaved == 1)
    {
        QMessageBox::information(this, "Готово", "Файл успешно сохранён:\n" + filePath);
    }
    else
    {
        QMessageBox::warning(this, "Ошибка", "Не удалось сохранить файл:\n" + filePath);
    }
}