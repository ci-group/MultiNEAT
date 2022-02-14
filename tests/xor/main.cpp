/*
 * Main.cpp
 *
 *  Created on: Sep 20, 2012
 *      Author: peter
 */

 /*
  * Ignore this file. I use it to test stuff.
  *
  */

#include "Genome.h"
#include "Population.h"
#include "NeuralNetwork.h"
#include "Parameters.h"
#include "Substrate.h"

#include <iostream>
#include <limits>

#define BOOST_TEST_MODULE XOR test
#include <boost/test/included/unit_test.hpp>

using namespace NEAT;

double xortest(Genome& g)
{
    double f = 0;

    NeuralNetwork net;
    g.BuildPhenotype(net);

    static const std::vector< std::vector< double > > inputs {
            {0.0,0.0,1.0},
            {0.0,1.0,1.0},
            {1.0,0.0,1.0},
            {1.0,1.0,1.0},
    };
    static const std::vector< double > outputs {
        0.0,
        1.0,
        1.0,
        0.0
    };

    for (long unsigned int i=0; i < inputs.size(); i++)
    {
        net.Input(inputs[i]);
        net.Activate();
        double test_output = outputs[i];
        double output = net.Output()[0];

        double diff = std::abs(test_output - output);
        f -= diff;
    }

    return f;
}


BOOST_AUTO_TEST_CASE(multineat_xor)
{
    Parameters *_params = new Parameters();
    Parameters &params = *_params;

    params.PopulationSize = 100;
    params.DynamicCompatibility = true;
    params.NormalizeGenomeSize = true;
    params.WeightDiffCoeff = 0.1;
    params.CompatTreshold = 2.0;
    params.YoungAgeTreshold = 15;
    params.SpeciesMaxStagnation = 15;
    params.OldAgeTreshold = 35;
    params.MinSpecies = 2;
    params.MaxSpecies = 10;
    params.RouletteWheelSelection = false;
    params.RecurrentProb = 0.0;
    params.OverallMutationRate = 1.0;

    params.ArchiveEnforcement = false;

    params.MutateWeightsProb = 0.05;

    params.WeightMutationMaxPower = 0.5;
    params.WeightReplacementMaxPower = 8.0;
    params.MutateWeightsSevereProb = 0.0;
    params.WeightMutationRate = 0.25;
    params.WeightReplacementRate = 0.9;

    params.MaxWeight = 8;

    params.MutateAddNeuronProb = 0.001;
    params.MutateAddLinkProb = 0.3;
    params.MutateRemLinkProb = 0.0;

    params.MinActivationA  = 4.9;
    params.MaxActivationA  = 4.9;

    params.ActivationFunction_SignedSigmoid_Prob = 0.0;
    params.ActivationFunction_UnsignedSigmoid_Prob = 1.0;
    params.ActivationFunction_Tanh_Prob = 0.0;
    params.ActivationFunction_SignedStep_Prob = 0.0;

    params.CrossoverRate = 0.0 ;
    params.MultipointCrossoverRate = 0.0;
    params.SurvivalRate = 0.2;

    params.AllowClones = true;
    params.AllowLoops = false;

    params.MutateNeuronTraitsProb = 0.0;
    params.MutateLinkTraitsProb = 0.0;

    Genome starting_genome(0, 3, 0, 1,
             false,
             UNSIGNED_SIGMOID,
             UNSIGNED_SIGMOID,
             0,
             params,
             0);

    int seed = 0;
    Population pop(starting_genome, params, true, 1.0, seed);
    pop.m_RNG.Seed(seed);

    double bestf = -std::numeric_limits<double>::infinity();
    for(int k=1; k<=21; k++)
    {
        bestf = -std::numeric_limits<double>::infinity();
        for(auto & m_Specie : pop.m_Species)
        {
            for(auto & m_Individual : m_Specie.m_Individuals)
            {
                double f = xortest(m_Individual);
                m_Individual.SetFitness(f);
                m_Individual.SetEvaluated();
                BOOST_TEST(not m_Individual.HasLoops());

                if (f > bestf)
                {
                    bestf = f;
                }
            }
        }

        Genome g = pop.GetBestGenome();
//        g.PrintAllTraits();

        std::cout << "Generation: " << k << ", best fitness: " << bestf << std::endl;
//        std::cout << "Species: " << pop.m_Species.size() << std::endl;
        pop.Epoch();
    }

//    double best_fitness = pop.GetBestGenome().GetFitness();
    double best_fitness = pop.GetBestFitnessEver();
    std::cout << "best fitness: " << best_fitness << std::endl;

    BOOST_TEST(best_fitness == bestf);
    BOOST_TEST(best_fitness > -1.2e-5);
    BOOST_TEST(best_fitness < 0);
}
