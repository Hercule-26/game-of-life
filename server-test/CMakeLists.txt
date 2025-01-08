cmake_minimum_required(VERSION 3.16)

project(server-test LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Activer AUTOMOC et AUTOMOC pour Qt6
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)  # Si vous utilisez des ressources Qt (non utilisé ici mais au cas où)

# Ajout de l'exécutable du serveur
add_executable(server-test main.cpp)

# Trouver Qt6 avec les modules nécessaires (Core et Network)
find_package(Qt6 REQUIRED Core Network)

# Ajouter les includes de Qt6
target_include_directories(server-test PRIVATE ${Qt6Core_INCLUDE_DIRS} ${Qt6Network_INCLUDE_DIRS})

# Lier les bibliothèques Qt6 à l'exécutable
target_link_libraries(server-test Qt6::Core Qt6::Network)

# Installation des fichiers compilés
include(GNUInstallDirs)
install(TARGETS server-test
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
