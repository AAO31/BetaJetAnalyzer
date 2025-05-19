import FWCore.ParameterSet.Config as cms # Importa herramientas de configuracion de CMSSW

# Configuracion basica del proceso
process = cms.Process("JETANALYSIS") # Crea el proceso principal

# Configuracion de mensajes
process.load("FWCore.MessageService.MessageLogger_cfi") # Habilita mensajes en consola
process.MessageLogger.cerr.FwkReport.reportEvery = 100 # Mostrar progreso cada 100 eventos

# Numero de eventos a procesar (ideal para pruebas)
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(10) # Procesa solo 10 eventos inicialmente
)

# Configuracion del archivo de entrada
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
        'file:input.root'  # Reemplazar con archivo root a analizar
    )
)

# Configuracion del servicio para archivos de salida ROOT
process.TFileService = cms.Service("TFileService",
    fileName = cms.string('jet_analysis_output.root') # Nombre del archivo de resultados
)

# Configuracion de analizador personalizado
process.myJetAnalyzer = cms.EDAnalyzer('MyJetAnalyzerBeta',
    jetInput = cms.InputTag("ak4PFJets") # Coleccion de jets a analizar
)

# Secuencia de ejecucion
process.p = cms.Path(process.myJetAnalyzer)

# Informacion adicional para el usuario
print "\nConfiguracion lista para analizar jets basicos:"
print "- Se usara la coleccion:", process.myJetAnalyzer.jetInput.value()
print "- Resultados se guardaran en:", process.TFileService.fileName.value()
print "- Numero de eventos a procesar:", process.maxEvents.input.value(), "\n"
