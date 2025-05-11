// Includes esenciales
#include <iostream>  // Para std::cout
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"  // ¡Necesario para DEFINE_FWK_MODULE!
#include "FWCore/ParameterSet/interface/ParameterSet.h"

class MyJetAnalyzerBeta : public edm::EDAnalyzer {
public:
    explicit MyJetAnalyzerBeta(const edm::ParameterSet&);
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
