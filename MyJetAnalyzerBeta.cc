// -*- C++ -*-
//
// Package:    JetAnalysis/MyJetAnalyzerBeta
// Class:      MyJetAnalyzerBeta
// 
/**\class MyJetAnalyzerBeta MyJetAnalyzerBeta.cc JetAnalysis/MyJetAnalyzerBeta/plugins/MyJetAnalyzerBeta.cc

 Description: Analyzer for basic jet properties (pt, eta, phi, mass)
 Implementation:
     - Uses PFJets collection
     - Configurable jet pt and eta cuts
     - Produces standard jet histograms
*/
//
// Original Author:  
//         Created:  Fri, 25 Apr 2025 12:07:03 GMT
//

// system include files
#include <memory>
#include <string>

// framework includes
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"

// jet data formats
#include "DataFormats/JetReco/interface/PFJet.h"
#include "DataFormats/JetReco/interface/PFJetCollection.h"

// ROOT includes
#include "TH1D.h"
#include "TH2D.h"
#include "TFileService.h"

using namespace std;
using namespace edm;
using namespace reco;

class MyJetAnalyzerBeta : public edm::one::EDAnalyzer<edm::one::SharedResources> {
   public:
      explicit MyJetAnalyzerBeta(const edm::ParameterSet&);
      ~MyJetAnalyzerBeta() override;
      
      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

   private:
      void beginJob() override;
      void analyze(const edm::Event&, const edm::EventSetup&) override;
      void endJob() override;

      // Input tokens
      const edm::EDGetTokenT<PFJetCollection> jetsToken_;
      
      // Configuration parameters
      const double jetPtMin_;
      const double jetEtaMax_;
      const std::string jetAlgo_;
      
      // Histograms
      TH1D* h_jetPt;
      TH1D* h_jetEta;
      TH1D* h_jetPhi;
      TH1D* h_jetMass;
      TH1D* h_nJets;
      TH2D* h_jetEtaVsPhi;
      TH1D* h_jetCharge;
};

//
// constructors and destructor
//
MyJetAnalyzerBeta::MyJetAnalyzerBeta(const edm::ParameterSet& iConfig):
  jetsToken_(consumes<PFJetCollection>(iConfig.getParameter<InputTag>("jets"))),
  jetPtMin_(iConfig.getParameter<double>("jetPtMin")),
  jetEtaMax_(iConfig.getParameter<double>("jetEtaMax")),
  jetAlgo_(iConfig.getParameter<string>("jetAlgo"))
{
  usesResource("TFileService");
  
  // Initialize histograms
  edm::Service<TFileService> fs;
  
  h_jetPt = fs->make<TH1D>("jetPt", "Jet p_{T}; p_{T} [GeV]; Jets", 200, 0, 1000);
  h_jetEta = fs->make<TH1D>("jetEta", "Jet #eta; #eta; Jets", 100, -5.0, 5.0);
  h_jetPhi = fs->make<TH1D>("jetPhi", "Jet #phi; #phi [rad]; Jets", 100, -M_PI, M_PI);
  h_jetMass = fs->make<TH1D>("jetMass", "Jet mass; mass [GeV]; Jets", 100, 0, 200);
  h_nJets = fs->make<TH1D>("nJets", "Jets per event; Number of jets; Events", 50, 0, 50);
  h_jetEtaVsPhi = fs->make<TH2D>("jetEtaVsPhi", "Jet #eta vs #phi; #eta; #phi [rad]", 
                                 100, -5.0, 5.0, 100, -M_PI, M_PI);
  h_jetCharge = fs->make<TH1D>("jetCharge", "Jet charge; Charge; Jets", 21, -10.5, 10.5);
}

MyJetAnalyzerBeta::~MyJetAnalyzerBeta() {}

//
// member functions
//

void MyJetAnalyzerBeta::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup) {
  Handle<PFJetCollection> jets;
  iEvent.getByToken(jetsToken_, jets);

  if (!jets.isValid()) {
    edm::LogError("MyJetAnalyzerBeta") << "Invalid jet collection!" << endl;
    return;
  }

  int nSelectedJets = 0;
  
  for (const auto& jet : *jets) {
    // Apply selection cuts
    if (jet.pt() < jetPtMin_) continue;
    if (fabs(jet.eta()) > jetEtaMax_) continue;
    
    // Fill histograms
    h_jetPt->Fill(jet.pt());
    h_jetEta->Fill(jet.eta());
    h_jetPhi->Fill(jet.phi());
    h_jetMass->Fill(jet.mass());
    h_jetEtaVsPhi->Fill(jet.eta(), jet.phi());
    h_jetCharge->Fill(jet.charge());
    
    nSelectedJets++;
  }
  
  h_nJets->Fill(nSelectedJets);
  
  LogDebug("MyJetAnalyzerBeta") << "Selected " << nSelectedJets << " jets (from " 
                               << jets->size() << " total jets)";
}

void MyJetAnalyzerBeta::beginJob() {}

void MyJetAnalyzerBeta::endJob() {}

void MyJetAnalyzerBeta::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  edm::ParameterSetDescription desc;
  desc.add<InputTag>("jets", InputTag("ak4PFJets"));
  desc.add<double>("jetPtMin", 30.0);
  desc.add<double>("jetEtaMax", 2.5);
  desc.add<string>("jetAlgo", "AK4");
  descriptions.add("myJetAnalyzerBeta", desc);
}

// Define this as a plug-in
DEFINE_FWK_MODULE(MyJetAnalyzerBeta);
