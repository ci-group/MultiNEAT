#ifndef _GENES_H
#define _GENES_H

///////////////////////////////////////////////////////////////////////////////////////////
//    MultiNEAT - Python/C++ NeuroEvolution of Augmenting Topologies Library
//
//    Copyright (C) 2012 Peter Chervenski
//
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU Lesser General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU Lesser General Public License
//    along with this program.  If not, see < http://www.gnu.org/licenses/ >.
//
//    Contact info:
//
//    Peter Chervenski < spookey@abv.bg >
//    Shane Ryan < shane.mcdonald.ryan@gmail.com >
///////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////
// File:        Genes.h
// Description: Definitions for the Neuron and Link gene classes.
/////////////////////////////////////////////////////////////////

#include <iostream>
#include <vector>
#include <map>
#include "Parameters.h"
#include "Traits.h"
#include "Random.h"
#include "Utils.h"

#include <cereal/cereal.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/map.hpp>
#include <cereal/archives/json.hpp>


namespace NEAT
{


//////////////////////////////////////////////
// Enumeration for all available neuron types
//////////////////////////////////////////////
    enum NeuronType
    {
        NONE = 0,
        INPUT,
        BIAS,
        HIDDEN,
        OUTPUT
    };


//////////////////////////////////////////////////////////
// Enumeration for all possible activation function types
//////////////////////////////////////////////////////////
    enum ActivationFunction
    {
        SIGNED_SIGMOID = 0,   // Sigmoid function   (default) (blurred cutting plane)
        UNSIGNED_SIGMOID,
        TANH,
        TANH_CUBIC,
        SIGNED_STEP,          // Treshold (0 or 1)  (cutting plane)
        UNSIGNED_STEP,
        SIGNED_GAUSS,         // Gaussian           (symettry)
        UNSIGNED_GAUSS,
        ABS,                  // Absolute value |x| (another symettry)
        SIGNED_SINE,          // Sine wave          (smooth repetition)
        UNSIGNED_SINE,
        LINEAR,               // Linear f(x)=x      (combining coordinate frames only)

        RELU,                 // Rectifiers
        SOFTPLUS

    };

    //////////////////////////////////
    // Base Gene class
    //////////////////////////////////
    class Gene
    {
        friend bool operator==(Gene const &lhs, Gene const &rhs);
        friend std::ostream &operator<<(std::ostream &stream, Gene const &gene);

    public:
        // Arbitrary traits
        std::map<std::string, Trait> m_Traits;

        Gene &operator=(const Gene &a_g)
        {
            if (this != &a_g)
            {
                m_Traits = a_g.m_Traits;
            }

            return *this;
        }

