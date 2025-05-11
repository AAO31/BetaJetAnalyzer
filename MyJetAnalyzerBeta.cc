#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

class MyJetAnalyzerBeta : public edm::EDAnalyzer {
public:
    explicit MyJetAnalyzerBeta(const edm::ParameterSet&);
    void analyze(const edm::Event&, const edm::EventSetup&) override;
};

MyJetAnalyzerBeta::MyJetAnalyzerBeta(const edm::ParameterSet& iConfig) {}

void MyJetAnalyzerBeta::analyze(const edm::Event& iEvent, const edm::EventSetup&) {
    // Solo imprime el número de evento como prueba
    std::cout << "Procesando evento: " << iEvent.id().event() << std::endl;
}

DEFINE_FWK_MODULE(MyJetAnalyzerBeta);
