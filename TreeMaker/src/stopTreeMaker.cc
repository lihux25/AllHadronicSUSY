// -*- C++ -*-
//
// Package:    AllHadronicSUSY/TreeMaker
// Class:      stopTreeMaker
// 
/**\class stopTreeMaker stopTreeMaker.cc AllHadronicSUSY/TreeMaker/plugins/stopTreeMaker.cc
 * 
 * Description: [one line class summary]
 * 
 * Implementation:
 *     [Notes on implementation]
 */
// However, code have been drastically changed by Hongxuan Liu
//
// Borrowed from Original Author:  Arne-Rasmus Draeger
//           Created:  Fri, 03 Dec 2014 13:48:35 GMT
//
//
#include "AllHadronicSUSY/TreeMaker/interface/stopTreeMaker.h"
#include "DataFormats/METReco/interface/MET.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include <memory>

// system include files

//
// constants, enums and typedefs
//


//
// static data member definitions
//

//
// constructors and destructor
//
stopTreeMaker::stopTreeMaker(const edm::ParameterSet& iConfig)
: nMaxCandidates_(200), tree_(0)
{
  // generell
  treeName_ = iConfig.getParameter<std::string>("TreeName");

  debug_ = iConfig.getParameter<bool> ("debug");

  varsDoubleTags_ = iConfig.getParameter< std::vector<edm::InputTag> >("VarsDouble");
  varsDoubleNames_= iConfig.getParameter< std::vector<std::string> >  ("VarsDoubleNamesInTree");
  varsIntTags_ = iConfig.getParameter< std::vector<edm::InputTag> >("VarsInt");
  varsIntNames_= iConfig.getParameter< std::vector<std::string> >  ("VarsIntNamesInTree");
  varsBoolTags_ = iConfig.getParameter< std::vector<edm::InputTag> >("VarsBool");
  varsBoolNames_= iConfig.getParameter< std::vector<std::string> >  ("VarsBoolNamesInTree");
  varsStringTags_ = iConfig.getParameter< std::vector<edm::InputTag> >("VarsString");
  varsStringNames_= iConfig.getParameter< std::vector<std::string> >  ("VarsStringNamesInTree");
  varsTLorentzVectorTags_ = iConfig.getParameter< std::vector<edm::InputTag> >("VarsTLorentzVector");
  varsTLorentzVectorNames_= iConfig.getParameter< std::vector<std::string> >  ("VarsTLorentzVectorNamesInTree");

  vectorDoubleTags_ = iConfig.getParameter< std::vector<edm::InputTag> >("VectorDouble");
  vectorDoubleNames_= iConfig.getParameter< std::vector<std::string> >  ("VectorDoubleNamesInTree");
  vectorIntTags_ = iConfig.getParameter< std::vector<edm::InputTag> >("VectorInt");
  vectorIntNames_= iConfig.getParameter< std::vector<std::string> >  ("VectorIntNamesInTree");
  vectorBoolTags_ = iConfig.getParameter< std::vector<edm::InputTag> >("VectorBool");
  vectorBoolNames_= iConfig.getParameter< std::vector<std::string> >  ("VectorBoolNamesInTree");
  vectorStringTags_ = iConfig.getParameter< std::vector<edm::InputTag> >("VectorString");
  vectorStringNames_= iConfig.getParameter< std::vector<std::string> >  ("VectorStringNamesInTree");
  vectorTLorentzVectorTags_ = iConfig.getParameter< std::vector<edm::InputTag> >("VectorTLorentzVector");
  vectorTLorentzVectorNames_= iConfig.getParameter< std::vector<std::string> >  ("VectorTLorentzVectorNamesInTree");

  cachedNames_.clear();
}

stopTreeMaker::~stopTreeMaker()
{
  
}

//
// member functions
//
// ------------ method called to produce the data  ------------
void
stopTreeMaker::produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  using namespace edm;
  using namespace reco;
  using namespace pat;

  setBranchVariablesToDefault();
	
// Event information
  edm::EventAuxiliary aux = iEvent.eventAuxiliary();
  runNum_       = aux.run();
  lumiBlockNum_ = aux.luminosityBlock();
  evtNum_       = aux.event();

