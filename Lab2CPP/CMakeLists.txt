cmake_minimum_required(VERSION 3.12)
project(Lab2CPP CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Lab2CPP main.cpp beule.cpp)
target_include_directories(Lab2CPP PUBLIC ../LibraryCPP)
target_link_libraries(Lab2CPP LibraryCPP)

enable_testing()

function(add_forth_test TEST_NAME INPUT_FILE EXPECTED_REGEX)
    add_test(
        NAME ${TEST_NAME}
        COMMAND Lab2CPP "${INPUT_FILE}"
    )
    set_tests_properties(${TEST_NAME} PROPERTIES
        PASS_REGULAR_EXPRESSION "${EXPECTED_REGEX}"
    )
endfunction()


add_forth_test(Test1_Rot "${CMAKE_CURRENT_SOURCE_DIR}/Tests/test1_rot.in" "1[ \r\n]+3[ \r\n]+2")
add_forth_test(Test2_DupAdd "${CMAKE_CURRENT_SOURCE_DIR}/Tests/test2_dup_add.in" "1[ \r\n]+2[ \r\n]+3[ \r\n]+6")
add_forth_test(Test3_SwapOver "${CMAKE_CURRENT_SOURCE_DIR}/Tests/test3_swap_over.in" "10[ \r\n]+20[ \r\n]+5[ \r\n]+7[ \r\n]+5")
add_forth_test(Test4_Math "${CMAKE_CURRENT_SOURCE_DIR}/Tests/test4_math.in" "2[ \r\n]+4[ \r\n]+10")
add_forth_test(Test5_Complex "${CMAKE_CURRENT_SOURCE_DIR}/Tests/test5_complex.in" "41")