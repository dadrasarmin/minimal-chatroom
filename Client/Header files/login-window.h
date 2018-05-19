//
// Created by dadrasarmin on 4/4/17.
//

#ifndef DIY_WINDOW_H
#define DIY_WINDOW_H

#include "Header files/chatroom-window.h"

#include <QThread>
#include <QLabel>

class loginWindow:public QWidget
{
    Q_OBJECT

public:
    // Prefixing the explicit keyword to the constructor prevents the compiler from using that constructor for implicit conversions
    explicit loginWindow( QWidget *parent = 0 );

    std::string id;
    QLineEdit *idInput;
    std::string ip;
    QLineEdit *ipInput;
    QPushButton *notificationOn;
    QPushButton *notificationOff;
    bool notificatoinStatus = true; // notification is by default in ON mode
    QPushButton *loginButton;

public slots:
    void login();

private slots:
    void notifOn();
    void notifOff();
};

#endif //DIY_WINDOW_H
