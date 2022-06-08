//
// Aart 2022 jun 8
//

#include <iostream>
#include <sstream>
#include <Innovation.h>
#include <Genome.h>

#define BOOST_TEST_MODULE serialize_innovation_database test
#include <boost/test/included/unit_test.hpp>

BOOST_AUTO_TEST_CASE(serialize_innovation_database)
{
    auto innov_db = NEAT::InnovationDatabase();

    NEAT::Parameters params;
    NEAT::Genome genome(42,
                        2, 1, 3,
                        NEAT::ActivationFunction::SIGNED_SIGMOID,
                        NEAT::ActivationFunction::SIGNED_SIGMOID,
                        params);

    NEAT::RNG rng;

    do
    {
        genome.Mutate(false, SearchMode::BLENDED, innov_db, params, rng);
    } while (innov_db.m_Innovations.size() < 100);

    std::string serialized = innov_db.Serialize();
    NEAT::InnovationDatabase innov_db_loaded = NEAT::InnovationDatabase();
    innov_db_loaded.Deserialize(serialized);

    BOOST_TEST(innov_db == innov_db_loaded);
}
