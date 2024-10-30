#include "voicehomemainwindow.h"
#include "ui_voicehomemainwindow.h"

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

QString pathtovcres = "C:/vcres";
QDir vcresdir;
QString filePath = pathtovcres + "/commands.txt";
QFile commandsfile(filePath);

QBluetoothAddress targetAddress2("00:19:06:34:DD:B5");
QBluetoothUuid serialPortUuid2 = QBluetoothUuid(QStringLiteral("00001101-0000-1000-8000-00805F9B34FB"));
QBluetoothAddress addr2(targetAddress2);
QBluetoothSocket *socket2 = new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol);


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
void VoiceHomeMainWindow::setcommand(){
    if(!vcresdir.exists(pathtovcres)){
        vcresdir.mkpath(pathtovcres);
    }
    if(!commandsfile.exists()){
        if (commandsfile.open(QIODevice::WriteOnly | QIODevice::Text)) {
                QTextStream out(&commandsfile);
                QStringList lines;
                lines << "Включи свет" << "Включи вентилятор" << "Включи чайник" << "Выключи свет" << "Выключи вентилятор" << "Выключи чайник" << "Выключи всё";
                out << lines.join("\n");
                commandsfile.close();
        }
    }
    QVector <QString> commands;
    if (commandsfile.open(QFile::ReadOnly | QFile::Text)) {
        QTextStream in(&commandsfile);
        QString text = in.readAll();
        commandsfile.close();
        QString comm = "";
        for(int i = 0; i < text.size(); i++){
            if(text[i] != '\n'){
                comm+=text[i];
            }
            else{
                commands.push_back(comm);
                comm = "";
            }
        }
        commands.push_back(comm);
    }
    ui->listWidget->clear();
    for (auto str : commands) {
            ui->listWidget->addItem(str);
    }
}
void VoiceHomeMainWindow::voicehomeprep(){
    setcommand();
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
    ui->listWidget->setVisible(false);
    ui->deletecommand->setVisible(false);
    ui->addcommand->setVisible(false);
    ui->commandline->setVisible(false);
    ui->temp->setVisible(true);
    ui->co2->setVisible(true);
    ui->vlazh->setVisible(true);
}


void VoiceHomeMainWindow::on_CommandsButton_clicked()
{
    ui->temp->setVisible(false);
    ui->co2->setVisible(false);
    ui->vlazh->setVisible(false);
    ui->listWidget->setVisible(true);
    ui->deletecommand->setVisible(true);
    ui->addcommand->setVisible(true);
    ui->commandline->setVisible(true);
}


void VoiceHomeMainWindow::on_addcommand_clicked()
{
    writecommand();
}
void VoiceHomeMainWindow::writecommand(){
    if(ui->commandline->text().size() != 0){
    if (commandsfile.open(QIODevice::Append | QIODevice::Text)) {
            QTextStream out(&commandsfile);
            out << '\n' << ui->commandline->text();
            commandsfile.close();
        }
    }
    ui->commandline->setText("");
    setcommand();
}

void VoiceHomeMainWindow::on_deletecommand_clicked()
{
    QVector <QString> commands;
    bool startdelete = true;
    if(commandsfile.size() == 0){
        QMessageBox::warning(this, "error", "Нельзя удалить пустую комманду!");
        startdelete = false;
    }
    if(startdelete == true){
    if (commandsfile.open(QFile::ReadOnly | QFile::Text)) {
        QTextStream in(&commandsfile);
        QString text = in.readAll();
        commandsfile.close();
        QString comm = "";
        for(int i = 0; i < text.size(); i++){
            if(text[i] != '\n'){
                comm+=text[i];
            }
            else{
                commands.push_back(comm);
                comm = "";
            }
        }
    }
    if (commandsfile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&commandsfile);
        out << commands[0];
        for (int i = 1; i < commands.size(); i++) {
            out << "\n" << commands[i];
        }
        commandsfile.close();
    }
    setcommand();
    }
}


void VoiceHomeMainWindow::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    int index = ui->listWidget->row(item) + 1;
    try{
            QString message = QString::number(index);
            socket2->write(message.toUtf8());
    }
    catch(QBluetoothLocalDevice::Error error){
        QString errorString = QString("Bluetooth Error: %1").arg(static_cast<int>(error));
        QMessageBox::critical(this, "err", errorString);
    }
}

