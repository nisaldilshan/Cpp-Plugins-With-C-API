cmake_minimum_required(VERSION 3.0)
set (PROJECT_VERSION "1.0")
project(mylib-proj VERSION ${PROJECT_VERSION})

# To build shared libraries in Windows, we set CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS to TRUE.
# See https://cmake.org/cmake/help/v3.4/variable/CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS.html
# See https://blog.kitware.com/create-dlls-on-windows-without-declspec-using-new-cmake-export-all-feature/
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

# Create our library target
add_library(mylib SHARED)

target_include_directories(mylib
PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_sources(mylib PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp 
  ${CMAKE_CURRENT_SOURCE_DIR}/src/APIClass.cpp
)

# This will name your output .so files "libsomething.1.0" which is pretty useful
set_target_properties(mylib
PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION}
    CXX_VISIBILITY_PRESET hidden
    VISIBILITY_INLINES_HIDDEN 1
)

include(GenerateExportHeader)
generate_export_header(mylib)

# Let's set compiler-specific flags
if (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
    # G++
    target_compile_options(mylib PRIVATE -Wall -Wextra)
elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")
    # MSVC
    target_compile_options(mylib PRIVATE /EHsc /MTd /W2 /c)
    # Set the DLLEXPORT variable to export symbols
    target_compile_definitions(mylib PRIVATE WIN_EXPORT)
endif()