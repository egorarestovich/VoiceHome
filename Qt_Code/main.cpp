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
    }

    /* Стиль для текстовых полей */
    QLineEdit, QTextEdit {
        background-color: #3e3e3e; /* Темный фон текстовых полей */
        color: #ffffff; /* Белый цвет текста */
        border: 1px solid #555; /* Упрощенная рамка вокруг текстового поля */
        padding: 6px; /* Отступы внутри текстового поля */
        font-size: 14px; /* Уменьшенный размер шрифта */
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
        border: 1px solid #555; /* Упрощенная рамка вокруг списка */
    }

    /* Стиль для QMessageBox */
    QMessageBox {
        background-color: #2c2c2c; /* Темный фон */
    }

    QMessageBox QLabel {
        color: #ffffff; /* Белый цвет текста */
        font-size: 14px; /* Уменьшенный размер шрифта */
        padding: 5px; /* Отступы вокруг текста */
    }

    /* Стиль для кнопок в QMessageBox */
    QMessageBox QPushButton {
        background-color: #0078d7; /* Синий цвет кнопки */
        color: #ffffff; /* Белый цвет текста кнопки */
        border: none; /* Убираем рамку */
        padding: 8px 16px; /* Уменьшенные отступы внутри кнопки */
        font-size: 14px; /* Уменьшенный размер шрифта кнопки */
        border-radius: 8px; /* Закругление углов кнопки */

    }

    QMessageBox QPushButton:hover {
        background-color: #0056a1; /* Темно-синий цвет при наведении */
    }

    QMessageBox QPushButton:pressed {
        background-color: #004080; /* Цвет кнопки при нажатии */
    }
    QLabel {
        color: #ffffff;
    }
    )");

    QTimer::singleShot(3000, &w, &VoiceHome::checkconnection);
    w.show();
    return a.exec();
}
