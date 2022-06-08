# This file and other cmake files in this project where inspired by
# https://github.com/pabloariasal/modern-cmake-sample Based on the article:
# https://pabloariasal.github.io/2018/02/19/its-time-to-do-cmake-right/

cmake_minimum_required(VERSION 3.15)
project(
    MultiNEAT
    VERSION 0.9
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

option(ENABLE_TESTING "If tests should be built.")

# Set compiler warnings
if(MSVC)
    # Force to always compile with W4
    if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
        string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS
                             "${CMAKE_CXX_FLAGS}")
    else()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
    endif()
elseif(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long -pedantic")
endif()

include(GNUInstallDirs)

find_package(cereal)

set(SOURCE_FILES
    src/Genome.cpp
    src/Genes.cpp
    src/Innovation.cpp
    src/NeuralNetwork.cpp
    src/Parameters.cpp
    src/Population.cpp
    src/Random.cpp
    src/Species.cpp
    src/Substrate.cpp
    src/Traits.cpp
    src/Utils.cpp)

if(NOT SKBUILD)

    add_library(MultiNEAT SHARED ${SOURCE_FILES})

    target_include_directories(
        MultiNEAT
        PRIVATE
        PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
               $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/multineat>)

    # INSTALL SECTION
    set(INSTALL_CONFIGDIR ${CMAKE_INSTALL_LIBDIR}/cmake/MultiNEAT)

    install(
        TARGETS MultiNEAT
        EXPORT MultiNEAT-targets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

    install(
        DIRECTORY ${CMAKE_SOURCE_DIR}/src/
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/multineat
        FILES_MATCHING
        PATTERN "*.h")

    set_target_properties(MultiNEAT PROPERTIES EXPORT_NAME MultiNEAT)

    install(
        EXPORT MultiNEAT-targets
        FILE MultiNEATTargets.cmake
        NAMESPACE MultiNEAT::
        DESTINATION ${INSTALL_CONFIGDIR})

    include(CMakePackageConfigHelpers)
    write_basic_package_version_file(
        ${CMAKE_CURRENT_BINARY_DIR}/MultiNEATConfigVersion.cmake
        VERSION ${PROJECT_VERSION}
        COMPATIBILITY AnyNewerVersion)

    configure_package_config_file(
        ${CMAKE_CURRENT_LIST_DIR}/cmake/MultiNEATConfig.cmake.in
        ${CMAKE_CURRENT_BINARY_DIR}/MultiNEATConfig.cmake
        INSTALL_DESTINATION ${INSTALL_CONFIGDIR})

    # Install the config, configversion and custom find modules
    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/MultiNEATConfig.cmake
                  ${CMAKE_CURRENT_BINARY_DIR}/MultiNEATConfigVersion.cmake
            DESTINATION ${INSTALL_CONFIGDIR})

    # ##########################################################################
    # Exporting from the build tree
    export(
        EXPORT MultiNEAT-targets
        FILE ${CMAKE_CURRENT_BINARY_DIR}/MultiNEATTargets.cmake
        NAMESPACE MultiNEAT::)

    # Register package in user's package registry
    export(PACKAGE MultiNEAT)

else()

    # Based on See https://github.com/pybind/scikit_build_example/blob/master/CMakeLists.txt

    # Invoke python to ask pybind11 where it is installed.
    # In this way we can use the pybind11 installation from pip.
    message("Finding pybind11 CMake dir using python..")
    execute_process(
        COMMAND "${PYTHON_EXECUTABLE}" -c
                "import pybind11; print(pybind11.get_cmake_dir())"
        OUTPUT_VARIABLE PYBIND11_CMAKE_DIR
        OUTPUT_STRIP_TRAILING_WHITESPACE COMMAND_ECHO STDOUT)
    list(APPEND CMAKE_PREFIX_PATH "${PYBIND11_CMAKE_DIR}")

    find_package(pybind11 CONFIG REQUIRED)

    set(PYTHON_SOURCE_FILES
        src/python/PythonBindings.cpp
        src/python/NeuronType.cpp
        src/python/ActivationFunction.cpp
        src/python/SearchMode.cpp
        src/python/RNG.cpp
        src/python/Connection.cpp
        src/python/Neuron.cpp
        src/python/NeuralNetwork.cpp
        src/python/LinkGene.cpp
        src/python/NeuronGene.cpp
        src/python/Genome.cpp
        src/python/Species.cpp
        src/python/Substrate.cpp
        src/python/PhenotypeBehavior.cpp
        src/python/Population.cpp
        src/python/Innovation.cpp
        src/python/InnovationDatabase.cpp
        src/python/Parameters.cpp
        src/python/Lists.cpp)

    pybind11_add_module(_multineat MODULE ${SOURCE_FILES} ${PYTHON_SOURCE_FILES})

    target_compile_definitions(_multineat PUBLIC PYTHON_BINDINGS)

    install(TARGETS _multineat DESTINATION .)

endif()

if(ENABLE_TESTING)
    enable_testing()
    add_subdirectory(tests)
endif()
