cmake_minimum_required(VERSION 3.16)

project(cardsearcher VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.2 COMPONENTS Quick Core QuickControls2 REQUIRED)

qt_add_executable(appcardsearcher
    src/main.cpp
    src/scan_rule.cpp
    src/luhna_validator.cpp

    include/scan_result.hpp
    include/validator.hpp
    include/scan_rule.hpp
    include/luhna_validator.hpp
    include/scanner_engine.hpp
)

qt_add_qml_module(appcardsearcher
    URI cardsearcher
    VERSION 1.0
    QML_FILES main.qml
)

set_target_properties(appcardsearcher PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appcardsearcher
    PRIVATE Qt6::Quick Qt6::Core Qt6::QuickControls2)

install(TARGETS appcardsearcher
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
