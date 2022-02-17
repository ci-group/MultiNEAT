//
// Created by matteo on 6/7/20.
// Edited by aart in 2022
//

#include "../Genes.h"
#include <pybind11/pybind11.h>

void export_NeuronType(pybind11::module_& mod) {
    pybind11::enum_<NEAT::NeuronType>(mod, "NeuronType")
        .value("NONE", NEAT::NeuronType::NONE)
        .value("INPUT", NEAT::NeuronType::INPUT)
        .value("BIAS", NEAT::NeuronType::BIAS)
        .value("HIDDEN", NEAT::NeuronType::HIDDEN)
        .value("OUTPUT", NEAT::NeuronType::OUTPUT)
        .export_values();
}
