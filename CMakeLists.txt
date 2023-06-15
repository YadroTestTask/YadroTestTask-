# ==================
#   Заголовок
# ==================

cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

project(tape_sorter LANGUAGES C CXX)

set(CMAKE_C_STANDARD   99)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_BUILD_TYPE Debug)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# ==================
#   Опции
# ==================

option(TAPE_SORTER_TESTS "Build tests for ${PROJECT_NAME}." OFF)

# ==================
#   Зависмости
# ==================

# ==================
#   Исходники
# ==================

set(TEST_SORTER_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(TEST_SORTER_SOURCE_DIR  ${CMAKE_CURRENT_SOURCE_DIR}/source)

set(TEST_SORTER_SOURCES
    ${TEST_SORTER_SOURCE_DIR}/tape_config.cpp
    ${TEST_SORTER_SOURCE_DIR}/tape_sorter.cpp
    ${TEST_SORTER_SOURCE_DIR}/tape.cpp
)

# ==================
#   Бинарники
# ==================

# Библиотека

set(TEST_SORTER_LIBRARY ${PROJECT_NAME})
add_library(${TEST_SORTER_LIBRARY} STATIC ${TEST_SORTER_SOURCES})
set_target_properties(${TEST_SORTER_LIBRARY} PROPERTIES POSITION_INDEPENDENT_CODE ON)
target_include_directories(${TEST_SORTER_LIBRARY} PUBLIC ${TEST_SORTER_INCLUDE_DIR})

# Консольный интерфейс

set(TEST_SORTER_SERVICE ${PROJECT_NAME}_service)
add_executable(${TEST_SORTER_SERVICE} ${TEST_SORTER_SOURCE_DIR}/service/cli.cpp)
target_link_libraries(${TEST_SORTER_SERVICE} PUBLIC ${TEST_SORTER_LIBRARY})

# ==================
#   Тесты
# ==================

if (TAPE_SORTER_TESTS)
    set(TEST_TARGET ${PROJECT_NAME}_test)

    find_package(CppUTest REQUIRED)

    set(TEST_SORTER_TEST_SOURCES
        ${TEST_SORTER_SOURCE_DIR}/test/main.cpp
        ${TEST_SORTER_SOURCE_DIR}/test/tape_config.cpp
        ${TEST_SORTER_SOURCE_DIR}/test/tape_sorter.cpp
        ${TEST_SORTER_SOURCE_DIR}/test/tape.cpp
    )

    add_executable(${TEST_TARGET} ${TEST_SORTER_TEST_SOURCES})

    target_include_directories(${TEST_TARGET} PUBLIC
        ${TEST_SORTER_INCLUDE_DIR}
        ${CPPUTEST_INCLUDE_DIRS}
    )

    target_link_libraries(${TEST_TARGET}
        ${CPPUTEST_LIBRARIES}
        ${TEST_SORTER_LIBRARY} 
    )
endif( )
