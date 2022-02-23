//
// Created by matteo on 6/7/20.
// Edited by aart in 2022
//

#include "../NeuralNetwork.h"
#include <pybind11/pybind11.h>

using namespace NEAT;

void (NeuralNetwork::*NN_Save)(const char*) = &NeuralNetwork::Save;
bool (NeuralNetwork::*NN_Load)(const char*) = &NeuralNetwork::Load;
void (NeuralNetwork::*NN_Input)(const pybind11::list&) = &NeuralNetwork::Input_python_list;
void (NeuralNetwork::*NN_Input_numpy)(const pybind11::array_t<double, pybind11::array::c_style | pybind11::array::forcecast>&) = &NeuralNetwork::Input_numpy;

void export_NeuralNetwork(pybind11::module_& mod) {
    pybind11::class_<NeuralNetwork>(mod, "NeuralNetwork")
        .def(pybind11::init<>())
        .def(pybind11::init<bool, RNG&>())

        .def("InitRTRLMatrix",
            &NeuralNetwork::InitRTRLMatrix)
        .def("RTRL_update_gradients",
            &NeuralNetwork::RTRL_update_gradients)
        .def("RTRL_update_error",
            &NeuralNetwork::RTRL_update_error)
        .def("RTRL_update_weights",
            &NeuralNetwork::RTRL_update_weights)

        .def("ActivateFast",
            &NeuralNetwork::ActivateFast)
        .def("Activate",
            &NeuralNetwork::Activate)
        .def("ActivateUseInternalBias",
            &NeuralNetwork::ActivateUseInternalBias)
        .def("ActivateLeaky",
            &NeuralNetwork::ActivateLeaky)

        .def("Adapt",
            &NeuralNetwork::Adapt)

        .def("Flush",
            &NeuralNetwork::Flush)
        .def("FlushCude",
            &NeuralNetwork::InitRTRLMatrix)

        .def("NumInputs",
            &NeuralNetwork::NumInputs)
        .def("NumOutputs",
            &NeuralNetwork::NumOutputs)

        .def("Clear",
            &NeuralNetwork::Clear)
        .def("Save",
            NN_Save)
        .def("Load",
            NN_Load)

        .def("Input",
            NN_Input)
        .def("Input",
            NN_Input_numpy)
        .def("Output",
            &NeuralNetwork::Output)

        .def("AddNeuron",
            &NeuralNetwork::AddNeuron)
        .def("AddConnection",
            &NeuralNetwork::AddConnection)
        .def("SetInputOutputDimentions",
            &NeuralNetwork::SetInputOutputDimentions)

        .def("GetTotalConnectionLength", &NeuralNetwork::GetTotalConnectionLength)


        .def_readwrite("neurons", &NeuralNetwork::m_neurons)
        .def_readwrite("connections", &NeuralNetwork::m_connections)
        ;
}
