#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
// additional headers
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "FWCore/Utilities/interface/EDMException.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "DataFormats/Provenance/interface/EventAuxiliary.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "TString.h"
#include "TTree.h"
#include <TFile.h>
#include <vector>
#include "TLorentzVector.h"
#include "Math/GenVector/LorentzVector.h"
#include <DataFormats/Math/interface/deltaR.h>
#include "DataFormats/PatCandidates/interface/PackedGenParticle.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"

#include "DataFormats/PatCandidates/interface/PackedCandidate.h"
//
// class declaration
//

class stopTreeMaker : public edm::EDProducer {
public:
  explicit stopTreeMaker(const edm::ParameterSet&);
  ~stopTreeMaker();
  static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);
private:
  virtual void beginJob() override;
  virtual void produce(edm::Event&, const edm::EventSetup&) override;
  virtual void endJob() override;
  // ----------member data ---------------------------
  const unsigned int nMaxCandidates_;
  void setBranchVariablesToDefault();
  TString treeName_;
  TTree* tree_;	
  bool debug_;
  // generell event information
  UInt_t runNum_;      
  UInt_t lumiBlockNum_;
  UInt_t evtNum_;
  
  // any float precision varialbes
  std::vector<edm::InputTag> varsDoubleTags_;
  std::vector<std::string> varsDoubleNames_;
  std::vector<double> varsDouble_;
  // any int precision varialbes
  std::vector<edm::InputTag> varsIntTags_;
  std::vector<std::string> varsIntNames_;
  std::vector<int> varsInt_;
  // any bool precision varialbes
  std::vector<edm::InputTag> varsBoolTags_;
  std::vector<std::string> varsBoolNames_;
  std::vector<unsigned int> varsBool_;
  // any string precision varialbes
  std::vector<edm::InputTag> varsStringTags_;
  std::vector<std::string> varsStringNames_;
  std::vector<std::string> varsString_;
  // any TLorentzVector precision varialbes
  std::vector<edm::InputTag> varsTLorentzVectorTags_;
  std::vector<std::string> varsTLorentzVectorNames_;
  std::vector<TLorentzVector> varsTLorentzVector_;
  
  // any float precision varialbes
  std::vector<edm::InputTag> vectorDoubleTags_;
  std::vector<std::string> vectorDoubleNames_;
  std::vector<std::vector<double> > vectorDoubleVector_;
  // any int precision varialbes
  std::vector<edm::InputTag> vectorIntTags_;
  std::vector<std::string> vectorIntNames_;
  std::vector<std::vector<int> > vectorIntVector_;
  // any bool precision varialbes
  std::vector<edm::InputTag> vectorBoolTags_;
  std::vector<std::string> vectorBoolNames_;
  std::vector<std::vector<unsigned int> > vectorBoolVector_;
  // any string precision varialbes
  std::vector<edm::InputTag> vectorStringTags_;
  std::vector<std::string> vectorStringNames_;
  std::vector<std::vector<std::string> > vectorStringVector_;
  // any TLorentzVector precision varialbes
  std::vector<edm::InputTag> vectorTLorentzVectorTags_;
  std::vector<std::string> vectorTLorentzVectorNames_;
  std::vector<std::vector<TLorentzVector> > vectorTLorentzVector_;

  TString formBranchName(const edm::InputTag & varTag, const std::vector<std::string> & vectorNames);

  std::vector<TString> cachedNames_;

};
