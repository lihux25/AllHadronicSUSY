import FWCore.ParameterSet.Config as cms

stopTreeMaker = cms.EDProducer(
'stopTreeMaker',
# Name of the output tree
TreeName          = cms.string('AUX'),
## might help if something isn working wilil produce couts
debug = cms.bool(False),
# List of InputTags for Float_t variables (Float_t) stored in
# optional names to store in the tree can be defined  not only will have an effect if the number of input tags for variable is exactly the same as number of optional names!!
VarsDouble        = cms.VInputTag(),
VarsDoubleNamesInTree = cms.vstring(),
# List of InputTags for Int variables (Int) stored in
# optional names to store in the tree can be defined  not only will have an effect if the number of input tags for variable is exactly the same as number of optional names!!
VarsInt        = cms.VInputTag(),
VarsIntNamesInTree = cms.vstring(),
# List of InputTags for bool variables (bool) stored in
# optional names to store in the tree can be defined  not only will have an effect if the number of input tags for variable is exactly the same as number of optional names!!
VarsBool        = cms.VInputTag(),
VarsBoolNamesInTree = cms.vstring(),

VarsString      = cms.VInputTag(),
VarsStringNamesInTree = cms.vstring(),

# List of InputTags for TLorentz variables (TLorentz) stored in
# optional names to store in the tree can be defined  not only will have an effect if the number of input tags for variable is exactly the same as number of optional names!!
VarsTLorentzVector        = cms.VInputTag(),
VarsTLorentzVectorNamesInTree = cms.vstring(),

VectorDouble              = cms.VInputTag(),
VectorDoubleNamesInTree   = cms.vstring(),

VectorInt                 = cms.VInputTag(),
VectorIntNamesInTree      = cms.vstring(),

VectorBool                = cms.VInputTag(),
VectorBoolNamesInTree     = cms.vstring(),

VectorString              = cms.VInputTag(),
VectorStringNamesInTree   = cms.vstring(),

VectorTLorentzVector        = cms.VInputTag(),
VectorTLorentzVectorNamesInTree = cms.vstring(),
)
