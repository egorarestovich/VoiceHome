#include "renameusercommanddialog.h"
#include "ui_renameusercommanddialog.h"
#include <QFile>
#include <QTextStream>
#include <QDir>

const QString filePath = "C:/vcres/commands.txt";

RenameUserCommandDIalog::RenameUserCommandDIalog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::RenameUserCommandDIalog)
{
    ui->setupUi(this);
}

RenameUserCommandDIalog::~RenameUserCommandDIalog() {
    delete ui;
}

void RenameUserCommandDIalog::on_pushButton_clicked() {
    QString text = ui->lineEdit->text().trimmed();
    if (text.isEmpty()) {
        text = "Ваше устройство";
    }

    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << text;
        file.close();
    }

    emit textChanged(text);
    accept();
}

void RenameUserCommandDIalog::on_pushButton_2_clicked() {
    reject();
}
