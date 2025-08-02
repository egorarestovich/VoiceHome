#pragma once
#include <QObject>
#include <QSerialPort>

class SerialPortManager : public QObject {
    Q_OBJECT

public:
    explicit SerialPortManager(QObject *parent = nullptr);
    bool connectToPort(const QString &portName = "COM3");
    void disconnect();
    bool isConnected() const;

    QSerialPort* serialPort() { return &m_serial; }

signals:
    void dataReceived(const QString &data);
    void errorOccurred(const QString &error);

private slots:
    void onReadyRead();

private:
    QSerialPort m_serial;
};
