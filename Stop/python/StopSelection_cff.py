
#from SandBox.Stop.StopJets_cff import *
#from SandBox.Stop.StopTrackIsolation_cff import *
##from SandBox.Stop.RA2Leptons_cff import *
#from SandBox.Stop.StopTauJets_cff        import *
from SandBox.Stop.StopObjects_cff        import *
from SandBox.Stop.StopDPhiSelection_cff  import *

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
