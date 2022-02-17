//
// Created by matteo on 6/7/20.
// Edited by aart in 2022
//

#include "../Innovation.h"
#include <pybind11/pybind11.h>

using namespace NEAT;

void export_InnovationDatabase(pybind11::module_& mod) {
    pybind11::class_<InnovationDatabase>(mod, "InnovationDatabase")
        .def(pybind11::init<>())
        .def(pybind11::init<int, int>())
        .def("Init_i_i", static_cast<void (InnovationDatabase::*)(int,int)>(&InnovationDatabase::Init))
        .def("Init_with_genome", static_cast<void (InnovationDatabase::*)(const Genome&)>(&InnovationDatabase::Init))
        .def("Init_with_file", static_cast<void (InnovationDatabase::*)(std::ifstream&)>(&InnovationDatabase::Init))
        .def("Flush", &InnovationDatabase::Flush)
        .def("GetInnovationByIdx", &InnovationDatabase::GetInnovationByIdx)
        .def("Save", &InnovationDatabase::Save)
        ;
}
