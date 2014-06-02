
from AllHadronicSUSY.Skims.RA2Jets_drt_from_AOD_cff import *
from AllHadronicSUSY.Skims.RA2HT_cff import *
from AllHadronicSUSY.Skims.RA2MHT_cff import *
from AllHadronicSUSY.Skims.RA2DeltaR_cff import *
from AllHadronicSUSY.Skims.RA2Leptons_cff import *
#from AllHadronicSUSY.Skims.RA2LeptonVeto_cff import *
#from AllHadronicSUSY.Skims.RA2Cleaning_cff import *

ra2FullPFSelectionNoMHT = cms.Sequence(
  countJetsAK5PFPt50Eta25 *
  htPFFilter *
  jetMHTPFDPhiFilter *
  ra2PFMuonVeto *
  ra2ElectronVeto
)

ra2FullPFSelection = cms.Sequence(
  ra2FullPFSelectionNoMHT *
  mhtPFFilter
)

ra2FullPFchsSelectionNoMHT = cms.Sequence(
  countJetsPFchsPt50Eta25 *
  htPFchsFilter *
  jetMHTPFchsDPhiFilter *
  ra2PFMuonVeto *
  ra2ElectronVeto
)

ra2FullPFchsSelection = cms.Sequence(
  ra2FullPFchsSelectionNoMHT *
  mhtPFchsFilter
)
