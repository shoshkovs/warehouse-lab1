cmake_minimum_required(VERSION 3.16)

project(warehouse_lab LANGUAGES CXX)

option(ENABLE_SANITIZERS "Enable AddressSanitizer and UndefinedBehaviorSanitizer" OFF)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

function(enable_project_warnings target_name)
    if(CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
        target_compile_options(${target_name} PRIVATE -Wall -Wextra -Wpedantic)
    endif()
endfunction()

function(enable_project_sanitizers target_name)
    if(ENABLE_SANITIZERS AND CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
        target_compile_options(${target_name} PRIVATE
            -fsanitize=address,undefined
            -fno-omit-frame-pointer
        )
        target_link_options(${target_name} PRIVATE
            -fsanitize=address,undefined
            -fno-omit-frame-pointer
        )
    endif()
endfunction()

enable_testing()

add_library(warehouse_core
    src/Bread.cpp
    src/Clothing.cpp
    src/ConstWarehouseIterator.cpp
    src/Electronics.cpp
    src/Food.cpp
    src/Jacket.cpp
    src/Laptop.cpp
    src/LoggingProxy.cpp
    src/Milk.cpp
    src/Price.cpp
    src/Product.cpp
    src/ProductFactory.cpp
    src/Quantity.cpp
    src/Smartphone.cpp
    src/TShirt.cpp
    src/Warehouse.cpp
    src/WarehouseIterator.cpp
    src/Weight.cpp
)
target_include_directories(warehouse_core PUBLIC include)
enable_project_warnings(warehouse_core)
enable_project_sanitizers(warehouse_core)

add_executable(warehouse_tests tests/test_main.cpp)
target_include_directories(warehouse_tests PRIVATE include tests)
target_link_libraries(warehouse_tests PRIVATE warehouse_core)
enable_project_warnings(warehouse_tests)
enable_project_sanitizers(warehouse_tests)

add_test(NAME warehouse_tests COMMAND warehouse_tests)

add_executable(warehouse_demo src/main.cpp src/Console.cpp)
target_link_libraries(warehouse_demo PRIVATE warehouse_core)
enable_project_warnings(warehouse_demo)
enable_project_sanitizers(warehouse_demo)

add_test(NAME warehouse_demo_smoke COMMAND warehouse_demo --demo)
set_tests_properties(
    warehouse_demo_smoke
    PROPERTIES PASS_REGULAR_EXPRESSION
               "Scenario 1.*Scenario 2.*Scenario 3.*Scenario 4.*Scenario 5"
)

add_test(
    NAME warehouse_logging
    COMMAND ${CMAKE_COMMAND}
        -DTEST_EXECUTABLE=$<TARGET_FILE:warehouse_tests>
        -P ${CMAKE_CURRENT_SOURCE_DIR}/tests/check_logging.cmake
)

add_test(
    NAME warehouse_console
    COMMAND ${CMAKE_COMMAND}
        -DAPP=$<TARGET_FILE:warehouse_demo>
        -P ${CMAKE_CURRENT_SOURCE_DIR}/tests/check_console.cmake
)
