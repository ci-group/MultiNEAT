//
// Created by matteo on 6/7/20.
// Edited by aart in 2022
//

#include "../Substrate.h"
#include <pybind11/pybind11.h>

using namespace NEAT;

// void (Substrate::*SetCustomConnectivity_Py)(pybind11::list) = &Substrate::SetCustomConnectivity;

void export_Substrate(pybind11::module_& mod) {
    pybind11::class_<Substrate>(mod, "Substrate")
        .def(pybind11::init<>())
        .def(pybind11::init<pybind11::list, pybind11::list, pybind11::list>())
        .def("GetMinCPPNInputs", &Substrate::GetMinCPPNInputs)
        .def("GetMinCPPNOutputs", &Substrate::GetMinCPPNOutputs)
        .def("PrintInfo", &Substrate::PrintInfo)
        // .def("SetCustomConnectivity", &Substrate::SetCustomConnectivity_Py) see substrate source for why this is removed
        .def("ClearCustomConnectivity", &Substrate::ClearCustomConnectivity)

        .def_readwrite("m_leaky", &Substrate::m_leaky)
        .def_readwrite("m_with_distance", &Substrate::m_with_distance)
        .def_readwrite("m_custom_conn_obeys_flags", &Substrate::m_custom_conn_obeys_flags)
        .def_readwrite("m_query_weights_only", &Substrate::m_query_weights_only)
        .def_readwrite("m_hidden_nodes_activation", &Substrate::m_hidden_nodes_activation)
        .def_readwrite("m_output_nodes_activation", &Substrate::m_output_nodes_activation)

        .def_readwrite("m_allow_input_hidden_links", &Substrate::m_allow_input_hidden_links)
        .def_readwrite("m_allow_input_output_links", &Substrate::m_allow_input_output_links)
        .def_readwrite("m_allow_hidden_hidden_links", &Substrate::m_allow_hidden_hidden_links)
        .def_readwrite("m_allow_hidden_output_links", &Substrate::m_allow_hidden_output_links)
        .def_readwrite("m_allow_output_hidden_links", &Substrate::m_allow_output_hidden_links)
        .def_readwrite("m_allow_output_output_links", &Substrate::m_allow_output_output_links)
        .def_readwrite("m_allow_looped_hidden_links", &Substrate::m_allow_looped_hidden_links)
        .def_readwrite("m_allow_looped_output_links", &Substrate::m_allow_looped_output_links)

        .def_readwrite("m_max_weight_and_bias", &Substrate::m_max_weight_and_bias)
        .def_readwrite("m_min_time_const", &Substrate::m_min_time_const)
        .def_readwrite("m_max_time_const", &Substrate::m_max_time_const)

        .def_readwrite("m_input_coords", &Substrate::m_input_coords )
        .def_readwrite("m_hidden_coords", &Substrate::m_hidden_coords)
        .def_readwrite("m_output_coords", &Substrate::m_output_coords)

        .def(pybind11::pickle(&Substrate::pickle_getstate, &Substrate::pickle_setstate))
        ;
}
