# This file and other cmake files in this project where inspired by https://github.com/pabloariasal/modern-cmake-sample
# Based on the article: https://pabloariasal.github.io/2018/02/19/its-time-to-do-cmake-right/

cmake_minimum_required(VERSION 3.3)
project(MultiNEAT VERSION 0.7 LANGUAGES C CXX)

set (CMAKE_CXX_STANDARD 11)

set (MultiNEAT_SRC_DIR ${CMAKE_SOURCE_DIR}/src)

if(MSVC)
    # Force to always compile with W4
    if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
        string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    else()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
    endif()
elseif(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long -pedantic")
endif()

include(GNUInstallDirs)

find_package(Threads REQUIRED)

find_package(Boost
        COMPONENTS
        date_time
        system
        filesystem
        serialization
        REQUIRED
        )

set(SOURCE_FILES
        src/Genome.cpp
        src/Innovation.cpp
        src/NeuralNetwork.cpp
        src/Parameters.cpp
        src/Population.cpp
        src/Random.cpp
        src/Species.cpp
        src/Substrate.cpp
        src/Utils.cpp
        src/Traits.cpp
        )


set(Boost_USE_STATIC_LIBS       OFF) # only find static libs
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    OFF)

if (NOT SKBUILD)

    add_library(MultiNEAT SHARED ${SOURCE_FILES})

    target_include_directories(MultiNEAT
            PRIVATE
            ${Boost_INCLUDE_DIRS}
            PUBLIC
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
            $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/multineat>
            )

    target_link_libraries(MultiNEAT
            PUBLIC
            Boost::date_time
            Boost::system
            Boost::filesystem
            Boost::serialization
            Threads::Threads
            )

    target_compile_definitions(MultiNEAT
            PUBLIC
            USE_BOOST_RANDOM
            )

    # INSTALL SECTION
    set(INSTALL_CONFIGDIR ${CMAKE_INSTALL_LIBDIR}/cmake/MultiNEAT)

    install(TARGETS MultiNEAT
            EXPORT MultiNEAT-targets
            LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    )

    install(DIRECTORY ${CMAKE_SOURCE_DIR}/src/
            DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/multineat
            FILES_MATCHING PATTERN "*.h")

    set_target_properties(MultiNEAT PROPERTIES EXPORT_NAME MultiNEAT)

    install(EXPORT MultiNEAT-targets
            FILE MultiNEATTargets.cmake
            NAMESPACE MultiNEAT::
            DESTINATION ${INSTALL_CONFIGDIR})

    include(CMakePackageConfigHelpers)
    write_basic_package_version_file(
            ${CMAKE_CURRENT_BINARY_DIR}/MultiNEATConfigVersion.cmake
            VERSION ${PROJECT_VERSION}
            COMPATIBILITY AnyNewerVersion
    )

    configure_package_config_file(
            ${CMAKE_CURRENT_LIST_DIR}/cmake/MultiNEATConfig.cmake.in
            ${CMAKE_CURRENT_BINARY_DIR}/MultiNEATConfig.cmake
            INSTALL_DESTINATION ${INSTALL_CONFIGDIR}
        )

    #Install the config, configversion and custom find modules
    install(FILES
            ${CMAKE_CURRENT_BINARY_DIR}/MultiNEATConfig.cmake
            ${CMAKE_CURRENT_BINARY_DIR}/MultiNEATConfigVersion.cmake
            DESTINATION ${INSTALL_CONFIGDIR}
            )

    ##############################################
    ## Exporting from the build tree
    export(EXPORT MultiNEAT-targets FILE ${CMAKE_CURRENT_BINARY_DIR}/MultiNEATTargets.cmake NAMESPACE MultiNEAT::)

    #Register package in user's package registry
    export(PACKAGE MultiNEAT)

endif(NOT SKBUILD)

