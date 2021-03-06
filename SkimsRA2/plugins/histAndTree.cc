#include <memory>

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDFilter.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/Framework/interface/Event.h"
#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/Common/interface/View.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Tau.h"
#include "DataFormats/PatCandidates/interface/Photon.h"

#include "DataFormats/METReco/interface/MET.h"
#include "DataFormats/METReco/interface/GenMET.h"

#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "SimDataFormats/GeneratorProducts/interface/HepMCProduct.h"
#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"

#include "DataFormats/ParticleFlowCandidate/interface/PFCandidateFwd.h"
#include "DataFormats/ParticleFlowCandidate/interface/PFCandidate.h"

#include "DataFormats/Common/interface/Ptr.h"

#include "JetMETCorrections/Objects/interface/JetCorrector.h"

#include "SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "DataFormats/Common/interface/ValueMap.h"

#include "DataFormats/JetReco/interface/BasicJet.h"
#include "DataFormats/JetReco/interface/BasicJetCollection.h"

//#include "SimGeneral/HepPDTRecord/interface/ParticleDataTable.h"

#include "recipeAUX/OxbridgeMT2/interface/Basic_Mt2_332_Calculator.h"
#include "recipeAUX/OxbridgeMT2/interface/ChengHanBisect_Mt2_332_Calculator.h"

#include "AllHadronicSUSY/TopTagger/interface/Type3TopTagger.h"

#include "AllHadronicSUSY/TopTagger/interface/combination.h"
#include "AllHadronicSUSY/TopTagger/interface/indexSort.h"

#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TRandom3.h"
#include "TLorentzVector.h"

typedef unsigned int size;
static const int sgnfnDof = 2;

using namespace edm;
using namespace std;

//For sorting by pt
struct GreaterByPtCandPtr
{
  bool operator()( const edm::Ptr<reco::Candidate> & t1, const edm::Ptr<reco::Candidate> & t2 ) const
  {return t1->pt() > t2->pt();}
};

class histAndTree : public edm::EDFilter{

  public:

    explicit histAndTree(const edm::ParameterSet & iConfig);
    ~histAndTree();
    virtual bool filter(edm::Event&, const edm::EventSetup&);
    virtual void beginJob();
    virtual void endJob();
    virtual bool beginRun(edm::Run&, const edm::EventSetup&);
    virtual bool endRun(edm::Run&, const edm::EventSetup&);

    size run, event, ls; bool isdata;
    edm::InputTag vtxSrc_;
    edm::Handle<edm::View<reco::Vertex> > vertices;
    size nVtxPUcut_, vtxSize;
    edm::InputTag evtWeightInput_;
    edm::Handle<double> evtWeight_;
    void loadEventInfo(const edm::Event& iEvent, const edm::EventSetup& iSetup);

    edm::InputTag jetSrc_;
    edm::Handle<edm::View<reco::Jet> > jets;
    edm::Handle<std::vector<pat::Jet> > patjets;
    std::vector<std::string> bTagKeyString_;
    size nbTagKeys;
    size nJets;
    reco::Jet jet1, jet2, jet3, jetother;
    edm::InputTag hepTaggerJetSrc_;
    edm::Handle<reco::BasicJetCollection> HEPTopTaggedCandidateHandle;
    bool isPatJet;
    virtual void loadRecoJets(const edm::Event& iEvent);

    edm::InputTag muonSrc_;
    edm::Handle<edm::View<reco::Muon > > muons;
    edm::InputTag eleSrc_;
//    edm::Handle<edm::View<pat::Electron > > electrons;
    edm::Handle<edm::View<reco::GsfElectron> > electrons;
    edm::InputTag tauSrc_;
    edm::Handle<edm::View<pat::Tau > > taus;
    size nMuons, nElectrons, nTaus;
    edm::InputTag forVetoMuonSrc_;
    edm::Handle<edm::View<reco::Muon > > forVetoMuons;
    edm::InputTag forVetoElectronSrc_;
//    edm::Handle<edm::View<pat::Electron > > forVetoElectrons;
    edm::Handle<edm::View<reco::GsfElectron> > forVetoElectrons;
    size nMuonsForVeto, nElectronsForVeto;
    reco::Muon muon1, muon2; int muon1Charge, muon2Charge;
    pat::Electron ele1, ele2; int ele1Charge, ele2Charge;
    virtual void loadLeptons(const edm::Event& iEvent);

    edm::InputTag forVetoIsoTrkSrc_;
    edm::Handle<edm::View<reco::PFCandidate> > forVetoIsoTrks;
    size nIsoTrksForVeto;

    edm::InputTag photonSrc_;
    edm::Handle<edm::View<pat::Photon> > photons;
    size nPhotons;
    virtual void loadPhotons(const edm::Event& iEvent);

    edm::InputTag metSrc_;
    edm::Handle<edm::View<reco::MET> > met;
    edm::InputTag type1metSrc_;
    edm::Handle<edm::View<reco::MET> > type1met;
    edm::InputTag mhtSrc_, mht_forSgnfSrc_;
    edm::Handle<edm::View<reco::MET> > mht, mht_forSgnf;
    virtual void loadMETMHT(const edm::Event& iEvent);

    edm::InputTag htSrc_;
    edm::Handle<double> ht;
    virtual void loadHT(const edm::Event& iEvent);

    double pthat, scalePDF;
    edm::InputTag genJetSrc_;
    edm::Handle<edm::View<reco::GenJet > > genJets;
    size nGenJets;
    reco::GenJet genJet1, genJet2, genJet3, genJetother;
    edm::InputTag genParticleSrc_;
    edm::Handle<edm::View<reco::GenParticle > > genParticles;
    edm::InputTag genMETSrc_;
    edm::Handle<edm::View<reco::GenMET > > genMET;
    Handle<std::vector< PileupSummaryInfo > >  PupInfo;
    int npv; double avg_npv; int nm1, n0, np1; double tru_npv;
    virtual void loadGenInfo(const edm::Event& iEvent);

    edm::InputTag dPhis_CUT_vec_Src_;
    edm::Handle<std::vector<double> > dPhis_CUT_vec_;
    edm::InputTag nJets_CUT_Src_;
    edm::Handle<int> nJets_CUT_;
    edm::InputTag externalBitToTree_Src_;
    edm::Handle<int> externalBitToTree_;
    virtual void loadAUX(const edm::Event& iEvent);

// Indices ==> 0 : for muon  1 : for electron 
// Combination is the following:
// 00 : veto all muons and electrons ==> standard RA2
// 10 : muon control sample ==> for lost-lepton, hadronic tau, W+Jets
// 20 : muon control sample ==> for Z+Jets
// others : currently NOT used
    std::vector<int> nLeptonsSels_;

    bool debug_;

    bool doFillTree_;

    bool isData;

    bool printOnce_;
    vector<std::string> availJECLevels_;

    TTree *outTree;
    double evtWeight_TR;
    double mht_TR, ht_TR, met_TR, mt_TR, type1mt_TR, type1met_TR;
    double mhtphi_TR, metphi_TR, type1metphi_TR;
    double metSgnf_TR, metSgnfProb_TR, type1metSgnf_TR, type1metSgnfProb_TR;
    double mht_forSgnf_TR, mhtphi_forSgnf_TR, mhtSgnf_TR, mhtSgnfProb_TR;
    double jet1pt_TR, jet1eta_TR, jet1phi_TR, jet1energy_TR;
    double jet2pt_TR, jet2eta_TR, jet2phi_TR, jet2energy_TR;
    double jet3pt_TR, jet3eta_TR, jet3phi_TR, jet3energy_TR;
    std::vector<double> *otherJetspt_TR, *otherJetseta_TR, *otherJetsphi_TR, *otherJetsenergy_TR;
    std::vector<TLorentzVector> *jetsLVec_TR;
    std::vector<TLorentzVector> *forVetoIsoTrksLVec_TR;
    std::vector<std::vector<double> > *forVetoIsoTrksAuxVec_TR;
    std::vector<int> *forVetoIsoTrksConsMatchedJetIdxVec_TR;

