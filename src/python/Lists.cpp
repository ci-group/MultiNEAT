//
// Created by matteo on 6/7/20.
// Edited by aart in 2022
//

#include "../Random.h"

#include "../Genome.h"
#include "../Species.h"
#include "../NeuralNetwork.h"
#include <pybind11/pybind11.h>
#include <pybind11/stl_bind.h>

using namespace NEAT;

PYBIND11_MAKE_OPAQUE(std::vector<double>);
PYBIND11_MAKE_OPAQUE(std::vector<std::vector<double>>);
PYBIND11_MAKE_OPAQUE(std::vector<float>);
PYBIND11_MAKE_OPAQUE(std::vector<std::vector<float>>);
PYBIND11_MAKE_OPAQUE(std::vector<int>);
PYBIND11_MAKE_OPAQUE(std::vector<std::vector<int>>);
PYBIND11_MAKE_OPAQUE(std::vector<NEAT::Genome>);
PYBIND11_MAKE_OPAQUE(std::vector<NEAT::Species>);
PYBIND11_MAKE_OPAQUE(std::vector<NEAT::Neuron>);
PYBIND11_MAKE_OPAQUE(std::vector<NEAT::Connection>);
PYBIND11_MAKE_OPAQUE(std::vector<NEAT::NeuronGene>);
PYBIND11_MAKE_OPAQUE(std::vector<NEAT::LinkGene>);
PYBIND11_MAKE_OPAQUE(std::vector<NEAT::PhenotypeBehavior>);

void export_Lists(pybind11::module_& mod) {
    pybind11::bind_vector<std::vector<double>>(mod, "DoublesList");
    pybind11::bind_vector<std::vector<std::vector<double>>>(mod, "DoublesList2");
    pybind11::bind_vector<std::vector<float>>(mod, "FloatsList");
    pybind11::bind_vector<std::vector<std::vector<float>>>(mod, "FloatsList2D");
    pybind11::bind_vector<std::vector<int>>(mod, "IntsList");
    pybind11::bind_vector<std::vector<std::vector<int>>>(mod, "IntsList2D");
    // These are necessary to let us iterate through the vectors of species, genomes and genes
    pybind11::bind_vector<std::vector<NEAT::Genome>>(mod, "GenomeList");
    pybind11::bind_vector<std::vector<NEAT::Species>>(mod, "SpeciesList");
    // These are necessary to iterate through lists of Neurons and Connections
    pybind11::bind_vector<std::vector<NEAT::Neuron>>(mod, "NeuronList");
    pybind11::bind_vector<std::vector<NEAT::Connection>>(mod, "ConnectionList");
    pybind11::bind_vector<std::vector<NEAT::NeuronGene>>(mod, "NeuronGeneList");
    pybind11::bind_vector<std::vector<NEAT::LinkGene>>(mod, "LinkGeneList");
    // For dealing with Phenotype behaviors
    pybind11::bind_vector<std::vector<NEAT::PhenotypeBehavior>>(mod, "PhenotypeBehaviorList");
}
