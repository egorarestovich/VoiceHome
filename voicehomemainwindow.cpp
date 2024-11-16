#include "voicehomemainwindow.h"
#include <voicehomemainwindow.h>
#include "ui_voicehomemainwindow.h"
#include <renameusercommanddialog.h>

#include <QVector>
#include <QMessageBox>
#include <QBluetoothLocalDevice>
#include <QBluetoothDeviceDiscoveryAgent>
#include <QBluetoothDeviceInfo>
#include <QBluetoothSocket>
#include <QBluetoothUuid>
#include <QTimer>
#include <QFile>
#include <QTextStream>
#include <QDir>
#include <QListView>
#include <QStringListModel>
#include <QString>
#include <QListWidgetItem>
#include <QCheckBox>

QBluetoothAddress targetAddress2("00:19:06:34:DD:B5");
QBluetoothUuid serialPortUuid2 = QBluetoothUuid(QStringLiteral("00001101-0000-1000-8000-00805F9B34FB"));
QBluetoothAddress addr2(targetAddress2);
QBluetoothSocket *socket2 = new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol);

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
void VoiceHomeMainWindow::voicehomeprep(){
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
    ui->HomeLayout->setEnabled(false);
    ui->CommandsButton->setVisible(true);
    ui->HomeButton->setVisible(true);
    socket2->connectToService(addr2, serialPortUuid2);
    QTimer *timer = new QTimer();
    QObject::connect(timer, &QTimer::timeout, [&]() {
        QObject::connect(socket2, &QBluetoothSocket::readyRead, [&]() {
            while (socket2->canReadLine()) {
                QByteArray data = socket2->readLine();
                QVector <QString> listofdata;
                QString datanow = "";
                for(int i = 0; i < data.size(); i++){
                    if(data[i] != ':'){
                        datanow+=data[i];
                    }
                    else{
                        listofdata.push_back(datanow);
                        datanow=";";
                    }
                }
                listofdata.push_back(datanow);
                ui->temp->setText(listofdata[0]);
                ui->vlazh->setText(listofdata[1]);
                ui->co2->setText(listofdata[2]);
            }
        });
    });
    timer->start(1000);
}

void VoiceHomeMainWindow::on_HomeButton_clicked()
{
    ui->temp->setVisible(true);
    ui->co2->setVisible(true);
    ui->vlazh->setVisible(true);
    ui->HomeLayout->setEnabled(false);
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
    ui->HomeLayout->setEnabled(false);
    ui->CheckBoxSvet->setVisible(true);
    ui->SvetLabel->setVisible(true);
    ui->CheckBoxFan->setVisible(true);
    ui->FanLabel->setVisible(true);
    ui->ChainikLabel->setVisible(true);
    ui->CheckBoxChainik->setVisible(true);
    ui->UserCommandButton->setVisible(true);
    ui->CheckBoxUserCommand->setVisible(true);
}
void VoiceHomeMainWindow::writebluetooth(int command){
    try{
        QString message = QString::number(command);
        socket2->write(message.toUtf8());
    }
    catch(QBluetoothLocalDevice::Error error){
        QString errorString = QString("Bluetooth Error: %1").arg(static_cast<int>(error));
        QMessageBox::critical(this, "err", errorString);
    }
}


void VoiceHomeMainWindow::on_CheckBoxSvet_stateChanged(int arg1)
{
    qDebug() << "State changed to:" << arg1; // Отладочное сообщение
    if (arg1 == Qt::Checked) {
        writebluetooth(2);
        QMessageBox::about(this, "ОК", "Свет выключен");
    } else {
        writebluetooth(1);
        QMessageBox::about(this, "ОК", "Свет включен");
    }
}


void VoiceHomeMainWindow::on_CheckBoxFan_stateChanged(int arg1)
{
    if (arg1 == Qt::Checked) {
        writebluetooth(4);
        QMessageBox::about(this, "ОК", "Вентилятор выключен");
    } else {
        writebluetooth(3);
        QMessageBox::about(this, "ОК", "Вентилятор включен");
    }
}


void VoiceHomeMainWindow::on_CheckBoxChainik_stateChanged(int arg1)
{
    if (arg1 == Qt::Checked) {
        writebluetooth(6);
        QMessageBox::about(this, "ОК", "Чайник выключен");
    } else {
        writebluetooth(5);
        QMessageBox::about(this, "ОК", "Чайник включен");
    }
}


void VoiceHomeMainWindow::on_CheckBoxUserCommand_stateChanged(int arg1)
{
    if (arg1 == Qt::Checked) {
        writebluetooth(8);
        QMessageBox::about(this, "ОК", ui->UserCommandButton->text() + " выключён");
    } else {
        writebluetooth(7);
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
