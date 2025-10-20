# Locate raylib and provide the raylib::raylib imported target.
#
# Variables provided on success:
#   raylib_FOUND
#   raylib_INCLUDE_DIRS
#   raylib_LIBRARIES
#
# The search can be guided with:
#   raylib_ROOT, raylib_DIR (CMake variables)
#   RAYLIB_ROOT, RAYLIB_DIR (environment variables)
#   raylib_USE_STATIC_LIBS (ON to prefer libraylib.a / raylib.lib)
#
# Additional link dependencies can be supplied through the cache variable
#   raylib_LINK_DEPENDENCIES.

include(FindPackageHandleStandardArgs)

if(NOT DEFINED raylib_USE_STATIC_LIBS)
    set(raylib_USE_STATIC_LIBS OFF)
endif()

set(raylib_LINK_DEPENDENCIES "" CACHE STRING "Extra libraries to link alongside raylib")

set(_raylib_roots)

foreach(_var raylib_ROOT raylib_DIR)
    if(DEFINED ${_var} AND NOT "${${_var}}" STREQUAL "")
        list(APPEND _raylib_roots "${${_var}}")
    endif()
endforeach()

foreach(_env RAYLIB_ROOT RAYLIB_DIR)
    if(NOT "$ENV{${_env}}" STREQUAL "")
        list(APPEND _raylib_roots "$ENV{${_env}}")
    endif()
endforeach()

if(WIN32)
    list(APPEND _raylib_roots
        "C:/raylib"
        "C:/raylib/raylib"
        "C:/Program Files/raylib"
        "C:/Program Files (x86)/raylib"
    )
endif()

list(REMOVE_DUPLICATES _raylib_roots)

find_path(raylib_INCLUDE_DIR
    NAMES raylib.h
    HINTS ${_raylib_roots}
    PATH_SUFFIXES include inc src
)

set(_raylib_library_names raylib)
if(raylib_USE_STATIC_LIBS)
    list(INSERT _raylib_library_names 0 libraylib.a raylib.lib)
else()
    list(APPEND _raylib_library_names raylib.dll)
endif()

find_library(raylib_LIBRARY
    NAMES ${_raylib_library_names}
    HINTS ${_raylib_roots}
    PATH_SUFFIXES lib lib64 lib/static lib/Release lib/Debug src
)

find_package_handle_standard_args(raylib
    REQUIRED_VARS raylib_INCLUDE_DIR raylib_LIBRARY
)

if(raylib_FOUND)
    set(raylib_INCLUDE_DIRS "${raylib_INCLUDE_DIR}")
    set(raylib_LIBRARIES "${raylib_LIBRARY}")
    mark_as_advanced(raylib_LIBRARY raylib_INCLUDE_DIR)

    if(NOT TARGET raylib::raylib)
        add_library(raylib::raylib UNKNOWN IMPORTED)
        set_target_properties(raylib::raylib PROPERTIES
            IMPORTED_LOCATION "${raylib_LIBRARY}"
            INTERFACE_INCLUDE_DIRECTORIES "${raylib_INCLUDE_DIR}"
        )

        if(raylib_LINK_DEPENDENCIES STREQUAL "")
            if(WIN32)
                set(raylib_LINK_DEPENDENCIES
                    winmm
                    gdi32
                    opengl32
                    user32
                    shell32
                )
            elseif(APPLE)
                set(raylib_LINK_DEPENDENCIES
                    "-framework OpenGL"
                    "-framework Cocoa"
                    "-framework IOKit"
                    "-framework CoreVideo"
                )
            else()
                set(raylib_LINK_DEPENDENCIES
                    m
                    pthread
                    dl
                )
            endif()
        endif()

        if(raylib_LINK_DEPENDENCIES)
            set_property(TARGET raylib::raylib PROPERTY
                INTERFACE_LINK_LIBRARIES "${raylib_LINK_DEPENDENCIES}"
            )
        endif()

        if(raylib_USE_STATIC_LIBS)
            set_property(TARGET raylib::raylib PROPERTY
                IMPORTED_LINK_INTERFACE_LANGUAGES "C"
            )
        endif()
    endif()

    set(raylib_LIBRARIES raylib::raylib)
endif()
