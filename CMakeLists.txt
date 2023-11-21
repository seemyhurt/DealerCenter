cmake_minimum_required(VERSION 3.5)

project(DilerCenter VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Sql)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Sql)

set(PROJECT_SOURCES
    appmenu.cpp

    TransportDBProvider.cpp
    transportdbservice.cpp
    customerwidget.cpp
    iinputvalidator.cpp
    ilocaldbservicebase.cpp
    inputcardialog.cpp

    main.cpp
    localdbproviderbase.cpp
    mainwidget.cpp
    servicelocator.cpp
)

set(PROJECT_HEADERS
    appmenu.h

    TransportDBProvider.h
    transportdbservice.h
    customerwidget.h
    iinputvalidator.h
    ilocaldbservicebase.h
    inputcardialog.h
    iprovider.h
    iservice.h

    localbbstorage.h
    localdbproviderbase.h
    mainwidget.h
    servicelocator.h
    userdata.h
)

add_executable(DilerCenter
    ${PROJECT_HEADERS}
    ${PROJECT_SOURCES}
    userdbprovider.h userdbprovider.cpp

    iinputdialogbase.h iinputdialogbase.cpp
    transportdata.h
    UserData.h
    inputuserdialog.h inputuserdialog.cpp
    userdbservice.h userdbservice.cpp
    inputnumberdialog.h inputnumberdialog.cpp
    coreservice.h coreservice.cpp
    administratorwidget.h administratorwidget.cpp

)

target_link_libraries(DilerCenter PRIVATE Qt${QT_VERSION_MAJOR}::Widgets
                                          Qt${QT_VERSION_MAJOR}::Sql)

set_target_properties(DilerCenter PROPERTIES
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS DilerCenter
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
