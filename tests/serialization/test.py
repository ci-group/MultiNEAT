#!/usr/bin/env python
import unittest
import multineat
import subprocess
import pickle
import os


def parse_bool(text: str):
    if text.upper() == 'TRUE':
        return True
    elif text.upper() == 'FALSE':
        return False
    else:
        raise RuntimeError("cannot parse boolean")


class TestSerialization(unittest.TestCase):

    @staticmethod
    def parameters():
        params = multineat.Parameters()
        params.PopulationSize = 100
        params.DynamicCompatibility = True
        params.NormalizeGenomeSize = True
        params.WeightDiffCoeff = 0.1
        params.CompatTreshold = 2.0
        params.YoungAgeTreshold = 15
        params.SpeciesDropoffAge = 15
        params.OldAgeTreshold = 35
        params.MinSpecies = 2
        params.MaxSpecies = 10
        params.RouletteWheelSelection = False
        params.RecurrentProb = 0.0
        params.OverallMutationRate = 1.0

        params.ArchiveEnforcement = False

        params.MutateWeightsProb = 0.05

        params.WeightMutationMaxPower = 0.5
        params.WeightReplacementMaxPower = 8.0
        params.MutateWeightsSevereProb = 0.0
        params.WeightMutationRate = 0.25
        params.WeightReplacementRate = 0.9

        params.MaxWeight = 8

        params.MutateAddNeuronProb = 0.001
        params.MutateAddLinkProb = 0.3
        params.MutateRemLinkProb = 0.0

        params.MinActivationA = 4.9
        params.MaxActivationA = 4.9

        params.ActivationFunction_SignedSigmoid_Prob = 0.0
        params.ActivationFunction_UnsignedSigmoid_Prob = 1.0
        params.ActivationFunction_Tanh_Prob = 0.0
        params.ActivationFunction_SignedStep_Prob = 0.0

        params.CrossoverRate = 0.0
        params.MultipointCrossoverRate = 0.0
        params.SurvivalRate = 0.2

        params.MutateNeuronTraitsProb = 0
        params.MutateLinkTraitsProb = 0

        params.AllowLoops = True
        params.AllowClones = True

        params.ClearNeuronTraitParameters()
        params.ClearLinkTraitParameters()
        params.ClearGenomeTraitParameters()

        return params

    def setUp(self):
        self._params = self.parameters()
        self._net = multineat.NeuralNetwork()
        self._rng = multineat.RNG()
        self._rng.Seed(0)
        self._innov_db = multineat.InnovationDatabase()
        self.g = multineat.Genome(42, 3, 7, 1, False,
                                  multineat.ActivationFunction.UNSIGNED_SIGMOID,
                                  multineat.ActivationFunction.UNSIGNED_SIGMOID,
                                  0, self._params, 0)
        for i in range(100):
            self.g.Mutate(False, multineat.SearchMode.COMPLEXIFYING, self._innov_db, self._params, self._rng)

    # def tearDown(self):
    #     pass

    def test_basics(self):
        self.assertEqual(self.g.IsEvaluated(), False)

    def test_pickle(self):
        str_genome = pickle.dumps(self.g)
        cloned = pickle.loads(str_genome)

        self.assertEqual(self.g.GetID(), cloned.GetID())
        self.assertEqual(self.g.NumInputs(), cloned.NumInputs())
        self.assertEqual(self.g.NumOutputs(), cloned.NumOutputs())
        self.assertEqual(self.g.GetFitness(), cloned.GetFitness())
        self.assertEqual(self.g.GetAdjFitness(), cloned.GetAdjFitness())
        self.assertEqual(self.g.GetDepth(), cloned.GetDepth())
        self.assertEqual(self.g.IsEvaluated(), cloned.IsEvaluated())

        for i, n_gene in enumerate(self.g.NeuronGenes):
            self.assertEqual(n_gene.A, cloned.NeuronGenes[i].A)
            self.assertEqual(n_gene.B, cloned.NeuronGenes[i].B)
            self.assertEqual(n_gene.TimeConstant, cloned.NeuronGenes[i].TimeConstant)
            self.assertEqual(n_gene.Bias, cloned.NeuronGenes[i].Bias)
            self.assertEqual(n_gene.ActFunction, cloned.NeuronGenes[i].ActFunction)
            self.assertEqual(n_gene.Type, cloned.NeuronGenes[i].Type)

        for i, l_gene in enumerate(self.g.LinkGenes):
            self.assertEqual(l_gene.FromNeuronID, cloned.LinkGenes[i].FromNeuronID)
            self.assertEqual(l_gene.ToNeuronID, cloned.LinkGenes[i].ToNeuronID)
            self.assertEqual(l_gene.InnovationID, cloned.LinkGenes[i].InnovationID)
            self.assertEqual(l_gene.Weight, cloned.LinkGenes[i].Weight)

    def test_serialize_deserialize(self):
        str_genome = self.g.Serialize()
        cloned = multineat.Genome()
        cloned.Deserialize(str_genome)

        self.assertEqual(self.g.GetID(), cloned.GetID())
        self.assertEqual(self.g.NumInputs(), cloned.NumInputs())
        self.assertEqual(self.g.NumOutputs(), cloned.NumOutputs())
        self.assertEqual(self.g.GetFitness(), cloned.GetFitness())
        self.assertEqual(self.g.GetAdjFitness(), cloned.GetAdjFitness())
        self.assertEqual(self.g.GetDepth(), cloned.GetDepth())
        self.assertEqual(self.g.IsEvaluated(), cloned.IsEvaluated())

        for i, n_gene in enumerate(self.g.NeuronGenes):
            self.assertEqual(n_gene.A, cloned.NeuronGenes[i].A)
            self.assertEqual(n_gene.B, cloned.NeuronGenes[i].B)
            self.assertEqual(n_gene.TimeConstant, cloned.NeuronGenes[i].TimeConstant)
            self.assertEqual(n_gene.Bias, cloned.NeuronGenes[i].Bias)
            self.assertEqual(n_gene.ActFunction, cloned.NeuronGenes[i].ActFunction)
            self.assertEqual(n_gene.Type, cloned.NeuronGenes[i].Type)

        for i, l_gene in enumerate(self.g.LinkGenes):
            self.assertEqual(l_gene.FromNeuronID, cloned.LinkGenes[i].FromNeuronID)
            self.assertEqual(l_gene.ToNeuronID, cloned.LinkGenes[i].ToNeuronID)
            self.assertEqual(l_gene.InnovationID, cloned.LinkGenes[i].InnovationID)
            self.assertEqual(l_gene.Weight, cloned.LinkGenes[i].Weight)

    def test_python_to_cpp(self):
        base = os.environ.get('CMAKE_CURRENT_BINARY_DIR',
                              default=os.path.join('..', '..', 'build', 'tests', 'serialization'))
        cpp_test_exe = os.path.join(base, 'analize_genome_file')
        test_file = os.path.join(base, 'test_genome.txt')

        serialized_genome = self.g.Serialize()
        with open(test_file, 'w') as pickle_file:
            pickle_file.write(serialized_genome)
        p = subprocess.run([cpp_test_exe, test_file], capture_output=True)
        data = []
        for i, line in enumerate(p.stdout.decode().split('\n')):
            data.append(line)
            # print(f'{i}:\t{line}')

        i = 0
        self.assertEqual(self.g.GetID(), int(data[0]))
        self.assertEqual(self.g.NumInputs(), int(data[1]))
        self.assertEqual(self.g.NumOutputs(), int(data[2]))
        self.assertEqual(self.g.GetFitness(), float(data[3]))
        self.assertEqual(self.g.GetAdjFitness(), float(data[4]))
        self.assertEqual(self.g.GetDepth(), int(data[5]))
        # self.assertEqual(self.g.GetOffspringAmount(), int(data[6]))
        self.assertEqual(self.g.IsEvaluated(), parse_bool(data[7]))

        n_link_genes = int(data[8])
        i += 9
        self.assertEqual(len(self.g.LinkGenes), n_link_genes)
        for l_gene in self.g.LinkGenes:
            # print(f'link gene {i}')
            self.assertEqual(l_gene.InnovationID, int(data[i + 0]))
            self.assertEqual(l_gene.FromNeuronID, int(data[i + 1]))
            self.assertEqual(l_gene.ToNeuronID, int(data[i + 2]))
            self.assertEqual(l_gene.IsRecurrent, parse_bool(data[i + 3]))
            self.assertAlmostEqual(l_gene.Weight, float(data[i + 4]), places=5)
            # self.assertEqual(l_gene.m_Traits, parse_bool(data[i + 5]))
            i += 5

        n_neuron_genes = int(data[i])
        i += 1
        self.assertEqual(len(self.g.NeuronGenes), n_neuron_genes)
        for n_gene in self.g.NeuronGenes:
            # print(f'neuron gene {i}')
            self.assertEqual(n_gene.ID, int(data[i + 0]))
            self.assertEqual(n_gene.Type, multineat.NeuronType(int(data[i + 1])))
            self.assertEqual(n_gene.A, float(data[i + 2]))
            self.assertEqual(n_gene.B, float(data[i + 3]))
            self.assertEqual(n_gene.TimeConstant, float(data[i + 4]))
            self.assertEqual(n_gene.Bias, float(data[i + 5]))
            self.assertEqual(n_gene.x, int(data[i + 6]))
            self.assertEqual(n_gene.y, int(data[i + 7]))
            self.assertEqual(n_gene.ActFunction, multineat.ActivationFunction(int(data[i + 8])))
            self.assertEqual(n_gene.SplitY, float(data[i + 9]))
            i += 10


if __name__ == '__main__':
    unittest.main()
