//
// Created by matteo on 6/7/20.
// Edited by aart in 2022
//

#include "../NeuralNetwork.h"
#include <pybind11/pybind11.h>

void export_Connection(pybind11::module_& mod) {
    pybind11::class_<NEAT::Connection>(mod, "Connection")
        .def(pybind11::init<>())
        .def_readwrite("source_neuron_idx", &NEAT::Connection::m_source_neuron_idx)
        .def_readwrite("target_neuron_idx", &NEAT::Connection::m_target_neuron_idx)
        .def_readwrite("weight", &NEAT::Connection::m_weight)
        .def_readwrite("recur_flag", &NEAT::Connection::m_recur_flag)
        .def_readwrite("hebb_rate", &NEAT::Connection::m_hebb_rate)
        .def_readwrite("hebb_pre_rate", &NEAT::Connection::m_hebb_pre_rate)
        ;
}