    double mu1pt_TR, mu1eta_TR, mu1phi_TR;
    double mu2pt_TR, mu2eta_TR, mu2phi_TR;
    std::vector<double> *otherMuspt_TR, *otherMuseta_TR, *otherMusphi_TR;
    std::vector<TLorentzVector> *muonsLVec_TR;
    std::vector<double> *muonsAux_TR;
    double ele1pt_TR, ele1eta_TR, ele1phi_TR;
    double ele2pt_TR, ele2eta_TR, ele2phi_TR;
    std::vector<double> *otherElespt_TR, *otherEleseta_TR, *otherElesphi_TR;
    std::vector<TLorentzVector> *elesLVec_TR;
    std::vector<double> *elesAux_TR;
    double dPhi0_CUT, dPhi1_CUT, dPhi2_CUT;
    int nJets_CUT;
    double genJet1pt_TR, genJet1eta_TR, genJet1phi_TR, genJet1energy_TR;
    double genJet2pt_TR, genJet2eta_TR, genJet2phi_TR, genJet2energy_TR;
    double genJet3pt_TR, genJet3eta_TR, genJet3phi_TR, genJet3energy_TR;
    std::vector<double> *otherGenJetspt_TR, *otherGenJetseta_TR, *otherGenJetsphi_TR, *otherGenJetsenergy_TR;
    double genMET_TR;
    double jet1Res_TR, jet2Res_TR, jet3Res_TR;
    std::vector<double> *otherJetsRes_TR;
    int externalBitToTree_TR;

    std::vector<int> *recoJetsFlavor_TR, *genJetsFlavor_TR;
    std::vector<std::vector<double> > recoJetsBtag_TR;

    void setTreeDefaultVars();

    double recoGenJetsDR_;

    bool doSgnf_;

    bool doFillGenTopInfo_;

    edm::InputTag gentopIdxVecSrc_, gentopDausIdxVecSrc_, genWDausIdxVecSrc_, gentauDausIdxVecSrc_, decayTypeVecSrc_;
    edm::Handle<std::vector<int> > gentopIdxVec_;
    edm::Handle<std::vector<std::vector<int> > > gentopDausIdxVec_, genWDausIdxVec_, gentauDausIdxVec_;
    edm::Handle<std::vector<std::string> > decayTypeVec_;

    std::vector<TLorentzVector> *gentopLVec_TR;
    std::vector<int> *gentoppdgIdVec_TR;
    std::vector<std::vector<TLorentzVector> > *gentopDausLVec_TR, *genWDausLVec_TR, *gentauDausLVec_TR;
    std::vector<std::vector<int> > *gentopDauspdgIdVec_TR, *genWDauspdgIdVec_TR, *gentauDauspdgIdVec_TR;
    std::vector<std::string> *decayTypeVec_TR;
    void fillGenDecayInfo(const edm::Event& iEvent);

    bool fillGenInfo_;

// For HepTopTagger
    std::vector<TLorentzVector> *hepTaggerJets_TR;
    std::vector<std::vector<TLorentzVector> > *hepTaggerSubJets_TR;

// To store top tagger information
    bool doTopTagger_;
    double maxJetEtaCutForTopTagger_, minJetPtCutForTopTagger_;
    topTagger::type3TopTagger *topTaggerPtr;

    int bestTopJetIdx_TR, pickedRemainingCombfatJetIdx_TR;
    bool remainPassCSVS_TR;
    double bestTopJetMass_TR, mTbestTopJet_TR, mTbJet_TR, MT2_TR, mTbestWJet_TR, mTbestbJet_TR, mTremainingTopJet_TR;

    int getConsMatchedJetIdx(const std::vector<pat::Jet> & patjets, const TLorentzVector tomatchLVec, const double tomatchCharge, const double minDRcut);
    double minDRcutForConsMatch_;

// To store gen part info related to the decays
//    edm::ESHandle<ParticleDataTable> pdt_;
    bool storeGenDecayInfo_;
    edm::InputTag genDecayStrVecSrc_, genDecayChainPartIdxVecSrc_;
    edm::Handle<std::vector<std::string> > genDecayStrVec_;
    edm::Handle<std::vector<int> > genDecayChainPartIdxVec_;
    std::vector<std::string> * genDecayStrVec_TR;
    std::vector<int> * genDecayIdxVec_TR, * genDecayPdgIdVec_TR, * genDecayMomIdxVec_TR;
    std::vector<TLorentzVector> * genDecayLVec_TR;

// To store SMS model parameters
    bool storeSMSmodelInfo_;
    edm::InputTag smsModelFileNameStrSrc_, smsModelStrSrc_, smsModelMotherMassSrc_, smsModelDaughterMassSrc_;
    edm::Handle<std::vector<std::string> > smsModelFileNameStrVec_, smsModelStrVec_;
    edm::Handle<double> smsModelMotherMass_, smsModelDaughterMass_;
    std::vector<std::string> * smsModelFileNameStr_TR, * smsModelStr_TR;
    double smsModelMotherMass_TR, smsModelDaughterMass_TR;

// To store genjet collections
    std::vector<edm::InputTag> genJetsInputTags_;
    std::vector<std::vector<TLorentzVector> > genJetsLVec_TR;
    int find_idx(const reco::Candidate & target);
};

