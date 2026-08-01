cmake_minimum_required(VERSION 3.21)

project(CryptoPulse VERSION 1.0 LANGUAGES CXX)

find_package(Qt6 6.11 REQUIRED COMPONENTS
    Graphs
    Network
    Quick
    QuickControls2
)

qt_standard_project_setup(REQUIRES 6.11)

set(QT_QML_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/qml")

add_subdirectory(src/CryptoPulse)
