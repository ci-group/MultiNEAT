#include "Genes.h"

namespace NEAT
{

    bool operator==(Gene const &lhs, Gene const &rhs)
    {
        return lhs.m_Traits == rhs.m_Traits;
    }

    std::ostream &operator<<(std::ostream &stream, Gene const &gene)
    {
        stream << gene.Serialize();
        return stream;
    }

    bool operator==(LinkGene const &lhs, LinkGene const &rhs)
    {
        return static_cast<Gene const &>(lhs) == static_cast<Gene const &>(rhs) &&
               lhs.m_FromNeuronID == rhs.m_FromNeuronID &&
               lhs.m_ToNeuronID == rhs.m_ToNeuronID &&
               lhs.m_InnovationID == rhs.m_InnovationID &&
               lhs.m_IsRecurrent == rhs.m_IsRecurrent &&
               lhs.m_Weight == rhs.m_Weight;
    }

    std::ostream &operator<<(std::ostream &stream, LinkGene const &gene)
    {
        stream << gene.Serialize();
        return stream;
    }

    bool operator==(NeuronGene const &lhs, NeuronGene const &rhs)
    {
        return static_cast<Gene const &>(lhs) == static_cast<Gene const &>(rhs) &&
               lhs.m_ID == rhs.m_ID &&
               lhs.m_Type == rhs.m_Type &&
               lhs.x == rhs.x &&
               lhs.y == rhs.y &&
               lhs.m_SplitY == rhs.m_SplitY &&
               lhs.m_A == rhs.m_A &&
               lhs.m_B == rhs.m_B &&
               lhs.m_TimeConstant == rhs.m_TimeConstant &&
               lhs.m_Bias == rhs.m_Bias &&
               lhs.m_ActFunction == rhs.m_ActFunction;
    }

    std::ostream &operator<<(std::ostream &stream, NeuronGene const &gene)
    {
        stream << gene.Serialize();
        return stream;
    }

}
