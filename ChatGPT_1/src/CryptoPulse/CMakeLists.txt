set_source_files_properties(Theme.qml PROPERTIES
    QT_QML_SINGLETON_TYPE TRUE
)

qt_add_executable(CryptoPulse
    ../main.cpp
)

qt_add_qml_module(CryptoPulse
    URI CryptoPulse
    VERSION 1.0
    QML_FILES
        Main.qml
        Theme.qml
        AppHeader.qml
        StatusBanner.qml
        WatchlistPanel.qml
        CoinDelegate.qml
        CoinDetail.qml
        PriceChart.qml
    SOURCES
        appcontroller.cpp
        appcontroller.h
        watchlistmodel.cpp
        watchlistmodel.h
)

target_link_libraries(CryptoPulse PRIVATE
    Qt6::Graphs
    Qt6::Network
    Qt6::Quick
    Qt6::QuickControls2
)

set_target_properties(CryptoPulse PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
    MACOSX_BUNDLE TRUE
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    WIN32_EXECUTABLE TRUE
)

install(TARGETS CryptoPulse
    BUNDLE DESTINATION .
    RUNTIME DESTINATION bin
)
