// -*- C++ -*-
//
// Package:    JetAnalyzerBeta
// Class:      MyJetAnalyzerBeta
// 
// Analizador de jets 
// Version beta para propiedades basicas

// Includes del sistema
#include <iostream>  // Para salida en consola
#include <vector>    // Para almacenar multiples jets
#include <memory>    // Para manejo de memoria

// Includes de CMSSW
#include "FWCore/Framework/interface/Frameworkfwd.h"  // Estructuras basicas
#include "FWCore/Framework/interface/EDAnalyzer.h"   // Clase base para analizadores
#include "FWCore/Framework/interface/Event.h"        // Acceso a datos del evento
#include "FWCore/Framework/interface/MakerMacros.h"  // Para DEFINE_FWK_MODULE
#include "FWCore/ParameterSet/interface/ParameterSet.h" // Configuracion
#include "FWCore/ServiceRegistry/interface/Service.h" // Servicios como TFileService
#include "CommonTools/UtilAlgos/interface/TFileService.h" // Para archivos ROOT

// Includes para datos de jets
#include "DataFormats/JetReco/interface/PFJet.h"      // Clase de jets
#include "DataFormats/JetReco/interface/PFJetCollection.h" // Coleccion de jets

// Includes de ROOT para salida
#include "TTree.h"  // Para guardar datos estructurados
#include "TH1.h"    // Para histogramas (para despues)

// Definicion de la clase principal
class MyJetAnalyzerBeta : public edm::EDAnalyzer {
public:
    // Constructor - configuracion
    explicit MyJetAnalyzerBeta(const edm::ParameterSet&);
    
    // Destructor
    ~MyJetAnalyzerBeta() override;
    
    // Para documentar parametros
    static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);
    
private:
    // Metodos principales
    virtual void beginJob() override;  // Al inicio del trabajo
    virtual void analyze(const edm::Event&, const edm::EventSetup&) override;  // Procesa cada evento
    virtual void endJob() override;   // Al final del trabajo
    
    // Etiqueta para la coleccion de jets (editable)
    edm::InputTag jetInput_;
    
    // Variables para el arbol ROOT
    TTree *jetTree_;          // Tree para guardar datos
    int numJets_;             // Numero de jets en el evento
    std::vector<float> jet_pt_;    // Momento transversal de los jets
    std::vector<float> jet_eta_;   // Posicion angular eta
    std::vector<float> jet_phi_;   // Posicion angular phi
    std::vector<float> jet_energy_; // Energia de los jets
};

// Implementacion del constructor
MyJetAnalyzerBeta::MyJetAnalyzerBeta(const edm::ParameterSet& iConfig) :
    jetInput_(iConfig.getParameter<edm::InputTag>("jetInput"))
{
    // Configuramos el servicio para crear archivos ROOT
    edm::Service<TFileService> fs;
    
    // Creamos el arbol para guardar los datos
    jetTree_ = fs->make<TTree>("JetTree", "Tree con propiedades de jets");
    
    // Definimos las ramas del Tree:
    // 1. Numero de jets en el evento
    jetTree_->Branch("numJets", &numJets_, "numJets/I");
    
    // 2. Propiedades individuales de cada jet
    jetTree_->Branch("jet_pt", &jet_pt_);      // Momento transversal
    jetTree_->Branch("jet_eta", &jet_eta_);    // Posicion eta
    jetTree_->Branch("jet_phi", &jet_phi_);    // Posicion phi
    jetTree_->Branch("jet_energy", &jet_energy_); // Energia
    
    // Mensaje inicial
    std::cout << "Inicializando analizador de jets..." << std::endl;
    std::cout << "Coleccion de jets usada: " << jetInput_.encode() << std::endl;
}

// Implementacion del destructor
MyJetAnalyzerBeta::~MyJetAnalyzerBeta()
{
    // Mensaje al finalizar
    std::cout << "Finalizando analizador de jets" << std::endl;
}

// Metodo principal que analiza cada evento
void MyJetAnalyzerBeta::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
    using namespace edm;
    
    // Limpia los datos del evento anterior
    numJets_ = 0;
    jet_pt_.clear();
    jet_eta_.clear();
    jet_phi_.clear();
    jet_energy_.clear();
    
    // Obtenemos la coleccion de jets del evento
    Handle<reco::PFJetCollection> jets;
    iEvent.getByLabel(jetInput_, jets);
    
    // Verifica si la coleccion es valida
    if (!jets.isValid()) {
        std::cout << "ADVERTENCIA: Coleccion de jets no valida!" << std::endl;
        return;
    }
    
    // Definimos el corte minimo de pt (20 GeV para probar)
    const float min_pt = 20.0;
    
    // recorrer todos los jets del evento
    for (const auto& jet : *jets) {
        // Aplicamos el corte en pt
        if (jet.pt() > min_pt) {
            // Guardamos las propiedades del jet
            jet_pt_.push_back(jet.pt());          // Momento transversal
            jet_eta_.push_back(jet.eta());        // Posicion eta
            jet_phi_.push_back(jet.phi());        // Posicion phi
            jet_energy_.push_back(jet.energy());  // Energia
            numJets_++;  // Contamos este jet
        }
    }
    
    // Guardar los datos en el tree para este evento
    jetTree_->Fill();
    
    // Mostramos informacion basica en consola
    std::cout << "Evento " << iEvent.id().event() 
              << ": Se encontraron " << numJets_ 
              << " jets con pt > " << min_pt << " GeV" << std::endl;
}

// Metodo ejecutado al inicio del trabajo
void MyJetAnalyzerBeta::beginJob() 
{
    std::cout << "Comenzando analisis de jets..." << std::endl;
}

// Metodo ejecutado al final del trabajo
void MyJetAnalyzerBeta::endJob() 
{
    std::cout << "Analisis de jets completado" << std::endl;
}

// Configuracion de parametros
void MyJetAnalyzerBeta::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
    edm::ParameterSetDescription desc;
    desc.add<edm::InputTag>("jetInput", edm::InputTag("ak4PFJets"));
    descriptions.add("myJetAnalyzerBeta", desc);
}

// Definimos este modulo como plugin de CMSSW
DEFINE_FWK_MODULE(MyJetAnalyzerBeta);
