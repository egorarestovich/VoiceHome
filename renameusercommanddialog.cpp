#include "renameusercommanddialog.h"
#include "ui_renameusercommanddialog.h"
#include <QMessageBox>
#include <QString>
#include <signal.h>
#include <emmintrin.h>
#include <QFile>
#include <QDir>

QString pathtovcres = "C:/vcres";
QDir vcresdir;
QString filePath = pathtovcres + "/commands.txt";
QFile commandsfile(filePath);

RenameUserCommandDIalog::RenameUserCommandDIalog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RenameUserCommandDIalog)
{
    ui->setupUi(this);
}

RenameUserCommandDIalog::~RenameUserCommandDIalog()
{
    delete ui;
}

void RenameUserCommandDIalog::on_pushButton_2_clicked()
{
    setAttribute(Qt::WA_DeleteOnClose);
    close();
}
void RenameUserCommandDIalog::on_pushButton_clicked() {
    if (commandsfile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&commandsfile);
        out << ui->lineEdit->text();
        commandsfile.close();
    }
    QString newText = ui->lineEdit->text();
    emit textChanged(newText);
    setAttribute(Qt::WA_DeleteOnClose);
    close();
}
