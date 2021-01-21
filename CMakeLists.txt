cmake_minimum_required(VERSION 3.7.2 FATAL_ERROR)
project(eld_any LANGUAGES CXX)

add_library(any INTERFACE)
target_include_directories(any INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}
        )
add_library(eld::any ALIAS any)

OPTION(ENABLE_TESTING "Enable unit tests" ON)

# testing
if (ENABLE_TESTING)
    find_package(GTest)
    if (NOT TARGET GTest::GTest)
        set(gtest_force_shared_crt TRUE)
        add_subdirectory(googletest)
        add_library(GTest::GTest ALIAS gtest)
    endif()

    add_executable(test main.cpp)
    target_link_libraries(test PRIVATE eld::any GTest::GTest)

    add_test(test test)
endif()