//Float variables
  for(unsigned int i = 0; i < varsDoubleTags_.size(); ++i) {
     edm::Handle<double> var;
     iEvent.getByLabel(varsDoubleTags_.at(i),var);
     if( var.isValid() ) {
        varsDouble_.at(i) = *var;
     }
  }
	
  for(unsigned int i = 0; i < varsIntTags_.size(); ++i) {
    edm::Handle<int> var;
    iEvent.getByLabel(varsIntTags_.at(i),var);
    if( var.isValid() ) {
      varsInt_.at(i) = *var;
    }
  }

  for(unsigned int i = 0; i < varsBoolTags_.size(); ++i) {
    edm::Handle<bool> var;
    iEvent.getByLabel(varsBoolTags_.at(i),var);
    if( var.isValid() ) {
      if( *var ) varsBool_.at(i) = 1;
      else varsBool_.at(i) = 0;
    }
  }
	
  for(unsigned int i = 0; i < varsStringTags_.size(); ++i) {
    edm::Handle<std::string> var;
    iEvent.getByLabel(varsStringTags_.at(i),var);
    if( var.isValid() ) {
      varsString_.at(i) = *var;
    }
  }
	
  for(unsigned int i = 0; i < varsTLorentzVectorTags_.size(); ++i) {
    edm::Handle<TLorentzVector> var;
    iEvent.getByLabel(varsTLorentzVectorTags_.at(i),var);
    if( var.isValid() ) {
      varsTLorentzVector_.at(i) = *var;
    }
  }

  for(unsigned int i = 0; i < vectorDoubleTags_.size(); ++i) {
    edm::Handle<std::vector<double> > var;
    iEvent.getByLabel(vectorDoubleTags_.at(i),var);
    if( var.isValid() ){
      for(unsigned int j=0; j< var->size(); j++){
        vectorDoubleVector_.at(i).push_back(var->at(j));
      }
    }
  }

  for(unsigned int i = 0; i < vectorIntTags_.size(); ++i) {
    edm::Handle<std::vector<int> > var;
    iEvent.getByLabel(vectorIntTags_.at(i),var);
    if( var.isValid() ){
      for(unsigned int j=0; j< var->size(); j++){
        vectorIntVector_.at(i).push_back(var->at(j));
      }
    }
  }

  for(unsigned int i = 0; i < vectorBoolTags_.size(); ++i) {
    edm::Handle<std::vector<bool> > var;
    iEvent.getByLabel(vectorBoolTags_.at(i),var);
    if( var.isValid() ){
      for(unsigned int j=0; j< var->size(); j++){
        if( var->at(j) ) vectorBoolVector_.at(i).push_back(1);
        else vectorBoolVector_.at(i).push_back(0);
      }
    }
  }

  for(unsigned int i = 0; i < vectorStringTags_.size(); ++i) {
    edm::Handle<std::vector<std::string> > var;
    iEvent.getByLabel(vectorStringTags_.at(i),var);
    if( var.isValid() ){
      for(unsigned int j=0; j< var->size(); j++){
        vectorStringVector_.at(i).push_back(var->at(j));
      }
    }
  }

  for(unsigned int i = 0; i < vectorTLorentzVectorTags_.size(); ++i) {
    edm::Handle<std::vector<TLorentzVector> > var;
    iEvent.getByLabel(vectorTLorentzVectorTags_.at(i),var);
    if( var.isValid() ) {
      for(unsigned int j=0; j< var->size();j++){
        vectorTLorentzVector_.at(i).push_back(var->at(j));
      }
    }
  }

  tree_->Fill();
}

