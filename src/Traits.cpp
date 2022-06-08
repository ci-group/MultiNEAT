#include "Traits.h"

namespace NEAT
{

    bool operator==(Trait const &lhs, Trait const &rhs)
    {
        return lhs.value == rhs.value &&
               lhs.dep_key == rhs.dep_key; // &&
                                           // lhs.dep_values == rhs.dep_values
    }

    std::ostream &operator<<(std::ostream &stream, Trait const &trait)
    {
        stream << trait.Serialize();
        return stream;
    }

    std::ostream &operator<<(std::ostream &stream, intsetelement const &trait)
    {
        stream << trait.Serialize();
        return stream;
    }

    std::ostream &operator<<(std::ostream &stream, floatsetelement const &trait)
    {
        stream << trait.Serialize();
        return stream;
    }

}
