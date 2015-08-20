import FWCore.ParameterSet.Config as cms

HcalHaloFilter = cms.EDFilter(
  "HcalHaloFilter",
  taggingMode = cms.bool(False),
  maxStripLength = cms.int32(5)
)