        // Randomize based on parameters
        void InitTraits(const std::map<std::string, TraitParameters> &tp, RNG &a_RNG)
        {
            for(auto it = tp.begin(); it != tp.end(); it++)
            {
                // Check what kind of type is this and create such trait
                TraitType t;

                if (it->second.type == "int")
                {
                    IntTraitParameters itp = std::get<IntTraitParameters>(it->second.m_Details);
                    t = a_RNG.RandInt(itp.min, itp.max);
                }
                else if (it->second.type == "float")
                {
                    FloatTraitParameters itp = std::get<FloatTraitParameters>(it->second.m_Details);
                    double x = a_RNG.RandFloat();
                    Scale(x, 0, 1, itp.min, itp.max);
                    t = x;
                }
                else if (it->second.type == "str")
                {
                    StringTraitParameters itp = std::get<StringTraitParameters>(it->second.m_Details);
                    std::vector<double> probs = itp.probs;
                    if (itp.set.size() == 0)
                    {
                        throw std::runtime_error("Empty set of string traits");
                    }
                    probs.resize(itp.set.size());

                    int idx = a_RNG.Roulette(probs);
                    t = itp.set[idx];
                }
                else if (it->second.type == "intset")
                {
                    IntSetTraitParameters itp = std::get<IntSetTraitParameters>(it->second.m_Details);
                    std::vector<double> probs = itp.probs;
                    if (itp.set.size() == 0)
                    {
                        throw std::runtime_error("Empty set of int traits");
                    }
                    probs.resize(itp.set.size());

                    int idx = a_RNG.Roulette(probs);
                    t = itp.set[idx];
                }
                else if (it->second.type == "floatset")
                {
                    FloatSetTraitParameters itp = std::get<FloatSetTraitParameters>(it->second.m_Details);
                    std::vector<double> probs = itp.probs;
                    if (itp.set.size() == 0)
                    {
                        throw std::runtime_error("Empty set of float traits");
                    }
                    probs.resize(itp.set.size());

                    int idx = a_RNG.Roulette(probs);
                    t = itp.set[idx];
                }
#ifdef PYTHON_BINDINGS
                else if (it->second.type == "pyobject")
                {
                    pybind11::object itp = std::get<pybind11::object>(it->second.m_Details);
                    t = itp(); // details is a function that returns a random instance of the trait
                }
                else if (it->second.type == "pyclassset")
                {
                    throw std::runtime_error("Unimplemented");
                    /*
                    TODO
                    I don't understand this code so just remove until we actually need it
                    --Aart 15 02 2022

                    pybind11::object tup = std::get<pybind11::object>(it->second.m_Details);
                    pybind11::list classlist = tup[0].cast<pybind11::list>();
                    pybind11::list probs = tup[1].cast<pybind11::list>();
                    std::vector<double> dprobs;

                    // get the probs
                    size_t ln = probs.size();
                    if ((ln == 0) || (classlist.size() == 0))
                    {
                        throw std::runtime_error("Empty class or probs list");
                    }

                    for (size_t i=0; i<ln; i++)
                    {
                        dprobs.push_back(probs[i].cast<double>());
                    }

                    // instantiate random class
                    int idx = a_RNG.Roulette(dprobs);
                    pybind11::object itp = classlist[idx].cast<pybind11::object>();
                    t = itp();
                    */ 
                }
#endif

                Trait tr;
                tr.value = t;
                tr.dep_key = it->second.dep_key;
                tr.dep_values = it->second.dep_values;
                // todo check for invalid dep_values types here
                m_Traits[it->first] = tr;
            }
        }

        // Traits are merged with this other parent
        void MateTraits(const std::map<std::string, Trait> &t, RNG &a_RNG)
        {
            for(auto it = t.begin(); it != t.end(); it++)
            {
                TraitType mine = m_Traits[it->first].value;
                TraitType yours = it->second.value;

                if (!(mine.index() == yours.index()))
                {
                    throw std::runtime_error("Types of traits doesn't match");
                }

                // if generic python object, forward all processing to its method
#ifdef PYTHON_BINDINGS
                if (std::holds_alternative<pybind11::object>(mine))
                {
                    // call mating function
                    m_Traits[it->first].value = std::get<pybind11::object>(mine).attr("mate")(std::get<pybind11::object>(yours));
                }
                else
#endif
                {
                    if (a_RNG.RandFloat() < 0.5) // pick either one
                    {
                        m_Traits[it->first].value = (a_RNG.RandFloat() < 0.5) ? mine : yours;
                    }
                    else
                    {
                        // try to average
                        if (std::holds_alternative<int>(mine))
                        {
                            int m1 = std::get<int>(mine);
                            int m2 = std::get<int>(yours);
                            m_Traits[it->first].value = (m1 + m2) / 2;
                        }

                        if (std::holds_alternative<double>(mine))
                        {
                            double m1 = std::get<double>(mine);
                            double m2 = std::get<double>(yours);
                            m_Traits[it->first].value = (m1 + m2) / 2.0;
                        }

                        if (std::holds_alternative<std::string>(mine))
                        {
                            // strings are always either-or
                            m_Traits[it->first].value = (a_RNG.RandFloat() < 0.5) ? mine : yours;
                        }

                        if (std::holds_alternative<intsetelement>(mine))
                        {
                            // int sets are always either-or
                            m_Traits[it->first].value = (a_RNG.RandFloat() < 0.5) ? mine : yours;
                        }

                        if (std::holds_alternative<floatsetelement>(mine))
                        {
                            // float sets are always either-or
                            m_Traits[it->first].value = (a_RNG.RandFloat() < 0.5) ? mine : yours;
                        }
                    }
                }
            }
        }


