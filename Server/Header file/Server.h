//
// Created by dadrasarmin on 4/3/17.
//

#ifndef DIY_SERVER_H
#define DIY_SERVER_H

// The QtWidgets Module provides a set of UI elements to create classic desktop-style user interfaces.
#include <QtWidgets>
// The QWidget class is the base class of all user interface objects.
#include <QWidget>
// QtNetwork provides a set of APIs for programming applications that use TCP/IP.
#include <QtNetwork>
// The QTcpServer class provides a TCP-based server.
#include <QTcpServer>
// Program uses vectors.
#include <vector>
// The QByteArray class provides an array of bytes, here program uses number function of it
#include <QByteArray>
using namespace std;

class server:public QWidget
{
    Q_OBJECT

public:
    // Prefixing the explicit keyword to the constructor prevents the compiler from using that constructor for implicit conversions
    explicit server();

private:

    vector<QTcpServer *> *serverVector; // a vector that handle server objects
    vector<QTcpSocket *> *clientsVector; // a vector that handle clients objects
    QTcpServer *serverObject; // create an object from QTcpServer
    quint16 newPort; // Typedef for signed short. This type is guaranteed to be 16-bit on all platforms supported by Qt.

    // From another class, you can't call a private slot as a function,
    // but if you emit a signal connected to that private slot, you can invoke it.
private slots:

    void createServer(); // when a new client connected to server this function do required things so
    // server listen to this new user too.
    void createClient(); // add new client to clientsVeoctor and if any message send to server
    // from this client, call displayMessage to send this message for everyone
    void displayMessage(); // display messages for everyone who listen to this ip and port
};


#endif //DIY_SERVER_H
