# Hello World Avogadro extension.
# See http://avogadro.cc/ for more information.

# Project name
project(TorsionExtension)

# Minimum version of CMake that can be used
cmake_minimum_required(VERSION 2.6)

# Set up Qt
set(QT_MIN_VERSION "4.5.0")
find_package(Qt4 REQUIRED)

find_package(OpenBabel2 REQUIRED)

# Set up Avogadro
find_package(Avogadro REQUIRED)
include(${Avogadro_USE_FILE})

# Specify include directories
include_directories(
  # Needed to include Qt moc'd headers
  ${CMAKE_CURRENT_BINARY_DIR}
)

# Create a list of all source files
set( torsionextension_SRCS
     torsionextension.cpp
     torsiondialog.cpp
)

# Create a list of all ui files
set( torsionextension_UIS
     torsiondialog.ui
)

# Create the extension target torsionextension
avogadro_plugin(torsionextension "${torsionextension_SRCS}" "${torsionextension_UIS}")