// ------------ method called once each job just before starting event loop  ------------
void 
stopTreeMaker::beginJob()
{
  edm::Service<TFileService> fs;
  if( !fs ) {
    throw edm::Exception(edm::errors::Configuration, "TFile Service is not registered in cfg file");
  }
  tree_ = fs->make<TTree>(treeName_,treeName_);  
  tree_->SetAutoSave(10000000000);
  tree_->SetAutoFlush(1000000);

  tree_->Branch("run",&runNum_,"run/i");
  tree_->Branch("lumi",&lumiBlockNum_,"lumi/i");
  tree_->Branch("event",&evtNum_,"event/i");

  if( debug_ ) std::cout<<std::endl;
  varsDouble_ = std::vector<double>(varsDoubleTags_.size(), 9999.);
  for(unsigned int i = 0; i < varsDouble_.size(); ++i) {
    TString nameT = formBranchName(varsDoubleTags_.at(i), varsDoubleNames_);
    if( debug_ ) std::cout<<"varsDoubleTags :  i : "<<i<<"  nameT : "<<nameT<<std::endl;
    tree_->Branch(nameT, &(varsDouble_.at(i)), nameT+"/D");
  }

  varsInt_ = std::vector<int>(varsIntTags_.size(), 9999);
  for(unsigned int i = 0; i < varsIntTags_.size(); ++i) {
    TString nameT = formBranchName(varsIntTags_.at(i), varsIntNames_);
    if( debug_ ) std::cout<<"varsIntTags :  i : "<<i<<"  nameT : "<<nameT<<std::endl;
    tree_->Branch(nameT, &(varsInt_.at(i)), nameT+"/I");
  }

  varsBool_ = std::vector<unsigned int>(varsBoolTags_.size(), 0);
  for(unsigned int i = 0; i < varsBoolTags_.size(); ++i) {
    TString nameT = formBranchName(varsBoolTags_.at(i), varsBoolNames_);
    if( debug_ ) std::cout<<"varsBoolTags :  i : "<<i<<"  nameT : "<<nameT<<std::endl;
    tree_->Branch(nameT, &(varsBool_.at(i)), nameT+"/i");
  }

  varsString_ = std::vector<std::string>(varsStringTags_.size(), "");
  for(unsigned int i = 0; i < varsStringTags_.size(); ++i) {
    TString nameT = formBranchName(varsStringTags_.at(i), varsStringNames_);
    if( debug_ ) std::cout<<"varsStringTags :  i : "<<i<<"  nameT : "<<nameT<<std::endl;
    tree_->Branch(nameT, nameT, &(varsString_.at(i)));
  }

  varsTLorentzVector_ = std::vector<TLorentzVector>(varsTLorentzVectorTags_.size(), TLorentzVector(0.,0.,0.,0.));
  for(unsigned int i = 0; i < varsTLorentzVectorTags_.size(); ++i) {
    TString nameT = formBranchName(varsTLorentzVectorTags_.at(i), varsTLorentzVectorNames_);
    if( debug_ ) std::cout<<"varsTLorentzVectorTags :  i : "<<i<<"  nameT : "<<nameT<<std::endl;
    tree_->Branch(nameT, nameT, &(varsTLorentzVector_.at(i)));
  }

// vector of ...
  for(unsigned int i=0; i< vectorDoubleTags_.size();i++)
  {
    std::vector<double> vector;
    vectorDoubleVector_.push_back(vector);
  }
  for(unsigned int i=0; i< vectorDoubleTags_.size();i++)
  {
    TString nameT = formBranchName(vectorDoubleTags_.at(i), vectorDoubleNames_);
    if( debug_ ) std::cout<<"vectorDoubleTags :  i : "<<i<<"  nameT : "<<nameT<<std::endl;
    tree_->Branch(nameT, "std::vector<double>", &(vectorDoubleVector_.at(i)), 32000, 0);
  }

//
  for(unsigned int i=0; i< vectorIntTags_.size();i++)
  {
    std::vector<int> vector;
    vectorIntVector_.push_back(vector);
  }
  for(unsigned int i=0; i< vectorIntTags_.size();i++)
  {
    TString nameT = formBranchName(vectorIntTags_.at(i), vectorIntNames_);
    if( debug_ ) std::cout<<"vectorIntTags :  i : "<<i<<"  nameT : "<<nameT<<std::endl;
    tree_->Branch(nameT, "std::vector<int>", &(vectorIntVector_.at(i)), 32000, 0);
  }

//
  for(unsigned int i=0; i< vectorBoolTags_.size();i++)
  {
    std::vector<unsigned int> vector;
    vectorBoolVector_.push_back(vector);
  }
  for(unsigned int i=0; i< vectorBoolTags_.size();i++)
  {
    TString nameT = formBranchName(vectorBoolTags_.at(i), vectorBoolNames_);
    if( debug_ ) std::cout<<"vectorBoolTags :  i : "<<i<<"  nameT : "<<nameT<<std::endl;
    tree_->Branch(nameT, "std::vector<unsigned int>", &(vectorBoolVector_.at(i)), 32000, 0);
  }

//
  for(unsigned int i=0; i< vectorStringTags_.size();i++)
  {
    std::vector<std::string> vector;
    vectorStringVector_.push_back(vector);
  }
  for(unsigned int i=0; i< vectorStringTags_.size();i++)
  {
    TString nameT = formBranchName(vectorStringTags_.at(i), vectorStringNames_);
    if( debug_ ) std::cout<<"vectorStringTags :  i : "<<i<<"  nameT : "<<nameT<<std::endl;
    tree_->Branch(nameT, "std::vector<std::string>", &(vectorStringVector_.at(i)), 32000, 0);
  }

//
  for(unsigned int i=0; i< vectorTLorentzVectorTags_.size();i++)
  {
    std::vector<TLorentzVector> vector;
    vectorTLorentzVector_.push_back(vector);
  }
  for(unsigned int i=0; i< vectorTLorentzVectorTags_.size();i++)
  {
    TString nameT = formBranchName(vectorTLorentzVectorTags_.at(i), vectorTLorentzVectorNames_);
    if( debug_ ) std::cout<<"vectorTLorentzVectorTags :  i : "<<i<<"  nameT : "<<nameT<<std::endl;
    tree_->Branch(nameT, "std::vector<TLorentzVector>", &(vectorTLorentzVector_.at(i)), 32000, 0);
  }
  if( debug_ ) std::cout<<std::endl;
}

