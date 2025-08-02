#include "voicehomemainwindow.h"
#include "ui_voicehomemainwindow.h"
#include "renameusercommanddialog.h"
#include "serialportmanager.h"
#include <QDir>
#include <QMessageBox>
#include <QTimer>
#include <QSerialPortInfo>
#include "styles.h"

VoiceHomeMainWindow::VoiceHomeMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(std::make_unique<Ui::VoiceHomeMainWindow>())
    , m_serialManager(std::make_unique<SerialPortManager>(this))
{
    ui->setupUi(this);
    setStyleSheet(Styles::darkTheme());

    connect(m_serialManager.get(), &SerialPortManager::dataReceived,
            this, &VoiceHomeMainWindow::handleSerialData);
    connect(m_serialManager.get(), &SerialPortManager::errorOccurred,
            this, &VoiceHomeMainWindow::handleSerialError);
}

VoiceHomeMainWindow::~VoiceHomeMainWindow() = default;

void VoiceHomeMainWindow::voicehomeprep() {
    openConnect();
    loadUserCommand();

    setupUIForHome();
}

void VoiceHomeMainWindow::openConnect() {
    if (!m_serialManager->connectToPort("COM3")) {
        QTimer::singleShot(2000, this, &VoiceHomeMainWindow::openConnect);
    }
}

void VoiceHomeMainWindow::loadUserCommand() {
    QDir dir("C:/vcres");
    if (!dir.exists()) {
        dir.mkpath(".");
    }

    QFile file(m_commandsFile);
    if (file.open(QIODevice::ReadOnly)) {
        m_userCommand = file.readAll().trimmed();
        file.close();
    } else {
        m_userCommand = "Ваше устройство";
    }
    ui->UserCommandButton->setText(m_userCommand);
}

void VoiceHomeMainWindow::saveUserCommand(const QString &command) {
    QFile file(m_commandsFile);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        file.write(command.toUtf8());
        file.close();
        m_userCommand = command;
    } else {
        QMessageBox::warning(this, "Ошибка", "Не удалось сохранить команду.");
    }
}

void VoiceHomeMainWindow::handleSerialData(const QString &data) {
    auto parts = data.split(':');
    if (parts.size() >= 3) {
        ui->temp->setText(parts[0]);
        ui->vlazh->setText(parts[1]);
        ui->co2->setText(parts[2]);
    }
}

void VoiceHomeMainWindow::handleSerialError(const QString &error) {
    QMessageBox::warning(this, "Ошибка COM", error);
}

void VoiceHomeMainWindow::on_HomeButton_clicked() {
    ui->temp->setVisible(true);
    ui->co2->setVisible(true);
    ui->vlazh->setVisible(true);
    ui->co2text->setVisible(true);
    ui->vltext->setVisible(true);
    ui->temptext->setVisible(true);
    ui->co2icon->setVisible(true);
    ui->tempicon->setVisible(true);
    ui->vlicon->setVisible(true);

    ui->CheckBoxSvet->setVisible(false);
    ui->SvetLabel->setVisible(false);
    ui->CheckBoxFan->setVisible(false);
    ui->FanLabel->setVisible(false);
    ui->CheckBoxChainik->setVisible(false);
    ui->ChainikLabel->setVisible(false);
    ui->UserCommandButton->setVisible(false);
    ui->CheckBoxUserCommand->setVisible(false);
}

void VoiceHomeMainWindow::on_CommandsButton_clicked() {
    ui->temp->setVisible(false);
    ui->co2->setVisible(false);
    ui->vlazh->setVisible(false);
    ui->co2text->setVisible(false);
    ui->vltext->setVisible(false);
    ui->temptext->setVisible(false);
    ui->co2icon->setVisible(false);
    ui->tempicon->setVisible(false);
    ui->vlicon->setVisible(false);

    ui->CheckBoxSvet->setVisible(true);
    ui->SvetLabel->setVisible(true);
    ui->CheckBoxFan->setVisible(true);
    ui->FanLabel->setVisible(true);
    ui->CheckBoxChainik->setVisible(true);
    ui->ChainikLabel->setVisible(true);
    ui->UserCommandButton->setVisible(true);
    ui->CheckBoxUserCommand->setVisible(true);
}

void VoiceHomeMainWindow::on_CheckBoxSvet_stateChanged(int state) {
    if (m_serialManager->isConnected()) {
        m_serialManager->serialPort()->write(state == Qt::Checked ? "2" : "1");
    }
}

void VoiceHomeMainWindow::on_CheckBoxFan_stateChanged(int state) {
    if (m_serialManager->isConnected()) {
        m_serialManager->serialPort()->write(state == Qt::Checked ? "4" : "3");
    }
}

void VoiceHomeMainWindow::on_CheckBoxChainik_stateChanged(int state) {
    if (m_serialManager->isConnected()) {
        m_serialManager->serialPort()->write(state == Qt::Checked ? "6" : "5");
    }
}

void VoiceHomeMainWindow::on_CheckBoxUserCommand_stateChanged(int state) {
    if (m_serialManager->isConnected()) {
        m_serialManager->serialPort()->write(state == Qt::Checked ? "8" : "7");
    }
}

void VoiceHomeMainWindow::on_UserCommandButton_clicked() {
    RenameUserCommandDIalog dialog(this);
    connect(&dialog, &RenameUserCommandDIalog::textChanged,
            this, &VoiceHomeMainWindow::WriteOnUserButton);
    dialog.exec();
}

void VoiceHomeMainWindow::WriteOnUserButton(const QString &text) {
    ui->UserCommandButton->setText(text);
    saveUserCommand(text);
}

void VoiceHomeMainWindow::setupUIForHome() {
    ui->temp->setVisible(true);
    ui->co2->setVisible(true);
    ui->vlazh->setVisible(true);
    ui->co2text->setVisible(true);
    ui->vltext->setVisible(true);
    ui->temptext->setVisible(true);
    ui->co2icon->setVisible(true);
    ui->tempicon->setVisible(true);
    ui->vlicon->setVisible(true);

    ui->CheckBoxSvet->setVisible(false);
    ui->SvetLabel->setVisible(false);
    ui->CheckBoxFan->setVisible(false);
    ui->FanLabel->setVisible(false);
    ui->ChainikLabel->setVisible(false);
    ui->CheckBoxChainik->setVisible(false);
    ui->UserCommandButton->setVisible(false);
    ui->CheckBoxUserCommand->setVisible(false);
}

void VoiceHomeMainWindow::setupUIForCommands() {
    ui->temp->setVisible(false);
    ui->co2->setVisible(false);
    ui->vlazh->setVisible(false);
    ui->co2text->setVisible(false);
    ui->vltext->setVisible(false);
    ui->temptext->setVisible(false);
    ui->co2icon->setVisible(false);
    ui->tempicon->setVisible(false);
    ui->vlicon->setVisible(false);

    ui->CheckBoxSvet->setVisible(true);
    ui->SvetLabel->setVisible(true);
    ui->CheckBoxFan->setVisible(true);
    ui->FanLabel->setVisible(true);
    ui->ChainikLabel->setVisible(true);
    ui->CheckBoxChainik->setVisible(true);
    ui->UserCommandButton->setVisible(true);
    ui->CheckBoxUserCommand->setVisible(true);
}
