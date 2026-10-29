# 1. ТЕСТ СУММАТОРА
add_executable(test_adder test_adder_4bit.cpp)
verilate(test_adder SOURCES 
    ${CMAKE_SOURCE_DIR}/src/adder_4bit.sv 
    ${CMAKE_SOURCE_DIR}/src/full_adder.sv 
    TRACE
)
target_link_libraries(test_adder PRIVATE GTest::gtest_main)
add_test(NAME AdderTest COMMAND test_adder)

# 2. ТЕСТ ВЫЧИТАТЕЛЯ
add_executable(test_subtractor test_subtractor_4bit.cpp)
verilate(test_subtractor SOURCES 
    ${CMAKE_SOURCE_DIR}/src/subtractor_4bit.sv 
    ${CMAKE_SOURCE_DIR}/src/adder_4bit.sv 
    ${CMAKE_SOURCE_DIR}/src/full_adder.sv 
    TRACE
)
target_link_libraries(test_subtractor PRIVATE GTest::gtest_main)
add_test(NAME SubtractorTest COMMAND test_subtractor)

# 3. ТЕСТ ПОСЛЕДОВАТЕЛЬНОСТНОЙ ЛОГИКИ
add_executable(test_seq test_seq_arith.cpp)
verilate(test_seq SOURCES 
    ${CMAKE_SOURCE_DIR}/src/calculator_program.sv 
    ${CMAKE_SOURCE_DIR}/src/calculator.sv 
    ${CMAKE_SOURCE_DIR}/src/adder_4bit.sv 
    ${CMAKE_SOURCE_DIR}/src/subtractor_4bit.sv 
    ${CMAKE_SOURCE_DIR}/src/full_adder.sv 
    TRACE
)
target_link_libraries(test_seq PRIVATE GTest::gtest_main)
add_test(NAME SeqTest COMMAND test_seq)