histAndTree::histAndTree(const edm::ParameterSet & iConfig) {

   isData = true;
 
   jetSrc_ = iConfig.getParameter<edm::InputTag>("jetSrc");
   hepTaggerJetSrc_ = iConfig.getParameter<edm::InputTag>("hepTaggerJetSrc");
   muonSrc_ = iConfig.getParameter<edm::InputTag>("muonSrc");
   eleSrc_ = iConfig.getParameter<edm::InputTag>("eleSrc");
//   tauSrc_ = iConfig.getParameter<edm::InputTag>("tauSrc");

//   std::string defaultbTagKeyString[] = {"jetBProbabilityBJetTags","jetProbabilityBJetTags","trackCountingHighPurBJetTags","trackCountingHighEffBJetTags","simpleSecondaryVertexHighEffBJetTags","simpleSecondaryVertexHighPurBJetTags","combinedSecondaryVertexBJetTags","combinedSecondaryVertexMVABJetTags"};
   std::string defaultbTagKeyString[] = {"combinedSecondaryVertexBJetTags"};
   std::vector<std::string> defaultbTagKeyStringStr(defaultbTagKeyString, defaultbTagKeyString + sizeof(defaultbTagKeyString)/sizeof(defaultbTagKeyString[0]));
   bTagKeyString_ = iConfig.getUntrackedParameter<std::vector<std::string> >("bTagKeyString", defaultbTagKeyStringStr);
   nbTagKeys = bTagKeyString_.size();
   std::cout<<"nbTagKeys : "<<nbTagKeys<<std::endl;

   forVetoMuonSrc_ = iConfig.getParameter<edm::InputTag>("forVetoMuonSrc");
   forVetoElectronSrc_ = iConfig.getParameter<edm::InputTag>("forVetoElectronSrc");
   forVetoIsoTrkSrc_ = iConfig.getParameter<edm::InputTag>("forVetoIsoTrkSrc");
 
   genJetSrc_ = iConfig.getParameter<edm::InputTag>("genJetSrc");
   genMETSrc_ = iConfig.getParameter<edm::InputTag>("genMETSrc");
   genParticleSrc_ = iConfig.getParameter<edm::InputTag>("genParticleSrc");

   recoGenJetsDR_ = iConfig.getParameter<double>("recoGenJetsDR");
 
   vtxSrc_ = iConfig.getParameter<edm::InputTag>("vtxSrc");
   evtWeightInput_ = iConfig.getParameter<edm::InputTag>("evtWeightInput");
   nVtxPUcut_ = iConfig.getParameter<unsigned int>("nVtxPUcut");
 
   metSrc_ = iConfig.getParameter<edm::InputTag>("metSrc");
   type1metSrc_ = iConfig.getParameter<edm::InputTag>("type1metSrc");
   mhtSrc_ = iConfig.getParameter<edm::InputTag>("mhtSrc");
   mht_forSgnfSrc_ = iConfig.getParameter<edm::InputTag>("mht_forSgnfSrc");
   htSrc_ = iConfig.getParameter<edm::InputTag>("htSrc");

   dPhis_CUT_vec_Src_ = iConfig.getParameter<edm::InputTag>("dPhis_CUT_vec_Src");
   nJets_CUT_Src_ = iConfig.getParameter<edm::InputTag>("nJets_CUT_Src");

   nLeptonsSels_ = iConfig.getParameter<std::vector<int> >("nLeptonsSels");
 
   debug_ = iConfig.getParameter<bool>("debug");

   doFillTree_ = iConfig.getParameter<bool>("doFillTree");

   externalBitToTree_Src_ = iConfig.getParameter<edm::InputTag>("externalBitToTree_Src");

   doSgnf_ = iConfig.getParameter<bool>("doSgnf");

   doFillGenTopInfo_ = iConfig.getParameter<bool>("doFillGenTopInfo");
   gentopIdxVecSrc_ = iConfig.getParameter<edm::InputTag>("gentopIdxVecSrc");
   gentopDausIdxVecSrc_ = iConfig.getParameter<edm::InputTag>("gentopDausIdxVecSrc");
   genWDausIdxVecSrc_ = iConfig.getParameter<edm::InputTag>("genWDausIdxVecSrc");
   gentauDausIdxVecSrc_ = iConfig.getParameter<edm::InputTag>("gentauDausIdxVecSrc");
   decayTypeVecSrc_ = iConfig.getParameter<edm::InputTag>("decayTypeVecSrc");

   fillGenInfo_ = iConfig.getParameter<bool>("fillGenInfo");

   doTopTagger_ = iConfig.getUntrackedParameter<bool>("doTopTagger", false);
   maxJetEtaCutForTopTagger_ = iConfig.getUntrackedParameter<double>("maxJetEtaCutForTopTagger", -1);
   minJetPtCutForTopTagger_ = iConfig.getUntrackedParameter<double>("minJetPtCutForTopTagger", 30);

   minDRcutForConsMatch_ = iConfig.getUntrackedParameter<double>("minDRcutForConsMatch", 0.01);

   storeGenDecayInfo_ = iConfig.getUntrackedParameter<bool>("storeGenDecayInfo", false);
   genDecayStrVecSrc_ = iConfig.getParameter<edm::InputTag>("genDecayStrVecSrc");
   genDecayChainPartIdxVecSrc_ = iConfig.getParameter<edm::InputTag>("genDecayChainPartIdxVecSrc");

   storeSMSmodelInfo_ = iConfig.getUntrackedParameter<bool>("storeSMSmodelInfo", false);
   smsModelFileNameStrSrc_ = iConfig.getParameter<edm::InputTag>("smsModelFileNameStrSrc");
   smsModelStrSrc_ = iConfig.getParameter<edm::InputTag>("smsModelStrSrc");
   smsModelMotherMassSrc_ = iConfig.getParameter<edm::InputTag>("smsModelMotherMassSrc");
   smsModelDaughterMassSrc_ = iConfig.getParameter<edm::InputTag>("smsModelDaughterMassSrc");

   genJetsInputTags_ = iConfig.getParameter<std::vector<edm::InputTag> >("genJetsInputTags");
   std::cout<<"genJetsInputTags_.size : "<<genJetsInputTags_.size()<<std::endl;

   if( doTopTagger_ ) topTaggerPtr = new topTagger::type3TopTagger();
 
   otherJetspt_TR = new std::vector<double>; otherJetseta_TR = new std::vector<double>; otherJetsphi_TR = new std::vector<double>; otherJetsenergy_TR = new std::vector<double>;
   otherMuspt_TR = new std::vector<double>; otherMuseta_TR = new std::vector<double>; otherMusphi_TR = new std::vector<double>;
   otherElespt_TR = new std::vector<double>; otherEleseta_TR = new std::vector<double>; otherElesphi_TR = new std::vector<double>;
   otherGenJetspt_TR = new std::vector<double>; otherGenJetseta_TR = new std::vector<double>; otherGenJetsphi_TR = new std::vector<double>; otherGenJetsenergy_TR = new std::vector<double>;
   otherJetsRes_TR = new std::vector<double>;

   recoJetsFlavor_TR = new std::vector<int>; genJetsFlavor_TR = new std::vector<int>;

   recoJetsBtag_TR.clear();
  
   for(size ib=0; ib<nbTagKeys; ib++){
      std::vector<double> dummyVec;
      recoJetsBtag_TR.push_back(dummyVec);
   }

   npv = -1; avg_npv = -1; nm1 = -1; n0 = -1; np1 = -1; tru_npv = -1;

// TLorentzVectors of generator level particles of the top decays
   gentopLVec_TR = new std::vector<TLorentzVector>; gentoppdgIdVec_TR = new std::vector<int>;
   gentopDausLVec_TR = new std::vector<std::vector<TLorentzVector> >; gentopDauspdgIdVec_TR = new std::vector<std::vector<int> >;
   genWDausLVec_TR = new std::vector<std::vector<TLorentzVector> >; genWDauspdgIdVec_TR = new std::vector<std::vector<int> >;
   gentauDausLVec_TR = new std::vector<std::vector<TLorentzVector> >; gentauDauspdgIdVec_TR = new std::vector<std::vector<int> >;
   decayTypeVec_TR = new std::vector<std::string>;

   jetsLVec_TR = new std::vector<TLorentzVector>;
   forVetoIsoTrksLVec_TR = new std::vector<TLorentzVector>(); forVetoIsoTrksAuxVec_TR = new std::vector<std::vector<double> >();
   forVetoIsoTrksConsMatchedJetIdxVec_TR = new std::vector<int>();

   muonsLVec_TR = new std::vector<TLorentzVector>; muonsAux_TR = new std::vector<double>;
   elesLVec_TR = new std::vector<TLorentzVector>; elesAux_TR = new std::vector<double>;

// For HepTopTagger
   hepTaggerJets_TR = new std::vector<TLorentzVector>;
   hepTaggerSubJets_TR = new std::vector<std::vector<TLorentzVector> >;

// For gen decay info
   genDecayStrVec_TR = new std::vector<std::string>;
   genDecayIdxVec_TR = new std::vector<int>; genDecayPdgIdVec_TR = new std::vector<int>; genDecayMomIdxVec_TR = new std::vector<int>;
   genDecayLVec_TR = new std::vector<TLorentzVector>;

// For SMS model info
   smsModelFileNameStr_TR = new std::vector<std::string>;
   smsModelStr_TR = new std::vector<std::string>;
   smsModelMotherMass_TR = -1; smsModelDaughterMass_TR = -1;

// For genjet collections
   genJetsLVec_TR.clear();
   for( unsigned int ig =0; ig<genJetsInputTags_.size(); ig++ ){
      std::vector<TLorentzVector> dummyLVec;
      genJetsLVec_TR.push_back(dummyLVec);
   }

   setTreeDefaultVars();

   edm::Service<TFileService> fs;

   if( doFillTree_ ){

      outTree = fs->make<TTree>("AUX", "aux info");
      outTree->Branch("run", &run, "run/I");
      outTree->Branch("event", &event, "event/I");
      outTree->Branch("lumi", &ls, "lumi/I");
      outTree->Branch("npv", &npv, "npv/I");
      outTree->Branch("avg_npv", &avg_npv, "avg_npv/D");
      outTree->Branch("nm1", &nm1, "nm1/I");
      outTree->Branch("n0", &n0, "n0/I");
      outTree->Branch("np1", &np1, "np1/I");
      outTree->Branch("tru_npv", &tru_npv, "tru_npv/D");
      outTree->Branch("vtxSize", &vtxSize, "vtxSize/I");
      outTree->Branch("nJets", &nJets, "nJets/I");
      outTree->Branch("nMuons", &nMuons, "nMuons/I");
      outTree->Branch("nMuons_CUT", &nMuonsForVeto, "nMuonsForVeto/I");
      outTree->Branch("nElectrons", &nElectrons, "nElectrons/I");
      outTree->Branch("nElectrons_CUT", &nElectronsForVeto, "nElectronsForVeto/I");
      outTree->Branch("nIsoTrks_CUT", &nIsoTrksForVeto, "nIsoTrksForVeto/I");
      outTree->Branch("evtWeight", &evtWeight_TR, "evtWeight/D");
      outTree->Branch("mht", &mht_TR, "mht/D");
      outTree->Branch("mht_forSgnf", &mht_forSgnf_TR, "mht_forSgnf/D");
      outTree->Branch("ht", &ht_TR, "ht/D");
      outTree->Branch("met", &met_TR, "met/D");
      outTree->Branch("type1met", &type1met_TR, "type1met/D");
      outTree->Branch("mt", &mt_TR, "mt/D");
      outTree->Branch("type1mt", &type1mt_TR, "type1mt/D");
      outTree->Branch("mhtphi", &mhtphi_TR, "mhtphi/D");
      outTree->Branch("mhtphi_forSgnf", &mhtphi_forSgnf_TR, "mhtphi_forSgnf/D");
      outTree->Branch("metphi", &metphi_TR, "metphi/D");
      outTree->Branch("metSgnf", &metSgnf_TR, "metSgnf/D");
      outTree->Branch("metSgnfProb", &metSgnfProb_TR, "metSgnfProb/D");
      outTree->Branch("type1metphi", &type1metphi_TR, "type1metphi/D");
      outTree->Branch("type1metSgnf", &type1metSgnf_TR, "type1metSgnf/D");
      outTree->Branch("type1metSgnfProb", &type1metSgnfProb_TR, "type1metSgnfProb/D");
      outTree->Branch("mhtSgnf", &mhtSgnf_TR, "mhtSgnf/D");
      outTree->Branch("mhtSgnfProb", &mhtSgnfProb_TR, "mhtSgnfProb/D");
      outTree->Branch("jetsLVec", "std::vector<TLorentzVector>", &jetsLVec_TR, 32000, 0);
      outTree->Branch("forVetoIsoTrksLVec", "std::vector<TLorentzVector>", &forVetoIsoTrksLVec_TR, 32000, 0);
      outTree->Branch("forVetoIsoTrksAuxVec", "std::vector<std::vector<double> >", &forVetoIsoTrksAuxVec_TR, 32000, 0);
      outTree->Branch("forVetoIsoTrksConsMatchedJetIdxVec", "std::vector<int>", &forVetoIsoTrksConsMatchedJetIdxVec_TR, 32000, 0);
      outTree->Branch("muonsLVec", "std::vector<TLorentzVector>", &muonsLVec_TR, 32000, 0);
      outTree->Branch("muonsAux", "std::vector<double>", &muonsAux_TR, 32000, 0);
      outTree->Branch("elesLVec", "std::vector<TLorentzVector>", &elesLVec_TR, 32000, 0);
      outTree->Branch("elesAux", "std::vector<double>", &elesAux_TR, 32000, 0);
      outTree->Branch("dPhi0_CUT", &dPhi0_CUT, "dPhi0_CUT/D"); 
      outTree->Branch("dPhi1_CUT", &dPhi1_CUT, "dPhi1_CUT/D"); 
      outTree->Branch("dPhi2_CUT", &dPhi2_CUT, "dPhi2_CUT/D");
      outTree->Branch("nJets_CUT", &nJets_CUT, "nJets_CUT/I");
    
      if( fillGenInfo_ ){
         outTree->Branch("genJet1pt", &genJet1pt_TR, "genJet1pt/D");
         outTree->Branch("genJet1eta", &genJet1eta_TR, "genJet1eta/D");
         outTree->Branch("genJet1phi", &genJet1phi_TR, "genJet1phi/D");
         outTree->Branch("genJet1energy", &genJet1energy_TR, "genJet1energy/D");
         outTree->Branch("genJet2pt", &genJet2pt_TR, "genJet2pt/D");
         outTree->Branch("genJet2eta", &genJet2eta_TR, "genJet2eta/D");
         outTree->Branch("genJet2phi", &genJet2phi_TR, "genJet2phi/D");
         outTree->Branch("genJet2energy", &genJet2energy_TR, "genJet2energy/D");
         outTree->Branch("genJet3pt", &genJet3pt_TR, "genJet3pt/D");
         outTree->Branch("genJet3eta", &genJet3eta_TR, "genJet3eta/D");
         outTree->Branch("genJet3phi", &genJet3phi_TR, "genJet3phi/D");
         outTree->Branch("genJet3energy", &genJet3energy_TR, "genJet3energy/D");
         outTree->Branch("otherGenJetspt", "std::vector<double>", &otherGenJetspt_TR, 32000, 0);
         outTree->Branch("otherGenJetseta", "std::vector<double>", &otherGenJetseta_TR, 32000, 0);
         outTree->Branch("otherGenJetsphi", "std::vector<double>", &otherGenJetsphi_TR, 32000, 0);
         outTree->Branch("otherGenJetsenergy", "std::vector<double>", &otherGenJetsenergy_TR, 32000, 0);
         outTree->Branch("genMET", &genMET_TR, "genMET/D");
         outTree->Branch("jet1Res", &jet1Res_TR, "jet1Res/D");
         outTree->Branch("jet2Res", &jet2Res_TR, "jet2Res/D");
         outTree->Branch("jet3Res", &jet3Res_TR, "jet3Res/D");
         outTree->Branch("otherJetsRes", "std::vector<double>", &otherJetsRes_TR, 32000, 0);
         outTree->Branch("genJetsFlavor", "std::vector<int>", &genJetsFlavor_TR, 32000, 0);
      }
      
      outTree->Branch("externalBit", &externalBitToTree_TR, "externalBitToTree_TR/I");

      outTree->Branch("recoJetsFlavor", "std::vector<int>", &recoJetsFlavor_TR, 32000, 0);

      outTree->Branch("bTagKeyString", "std::vector<std::string>", &bTagKeyString_, 32000, 0);
      char treeBranchNameStr[200];
      for(size ib=0; ib<nbTagKeys; ib++){
         sprintf(treeBranchNameStr, "recoJetsBtag_%d", ib);
         outTree->Branch(treeBranchNameStr, "std::vector<double>", &recoJetsBtag_TR[ib], 32000, 0);
      }

      if( doFillGenTopInfo_ ){
         outTree->Branch("gentopLVec", "std::vector<TLorentzVector>", &gentopLVec_TR, 32000, 0);
         outTree->Branch("gentoppdgIdVec", "std::vector<int>", &gentoppdgIdVec_TR, 32000, 0);
         outTree->Branch("gentopDausLVec", "std::vector<std::vector<TLorentzVector> >", &gentopDausLVec_TR, 32000, 0);
         outTree->Branch("gentopDauspdgIdVec", "std::vector<std::vector<int> >", &gentopDauspdgIdVec_TR, 32000, 0);
         outTree->Branch("genWDausLVec", "std::vector<std::vector<TLorentzVector> >", &genWDausLVec_TR, 32000, 0);
         outTree->Branch("genWDauspdgIdVec", "std::vector<std::vector<int> >", &genWDauspdgIdVec_TR, 32000, 0);
         outTree->Branch("gentauDausLVec", "std::vector<std::vector<TLorentzVector> >", &gentauDausLVec_TR, 32000, 0);
         outTree->Branch("gentauDauspdgIdVec", "std::vector<std::vector<int> >", &gentauDauspdgIdVec_TR, 32000, 0);
         outTree->Branch("decayTypeVec", "std::vector<std::string>", &decayTypeVec_TR, 32000, 0);
      }
      outTree->Branch("hepTaggerJets", "std::vector<TLorentzVector>", &hepTaggerJets_TR, 32000, 0);
      outTree->Branch("hepTaggerSubJets", "std::vector<std::vector<TLorentzVector> >", &hepTaggerSubJets_TR, 32000, 0);

      if( doTopTagger_ ){
        outTree->Branch("bestTopJetIdx", &bestTopJetIdx_TR, "bestTopJetIdx/I");
        outTree->Branch("pickedRemainingCombfatJetIdx", &pickedRemainingCombfatJetIdx_TR, "pickedRemainingCombfatJetIdx/I");
        outTree->Branch("remainPassCSVS", &remainPassCSVS_TR, "remainPassCSVS/O");
        outTree->Branch("bestTopJetMass", &bestTopJetMass_TR, "bestTopJetMass/D");
        outTree->Branch("mTbestTopJet", &mTbestTopJet_TR, "mTbestTopJet/D");
        outTree->Branch("mTbJet", &mTbJet_TR, "mTbJet/D");
        outTree->Branch("MT2", &MT2_TR, "MT2/D");
        outTree->Branch("mTbestWJet", &mTbestWJet_TR, "mTbestWJet/D");
        outTree->Branch("mTbestbJet", &mTbestbJet_TR, "mTbestbJet/D");
        outTree->Branch("mTremainingTopJet", &mTremainingTopJet_TR, "mTremainingTopJet/D");
     }
     
     if( storeGenDecayInfo_ ){
        outTree->Branch("genDecayStrVec", "std::vector<std::string>", &genDecayStrVec_TR, 32000, 0);
        outTree->Branch("genDecayIdxVec", "std::vector<int>", &genDecayIdxVec_TR, 32000, 0);
        outTree->Branch("genDecayMomIdxVec", "std::vector<int>", &genDecayMomIdxVec_TR, 32000, 0);
        outTree->Branch("genDecayPdgIdVec", "std::vector<int>", &genDecayPdgIdVec_TR, 32000, 0);
        outTree->Branch("genDecayLVec", "std::vector<TLorentzVector>", &genDecayLVec_TR, 32000, 0);

        for(unsigned int ig=0; ig<genJetsInputTags_.size(); ig++){
           sprintf(treeBranchNameStr, "genJetsLVec_%s", genJetsInputTags_[ig].label().c_str());
           std::cout<<"Declaring a tree branch with name : "<<treeBranchNameStr<<std::endl;
           outTree->Branch(treeBranchNameStr, "std::vector<TLorentzVector>", &genJetsLVec_TR[ig], 32000, 0);
        }
     }

     if( storeSMSmodelInfo_ ){
        outTree->Branch("smsModelFileNameStrVec", "std::vector<std::string>", &smsModelFileNameStr_TR, 32000, 0);
        outTree->Branch("smsModelStrVec", "std::vector<std::string>", &smsModelStr_TR, 32000, 0);
        outTree->Branch("smsModelMotherMass", &smsModelMotherMass_TR, "smsModelMotherMass/D");
        outTree->Branch("smsModelDaughterMass", &smsModelDaughterMass_TR, "smsModelDaughterMass/D");
     }
   }
}

