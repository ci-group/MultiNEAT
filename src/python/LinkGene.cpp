//
// Created by matteo on 6/7/20.
// Edited by aart in 2022
//

#include "../Genes.h"
#include <pybind11/pybind11.h>

using namespace NEAT;

void export_LinkGene(pybind11::module_& mod) {
    pybind11::class_<LinkGene>(mod, "LinkGene")
        .def(pybind11::init<>())
        .def_readwrite("FromNeuronID", &LinkGene::m_FromNeuronID)
        .def_readwrite("ToNeuronID", &LinkGene::m_ToNeuronID)
        .def_readwrite("InnovationID", &LinkGene::m_InnovationID)
        .def_readwrite("Weight", &LinkGene::m_Weight)
        .def_readwrite("IsRecurrent", &LinkGene::m_IsRecurrent)
        ;
}
