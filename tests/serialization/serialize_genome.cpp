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
}
