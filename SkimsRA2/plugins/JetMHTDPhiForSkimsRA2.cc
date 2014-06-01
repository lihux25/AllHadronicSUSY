
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDFilter.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/Common/interface/View.h"
#include "DataFormats/METReco/interface/MET.h"
#include "DataFormats/JetReco/interface/Jet.h"
#include "DataFormats/Math/interface/deltaPhi.h"


class JetMHTDPhiForSkimsRA2 : public edm::EDFilter {

  public:

    explicit JetMHTDPhiForSkimsRA2(const edm::ParameterSet & iConfig);
    ~JetMHTDPhiForSkimsRA2() {}

  private:

    virtual bool filter(edm::Event & iEvent, const edm::EventSetup & iSetup);
    
    edm::InputTag mhtSrc_, jetSrc_;

};


JetMHTDPhiForSkimsRA2::JetMHTDPhiForSkimsRA2(const edm::ParameterSet & iConfig) {
  mhtSrc_ = iConfig.getParameter<edm::InputTag>("MHTSource");
  jetSrc_ = iConfig.getParameter<edm::InputTag>("JetSource");

  produces<std::vector<double> >("jetMHTDPhiVec");
}


bool JetMHTDPhiForSkimsRA2::filter(edm::Event & iEvent, const edm::EventSetup & iSetup) {

  // read in the objects
  edm::Handle<edm::View<reco::MET> > mht;
  iEvent.getByLabel(mhtSrc_, mht);
  edm::Handle<edm::View<reco::Jet> > jets;
  iEvent.getByLabel(jetSrc_, jets);

  std::auto_ptr<std::vector<double> > jetMHTDPhiVecPtr (new std::vector<double> );

  double dPhi0 = 999., dPhi1 = 999., dPhi2 = 999.;

  if (jets->size() >= 1) dPhi0 = std::abs(reco::deltaPhi((*jets)[0].phi(), (*mht)[0].phi()));
  if (jets->size() >= 2) dPhi1 = std::abs(reco::deltaPhi((*jets)[1].phi(), (*mht)[0].phi()));
  if (jets->size() >= 3) dPhi2 = std::abs(reco::deltaPhi((*jets)[2].phi(), (*mht)[0].phi()));

  jetMHTDPhiVecPtr->push_back(dPhi0); jetMHTDPhiVecPtr->push_back(dPhi1); jetMHTDPhiVecPtr->push_back(dPhi2);

  iEvent.put( jetMHTDPhiVecPtr, "jetMHTDPhiVec");

  return true;

}


#include "FWCore/Framework/interface/MakerMacros.h"

DEFINE_FWK_MODULE(JetMHTDPhiForSkimsRA2);
