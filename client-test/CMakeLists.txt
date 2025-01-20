cmake_minimum_required(VERSION 3.16)

project(client-test LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Ajout de l'exécutable du client
add_executable(client-test main.cpp
    client.h
    client.cpp)

# Trouver Qt5 avec les modules nécessaires (Core et Network)
find_package(Qt6 REQUIRED Core Network)

# Lier les bibliothèques Qt5 à l'exécutable
target_link_libraries(client-test Qt6::Core Qt6::Network)

# Installation des fichiers compilés
include(GNUInstallDirs)
install(TARGETS client-test
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
