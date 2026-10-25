execute_process(
    COMMAND "${TEST_EXECUTABLE}"
    RESULT_VARIABLE test_result
    OUTPUT_VARIABLE test_output
    ERROR_VARIABLE test_errors
)
if(NOT test_result EQUAL 0)
    message(FATAL_ERROR "Tests failed: ${test_errors}")
endif()

foreach(expected_text
    "[WAREHOUSE] add:"
    "[PRODUCT] transfer:"
    "[FACTORY] create Milk:"
    "[WAREHOUSE] find by id:"
    "[WAREHOUSE] find by category:"
    "[WAREHOUSE] find by price:"
    "[WAREHOUSE] copy constructor:"
    "[WAREHOUSE] copy assignment:"
    "[WAREHOUSE] move constructor:"
    "[WAREHOUSE] move assignment:"
)
    string(FIND "${test_output}" "${expected_text}" position)
    if(position EQUAL -1)
        message(FATAL_ERROR "Missing log entry: ${expected_text}")
    endif()
endforeach()
