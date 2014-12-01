//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Dec  1 15:47:36 2014 by ROOT version 5.34/10
// from TTree AUX/aux info
// found on file: stdStopHistAndTree.root.dR.0.5.T1tttt.no.ak5
//////////////////////////////////////////////////////////

#ifndef aux_h
#define aux_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include <vector>
#include <vector>
#include <vector>
#include <vector>

// Fixed size dimensions of array or collections stored in the TTree if any.

class aux {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Int_t           run; // run number
   Int_t           event; // event number
   Int_t           lumi; // lumi number
   Int_t           npv; // number of interations in BX=0
   Double_t        avg_npv; // averaged number of interactions in BX=-1, 0, 1
   Int_t           nm1; // number of interactions in BX=-1
   Int_t           n0; // // number of interactions in BX=0
   Int_t           np1; // number of interactions in BX=1
   Double_t        tru_npv; // true number of interactions
   Int_t           vtxSize; // number of vertices
   Int_t           nJets; // number of jets in the input jet collection (please check pt, eta of the input jets)
   Int_t           nMuons; // number of muons in the input muon collection (currently same as nMuons_CUT)
   Int_t           nMuons_CUT; // number of isolated/ID muons (can be used for veto)
   Int_t           nElectrons; // number of electrons in the input electron collection (currently same as nElectrons_CUT)
   Int_t           nElectrons_CUT; // number of isolated/ID electrons (can be used for veto)
   Int_t           nIsoTrks; // number of LOOSE isolated tracks (check input collection for criteria)
   Int_t           nIsoTrks_CUT; // number of default isolated tracks (can be used for veto)
   Double_t        evtWeight; // default is 1.0
   Double_t        mht; // mht (external input, please check what are used to calculate it) 
   Double_t        mht_forSgnf;
   Double_t        ht; // ht (external input, please check what are used to calculate it)
   Double_t        met; // missing transverse momentum (same as type1met as of now)
   Double_t        type1met;
   Double_t        mt; // dis-functioned
   Double_t        type1mt; // ditto
   Double_t        mhtphi;
   Double_t        mhtphi_forSgnf;
   Double_t        metphi; // phi of MET
   Double_t        metSgnf; // 
   Double_t        metSgnfProb;
   Double_t        type1metphi;
   Double_t        type1metSgnf;
   Double_t        type1metSgnfProb;
   Double_t        mhtSgnf;
   Double_t        mhtSgnfProb;
   vector<TLorentzVector> *jetsLVec; // vector of TLorentzVector of the input jets (check pt, eta of the input jets, currently pt>10 GeV)
   vector<TLorentzVector> *groomedJetsLVec; // disabled as this one takes lots of CPU time...
   vector<TLorentzVector> *muonsLVec; // vector of TLorentzVector of the input muons 
   vector<double>  *muonsAux; // vector of other quatities: charge, mtw(mu, met)
   vector<TLorentzVector> *elesLVec; // vector of TLorentzVector of the input electrons
   vector<double>  *elesAux; // vector of other quatities: charge, mtw(ele, met)
   Double_t        dPhi0_CUT; // deltaPhi of MET and jet0
   Double_t        dPhi1_CUT; // deltaPhi of MET and jet1
   Double_t        dPhi2_CUT; // deltaPhi of MET and jet2
   Int_t           nJets_CUT; // external number of jets counting (check input before use it)
   vector<TLorentzVector> *loose_isoTrksLVec; // vector of TLorentzVector of the loose isolated tracks (relIso<0.5 & pt> 5GeV)
   vector<vector<double> > *loose_isoTrksAuxVec; // other quatities of the loose isolated tracks: charge, pdgId, dz, iso (need divide by pt to get relIso), mtw(isotrk, met)
   vector<int>     *loose_isoTrksConsMatchedJetIdxVec; // empty as currently the code breaks...
   vector<int>     *forVetoIsoTrkIdxVec; // indices of default isolated tracks (tight): index is referred to pf candidate collection (packed)
   vector<TLorentzVector> *trksForIsoVetoLVec; // vector of TLorentzVector of the charged tracks around the gen level ele, mu, tau prongs and looser isolated tracks (a cone of DR<0.5 & dz<0.15)
   vector<vector<double> > *trksForIsoVetoAux; // other quatities: charge, pdgId, dz, index (referred to the packed pf candidate collection)
   Int_t           externalBit; // not used
   vector<int>     *recoJetsFlavor; // parton flavor from the pat::Jet
   vector<string>  *bTagKeyString; // the b-tagging key string
   vector<double>  *recoJetsBtag_0; // the b-tagging CSV value
   vector<TLorentzVector> *hepTaggerJets; // not used
   vector<vector<TLorentzVector> > *hepTaggerSubJets; // not used
   Int_t           bestTopJetIdx; // top tagger index: -1 means no top quark (triplet) found; otherwise it is the index of the triplet combinations
   Int_t           pickedRemainingCombfatJetIdx; // ... refer to the top tagger code 
   Bool_t          remainPassCSVS;
   Double_t        bestTopJetMass;
   Double_t        mTbestTopJet;
   Double_t        mTbJet;
   Double_t        MT2;
   Double_t        mTbestWJet;
   Double_t        mTbestbJet;
   Double_t        mTremainingTopJet; // ... refer to the top tagger code
   vector<string>  *genDecayStrVec; // the decay strings (useful for print out directly)
   vector<int>     *genDecayIdxVec; // index of the gen particle: index refers to the GenParticle collection (storing full decay chain)
   vector<int>     *genDecayMomIdxVec; // mother index of the gen particle: index refers to the GenParticle collection
   vector<int>     *genDecayPdgIdVec; // pdgId of the gen particle
   vector<TLorentzVector> *genDecayLVec; // vector of TLorentzVector of the gen particles
   vector<int>     *W_emuVec; // store indices of the ele and mu from W decay: index refers to the genDecayLVec vector 
   vector<int>     *W_tau_emuVec; // store indices of the ele and mu from W->tau decay: index referes to the genDecayLVec vector
   vector<int>     *W_tau_prongsVec; // store indices of the tau prongs: index referes to the genDecayLVec vector (note that if there are two or more taus decay hadronically, all the prongs are stored here. Be careful to check their mothers are the same to classify the prongs)

