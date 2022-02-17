//
// Created by matteo on 6/7/20.
// Edited by aart in 2022
//

#include "../Population.h"
#include <pybind11/pybind11.h>

using namespace NEAT;

void export_Population(pybind11::module_& mod) {
    pybind11::class_<Population>(mod, "Population")
        .def(pybind11::init<Genome, Parameters, bool, double, int>())
        .def(pybind11::init<char*>())
        .def("Epoch", &Population::Epoch)
        .def("Tick", &Population::Tick, pybind11::return_value_policy::reference)
        .def("InitPhenotypeBehaviorData", &Population::InitPhenotypeBehaviorData)
        .def("NoveltySearchTick", &Population::NoveltySearchTick)
        .def("Save", &Population::Save)
        .def("GetBestFitnessEver", &Population::GetBestFitnessEver)
        .def("GetBestGenome", &Population::GetBestGenome)
        .def("GetSearchMode", &Population::GetSearchMode)
        .def("GetCurrentMPC", &Population::GetCurrentMPC)
        .def("GetBaseMPC", &Population::GetBaseMPC)
        .def("GetStagnation", &Population::GetStagnation)
        .def("GetMPCStagnation", &Population::GetMPCStagnation)
        .def("AccessGenomeByIndex", &Population::AccessGenomeByIndex, pybind11::return_value_policy::reference)
        .def("AccessGenomeByID", &Population::AccessGenomeByID, pybind11::return_value_policy::reference)
        .def("NumGenomes", &Population::NumGenomes)
        .def_readwrite("Species", &Population::m_Species)
        .def_readwrite("Parameters", &Population::m_Parameters)
        .def_readwrite("RNG", &Population::m_RNG)
        .def_readwrite("ID", &Population::m_ID)
        .def(pybind11::pickle(&Population::pickle_getstate, &Population::pickle_setstate))
        ;
}
