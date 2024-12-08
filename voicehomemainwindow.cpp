#include "voicehomemainwindow.h"
#include <voicehomemainwindow.h>
#include "ui_voicehomemainwindow.h"
#include <renameusercommanddialog.h>
#include <voicehome.h>

#include <QVector>
#include <QMessageBox>
#include <QTimer>
#include <QFile>
#include <QTextStream>
#include <QDir>
#include <QListView>
#include <QStringListModel>
#include <QString>
#include <QListWidgetItem>
#include <QCheckBox>
#include <QSerialPort>
#include <QSerialPortInfo>

QString portname = "COM3";
QSerialPort serialport;

QString pathtovcres2 = "C:/vcres";
QDir vcresdir2;
QString filePath2 = pathtovcres2 + "/commands.txt";
QFile commandsfile2(filePath2);

VoiceHomeMainWindow::VoiceHomeMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::VoiceHomeMainWindow)
{
    ui->setupUi(this);
}

VoiceHomeMainWindow::~VoiceHomeMainWindow()
{
    delete ui;
}
void VoiceHomeMainWindow::openconnect(){
    try {
        QList<QSerialPortInfo> availablePorts = QSerialPortInfo::availablePorts();

        bool portFound = false;
        for (const QSerialPortInfo &portInfo : availablePorts) {
            if (portInfo.portName() == portname) {
                portFound = true;
                break;
            }
        }
        if (portFound == true && serialport.isOpen() == false) {
            serialport.setPortName(portname);
            if (serialport.open(QIODevice::ReadWrite)) {
                serialport.setBaudRate(QSerialPort::Baud9600);
                serialport.setDataBits(QSerialPort::Data8);
                serialport.setParity(QSerialPort::NoParity);
                serialport.setStopBits(QSerialPort::OneStop);
                serialport.setFlowControl(QSerialPort::NoFlowControl);
            } else {
                QMessageBox::warning(nullptr, "Ошибка COM порта", "Не удалось открыть COM-порт!");
                openconnect();
            }
        }
        else {
                QMessageBox::warning(nullptr, "Ошибка COM порта", "COM-порт не доступен!\
    \nВозможное решение:\nПопробуйте подключить VoiceHome к COM порту №3");
                openconnect();
        }
    } catch (const std::exception &e) {
        QMessageBox::critical(nullptr, "Error", "Произошла ошибка: " + QString::fromStdString(e.what()));
        openconnect();
    }
}
void VoiceHomeMainWindow::voicehomeprep(){
    openconnect();
    if(!vcresdir2.exists(pathtovcres2)){
        vcresdir2.mkpath(pathtovcres2);
    }
    if(!commandsfile2.exists()){
        if (commandsfile2.open(QIODevice::WriteOnly | QIODevice::Text)) {
                QTextStream out(&commandsfile2);
                out << "Ваше устройство";
                commandsfile2.close();
        }
    }
    if (commandsfile2.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream read(&commandsfile2);
        QString text = read.readAll();
        commandsfile2.close();
        WriteOnUserButton(text);
    }
    ui->temp->setVisible(false);
    ui->co2->setVisible(false);
    ui->vlazh->setVisible(false);
    ui->co2text->setVisible(false);
    ui->vltext->setVisible(false);
    ui->temptext->setVisible(false);
    ui->CommandsButton->setVisible(true);
    ui->HomeButton->setVisible(true);

    connect(&serialport, &QSerialPort::readyRead, [&]() {
        while (serialport.canReadLine()) {
            QByteArray data = serialport.readLine();
            qDebug() << data;

            QString decodedData = QString::fromUtf8(data);

            decodedData = decodedData.trimmed();

            QVector<QString> listofdata;
            QString datanow = "";
            for (int i = 0; i < decodedData.size(); i++) {
                if (decodedData[i] != ':') {
                    datanow += decodedData[i];
                } else {
                    listofdata.push_back(datanow);
                    datanow = "";
                }
            }
            if (!datanow.isEmpty()) {
                listofdata.push_back(datanow);
            }

            if (listofdata.size() >= 3) {
                ui->temp->setText(listofdata[0]);
                ui->vlazh->setText(listofdata[1]);
                ui->co2->setText(listofdata[2]);
            }
        }
    });


}