   // List of branches
   TBranch        *b_run;   //!
   TBranch        *b_event;   //!
   TBranch        *b_lumi;   //!
   TBranch        *b_npv;   //!
   TBranch        *b_avg_npv;   //!
   TBranch        *b_nm1;   //!
   TBranch        *b_n0;   //!
   TBranch        *b_np1;   //!
   TBranch        *b_tru_npv;   //!
   TBranch        *b_vtxSize;   //!
   TBranch        *b_nJets;   //!
   TBranch        *b_nMuons;   //!
   TBranch        *b_nMuonsForVeto;   //!
   TBranch        *b_nElectrons;   //!
   TBranch        *b_nElectronsForVeto;   //!
   TBranch        *b_loose_nIsoTrks;   //!
   TBranch        *b_nIsoTrksForVeto;   //!
   TBranch        *b_evtWeight;   //!
   TBranch        *b_mht;   //!
   TBranch        *b_mht_forSgnf;   //!
   TBranch        *b_ht;   //!
   TBranch        *b_met;   //!
   TBranch        *b_type1met;   //!
   TBranch        *b_mt;   //!
   TBranch        *b_type1mt;   //!
   TBranch        *b_mhtphi;   //!
   TBranch        *b_mhtphi_forSgnf;   //!
   TBranch        *b_metphi;   //!
   TBranch        *b_metSgnf;   //!
   TBranch        *b_metSgnfProb;   //!
   TBranch        *b_type1metphi;   //!
   TBranch        *b_type1metSgnf;   //!
   TBranch        *b_type1metSgnfProb;   //!
   TBranch        *b_mhtSgnf;   //!
   TBranch        *b_mhtSgnfProb;   //!
   TBranch        *b_jetsLVec;   //!
   TBranch        *b_groomedJetsLVec;   //!
   TBranch        *b_muonsLVec;   //!
   TBranch        *b_muonsAux;   //!
   TBranch        *b_elesLVec;   //!
   TBranch        *b_elesAux;   //!
   TBranch        *b_dPhi0_CUT;   //!
   TBranch        *b_dPhi1_CUT;   //!
   TBranch        *b_dPhi2_CUT;   //!
   TBranch        *b_nJets_CUT;   //!
   TBranch        *b_loose_isoTrksLVec;   //!
   TBranch        *b_loose_isoTrksAuxVec;   //!
   TBranch        *b_loose_isoTrksConsMatchedJetIdxVec;   //!
   TBranch        *b_forVetoIsoTrkIdxVec;   //!
   TBranch        *b_trksForIsoVetoLVec;   //!
   TBranch        *b_trksForIsoVetoAux;   //!
   TBranch        *b_externalBitToTree_TR;   //!
   TBranch        *b_recoJetsFlavor;   //!
   TBranch        *b_bTagKeyString;   //!
   TBranch        *b_recoJetsBtag_0;   //!
   TBranch        *b_hepTaggerJets;   //!
   TBranch        *b_hepTaggerSubJets;   //!
   TBranch        *b_bestTopJetIdx;   //!
   TBranch        *b_pickedRemainingCombfatJetIdx;   //!
   TBranch        *b_remainPassCSVS;   //!
   TBranch        *b_bestTopJetMass;   //!
   TBranch        *b_mTbestTopJet;   //!
   TBranch        *b_mTbJet;   //!
   TBranch        *b_MT2;   //!
   TBranch        *b_mTbestWJet;   //!
   TBranch        *b_mTbestbJet;   //!
   TBranch        *b_mTremainingTopJet;   //!
   TBranch        *b_genDecayStrVec;   //!
   TBranch        *b_genDecayIdxVec;   //!
   TBranch        *b_genDecayMomIdxVec;   //!
   TBranch        *b_genDecayPdgIdVec;   //!
   TBranch        *b_genDecayLVec;   //!
   TBranch        *b_W_emuVec;   //!
   TBranch        *b_W_tau_emuVec;   //!
   TBranch        *b_W_tau_prongsVec;   //!

