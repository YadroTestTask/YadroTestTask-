if (CPPUTEST_LIBRARIES AND CPPUTEST_INCLUDE_DIRS)
    set(CPPUTEST_FOUND TRUE)
else( )
    find_path(CPPUTEST_INCLUDE_DIR
        NAMES CppUTest CppUTestExt
        PATHS /usr/include
              /usr/local/include
              /opt/local/include
    )

    find_library(CPPUTEST_LIBRARY
        NAMES CppUTest CppUTestExt
        PATHS /usr/lib
              /usr/local/lib
              /opt/local/lib
    )

    set(CPPUTEST_INCLUDE_DIRS ${CPPUTEST_INCLUDE_DIR})
    set(CPPUTEST_LIBRARIES    ${CPPUTEST_LIBRARY})

    if (CPPUTEST_INCLUDE_DIRS AND CPPUTEST_LIBRARIES)
        set(CPPUTEST_FOUND TRUE)
    endif( )

    if (CPPUTEST_FOUND)
        message(STATUS "Found CppUTest:")
        message(STATUS " - Includes: ${CPPUTEST_INCLUDE_DIRS}")
        message(STATUS " - Libraries: ${CPPUTEST_LIBRARIES}")
    else( )
        message(FATAL_ERROR "Could not find CppUTest")
    endif( )

    mark_as_advanced(CPPUTEST_INCLUDE_DIRS CPPUTEST_LIBRARIES)
endif( )