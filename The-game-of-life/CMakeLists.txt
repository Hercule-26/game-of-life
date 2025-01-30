cmake_minimum_required(VERSION 3.16)

project(game-of-life VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Network Widgets)

set(LOCAL_SOURCES
    local/mainwindow_local.cpp
    local/mainwindow_local.h
    local/mainwindow_local.ui
    local/view/clickableRect.cpp
    local/view/clickableRect.h
    local/view/tableWidget.cpp
    local/view/tableWidget.h
)

set(ONLINE_SOURCES
    #online/view/clickableRect.cpp
    #online/view/clickableRect.h
    #online/view/tableWidget.cpp
    #online/view/tableWidget.h
    online/mainwindow_online.h
    online/mainwindow_online.cpp
)

set(NETWORK_SOURCES
    online/network/client.cpp
    online/network/client.h
    online/network/requestType.h
)

set(MODEL_SOURCES
    local/model/model.cpp
    local/model/model.h
    local/model/table.h
)

# Tous les fichiers source
set(PROJECT_SOURCES
    ${LOCAL_SOURCES}
    ${NETWORK_SOURCES}
    ${ONLINE_SOURCES}
    ${MODEL_SOURCES}
)

if(QT_VERSION_MAJOR GREATER_EQUAL 6)
    qt_add_executable(game-of-life
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    add_executable(game-of-life ${PROJECT_SOURCES}
        main.cpp
        mainwindow.cpp
        mainwindow.h
    )
endif()

# Lier les bibliothèques Qt nécessaires au projet
target_link_libraries(game-of-life PRIVATE Qt6::Core Qt6::Network Qt6::Widgets)

# Définir les propriétés du target
set_target_properties(game-of-life PROPERTIES
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

# Installer le projet
install(TARGETS game-of-life
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Finaliser l'exécutable si Qt6
if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(game-of-life)
endif()
