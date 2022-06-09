//
// Created by matteo on 10/9/19.
//

#include <iostream>
#include <sstream>
#include <Genome.h>

#define BOOST_TEST_MODULE Serialization test
#include <boost/test/included/unit_test.hpp>

BOOST_AUTO_TEST_CASE(serialize_genome)
{
    NEAT::Parameters params;
    NEAT::RNG rng;

    NEAT::Genome genome(42,
                        2, 1, 3,
                        NEAT::ActivationFunction::SIGNED_SIGMOID,
                        NEAT::ActivationFunction::SIGNED_SIGMOID,
                        params);
    std::string serialized = genome.Serialize();

    NEAT::Genome genome_loaded;
    genome_loaded.Deserialize(serialized);

    BOOST_TEST(genome == genome_loaded);

    auto innov_db = NEAT::InnovationDatabase();

    do
    {
        genome.Mutate(false, SearchMode::BLENDED, innov_db, params, rng);
    } while (innov_db.m_Innovations.size() < 100);

    serialized = genome.Serialize();

    NEAT::Genome genome_loaded2;
    genome_loaded2.Deserialize(serialized);

    BOOST_TEST(genome == genome_loaded2);

    // below are old tests, keeping them as extra
    BOOST_TEST(genome.GetID() == genome_loaded2.GetID());
    BOOST_TEST(genome.m_LinkGenes == genome_loaded2.m_LinkGenes);
    BOOST_TEST(genome.m_NeuronGenes == genome_loaded2.m_NeuronGenes);
    BOOST_TEST(genome.GetDepth() == genome_loaded2.GetDepth());
    BOOST_TEST(genome.NumInputs() == genome_loaded2.NumInputs());
    BOOST_TEST(genome.NumOutputs() == genome_loaded2.NumOutputs());
    BOOST_TEST(genome.GetFitness() == genome_loaded2.GetFitness());
    BOOST_TEST(genome.GetAdjFitness() == genome_loaded2.GetAdjFitness());
    BOOST_TEST(genome.GetDepth() == genome_loaded2.GetDepth());
    BOOST_TEST(genome.GetOffspringAmount() == genome_loaded2.GetOffspringAmount());
    BOOST_TEST(genome.m_Evaluated == genome_loaded2.m_Evaluated);
}
