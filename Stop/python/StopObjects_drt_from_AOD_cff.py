
from SandBox.Skims.RA2Cleaning_cff       import *
from SandBox.Stop.StopJets_drt_from_AOD_cff   import *
from SandBox.Stop.StopLeptons_cff        import *
#from SandBox.Stop.StopPhotons_cff       import *
from SandBox.Stop.StopTrackIsolation_cff import *
from SandBox.Stop.StopTauJets_cff        import *
from SandBox.Stop.StopBTagJets_cff       import *

stopObjects = cms.Sequence(  
  stopPFJets *
  #stopMuons *     # use from RA2 for now, update soon
  #stopElectrons * # use from RA2 for now, update soon
  stopIsoTracks *
  stopTauJets *
  stopBJets
  #stopPhotons
)

stopObjectsOnPatTuples = cms.Sequence(  
  stopPFJets *
  #stopMuons *     # use from RA2 for now, update soon
  #stopElectrons * # use from RA2 for now, update soon
  stopIsoTracks *
  stopTauJets *
  stopBJets
  #stopPhotons
)

