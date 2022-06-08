# C++ test
add_executable(serialize_genome
        serialize_genome.cpp)

target_link_libraries(serialize_genome
        MultiNEAT
        Boost::unit_test_framework)

add_test(genome serialize_genome)

# serialize_innovation_database
add_executable(serialize_innovation_database
serialize_innovation_database.cpp)

target_link_libraries(serialize_innovation_database
        MultiNEAT
        Boost::unit_test_framework)

add_test(serialize_innovation_database serialize_innovation_database)

if(GENERATE_PYTHON_BINDINGS)
    # python to C++ test
    add_executable(analize_genome_file
            analize_genome_file.cpp)

    target_link_libraries(analize_genome_file
            MultiNEAT)

    ## C++ to python test
    #add_executable(generate_genome_file
    #        generate_genome_file.cpp)
    #
    #target_link_libraries(generate_genome_file
    #        MultiNEAT)

    add_test(python_to_cpp_to_python ${CMAKE_CURRENT_SOURCE_DIR}/test.py)
    set_tests_properties(python_to_cpp_to_python PROPERTIES
            ENVIRONMENT "CMAKE_CURRENT_BINARY_DIR=${CMAKE_CURRENT_BINARY_DIR}")
endif()
