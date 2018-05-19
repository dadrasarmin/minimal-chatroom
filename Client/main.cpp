//
// Created by dadrasarmin on 4/4/17.
//

// program use QApplication for gui
#include <QApplication>
#include "Header files/chatroom-window.h"
#include "Header files/login-window.h"

// function main begins program execution
int main( int argc, char **argv )
{
    // The QApplication class manages the GUI application's control flow and main settings.
    QApplication app(argc,argv);

    // create a new object of loginWindow for new client
    new loginWindow;

    return app.exec();
} // end main functoin
