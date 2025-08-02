#include "serialportmanager.h"
#include <QDebug>

SerialPortManager::SerialPortManager(QObject *parent)
    : QObject(parent)
{
}

bool SerialPortManager::connectToPort(const QString &portName) {
    if (m_serial.isOpen())
        m_serial.close();

    m_serial.setPortName(portName);
    if (!m_serial.open(QIODevice::ReadWrite)) {
        emit errorOccurred("Не удалось открыть порт: " + m_serial.errorString());
        return false;
    }

    m_serial.setBaudRate(QSerialPort::Baud9600);
    m_serial.setDataBits(QSerialPort::Data8);
    m_serial.setParity(QSerialPort::NoParity);
    m_serial.setStopBits(QSerialPort::OneStop);
    m_serial.setFlowControl(QSerialPort::NoFlowControl);

    connect(&m_serial, &QSerialPort::readyRead, this, &SerialPortManager::onReadyRead);
    return true;
}

void SerialPortManager::onReadyRead() {
    while (m_serial.canReadLine()) {
        QByteArray data = m_serial.readLine();
        QString line = QString::fromUtf8(data).trimmed();
        if (!line.isEmpty()) {
            emit dataReceived(line);
        }
    }
}

void SerialPortManager::disconnect() {
    if (m_serial.isOpen()) {
        m_serial.close();
    }
}

bool SerialPortManager::isConnected() const {
    return m_serial.isOpen();
}