        // Traits are mutated according to parameters
        bool MutateTraits(const std::map<std::string, TraitParameters> &tp, RNG &a_RNG)
        {
            bool did_mutate = false;
            for(auto it = tp.cbegin(); it != tp.cend(); it++)
            {
                // only mutate the trait if it's enabled
                bool doit = false;
                if (it->second.dep_key != "")
                {
                    // there is such trait..
                    if (m_Traits.count(it->second.dep_key) != 0)
                    {
                        // and it matches any of the right values?
                        for(long unsigned int ix=0; ix<it->second.dep_values.size(); ix++)
                        {
                            if (m_Traits[it->second.dep_key].value == it->second.dep_values[ix])
                            {
                                doit = true;
                                break;
                            }
                        }
                    }
                }
                else
                {
                    doit = true;
                }

                if (doit && a_RNG.RandFloat() < it->second.m_MutationProb)
                {
                    if (it->second.type == "int")
                    {
                        IntTraitParameters itp = std::get<IntTraitParameters>(it->second.m_Details);
                        // determine type of mutation - modify or replace, according to parameters
                        int val = std::get<int>(m_Traits[it->first].value);
                        int cur = val;
                        if (a_RNG.RandFloat() < itp.mut_replace_prob)
                        {
                            // replace
                            while(cur == val)
                            {
                                val = a_RNG.RandInt(itp.min, itp.max);
                            }
                        }
                        else
                        {
                            // modify
                            while(cur == val)
                            {
                                val += a_RNG.RandInt(-itp.mut_power, itp.mut_power);
                                Clamp(val, itp.min, itp.max);
                            }
                        }
                        m_Traits[it->first].value = val;
                        did_mutate = true;
                    }
                    else if (it->second.type == "float")
                    {
                        FloatTraitParameters itp = std::get<FloatTraitParameters>(it->second.m_Details);
                        double val = std::get<double>(m_Traits[it->first].value);
                        double cur = val;

                        // determine type of mutation - modify or replace, according to parameters
                        if (a_RNG.RandFloat() < itp.mut_replace_prob)
                        {
                            // replace;
                            while(cur == val)
                            {
                                val = a_RNG.RandFloat();
                                Scale(val, 0, 1, itp.min, itp.max);
                            }
                        }
                        else
                        {
                            // modify
                            while(cur == val)
                            {
                                val += a_RNG.RandFloatSigned() * itp.mut_power;
                                Clamp(val, itp.min, itp.max);
                            }
                        }
                        m_Traits[it->first].value = val;
                        did_mutate = true;
                    }
                    else if (it->second.type == "str")
                    {
                        StringTraitParameters itp = std::get<StringTraitParameters>(it->second.m_Details);
                        std::vector<double> probs = itp.probs;
                        probs.resize(itp.set.size());
                        std::string cur = std::get<std::string>(m_Traits[it->first].value);
                        
                        int idx;
                        do 
                        {
                            idx = a_RNG.Roulette(probs);
                        } 
                        while (cur == itp.set[idx]);

                        // now choose the new idx from the set
                        m_Traits[it->first].value = itp.set[idx];
                        did_mutate = true;
                    }
                    else if (it->second.type == "intset")
                    {
                        IntSetTraitParameters itp = std::get<IntSetTraitParameters>(it->second.m_Details);
                        std::vector<double> probs = itp.probs;
                        probs.resize(itp.set.size());
                        intsetelement cur = std::get<intsetelement>(m_Traits[it->first].value);

                        int idx;
                        do 
                        {
                            idx = a_RNG.Roulette(probs);
                        } 
                        while (cur.value == itp.set[idx].value);

                        // now choose the new idx from the set
                        m_Traits[it->first].value = itp.set[idx];
                        did_mutate = true;
                    }
                    else if (it->second.type == "floatset")
                    {
                        FloatSetTraitParameters itp = std::get<FloatSetTraitParameters>(it->second.m_Details);
                        std::vector<double> probs = itp.probs;
                        probs.resize(itp.set.size());
                        floatsetelement cur = std::get<floatsetelement>(m_Traits[it->first].value);

                        int idx;
                        do 
                        {
                            idx = a_RNG.Roulette(probs);
                        } 
                        while (cur.value == itp.set[idx].value);

                        // now choose the new idx from the set
                        m_Traits[it->first].value = itp.set[idx];
                        did_mutate = true;
                    }
#ifdef PYTHON_BINDINGS
                    else if ((it->second.type == "pyobject") || (it->second.type == "pyclassset"))
                    {
                        m_Traits[it->first].value = std::get<pybind11::object>(m_Traits[it->first].value).attr("mutate")();
                        did_mutate = true;
                    }
#endif
                }
            }

            return did_mutate;
        }

