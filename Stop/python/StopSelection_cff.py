
#from AllHadronicSUSY.Stop.StopJets_cff import *
#from AllHadronicSUSY.Stop.StopTrackIsolation_cff import *
##from AllHadronicSUSY.Stop.RA2Leptons_cff import *
#from AllHadronicSUSY.Stop.StopTauJets_cff        import *
from AllHadronicSUSY.Stop.StopObjects_cff        import *
from AllHadronicSUSY.Stop.StopDPhiSelection_cff  import *

stopFullPFchsSelectionNoMET = cms.Sequence(
  stopCountPFchsJetsPt30 *
  stopCountPFchsJetsPt70eta2p5 *
  stopCountBJets *
  jetsMETDPhiFilter *
  stopPFMuonVeto  *  
  stopElectronVeto * 
  stopTauJetVeto   
  #stopIsoTrackVeto # need to check the code
)

stopFullPFchsSelection = cms.Sequence(
  stopFullPFchsSelectionNoMET #*
  # add met filter here
)
