import FWCore.ParameterSet.Config as cms

process = cms.Process("Analysis")

#===================== Message Logger =============================
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.categories.append('PATSummaryTables')
process.MessageLogger.cerr.PATSummaryTables = cms.untracked.PSet(
        limit = cms.untracked.int32(10),
            reportEvery = cms.untracked.int32(1)
            )
process.options = cms.untracked.PSet(
        wantSummary = cms.untracked.bool(True)
            )
process.MessageLogger.cerr.FwkReport.reportEvery = 500


# Check for ny duplicates
#process.source.duplicateCheckMode = cms.untracked.string('noDuplicateCheck')

process.load("Configuration.StandardSequences.Geometry_cff")
process.load("Configuration.StandardSequences.MagneticField_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.load("SimGeneral.HepPDTESSource.pythiapdt_cfi")

runningOnMC = False
process.GlobalTag.globaltag = "START52_V11C::All"
if runningOnMC == False:
    process.GlobalTag.globaltag = "GR_R_52_V9D::All"

process.source = cms.Source("PoolSource",
   fileNames = cms.untracked.vstring(
    #"/store/user/lpcsusyhad/lacroix/2012SEP05/T2tt/lacroix/T2tt_mStop650_mLSP0_NOCUTS_09Aug2012V1/susypat_T2tt_650_0_job1.root"
    "file:/eos/uscms/store/user/lhx/2012DirectStop/Aug21/lhx/smallScan-T2tt_xpar500_ypar100/smallScan-T2tt_xpar500_ypar100/0a1dcad3823fc691dc21103faf8c043f/SUSYPAT_1_1_0vS.root"
    #,"file:/eos/uscms/store/user/lhx/2012DirectStop/Aug21/lhx/smallScan-T2tt_xpar500_ypar100/smallScan-T2tt_xpar500_ypar100/0a1dcad3823fc691dc21103faf8c043f/SUSYPAT_1_1_9s9.root"
    #,"file:/eos/uscms/store/user/lhx/2012DirectStop/Aug21/lhx/smallScan-T2tt_xpar500_ypar100/smallScan-T2tt_xpar500_ypar100/0a1dcad3823fc691dc21103faf8c043f/SUSYPAT_1_1_9xY.root"
    #,"file:/eos/uscms/store/user/lhx/2012DirectStop/Aug21/lhx/smallScan-T2tt_xpar500_ypar100/smallScan-T2tt_xpar500_ypar100/0a1dcad3823fc691dc21103faf8c043f/SUSYPAT_1_1_Bd4.root"
    #,"file:/eos/uscms/store/user/lhx/2012DirectStop/Aug21/lhx/smallScan-T2tt_xpar500_ypar100/smallScan-T2tt_xpar500_ypar100/0a1dcad3823fc691dc21103faf8c043f/SUSYPAT_1_1_Ezr.root"
    #,"file:/eos/uscms/store/user/lhx/2012DirectStop/Aug21/lhx/smallScan-T2tt_xpar500_ypar100/smallScan-T2tt_xpar500_ypar100/0a1dcad3823fc691dc21103faf8c043f/SUSYPAT_1_1_FFE.root"
    #,"file:/eos/uscms/store/user/lhx/2012DirectStop/Aug21/lhx/smallScan-T2tt_xpar500_ypar100/smallScan-T2tt_xpar500_ypar100/0a1dcad3823fc691dc21103faf8c043f/SUSYPAT_1_1_FRQ.root"
  )
)

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.source.skipEvents = cms.untracked.uint32(0)  

#=============== configure cleaning sequence ================================
process.load("SandBox.Skims.filterBoolean_cfi")
process.RA2_HBHENoiseFilterRA2    = process.booleanFilter.clone()
process.RA2_HBHENoiseFilterRA2.ResultSource = cms.InputTag("HBHENoiseFilterRA2","HBHENoiseFilterResult","PAT")
process.RA2_beamHaloFilter        = process.booleanFilter.clone()
process.RA2_beamHaloFilter.ResultSource = cms.InputTag("beamHaloFilter")
process.RA2_eeNoiseFilter         = process.booleanFilter.clone()
process.RA2_eeNoiseFilter.ResultSource = cms.InputTag("eeNoiseFilter")
process.RA2_trackingFailureFilter = process.booleanFilter.clone()
process.RA2_trackingFailureFilter.ResultSource = cms.InputTag("trackingFailureFilter")
process.RA2_inconsistentMuons     = process.booleanFilter.clone()
process.RA2_inconsistentMuons.ResultSource = cms.InputTag("inconsistentMuons")
process.RA2_greedyMuons           = process.booleanFilter.clone()
process.RA2_greedyMuons.ResultSource = cms.InputTag("greedyMuons")
process.RA2_EcalTPFilter          = process.booleanFilter.clone()
process.RA2_EcalTPFilter.ResultSource = cms.InputTag("ra2EcalTPFilter")
process.RA2_EcalBEFilter          = process.booleanFilter.clone()
process.RA2_EcalBEFilter.ResultSource = cms.InputTag("ra2EcalBEFilter")
process.HcalLaserEventFilter      = process.booleanFilter.clone()
process.HcalLaserEventFilter.ResultSource = cms.InputTag("hcalLaserEventFilter")
process.EEBadScFilter             = process.booleanFilter.clone()
process.EEBadScFilter.ResultSource = cms.InputTag("eeBadScFilter")

process.cleaningSeq  = cms.Sequence(
    process.RA2_HBHENoiseFilterRA2
  * process.RA2_beamHaloFilter
  * process.RA2_eeNoiseFilter
  * process.RA2_trackingFailureFilter
  * process.RA2_inconsistentMuons
  * process.RA2_greedyMuons
  * process.RA2_EcalTPFilter
  * process.RA2_EcalBEFilter
  #* process.HcalLaserEventFilter
  #* process.EEBadScFilter
)

##============ configure output module configuration ========================
process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string('test.root')
)

process.load("SandBox.Stop.StopObjects_cff")
process.load("SandBox.Stop.StopSelection_cff")

#process.analysisSeq = cms.Sequence(
#    #process.countJetsAK5PFPt50Eta25 *
#)    

#process.load("SandBox.Stop.goldenTauSelector_cfi")
#process.goldenTauSelector.doTauVeto = True
#process.goldenTauSelector.jetSrc = cms.InputTag("patJetsAK5PF")
#process.goldenTauSelector.jetSrc = cms.InputTag("patJetsPF")

#process.load("SandBox.Stop.tauJetsProducer_cfi")
#process.tauJetsProducer.JetSrc = cms.InputTag("patJetsAK5PF")
#process.tauJetsProducer.JetSrc = cms.InputTag("patJetsPF")

#process.stopFullPFchsSelectionNoMET.remove(process.stopIsoTrackVeto)

process.ppf = cms.Path(process.stopObjectsOnPatTuples *
                       process.stopFullPFchsSelectionNoMET 
                       #process.goldenTauSelector
                       #process.tauJetsProducer
                       )



###-- Dump config ------------------------------------------------------------
##file = open('SusyPAT_RA2414_cfg.py','w')
##file.write(str(process.dumpPython()))
##file.close()
