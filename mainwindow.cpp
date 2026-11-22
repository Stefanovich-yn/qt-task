/**
 * @file mainwindow.cpp
 * @brief Реализация методов главного окна MainWindow.
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <stdint.h>
#include <vector>

#include <QFileDialog>
#include <QMessageBox>
#include <QPushButton>
#include <QString>

#include "bitprocessor.h"
#include "numstr.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pushButtonRun, &QPushButton::clicked, this, &MainWindow::onRunClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onRunClicked()
{
    // Заполняем структуру NumStr значениями с формы
    NumStr data{};
    data.A = static_cast<uint16_t>(ui->spinBoxA->value());
    data.B = static_cast<uint8_t>(ui->spinBoxB->value());
    data.C = static_cast<int8_t>(ui->spinBoxC->value());
    data.D = static_cast<uint32_t>(ui->spinBoxD->value());

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

    // Переводим в байты, инвертируем чётные биты и записываем в файл
    BitProcessor processor;
    std::vector<uint8_t> bytes = processor.toByteArray(data);
    processor.invertEvenBits(bytes);
    uint8_t isSaved = processor.saveBitsToFile(bytes, filePath.toLocal8Bit().toStdString());

    if (isSaved == 1)
    {
        QMessageBox::information(this, "Готово", "Файл успешно сохранён:\n" + filePath);
    }
    else
    {
        QMessageBox::warning(this, "Ошибка", "Не удалось сохранить файл:\n" + filePath);
    }
}