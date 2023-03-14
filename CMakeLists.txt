cmake_minimum_required(VERSION 3.22)
project(aquarium-seagrass VERSION 3.0.0
        LANGUAGES C
        DESCRIPTION "Safe C")

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
# Dependencies
set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)
find_package(Doxygen OPTIONAL_COMPONENTS dot mscgen dia)
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    include(cmake/FetchAquariumCMocka.cmake)
endif()
include(cmake/FetchAquariumSeaUrchin.cmake)

# Sources
set(EXPORTED_HEADER_FILES
        include/seagrass/float.h
        include/seagrass/uintmax_t.h
        include/seagrass.h)
set(SOURCES
        ${EXPORTED_HEADER_FILES}
        src/float.c
        src/seagrass.c
        src/uintmax_t.c)

if(DOXYGEN_FOUND)
    set(DOXYGEN_EXTRACT_ALL YES)
    doxygen_add_docs(${PROJECT_NAME}-documentation ${EXPORTED_HEADER_FILES})
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_library(${PROJECT_NAME} STATIC "")
    add_compile_definitions(TEST)
    target_sources(${PROJECT_NAME}
            PRIVATE
                ${SOURCES})
    target_link_libraries(${PROJECT_NAME}
            PUBLIC
                m
                ${CMAKE_THREAD_LIBS_INIT}
                aquarium-cmocka
                aquarium-sea-urchin)
    target_include_directories(${PROJECT_NAME}
            PUBLIC
                "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
                "$<INSTALL_INTERFACE:$<INSTALL_PREFIX>/${CMAKE_INSTALL_INCLUDEDIR}>")
    # Unit Tests
    enable_testing()
    # aquarium-seagrass-unit-test
    add_executable(${PROJECT_NAME}-unit-test test/test_seagrass.c)
    target_include_directories(${PROJECT_NAME}-unit-test
            PRIVATE
                "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>")
    target_link_libraries(${PROJECT_NAME}-unit-test
            PRIVATE
                ${PROJECT_NAME})
    add_test(${PROJECT_NAME}-unit-test ${PROJECT_NAME}-unit-test)
    # aquarium-seagrass-float-unit-test
    add_executable(${PROJECT_NAME}-float-unit-test test/test_float.c)
    target_include_directories(${PROJECT_NAME}-float-unit-test
            PRIVATE
                "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>")
    target_link_libraries(${PROJECT_NAME}-float-unit-test
            PRIVATE
                ${PROJECT_NAME})
    add_test(${PROJECT_NAME}-float-unit-test ${PROJECT_NAME}-float-unit-test)
    # aquarium-seagrass-uintmax_t-unit-test
    add_executable(${PROJECT_NAME}-uintmax_t-unit-test test/test_uintmax_t.c)
    target_include_directories(${PROJECT_NAME}-uintmax_t-unit-test
            PRIVATE
                "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>")
    target_link_libraries(${PROJECT_NAME}-uintmax_t-unit-test
            PRIVATE
                ${PROJECT_NAME})
    add_test(${PROJECT_NAME}-uintmax_t-unit-test
            ${PROJECT_NAME}-uintmax_t-unit-test)
else()
    add_library(${PROJECT_NAME} "")
    target_sources(${PROJECT_NAME}
            PRIVATE
                ${SOURCES})
    target_include_directories(${PROJECT_NAME}
            PUBLIC
                "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
                "$<INSTALL_INTERFACE:$<INSTALL_PREFIX>/${CMAKE_INSTALL_INCLUDEDIR}>")
    target_link_libraries(${PROJECT_NAME}
            PUBLIC
                m
                ${CMAKE_THREAD_LIBS_INIT}
                aquarium-sea-urchin)
    set_target_properties(${PROJECT_NAME}
            PROPERTIES
                VERSION ${PROJECT_VERSION}
                SOVERSION ${PROJECT_VERSION_MAJOR})
    include(GNUInstallDirs)
    install(DIRECTORY include/
            DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
    install(TARGETS ${PROJECT_NAME}
            LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
    configure_file(${PROJECT_NAME}.pc.in ${PROJECT_NAME}.pc @ONLY)
    install(FILES ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.pc
            DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig)
endif()
