
from AllHadronicSUSY.Stop.dPhiFilter_cfi import *

jetsMETDPhiFilter = dPhiFilter.clone()
jetsMETDPhiFilter.jetSrc = cms.InputTag("patJetsPF")
jetsMETDPhiFilter.metSrc = cms.InputTag("patMETsPF")
