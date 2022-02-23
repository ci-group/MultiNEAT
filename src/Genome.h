#ifndef _GENOME_H
#define _GENOME_H

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
//    but WITHOUT ANY WARRbbbbbbbbbbANTY; without even the implied warranty of
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

///////////////////////////////////////////////////////////////////////////////
// File:        Genome.h
// Description: Definition for the Genome class.
///////////////////////////////////////////////////////////////////////////////

#include <cereal/cereal.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/archives/json.hpp>

#include <vector>
#include <queue>

#include "NeuralNetwork.h"
#include "Substrate.h"
#include "Innovation.h"
#include "Genes.h"
#include "MultiNEATAssert.h"
#include "PhenotypeBehavior.h"
#include "Random.h"
#include "Utils.h"

namespace NEAT
{

    //////////////////////////////////////////////
    // The Genome class
    //////////////////////////////////////////////

    // forward
    class Innovation;

    class InnovationDatabase;

    class PhenotypeBehavior;

    extern ActivationFunction GetRandomActivation(Parameters &a_Parameters, RNG &a_RNG);

    class Genome
    {
        /////////////////////
        // Members
        /////////////////////
    private:

        // ID of genome
        unsigned int m_ID;

        // How many inputs/outputs
        unsigned int m_NumInputs;
        unsigned int m_NumOutputs;

        // The genome's fitness score
        double m_Fitness;

        // The genome's adjusted fitness score
        double m_AdjustedFitness;

        // The depth of the network
        unsigned int m_Depth;

        // recursion limit on network depth calculations
        unsigned int m_NeuronRecursionLimit;

        // how many individuals this genome should spawn
        double m_OffspringAmount;

        ////////////////////
        // Private methods

        // Returns true if the specified neuron ID is present in the genome
        bool HasNeuronID(int a_id) const;

        // Returns true if the specified link is present in the genome
        bool HasLink(int a_n1id, int a_n2id) const;

        // Returns true if the specified link is present in the genome
        bool HasLinkByInnovID(int a_id) const;

        // Removes the link with the specified innovation ID
        void RemoveLinkGene(int a_innovid);

        // Remove node
        // Links connected to this node are also removed
        void RemoveNeuronGene(int a_id);

        // Returns the count of links inputting from the specified neuron ID
        int LinksInputtingFrom(int a_id) const;

        // Returns the count of links outputting to the specified neuron ID
        int LinksOutputtingTo(int a_id) const;

        // A recursive function returning the max depth from the specified neuron to the inputs
        unsigned int NeuronDepth(int a_NeuronID, unsigned int a_Depth);

        // Returns true is the specified neuron ID is a dead end or isolated
        bool IsDeadEndNeuron(int a_id) const;

    public:

        // The two lists of genes
        std::vector<NeuronGene> m_NeuronGenes;
        std::vector<LinkGene> m_LinkGenes;

        // To have traits that belong to the genome itself
        Gene m_GenomeGene;

        // tells whether this genome was evaluated already
        // used in steady state evolution
        bool m_Evaluated;

        // the initial genome complexity
        unsigned int m_initial_num_neurons;
        unsigned int m_initial_num_links;

        // A pointer to a class representing the phenotype's behavior
        // Used in novelty searches
        PhenotypeBehavior *m_PhenotypeBehavior;
        // A Python object behavior
#ifdef PYTHON_BINDINGS
        pybind11::object m_behavior;
#endif

        ////////////////////////////
        // Constructors
        ////////////////////////////

        Genome();

        // copy constructor
        Genome(const Genome &a_g);

        // assignment operator
        Genome &operator=(const Genome &a_g);

        // comparison operator (nessesary for python bindings)
        // todo: implement a better comparison technique
        bool operator==(Genome const &other) const
        {
            return m_ID == other.m_ID;
        }

        // Builds this genome from a file
        Genome(const char *a_filename);

        // Builds this genome from an opened file
        Genome(std::ifstream &a_DataFile);

        // This creates a CTRNN fully-connected genome
        Genome(unsigned int a_ID, unsigned int a_NumInputs, unsigned int a_NumHidden, unsigned int a_NumOutputs,
               ActivationFunction a_OutputActType, ActivationFunction a_HiddenActType, const Parameters &a_Parameters);

        // This creates a standart minimal genome - perceptron-like structure
        Genome(unsigned int a_ID,
               unsigned int a_NumInputs,
               unsigned int a_NumHidden, // ignored for seed_type == 0, specifies number of hidden units if seed_type == 1
               unsigned int a_NumOutputs,
               bool a_FS_NEAT, ActivationFunction a_OutputActType,
               ActivationFunction a_HiddenActType,
               unsigned int a_SeedType,
               const Parameters &a_Parameters,
               unsigned int a_NumLayers);

