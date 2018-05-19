//
// Created by dadrasarmin on 4/4/17.
//

#include "Header files/chatroom-window.h"
using namespace std;

// constructor
chatroom::chatroom( QWidget *parent ) : QWidget( parent )
{
    monitor = new QTextEdit( this ); // monitor is an object from class QTextEdit
    monitor -> setGeometry(5, 5, 300, 300 ); // a 300*300 window that messages display on it
    monitor -> setReadOnly( true ); // cannot edit it

    typeHere = new QTextEdit( this ); // typeHere is an object from class QTextEdit and where user type input
    typeHere -> setGeometry( 5, 310, 235, 60 ); // a 235*60 window that messages can be written in it

    sendButton = new QPushButton( "Send", this ); // sendButton is an object from class QPushButton
    sendButton -> setGeometry( 245, 310, 60, 60 ); // a 60*60 button for send
    connect( sendButton, SIGNAL( clicked() ),this,SLOT( talk() ) ); // if send button clicked then call sendData method

    shortcut = new QShortcut( QKeySequence( "Alt+Return" ), this); // create a keyboard shortcut from class QShortcut for sending message
    connect( shortcut, SIGNAL( activated() ), this, SLOT( talk() ) ); // if shortcut entered then call sendData method

    QLabel *message = new QLabel( this ); // message is an object from class QLabel
    message -> setText( "Press \"Alt + Enter\" to Send" ); // it notify user how to use shortcut
    message -> setGeometry( 5 , 375, 300, 20 ); // it's show below the typeHere window

    notifPlayer = new QMediaPlayer(); // create an object from QMediaPlayer class
    notifPlayer -> setMedia( QUrl::fromLocalFile(
            QFileInfo( "/home/dadrasarmin/CLionProjects/minimalistic-chatroom/Client/demonstrative.mp3" ).absoluteFilePath() ) ); // load notificatoin sound

    this -> show(); // show a window with above features
} // end constructor

// start method takes id and ip, then connected to server with appropriate address then takes new port and
// connect to it. then every time new message sent to server it call getData method
void chatroom::start( std::string id, QString ip, bool notificationStatus)
{
    userName = id; // assign id value to userName
    ipAddress = ip;  // assign ip value to ipAddress
    notif = notificationStatus;

    userTcpSocket = new QTcpSocket; // create and object from QTcpSocket class
    userTcpSocket -> connectToHost( ipAddress, 4444 ); // attempts to make a connection to ipAddress on the given port.
    userTcpSocket -> waitForReadyRead(); // this function blocks until new data is available for reading
    // and the readyRead() signal has been emitted.
    userPort = userTcpSocket -> readAll().toUShort(); // readllAll function reads all remaining data from the device,
    // and returns it as a byte array. toUshort function returns the string converted to an unsigned short using base 10.
    userTcpSocket -> disconnectFromHost(); // attempts to close the previous socket
    userTcpSocket -> connectToHost( ipAddress, userPort ); // attempts to make a connection to ipAddress on the port
    // that server gives to it.

    // readyRead function, this signal is emitted once every time new data is available for reading from
    // the device's current read channel. It will only be emitted again once new data is available,
    // such as when a new payload of network data has arrived on your network socket,
    // or when a new block of data has been appended to your device.
    connect( userTcpSocket, SIGNAL( readyRead() ), this, SLOT( updateMonitor() ) ); // if signal emitted call getData function
} // end start method

// updateMonitor method extends the monitor by appending all remaining data from the server at the end of its current value.
void chatroom::updateMonitor()
{
    QString message = userTcpSocket -> readAll(); // get message from server
    // below module check wheter sender is this user or another person
    string text = message.toStdString(); // change message into string
    string name; // this string store sender name
    for( int i=1; i < text.length() && text[i] != ' '; i++ ) // this module run until first space
        name += text[i]; // get sender name letter by letter
    if( name != this -> userName && notif ) // if this message doesn't send by this user and user choose to have notificatoin
        messageNotification(); // play notificatoin sound
    // end checking who is message sender
    monitor -> append( message ); // append text to the monitor window
} // end getData method

// talk method combine typeHere content and userName and a colon and write it on server and clear the typeHere window
void chatroom::talk()
{
    string myMessage = this -> userName + " : " + typeHere -> toPlainText().toStdString(); // add userName and a colon to
    // first of the message and assign it to a string called myMessage
    userTcpSocket -> write( &myMessage[0] ); // write myMessage on server
    typeHere -> clear(); // clear typeHere window after write data to server
} // end talk method

// messageNotification method play notification if notif value is true
void chatroom::messageNotification()
{
    notifPlayer -> play(); // play notification file that loaded
}
// end messageNotification
