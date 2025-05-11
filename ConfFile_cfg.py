import FWCore.ParameterSet.Config as cms

process = cms.Process("JETANALYSIS")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(10))

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
        'file:909488FF-8D72-E211-893B-0026189438EF.root'  # Reemplazar con tu archivo
    )
)

process.myJetAnalyzer = cms.EDAnalyzer('MyJetAnalyzerBeta')

process.p = cms.Path(process.myJetAnalyzer)
