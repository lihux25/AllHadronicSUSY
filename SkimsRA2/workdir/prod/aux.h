//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Dec 11 11:35:12 2014 by ROOT version 5.34/18
// from TTree AUX/AUX
// found on file: stopFlatNtuples.root
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

// Fixed size dimensions of array or collections stored in the TTree if any.

class aux {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   UInt_t          run;
   UInt_t          lumi;
   UInt_t          event;
   Double_t        mht;
   Double_t        ht;
   Double_t        met;
   Double_t        metphi;
   Double_t        tru_npv;
   Double_t        avg_npv;
   Double_t        bestTopJetMass;
   Double_t        MT2;
   Double_t        mTbestTopJet;
   Double_t        mTbJet;
   Double_t        linearCombmTbJetPlusmTbestTopJet;
   Double_t        mTbestWJet;
   Double_t        mTbestbJet;
   Double_t        mTremainingTopJet;
   Double_t        evtWeight;
   Double_t        smsMotherMass;
   Double_t        smsDaughterMass;
   Int_t           nMuons_CUT;
   Int_t           nElectrons_CUT;
   Int_t           nJets;
   Int_t           loose_nIsoTrks;
   Int_t           nIsoTrks_CUT;
   Int_t           nJets_CUT;
   Int_t           vtxSize;
   Int_t           npv;
   Int_t           nm1;
   Int_t           n0;
   Int_t           np1;
   Int_t           bestTopJetIdx;
   Int_t           pickedRemainingCombfatJetIdx;
   UInt_t          remainPassCSVS;
   vector<double>  *muonsCharge;
   vector<double>  *muonsMtw;
   vector<double>  *elesCharge;
   vector<double>  *elesMtw;
   vector<double>  *recoJetsBtag;
   vector<double>  *trksForIsoVeto_charge;
   vector<double>  *trksForIsoVeto_dz;
   vector<double>  *loose_isoTrks_charge;
   vector<double>  *loose_isoTrks_dz;
   vector<double>  *loose_isoTrks_iso;
   vector<double>  *loose_isoTrks_mtw;
   vector<double>  *dPhis_CUT;
   vector<int>     *recoJetsFlavor;
   vector<int>     *genDecayIdxVec;
   vector<int>     *genDecayPdgIdVec;
   vector<int>     *genDecayMomIdxVec;
   vector<int>     *W_emuVec;
   vector<int>     *W_tau_emuVec;
   vector<int>     *W_tau_prongsVec;
   vector<int>     *trksForIsoVeto_pdgId;
   vector<int>     *trksForIsoVeto_idx;
   vector<int>     *loose_isoTrks_pdgId;
   vector<int>     *loose_isoTrks_idx;
   vector<int>     *forVetoIsoTrkIdxVec;
   vector<string>  *genDecayStrVec;
   vector<string>  *fileNameStr;
   vector<string>  *smsModelStr;
   vector<TLorentzVector> *muonsLVec;
   vector<TLorentzVector> *elesLVec;
   vector<TLorentzVector> *jetsLVec;
   vector<TLorentzVector> *genDecayLVec;
   vector<TLorentzVector> *trksForIsoVetoLVec;
   vector<TLorentzVector> *loose_isoTrksLVec;

