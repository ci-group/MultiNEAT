//
// Created by matteo on 6/7/20.
// Edited by aart in 2022
//

#include "../Species.h"
#include <pybind11/pybind11.h>

using namespace NEAT;

void export_Species(pybind11::module_& mod) {
    pybind11::class_<Species>(mod, "Species")
        .def(pybind11::init<Genome, int>())
        .def("GetLeader", &Species::GetLeader)
        .def("NumIndividuals", &Species::NumIndividuals)
        .def("GensNoImprovement", &Species::GensNoImprovement)
        .def("ID", &Species::ID)
        .def("AgeGens", &Species::AgeGens)
        .def("IsBestSpecies", &Species::IsBestSpecies)
        .def_readwrite("Individuals", &Species::m_Individuals)
        .def_readonly("Red", &Species::m_R)
        .def_readonly("Green", &Species::m_G)
        .def_readonly("Blue", &Species::m_B)
        .def_readwrite("EvalsNoImprovement", &Species::m_EvalsNoImprovement)
        .def_readwrite("BestFitness", &Species::m_BestFitness)
        ;
}
