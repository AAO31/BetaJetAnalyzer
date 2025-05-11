// Includes esenciales
#include <iostream>  // Para std::cout
#include "FWCore/Framework/interface/Frameworkfwd.h" //componentes esenciales de CMSSW
#include "FWCore/Framework/interface/EDAnalyzer.h" // construir analizador
#include "FWCore/Framework/interface/Event.h" //para acceder la información de cada colisión
#include "FWCore/Framework/interface/MakerMacros.h"  //  DEFINE_FWK_MODULE
#include "FWCore/ParameterSet/interface/ParameterSet.h"

// Definir Analyzer
class MyJetAnalyzerBeta : public edm::EDAnalyzer {
public:
    explicit MyJetAnalyzerBeta(const edm::ParameterSet&); //Para leer configuraciones desde el archivo .cfg
    void analyze(const edm::Event&, const edm::EventSetup&) override;
};

// Implementación del constructor
MyJetAnalyzerBeta::MyJetAnalyzerBeta(const edm::ParameterSet& iConfig) {}

// Implementación de analyze()
void MyJetAnalyzerBeta::analyze(const edm::Event& iEvent, const edm::EventSetup&) {
    std::cout << "Procesando evento: " << iEvent.id().event() << std::endl;
}

// Macro final (debe estar después de la definición completa de la clase)
DEFINE_FWK_MODULE(MyJetAnalyzerBeta);
