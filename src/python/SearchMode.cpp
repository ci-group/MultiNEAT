//
// Created by matteo on 6/7/20.
// Edited by aart in 2022
//

#include "../Utils.h"
#include <pybind11/pybind11.h>

void export_SearchMode(pybind11::module_& mod) {
    pybind11::enum_<SearchMode>(mod, "SearchMode")
        .value("COMPLEXIFYING", COMPLEXIFYING)
        .value("SIMPLIFYING", SIMPLIFYING)
        .value("BLENDED", BLENDED)
        .export_values();
}
