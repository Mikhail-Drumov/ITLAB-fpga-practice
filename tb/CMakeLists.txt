set(TARGET testbench)

file(GLOB_RECURSE TARGET_SRC "*.c*")
file(GLOB_RECURSE SV_SOURCES "${CMAKE_SOURCE_DIR}/src/*.sv")

add_executable(${TARGET} ${TARGET_SRC})

verilate(${TARGET}
	SOURCES ${SV_SOURCES}
	TRACE
)

target_link_libraries(${TARGET} PRIVATE GTest::gtest_main)

set_target_properties(${TARGET} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"}

include(GoogleTest)
gtest_discover_tests(${TARGET})