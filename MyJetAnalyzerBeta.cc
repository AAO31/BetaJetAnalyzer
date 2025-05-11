// -*- C++ -*-
//
// Package:    JetAnalyzerBeta/MyJetAnalyzerBeta
// Class:      MyJetAnalyzerBeta
// 
/**\class MyJetAnalyzerBeta MyJetAnalyzerBeta.cc JetAnalyzerBeta/MyJetAnalyzerBeta/plugins/MyJetAnalyzerBeta.cc

 Description: [one line class summary]
 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  
//         Created:  Fri, 25 Apr 2025 12:07:03 GMT
//

// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

// jet data formats
#include "DataFormats/JetReco/interface/PFJet.h"
#include "DataFormats/JetReco/interface/PFJetCollection.h"

// ROOT includes
#include "TH1.h"
#include "TH2.h"

class MyJetAnalyzerBeta : public edm::EDAnalyzer {
   public:
      explicit MyJetAnalyzerBeta(const edm::ParameterSet&);
      ~MyJetAnalyzerBeta() override;
      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

   private:
      void beginJob() override;
      void analyze(const edm::Event&, const edm::EventSetup&) override;
      void endJob() override;

      edm::EDGetTokenT<reco::PFJetCollection> jetsToken_;
      edm::Service<TFileService> fs;
      
      TH1D *h_jetPt;
      TH1D *h_jetEta;
      TH1D *h_jetPhi;
      TH1D *h_jetMass;
      TH1D *h_nJets;
};

MyJetAnalyzerBeta::MyJetAnalyzerBeta(const edm::ParameterSet& iConfig) :
  jetsToken_(consumes<reco::PFJetCollection>(iConfig.getParameter<edm::InputTag>("jets")))
{
  h_jetPt = fs->make<TH1D>("jetPt","Jet p_{T};p_{T} (GeV);Jets",100,0,500);
  h_jetEta = fs->make<TH1D>("jetEta","Jet #eta;#eta;Jets",100,-5,5);
  h_jetPhi = fs->make<TH1D>("jetPhi","Jet #phi;#phi;Jets",100,-3.1416,3.1416);
  h_jetMass = fs->make<TH1D>("jetMass","Jet mass;mass (GeV);Jets",100,0,200);
  h_nJets = fs->make<TH1D>("nJets","Number of jets per event;N_{jets};Events",50,0,50);
}

MyJetAnalyzerBeta::~MyJetAnalyzerBeta() {}

void MyJetAnalyzerBeta::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup) {
  edm::Handle<reco::PFJetCollection> jets;
  iEvent.getByToken(jetsToken_, jets);
  
  int nJets = 0;
  for(const auto& jet : *jets) {
    h_jetPt->Fill(jet.pt());
    h_jetEta->Fill(jet.eta());
    h_jetPhi->Fill(jet.phi());
    h_jetMass->Fill(jet.mass());
    nJets++;
  }
  h_nJets->Fill(nJets);
}

void MyJetAnalyzerBeta::beginJob() {}
void MyJetAnalyzerBeta::endJob() {}

void MyJetAnalyzerBeta::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  edm::ParameterSetDescription desc;
  desc.add<edm::InputTag>("jets",edm::InputTag("ak4PFJets"));
  descriptions.add("myJetAnalyzerBeta",desc);
}

DEFINE_FWK_MODULE(MyJetAnalyzerBeta);
