/*
 * PythonBindings.cpp
 *
 *  Created on: Jun 26, 2012
 *      Author: peter
 * 
 *  Edited in 2021 by Aart
 */

///////////////////////////////////////////////////////////////////////////////////////////
//    MultiNEAT - Python/C++ NeuroEvolution of Augmenting Topologies Library
//
//    Copyright (C) 2012 Peter Chervenski
//
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU Lesser General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU Lesser General Public License
//    along with this program.  If not, see < http://www.gnu.org/licenses/ >.
//
//    Contact info:
//
//    Peter Chervenski < spookey@abv.bg >
//    Shane Ryan < shane.mcdonald.ryan@gmail.com >
///////////////////////////////////////////////////////////////////////////////////////////

#include <pybind11/pybind11.h>

void export_NeuronType(pybind11::module_& mod);
void export_ActivationFunction(pybind11::module_& mod);
void export_SearchMode(pybind11::module_& mod);
void export_RNG(pybind11::module_& mod);
void export_Connection(pybind11::module_& mod);
void export_Neuron(pybind11::module_& mod);
void export_NeuralNetwork(pybind11::module_& mod);
void export_LinkGene(pybind11::module_& mod);
void export_NeuronGene(pybind11::module_& mod);
void export_Genome(pybind11::module_& mod);
void export_Species(pybind11::module_& mod);
void export_Substrate(pybind11::module_& mod);
void export_PhenotypeBehaviour(pybind11::module_& mod);
void export_Population(pybind11::module_& mod);
void export_Innovation(pybind11::module_& mod);
void export_InnovationDatabase(pybind11::module_& mod);
void export_Parameters(pybind11::module_& mod);
void export_Lists(pybind11::module_& mod);

PYBIND11_MODULE(_multineat, mod)
{
///////////////////////////////////////////////////////////////////
// Enums
///////////////////////////////////////////////////////////////////

    export_NeuronType(mod);
    export_ActivationFunction(mod);
    export_SearchMode(mod);

///////////////////////////////////////////////////////////////////
// RNG class
///////////////////////////////////////////////////////////////////
    export_RNG(mod);

///////////////////////////////////////////////////////////////////
// Neural Network class
///////////////////////////////////////////////////////////////////

    export_Connection(mod);
    export_Neuron(mod);
    export_NeuralNetwork(mod);

///////////////////////////////////////////////////////////////////
// Genome class
///////////////////////////////////////////////////////////////////

    export_LinkGene(mod);
    export_NeuronGene(mod);
    export_Genome(mod);

///////////////////////////////////////////////////////////////////
// Species class
///////////////////////////////////////////////////////////////////

    export_Species(mod);

///////////////////////////////////////////////////////////////////
// Substrate class
///////////////////////////////////////////////////////////////////

    export_Substrate(mod);

///////////////////////////////////////////////////////////////////
// PhenotypeBehavior class
///////////////////////////////////////////////////////////////////

    export_PhenotypeBehaviour(mod);

///////////////////////////////////////////////////////////////////
// Population class
///////////////////////////////////////////////////////////////////

    export_Population(mod);

    export_Innovation(mod);

    export_InnovationDatabase(mod);

///////////////////////////////////////////////////////////////////
// Parameters class
///////////////////////////////////////////////////////////////////

    export_Parameters(mod);

/////////////////////////////////////////////////////////
// General stuff applicable across the entire module
/////////////////////////////////////////////////////////

    export_Lists(mod);

}
