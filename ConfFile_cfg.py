import FWCore.ParameterSet.Config as cms

process = cms.Process("JETANALYSIS")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(-1))

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
        'file:input.root'
    )
)

process.myJetAnalyzerBeta = cms.EDAnalyzer('MyJetAnalyzerBeta',
    jets = cms.InputTag("ak4PFJets"),
    jetPtMin = cms.double(30.0),
    jetEtaMax = cms.double(2.5),
    jetAlgo = cms.string("AK4")
)

process.TFileService = cms.Service("TFileService",
    fileName = cms.string('jetAnalysisOutput.root')
)

process.p = cms.Path(process.myJetAnalyzerBeta)
