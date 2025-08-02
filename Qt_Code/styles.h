#pragma once
#include <QString>

class Styles {
public:
    static QString darkTheme() {
        return R"(
            QWidget {
                background-color: #2e2e2e;
                color: #ffffff;
            }
            QMainWindow {
                background-color: #2e2e2e;
            }
            QLineEdit, QTextEdit, QListView {
                background-color: #3e3e3e;
                color: #ffffff;
                border: 1px solid #555;
                padding: 6px;
                font-size: 14px;
            }
            QCheckBox, QRadioButton {
                color: #ffffff;
                font-size: 14px;
            }
            QListView {
                background-color: #3e3e3e;
                color: #ffffff;
                border: 1px solid #555;
            }
            QMessageBox {
                background-color: #2c2c2c;
            }
            QMessageBox QLabel {
                color: #ffffff;
                font-size: 14px;
                padding: 5px;
            }
            QMessageBox QPushButton {
                background-color: #0078d7;
                color: #ffffff;
                border: none;
                padding: 8px 16px;
                font-size: 14px;
                border-radius: 8px;
            }
            QMessageBox QPushButton:hover {
                background-color: #0056a1;
            }
            QMessageBox QPushButton:pressed {
                background-color: #004080;
            }
            QLabel {
                color: #ffffff;
            }
        )";
    }
};
