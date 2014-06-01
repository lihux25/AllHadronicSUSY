
from SandBox.Skims.basicJetSelector_drt_from_AOD_cfi import *
from PhysicsTools.PatAlgos.selectionLayer1.jetCountFilter_cfi import *

# PFJets (default)
patJetsAK5PFPt30     = selectedPatJetsRA2.clone()
patJetsAK5PFPt30.src = cms.InputTag('patJetsAK5PF')
patJetsAK5PFPt30.cut = cms.string('pt > 30')

patJetsAK5PFPt50Eta25     = selectedPatJetsRA2.clone()
patJetsAK5PFPt50Eta25.src = cms.InputTag('patJetsAK5PFPt30')
patJetsAK5PFPt50Eta25.cut = cms.string('pt > 50 & abs(eta) < 2.5')

# PFJets - filters
countJetsAK5PFPt50Eta25           = countPatJets.clone()
countJetsAK5PFPt50Eta25.src       = cms.InputTag('patJetsAK5PFPt50Eta25')
countJetsAK5PFPt50Eta25.minNumber = cms.uint32(3)

# PF sequences
ra2PFJets = cms.Sequence(
  patJetsAK5PFPt30 *
  patJetsAK5PFPt50Eta25
)


# PFJets (with CHS)
patJetsPFchsPt30     = selectedPatJetsRA2.clone()
patJetsPFchsPt30.src = cms.InputTag('patJetsPF')
patJetsPFchsPt30.cut = cms.string('pt > 30')

patJetsPFchsPt50Eta25     = selectedPatJetsRA2.clone()
patJetsPFchsPt50Eta25.src = cms.InputTag('patJetsPFchsPt30')
patJetsPFchsPt50Eta25.cut = cms.string('pt > 50 & abs(eta) < 2.5')

# PFJets - filters
countJetsPFchsPt50Eta25           = countPatJets.clone()
countJetsPFchsPt50Eta25.src       = cms.InputTag('patJetsPFchsPt50Eta25')
countJetsPFchsPt50Eta25.minNumber = cms.uint32(3)

# PF sequences
ra2PFchsJets = cms.Sequence(
  patJetsPFchsPt30 *
  patJetsPFchsPt50Eta25
)
