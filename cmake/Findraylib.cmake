# SPDX-License-Identifier: MIT
#
# CMake find module for raylib that works across Windows, macOS, and Linux
# without requiring a pre-configured raylib package configuration.
#
# The search honours the following hints (in order):
#   - raylib_ROOT cache variable
#   - raylib_DIR cache variable
#   - RAYLIB_ROOT or RAYLIB_DIR environment variables
#   - A handful of common installation prefixes (including the official
#     Windows installer default C:\raylib\raylib)
#
# It exposes the imported target `raylib::raylib` and the legacy variables
#   raylib_FOUND
#   raylib_INCLUDE_DIRS
#   raylib_LIBRARIES
#   raylib_SYSTEM_LIBS

include(FindPackageHandleStandardArgs)

set(_raylib_hint_dirs "")

foreach(var IN ITEMS raylib_ROOT raylib_DIR)
    if(DEFINED ${var})
        list(APPEND _raylib_hint_dirs "${${var}}")
    endif()
endforeach()

foreach(env_var IN ITEMS RAYLIB_ROOT RAYLIB_DIR)
    if(DEFINED ENV{${env_var}})
        list(APPEND _raylib_hint_dirs "$ENV{${env_var}}")
    endif()
endforeach()

list(APPEND _raylib_hint_dirs
    "${CMAKE_CURRENT_LIST_DIR}/.."
    "C:/raylib"
    "C:/raylib/raylib"
    "C:/raylib/w64devkit/x86_64-w64-mingw32"
    "/opt/homebrew"
    "/usr/local"
    "/usr"
)

list(REMOVE_DUPLICATES _raylib_hint_dirs)

find_path(raylib_INCLUDE_DIR
    NAMES raylib.h
    HINTS ${_raylib_hint_dirs}
    PATH_SUFFIXES include include/raylib src
)

find_library(raylib_LIBRARY
    NAMES raylib libraylib
    HINTS ${_raylib_hint_dirs}
    PATH_SUFFIXES lib lib64 libs src
)

find_package_handle_standard_args(raylib
    REQUIRED_VARS raylib_INCLUDE_DIR raylib_LIBRARY
)

if(NOT raylib_FOUND)
    return()
endif()

set(raylib_INCLUDE_DIRS "${raylib_INCLUDE_DIR}")

set(_raylib_system_libs "")
if(WIN32)
    list(APPEND _raylib_system_libs winmm gdi32 opengl32 shell32)
elseif(APPLE)
    # Prefer the newer Metal backend, fall back to the OpenGL stack if missing.
    find_library(_raylib_metal Metal)
    find_library(_raylib_cocoa Cocoa)
    find_library(_raylib_iokit IOKit)
    find_library(_raylib_corevideo CoreVideo)

    foreach(_lib IN ITEMS _raylib_metal _raylib_cocoa _raylib_iokit _raylib_corevideo)
        if(${${_lib}})
            list(APPEND _raylib_system_libs "${${_lib}}")
        endif()
    endforeach()
else()
    find_package(OpenGL REQUIRED)
    find_package(X11 REQUIRED)
    list(APPEND _raylib_system_libs m pthread ${OPENGL_LIBRARIES} ${X11_LIBRARIES})
    if(CMAKE_DL_LIBS)
        list(APPEND _raylib_system_libs ${CMAKE_DL_LIBS})
    endif()
endif()

# Filter out any NOTFOUND entries that may sneak in on certain toolchains.
set(_raylib_filtered_libs "")
foreach(_lib IN LISTS _raylib_system_libs)
    if(_lib AND NOT _lib MATCHES "-NOTFOUND$")
        list(APPEND _raylib_filtered_libs "${_lib}")
    endif()
endforeach()
set(raylib_SYSTEM_LIBS ${_raylib_filtered_libs})

set(raylib_LIBRARIES "${raylib_LIBRARY}" ${raylib_SYSTEM_LIBS})

if(NOT TARGET raylib::raylib)
    add_library(raylib::raylib UNKNOWN IMPORTED)
    set_target_properties(raylib::raylib PROPERTIES
        IMPORTED_LOCATION "${raylib_LIBRARY}"
        INTERFACE_INCLUDE_DIRECTORIES "${raylib_INCLUDE_DIRS}"
    )
    if(raylib_SYSTEM_LIBS)
        set_property(TARGET raylib::raylib PROPERTY
            INTERFACE_LINK_LIBRARIES "${raylib_SYSTEM_LIBS}"
        )
    endif()
endif()

mark_as_advanced(raylib_INCLUDE_DIR raylib_LIBRARY)
