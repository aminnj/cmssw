import FWCore.ParameterSet.Config as cms
from RecoJets.JetProducers.PileupJetIDCutParams_cfi import *

####################################################################################################################                                                                                      
full_74x_chs = cms.PSet(
 impactParTkThreshold = cms.double(1.) ,
 cutBased = cms.bool(False),
 etaBinnedWeights = cms.bool(True),
 tmvaWeights_jteta_0_2 = cms.string("RecoJets/JetProducers/data/TMVAClassificationCategory_BDTG.weights_jteta_0_2.xml.gz"),
 tmvaWeights_jteta_2_2p5 = cms.string("RecoJets/JetProducers/data/TMVAClassificationCategory_BDTG.weights_jteta_2_2p5.xml.gz"),
 tmvaWeights_jteta_2p5_3 = cms.string("RecoJets/JetProducers/data/TMVAClassificationCategory_BDTG.weights_jteta_2p5_3.xml.gz"),
 tmvaWeights_jteta_3_5 = cms.string("RecoJets/JetProducers/data/TMVAClassificationCategory_BDTG.weights_jteta_3_5.xml.gz"),
 tmvaMethod  = cms.string("JetIDMVAHighPt"),
 version = cms.int32(-1),
 tmvaVariables_jteta_0_3 = cms.vstring(
    "DRweighted"     ,
    "rho"       ,
    "nTot"     ,
    "nCh" ,
    "axisMajor" ,
    "axisMinor",
    "fRing0"  ,
    "fRing1"      ,
    "fRing2"   ,
    "fRing3"   ,
    "ptD"   ,
    "beta"   ,
    "betaStar"   ,
    "min(pull,0.1)"   ,
    "jetR"   ,
    "jetRchg"   ,
    ),
 tmvaVariables_jteta_3_5 = cms.vstring(
    "DRweighted"     ,
    "rho"       ,
    "nTot"     ,
    "axisMajor" ,
    "axisMinor",
    "fRing0"  ,
    "fRing1"      ,
    "fRing2"   ,
    "fRing3"   ,
    "ptD"   ,
    "min(pull,0.1)"   ,
    "jetR"   ,
    ),
 tmvaSpectators = cms.vstring(
    "p4.fCoordinates.fPt"   ,
    "p4.fCoordinates.fEta"   ,
    "nTrueInt"   ,
    "dRMatch"   ,
    ),
 JetIdParams = full_74x_chs_wp,
 label = cms.string("full")
 )
####################################################################################################################  
full_5x = cms.PSet(
 impactParTkThreshold = cms.double(1.) ,
 cutBased = cms.bool(False),
 etaBinnedWeights = cms.bool(False),
 tmvaWeights = cms.string("RecoJets/JetProducers/data/TMVAClassificationCategory_JetID_MET_53X_Dec2012.weights.xml.gz"),
 tmvaMethod  = cms.string("BDT_fullPlusRMS"),
 version = cms.int32(-1),
 tmvaVariables = cms.vstring(
    "frac01",
    "frac02",
    "frac03",
    "frac04",
    "frac05",
    "dR2Mean",
    "nvtx",
    "nNeutrals",
    "beta",
    "betaStar",
    "dZ",
    "nCharged",
    ),
 tmvaSpectators = cms.vstring(
    "jetPt",
    "jetEta",
    ),
 JetIdParams = full_5x_wp,
 label = cms.string("full")
 )


####################################################################################################################  
full_5x_chs = cms.PSet(
 impactParTkThreshold = cms.double(1.) ,
 cutBased = cms.bool(False),
 etaBinnedWeights = cms.bool(False),
 tmvaWeights = cms.string("RecoJets/JetProducers/data/TMVAClassification_5x_BDT_chsFullPlusRMS.weights.xml.gz"),
 tmvaMethod  = cms.string("BDT_chsFullPlusRMS"),
 version = cms.int32(-1),
 tmvaVariables = cms.vstring(
    "frac01",
    "frac02",
    "frac03",
    "frac04",
    "frac05",
    "dR2Mean",
    "nvtx",
    "nNeutrals",
    "beta",
    "betaStar",
    "dZ",
    "nCharged",
    ),
 tmvaSpectators = cms.vstring(
    "jetPt",
    "jetEta",
    ),
 JetIdParams = full_5x_chs_wp,
 label = cms.string("full")
 )
####################################################################################################################  
cutbased = cms.PSet( 
 impactParTkThreshold = cms.double(1.),
 cutBased = cms.bool(True),
 JetIdParams = PuJetIdCutBased_wp,
 label = cms.string("cutbased")
 )

####################################################################################################################  
PhilV1 = cms.PSet(
 impactParTkThreshold = cms.double(1.) ,
 cutBased = cms.bool(False),
 etaBinnedWeights = cms.bool(False),
 tmvaWeights = cms.string("RecoJets/JetProducers/data/mva_JetID_v1.weights.xml"),
 tmvaMethod  = cms.string("JetID"),
 version = cms.int32(-1),
 tmvaVariables = cms.vstring(
    "nvtx",
    "jetPt",
    "jetEta",
    "jetPhi",
    "dZ",
    "d0",
    "beta",
    "betaStar",
    "nCharged",
    "nNeutrals",
    "dRMean",
    "frac01",
    "frac02",
    "frac03",
    "frac04",
    "frac05",
    ),
 tmvaSpectators = cms.vstring(),
 JetIdParams = JetIdParams,
 label = cms.string("philv1")
 )