        // Compute and return distances between each matching pair of traits
        std::map<std::string, double> GetTraitDistances(const std::map<std::string, Trait> &other) const
        {
            std::map<std::string, double> dist;
            for(auto it = other.begin(); it!=other.end(); it++)
            {
                const TraitType mine = m_Traits.at(it->first).value;
                const TraitType yours = it->second.value;

                if (!(mine.index() == yours.index()))
                {
                    throw std::runtime_error("Types of traits don't match");
                }

                // only do it if the trait if it's enabled
                // todo: not sure about the distance, think more about it
                bool doit = false;
                if (it->second.dep_key != "")
                {
                    // there is such trait..
                    if (m_Traits.count(it->second.dep_key) != 0)
                    {
                        // and it has the right value?
                        // also the other genome has to have the trait turned on
                        for(long unsigned int ix=0; ix<it->second.dep_values.size(); ix++)
                        {
                            if ((m_Traits.at(it->second.dep_key).value == it->second.dep_values[ix]) &&
                                (other.at(it->second.dep_key).value == it->second.dep_values[ix]))
                            {
                                doit = true;
                                break;
                            }
                        }
                    }
                }
                else
                {
                    doit = true;
                }

                if (doit)
                {
                    if (std::holds_alternative<int>(mine))
                    {
                        // distance between ints - calculate directly
                        dist[it->first] = abs(std::get<int>(mine) - std::get<int>(yours));
                    }
                    if (std::holds_alternative<double>(mine))
                    {
                        // distance between floats - calculate directly
                        dist[it->first] = abs(std::get<double>(mine) - std::get<double>(yours));
                    }
                    if (std::holds_alternative<std::string>(mine))
                    {
                        // distance between strings - matching is 0, non-matching is 1
                        if (std::get<std::string>(mine) == std::get<std::string>(yours))
                        {
                            dist[it->first] = 0.0;
                        }
                        else
                        {
                            dist[it->first] = 1.0;
                        }
                    }
                    if (std::holds_alternative<intsetelement>(mine))
                    {
                        // distance between ints - calculate directly
                        dist[it->first] = abs((std::get<intsetelement>(mine)).value - (std::get<intsetelement>(yours)).value);
                    }
                    if (std::holds_alternative<floatsetelement>(mine))
                    {
                        // distance between floats - calculate directly
                        dist[it->first] = abs((std::get<floatsetelement>(mine)).value - (std::get<floatsetelement>(yours)).value);
                    }
#ifdef PYTHON_BINDINGS
                    if (std::holds_alternative<pybind11::object>(mine))
                    {
                        // distance between objects - calculate via method
                        dist[it->first] = std::get<pybind11::object>(mine).attr("distance_to")(std::get<pybind11::object>(yours)).cast<double>();
                    }
#endif
                }
            }

            return dist;
        }

