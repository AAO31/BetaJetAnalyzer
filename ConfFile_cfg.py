import FWCore.ParameterSet.Config as cms

process = cms.Process("JETANALYSIS")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(10))

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
        'file:input.root'  # Reemplazar con tu archivo
    )
)

process.myJetAnalyzer = cms.EDAnalyzer('MyJetAnalyzerBeta')

process.p = cms.Path(process.myJetAnalyzer)
