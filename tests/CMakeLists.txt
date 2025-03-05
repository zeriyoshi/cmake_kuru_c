include(FetchContent)
FetchContent_Declare(
    unity
    GIT_REPOSITORY https://github.com/ThrowTheSwitch/Unity.git
    GIT_TAG v2.6.0
)
FetchContent_MakeAvailable(unity)

find_program(VALGRIND "valgrind")
if(VALGRIND)
    message(STATUS "Found Valgrind: ${VALGRIND}")
endif()

set(MEMORYCHECK_COMMAND_OPTIONS
    "--tool=memcheck --leak-check=full --show-leak-kinds=all --track-origins=yes --error-exitcode=1"
)

file(GLOB TEST_SOURCES "test_*.c")
foreach(TEST_SOURCE ${TEST_SOURCES})
    get_filename_component(TEST_NAME ${TEST_SOURCE} NAME_WE)
    add_executable(${TEST_NAME} ${TEST_SOURCE})
    target_link_libraries(${TEST_NAME}
        PRIVATE
            ${CMAKE_PROJECT_NAME}
            unity
    )
    target_include_directories(${TEST_NAME}
        PRIVATE
            ${unity_SOURCE_DIR}/src
            ${CMAKE_SOURCE_DIR}/include
    )

    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})

    if(VALGRIND)
        add_test(
            NAME memcheck_${TEST_NAME}
            COMMAND ${VALGRIND} ${MEMORYCHECK_COMMAND_OPTIONS} $<TARGET_FILE:${TEST_NAME}>
        )
    endif()
endforeach()
