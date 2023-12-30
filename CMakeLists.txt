cmake_minimum_required(VERSION 3.5)

project(DealerCenter VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt5 REQUIRED COMPONENTS Widgets Sql)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Sql)

set(PROJECT_SOURCES
    Widgets/Dialogs/inputuserdialog.cpp
    Widgets/Dialogs/iinputdialogbase.cpp
    Widgets/Dialogs/logindialog.cpp
    Widgets/Dialogs/inputmanufacturerdialog.cpp
    Widgets/Dialogs/inputvalidatorfactory.cpp

    Widgets/appmenu.cpp
    Widgets/customerwidget.cpp
    Widgets/administratorwidget.cpp
    Widgets/mainwidget.cpp
    Widgets/customerstablewidget.cpp
    Widgets/manufacturerstablewidget.cpp
    Widgets/managerstablewidget.cpp
    Widgets/managerswidget.cpp
    Widgets/purchasewidget.cpp
    Widgets/transporttablewidget.cpp
    Widgets/purchasestablewidget.cpp

    Providers/transportdbprovider.cpp
    Providers/localdbproviderbase.cpp
    Providers/userdbprovider.cpp
    Providers/manufacturerdbprovider.cpp
    Providers/purchasedbprovider.cpp

    Services/transportdbservice.cpp
    Services/servicelocator.cpp
    Services/coreservice.cpp
    Services/userdbservice.cpp
    Services/ilocaldbservicebase.cpp
    Services/manufacturerdbservice.cpp
    Services/purchasesdbservice.cpp

    Models/manufacturersmodel.cpp
    Models/transportsmodel.cpp
    Models/purchasesmodel.cpp

    main.cpp
)

set(PROJECT_HEADERS
    Widgets/Dialogs/logindialog.h
    Widgets/Dialogs/inputuserdialog.h
    Widgets/Dialogs/iinputdialogbase.h
    Widgets/Dialogs/inputmanufacturerdialog.h
    Widgets/Dialogs/inputvalidatorfactory.h

    Widgets/appmenu.h
    Widgets/customerwidget.h
    Widgets/administratorwidget.h
    Widgets/mainwidget.h
    Widgets/customerstablewidget.h
    Widgets/manufacturerstablewidget.h
    Widgets/managerstablewidget.h
    Widgets/managerswidget.h
    Widgets/purchasewidget.h
    Widgets/transporttablewidget.h
    Widgets/purchasestablewidget.h

    Providers/transportdbprovider.h
    Providers/iprovider.h
    Providers/localbbstorage.h
    Providers/localdbproviderbase.h
    Providers/userdbprovider.h
    Providers/manufacturerdbprovider.h
    Providers/purchasedbprovider.h

    Services/ilocaldbservicebase.h
    Services/transportdbservice.h
    Services/iservice.h
    Services/servicelocator.h
    Services/userdbservice.h
    Services/coreservice.h
    Services/manufacturerdbservice.h
    Services/purchasesdbservice.h

    Common/userdata.h
    Common/transportdata.h
    Common/manufacturerdata.h
    Common/purchasedata.h

    Models/manufacturersmodel.h
    Models/transportsmodel.h
    Models/purchasesmodel.h    
)

add_executable(${PROJECT_NAME}
    ${PROJECT_HEADERS}
    ${PROJECT_SOURCES}
    resources.qrc
)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Widgets
                                          Qt${QT_VERSION_MAJOR}::Sql)

set_target_properties(${PROJECT_NAME} PROPERTIES
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS ${PROJECT_NAME}
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
