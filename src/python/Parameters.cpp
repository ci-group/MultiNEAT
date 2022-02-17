//
// Created by matteo on 6/7/20.
// Edited by aart in 2022
//

#include "../Parameters.h"
#include <pybind11/pybind11.h>

using namespace NEAT;

void (Parameters::*Parameters_Save)(const char*) = &Parameters::Save;
int (Parameters::*Parameters_Load)(const char*) = &Parameters::Load;

void export_Parameters(pybind11::module_& mod) {
    pybind11::class_<Parameters>(mod, "Parameters")
        .def(pybind11::init<>())
        .def("Reset", &Parameters::Reset)
        .def("Load", Parameters_Load)
        .def("Save", Parameters_Save)
        .def("ListNeuronTraitParameters", &Parameters::ListNeuronTraitParameters)
        .def("ListLinkTraitParameters", &Parameters::ListLinkTraitParameters)
        .def("ListGenomeTraitParameters", &Parameters::ListGenomeTraitParameters)
        .def("SetNeuronTraitParameters", &Parameters::SetNeuronTraitParameters)
        .def("SetLinkTraitParameters", &Parameters::SetLinkTraitParameters)
        .def("SetGenomeTraitParameters", &Parameters::SetGenomeTraitParameters)
        .def("GetNeuronTraitParameters", &Parameters::GetNeuronTraitParameters)
        .def("GetLinkTraitParameters", &Parameters::GetLinkTraitParameters)
        .def("GetGenomeTraitParameters", &Parameters::GetGenomeTraitParameters)
        .def("ClearNeuronTraitParameters", &Parameters::ClearNeuronTraitParameters)
        .def("ClearLinkTraitParameters", &Parameters::ClearLinkTraitParameters)
        .def("ClearGenomeTraitParameters", &Parameters::ClearGenomeTraitParameters)

        .def_readwrite("PopulationSize", &Parameters::PopulationSize)
        .def_readwrite("DynamicCompatibility", &Parameters::DynamicCompatibility)
        .def_readwrite("MinSpecies", &Parameters::MinSpecies)
        .def_readwrite("MaxSpecies", &Parameters::MaxSpecies)
        .def_readwrite("InnovationsForever", &Parameters::InnovationsForever)
        .def_readwrite("AllowClones", &Parameters::AllowClones)
        .def_readwrite("ArchiveEnforcement", &Parameters::ArchiveEnforcement)
        .def_readwrite("NormalizeGenomeSize", &Parameters::NormalizeGenomeSize)
        .def_readwrite("CustomConstraints", &Parameters::pyCustomConstraints)
        .def_readwrite("YoungAgeTreshold", &Parameters::YoungAgeTreshold)
        .def_readwrite("YoungAgeFitnessBoost", &Parameters::YoungAgeFitnessBoost)
        .def_readwrite("SpeciesDropoffAge", &Parameters::SpeciesMaxStagnation)
        .def_readwrite("StagnationDelta", &Parameters::StagnationDelta)
        .def_readwrite("OldAgeTreshold", &Parameters::OldAgeTreshold)
        .def_readwrite("OldAgePenalty", &Parameters::OldAgePenalty)
        .def_readwrite("DetectCompetetiveCoevolutionStagnation", &Parameters::DetectCompetetiveCoevolutionStagnation)
        .def_readwrite("KillWorstSpeciesEach", &Parameters::KillWorstSpeciesEach)
        .def_readwrite("KillWorstAge", &Parameters::KillWorstAge)
        .def_readwrite("SurvivalRate", &Parameters::SurvivalRate)
        .def_readwrite("CrossoverRate", &Parameters::CrossoverRate)
        .def_readwrite("OverallMutationRate", &Parameters::OverallMutationRate)
        .def_readwrite("InterspeciesCrossoverRate", &Parameters::InterspeciesCrossoverRate)
        .def_readwrite("MultipointCrossoverRate", &Parameters::MultipointCrossoverRate)
        .def_readwrite("RouletteWheelSelection", &Parameters::RouletteWheelSelection)
        .def_readwrite("PhasedSearching", &Parameters::PhasedSearching)
        .def_readwrite("DeltaCoding", &Parameters::DeltaCoding)
        .def_readwrite("SimplifyingPhaseMPCTreshold", &Parameters::SimplifyingPhaseMPCTreshold)
        .def_readwrite("SimplifyingPhaseStagnationTreshold", &Parameters::SimplifyingPhaseStagnationTreshold)
        .def_readwrite("ComplexityFloorGenerations", &Parameters::ComplexityFloorGenerations)
        .def_readwrite("NoveltySearch_K", &Parameters::NoveltySearch_K)
        .def_readwrite("NoveltySearch_P_min", &Parameters::NoveltySearch_P_min)
        .def_readwrite("NoveltySearch_Dynamic_Pmin", &Parameters::NoveltySearch_Dynamic_Pmin)
        .def_readwrite("NoveltySearch_No_Archiving_Stagnation_Treshold", &Parameters::NoveltySearch_No_Archiving_Stagnation_Treshold)
        .def_readwrite("NoveltySearch_Pmin_lowering_multiplier", &Parameters::NoveltySearch_Pmin_lowering_multiplier)
        .def_readwrite("NoveltySearch_Pmin_min", &Parameters::NoveltySearch_Pmin_min)
        .def_readwrite("NoveltySearch_Quick_Archiving_Min_Evaluations", &Parameters::NoveltySearch_Quick_Archiving_Min_Evaluations)
        .def_readwrite("NoveltySearch_Pmin_raising_multiplier", &Parameters::NoveltySearch_Pmin_raising_multiplier)
        .def_readwrite("NoveltySearch_Recompute_Sparseness_Each", &Parameters::NoveltySearch_Recompute_Sparseness_Each)
        .def_readwrite("MutateAddNeuronProb", &Parameters::MutateAddNeuronProb)
        .def_readwrite("SplitRecurrent", &Parameters::SplitRecurrent)
        .def_readwrite("SplitLoopedRecurrent", &Parameters::SplitLoopedRecurrent)
        .def_readwrite("MutateAddLinkProb", &Parameters::MutateAddLinkProb)
        .def_readwrite("MutateAddLinkFromBiasProb", &Parameters::MutateAddLinkFromBiasProb)
        .def_readwrite("MutateRemLinkProb", &Parameters::MutateRemLinkProb)
        .def_readwrite("MutateRemSimpleNeuronProb", &Parameters::MutateRemSimpleNeuronProb)
        .def_readwrite("LinkTries", &Parameters::LinkTries)
        .def_readwrite("RecurrentProb", &Parameters::RecurrentProb)
        .def_readwrite("RecurrentLoopProb", &Parameters::RecurrentLoopProb)
        .def_readwrite("MutateWeightsProb", &Parameters::MutateWeightsProb)
        .def_readwrite("MutateWeightsSevereProb", &Parameters::MutateWeightsSevereProb)
        .def_readwrite("WeightMutationRate", &Parameters::WeightMutationRate)
        .def_readwrite("WeightMutationMaxPower", &Parameters::WeightMutationMaxPower)
        .def_readwrite("WeightReplacementRate", &Parameters::WeightReplacementRate)
        .def_readwrite("WeightReplacementMaxPower", &Parameters::WeightReplacementMaxPower)
        .def_readwrite("MaxWeight", &Parameters::MaxWeight)
        .def_readwrite("MutateActivationAProb", &Parameters::MutateActivationAProb)
        .def_readwrite("MutateActivationBProb", &Parameters::MutateActivationBProb)
        .def_readwrite("ActivationAMutationMaxPower", &Parameters::ActivationAMutationMaxPower)
        .def_readwrite("ActivationBMutationMaxPower", &Parameters::ActivationBMutationMaxPower)
        .def_readwrite("MinActivationA", &Parameters::MinActivationA)
        .def_readwrite("MaxActivationA", &Parameters::MaxActivationA)
        .def_readwrite("MinActivationB", &Parameters::MinActivationB)
        .def_readwrite("MaxActivationB", &Parameters::MaxActivationB)
        .def_readwrite("TimeConstantMutationMaxPower", &Parameters::TimeConstantMutationMaxPower)
        .def_readwrite("BiasMutationMaxPower", &Parameters::BiasMutationMaxPower)
        .def_readwrite("MutateNeuronTimeConstantsProb", &Parameters::MutateNeuronTimeConstantsProb)
        .def_readwrite("MutateNeuronBiasesProb", &Parameters::MutateNeuronBiasesProb)
        .def_readwrite("MinNeuronTimeConstant", &Parameters::MinNeuronTimeConstant)
        .def_readwrite("MaxNeuronTimeConstant", &Parameters::MaxNeuronTimeConstant)
        .def_readwrite("MinNeuronBias", &Parameters::MinNeuronBias)
        .def_readwrite("MaxNeuronBias", &Parameters::MaxNeuronBias)
        .def_readwrite("MutateNeuronActivationTypeProb", &Parameters::MutateNeuronActivationTypeProb)
        .def_readwrite("MutateOutputActivationFunction", &Parameters::MutateOutputActivationFunction)
        .def_readwrite("ActivationFunction_SignedSigmoid_Prob", &Parameters::ActivationFunction_SignedSigmoid_Prob)
        .def_readwrite("ActivationFunction_UnsignedSigmoid_Prob", &Parameters::ActivationFunction_UnsignedSigmoid_Prob)
        .def_readwrite("ActivationFunction_Tanh_Prob", &Parameters::ActivationFunction_Tanh_Prob)
        .def_readwrite("ActivationFunction_TanhCubic_Prob", &Parameters::ActivationFunction_TanhCubic_Prob)
        .def_readwrite("ActivationFunction_SignedStep_Prob", &Parameters::ActivationFunction_SignedStep_Prob)
        .def_readwrite("ActivationFunction_UnsignedStep_Prob", &Parameters::ActivationFunction_UnsignedStep_Prob)
        .def_readwrite("ActivationFunction_SignedGauss_Prob", &Parameters::ActivationFunction_SignedGauss_Prob)
        .def_readwrite("ActivationFunction_UnsignedGauss_Prob", &Parameters::ActivationFunction_UnsignedGauss_Prob)
        .def_readwrite("ActivationFunction_Abs_Prob", &Parameters::ActivationFunction_Abs_Prob)
        .def_readwrite("ActivationFunction_SignedSine_Prob", &Parameters::ActivationFunction_SignedSine_Prob)
        .def_readwrite("ActivationFunction_UnsignedSine_Prob", &Parameters::ActivationFunction_UnsignedSine_Prob)
        .def_readwrite("ActivationFunction_Linear_Prob", &Parameters::ActivationFunction_Linear_Prob)
        .def_readwrite("DontUseBiasNeuron", &Parameters::DontUseBiasNeuron)
        .def_readwrite("AllowLoops", &Parameters::AllowLoops)
        .def_readwrite("MutateNeuronTraitsProb", &Parameters::MutateNeuronTraitsProb)
        .def_readwrite("MutateLinkTraitsProb", &Parameters::MutateLinkTraitsProb)
        .def_readwrite("DisjointCoeff", &Parameters::DisjointCoeff)
        .def_readwrite("ExcessCoeff", &Parameters::ExcessCoeff)
        .def_readwrite("WeightDiffCoeff", &Parameters::WeightDiffCoeff)
        .def_readwrite("ActivationADiffCoeff", &Parameters::ActivationADiffCoeff)
        .def_readwrite("ActivationBDiffCoeff", &Parameters::ActivationBDiffCoeff)
        .def_readwrite("TimeConstantDiffCoeff", &Parameters::TimeConstantDiffCoeff)
        .def_readwrite("BiasDiffCoeff", &Parameters::BiasDiffCoeff)
        .def_readwrite("ActivationFunctionDiffCoeff", &Parameters::ActivationFunctionDiffCoeff)
        .def_readwrite("CompatTreshold", &Parameters::CompatTreshold)
        .def_readwrite("MinCompatTreshold", &Parameters::MinCompatTreshold)
        .def_readwrite("CompatTresholdModifier", &Parameters::CompatTresholdModifier)
        .def_readwrite("CompatTreshChangeInterval_Generations", &Parameters::CompatTreshChangeInterval_Generations)
        .def_readwrite("CompatTreshChangeInterval_Evaluations", &Parameters::CompatTreshChangeInterval_Evaluations)

        .def_readwrite("DivisionThreshold", &Parameters::DivisionThreshold)
        .def_readwrite("VarianceThreshold", &Parameters::VarianceThreshold)
        .def_readwrite("BandThreshold", &Parameters::BandThreshold)
        .def_readwrite("InitialDepth", &Parameters::InitialDepth)
        .def_readwrite("MaxDepth", &Parameters::MaxDepth)
        .def_readwrite("CPPN_Bias", &Parameters::CPPN_Bias)
        .def_readwrite("Width", &Parameters::Width)
        .def_readwrite("Height", &Parameters::Height)
        .def_readwrite("Qtree_Y", &Parameters::Qtree_Y)
        .def_readwrite("Qtree_X", &Parameters::Qtree_X)
        .def_readwrite("Leo", &Parameters::Leo)
        .def_readwrite("LeoThreshold", &Parameters::LeoThreshold)
        .def_readwrite("LeoSeed", &Parameters::LeoSeed)

        .def_readwrite("GeometrySeed", &Parameters::GeometrySeed)
        .def_readwrite("TournamentSize", &Parameters::TournamentSize)
        .def_readwrite("EliteFraction", &Parameters::EliteFraction)
        .def_readwrite("NeuronRecursionLimit", &Parameters::NeuronRecursionLimit)
        .def(pybind11::pickle(&Parameters::pickle_getstate, &Parameters::pickle_setstate))
        ;
}