        /////////////
        // Other possible constructors for different types of networks go here
        // TODO


        ////////////////////////////
        // Destructor
        ////////////////////////////

        ////////////////////////////
        // Methods
        ////////////////////////////

        ////////////////////
        // Accessor methods

        NeuronGene GetNeuronByID(int a_ID) const;

        NeuronGene GetNeuronByIndex(int a_idx) const;

        LinkGene GetLinkByInnovID(int a_ID) const;

        LinkGene GetLinkByIndex(int a_idx) const;

        // A little helper function to find the index of a neuron, given its ID
        int GetNeuronIndex(int a_id) const;

        // A little helper function to find the index of a link, given its innovation ID
        int GetLinkIndex(int a_innovid) const;

        unsigned int NumNeurons() const
        { return static_cast<unsigned int>(m_NeuronGenes.size()); }

        unsigned int NumLinks() const
        { return static_cast<unsigned int>(m_LinkGenes.size()); }

        unsigned int NumInputs() const
        { return m_NumInputs; }

        unsigned int NumOutputs() const
        { return m_NumOutputs; }

        void SetNeuronXY(unsigned int a_idx, int a_x, int a_y);

        void SetNeuronX(unsigned int a_idx, int a_x);

        void SetNeuronY(unsigned int a_idx, int a_y);

        double GetFitness() const;

        double GetAdjFitness() const;

        void SetFitness(double a_f);

        void SetAdjFitness(double a_af);

        unsigned int GetID() const;

        void SetID(unsigned int a_id);

        unsigned int GetDepth() const;

        void SetDepth(unsigned int a_d);

        unsigned int GetNeuronRecursionLimit() const;

        void SetNeuronRecursionLimit(unsigned int a_l);

        // Returns true if there is any dead end in the network
        bool HasDeadEnds() const;

        // Returns true if there is any looping path in the network
        bool HasLoops();

        bool FailsConstraints(const Parameters &a_Parameters)
        {
            if (HasDeadEnds() || (NumLinks() == 0))
            {
                return true; // no reason to continue
            }

            if ((HasLoops() && (a_Parameters.AllowLoops == false)))
            {
                return true;
            }

            // Custom constraints
            if (a_Parameters.CustomConstraints != NULL)
            {
                if (a_Parameters.CustomConstraints(*this))
                {
                    return true;
                }
            }

            // for Python-based custom constraint callbacks
#ifdef PYTHON_BINDINGS
            if (a_Parameters.pyCustomConstraints.ptr() != pybind11::object().ptr()) // is it not None?
            {
                return a_Parameters.pyCustomConstraints(*this).cast<bool>();
            }
#endif
            // add more constraints here
            return false;
        }

        double GetOffspringAmount() const;

        void SetOffspringAmount(double a_oa);

        // This builds a fastnetwork structure out from the genome
        void BuildPhenotype(NeuralNetwork &net) const;

        // Projects the phenotype's weights back to the genome
        void DerivePhenotypicChanges(NeuralNetwork &a_Net);

        ////////////
        // Other possible methods for building a phenotype go here
        // Like CPPN/HyperNEAT stuff
        ////////////
        void BuildHyperNEATPhenotype(NeuralNetwork &net, Substrate &subst, RNG& rng);

#ifdef PYTHON_BINDINGS

        pybind11::dict TraitMap2Dict(const std::map< std::string, Trait>& tmap) const;

        pybind11::object GetNeuronTraits() const;

        pybind11::object GetLinkTraits(bool with_weights=false) const;

        pybind11::dict GetGenomeTraits()
        {
            return TraitMap2Dict(m_GenomeGene.m_Traits);
        }

#endif

        // Saves this genome to a file
        void Save(const char *a_filename);

        // Saves this genome to an already opened file for writing
        void Save(FILE *a_fstream) const;

        void PrintTraits(const std::map< std::string, Trait>& traits) const;
        void PrintAllTraits() const;

        // returns the max neuron ID
        int GetLastNeuronID() const;

        // returns the max innovation Id
        int GetLastInnovationID() const;

        // Sorts the genes of the genome
        // The neurons by IDs and the links by innovation numbers.
        void SortGenes();

        // overload '<' used for sorting. From fittest to poorest.
        friend bool operator<(const Genome &a_lhs, const Genome &a_rhs)
        {
            return (a_lhs.m_Fitness > a_rhs.m_Fitness);
        }