histAndTree::~histAndTree() {

}

void histAndTree::setTreeDefaultVars(){

   evtWeight_TR = 1.0;
   mht_TR= -99, ht_TR= -99, met_TR= -99, mt_TR= -99, type1mt_TR = -99, type1met_TR = -99;
   mhtphi_TR= -99, metphi_TR= -99, type1metphi_TR = -99;
   metSgnf_TR= -99, metSgnfProb_TR= -99, type1metSgnf_TR= -99, type1metSgnfProb_TR= -99;
   mht_forSgnf_TR = -99, mhtphi_forSgnf_TR = -99;
   mhtSgnf_TR= -99, mhtSgnfProb_TR= -99;
   jet1pt_TR= -99, jet1eta_TR= -99, jet1phi_TR= -99, jet1energy_TR= -99;
   jet2pt_TR= -99, jet2eta_TR= -99, jet2phi_TR= -99, jet2energy_TR= -99;
   jet3pt_TR= -99, jet3eta_TR= -99, jet3phi_TR= -99, jet3energy_TR= -99;
   otherJetspt_TR->clear(); otherJetseta_TR->clear(); otherJetsphi_TR->clear(); otherJetsenergy_TR->clear();
   jetsLVec_TR->clear();
   forVetoIsoTrksLVec_TR->clear(); forVetoIsoTrksAuxVec_TR->clear(); forVetoIsoTrksConsMatchedJetIdxVec_TR->clear();

   bestTopJetIdx_TR = -99; pickedRemainingCombfatJetIdx_TR = -99;
   remainPassCSVS_TR = false;
   bestTopJetMass_TR =-99; mTbestTopJet_TR =-99; mTbJet_TR =-99; MT2_TR =-99; mTbestWJet_TR =-99; mTbestbJet_TR =-99; mTremainingTopJet_TR = -99;
 
   mu1pt_TR= -99, mu1eta_TR= -99, mu1phi_TR= -99;
   mu2pt_TR= -99, mu2eta_TR= -99, mu2phi_TR= -99;
   otherMuspt_TR->clear(); otherMuseta_TR->clear(); otherMusphi_TR->clear();
   ele1pt_TR= -99, ele1eta_TR= -99, ele1phi_TR= -99;
   ele2pt_TR= -99, ele2eta_TR= -99, ele2phi_TR= -99;
   otherElespt_TR->clear(); otherEleseta_TR->clear(); otherElesphi_TR->clear();

   muonsLVec_TR->clear(); elesLVec_TR->clear();
   muonsAux_TR->clear(); elesAux_TR->clear();

   dPhi0_CUT = -99, dPhi1_CUT = -99, dPhi2_CUT = -99;
   nJets_CUT = -99;

   genJet1pt_TR= -99, genJet1eta_TR= -99, genJet1phi_TR= -99, genJet1energy_TR= -99;
   genJet2pt_TR= -99, genJet2eta_TR= -99, genJet2phi_TR= -99, genJet2energy_TR= -99;
   genJet3pt_TR= -99, genJet3eta_TR= -99, genJet3phi_TR= -99, genJet3energy_TR= -99;
   otherGenJetspt_TR->clear(); otherGenJetseta_TR->clear(); otherGenJetsphi_TR->clear(); otherGenJetsenergy_TR->clear();
   genMET_TR = -99;
   jet1Res_TR = -99, jet2Res_TR = -99, jet3Res_TR = -99;
   otherJetsRes_TR->clear();
   externalBitToTree_TR = -99;

   npv = -1; avg_npv = -1; nm1 = -1; n0 = -1; np1 = -1; tru_npv = -1;

   recoJetsFlavor_TR->clear(); genJetsFlavor_TR->clear();
   for(size ib=0; ib<nbTagKeys; ib++){
      recoJetsBtag_TR[ib].clear();
   }

   gentopLVec_TR->clear(); gentoppdgIdVec_TR->clear();
   gentopDausLVec_TR->clear(); gentopDauspdgIdVec_TR->clear();
   genWDausLVec_TR->clear(); genWDauspdgIdVec_TR->clear();
   gentauDausLVec_TR->clear(); gentauDauspdgIdVec_TR->clear();
   decayTypeVec_TR->clear();

   hepTaggerJets_TR->clear(); hepTaggerSubJets_TR->clear();

   genDecayStrVec_TR->clear();
   genDecayIdxVec_TR->clear(); genDecayPdgIdVec_TR->clear(); genDecayMomIdxVec_TR->clear();
   genDecayLVec_TR->clear();

   smsModelFileNameStr_TR->clear();
   smsModelStr_TR->clear();
   smsModelMotherMass_TR = -1; smsModelDaughterMass_TR = -1;

   for( unsigned int ig =0; ig<genJetsInputTags_.size(); ig++ ){
      genJetsLVec_TR[ig].clear();
   }
}