// ------------ method called once each job just after ending the event loop  ------------
void 
stopTreeMaker::endJob() {
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
stopTreeMaker::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

void 
stopTreeMaker::setBranchVariablesToDefault() 
{
  // event information
  runNum_=0;
  lumiBlockNum_=0;
  evtNum_=0;

  for(unsigned int i = 0; i < varsDouble_.size(); ++i) {
    varsDouble_.at(i) = 9999.;
  }
  for(unsigned int i = 0; i < varsInt_.size(); ++i) {
    varsInt_.at(i) = 9999;
  }
  for(unsigned int i = 0; i < varsBool_.size(); ++i) {
    varsBool_.at(i) = 0;
  }
  for(unsigned int i = 0; i < varsString_.size(); ++i) {
    varsString_.at(i) = "";
  }
  for(unsigned int i = 0; i < varsTLorentzVector_.size(); ++i){
    varsTLorentzVector_.at(i).SetXYZT(0, 0, 0, 0);
  }

  for(unsigned int i=0; i < vectorDoubleVector_.size();i++)
  {
    vectorDoubleVector_.at(i).clear();
  }
  for(unsigned int i=0; i < vectorIntVector_.size();i++)
  {
    vectorIntVector_.at(i).clear();
  }
  for(unsigned int i=0; i < vectorBoolVector_.size();i++)
  {
    vectorBoolVector_.at(i).clear();
  }
  for(unsigned int i=0; i < vectorStringVector_.size();i++)
  {
    vectorStringVector_.at(i).clear();
  }
  for(unsigned int i=0; i < vectorTLorentzVector_.size();i++)
  {
    vectorTLorentzVector_.at(i).clear();
  }
}

TString stopTreeMaker::formBranchName(const edm::InputTag & varTag, const std::vector<std::string> & vectorNames){

  std::string label = varTag.label(), instance = varTag.instance();

// Assume label + instance can descriminate any variables.
// If not, same variables but from different processes stored? why?
  TString nameT, labelPLUSinstanceT, keyStrT;
  
  if(instance.empty()){
     TString labelT = label;
     keyStrT = labelT;
     TObjArray * vlist = labelT.Tokenize(": ");
     if( vlist->GetEntries() >= 2 ){
       TObjString* obj = dynamic_cast<TObjString*>(vlist->At(1));
       nameT = obj->GetString();
     }else{
       TObjString* obj = dynamic_cast<TObjString*>(vlist->At(0));
       nameT = obj->GetString();
     }
     for(int ie=0; ie<vlist->GetEntries(); ie++){
       TObjString* obj = dynamic_cast<TObjString*>(vlist->At(ie));
       labelPLUSinstanceT += obj->GetString();
       if( ie != vlist->GetEntries()-1 ) labelPLUSinstanceT += "_";
     }
  }else{
     nameT = instance;
     labelPLUSinstanceT = label + "_" + instance;
     keyStrT = label + ":" + instance;
  }

  std::vector<TString>::iterator it = std::find(cachedNames_.begin(), cachedNames_.end(), nameT);
  if( it != cachedNames_.end() ){
     nameT = labelPLUSinstanceT;
  }

// Override name takes the format "label:instance|NEWNAME".
  for(unsigned int in=0; in<vectorNames.size(); in++){
     TString tmpT = vectorNames[in];
     TObjArray * vlist = tmpT.Tokenize("|");
     if( vlist->GetEntries() == 2 ){
        TObjString * obj0 = dynamic_cast<TObjString*>(vlist->At(0));
        TString objT0 = obj0->GetString();
        if( objT0 != keyStrT ) continue;
        TObjString * obj1 = dynamic_cast<TObjString*>(vlist->At(1));
        nameT = obj1->GetString();
     }
  }

  cachedNames_.push_back(nameT);

  return nameT;
}

//define this as a plug-in
DEFINE_FWK_MODULE(stopTreeMaker);