        // Returns true if this genome and a_G are compatible (belong in the same species)
        bool IsCompatibleWith(const Genome &a_G, const Parameters &a_Parameters) const;

        // returns the absolute compatibility distance between this genome and a_G
        double CompatibilityDistance(const Genome &a_G, const Parameters &a_Parameters) const;

        // Calculates the network depth
        void CalculateDepth();

        ////////////
        // Mutation
        ////////////

        void Mutate(bool t_baby_is_clone, const SearchMode a_searchMode, InnovationDatabase &a_innov_database, const Parameters &a_Parameters, RNG &a_RNG);

        // Adds a new neuron to the genome
        // returns true if succesful
        bool Mutate_AddNeuron(InnovationDatabase &a_Innovs, const Parameters &a_Parameters, RNG &a_RNG);

        // Adds a new link to the genome
        // returns true if succesful
        bool Mutate_AddLink(InnovationDatabase &a_Innovs, const Parameters &a_Parameters, RNG &a_RNG);

        // Remove a random link from the genome
        // A cleanup procedure is invoked so any dead-ends or stranded neurons are also deleted
        // returns true if succesful
        bool Mutate_RemoveLink(RNG &a_RNG);

        // Removes a hidden neuron having only one input and only one output with
        // a direct link between them.
        bool Mutate_RemoveSimpleNeuron(InnovationDatabase &a_Innovs, RNG &a_RNG);

        // Perturbs the weights
        bool Mutate_LinkWeights(const Parameters &a_Parameters, RNG &a_RNG);

        // Set all link weights to random values between [-R .. R]
        void Randomize_LinkWeights(double a_Range, RNG &a_RNG);

        // Set all traits to random values
        void Randomize_Traits(const Parameters& a_Parameters, RNG &a_RNG);

        // Perturbs the A parameters of the neuron activation functions
        bool Mutate_NeuronActivations_A(const Parameters &a_Parameters, RNG &a_RNG);

        // Perturbs the B parameters of the neuron activation functions
        bool Mutate_NeuronActivations_B(const Parameters &a_Parameters, RNG &a_RNG);

        // Changes the activation function type for a random neuron
        bool Mutate_NeuronActivation_Type(const Parameters &a_Parameters, RNG &a_RNG);

        // Perturbs the neuron time constants
        bool Mutate_NeuronTimeConstants(const Parameters &a_Parameters, RNG &a_RNG);

        // Perturbs the neuron biases
        bool Mutate_NeuronBiases(const Parameters &a_Parameters, RNG &a_RNG);

        // Perturbs the neuron traits
        bool Mutate_NeuronTraits(const Parameters &a_Parameters, RNG &a_RNG);

        // Perturbs the link traits
        bool Mutate_LinkTraits(const Parameters &a_Parameters, RNG &a_RNG);

        // Perturbs the genome traits
        bool Mutate_GenomeTraits(const Parameters &a_Parameters, RNG &a_RNG);

        ///////////
        // Mating
        ///////////


        // Mate this genome with dad and return the baby
        // If this is multipoint mating, genes are inherited randomly
        // If the a_averagemating bool is true, then the genes are averaged
        // Disjoint and excess genes are inherited from the fittest parent
        // If fitness is equal, the smaller genome is assumed to be the better one
        Genome Mate(Genome &a_dad, bool a_averagemating, bool a_interspecies, RNG &a_RNG, Parameters &a_Parameters);


        //////////
        // Utility
        //////////

        // Search the genome for isolated structure and clean it up
        // Returns true is something was removed
        bool Cleanup();

        ////////////////////
        // new stuff
        bool IsEvaluated() const;

        void SetEvaluated();

        void ResetEvaluated();


        /////////////////////////////////////////////
        // Evolvable Substrate HyperNEAT
        ////////////////////////////////////////////

        // A connection between two points. Stores weight and the coordinates of the points
        struct TempConnection
        {
            std::vector<double> source;
            std::vector<double> target;
            double weight;

            TempConnection()
            {
                source.reserve(3);
                target.reserve(3);
                weight = 0;
            }

            TempConnection(std::vector<double> t_source, std::vector<double> t_target,
                           double t_weight)
            {
                source = t_source;
                target = t_target;
                weight = t_weight;
                source.reserve(3);
                target.reserve(3);
            }

            TempConnection(std::vector<double> t_source, std::vector<double> t_target, double t_weight, unsigned int coord_size)
            {
                source = t_source;
                target = t_target;
                weight = t_weight;
            }

            ~TempConnection()
            {};

            bool operator==(const TempConnection &rhs) const
            {
                return (source == rhs.source && target == rhs.target);
            }

