cmake_minimum_required(VERSION 3.16)

project(cardsearcher VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.2 COMPONENTS Quick Core QuickControls2 REQUIRED)
find_path(TESSERACT_INCLUDE_DIR tesseract/baseapi.h)
find_library(TESSERACT_LIBRARY tesseract)

find_path(LEPTONICA_INCLUDE_DIR leptonica/allheaders.h)
find_library(LEPTONICA_LIBRARY lept)

qt_add_executable(appcardsearcher
        src/main.cpp
        src/scan_rule.cpp
        src/luhna_validator.cpp

        include/scan_result.hpp
        include/validator.hpp
        include/scan_rule.hpp
        include/luhna_validator.hpp
        include/scanner_engine.hpp
        src/backend.cpp
        include/backend.hpp
        include/iscanner_parser.hpp
        include/text_scanner_parser.hpp
        include/image_scanner_parser.hpp
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

target_include_directories(appcardsearcher PRIVATE
        ${TESSERACT_INCLUDE_DIR}
        ${LEPTONICA_INCLUDE_DIR}
)

target_link_libraries(appcardsearcher
        PRIVATE Qt6::Quick Qt6::Core Qt6::QuickControls2
        ${TESSERACT_LIBRARY}
        ${LEPTONICA_LIBRARY})

install(TARGETS appcardsearcher
        BUNDLE DESTINATION .
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
