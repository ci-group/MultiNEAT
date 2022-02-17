//
// Created by matteo on 6/7/20.
// Edited by aart in 2022
//

#include "../Genes.h"
#include <pybind11/pybind11.h>

using namespace NEAT;

void export_NeuronGene(pybind11::module_& mod) {
    pybind11::class_<NeuronGene>(mod, "NeuronGene")
        .def(pybind11::init<>())
        .def_readwrite("ID", &NeuronGene::m_ID)
        .def_readwrite("A", &NeuronGene::m_A)
        .def_readwrite("B", &NeuronGene::m_B)
        .def_readwrite("TimeConstant", &NeuronGene::m_TimeConstant)
        .def_readwrite("Bias", &NeuronGene::m_Bias)
        .def_readwrite("ActFunction", &NeuronGene::m_ActFunction)
        .def_readwrite("Type", &NeuronGene::m_Type)
        .def_readwrite("x", &NeuronGene::x)
        .def_readwrite("y", &NeuronGene::y)
        .def_readwrite("SplitY", &NeuronGene::m_SplitY)
        ;
}
