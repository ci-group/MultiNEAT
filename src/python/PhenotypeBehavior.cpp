//
// Created by matteo on 6/7/20.
// Edited by aart in 2022
//

#include "../Genome.h"
#include "../PhenotypeBehavior.h"
#include <pybind11/pybind11.h>

using namespace NEAT;

void export_PhenotypeBehaviour(pybind11::module_& mod) {
    pybind11::class_<PhenotypeBehavior>(mod, "PhenotypeBehavior")
        .def(pybind11::init<>())
        .def("Acquire", &PhenotypeBehavior::Acquire)
        .def("Distance_To", &PhenotypeBehavior::Distance_To)
        .def("Successful", &PhenotypeBehavior::Successful)

        .def_readwrite("m_Data", &PhenotypeBehavior::m_Data)
        ;
}
