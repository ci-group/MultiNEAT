//
// Created by matteo on 10/9/19.
//

#include <iostream>
#include <sstream>
#include <Genome.h>

#define BOOST_TEST_MODULE Serialization test
#include <boost/test/included/unit_test.hpp>

std::string serialize(const NEAT::Genome &g)
{
    std::ostringstream output_data;

    {
        cereal::JSONOutputArchive archive(output_data);
        archive << g;
    }

    return output_data.str();
}

NEAT::Genome deserialize(const std::string &data)
{
    NEAT::Genome g;
    std::istringstream input_data(data);
    {
        cereal::JSONInputArchive archive(input_data);
        archive >> g;
    }
    return g;
}

BOOST_AUTO_TEST_CASE(serialize_genome)
{
    NEAT::Parameters params;

    NEAT::Genome g(42,
            2, 1, 3,
            NEAT::ActivationFunction::SIGNED_SIGMOID,
            NEAT::ActivationFunction::SIGNED_SIGMOID,
            params
            );

    const std::string serialized = serialize(g);
    NEAT::Genome copy = deserialize(serialized);

    BOOST_TEST(g.GetID() == copy.GetID());
    BOOST_TEST(g.m_LinkGenes == copy.m_LinkGenes);
    BOOST_TEST(g.m_NeuronGenes == copy.m_NeuronGenes);
    BOOST_TEST(g.GetDepth() == copy.GetDepth());
    BOOST_TEST(g.NumInputs() == copy.NumInputs());
    BOOST_TEST(g.NumOutputs() == copy.NumOutputs());
    BOOST_TEST(g.GetFitness() == copy.GetFitness());
    BOOST_TEST(g.GetAdjFitness() == copy.GetAdjFitness());
    BOOST_TEST(g.GetDepth() == copy.GetDepth());
    BOOST_TEST(g.GetOffspringAmount() == copy.GetOffspringAmount());
    BOOST_TEST(g.m_Evaluated == copy.m_Evaluated);

    // This last test should fail, but it does not :)
    BOOST_TEST(g.m_PhenotypeBehavior == copy.m_PhenotypeBehavior);
}