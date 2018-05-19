//
// Created by dadrasarmin on 4/3/17.
//

// program use QApplication for gui
#include <QApplication>
#include "Header files/server.h"

// "argc" is the number of arguments being passed into my program from the command line and "argv" is the array of arguments.
// it's needed for process command line arguments.
int main( int argc, char **argv ) // function main begins program execution
{
    // The QApplication class manages the GUI application's control flow and main settings.
    QApplication myApplication( argc, argv );

    server myServer; // Create an object from server class
    myServer.show(); // Shows the window.

    return myApplication.exec(); // prevent from ending program

} // end main functoin
