create_test(test_bigint_arithmetic)

target_sources(test_bigint_arithmetic PRIVATE ${CMAKE_SOURCE_DIR}/ARITHMETIC_SOURCES
        ${CMAKE_SOURCE_DIR}/CORE_SOURCES)

create_test(test_bigint_core)
target_sources(test_bigint_core PRIVATE ${CMAKE_SOURCE_DIR}/CORE_SOURCES)


create_test(test_linkedlist)

target_link_libraries(test_linked_list PRIVATE bigint)