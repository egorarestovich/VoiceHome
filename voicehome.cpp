#include <QMessageBox>
#include <QBluetoothLocalDevice>
#include <voicehomemainwindow.h>
#include <QBluetoothDeviceDiscoveryAgent>
#include <QBluetoothDeviceInfo>
#include <QBluetoothSocket>
#include <QBluetoothUuid>
#include <QTimer>
#include <QCoreApplication>
#include "voicehome.h"
#include "ui_voicehome.h"
#include "voicehomemainwindow.h"
#include "voicehomemainwindow.cpp"

QBluetoothAddress targetAddress("00:19:06:34:DD:B5");
QBluetoothUuid serialPortUuid = QBluetoothUuid(QStringLiteral("00001101-0000-1000-8000-00805F9B34FB"));
QBluetoothAddress addr(targetAddress);
QBluetoothSocket socket(QBluetoothServiceInfo::RfcommProtocol);

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



bool VoiceHome::isconnectpossible()
{
    try {
        QBluetoothLocalDevice localDevice;
        if(localDevice.isValid()){
            try {
                socket.connectToService(addr, QBluetoothUuid(serialPortUuid));
            }
            catch (const std::exception &e) {
                QMessageBox::warning(this, "Bluetooth error", "Не удалось подключиться к устройству");
                qDebug() << e.what();
                return false;
            }
        }
        else{
            QMessageBox::warning(this, "Bluetooth error", "Блютуз адаптер не доступен!");
            return false;
        }
    }
    catch (QBluetoothLocalDevice::Error error) {
        QString errorString = QString("Bluetooth Error: %1").arg(static_cast<int>(error));
        QMessageBox::critical(this, "err", errorString);
        return false;
    }
}
void VoiceHome::checkconnection(){
    /*if(isconnectpossible() == false){
        QMessageBox::StandardButton reply = QMessageBox::question(this, "Ошибка!", "Возникла ошибка, показанная вам ранее. Попробовать переподключиться?",
                                                                      QMessageBox::Yes | QMessageBox::No);
        if(reply == QMessageBox::StandardButton::Yes){
            checkconnection();
        }
        else{
            exit(0);
        }
    }
    else{
        loadinterface();
    }*/
    loadinterface();
}
void VoiceHome::loadinterface(){
    hide();
    mainapp = new VoiceHomeMainWindow();
    mainapp->setAttribute(Qt::WA_ShowWithoutActivating);
    mainapp->setWindowTitle("VoiceHome");
    mainapp->show();
    QTimer::singleShot(0, mainapp, &VoiceHomeMainWindow::voicehomeprep);
}
