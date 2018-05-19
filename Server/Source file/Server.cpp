//
// Created by dadrasarmin on 4/3/17.
//

#include "Header files/server.h"

// constructor block
server::server()
{
    serverVector = new vector<QTcpServer *>; // a vector that handle server objects
    clientsVector = new vector<QTcpSocket *>; // a vector that handle clients sockets
    newPort = 4445; // type quint16

    serverObject = new QTcpServer; // create an object from QTcpServer

    // The QHostAddress class provides an IP address.
    // listen function tells the server to listen for incoming connections on address address and port port.
    serverObject -> listen( QHostAddress::LocalHost, 4444 );

    // if newConnection called then call createConnection method
    // newConnection(), This signal is emitted every time a new connection is available.
    connect( serverObject, SIGNAL( newConnection() ), this, SLOT( createServer() ) );

    // graphical settings
    // The QLabel widget provides a text or image display.
    QLabel *serverDetails = new QLabel( this ); // create an object from class QLabel.
    serverDetails -> setText( "Server is runnig on: 127.0.0.1 and port: 4444" ); // what text should be shown
    serverDetails -> setGeometry( 5, 5, 300, 20 ); // where show this text
    // end graphical settings
} // end constructor

// createServer method, when a new client connected to server this method do required things so
// server listen (and write) to this new user.
void server::createServer()
{
    // nextPendingConnectoin function returns the next pending connection as a connected QTcpSocket object.
    QTcpSocket *newUserSocket = serverObject -> nextPendingConnection();

    // QByteArray::number returns a byte array containing the string equivalent of the number n to base 10
    // write() is an overloaded function writes data from a zero-terminated string of 8-bit characters to the device.
    newUserSocket -> write( QByteArray::number( newPort ) );

    QTcpServer *newServer = new QTcpServer; // create an object from QTcpServer class
    // listen function tells the server to listen for incoming connections on address address and port port.
    newServer -> listen( QHostAddress::LocalHost, newPort );
    // push_back function adds a new element at the end of the vector, after its current last element.
    serverVector -> push_back( newServer );

    // when newConnectoin method called, this signal is emitted every time a new connection is available.
    connect( newServer, SIGNAL ( newConnection() ), this, SLOT( createClient() ) );

    newPort++;
}
// end createServer method

// createClient method
void server::createClient()
{
    // The QList class is a template class that provides lists.back function is provided for STL
    // (standard template library) compatibility. returns a reference to the last item in the list.
    QTcpSocket *clientSocket = serverVector -> back() -> nextPendingConnection();

    clientsVector -> push_back( clientSocket );

    // readyRead function signifying that data has been received
    connect( clientSocket, SIGNAL( readyRead() ), this, SLOT( displayMessage() ) );
}
// end createClient method

// displayMessage method listen to messages and display them for everyone who listen to this ip and port
void server::displayMessage()
{
    // QString stores a string of 16-bit QChars, where each QChar corresponds one Unicode 4.0 character.
    QString message;

    for( int i = 0; i < clientsVector -> size(); i++ )
    {
        // this module find what client send messeges to the server
        // bytesAvailable function returns the number of bytes that are available for reading.
        if( clientsVector -> at( i ) -> bytesAvailable() ) // if number of bytes are zero "if" doesn't execute
        {
            // readAll function reads all remaining data from the device, and returns it as a byte array.
            message = clientsVector -> at( i ) -> readAll();
            break; // exit from "for" and print message on screen
        }
    } // end for module

    // this module display message on monitor window clients that present on the chatroom
    for( int i = 0; i < clientsVector -> size(); i++ )
        clientsVector -> at(i) -> write( &message.toStdString()[0] );
}
// end displayMessage method