// ------------ method called on each new Event  ------------
bool histAndTree::filter(edm::Event& iEvent, const edm::EventSetup& iSetup) {

   setTreeDefaultVars();

//   iSetup.getData( pdt_ );

// Event setup
   loadEventInfo(iEvent, iSetup);

   loadGenInfo(iEvent);
   loadRecoJets(iEvent);
   loadLeptons(iEvent);
   loadMETMHT(iEvent);
   loadHT(iEvent);
   loadAUX(iEvent); if( externalBitToTree_.isValid() ) externalBitToTree_TR = (*externalBitToTree_);

   if( doFillGenTopInfo_ ) fillGenDecayInfo(iEvent);

   if( nLeptonsSels_.size() <2 ){ std::cout<<"\nERROR ... input nLeptonsSels_.size : "<<nLeptonsSels_.size()<<"  less than 2?!"<<std::endl; } 

// If muons or electrons are not the size we require, don't go further
   if( (nLeptonsSels_[0] !=-1 && (int)nMuonsForVeto != nLeptonsSels_[0]) || (nLeptonsSels_[1] !=-1 && (int)nElectronsForVeto != nLeptonsSels_[1]) ){
      if( debug_ ){
         std::cout<<"nMuonsForVeto : "<<nMuonsForVeto<<"  nElectronsForVeto : "<<nElectronsForVeto<<std::endl;
         std::cout<<"nLeptonsSels_[0] : "<<nLeptonsSels_[0]<<"  nLeptonsSels_[1] : "<<nLeptonsSels_[1]<<std::endl;
      }
      return true;
   }

// Selection requirement of jets can be decided by the input jet collection.
   for(unsigned int is=0; is<nIsoTrksForVeto; is++){
      const reco::PFCandidate isoTrk = (*forVetoIsoTrks)[is];
      double isoTrkpt = isoTrk.pt(), isoTrketa = isoTrk.eta(), isoTrkphi = isoTrk.phi(), isoTrkenergy = isoTrk.energy();
      double isoTrkcharge = isoTrk.charge();

      if( isoTrkpt != isoTrkpt ){ std::cout<<"\nSkipping an isolated track where isoTrkpt : "<<isoTrkpt<<" is BAD!"<<std::endl<<std::endl; continue; }

      TLorentzVector perIsoTrkLVec;
      perIsoTrkLVec.SetPtEtaPhiE(isoTrkpt, isoTrketa, isoTrkphi, isoTrkenergy);
      forVetoIsoTrksLVec_TR->push_back(perIsoTrkLVec);

      std::vector<double> perAuxVec;
      perAuxVec.push_back(isoTrkcharge);
      forVetoIsoTrksAuxVec_TR->push_back(perAuxVec);

      int perIsoTrksConsMatchedJetIdx = getConsMatchedJetIdx((*patjets), perIsoTrkLVec, isoTrkcharge, minDRcutForConsMatch_);
      forVetoIsoTrksConsMatchedJetIdxVec_TR->push_back(perIsoTrksConsMatchedJetIdx);
   }

   evtWeight_TR = (*evtWeight_);

   double sgnfMET =0, probMET =0;
   double sgnfType1MET =0, probType1MET =0;
   double sgnfMHT =0, probMHT =0;
   if( doSgnf_ ){ 
      sgnfMET = (*met)[0].significance(); probMET = TMath::Prob(sgnfMET, sgnfnDof); 
      sgnfType1MET = (*type1met)[0].significance(); probType1MET = TMath::Prob(sgnfType1MET, sgnfnDof); 
      sgnfMHT = (*mht_forSgnf)[0].significance(); probMHT = TMath::Prob(sgnfMHT, sgnfnDof); 
   }

   double mtw = -1, type1mtw = -1;
   if( nMuons == 1 ){
      mtw = sqrt( 2*( (*met)[0].pt()*muon1.pt() -( (*met)[0].px()*muon1.px() + (*met)[0].py()*muon1.py() ) ) ); 
      type1mtw = sqrt( 2*( (*type1met)[0].pt()*muon1.pt() -( (*type1met)[0].px()*muon1.px() + (*type1met)[0].py()*muon1.py() ) ) ); 
   }
   if( nMuons ==2 && muon1Charge*muon2Charge == -1 ){
      mtw = sqrt( 2*( muon2.pt()*muon1.pt() -( muon2.px()*muon1.px() + muon2.py()*muon1.py() ) ) );
      type1mtw = sqrt( 2*( muon2.pt()*muon1.pt() -( muon2.px()*muon1.px() + muon2.py()*muon1.py() ) ) );
   }

   mht_TR = (*mht)[0].pt(); ht_TR = (*ht); met_TR = (*met)[0].pt(); type1met_TR = (*type1met)[0].pt(); mt_TR = mtw; type1mt_TR = type1mtw;
   mhtphi_TR = (*mht)[0].phi(); metphi_TR = (*met)[0].phi(); type1metphi_TR = (*type1met)[0].phi();
   metSgnf_TR = sgnfMET; metSgnfProb_TR = probMET;
   type1metSgnf_TR = sgnfType1MET; type1metSgnfProb_TR = probType1MET;
   mhtSgnf_TR = sgnfMHT; mhtSgnfProb_TR = probMHT;
   mht_forSgnf_TR = (*mht_forSgnf)[0].pt(); mhtphi_forSgnf_TR = (*mht_forSgnf)[0].phi();

   if( !isData && fillGenInfo_ ){
      genMET_TR = (*genMET)[0].pt();
      for(size ig=0; ig<nGenJets; ig++){
         if( ig ==0 ){
            genJet1 = (*genJets)[ig];
            genJet1pt_TR = genJet1.pt(); genJet1eta_TR = genJet1.eta(); genJet1phi_TR = genJet1.phi(); genJet1energy_TR = genJet1.energy();
         }
         if( ig ==1 ){
            genJet2 = (*genJets)[ig];
            genJet2pt_TR = genJet2.pt(); genJet2eta_TR = genJet2.eta(); genJet2phi_TR = genJet2.phi(); genJet2energy_TR = genJet2.energy();
         }
         if( ig ==2 ){
            genJet3 = (*genJets)[ig];
            genJet3pt_TR = genJet3.pt(); genJet3eta_TR = genJet3.eta(); genJet3phi_TR = genJet3.phi(); genJet3energy_TR = genJet3.energy();
         }
         if( ig >2 ){
            genJetother = (*genJets)[ig];
            otherGenJetspt_TR->push_back(genJetother.pt()); otherGenJetseta_TR->push_back(genJetother.eta()); otherGenJetsphi_TR->push_back(genJetother.phi()); otherGenJetsenergy_TR->push_back(genJetother.energy());
         }
      }   
   }

   for(size ij=0; ij<nJets; ij++){
      if( !isData && fillGenInfo_ ){
         double jeteta = (*jets)[ij].eta(), jetphi = (*jets)[ij].phi(), jetpt = (*jets)[ij].pt();
         double minDR = 999.0, jetRes = -999.0;
         for(size ig=0; ig<nGenJets; ig++){
            double genjeteta = (*genJets)[ig].eta(), genjetphi = (*genJets)[ig].phi(), genjetpt = (*genJets)[ig].pt();
            const double dR = reco::deltaR(jeteta, jetphi, genjeteta, genjetphi);
            if( minDR > dR ){ minDR = dR; jetRes = jetpt/genjetpt; }
         }
         if( minDR < recoGenJetsDR_ ){
            if( ij == 0 ){
               jet1Res_TR = jetRes;
            }
            if( ij == 1 ){
               jet2Res_TR = jetRes;
            }
            if( ij == 2 ){
               jet3Res_TR = jetRes;
            }
            if( ij > 2 ){
               otherJetsRes_TR->push_back(jetRes);
            }
         }
      }
      TLorentzVector perJetLVec;
      perJetLVec.SetPtEtaPhiE( (*jets)[ij].pt(), (*jets)[ij].eta(), (*jets)[ij].phi(), (*jets)[ij].energy() );
      jetsLVec_TR->push_back(perJetLVec);

      if( ij ==0 ){
         jet1 = (*jets)[ij];
         jet1pt_TR = jet1.pt(); jet1eta_TR = jet1.eta(); jet1phi_TR = jet1.phi(); jet1energy_TR = jet1.energy();
      }
      if( ij ==1 ){
         jet2 = (*jets)[ij];
         jet2pt_TR = jet2.pt(); jet2eta_TR = jet2.eta(); jet2phi_TR = jet2.phi(); jet2energy_TR = jet2.energy();
      }
      if( ij ==2 ){
         jet3 = (*jets)[ij]; 
         jet3pt_TR = jet3.pt(); jet3eta_TR = jet3.eta(); jet3phi_TR = jet3.phi(); jet3energy_TR = jet3.energy();
      }
      if( ij > 2 ){
         jetother = (*jets)[ij];
         otherJetspt_TR->push_back(jetother.pt()); otherJetseta_TR->push_back(jetother.eta()); otherJetsphi_TR->push_back(jetother.phi()); otherJetsenergy_TR->push_back(jetother.energy());
      }
   }

   if( isPatJet ){
      for(size ij=0; ij<nJets; ij++){
         const pat::Jet& jet = (*patjets)[ij];
         int flavor = jet.partonFlavour();
         recoJetsFlavor_TR->push_back(flavor);
        
         for(size ib=0; ib<nbTagKeys; ib++){
            double btag = jet.bDiscriminator(bTagKeyString_[ib].c_str());
            recoJetsBtag_TR[ib].push_back(btag);
         }
      }
   }

   if( doTopTagger_ ){

      std::vector<TLorentzVector> oriJetsVec;
      std::vector<double> recoJetsBtagCSVS;
      for(unsigned int ij=0; ij<jetsLVec_TR->size(); ij++){
         double jetEta = jetsLVec_TR->at(ij).Eta(), jetPt = jetsLVec_TR->at(ij).Pt();
         if( maxJetEtaCutForTopTagger_ != -1 && fabs(jetEta) >= maxJetEtaCutForTopTagger_ ) continue;
         if( minJetPtCutForTopTagger_ != -1 && jetPt <= minJetPtCutForTopTagger_ ) continue;
         oriJetsVec.push_back( jetsLVec_TR->at(ij) );
         recoJetsBtagCSVS.push_back( recoJetsBtag_TR.at(0)[ij] );
      }

      TLorentzVector metLVec; metLVec.SetPtEtaPhiM( met_TR, 0, metphi_TR, 0);

      bool passTopTagger = topTaggerPtr->processEvent(oriJetsVec, recoJetsBtagCSVS, metLVec);
      if( passTopTagger ){/*empty to avoid a compiling error*/}

      bestTopJetIdx_TR = topTaggerPtr->bestTopJetIdx; pickedRemainingCombfatJetIdx_TR = topTaggerPtr->pickedRemainingCombfatJetIdx;
      remainPassCSVS_TR = topTaggerPtr->remainPassCSVS;
      bestTopJetMass_TR = topTaggerPtr->bestTopJetMass;
      mTbestTopJet_TR = topTaggerPtr->mTbestTopJet;
      mTbJet_TR = topTaggerPtr->mTbJet;
      MT2_TR = topTaggerPtr->MT2;
      mTbestWJet_TR = topTaggerPtr->mTbestWJet;
      mTbestbJet_TR = topTaggerPtr->mTbestbJet;
      mTremainingTopJet_TR = topTaggerPtr->mTremainingTopJet;

   }

   if( storeGenDecayInfo_ ){
      iEvent.getByLabel(genDecayStrVecSrc_, genDecayStrVec_);
      for(unsigned int id=0; id<genDecayStrVec_->size(); id++){
         genDecayStrVec_TR->push_back( (*genDecayStrVec_)[id] );
      }

      iEvent.getByLabel(genDecayChainPartIdxVecSrc_, genDecayChainPartIdxVec_);
      for(unsigned int id=0; id<genDecayChainPartIdxVec_->size(); id++){
         int idxGen = (*genDecayChainPartIdxVec_)[id];
         const reco::GenParticle& genPart = genParticles->at(idxGen);
         TLorentzVector genPartLVec;
         genPartLVec.SetPtEtaPhiE(genPart.pt(), genPart.eta(), genPart.phi(), genPart.energy());
         int pdgId = genPart.pdgId();

         int momIdx = -1;
         if( genPart.numberOfMothers() >0 ){
            momIdx = find_idx( * (genPart.mother()) );
         }

         genDecayIdxVec_TR->push_back(idxGen);
         genDecayMomIdxVec_TR->push_back(momIdx);
         genDecayPdgIdVec_TR->push_back(pdgId);
         genDecayLVec_TR->push_back(genPartLVec);
      }

      for(unsigned int ig=0; ig<genJetsInputTags_.size(); ig++){
         edm::Handle<edm::View<reco::GenJet > > perGenJets;
         iEvent.getByLabel(genJetsInputTags_[ig], perGenJets);
         for(unsigned int ip=0; ip<perGenJets->size(); ip++){
            TLorentzVector perGenJetLVec;
            perGenJetLVec.SetPtEtaPhiE((*perGenJets)[ip].pt(), (*perGenJets)[ip].eta(), (*perGenJets)[ip].phi(), (*perGenJets)[ip].energy());
            genJetsLVec_TR[ig].push_back(perGenJetLVec);
         }
      }
   }
  
   if( storeSMSmodelInfo_ ){
      iEvent.getByLabel(smsModelFileNameStrSrc_, smsModelFileNameStrVec_);
      iEvent.getByLabel(smsModelStrSrc_, smsModelStrVec_);
      iEvent.getByLabel(smsModelMotherMassSrc_, smsModelMotherMass_);
      iEvent.getByLabel(smsModelDaughterMassSrc_, smsModelDaughterMass_);
      for(unsigned int is=0; is<smsModelFileNameStrVec_->size(); is++){
         smsModelFileNameStr_TR->push_back((*smsModelFileNameStrVec_)[is]);
      }
      for(unsigned int is=0; is<smsModelStrVec_->size(); is++){
         smsModelStr_TR->push_back((*smsModelStrVec_)[is]);
      }
      smsModelMotherMass_TR = (*smsModelMotherMass_);
      smsModelDaughterMass_TR = (*smsModelDaughterMass_);
   }

   if( HEPTopTaggedCandidateHandle.isValid() ){

      for(size_t i = 0; i < HEPTopTaggedCandidateHandle->size(); ++i){
         reco::BasicJetRef itJet (HEPTopTaggedCandidateHandle, i);

         TLorentzVector perJetLVec;
         perJetLVec.SetPtEtaPhiE(itJet->pt(), itJet->eta(), itJet->phi(), itJet->energy());
         hepTaggerJets_TR->push_back(perJetLVec);

         reco::Jet::Constituents subjets = itJet->getJetConstituents();

         sort(subjets.begin(), subjets.end(), GreaterByPtCandPtr()); //Sort them by pt
         
         std::vector<TLorentzVector> subJetsVec;

         for(size_t is=0; is<subjets.size(); is++){
            TLorentzVector persubJetLVec;
            persubJetLVec.SetPtEtaPhiE(subjets[is]->p4().pt(), subjets[is]->p4().eta(), subjets[is]->p4().phi(), subjets[is]->p4().energy());
            subJetsVec.push_back(persubJetLVec);
         }
         hepTaggerSubJets_TR->push_back(subJetsVec);
      }
   }

   for(size im=0; im<nMuons; im++){
      TLorentzVector perMuonLVec;
      perMuonLVec.SetPtEtaPhiE( (*muons)[im].pt(), (*muons)[im].eta(), (*muons)[im].phi(), (*muons)[im].energy() );
      muonsLVec_TR->push_back(perMuonLVec);
      muonsAux_TR->push_back( (*muons)[im].charge() );

      if( im == 0){
         mu1pt_TR = muon1.pt(); mu1eta_TR = muon1.eta(); mu1phi_TR = muon1.phi();
      }
      if( im == 1){
         mu2pt_TR = muon2.pt(); mu2eta_TR = muon2.eta(); mu2phi_TR = muon2.phi();
      }
      if( im >1 ){
         otherMuspt_TR->push_back((*muons)[im].pt()); otherMuseta_TR->push_back((*muons)[im].eta()); otherMusphi_TR->push_back((*muons)[im].phi());
      }
   }

   for(size ie=0; ie<nElectrons; ie++){
      TLorentzVector perEleLVec;
      perEleLVec.SetPtEtaPhiE( (*electrons)[ie].pt(), (*electrons)[ie].eta(), (*electrons)[ie].phi(), (*electrons)[ie].energy() );
      elesLVec_TR->push_back(perEleLVec);
      elesAux_TR->push_back( (*electrons)[ie].charge() );

      if( ie == 0){
         ele1pt_TR = ele1.pt(); ele1eta_TR = ele1.eta(); ele1phi_TR = ele1.phi();
      }
      if( ie == 1){
         ele2pt_TR = ele2.pt(); ele2eta_TR = ele2.eta(); ele2phi_TR = ele2.phi();
      }
      if( ie >1 ){
         otherElespt_TR->push_back((*electrons)[ie].pt()); otherEleseta_TR->push_back((*electrons)[ie].eta()); otherElesphi_TR->push_back((*electrons)[ie].phi());
      }
   }

   if( doFillTree_ ){
      dPhi0_CUT = (*dPhis_CUT_vec_)[0]; dPhi1_CUT = (*dPhis_CUT_vec_)[1]; dPhi2_CUT = (*dPhis_CUT_vec_)[2];
      nJets_CUT = (*nJets_CUT_);
      outTree->Fill(); 
   }

   return true;

}

