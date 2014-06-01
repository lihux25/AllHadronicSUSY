
from SandBox.Skims.basicJetSelector_drt_from_AOD_cfi import *
from PhysicsTools.PatAlgos.selectionLayer1.jetCountFilter_cfi import *

# PFJets (with CHS)
stopJetsPFchsPt30     = selectedPatJetsRA2.clone()
stopJetsPFchsPt30.src = cms.InputTag('patJetsPF')
stopJetsPFchsPt30.cut = cms.string('pt > 30')

stopJetsPFchsPt70Eta24 = selectedPatJetsRA2.clone()
stopJetsPFchsPt70Eta24.src = cms.InputTag("patJetsPF")
stopJetsPFchsPt70Eta24.cut = cms.string("pt>70 && abs(eta)<2.4")

stopJetsPFchsPt50Eta24 = selectedPatJetsRA2.clone()
stopJetsPFchsPt50Eta24.src = cms.InputTag("patJetsPF")
stopJetsPFchsPt50Eta24.cut = cms.string("pt>50 && abs(eta)<2.4")

stopJetsPFchsPt30Eta24 = selectedPatJetsRA2.clone()
stopJetsPFchsPt30Eta24.src = cms.InputTag("patJetsPF")
stopJetsPFchsPt30Eta24.cut = cms.string("pt>30 && abs(eta)<2.4")

stopJetsPFchsPt70eta2p5 = selectedPatJetsRA2.clone()
stopJetsPFchsPt70eta2p5.src = cms.InputTag('patJetsPF')
stopJetsPFchsPt70eta2p5.cut = cms.string('pt > 70 & abs(eta) < 2.5')

#count jets
stopCountPFchsJetsPt30           = countPatJets.clone()
stopCountPFchsJetsPt30.src       = cms.InputTag('stopJetsPFchsPt30')
stopCountPFchsJetsPt30.minNumber = cms.uint32(6)

count2JetsPFchsPt70Eta24Std = countPatJets.clone()
count2JetsPFchsPt70Eta24Std.src = cms.InputTag("stopJetsPFchsPt70Eta24")
count2JetsPFchsPt70Eta24Std.minNumber = cms.uint32(2)

count4JetsPFchsPt50Eta24Std = countPatJets.clone()
count4JetsPFchsPt50Eta24Std.src = cms.InputTag("stopJetsPFchsPt50Eta24")
count4JetsPFchsPt50Eta24Std.minNumber = cms.uint32(4)

count5JetsPFchsPt30Eta24Std = countPatJets.clone()
count5JetsPFchsPt30Eta24Std.src = cms.InputTag("stopJetsPFchsPt30Eta24")
count5JetsPFchsPt30Eta24Std.minNumber = cms.uint32(5)

count5JetsPFchsPt30Std = countPatJets.clone()
count5JetsPFchsPt30Std.src = cms.InputTag("stopJetsPFchsPt30")
count5JetsPFchsPt30Std.minNumber = cms.uint32(5)

stopCountPFchsJetsPt70eta2p5           = countPatJets.clone()
stopCountPFchsJetsPt70eta2p5.src       = cms.InputTag('stopJetsPFchsPt70eta2p5')
stopCountPFchsJetsPt70eta2p5.minNumber = cms.uint32(2)


# need to have counter for leading 2 jets with pT>70 GeV & |eta|<2.5


# should we have a counter for b-jets too ?


stopPFJets = cms.Sequence(
  stopJetsPFchsPt30 * stopJetsPFchsPt30Eta24 * stopJetsPFchsPt50Eta24 * stopJetsPFchsPt70Eta24 *
  stopJetsPFchsPt70eta2p5
)
