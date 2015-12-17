include(../RibiLibraries/DesktopApplication.pri)

include(../RibiLibraries/Boost.pri)

include(../RibiLibraries/GeneralConsole.pri)
include(../RibiLibraries/GeneralDesktop.pri)

#Specific, console
include(../RibiClasses/CppCanvas/CppCanvas.pri)
include(../RibiClasses/CppDotMatrix/CppDotMatrix.pri)
include(../RibiClasses/CppReversi/CppReversi.pri)
include(../RibiClasses/CppTextCanvas/CppTextCanvas.pri)

#Specific, desktop
include(../RibiClasses/CppQtReversi/CppQtReversi.pri)

include(ReversiDesktop.pri)

SOURCES += qtmain.cpp

