//
// Created by dadrasarmin on 4/4/17.
//

#ifndef DIY_CLIENT_H
#define DIY_CLIENT_H

#include <QtWidgets>
#include <QtNetwork>
#include <QComboBox>
#include <QShortcut>
#include <QtMultimedia/qmediaplayer.h>
#include <QFileInfo>

class chatroom:public QWidget
{
    Q_OBJECT

public:

    explicit chatroom( QWidget *parent = 0 );
    void start( std::string id, QString ip, bool notificationStatus );

    QTextEdit *monitor;
    QTextEdit *typeHere;
    QPushButton *sendButton;
    QShortcut *shortcut;

private:

    std::string userName;
    QString ipAddress;
    bool notif;
    QMediaPlayer *notifPlayer;

    QTcpSocket *userTcpSocket;
    quint16 userPort;

private slots:

    void updateMonitor();
    void talk();
    void messageNotification();
};

#endif //DIY_CLIENT_H