// ------------ method called once each job just before starting event loop  ------------
void histAndTree::beginJob() {
}

// ------------ method called once each job just after ending the event loop  ------------
void histAndTree::endJob() {
}

// ------------ method called once each run just before starting event loop  ------------
bool histAndTree::beginRun(edm::Run &run, const edm::EventSetup& iSetup) {
  return true;
}

// ------------ method called once each run just after starting event loop  ------------
bool histAndTree::endRun(edm::Run &run, const edm::EventSetup& iSetup) {
  return true;
}


void histAndTree::loadEventInfo(const edm::Event& iEvent, const edm::EventSetup& iSetup){

// Determine if it's data
   if( !iEvent.isRealData() ) isData = false;

// Get run, event, lumi info
   run = iEvent.id().run();
   event = iEvent.id().event();
   ls = iEvent.luminosityBlock();

// Get vertices
   iEvent.getByLabel(vtxSrc_, vertices); vtxSize = vertices->size();
   
// Get event weight
   iEvent.getByLabel(evtWeightInput_, evtWeight_);

}

void histAndTree::loadGenInfo(const edm::Event& iEvent){

// MC generate level related info
   scalePDF = -1; pthat = -1;
   if (!isData) {
      edm::Handle<edm::HepMCProduct> evt;
      edm::Handle< GenEventInfoProduct > GenInfoHandle;

      iEvent.getByLabel("generator", evt);
      if (evt.isValid()) {
         HepMC::GenEvent * myGenEvent = new HepMC::GenEvent(*(evt->GetEvent()));
         scalePDF = myGenEvent->event_scale();
         if( myGenEvent ) delete myGenEvent;
      }

      iEvent.getByLabel( "generator", GenInfoHandle );
      if (GenInfoHandle.isValid()) { pthat = ( GenInfoHandle->hasBinningValues() ? (GenInfoHandle->binningValues())[0] : 0.0); }

      iEvent.getByLabel(genParticleSrc_, genParticles);
      iEvent.getByLabel(genJetSrc_, genJets); nGenJets = genJets->size();
      iEvent.getByLabel(genMETSrc_, genMET); 

      iEvent.getByLabel(edm::InputTag("addPileupInfo"), PupInfo);
      std::vector<PileupSummaryInfo>::const_iterator PVI;

      npv = -1; avg_npv = 0; nm1 = -1; n0 = -1; np1 = -1; tru_npv = -1;
      for(PVI = PupInfo->begin(); PVI != PupInfo->end(); ++PVI) {

         int BX = PVI->getBunchCrossing();

         avg_npv += double(PVI->getPU_NumInteractions());

         if(BX == -1) { 
            nm1 = PVI->getPU_NumInteractions();
         }
         if(BX == 0) { 
            n0 = PVI->getPU_NumInteractions();
         }
         if(BX == 1) { 
            np1 = PVI->getPU_NumInteractions();
         }

         if(BX == 0) {
            npv = PVI->getPU_NumInteractions();
            tru_npv = PVI->getTrueNumInteractions();
            continue; // No touching of this "continue", since I'm not sure why it's here originally
         }
      }
      avg_npv /= 3.0;
   }
}

