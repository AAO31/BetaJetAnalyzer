import FWCore.ParameterSet.Config as cms #Importa las herramientas de configuracion de CMSSW (cms)

process = cms.Process("JETANALYSIS") #Crea el proceso CMSSW JETANALYSIS (el nombre puede variar)

process.load("FWCore.MessageService.MessageLogger_cfi") # mensajes en consola
process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(10)) #procesa n eventos (10 en este caso)

process.source = cms.Source("PoolSource", # Lee eventos desde archivos ROOT de CMS
    fileNames = cms.untracked.vstring(
        'file:909488FF-8D72-E211-893B-0026189438EF.root'  # Reemplazar con archivo a analizar
    )
)

process.myJetAnalyzer = cms.EDAnalyzer('MyJetAnalyzerBeta')

process.p = cms.Path(process.myJetAnalyzer)