void VoiceHomeMainWindow::on_HomeButton_clicked()
{
    ui->temp->setVisible(true);
    ui->co2->setVisible(true);
    ui->vlazh->setVisible(true);
    ui->co2text->setVisible(true);
    ui->vltext->setVisible(true);
    ui->temptext->setVisible(true);
    ui->CheckBoxSvet->setVisible(false);
    ui->SvetLabel->setVisible(false);
    ui->CheckBoxFan->setVisible(false);
    ui->FanLabel->setVisible(false);
    ui->ChainikLabel->setVisible(false);
    ui->CheckBoxChainik->setVisible(false);
    ui->UserCommandButton->setVisible(false);
    ui->CheckBoxUserCommand->setVisible(false);
}


void VoiceHomeMainWindow::on_CommandsButton_clicked()
{
    ui->temp->setVisible(false);
    ui->co2->setVisible(false);
    ui->vlazh->setVisible(false);
    ui->co2text->setVisible(false);
    ui->vltext->setVisible(false);
    ui->temptext->setVisible(false);
    ui->CheckBoxSvet->setVisible(true);
    ui->SvetLabel->setVisible(true);
    ui->CheckBoxFan->setVisible(true);
    ui->FanLabel->setVisible(true);
    ui->ChainikLabel->setVisible(true);
    ui->CheckBoxChainik->setVisible(true);
    ui->UserCommandButton->setVisible(true);
    ui->CheckBoxUserCommand->setVisible(true);
}

void VoiceHomeMainWindow::writeSerial(int command) {
    try {
        QString message = QString::number(command);
        QByteArray data = message.toUtf8();
        qDebug() << data;
        if (serialport.isOpen()) {
            serialport.write(data);
        } else {
            throw std::runtime_error("COM порт не открыт!");
            openconnect();
        }
    } catch (const std::exception &e) {
        QString errorString = QString("Serial Port Error: %1").arg(e.what());
        QMessageBox::critical(this, "Error", errorString);
    }
}


void VoiceHomeMainWindow::on_CheckBoxSvet_stateChanged(int arg1)
{
    if (arg1 == Qt::Checked) {
        writeSerial(2);
        QMessageBox::about(this, "ОК", "Свет выключен");
    } else {
        writeSerial(1);
        QMessageBox::about(this, "ОК", "Свет включен");
    }
}


void VoiceHomeMainWindow::on_CheckBoxFan_stateChanged(int arg1)
{
    if (arg1 == Qt::Checked) {
        writeSerial(4);
        QMessageBox::about(this, "ОК", "Вентилятор выключен");
    } else {
        writeSerial(3);
        QMessageBox::about(this, "ОК", "Вентилятор включен");
    }
}


void VoiceHomeMainWindow::on_CheckBoxChainik_stateChanged(int arg1)
{
    if (arg1 == Qt::Checked) {
        writeSerial(6);
        QMessageBox::about(this, "ОК", "Чайник выключен");
    } else {
        writeSerial(5);
        QMessageBox::about(this, "ОК", "Чайник включен");
    }
}


void VoiceHomeMainWindow::on_CheckBoxUserCommand_stateChanged(int arg1)
{
    if (arg1 == Qt::Checked) {
        writeSerial(8);
        QMessageBox::about(this, "ОК", ui->UserCommandButton->text() + " выключён");
    } else {
        writeSerial(7);
        QMessageBox::about(this, "ОК", ui->UserCommandButton->text() + " включен");
    }
}


void VoiceHomeMainWindow::on_UserCommandButton_clicked()
{
    RenameUserCommandDIalog dialog(this);
    setAttribute(Qt::WA_DeleteOnClose);
    connect(&dialog, &RenameUserCommandDIalog::textChanged, this, &VoiceHomeMainWindow::WriteOnUserButton);
    dialog.exec();
}
void VoiceHomeMainWindow::WriteOnUserButton(QString text){
    ui->UserCommandButton->setText(text);
}
