cmake_minimum_required(VERSION 3.22)
project(aquarium-seagrass VERSION 1.0
        LANGUAGES C
        DESCRIPTION "Shared code in aquarium libraries")

set(CMAKE_C_STANDARD 11)
# Dependencies
set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)
find_package(Doxygen OPTIONAL_COMPONENTS dot mscgen dia)

# Sources
set(EXPORTED_HEADER_FILES
        include/seagrass/error.h
        include/seagrass/float.h
        include/seagrass/size_t.h
        include/seagrass.h)
set(SOURCES
        ${EXPORTED_HEADER_FILES}
        src/error.c
        src/float.c
        src/seagrass.c
        src/size_t.c)

if(DOXYGEN_FOUND)
    set(DOXYGEN_EXTRACT_ALL YES)
    doxygen_add_docs(doc ${EXPORTED_HEADER_FILES})
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    include(cmake/FetchCMocka.cmake)
    add_library(${PROJECT_NAME} STATIC "")
    add_compile_definitions(TEST)
    target_sources(${PROJECT_NAME}
            PRIVATE
                ${SOURCES}
                src/test/cmocka.h
                src/test/wrap.c
                src/test/wrap.h)
    target_link_libraries(${PROJECT_NAME}
            PUBLIC
                m
                ${CMAKE_THREAD_LIBS_INIT}
                ${CMOCKA_SHARED_LIBRARY})
    target_include_directories(${PROJECT_NAME}
            PUBLIC
                "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
                "$<INSTALL_INTERFACE:$<INSTALL_PREFIX>/${CMAKE_INSTALL_INCLUDEDIR}>")
    set(LINK_FLAGS "-Wl,--wrap=abort")
    # Unit Tests
    enable_testing()
    # seagrass-unit-test
    add_executable(seagrass-unit-test test/test_seagrass.c)
    target_include_directories(seagrass-unit-test
            PRIVATE
                "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>")
    target_link_libraries(seagrass-unit-test
            PRIVATE
                ${PROJECT_NAME})
    set_target_properties(seagrass-unit-test
            PROPERTIES
                LINK_FLAGS ${LINK_FLAGS})
    add_test(seagrass-unit-test seagrass-unit-test)
    # float-unit-test
    add_executable(float-unit-test test/test_float.c)
    target_include_directories(float-unit-test
            PRIVATE
                "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>")
    target_link_libraries(float-unit-test
            PRIVATE
                ${PROJECT_NAME})
    set_target_properties(float-unit-test
            PROPERTIES
                LINK_FLAGS ${LINK_FLAGS})
    add_test(float-unit-test float-unit-test)
    # size_t-unit-test
    add_executable(size_t-unit-test test/test_size_t.c)
    target_include_directories(size_t-unit-test
            PRIVATE
                "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>")
    target_link_libraries(size_t-unit-test
            PRIVATE
                ${PROJECT_NAME})
    set_target_properties(size_t-unit-test
            PROPERTIES
                LINK_FLAGS ${LINK_FLAGS})
    add_test(size_t-unit-test size_t-unit-test)
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
                ${CMAKE_THREAD_LIBS_INIT})
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
