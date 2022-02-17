//
// Created by matteo on 6/7/20.
// Edited by aart in 2022
//

#include "../Random.h"
#include <pybind11/pybind11.h>

using namespace NEAT;

void export_RNG(pybind11::module_& mod) {
    pybind11::class_<RNG>(mod, "RNG")
        .def(pybind11::init<>())
        .def("Seed", &RNG::Seed)
        .def("TimeSeed", &RNG::TimeSeed)
        .def("RandPosNeg", &RNG::RandPosNeg)
        .def("RandInt", &RNG::RandInt)
        .def("RandFloat", &RNG::RandFloat)
        .def("RandFloatSigned", &RNG::RandFloatSigned)
        .def("RandGaussSigned", &RNG::RandGaussSigned)
        .def("Roulette", &RNG::Roulette);
}
