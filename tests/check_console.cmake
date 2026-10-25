function(check_console name input)
    set(input_file "${CMAKE_CURRENT_BINARY_DIR}/console-${name}.txt")
    file(WRITE "${input_file}" "${input}")
    execute_process(
        COMMAND "${APP}"
        INPUT_FILE "${input_file}"
        RESULT_VARIABLE result
        OUTPUT_VARIABLE output
        ERROR_VARIABLE errors
        TIMEOUT 5
    )
    if(NOT "${result}" STREQUAL "0")
        message(FATAL_ERROR "${name}: console failed: ${result}\n${errors}")
    endif()
    foreach(expected IN LISTS ARGN)
        string(FIND "${output}" "${expected}" position)
        if(position EQUAL -1)
            message(FATAL_ERROR "${name}: missing '${expected}'\n${output}")
        endif()
    endforeach()
    if(NOT "${errors}" STREQUAL "")
        message(FATAL_ERROR "${name}: unexpected diagnostics: ${errors}")
    endif()
    message(STATUS "PASS: ${name}")
endfunction()

check_console(exit "2\n2\n0\n" "Warehouse menu" "Goodbye.")

check_console(lifecycle [=[2
2
2
1
1
Phone A
100
2
0.2
1
5
1
1
150
5
1
2
3
4
1
1
6
1
7
1
3
1
1
1
0
]=] "Added product ID 1." "price=150 | quantity=5" "Transferred product ID 1." "Active warehouse: 2" "Removed product ID 1." "Warehouse is empty.")

check_console(invalid_input [=[letters
0
2
2
bad
99
1junk
2
7
1
2147483647
1
   
Phone with spaces
-1
100
-3
2
nan
inf
-0.2
0.2
1
0
]=] "Enter an integer" "Name cannot be empty." "Enter a finite non-negative weight." "name=Phone with spaces | price=100 | quantity=2")

check_console(capacity [=[1
1
2
6
1
Bread
2
3
0.5
2
1
0
]=] "Error: Warehouse is full" "Bread | id=1 | name=Bread | price=2 | quantity=3")

check_console(duplicate_and_search [=[2
2
2
1
1
Phone
100
2
0.2
2
6
1
Duplicate
2
3
0.5
2
6
2
Bread
2
3
0.5
4
2
1
4
3
2
3
2
99
3
2
0
4
1
1
1
0
]=] "Error: Product ID already exists" "Found 1 product(s)." "Error: Product index is out of range" "Removed product at index 0." "Error: Product ID not found" "Bread | id=2 | name=Bread")

check_console(quantity_limits [=[2
2
2
1
1
Phone
100
2
0.2
5
1
2
-3
5
1
2
2147483647
5
99
1
1
0
]=] "Error: Quantity change is out of range" "Error: Product ID not found" "price=100 | quantity=2")

check_console(full_target [=[2
1
7
2
6
2
Bread
2
3
0.5
7
2
1
1
Phone
100
2
0.2
6
1
1
0
]=] "Error: Target warehouse is full" "Smartphone | id=1 | name=Phone")

check_console(duplicate_target [=[2
2
2
1
1
Phone
100
2
0.2
7
2
6
1
Bread
2
3
0.5
6
1
1
0
]=] "Error: Product ID already exists in target" "Bread | id=1 | name=Bread")

check_console(eof_start "")
check_console(eof_add "2\n2\n2\n1\n1\n" "Goodbye.")

check_console(all_factories [=[6
1
2
1
1
Phone
100
1
0.2
2
2
2
Laptop
200
1
1.5
2
3
3
Shirt
30
1
0.3
2
4
4
Jacket
80
1
0.8
2
5
5
Milk
3
1
1
2
6
6
Bread
2
1
0.5
1
0
]=] "Smartphone | id=1" "Laptop | id=2" "TShirt | id=3" "Jacket | id=4" "Milk | id=5" "Bread | id=6" "Products: 6 / 6")

execute_process(COMMAND "${APP}" --help RESULT_VARIABLE result OUTPUT_VARIABLE output)
if(NOT "${result}" STREQUAL "0" OR NOT output MATCHES "interactive warehouse menu")
    message(FATAL_ERROR "Console help failed")
endif()
message(STATUS "PASS: help")

execute_process(COMMAND "${APP}" --unknown RESULT_VARIABLE result ERROR_VARIABLE output)
if(NOT "${result}" STREQUAL "2" OR NOT output MATCHES "Usage:")
    message(FATAL_ERROR "Invalid command-line argument was not rejected")
endif()
message(STATUS "PASS: invalid argument")

check_console(copy_cancel "2\n1\n8\n0\n7\n1\n0\n" "Copy cancelled." "Products: 0 / 1")
check_console(copy_confirm "2\n1\n7\n2\n6\n2\nOld bread\n2\n1\n0.5\n7\n2\n1\n1\nPhone\n100\n2\n0.2\n8\n1\n7\n5\n1\n1\n150\n1\n7\n1\n0\n" "Warehouse copied." "price=150 | quantity=2" "price=100 | quantity=2" "Products: 1 / 2")
check_console(copy_eof "2\n1\n8\n" "Goodbye.")