   aux(TTree *tree=0);
   virtual ~aux();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef aux_cxx
aux::aux(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("stdStopHistAndTree.root.dR.0.5.T1tttt.no.ak5");
      if (!f || !f->IsOpen()) {
         f = new TFile("stdStopHistAndTree.root.dR.0.5.T1tttt.no.ak5");
      }
      TDirectory * dir = (TDirectory*)f->Get("stdStopHistAndTree.root.dR.0.5.T1tttt.no.ak5:/ak4Stop_histAndTree");
      dir->GetObject("AUX",tree);

   }
   Init(tree);
}

aux::~aux()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t aux::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t aux::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void aux::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   jetsLVec = 0;
   groomedJetsLVec = 0;
   muonsLVec = 0;
   muonsAux = 0;
   elesLVec = 0;
   elesAux = 0;
   loose_isoTrksLVec = 0;
   loose_isoTrksAuxVec = 0;
   loose_isoTrksConsMatchedJetIdxVec = 0;
   forVetoIsoTrkIdxVec = 0;
   trksForIsoVetoLVec = 0;
   trksForIsoVetoAux = 0;
   recoJetsFlavor = 0;
   bTagKeyString = 0;
   recoJetsBtag_0 = 0;
   hepTaggerJets = 0;
   hepTaggerSubJets = 0;
   genDecayStrVec = 0;
   genDecayIdxVec = 0;
   genDecayMomIdxVec = 0;
   genDecayPdgIdVec = 0;
   genDecayLVec = 0;
   W_emuVec = 0;
   W_tau_emuVec = 0;
   W_tau_prongsVec = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("run", &run, &b_run);
   fChain->SetBranchAddress("event", &event, &b_event);
   fChain->SetBranchAddress("lumi", &lumi, &b_lumi);
   fChain->SetBranchAddress("npv", &npv, &b_npv);
   fChain->SetBranchAddress("avg_npv", &avg_npv, &b_avg_npv);
   fChain->SetBranchAddress("nm1", &nm1, &b_nm1);
   fChain->SetBranchAddress("n0", &n0, &b_n0);
   fChain->SetBranchAddress("np1", &np1, &b_np1);
   fChain->SetBranchAddress("tru_npv", &tru_npv, &b_tru_npv);
   fChain->SetBranchAddress("vtxSize", &vtxSize, &b_vtxSize);
   fChain->SetBranchAddress("nJets", &nJets, &b_nJets);
   fChain->SetBranchAddress("nMuons", &nMuons, &b_nMuons);
   fChain->SetBranchAddress("nMuons_CUT", &nMuons_CUT, &b_nMuonsForVeto);
   fChain->SetBranchAddress("nElectrons", &nElectrons, &b_nElectrons);
   fChain->SetBranchAddress("nElectrons_CUT", &nElectrons_CUT, &b_nElectronsForVeto);
   fChain->SetBranchAddress("nIsoTrks", &nIsoTrks, &b_loose_nIsoTrks);
   fChain->SetBranchAddress("nIsoTrks_CUT", &nIsoTrks_CUT, &b_nIsoTrksForVeto);
   fChain->SetBranchAddress("evtWeight", &evtWeight, &b_evtWeight);
   fChain->SetBranchAddress("mht", &mht, &b_mht);
   fChain->SetBranchAddress("mht_forSgnf", &mht_forSgnf, &b_mht_forSgnf);
   fChain->SetBranchAddress("ht", &ht, &b_ht);
   fChain->SetBranchAddress("met", &met, &b_met);
   fChain->SetBranchAddress("type1met", &type1met, &b_type1met);
   fChain->SetBranchAddress("mt", &mt, &b_mt);
   fChain->SetBranchAddress("type1mt", &type1mt, &b_type1mt);
   fChain->SetBranchAddress("mhtphi", &mhtphi, &b_mhtphi);
   fChain->SetBranchAddress("mhtphi_forSgnf", &mhtphi_forSgnf, &b_mhtphi_forSgnf);
   fChain->SetBranchAddress("metphi", &metphi, &b_metphi);
   fChain->SetBranchAddress("metSgnf", &metSgnf, &b_metSgnf);
   fChain->SetBranchAddress("metSgnfProb", &metSgnfProb, &b_metSgnfProb);
   fChain->SetBranchAddress("type1metphi", &type1metphi, &b_type1metphi);
   fChain->SetBranchAddress("type1metSgnf", &type1metSgnf, &b_type1metSgnf);
   fChain->SetBranchAddress("type1metSgnfProb", &type1metSgnfProb, &b_type1metSgnfProb);
   fChain->SetBranchAddress("mhtSgnf", &mhtSgnf, &b_mhtSgnf);
   fChain->SetBranchAddress("mhtSgnfProb", &mhtSgnfProb, &b_mhtSgnfProb);
   fChain->SetBranchAddress("jetsLVec", &jetsLVec, &b_jetsLVec);
   fChain->SetBranchAddress("groomedJetsLVec", &groomedJetsLVec, &b_groomedJetsLVec);
   fChain->SetBranchAddress("muonsLVec", &muonsLVec, &b_muonsLVec);
   fChain->SetBranchAddress("muonsAux", &muonsAux, &b_muonsAux);
   fChain->SetBranchAddress("elesLVec", &elesLVec, &b_elesLVec);
   fChain->SetBranchAddress("elesAux", &elesAux, &b_elesAux);
   fChain->SetBranchAddress("dPhi0_CUT", &dPhi0_CUT, &b_dPhi0_CUT);
   fChain->SetBranchAddress("dPhi1_CUT", &dPhi1_CUT, &b_dPhi1_CUT);
   fChain->SetBranchAddress("dPhi2_CUT", &dPhi2_CUT, &b_dPhi2_CUT);
   fChain->SetBranchAddress("nJets_CUT", &nJets_CUT, &b_nJets_CUT);
   fChain->SetBranchAddress("loose_isoTrksLVec", &loose_isoTrksLVec, &b_loose_isoTrksLVec);
   fChain->SetBranchAddress("loose_isoTrksAuxVec", &loose_isoTrksAuxVec, &b_loose_isoTrksAuxVec);
   fChain->SetBranchAddress("loose_isoTrksConsMatchedJetIdxVec", &loose_isoTrksConsMatchedJetIdxVec, &b_loose_isoTrksConsMatchedJetIdxVec);
   fChain->SetBranchAddress("forVetoIsoTrkIdxVec", &forVetoIsoTrkIdxVec, &b_forVetoIsoTrkIdxVec);
   fChain->SetBranchAddress("trksForIsoVetoLVec", &trksForIsoVetoLVec, &b_trksForIsoVetoLVec);
   fChain->SetBranchAddress("trksForIsoVetoAux", &trksForIsoVetoAux, &b_trksForIsoVetoAux);
   fChain->SetBranchAddress("externalBit", &externalBit, &b_externalBitToTree_TR);
   fChain->SetBranchAddress("recoJetsFlavor", &recoJetsFlavor, &b_recoJetsFlavor);
   fChain->SetBranchAddress("bTagKeyString", &bTagKeyString, &b_bTagKeyString);
   fChain->SetBranchAddress("recoJetsBtag_0", &recoJetsBtag_0, &b_recoJetsBtag_0);
   fChain->SetBranchAddress("hepTaggerJets", &hepTaggerJets, &b_hepTaggerJets);
   fChain->SetBranchAddress("hepTaggerSubJets", &hepTaggerSubJets, &b_hepTaggerSubJets);
   fChain->SetBranchAddress("bestTopJetIdx", &bestTopJetIdx, &b_bestTopJetIdx);
   fChain->SetBranchAddress("pickedRemainingCombfatJetIdx", &pickedRemainingCombfatJetIdx, &b_pickedRemainingCombfatJetIdx);
   fChain->SetBranchAddress("remainPassCSVS", &remainPassCSVS, &b_remainPassCSVS);
   fChain->SetBranchAddress("bestTopJetMass", &bestTopJetMass, &b_bestTopJetMass);
   fChain->SetBranchAddress("mTbestTopJet", &mTbestTopJet, &b_mTbestTopJet);
   fChain->SetBranchAddress("mTbJet", &mTbJet, &b_mTbJet);
   fChain->SetBranchAddress("MT2", &MT2, &b_MT2);
   fChain->SetBranchAddress("mTbestWJet", &mTbestWJet, &b_mTbestWJet);
   fChain->SetBranchAddress("mTbestbJet", &mTbestbJet, &b_mTbestbJet);
   fChain->SetBranchAddress("mTremainingTopJet", &mTremainingTopJet, &b_mTremainingTopJet);
   fChain->SetBranchAddress("genDecayStrVec", &genDecayStrVec, &b_genDecayStrVec);
   fChain->SetBranchAddress("genDecayIdxVec", &genDecayIdxVec, &b_genDecayIdxVec);
   fChain->SetBranchAddress("genDecayMomIdxVec", &genDecayMomIdxVec, &b_genDecayMomIdxVec);
   fChain->SetBranchAddress("genDecayPdgIdVec", &genDecayPdgIdVec, &b_genDecayPdgIdVec);
   fChain->SetBranchAddress("genDecayLVec", &genDecayLVec, &b_genDecayLVec);
   fChain->SetBranchAddress("W_emuVec", &W_emuVec, &b_W_emuVec);
   fChain->SetBranchAddress("W_tau_emuVec", &W_tau_emuVec, &b_W_tau_emuVec);
   fChain->SetBranchAddress("W_tau_prongsVec", &W_tau_prongsVec, &b_W_tau_prongsVec);
   Notify();
}

Bool_t aux::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void aux::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t aux::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef aux_cxx