   // List of branches
   TBranch        *b_run;   //!
   TBranch        *b_lumi;   //!
   TBranch        *b_event;   //!
   TBranch        *b_mht;   //!
   TBranch        *b_ht;   //!
   TBranch        *b_met;   //!
   TBranch        *b_metphi;   //!
   TBranch        *b_tru_npv;   //!
   TBranch        *b_avg_npv;   //!
   TBranch        *b_bestTopJetMass;   //!
   TBranch        *b_MT2;   //!
   TBranch        *b_mTbestTopJet;   //!
   TBranch        *b_mTbJet;   //!
   TBranch        *b_linearCombmTbJetPlusmTbestTopJet;   //!
   TBranch        *b_mTbestWJet;   //!
   TBranch        *b_mTbestbJet;   //!
   TBranch        *b_mTremainingTopJet;   //!
   TBranch        *b_evtWeight;   //!
   TBranch        *b_smsMotherMass;   //!
   TBranch        *b_smsDaughterMass;   //!
   TBranch        *b_nMuons_CUT;   //!
   TBranch        *b_nElectrons_CUT;   //!
   TBranch        *b_nJets;   //!
   TBranch        *b_loose_nIsoTrks;   //!
   TBranch        *b_nIsoTrks_CUT;   //!
   TBranch        *b_nJets_CUT;   //!
   TBranch        *b_vtxSize;   //!
   TBranch        *b_npv;   //!
   TBranch        *b_nm1;   //!
   TBranch        *b_n0;   //!
   TBranch        *b_np1;   //!
   TBranch        *b_bestTopJetIdx;   //!
   TBranch        *b_pickedRemainingCombfatJetIdx;   //!
   TBranch        *b_remainPassCSVS;   //!
   TBranch        *b_muonsCharge;   //!
   TBranch        *b_muonsMtw;   //!
   TBranch        *b_elesCharge;   //!
   TBranch        *b_elesMtw;   //!
   TBranch        *b_recoJetsBtag;   //!
   TBranch        *b_trksForIsoVeto_charge;   //!
   TBranch        *b_trksForIsoVeto_dz;   //!
   TBranch        *b_loose_isoTrks_charge;   //!
   TBranch        *b_loose_isoTrks_dz;   //!
   TBranch        *b_loose_isoTrks_iso;   //!
   TBranch        *b_loose_isoTrks_mtw;   //!
   TBranch        *b_dPhis_CUT;   //!
   TBranch        *b_recoJetsFlavor;   //!
   TBranch        *b_genDecayIdxVec;   //!
   TBranch        *b_genDecayPdgIdVec;   //!
   TBranch        *b_genDecayMomIdxVec;   //!
   TBranch        *b_W_emuVec;   //!
   TBranch        *b_W_tau_emuVec;   //!
   TBranch        *b_W_tau_prongsVec;   //!
   TBranch        *b_trksForIsoVeto_pdgId;   //!
   TBranch        *b_trksForIsoVeto_idx;   //!
   TBranch        *b_loose_isoTrks_pdgId;   //!
   TBranch        *b_loose_isoTrks_idx;   //!
   TBranch        *b_forVetoIsoTrkIdxVec;   //!
   TBranch        *b_genDecayStrVec;   //!
   TBranch        *b_fileNameStr;   //!
   TBranch        *b_smsModelStr;   //!
   TBranch        *b_muonsLVec;   //!
   TBranch        *b_elesLVec;   //!
   TBranch        *b_jetsLVec;   //!
   TBranch        *b_genDecayLVec;   //!
   TBranch        *b_trksForIsoVetoLVec;   //!
   TBranch        *b_loose_isoTrksLVec;   //!

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
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("stopFlatNtuples.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("stopFlatNtuples.root");
      }
      TDirectory * dir = (TDirectory*)f->Get("stopFlatNtuples.root:/stopTreeMaker");
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
   muonsCharge = 0;
   muonsMtw = 0;
   elesCharge = 0;
   elesMtw = 0;
   recoJetsBtag = 0;
   trksForIsoVeto_charge = 0;
   trksForIsoVeto_dz = 0;
   loose_isoTrks_charge = 0;
   loose_isoTrks_dz = 0;
   loose_isoTrks_iso = 0;
   loose_isoTrks_mtw = 0;
   dPhis_CUT = 0;
   recoJetsFlavor = 0;
   genDecayIdxVec = 0;
   genDecayPdgIdVec = 0;
   genDecayMomIdxVec = 0;
   W_emuVec = 0;
   W_tau_emuVec = 0;
   W_tau_prongsVec = 0;
   trksForIsoVeto_pdgId = 0;
   trksForIsoVeto_idx = 0;
   loose_isoTrks_pdgId = 0;
   loose_isoTrks_idx = 0;
   forVetoIsoTrkIdxVec = 0;
   genDecayStrVec = 0;
   fileNameStr = 0;
   smsModelStr = 0;
   muonsLVec = 0;
   elesLVec = 0;
   jetsLVec = 0;
   genDecayLVec = 0;
   trksForIsoVetoLVec = 0;
   loose_isoTrksLVec = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("run", &run, &b_run);
   fChain->SetBranchAddress("lumi", &lumi, &b_lumi);
   fChain->SetBranchAddress("event", &event, &b_event);
   fChain->SetBranchAddress("mht", &mht, &b_mht);
   fChain->SetBranchAddress("ht", &ht, &b_ht);
   fChain->SetBranchAddress("met", &met, &b_met);
   fChain->SetBranchAddress("metphi", &metphi, &b_metphi);
   fChain->SetBranchAddress("tru_npv", &tru_npv, &b_tru_npv);
   fChain->SetBranchAddress("avg_npv", &avg_npv, &b_avg_npv);
   fChain->SetBranchAddress("bestTopJetMass", &bestTopJetMass, &b_bestTopJetMass);
   fChain->SetBranchAddress("MT2", &MT2, &b_MT2);
   fChain->SetBranchAddress("mTbestTopJet", &mTbestTopJet, &b_mTbestTopJet);
   fChain->SetBranchAddress("mTbJet", &mTbJet, &b_mTbJet);
   fChain->SetBranchAddress("linearCombmTbJetPlusmTbestTopJet", &linearCombmTbJetPlusmTbestTopJet, &b_linearCombmTbJetPlusmTbestTopJet);
   fChain->SetBranchAddress("mTbestWJet", &mTbestWJet, &b_mTbestWJet);
   fChain->SetBranchAddress("mTbestbJet", &mTbestbJet, &b_mTbestbJet);
   fChain->SetBranchAddress("mTremainingTopJet", &mTremainingTopJet, &b_mTremainingTopJet);
   fChain->SetBranchAddress("evtWeight", &evtWeight, &b_evtWeight);
   fChain->SetBranchAddress("smsMotherMass", &smsMotherMass, &b_smsMotherMass);
   fChain->SetBranchAddress("smsDaughterMass", &smsDaughterMass, &b_smsDaughterMass);
   fChain->SetBranchAddress("nMuons_CUT", &nMuons_CUT, &b_nMuons_CUT);
   fChain->SetBranchAddress("nElectrons_CUT", &nElectrons_CUT, &b_nElectrons_CUT);
   fChain->SetBranchAddress("nJets", &nJets, &b_nJets);
   fChain->SetBranchAddress("loose_nIsoTrks", &loose_nIsoTrks, &b_loose_nIsoTrks);
   fChain->SetBranchAddress("nIsoTrks_CUT", &nIsoTrks_CUT, &b_nIsoTrks_CUT);
   fChain->SetBranchAddress("nJets_CUT", &nJets_CUT, &b_nJets_CUT);
   fChain->SetBranchAddress("vtxSize", &vtxSize, &b_vtxSize);
   fChain->SetBranchAddress("npv", &npv, &b_npv);
   fChain->SetBranchAddress("nm1", &nm1, &b_nm1);
   fChain->SetBranchAddress("n0", &n0, &b_n0);
   fChain->SetBranchAddress("np1", &np1, &b_np1);
   fChain->SetBranchAddress("bestTopJetIdx", &bestTopJetIdx, &b_bestTopJetIdx);
   fChain->SetBranchAddress("pickedRemainingCombfatJetIdx", &pickedRemainingCombfatJetIdx, &b_pickedRemainingCombfatJetIdx);
   fChain->SetBranchAddress("remainPassCSVS", &remainPassCSVS, &b_remainPassCSVS);
   fChain->SetBranchAddress("muonsCharge", &muonsCharge, &b_muonsCharge);
   fChain->SetBranchAddress("muonsMtw", &muonsMtw, &b_muonsMtw);
   fChain->SetBranchAddress("elesCharge", &elesCharge, &b_elesCharge);
   fChain->SetBranchAddress("elesMtw", &elesMtw, &b_elesMtw);
   fChain->SetBranchAddress("recoJetsBtag", &recoJetsBtag, &b_recoJetsBtag);
   fChain->SetBranchAddress("trksForIsoVeto_charge", &trksForIsoVeto_charge, &b_trksForIsoVeto_charge);
   fChain->SetBranchAddress("trksForIsoVeto_dz", &trksForIsoVeto_dz, &b_trksForIsoVeto_dz);
   fChain->SetBranchAddress("loose_isoTrks_charge", &loose_isoTrks_charge, &b_loose_isoTrks_charge);
   fChain->SetBranchAddress("loose_isoTrks_dz", &loose_isoTrks_dz, &b_loose_isoTrks_dz);
   fChain->SetBranchAddress("loose_isoTrks_iso", &loose_isoTrks_iso, &b_loose_isoTrks_iso);
   fChain->SetBranchAddress("loose_isoTrks_mtw", &loose_isoTrks_mtw, &b_loose_isoTrks_mtw);
   fChain->SetBranchAddress("dPhis_CUT", &dPhis_CUT, &b_dPhis_CUT);
   fChain->SetBranchAddress("recoJetsFlavor", &recoJetsFlavor, &b_recoJetsFlavor);
   fChain->SetBranchAddress("genDecayIdxVec", &genDecayIdxVec, &b_genDecayIdxVec);
   fChain->SetBranchAddress("genDecayPdgIdVec", &genDecayPdgIdVec, &b_genDecayPdgIdVec);
   fChain->SetBranchAddress("genDecayMomIdxVec", &genDecayMomIdxVec, &b_genDecayMomIdxVec);
   fChain->SetBranchAddress("W_emuVec", &W_emuVec, &b_W_emuVec);
   fChain->SetBranchAddress("W_tau_emuVec", &W_tau_emuVec, &b_W_tau_emuVec);
   fChain->SetBranchAddress("W_tau_prongsVec", &W_tau_prongsVec, &b_W_tau_prongsVec);
   fChain->SetBranchAddress("trksForIsoVeto_pdgId", &trksForIsoVeto_pdgId, &b_trksForIsoVeto_pdgId);
   fChain->SetBranchAddress("trksForIsoVeto_idx", &trksForIsoVeto_idx, &b_trksForIsoVeto_idx);
   fChain->SetBranchAddress("loose_isoTrks_pdgId", &loose_isoTrks_pdgId, &b_loose_isoTrks_pdgId);
   fChain->SetBranchAddress("loose_isoTrks_idx", &loose_isoTrks_idx, &b_loose_isoTrks_idx);
   fChain->SetBranchAddress("forVetoIsoTrkIdxVec", &forVetoIsoTrkIdxVec, &b_forVetoIsoTrkIdxVec);
   fChain->SetBranchAddress("genDecayStrVec", &genDecayStrVec, &b_genDecayStrVec);
   fChain->SetBranchAddress("fileNameStr", &fileNameStr, &b_fileNameStr);
   fChain->SetBranchAddress("smsModelStr", &smsModelStr, &b_smsModelStr);
   fChain->SetBranchAddress("muonsLVec", &muonsLVec, &b_muonsLVec);
   fChain->SetBranchAddress("elesLVec", &elesLVec, &b_elesLVec);
   fChain->SetBranchAddress("jetsLVec", &jetsLVec, &b_jetsLVec);
   fChain->SetBranchAddress("genDecayLVec", &genDecayLVec, &b_genDecayLVec);
   fChain->SetBranchAddress("trksForIsoVetoLVec", &trksForIsoVetoLVec, &b_trksForIsoVetoLVec);
   fChain->SetBranchAddress("loose_isoTrksLVec", &loose_isoTrksLVec, &b_loose_isoTrksLVec);
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