void histAndTree::loadRecoJets(const edm::Event& iEvent){
   iEvent.getByLabel(jetSrc_, jets); nJets = jets->size();

   isPatJet = false;
   edm::ProductID jetProdID = jets.id();
   const edm::Provenance & jetProv = iEvent.getProvenance(jetProdID);
   const std::string jetclassName = jetProv.className();
   TString jetclassNameT(jetclassName);
   if( jetclassNameT.Contains("pat::Jet") ) isPatJet = true;

   if( isPatJet ) iEvent.getByLabel(jetSrc_, patjets);
   
   iEvent.getByLabel(hepTaggerJetSrc_, HEPTopTaggedCandidateHandle);
}

void histAndTree::loadLeptons(const edm::Event& iEvent){
   iEvent.getByLabel(muonSrc_, muons); nMuons = muons->size();
   iEvent.getByLabel(eleSrc_, electrons); nElectrons = electrons->size();
//   iEvent.getByLabel(tauSrc_, taus); nTaus = taus->size();
   iEvent.getByLabel(forVetoMuonSrc_, forVetoMuons); nMuonsForVeto = forVetoMuons->size();
   iEvent.getByLabel(forVetoElectronSrc_, forVetoElectrons); nElectronsForVeto = forVetoElectrons->size();
   iEvent.getByLabel(forVetoIsoTrkSrc_, forVetoIsoTrks); if( forVetoIsoTrks.isValid() ) nIsoTrksForVeto = forVetoIsoTrks->size(); else nIsoTrksForVeto =0;

   for( size im=0; im<nMuons; im++){
      if( im ==0 ){ muon1 = (*muons)[im]; muon2 = (*muons)[im]; }
      if( im ==1 ) muon2 = (*muons)[im];
   }

   muon1Charge = muon1.charge(); muon2Charge = muon2.charge();

   for( size ie=0; ie<nElectrons; ie++){
      if( ie ==0 ){ ele1 = (*electrons)[ie]; ele2 = (*electrons)[ie]; }
      if( ie ==1 ) ele2 = (*electrons)[ie];
   }

   ele1Charge = ele1.charge(); ele2Charge = ele2.charge();

}

