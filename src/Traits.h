//
// Created by peter on 28.04.17.
//

#ifndef MULTINEAT_TRAITS_H
#define MULTINEAT_TRAITS_H

#include <string>
#include <vector>
#include <variant>
#include <cmath>
#include <cereal/cereal.hpp>
#include <cereal/archives/json.hpp>
#include <cereal/types/variant.hpp>
#include <cereal/types/vector.hpp>

#ifdef PYTHON_BINDINGS
    #include <pybind11/pybind11.h>
#endif

namespace NEAT
{
    class intsetelement
    {
    public:
        // Comparison operator
        bool operator==(const intsetelement& rhs) const
        {
            return rhs.value == value;
        }

        friend std::ostream &operator<<(std::ostream &stream, intsetelement const &trait);

        int value;

        // Serialization
        template<class Archive>
        void serialize(Archive & ar)
        {
            ar & value;
        }

        std::string Serialize() const
        {
            std::ostringstream os;
            {
                cereal::JSONOutputArchive oa(os);
                oa << *this;
            }
            return os.str();
        }

        void Deserialize(const std::string &text)
        {
            std::istringstream is (text);
            cereal::JSONInputArchive ia(is);
            ia >> *this;
        }
    };
    std::ostream &operator<<(std::ostream &stream, intsetelement const &trait);

    class floatsetelement
    {
    public:
        // Comparison operator
        bool operator==(const floatsetelement& rhs) const
        {
            return rhs.value == value;
        }

        friend std::ostream &operator<<(std::ostream &stream, floatsetelement const &trait);

        double value;

        // Serialization
        template<class Archive>
        void serialize(Archive & ar)
        {
            ar & value;
        }

        std::string Serialize() const
        {
            std::ostringstream os;
            {
                cereal::JSONOutputArchive oa(os);
                oa << *this;
            }
            return os.str();
        }

        void Deserialize(const std::string &text)
        {
            std::istringstream is (text);
            cereal::JSONInputArchive ia(is);
            ia >> *this;
        }
    };
    std::ostream &operator<<(std::ostream &stream, floatsetelement const &trait);
    
    typedef std::variant<int, double, std::string, intsetelement, floatsetelement
#ifdef PYTHON_BINDINGS
  , pybind11::object
#endif
    > TraitType;

    class IntTraitParameters
    {
    public:
        int min, max;
        int mut_power; // magnitude of max change up/down
        double mut_replace_prob; // probability to replace when mutating

        IntTraitParameters()
        {
            min = 0; max = 0;
            mut_power = 0;
            mut_replace_prob = 0;
        }
    };
    class FloatTraitParameters
    {
    public:
        double min, max;
        double mut_power; // magnitude of max change up/down
        double mut_replace_prob; // probability to replace when mutating

        FloatTraitParameters()
        {
            min = 0; max = 0;
            mut_power = 0;
            mut_replace_prob = 0;
        }
    };
    class StringTraitParameters
    {
    public:
        std::vector<std::string> set; // the set of possible strings
        std::vector<double> probs; // their respective probabilities for appearance
    };
    class IntSetTraitParameters
    {
    public:
        std::vector<intsetelement> set; // the set of possible ints
        std::vector<double> probs; // their respective probabilities for appearance
    };
    class FloatSetTraitParameters
    {
    public:
        std::vector<floatsetelement> set; // the set of possible floats
        std::vector<double> probs; // their respective probabilities for appearance
    };


    class TraitParameters
    {
    public:
        double m_ImportanceCoeff;
        double m_MutationProb;

        std::string type; // can be "int", "float", "string", "intset", "floatset", "pyobject"
        std::variant<IntTraitParameters,
                    FloatTraitParameters,
                    StringTraitParameters,
                    IntSetTraitParameters,
                    FloatSetTraitParameters
#ifdef PYTHON_BINDINGS
                  , pybind11::object
#endif
        > m_Details;

        std::string dep_key; // counts only if this other trait exists..
        std::vector<TraitType> dep_values; // and has one of these values

        // keep dep_key empty and no conditional logic will apply

        TraitParameters()
            : m_ImportanceCoeff(0)
            , m_MutationProb(0)
            , type("int")
            , m_Details(IntTraitParameters())
            , dep_key("")
        {
            dep_values.push_back( std::string("") );
        }
    };

    class Trait
    {
        friend bool operator==(Trait const &lhs, Trait const &rhs);
        friend std::ostream &operator<<(std::ostream &stream, Trait const &trait);

    public:
        TraitType value;

        Trait()
        {
            value = 0;
            dep_values.push_back(0);
            dep_key = "";
        }

        std::string dep_key; // counts only if this other trait exists..
        std::vector<TraitType> dep_values; // and has this value

        // Serialization
        template<class Archive>
        void serialize(Archive & ar)
        {
            // ar & value;
            ar & dep_key;
            // ar & dep_values; TODO
        }

        std::string Serialize() const
        {
            std::ostringstream os;
            {
                cereal::JSONOutputArchive oa(os);
                oa << *this;
            }
            return os.str();
        }

        void Deserialize(const std::string &text)
        {
            std::istringstream is (text);
            cereal::JSONInputArchive ia(is);
            ia >> *this;
        }
    };

    bool operator==(Trait const &lhs, Trait const &rhs);
    std::ostream &operator<<(std::ostream &stream, Trait const &trait);

}
#endif //MULTINEAT_TRAITS_H
