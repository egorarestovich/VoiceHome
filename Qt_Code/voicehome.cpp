#include "voicehome.h"
#include "voicehomemainwindow.h"
#include "ui_voicehome.h"
#include <QTimer>
#include <QMessageBox>
#include <QSerialPortInfo>

VoiceHome::VoiceHome(QWidget *parent)
    : QMainWindow(parent)
    , ui(std::make_unique<Ui::VoiceHome>())
{
    ui->setupUi(this);
}

VoiceHome::~VoiceHome() = default;

void VoiceHome::checkConnection() {
    if (!isPortAvailable("COM3")) {
        auto reply = QMessageBox::question(this, "Ошибка", "COM-порт недоступен. Попробовать снова?",
                                           QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            QTimer::singleShot(1000, this, &VoiceHome::checkConnection);
        } else {
            qApp->quit();
        }
    } else {
        loadInterface();
    }
}

bool VoiceHome::isPortAvailable(const QString &portName) {
    for (const QSerialPortInfo &portInfo : QSerialPortInfo::availablePorts()) {
        if (portInfo.portName() == portName) {
            return true;
        }
    }
    return false;
}

void VoiceHome::loadInterface() {
    hide();
    mainapp = std::make_unique<VoiceHomeMainWindow>(this);
    mainapp->show();
}
