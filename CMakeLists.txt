cmake_minimum_required(VERSION 3.12)
project(wavelette VERSION 0.1.0 LANGUAGES CXX DESCRIPTION "Wavelette is a library for loading and processing spectral power distribution images..")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
include(GNUInstallDirs)

# Add colorama subdirectory
add_subdirectory(external/colorama)
find_package(ZLIB REQUIRED)
find_package(PNG REQUIRED)

set(WAVELETTE_SOURCES
    src/spdimage.cpp
    src/image.cpp
)
if(MSVC)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()
# Create library target
add_library(wavelette SHARED ${WAVELETTE_SOURCES})

set_target_properties(wavelette PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
    PUBLIC_HEADER include/spdimage.h
    WINDOWS_EXPORT_ALL_SYMBOLS ON
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/bin/Debug"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/bin/Release"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/lib/Debug"
    LIBRARY_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/lib/Release"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/lib/Debug"
    ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/lib/Release"
)

configure_file(wavelette.pc.in wavelette.pc @ONLY)

target_include_directories(wavelette 
    PRIVATE 
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
        ${CMAKE_CURRENT_SOURCE_DIR}/external/colorama/include
)

target_link_libraries(wavelette 
    PUBLIC 
        colorama
        PNG::PNG
)

add_dependencies(wavelette colorama)

install(TARGETS wavelette
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(FILES ${CMAKE_BINARY_DIR}/wavelette.pc
    DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)