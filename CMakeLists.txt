cmake_minimum_required(VERSION 3.16)

project(TouristManager VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include Qt Widgets and SQL modules
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Sql)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Sql)

set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    addpackage.h
    addpackage.cpp
    addpackage.ui
    registertourist.h
    registertourist.cpp
    registertourist.ui
    findtourist.h
    findtourist.cpp
    findtourist.ui
    findpackage.h
    findpackage.cpp
    findpackage.ui
    databaseheader.h
    resource.qrc
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(TouristManager
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        resource.qrc
    )
else()
    if(ANDROID)
        add_library(TouristManager SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(TouristManager
            ${PROJECT_SOURCES}
        )
    endif()
endif()

# Link Qt Widgets and SQL libraries
target_link_libraries(TouristManager PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Sql)

# macOS/iOS Bundle settings (if applicable)
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.TouristManager)
endif()
set_target_properties(TouristManager PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS TouristManager
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(TouristManager)
endif()
