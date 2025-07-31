create_test(test_bigint_arithmetic)

target_link_libraries(test_bigint_arithmetic PRIVATE bigint)

create_test(test_bigint_core)
target_link_libraries(test_bigint_core PRIVATE bigint)


create_test(test_linkedlist)

target_sources(test_linkedlist PRIVATE ${UTILS_SOURCES})
target_include_directories(test_linkedlist PRIVATE ${CMAKE_SOURCE_DIR}/src)