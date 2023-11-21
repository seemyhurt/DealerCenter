cmake_minimum_required(VERSION 3.5)

project(DilerCenter VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt5 REQUIRED COMPONENTS Widgets Sql)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Sql)

set(PROJECT_SOURCES
    Widgets/appmenu.cpp
    Widgets/inputcardialog.cpp
    Widgets/customerwidget.cpp
    Widgets/administratorwidget.cpp
    Widgets/inputuserdialog.cpp
    Widgets/iinputdialogbase.cpp
    Widgets/inputnumberdialog.cpp
    Widgets/mainwidget.cpp

    Providers/transportdbprovider.cpp
    Providers/localdbproviderbase.cpp
    Providers/userdbprovider.cpp
    Providers/manufacturerdbprovider.cpp

    Services/transportdbservice.cpp
    Services/servicelocator.cpp
    Services/coreservice.cpp
    Services/userdbservice.cpp
    Services/ilocaldbservicebase.cpp
    Services/manufacturerdbservice.cpp

    iinputvalidator.cpp
    main.cpp
)

set(PROJECT_HEADERS
    Widgets/appmenu.h
    Widgets/customerwidget.h
    Widgets/inputcardialog.h
    Widgets/inputnumberdialog.h
    Widgets/administratorwidget.h
    Widgets/inputuserdialog.h
    Widgets/iinputdialogbase.h
    Widgets/mainwidget.h

    Providers/transportdbprovider.h
    Providers/iprovider.h
    Providers/localbbstorage.h
    Providers/localdbproviderbase.h
    Providers/userdbprovider.h
    Providers/manufacturerdbprovider.h

    Services/ilocaldbservicebase.h
    Services/transportdbservice.h
    Services/iservice.h
    Services/servicelocator.h
    Services/userdbservice.h
    Services/coreservice.h
    Services/manufacturerdbservice.h

    Common/userdata.h
    Common/transportdata.h
    Common/manufacturerdata.h

    iinputvalidator.h
)

add_executable(DilerCenter
    ${PROJECT_HEADERS}
    ${PROJECT_SOURCES}
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