void histAndTree::loadPhotons(const edm::Event& iEvent){
   iEvent.getByLabel(photonSrc_, photons); nPhotons = photons->size();
}

void histAndTree::loadMETMHT(const edm::Event& iEvent){
   iEvent.getByLabel(metSrc_, met);
   iEvent.getByLabel(type1metSrc_, type1met);
   iEvent.getByLabel(mhtSrc_, mht);
   iEvent.getByLabel(mht_forSgnfSrc_, mht_forSgnf);
}

void histAndTree::loadHT(const edm::Event& iEvent){
   iEvent.getByLabel(htSrc_, ht);
}

void histAndTree::loadAUX(const edm::Event& iEvent){
   iEvent.getByLabel(dPhis_CUT_vec_Src_, dPhis_CUT_vec_);
   iEvent.getByLabel(nJets_CUT_Src_, nJets_CUT_);

   iEvent.getByLabel(externalBitToTree_Src_, externalBitToTree_);
}

void histAndTree::fillGenDecayInfo(const edm::Event& iEvent){
   if( !isData ){

      iEvent.getByLabel(gentopIdxVecSrc_, gentopIdxVec_);
      iEvent.getByLabel(gentopDausIdxVecSrc_, gentopDausIdxVec_);
      iEvent.getByLabel(genWDausIdxVecSrc_, genWDausIdxVec_);
      iEvent.getByLabel(gentauDausIdxVecSrc_, gentauDausIdxVec_);
      iEvent.getByLabel(decayTypeVecSrc_, decayTypeVec_);

      unsigned int nGentops = gentopIdxVec_->size();
      for(unsigned int it=0; it<nGentops; it++){
         int gentopIdx = (*gentopIdxVec_)[it];
         const reco::GenParticle& gentop = genParticles->at(gentopIdx);
         TLorentzVector gentopLVec;
         gentopLVec.SetPtEtaPhiE(gentop.pt(), gentop.eta(), gentop.phi(), gentop.energy());

         vector<TLorentzVector> gentopDausLVec, genWDausLVec, gentauDausLVec;
         vector<int> gentopDauspdgIdVec, genWDauspdgIdVec, gentauDauspdgIdVec;
         for(unsigned int itd=0; itd<(*gentopDausIdxVec_)[it].size(); itd++){
            int gentopDausIdx = (*gentopDausIdxVec_)[it][itd];
            const reco::GenParticle &gentopDau = genParticles->at(gentopDausIdx);
            TLorentzVector perLVec;
            perLVec.SetPtEtaPhiE(gentopDau.pt(), gentopDau.eta(), gentopDau.phi(), gentopDau.energy());

            gentopDausLVec.push_back(perLVec);
            gentopDauspdgIdVec.push_back(gentopDau.pdgId());
         }
         for(unsigned int iwd=0; iwd<(*genWDausIdxVec_)[it].size(); iwd++){
            int genWDausIdx = (*genWDausIdxVec_)[it][iwd];
            const reco::GenParticle &genWDau = genParticles->at(genWDausIdx);
            TLorentzVector perLVec;
            perLVec.SetPtEtaPhiE(genWDau.pt(), genWDau.eta(), genWDau.phi(), genWDau.energy());

            genWDausLVec.push_back(perLVec);
            genWDauspdgIdVec.push_back(genWDau.pdgId());
         }
         for(unsigned int itd=0; itd<(*gentauDausIdxVec_)[it].size(); itd++){
            int gentauDausIdx = (*gentauDausIdxVec_)[it][itd];
            const reco::GenParticle &gentauDau = genParticles->at(gentauDausIdx);
            TLorentzVector perLVec;
            perLVec.SetPtEtaPhiE(gentauDau.pt(), gentauDau.eta(), gentauDau.phi(), gentauDau.energy());

            gentauDausLVec.push_back(perLVec);
            gentauDauspdgIdVec.push_back(gentauDau.pdgId());
         }
         gentopLVec_TR->push_back(gentopLVec); gentoppdgIdVec_TR->push_back(gentop.pdgId());
         gentopDausLVec_TR->push_back(gentopDausLVec); gentopDauspdgIdVec_TR->push_back(gentopDauspdgIdVec);
         genWDausLVec_TR->push_back(genWDausLVec); genWDauspdgIdVec_TR->push_back(genWDauspdgIdVec);
         gentauDausLVec_TR->push_back(gentauDausLVec); gentauDauspdgIdVec_TR->push_back(gentauDauspdgIdVec);
         decayTypeVec_TR->push_back((*decayTypeVec_)[it]);
      }
   }
}

int histAndTree::getConsMatchedJetIdx(const std::vector<pat::Jet> & patjets, const TLorentzVector tomatchLVec, const double tomatchCharge, const double minDRcut){

   int consMatchedJetsIdx = -1;
   double tomatchEta = tomatchLVec.Eta(), tomatchPhi = tomatchLVec.Phi();
   for(int ij=0; ij<(int)patjets.size(); ij++){

      const std::vector<reco::PFCandidatePtr> & constituents = patjets[ij].getPFConstituents();
      const unsigned int numConstituents = constituents.size();

      double minDRCon = 999.; int selConIdx = -1;
      for (unsigned int iCon = 0; iCon < numConstituents; ++iCon){
         const reco::PFCandidatePtr& constituent = constituents[iCon];
         if( constituent->charge() != tomatchCharge ) continue;
         const double tomatchDR = reco::deltaR(constituent->eta(), constituent->phi(), tomatchEta, tomatchPhi);
         if( minDRCon > tomatchDR ){
            minDRCon = tomatchDR;
            selConIdx = (int)iCon;
         }
      }
      if( selConIdx ){/*empty to avoid a compiling error*/}

      if( minDRCon < minDRcut ){
         consMatchedJetsIdx = ij;
         break;
      }
   }

   return consMatchedJetsIdx;
}

int histAndTree::find_idx(const reco::Candidate & target){
   int pickedIdx = -1;
   for(size_t ig=0; ig<genParticles->size(); ig++){
      const reco::GenParticle& gen = genParticles->at(ig);
      if( target.p4() == gen.p4() && target.vertex() == gen.vertex() && target.charge() == gen.charge() ){
         pickedIdx = (int)ig;
         break;
      }
   }
   return pickedIdx;
}

#include "FWCore/Framework/interface/MakerMacros.h"
//define this as a plug-in
DEFINE_FWK_MODULE(histAndTree);
