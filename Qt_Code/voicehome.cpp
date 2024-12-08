#include <QMessageBox>
#include <voicehomemainwindow.h>
#include <QTimer>
#include <QCoreApplication>
#include <QSerialPort>
#include <QSerialPortInfo>
#include "voicehome.h"
#include "ui_voicehome.h"
#include "voicehomemainwindow.h"

QString portName = "COM3";

VoiceHome::VoiceHome(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::VoiceHome)
{
    ui->setupUi(this);
}

VoiceHome::~VoiceHome()
{
    delete ui;
}



bool VoiceHome::isconnectpossible() {
    try {
        QList<QSerialPortInfo> availablePorts = QSerialPortInfo::availablePorts();
        bool portFound = false;
        for (const QSerialPortInfo &portInfo : availablePorts) {
            if (portInfo.portName() == portName) {
                portFound = true;
                break;
            }
        }

        if (portFound) {
            return true;
        } else {
            QMessageBox::warning(nullptr, "Ошибка COM порта", "COM-порт не доступен!\
\nВозможное решение:\nПопробуйте подключить VoiceHome к COM порту №3");
            return false;
        }
    } catch (const std::exception &e) {
        QMessageBox::critical(nullptr, "Error", "Произошла ошибка: " + QString::fromStdString(e.what()));
        return false;
    }
}

void VoiceHome::checkconnection() {
    if (!isconnectpossible()) {
        QMessageBox::StandardButton reply = QMessageBox::question(nullptr, "Ошибка!", "Возникла ошибка, показанная вам ранее. Попробовать переподключиться?",
                                                                  QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::StandardButton::Yes) {
            checkconnection();
        } else {
            exit(0);
        }
    } else {
        loadinterface();
    }
}
void VoiceHome::loadinterface(){
    hide();
    mainapp = new VoiceHomeMainWindow();
    mainapp->setAttribute(Qt::WA_ShowWithoutActivating);
    mainapp->setWindowTitle("VoiceHome");
    mainapp->setStyleSheet(R"(
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
    mainapp->show();
    QTimer::singleShot(0, mainapp, &VoiceHomeMainWindow::voicehomeprep);
}