            bool operator!=(const TempConnection &rhs) const
            {
                return (source != rhs.source && target != rhs.target);
            }
        };

        // A quadpoint in the HyperCube.
        struct QuadPoint
        {
            double x;
            double y;
            double z;
            double width;
            double weight;
            double height;
            double variance;
            int level;
            // Do I use this?
            double leo;


            std::vector<std::shared_ptr<QuadPoint> > children;

            QuadPoint()
            {
                x = y = z = width = height = weight = variance = leo = 0;
                level = 0;
                children.reserve(4);
            }

            QuadPoint(double t_x, double t_y, double t_width, double t_height, int t_level)
            {
                x = t_x;
                y = t_y;
                z = 0.0;
                width = t_width;
                height = t_height;
                level = t_level;
                weight = 0.0;
                leo = 0.0;
                variance = 0.0;
                children.reserve(4);
                children.clear();
            }

            // Mind the Z
            QuadPoint(double t_x, double t_y, double t_z, double t_width, double t_height,
                      int t_level)
            {
                x = t_x;
                y = t_y;
                z = t_z;
                width = t_width;
                height = t_height;
                level = t_level;
                weight = 0.0;
                variance = 0.0;
                leo = 0.0;
                children.reserve(4);
                children.clear();
            }

            ~QuadPoint()
            {
            };
        };


        struct nTree
        {
            std::vector<double> coord;
            double weight;
            double varience;
            int lvl;
            double width;
            double leo = 0.0;
            std::vector<std::shared_ptr<nTree> > children;

            nTree(std::vector<double> coord_in, double wdth, double level)
            {
                width = wdth;
                lvl = level;
                coord = coord_in;
            };

        public: void set_children()
            {
                unsigned int ix_max = std::pow(2, coord.size());
                for(unsigned int ix = 0; ix < ix_max; ix++){
                    std::string sum_permute = toBinary(ix, coord.size());
                    std::vector<double> child_coords;
                    unsigned int child_param_len = sum_permute.length();
                    child_coords.reserve(child_param_len);
                    for(unsigned int sign_ix = 0; sign_ix < child_param_len; sign_ix++)
                    {
                        if(sum_permute[sign_ix] == '0')
                        {
                            child_coords.push_back(coord[sign_ix] + width/2.0);
                        }
                        else
                        {
                            child_coords.push_back(coord[sign_ix] - width/2.0);
                        }
                        children.push_back(
                            std::make_shared<nTree>(child_coords, width/2.0, lvl+1)
                        );
                    }
                }
            }

            std::string toBinary(unsigned int n, unsigned int min_len)
            {
                std::string r;
                while(n!=0)
                {
                    r=(n%2==0 ?"0":"1")+r; n/=2;

                }
                if(r.length() < min_len)
                {
                    int diff = min_len - r.length();
                    for(int x = 0; x < diff; x++)
                    {
                        r = '0' +r;
                    }
                }
                return r;
            }
        };

        void BuildESHyperNEATPhenotype(NeuralNetwork &a_net, Substrate &subst, Parameters &params, RNG& rng);

        void DivideInitialize(const std::vector<double> &node,
                              std::shared_ptr<QuadPoint> &root,
                              NeuralNetwork &cppn, Parameters &params,
                              const bool &outgoing, const double &z_coord);

        void PruneExpress(const std::vector<double> &node,
                          std::shared_ptr<QuadPoint> &root, NeuralNetwork &cppn,
                          Parameters &params, std::vector<Genome::TempConnection> &connections,
                          const bool &outgoing);

        void CollectValues(std::vector<double> &vals, std::shared_ptr<QuadPoint> &point);

        double Variance(std::shared_ptr<QuadPoint> &point);

        void Clean_Net(std::vector<Connection> &connections, unsigned int input_count,
                       unsigned int output_count, unsigned int hidden_count);

        // Serialization
        template<class Archive>
        void serialize(Archive & ar)
        {
            ar & m_ID;
            ar & m_NeuronGenes;
            ar & m_LinkGenes;
            ar & m_NumInputs;
            ar & m_NumOutputs;
            ar & m_Fitness;
            ar & m_AdjustedFitness;
            ar & m_Depth;
            ar & m_OffspringAmount;
            ar & m_Evaluated;
            //ar & m_PhenotypeBehavior; // todo: think about how we will handle the behaviors with pickle
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

#ifdef PYTHON_BINDINGS
        static std::string pickle_getstate(const Genome& a)
        {
            return a.Serialize();
        }

        static Genome pickle_setstate(std::string a)
        {
            Genome genome;
            genome.Deserialize(a);
            return genome;
        }
#endif

    };

} // namespace NEAT

#endif
