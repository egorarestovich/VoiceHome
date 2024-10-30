#include "voicehome.h"
#include "voicehome.cpp"

#include <QApplication>
#include <QMessageBox>
#include <QTime>
#include <QTimer>
#include <QPalette>
#include <QThread>
#include <QWidget>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    VoiceHome w;
    QPalette darkPalette;

        a.setStyleSheet(R"(
QWidget {
    background-color: #2e2e2e; /* Темный фон для всего приложения */
    color: #ffffff; /* Белый цвет текста */
}

/* Стиль для заголовков окон */
QMainWindow {
    background-color: #2e2e2e; /* Темный фон для главного окна */
    border: 2px solid #555; /* Рамка вокруг окна */
    border-radius: 10px; /* Закругление углов */
}

/* Стиль для текстовых полей */
QLineEdit, QTextEdit {
    background-color: #3e3e3e; /* Темный фон текстовых полей */
    color: #ffffff; /* Белый цвет текста */
    border: 1px solid #242323; /* Рамка вокруг текстового поля */
    border-radius: 5px; /* Закругление углов текстового поля */
    padding: 8px; /* Отступы внутри текстового поля */
    font-size: 16px; /* Размер шрифта */
}

/* Стиль для чекбоксов и радиокнопок */
QCheckBox, QRadioButton {
    color: #ffffff; /* Белый цвет текста */
    font-size: 14px; /* Размер шрифта */
}

/* Стиль для списков */
QListView {
    background-color: #3e3e3e; /* Темный фон для списков */
    color: #ffffff; /* Белый цвет текста */
    border: 1px solid #555; /* Рамка вокруг списка */
    border-radius: 5px; /* Закругление углов списка */
}

/* Стиль для QMessageBox */
QMessageBox {
    background-color: #2c2c2c; /* Темный фон */
    border: 2px solid #555; /* Цвет рамки */
    border-radius: 15px; /* Закругление углов */
    padding: 20px; /* Отступы внутри */
    box-shadow: 0px 0px 20px rgba(0, 0, 0, 0.6); /* Эффект тени */
}

QMessageBox QLabel {
    color: #ffffff; /* Белый цвет текста */
    font-size: 18px; /* Размер шрифта */
    padding: 10px; /* Отступы вокруг текста */
}

/* Стиль для кнопок в QMessageBox */
QMessageBox QPushButton {
    background-color: #0078d7; /* Синий цвет кнопки */
    color: #ffffff; /* Белый цвет текста кнопки */
    border: none; /* Убираем рамку */
    padding: 12px 20px; /* Отступы внутри кнопки */
    border-radius: 8px; /* Закругление углов кнопки */
    font-size: 16px; /* Размер шрифта кнопки */
}

QMessageBox QPushButton:hover {
    background-color: #0056a1; /* Темно-синий цвет при наведении */
}

QMessageBox QPushButton:pressed {
    background-color: #004080; /* Цвет кнопки при нажатии */
}
            )");
    QTimer::singleShot(3000, &w, &VoiceHome::checkconnection);
    w.show();
    return a.exec();
}