if(GENERATE_PYTHON_BINDINGS)

    if (${CMAKE_VERSION} VERSION_LESS "3.12.0")
        set(CMAKE_LEGACY_PYTHON ON)
    endif()

    if (DEFINED PYTHON_VERSION_STRING)
        set(PYTHON_VERSION "${PYTHON_VERSION_STRING}" "EXACT")
    endif()

    if (CMAKE_LEGACY_PYTHON)
        find_package(PythonLibs ${PYTHON_VERSION} REQUIRED)
        message("[legacy] found python ${PYTHONLIBS_VERSION_STRING} [pythonlibs]")
        string(REGEX REPLACE "([0-9]+)\\.([0-9]+)\\.([0-9]+)"
                "\\1" 3
                ${PYTHONLIBS_VERSION_STRING})
        string(REGEX REPLACE "([0-9]+)\\.([0-9]+)\\.([0-9]+)"
                "\\1\\2" 3x
                ${PYTHONLIBS_VERSION_STRING})
        string(REGEX REPLACE "([0-9]+)\\.([0-9]+)\\.([0-9]+)"
                "-py\\1\\2" PY3x
                ${PYTHONLIBS_VERSION_STRING})
    else()
        find_package(Python3 ${PYTHON_VERSION}
            COMPONENTS
                Development
            REQUIRED
        )
        message("found python ${Python3_VERSION_MAJOR}.${Python3_VERSION_MINOR}.${Python3_VERSION_PATCH}")

        set(3 ${Python3_VERSION_MAJOR})
        set(3x "${Python3_VERSION_MAJOR}${Python3_VERSION_MINOR}")
        set(PY3x "-py${Python3_VERSION_MAJOR}${Python3_VERSION_MINOR}") # ubuntu version

    endif()

    if (SKBUILD)
        find_package(PythonExtensions REQUIRED)
        set(Boost_INTERNAL TRUE)
    endif()

    if (NOT ${Boost_INTERNAL})
        find_package(Boost COMPONENTS
                python${3x}
                python${PY3x}
                numpy${3x}
                numpy${PY3x}
                QUIET
                )

        if(Boost_python${3x}_FOUND OR Boost_PYTHON${3x}_FOUND)
            message("Boost python${3x} found")
        elseif(Boost_python${PY3x}_FOUND OR Boost_PYTHON${PY3x}_FOUND)
            message("Boost python${PY3x} found")
        else()
            set(Boost_INTERNAL TRUE)
            message(WARNING "Boost python${3x} not found")
        endif()

        if(Boost_numpy${3x}_FOUND OR Boost_NUMPY${3x}_FOUND)
            message("Boost python-numpy${3x} found")
        elseif(Boost_numpy${PY3x}_FOUND OR Boost_NUMPY${PY3x}_FOUND)
            message("Boost python-numpy${PY3x} found")
        else()
            set(Boost_INTERNAL TRUE)
            message(WARNING "Boost python numpy ${3x} not found")
        endif()
    endif()

    if (${Boost_INTERNAL})
        message("Attempting to compile boost as a static library")
        set(Boost_PYTHON${3}_FOUND False)
        set(Boost_PYTHON${3x}_FOUND False)
        set(Boost_PYTHON${PY3x}_FOUND False)
        set(Boost_NUMPY${3}_FOUND False)
        set(Boost_NUMPY${3x}_FOUND False)
        set(Boost_NUMPY${PY3x}_FOUND False)
        set(Boost_python${3}_FOUND False)
        set(Boost_python${3x}_FOUND False)
        set(Boost_python${PY3x}_FOUND False)
        set(Boost_numpy${3}_FOUND False)
        set(Boost_numpy${3x}_FOUND False)
        set(Boost_numpy${PY3x}_FOUND False)

        # Add tasks subprojects
        if (SKBUILD)
            string(REGEX REPLACE "/lib/" "/lib64/"
                PYTHON_SITE_PACKAGES_DIR_FIXED "${PYTHON_SITE_PACKAGES_DIR}")
            find_file(NUMPY "numpyconfig.h"
                PATHS "${PYTHON_SITE_PACKAGES_DIR_FIXED}" "${PYTHON_SITE_PACKAGES_DIR}"
                PATH_SUFFIXES "/numpy/core/include/numpy/")
            if (${NUMPY} STREQUAL "NUMPY-NOTFOUND")
                message(FATAL_ERROR "Numpy not found, searched in \"${PYTHON_SITE_PACKAGES_DIR_FIXED}\" and \"${PYTHON_SITE_PACKAGES_DIR}\"")
            else()
                message("Numpy found: ${NUMPY}")
            endif()
            get_filename_component(NUMPY_INCLUDE_DIR "${NUMPY}" DIRECTORY)

            set(Python_NumPy_INCLUDE_DIR "${NUMPY_INCLUDE_DIR}/../")
        endif()
        add_subdirectory(${CMAKE_SOURCE_DIR}/thirdparty)
    endif()


    set(PYTHON_SOURCE_FILES src/python/PythonBindings.cpp
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
            src/python/Lists.cpp
    )

    if(CMAKE_LEGACY_PYTHON)
        python_add_module(_multineat
                ${SOURCE_FILES}
                ${PYTHON_SOURCE_FILES}
                )
    else()
        Python3_add_library(_multineat
                MODULE
                ${SOURCE_FILES}
                ${PYTHON_SOURCE_FILES}
                )
    endif()


    target_compile_definitions(_multineat
            PUBLIC
            USE_BOOST_RANDOM
            USE_BOOST_PYTHON
            )

    target_include_directories(_multineat
            PRIVATE
            $<$<BOOL:${CMAKE_LEGACY_PYTHON}>:${PYTHON_INCLUDE_DIRS}>
            ${Boost_INCLUDE_DIRS}
            )

    set(MULTINEAT_PYTHON_LIBRARIES
            Boost::date_time
            Boost::system
            Boost::filesystem
            Boost::serialization

            # Python3::Python # already included by default
            $<$<BOOL:${Boost_PYTHON${3}_FOUND}>:${Boost_PYTHON${3}_LIBRARY}>
            $<$<BOOL:${Boost_PYTHON${3x}_FOUND}>:${Boost_PYTHON${3x}_LIBRARY}>
            $<$<BOOL:${Boost_PYTHON${PY3x}_FOUND}>:${Boost_PYTHON${PY3x}_LIBRARY}>
            $<$<BOOL:${Boost_NUMPY${3}_FOUND}>:${Boost_NUMPY${3}_LIBRARY}>
            $<$<BOOL:${Boost_NUMPY${3x}_FOUND}>:${Boost_NUMPY${3x}_LIBRARY}>
            $<$<BOOL:${Boost_NUMPY${PY3x}_FOUND}>:${Boost_NUMPY${PY3x}_LIBRARY}>

            #SKBUILD VERSION
            $<$<BOOL:${Boost_python${3}_FOUND}>:${Boost_PYTHON${3}_LIBRARY}>
            $<$<BOOL:${Boost_python${3x}_FOUND}>:${Boost_PYTHON${3x}_LIBRARY}>
            $<$<BOOL:${Boost_python${PY3x}_FOUND}>:${Boost_PYTHON${PY3x}_LIBRARY}>
            $<$<BOOL:${Boost_numpy${3}_FOUND}>:${Boost_NUMPY${3}_LIBRARY}>
            $<$<BOOL:${Boost_numpy${3x}_FOUND}>:${Boost_NUMPY${3x}_LIBRARY}>
            $<$<BOOL:${Boost_numpy${PY3x}_FOUND}>:${Boost_NUMPY${PY3x}_LIBRARY}>

            # Internal Boost python
            $<$<BOOL:${Boost_INTERNAL}>:Boost::python${3x}>
            $<$<BOOL:${Boost_INTERNAL}>:Boost::numpy${3x}>
            )

    target_link_libraries(_multineat PUBLIC
            $<$<BOOL:${CMAKE_LEGACY_PYTHON}>:${PYTHON_LIBRARIES}>
            ${MULTINEAT_PYTHON_LIBRARIES}
            )

    if (SKBUILD)
        set(site_packages "${PYTHON_RELATIVE_SITE_PACKAGES_DIR}")
        install(TARGETS _multineat LIBRARY DESTINATION "${site_packages}/multineat")
    endif ()

endif()

if (ENABLE_TESTING)
    enable_testing()
    add_subdirectory(tests)
endif()
