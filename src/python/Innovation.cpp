//
// Created by matteo on 6/7/20.
// Edited by aart in 2022
//

#include "../Innovation.h"
#include <pybind11/pybind11.h>

using namespace NEAT;

void export_Innovation(pybind11::module_& mod) {
    pybind11::class_<Innovation>(mod, "Innovation")
        .def(pybind11::init<int, InnovationType, int, int, NeuronType, int>())
            .def("ID", &Innovation::ID)
            .def("InnovType", &Innovation::InnovType)
            .def("FromNeuronID", &Innovation::FromNeuronID)
            .def("ToNeuronID", &Innovation::ToNeuronID)
            .def("NeuronID", &Innovation::NeuronID)
            .def("GetNeuronType", &Innovation::GetNeuronType)
            ;
}
