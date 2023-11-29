cmake_minimum_required(VERSION 3.5)

project(GameLab3 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    CommandInterpreter.cpp
    CommandInterpreter.h
    GameWidget.cpp
    GameWidget.h
    GameController.cpp
    GameController.h
)

# Use the generated ui_MainWindow.h file
set(UIS
    mainwindow.ui
)

add_executable(GameLab3 ${SOURCES} ${UIS})

target_link_libraries(GameLab3 PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(GameLab3 PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS GameLab3
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(GameLab3)
endif()
