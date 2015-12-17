include(../RibiLibraries/ConsoleApplication.pri)

#Libs
include(../RibiLibraries/Boost.pri)
include(../RibiLibraries/GeneralConsole.pri)
#include(../RibiLibraries/Fparser.pri)

#Specific, console
include(../RibiClasses/CppCanvas/CppCanvas.pri)
include(../RibiClasses/CppDotMatrix/CppDotMatrix.pri)
include(../RibiClasses/CppReversi/CppReversi.pri)
include(../RibiClasses/CppTextCanvas/CppTextCanvas.pri)
include(../Reversi/ReversiConsole.pri)

SOURCES += main.cpp
