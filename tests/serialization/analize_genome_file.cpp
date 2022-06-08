//
// Created by matteo on 10/9/19.
//

#include <iostream>
#include <Genome.h>


NEAT::Genome deserialize(const std::string &filename)
{
    NEAT::Genome g;
    std::ifstream input_file(filename);
    {
        cereal::JSONInputArchive archive(input_file);
        archive >> g;
    }
    return g;
}

int main(int argc, const char** argv)
{
    assert(argc == 2);
    NEAT::Genome g = deserialize(argv[1]);

    std::cout << g.GetID() << std::endl;
    std::cout << g.NumInputs() << std::endl;
    std::cout << g.NumOutputs() << std::endl;
    std::cout << g.GetFitness() << std::endl;
    std::cout << g.GetAdjFitness() << std::endl;
    std::cout << g.GetDepth() << std::endl;
    std::cout << g.GetOffspringAmount() << std::endl;
    std::cout << (g.m_Evaluated ? "True" : "False") << std::endl;

    std::cout << g.m_LinkGenes.size() << std::endl;
    for (const auto &l_gene: g.m_LinkGenes)
    {
        std::cout << l_gene.m_InnovationID << std::endl;
        std::cout << l_gene.m_FromNeuronID << std::endl;
        std::cout << l_gene.m_ToNeuronID << std::endl;
        std::cout << (l_gene.m_IsRecurrent ? "True" : "False") << std::endl;
        std::cout << l_gene.m_Weight << std::endl;
//        std::cout << l_gene.m_Traits << std::endl;
    }

    std::cout << g.m_NeuronGenes.size() << std::endl;
    for (const auto &n_gene: g.m_NeuronGenes)
    {
        std::cout << n_gene.m_ID << std::endl;
        std::cout << n_gene.m_Type << std::endl;
        std::cout << n_gene.m_A << std::endl;
        std::cout << n_gene.m_B << std::endl;
        std::cout << n_gene.m_TimeConstant << std::endl;
        std::cout << n_gene.m_Bias << std::endl;
        std::cout << n_gene.x << std::endl;
        std::cout << n_gene.y << std::endl;
        std::cout << n_gene.m_ActFunction << std::endl;
        std::cout << n_gene.m_SplitY << std::endl;
//        std::cout << n_gene.m_Traits << std::endl;
    }

    return 0;
}