        // Serialization
        template<class Archive>
        void serialize(Archive & ar)
        {
            ar & m_Traits;
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

    bool operator==(Gene const &lhs, Gene const &rhs);
    std::ostream &operator<<(std::ostream &stream, Gene const &gene);

    //////////////////////////////////
    // This class defines a link gene
    //////////////////////////////////
    class LinkGene : public Gene
    {
        /////////////////////
        // Members
        /////////////////////

        friend bool operator==(LinkGene const &lhs, LinkGene const &rhs);
        friend std::ostream &operator<<(std::ostream &stream, LinkGene const &gene);

    public:

        // These variables are initialized once and cannot be changed
        // anymore

        // The IDs of the neurons that this link connects
        int m_FromNeuronID, m_ToNeuronID;

        // The link's innovation ID
        int m_InnovationID;

        // This variable is modified during evolution
        // The weight of the connection
        double m_Weight;

        // Is it recurrent?
        bool m_IsRecurrent;

    public:

        double GetWeight() const
        {
            return m_Weight;
        }

        void SetWeight(const double a_Weight)
        {
            m_Weight = a_Weight;
        }

        ////////////////
        // Constructors
        ////////////////
        LinkGene()
            : m_FromNeuronID(0)
            , m_ToNeuronID(0)
            , m_InnovationID(0)
            , m_Weight(0)
            , m_IsRecurrent(false)
        {}

        LinkGene(int a_InID, int a_OutID, int a_InnovID, double a_Wgt, bool a_Recurrent = false)
        {
            m_FromNeuronID = a_InID;
            m_ToNeuronID = a_OutID;
            m_InnovationID = a_InnovID;

            m_Weight = a_Wgt;
            m_IsRecurrent = a_Recurrent;
        }

        // assigment operator
        LinkGene &operator=(const LinkGene &a_g)
        {
            if (this != &a_g)
            {
                m_FromNeuronID = a_g.m_FromNeuronID;
                m_ToNeuronID = a_g.m_ToNeuronID;
                m_Weight = a_g.m_Weight;
                m_IsRecurrent = a_g.m_IsRecurrent;
                m_InnovationID = a_g.m_InnovationID;
                m_Traits = a_g.m_Traits;
            }

            return *this;
        }

        //////////////
        // Methods
        //////////////

        // Access to static (const) variables
        int FromNeuronID() const
        {
            return m_FromNeuronID;
        }

        int ToNeuronID() const
        {
            return m_ToNeuronID;
        }

        int InnovationID() const
        {
            return m_InnovationID;
        }

        bool IsRecurrent() const
        {
            return m_IsRecurrent;
        }

        bool IsLoopedRecurrent() const
        {
            return m_FromNeuronID == m_ToNeuronID;
        }

        //overload '<', '>', '!=' and '==' used for sorting and comparison (we use the innovation ID as the criteria)
        friend bool operator<(const LinkGene &a_lhs, const LinkGene &a_rhs)
        {
            return (a_lhs.m_InnovationID < a_rhs.m_InnovationID);
        }

        friend bool operator>(const LinkGene &a_lhs, const LinkGene &a_rhs)
        {
            return (a_lhs.m_InnovationID > a_rhs.m_InnovationID);
        }

        friend bool operator!=(const LinkGene &a_lhs, const LinkGene &a_rhs)
        {
            return (a_lhs.m_InnovationID != a_rhs.m_InnovationID);
        }

        // Serialization
        template<class Archive>
        void serialize(Archive & ar)
        {
            ar & cereal::base_class<Gene>(this);
            ar & m_FromNeuronID;
            ar & m_ToNeuronID;
            ar & m_InnovationID;
            ar & m_IsRecurrent;
            ar & m_Weight;
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

    bool operator==(LinkGene const &lhs, LinkGene const &rhs);
    std::ostream &operator<<(std::ostream &stream, LinkGene const &gene);


////////////////////////////////////
// This class defines a neuron gene
////////////////////////////////////
    class NeuronGene : public Gene
    {
        /////////////////////
        // Members
        /////////////////////

        friend bool operator==(NeuronGene const &lhs, NeuronGene const &rhs);
        friend std::ostream &operator<<(std::ostream &stream, NeuronGene const &gene);

    public:
        // These variables are initialized once and cannot be changed
        // anymore

        // Its unique identification number
        int m_ID;

        // Its type and role in the network
        NeuronType m_Type;

    public:
        // These variables are modified during evolution
        // Safe to access directly

        // useful for displaying the genome
        int x, y;
        // Position (depth) within the network
        double m_SplitY;


        /////////////////////////////////////////////////////////
        // Any additional properties of the neuron
        // should be added here. This may include
        // time constant & bias for leaky integrators,
        // activation function type,
        // activation function slope (or maybe other properties),
        // etc...
        /////////////////////////////////////////////////////////

        // Additional parameters associated with the
        // neuron's activation function.
        // The current activation function may not use
        // any of them anyway.
        // A is usually used to alter the function's slope with a scalar
        // B is usually used to force a bias to the neuron
        // -------------------
        // Sigmoid : using A, B (slope, shift)
        // Step    : using B    (shift)
        // Gauss   : using A, B (slope, shift))
        // Abs     : using B    (shift)
        // Sine    : using A    (frequency, phase)
        // Square  : using A, B (high phase lenght, low phase length)
        // Linear  : using B    (shift)
        double m_A, m_B;

        // Time constant value used when
        // the neuron is activating in leaky integrator mode
        double m_TimeConstant;

        // Bias value used when the neuron is activating in
        // leaky integrator mode
        double m_Bias;

        // The type of activation function the neuron has
        ActivationFunction m_ActFunction;

        ////////////////
        // Constructors
        ////////////////
        NeuronGene()
        {

        }

        NeuronGene(NeuronType a_type, int a_id, double a_splity)
        {
            m_ID = a_id;
            m_Type = a_type;
            m_SplitY = a_splity;

            // Initialize the node specific parameters
            m_A = 0.0f;
            m_B = 0.0f;
            m_TimeConstant = 0.0f;
            m_Bias = 0.0f;
            m_ActFunction = UNSIGNED_SIGMOID;

            x = 0;
            y = 0;
        }

        // assigment operator
        NeuronGene &operator=(const NeuronGene &a_g)
        {
            if (this != &a_g)
            {
                m_ID = a_g.m_ID;
                m_Type = a_g.m_Type;
                m_SplitY = a_g.m_SplitY;

                // maybe inputs don't need that
                if ((m_Type != NeuronType::INPUT) && (m_Type != NeuronType::BIAS))
                {
                    x = a_g.x;
                    y = a_g.y;
                    m_A = a_g.m_A;
                    m_B = a_g.m_B;
                    m_TimeConstant = a_g.m_TimeConstant;
                    m_Bias = a_g.m_Bias;
                    m_ActFunction = a_g.m_ActFunction;

                    m_Traits = a_g.m_Traits;
                }
            }

            return *this;
        }


        //////////////
        // Methods
        //////////////

        // Accessing static (const) variables
        int ID() const
        {
            return m_ID;
        }

        NeuronType Type() const
        {
            return m_Type;
        }

        double SplitY() const
        {
            return m_SplitY;
        }

        // Initializing
        void Init(double a_A, double a_B, double a_TimeConstant, double a_Bias, ActivationFunction a_ActFunc)
        {
            m_A = a_A;
            m_B = a_B;
            m_TimeConstant = a_TimeConstant;
            m_Bias = a_Bias;
            m_ActFunction = a_ActFunc;
        }

        // Serialization
        template<class Archive>
        void serialize(Archive & ar)
        {
            ar & cereal::base_class<Gene>(this);
            ar & m_ID;
            ar & m_Type;
            ar & m_A;
            ar & m_B;
            ar & m_TimeConstant;
            ar & m_Bias;
            ar & x;
            ar & y;
            ar & m_ActFunction;
            ar & m_SplitY;
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

    bool operator==(NeuronGene const &lhs, NeuronGene const &rhs);
    std::ostream &operator<<(std::ostream &stream, NeuronGene const &gene);


} // namespace NEAT

#endif
