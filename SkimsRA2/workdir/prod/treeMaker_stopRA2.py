import FWCore.ParameterSet.Config as cms

process = cms.Process("SUSY")

## MessageLogger
process.load("FWCore.MessageLogger.MessageLogger_cfi")

## Options and Output Report
process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )

## Source
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
      '/store/relval/CMSSW_3_8_0_pre8/RelValTTbar/GEN-SIM-RECO/START38_V6-v1/0004/847D00B0-608E-DF11-A37D-003048678FA0.root'
    )
)
## Maximal Number of Events
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

# The following is make patJets, but EI is done with the above
process.load("PhysicsTools.PatAlgos.producersLayer1.patCandidates_cff")
process.load("Configuration.EventContent.EventContent_cff")
process.load('Configuration.StandardSequences.Geometry_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

import os
import sys
import re

import FWCore.ParameterSet.VarParsing as VarParsing
options = VarParsing.VarParsing ('standard')

options.register('GlobalTag', "PHYS14_25_V1::All", VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.string, "GlobaTTag to use (otherwise default Pat GT is used)")
options.register('mcInfo', True, VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.int, "process MonteCarlo data, default is data")
options.register('jetCorrections', 'L2Relative', VarParsing.VarParsing.multiplicity.list, VarParsing.VarParsing.varType.string, "Level of jet corrections to use: Note the factors are read from DB via GlobalTag")
options.jetCorrections.append('L3Absolute')

options.register('hltName', 'HLT', VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.string, "HLT menu to use for trigger matching")
options.register('mcVersion', '', VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.string, "'36X' for example. Used for specific MC fix")
options.register('jetTypes', 'AK4PF', VarParsing.VarParsing.multiplicity.list, VarParsing.VarParsing.varType.string, "Additional jet types that will be produced (AK4Calo and AK4PF, cross cleaned in PF2PAT, are included anyway)")
options.register('hltSelection', '*', VarParsing.VarParsing.multiplicity.list, VarParsing.VarParsing.varType.string, "hlTriggers (OR) used to filter events. for data: ''HLT_Mu9', 'HLT_IsoMu9', 'HLT_IsoMu13_v*''; for MC, HLT_Mu9")
options.register('addKeep', '', VarParsing.VarParsing.multiplicity.list, VarParsing.VarParsing.varType.string, "Additional keep and drop statements to trim the event content")

options.register('dataVersion', '', VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.string, "'36X' for example. Used for specific DATA fix")

options.register('debug', False, VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.bool, "switch on/off debug mode")

options.register('test', False, VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.int, "switch on/off debug mode")

options.register('doPtHatWeighting', False, VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.int, "PtHat weighting for QCD flat samples, default is False")

options.register('fileslist', '', VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.string, "name of a file with input source list")

options.register('fastsim', False, VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.int, "fastsim sample or not, default is False")

options.register('doTopTagger', True, VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.int, "do top tagger or not, default is True")

options.register('usePhiCorrMET', False, VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.int, "use phi corrected MET or not, default is False")

options.register('reducedfilterTags', True, VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.int, "use phi corrected MET or not, default is True")

options.register('smsModel', 'T1tttt', VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.string, "SMS model name")
options.register('smsMotherMass',  -1, VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.int, "SMS mother mass")
options.register('smsDaughterMass',  -1, VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.int, "SMS daughter mass")
options.register('selSMSpts', False, VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.int, "select model points")

options.register('pythia8', True, VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.int, "pythi8 or not, default True")

options.parseArguments()
options._tagOrder =[]

print options

#-- Message Logger ------------------------------------------------------------
process.MessageLogger.cerr.FwkReport.reportEvery = 100
if options.debug:
   process.MessageLogger.cerr.FwkReport.reportEvery = 1

#-- Input Source --------------------------------------------------------------
inputfiles = cms.untracked.vstring()
if options.fileslist:
   if os.path.exists(options.fileslist) == False or os.path.isfile(options.fileslist) == False:
      sys.exit(5)
   else:
      ifile = open(options.fileslist, 'r')
      for line in ifile.readlines():
         inputfiles.append(line)

print "inputfiles : \n", inputfiles, "\n"

if options.files:
   process.source.fileNames = options.files
elif options.fileslist:
   process.source.fileNames = inputfiles
else:
   process.source.fileNames = [
       '/store/mc/Phys14DR/SMS-T1tttt_2J_mGl-1500_mLSP-100_Tune4C_13TeV-madgraph-tauola/MINIAODSIM/PU40bx25_PHYS14_25_V1-v1/00000/2281F34C-8475-E411-9E7D-00259073E450.root',
       '/store/mc/Phys14DR/SMS-T1tttt_2J_mGl-1500_mLSP-100_Tune4C_13TeV-madgraph-tauola/MINIAODSIM/PU40bx25_PHYS14_25_V1-v1/00000/A6D4FF88-8275-E411-9259-20CF305616F4.root',
       '/store/mc/Phys14DR/SMS-T1tttt_2J_mGl-1500_mLSP-100_Tune4C_13TeV-madgraph-tauola/MINIAODSIM/PU40bx25_PHYS14_25_V1-v1/00000/A6EFFE6A-9A75-E411-9218-002590D0B0D8.root',
       '/store/mc/Phys14DR/SMS-T1tttt_2J_mGl-1500_mLSP-100_Tune4C_13TeV-madgraph-tauola/MINIAODSIM/PU40bx25_PHYS14_25_V1-v1/10000/E67905FE-8B75-E411-8D33-E0CB4E29C511.root' 
   ]

process.maxEvents.input = options.maxEvents

#-- Calibration tag -----------------------------------------------------------
if options.GlobalTag:
   process.GlobalTag.globaltag = options.GlobalTag

if options.mcInfo == False: options.jetCorrections.append('L2L3Residual')
options.jetCorrections.insert(0, 'L1FastJet')

print "jetCorrections: "
print options.jetCorrections

from RecoJets.JetProducers.ak4PFJets_cfi import ak4PFJets
from RecoJets.JetProducers.ak4GenJets_cfi import ak4GenJets
from RecoMET.METProducers.PFMET_cfi import pfMet

#select isolated collections
process.selectedMuons = cms.EDFilter("CandPtrSelector", src = cms.InputTag("slimmedMuons"), cut = cms.string('''abs(eta)<2.5 && pt>5. &&
   (pfIsolationR04().sumChargedHadronPt+
    max(0.,pfIsolationR04().sumNeutralHadronEt+
    pfIsolationR04().sumPhotonEt-
    0.50*pfIsolationR04().sumPUPt))/pt < 0.20 && 
    (isPFMuon && (isGlobalMuon || isTrackerMuon) )'''))
process.selectedElectrons = cms.EDFilter("CandPtrSelector", src = cms.InputTag("slimmedElectrons"), cut = cms.string('''abs(eta)<2.5 && pt>5. &&
    gsfTrack.isAvailable() &&
    gsfTrack.hitPattern().numberOfLostHits('MISSING_INNER_HITS')<2 && 
    (pfIsolationVariables().sumChargedHadronPt+
    max(0.,pfIsolationVariables().sumNeutralHadronEt+
    pfIsolationVariables().sumPhotonEt-
    0.5*pfIsolationVariables().sumPUPt))/pt < 0.20'''))

## --- Selection sequences ---------------------------------------------
# leptons
process.load("PhysicsTools.PatAlgos.selectionLayer1.muonCountFilter_cfi")
process.load("PhysicsTools.PatAlgos.selectionLayer1.electronCountFilter_cfi")
process.selectedIDIsoMuons = cms.EDFilter("CandPtrSelector", src = cms.InputTag("slimmedMuons"), cut = cms.string('''abs(eta)<2.5 && pt>5. &&
   (pfIsolationR04().sumChargedHadronPt+
   max(0.,pfIsolationR04().sumNeutralHadronEt+
   pfIsolationR04().sumPhotonEt-
   0.50*pfIsolationR04().sumPUPt))/pt < 0.20 &&
   (isPFMuon && (isGlobalMuon || isTrackerMuon) )'''))
process.selectedIDMuons = cms.EDFilter("CandPtrSelector", src = cms.InputTag("slimmedMuons"), cut = cms.string('''abs(eta)<2.5 && pt>5. &&
   (isPFMuon && (isGlobalMuon || isTrackerMuon) )'''))
process.selectedIDIsoElectrons = cms.EDFilter("CandPtrSelector", src = cms.InputTag("slimmedElectrons"), cut = cms.string('''abs(eta)<2.5 && pt>5. &&
   gsfTrack.isAvailable() &&
   gsfTrack.hitPattern().numberOfLostHits('MISSING_INNER_HITS')<2 &&
   (pfIsolationVariables().sumChargedHadronPt+
   max(0.,pfIsolationVariables().sumNeutralHadronEt+
   pfIsolationVariables().sumPhotonEt-
   0.5*pfIsolationVariables().sumPUPt))/pt < 0.20'''))
process.selectedIDElectrons = cms.EDFilter("CandPtrSelector", src = cms.InputTag("slimmedElectrons"), cut = cms.string('''abs(eta)<2.5 && pt>5. &&
   gsfTrack.isAvailable() &&
   gsfTrack.hitPattern().numberOfLostHits('MISSING_INNER_HITS')<2'''))

#do projections
process.pfCHS = cms.EDFilter("CandPtrSelector", src = cms.InputTag("packedPFCandidates"), cut = cms.string("fromPV"))
process.pfNoMuonCHS =  cms.EDProducer("CandPtrProjector", src = cms.InputTag("pfCHS"), veto = cms.InputTag("selectedMuons"))
process.pfNoElectronsCHS = cms.EDProducer("CandPtrProjector", src = cms.InputTag("pfNoMuonCHS"), veto =  cms.InputTag("selectedElectrons"))

process.pfNoMuon =  cms.EDProducer("CandPtrProjector", src = cms.InputTag("packedPFCandidates"), veto = cms.InputTag("selectedMuons"))
process.pfNoElectrons = cms.EDProducer("CandPtrProjector", src = cms.InputTag("pfNoMuon"), veto =  cms.InputTag("selectedElectrons"))

process.ak4GenJets = ak4GenJets.clone(src = 'packedGenParticles', rParam = 0.4)

process.pfMet = pfMet.clone(src = "packedPFCandidates")
process.pfMet.calculateSignificance = False # this can't be easily implemented on packed PF candidates at the moment

#from PhysicsTools.PatAlgos.producersLayer1.metProducer_cfi import patMETs
process.load('PhysicsTools.PatAlgos.producersLayer1.metProducer_cfi')
#from JetMETCorrections.Type1MET.pfMETCorrections_cff import *
from JetMETCorrections.Type1MET.correctionTermsPfMetType1Type2_cff import *
from PhysicsTools.PatUtils.patPFMETCorrections_cff import patPFJetMETtype1p2Corr

process.patMETs.addGenMET = cms.bool(False)

process.patJetPartons.particles = "prunedGenParticles"
process.patJetPartons.skipFirstN = cms.uint32(0) # do not skip first 6 particles, we already pruned some!
process.patJetPartons.acceptNoDaughters = cms.bool(True) # as we drop intermediate stuff, we need to accept quarks with no siblings

process.MessageLogger.suppressWarning = cms.untracked.vstring('ecalLaserCorrFilter','manystripclus53X','toomanystripclus53X')
process.options.allowUnscheduled = cms.untracked.bool(True)

#Analysis related configuration
import HLTrigger.HLTfilters.hltHighLevel_cfi as hlt
if options.hltSelection:
   process.hltFilter = hlt.hltHighLevel.clone(
      TriggerResultsTag = cms.InputTag("TriggerResults","",options.hltName),
      HLTPaths = cms.vstring(options.hltSelection),
      throw = True, # Don't throw?!
      andOr = True
   )

process.load("RecoJets.Configuration.GenJetParticles_cff")
process.genParticlesForJets.src = cms.InputTag("prunedGenParticles")

process.load("AllHadronicSUSY.SkimsRA2.simpleJetSelector_cfi")
process.selectedPatJetsRA2 = process.simpleJetSelector.clone()

process.load("PhysicsTools.PatAlgos.selectionLayer1.jetCountFilter_cfi")
# PFJets (with CHS)
process.ak4patJetsPFchsPt10     = process.selectedPatJetsRA2.clone()
process.ak4patJetsPFchsPt10.jetSrc = cms.InputTag('slimmedJets')
process.ak4patJetsPFchsPt10.pfJetCut = cms.string('pt > 10')

process.ak4patJetsPFchsPt30     = process.selectedPatJetsRA2.clone()
process.ak4patJetsPFchsPt30.jetSrc = cms.InputTag('slimmedJets')
process.ak4patJetsPFchsPt30.pfJetCut = cms.string('pt > 30')

process.ak4patJetsPFchsPt50Eta25     = process.selectedPatJetsRA2.clone()
process.ak4patJetsPFchsPt50Eta25.jetSrc = cms.InputTag('slimmedJets')
process.ak4patJetsPFchsPt50Eta25.pfJetCut = cms.string('pt > 50 & abs(eta) < 2.5')

# PFJets - filters
process.countak4JetsPFchsPt50Eta25           = process.countPatJets.clone()
process.countak4JetsPFchsPt50Eta25.src       = cms.InputTag('ak4patJetsPFchsPt50Eta25')
process.countak4JetsPFchsPt50Eta25.minNumber = cms.uint32(3)

process.ra2PFchsJets = cms.Sequence( process.ak4patJetsPFchsPt10 * process.ak4patJetsPFchsPt30 * process.ak4patJetsPFchsPt50Eta25 )

# HT 
process.load("AllHadronicSUSY.Skims.htProducer_cfi")
process.load("AllHadronicSUSY.Skims.htFilter_cfi")
process.htPFchs = process.ht.clone()
process.htPFchs.JetCollection = cms.InputTag("ak4patJetsPFchsPt50Eta25")

process.htPFchsFilter = process.htFilter.clone()
process.htPFchsFilter.HTSource = cms.InputTag("htPFchs")

# MHT
process.load("AllHadronicSUSY.Skims.mhtProducer_cfi")
process.load("AllHadronicSUSY.Skims.mhtFilter_cfi")
process.mhtPFchs = process.mht.clone()
process.mhtPFchs.JetCollection = cms.InputTag("ak4patJetsPFchsPt30")

process.mhtPFchsFilter = process.mhtFilter.clone()
process.mhtPFchsFilter.MHTSource = cms.InputTag("mhtPFchs")

# Delta Phi
process.load("AllHadronicSUSY.Skims.jetMHTDPhiFilter_cfi")

process.ak4jetMHTPFchsDPhiFilter = process.jetMHTDPhiFilter.clone()
process.ak4jetMHTPFchsDPhiFilter.JetSource = cms.InputTag("ak4patJetsPFchsPt30")
process.ak4jetMHTPFchsDPhiFilter.MHTSource = cms.InputTag("mhtPFchs")

process.ra2Objects = cms.Sequence( 
                                   process.ra2PFchsJets *
                                   process.htPFchs *
                                   process.mhtPFchs *
                                   process.selectedMuons *
                                   process.selectedElectrons *
                                   process.selectedIDIsoMuons * process.selectedIDMuons *
                                   process.selectedIDIsoElectrons * process.selectedIDElectrons
                                 )

process.load("PhysicsTools.PatAlgos.selectionLayer1.muonCountFilter_cfi")
process.load("PhysicsTools.PatAlgos.selectionLayer1.electronCountFilter_cfi")

process.countPFMuonsIDIso = process.countPatMuons.clone()
process.countPFMuonsIDIso.src = cms.InputTag('selectedIDIsoMuons')
process.countPFMuonsIDIso.minNumber = cms.uint32(1)

process.countPFElectronsIDIso = process.countPatElectrons.clone()
process.countPFElectronsIDIso.src = cms.InputTag('selectedIDIsoElectrons')
process.countPFElectronsIDIso.minNumber = cms.uint32(1)

process.ra2PFMuonVeto = cms.Sequence( ~process.countPFMuonsIDIso )
process.ra2PFElectronVeto = cms.Sequence( ~process.countPFElectronsIDIso )

############################# START SUSYPAT specifics ####################################
process.prefilterCounter        = cms.EDProducer("EventCountProducer")
process.postStdCleaningCounter  = cms.EDProducer("EventCountProducer")

# Standard Event cleaning 
process.load("AllHadronicSUSY.Skims.noscraping_cfi")
process.load("AllHadronicSUSY.Skims.vertex_cfi")

process.goodVertices = cms.EDFilter(
  "VertexSelector",
  filter = cms.bool(False),
  src = cms.InputTag("offlineSlimmedPrimaryVertices"),
  cut = cms.string("!isFake && ndof > 4 && abs(z) <= 24 && position.rho < 2")
)

process.ra2StdCleaning = cms.Sequence(
#                 process.noscraping *
                 process.oneGoodVertex
)

# an example sequence to create skimmed susypat-tuples
process.cleanpatseq = cms.Sequence(
#                      process.ra2StdCleaning          *
                      process.postStdCleaningCounter  *
                      process.ra2Objects
                      )
############################# EDN SUSYPAT specifics ####################################

process.dummyCounter = cms.EDProducer("EventCountProducer")

process.load('RecoMET.METFilters.jetIDFailureFilter_cfi')
process.jetIDFailure.JetSource = cms.InputTag("slimmedJets")
process.jetIDFailure.MinJetPt  = cms.double(30.0)
process.jetIDFailure.MaxJetEta = cms.double(999.0)
# Adjust jets due to JEC in jetIDFailure filter
if options.mcInfo == True:
   process.jetIDFailure.JECLevel = cms.untracked.string('ak4PFJetsL1FastL2L3')
else:
   process.jetIDFailure.JECLevel = cms.untracked.string('ak4PFJetsL1FastL2L3Residual')
# End of the adjusting in the jetIDFailure filter

process.load('AllHadronicSUSY.SkimsRA2.weightProducer_cfi')
process.weightProducer.inputPUfileMC   = cms.untracked.string("")
process.weightProducer.inputPUfileData = cms.untracked.string("")
if options.doPtHatWeighting:
   process.weightProducer.Method     = cms.string("PtHat")
   process.weightProducer.Exponent   = cms.double(-4.5)
   process.weightProducer.XS         = cms.double(1.0)
   process.weightProducer.NumberEvts = cms.double(1.0)
   process.weightProducer.Lumi       = cms.double(1.0)
   process.weightProducer.weightWARNingUpThreshold  = cms.double(2.0)

from JetMETCorrections.Configuration.DefaultJEC_cff import *
process.ak4PFJetschsL1FastL2L3Residual = ak4PFJetsL1FastL2L3Residual.clone( algorithm = cms.string('AK4PFchs'), src = 'slimmedJets' )
process.ak4PFJetschsL1FastL2L3 = ak4PFJetsL1FastL2L3.clone( algorithm = cms.string('AK4PFchs'), src = 'slimmedJets' )

# Default is dR = 0.3, dz < 0.05, pt > 10, reliso < 0.1
process.load("AllHadronicSUSY.Stop.trackIsolationMaker_cfi")
process.trackIsolation = process.trackIsolationFilter.clone()
process.trackIsolation.pfCandidatesTag = cms.InputTag("packedPFCandidates")
process.trackIsolation.doTrkIsoVeto = cms.bool(False)

process.loosetrackIsolation = process.trackIsolation.clone()
process.loosetrackIsolation.minPt_PFCandidate = cms.double(5.0)
process.loosetrackIsolation.isoCut            = cms.double(0.5)

process.load('AllHadronicSUSY.Stop.StopJets_drt_from_AOD_cff')

process.load("AllHadronicSUSY.SkimsRA2.nJetsForSkimsRA2_cfi")
process.load("AllHadronicSUSY.SkimsRA2.jetMHTDPhiForSkimsRA2_cfi")

# ak4 jets
process.ak4stopJetsPFchsPt30 = process.stopJetsPFchsPt30.clone(jetSrc = "slimmedJets")
process.ak4stopJetsPFchsPt50Eta24 = process.stopJetsPFchsPt50Eta24.clone(jetSrc = "slimmedJets")

process.ak4nJetsForSkimsStop = process.nJetsForSkimsRA2.clone()
process.ak4nJetsForSkimsStop.JetSource = cms.InputTag("ak4stopJetsPFchsPt30")
process.ak4jetMHTDPhiForSkimsStop = process.jetMHTDPhiForSkimsRA2.clone()
process.ak4jetMHTDPhiForSkimsStop.MHTSource = cms.InputTag("slimmedMETs")
process.ak4jetMHTDPhiForSkimsStop.JetSource = cms.InputTag("ak4stopJetsPFchsPt30")

process.ak4stophtPFchs = process.htPFchs.clone()
process.ak4stophtPFchs.JetCollection = cms.InputTag("ak4stopJetsPFchsPt50Eta24")

process.ak4stopmhtPFchs = process.mhtPFchs.clone()
process.ak4stopmhtPFchs.JetCollection = cms.InputTag("ak4stopJetsPFchsPt30")
#

process.prepareCutvars_seq = cms.Sequence( process.ak4stopJetsPFchsPt30 * process.ak4stopJetsPFchsPt50Eta24 * process.ak4nJetsForSkimsStop * process.ak4jetMHTDPhiForSkimsStop * process.ak4stophtPFchs * process.ak4stopmhtPFchs )

process.load("AllHadronicSUSY.Stop.StopBTagJets_cff")
process.stopBJets.JetSrc = cms.InputTag("stopJetsPFchsPt30")

# Other sequence
process.comb_seq = cms.Sequence(
# All cleaning && all basic variables, e.g., mht, ht...     
   process.cleanpatseq *
# hlt requirement
   process.hltFilter *
   process.weightProducer *
   process.trackIsolation * process.loosetrackIsolation *
   process.stopPFJets * process.stopBJets *
   process.prepareCutvars_seq
)

process.load("AllHadronicSUSY.Stop.StopDPhiSelection_cff")
process.jetsMETDPhiFilter.jetSrc = cms.InputTag("stopJetsPFchsPt30")
if options.usePhiCorrMET == True:
   process.jetsMETDPhiFilter.metSrc = cms.InputTag("slimmedMETs")
else:
   process.jetsMETDPhiFilter.metSrc = cms.InputTag("slimmedMETs")
process.jetsMETDPhiFilter.dPhiCuts = cms.untracked.vdouble(0.5, 0.5, 0.3)

process.stopCount1BJets = process.stopCountBJets.clone()
process.stopCount1BJets.minNumber = cms.uint32(1)

process.stopCount2BJets = process.stopCountBJets.clone()
process.stopCount2BJets.minNumber = cms.uint32(2)

process.load("AllHadronicSUSY.Stop.StopType3TopTagger_cff")
if options.usePhiCorrMET == True:
   process.type3topTagger.metSrc = cms.InputTag("slimmedMETs")
else:
   process.type3topTagger.metSrc = cms.InputTag("slimmedMETs")
process.type3topTagger.taggingMode = cms.untracked.bool(True)
process.type3topTagger.jetSrc = cms.InputTag("stopJetsPFchsPt30")

process.metPFchsFilter = process.mhtPFchsFilter.clone()
if options.usePhiCorrMET == True:
   process.metPFchsFilter.MHTSource = cms.InputTag("slimmedMETs")
else:
   process.metPFchsFilter.MHTSource = cms.InputTag("slimmedMETs")

process.met175PFchsFilter = process.metPFchsFilter.clone()
process.met175PFchsFilter.MinMHT = cms.double(175)

process.met200PFchsFilter = process.metPFchsFilter.clone()
process.met200PFchsFilter.MinMHT = cms.double(200)

process.met350PFchsFilter = process.metPFchsFilter.clone()
process.met350PFchsFilter.MinMHT = cms.double(350)

process.TFileService = cms.Service("TFileService",
   fileName = cms.string('stopFlatNtuples.root')
)

process.load("AllHadronicSUSY.SkimsRA2.myGenJetsPartSelector_cfi")
process.myGenParticlesForJets.src = cms.InputTag("packedGenParticles")

process.myGenParticlesForJetsNoNu = process.myGenParticlesForJets.clone()
process.myGenParticlesForJetsNoNu.ignoreParticleIDs += cms.vuint32( 12,14,16)

process.myGenParticlesForJetsNoNuNoStopDecays = process.myGenParticlesForJetsNoNu.clone()
process.myGenParticlesForJetsNoNuNoStopDecays.ignoreParticleDecayIDs = cms.vint32(1000006, -1000006)

process.myGenParticlesForJetsNoNuOnlyStopDecays = process.myGenParticlesForJetsNoNu.clone()
process.myGenParticlesForJetsNoNuOnlyStopDecays.ignoreParticleDecayIDs = cms.vint32(1000006, -1000006)
process.myGenParticlesForJetsNoNuOnlyStopDecays.invertignoreParticleDecay = cms.bool(True)

process.myak4GenJetsNoNu = process.ak4GenJets.clone( src = cms.InputTag("myGenParticlesForJetsNoNu") )
process.myak4GenJetsNoNuNoStopDecays = process.ak4GenJets.clone( src = cms.InputTag("myGenParticlesForJetsNoNuNoStopDecays") )
process.myak4GenJetsNoNuOnlyStopDecays = process.ak4GenJets.clone( src = cms.InputTag("myGenParticlesForJetsNoNuOnlyStopDecays") )

process.load("SimGeneral.HepPDTESSource.pythiapdt_cfi")

process.load("AllHadronicSUSY.SignalScan.genDecayStringMaker_cfi")
process.printDecay.src = cms.InputTag("prunedGenParticles")
process.printDecay.keyDecayStrs = cms.vstring("t", "tbar", "~chi_1+", "~chi_1-")
process.printDecay.printDecay = cms.untracked.bool(options.debug)

process.load("AllHadronicSUSY.SignalScan.genDecayStringMakerPythia8_cfi")
process.printDecayPythia8.src = cms.InputTag("prunedGenParticles")
process.printDecayPythia8.keyDecayStrs = cms.vstring("t", "tbar", "~chi_1+", "~chi_1-")
process.printDecayPythia8.printDecay = cms.untracked.bool(options.debug)

process.load("AllHadronicSUSY.SignalScan.smsModelFilter_cfi")
process.smsModelFilter.SusyScanTopology   = cms.string(options.smsModel)
process.smsModelFilter.SusyScanMotherMass = cms.double(options.smsMotherMass)
process.smsModelFilter.SusyScanLSPMass    = cms.double(options.smsDaughterMass)
process.smsModelFilter.SusyScanFracLSP    = cms.double(0.0)
process.smsModelFilter.Debug              = cms.bool(options.debug)

process.load("AllHadronicSUSY.TopTagger.groomProd_cfi")
process.groomProdak4 = process.groomProd.clone()
process.groomProdak4.jetSrc = cms.InputTag("ak4patJetsPFchsPt10")
process.groomProdak4.groomingOpt = cms.untracked.int32(1)
#process.groomProdak4.debug = cms.untracked.bool(options.debug)

process.load("AllHadronicSUSY.SkimsRA2.prodMuons_cfi")
process.load("AllHadronicSUSY.SkimsRA2.prodElectrons_cfi")
process.load("AllHadronicSUSY.SkimsRA2.prodJets_cfi")
process.load("AllHadronicSUSY.SkimsRA2.prodMET_cfi")
process.load("AllHadronicSUSY.SkimsRA2.prodGenInfo_cfi")
process.load("AllHadronicSUSY.SkimsRA2.prodIsoTrks_cfi")
process.load("AllHadronicSUSY.SkimsRA2.prodEventInfo_cfi")

process.load("AllHadronicSUSY.TreeMaker.stopTreeMaker_cfi")
process.stopTreeMaker.debug = cms.bool(options.debug)
process.stopTreeMaker.TreeName = cms.string("AUX")

process.stopTreeMaker.varsInt.append(cms.InputTag("prodMuons", "nMuons"))
process.stopTreeMaker.varsIntNamesInTree.append("prodMuons:nMuons|nMuons_CUT")
process.stopTreeMaker.vectorTLorentzVector.append(cms.InputTag("prodMuons", "muonsLVec"))
process.stopTreeMaker.vectorDouble.extend([cms.InputTag("prodMuons", "muonsCharge"), cms.InputTag("prodMuons", "muonsMtw")])

process.stopTreeMaker.varsInt.append(cms.InputTag("prodElectrons", "nElectrons"))
process.stopTreeMaker.varsIntNamesInTree.append("prodElectrons:nElectrons|nElectrons_CUT")
process.stopTreeMaker.vectorTLorentzVector.append(cms.InputTag("prodElectrons", "elesLVec"))
process.stopTreeMaker.vectorDouble.extend([cms.InputTag("prodElectrons", "elesCharge"), cms.InputTag("prodElectrons", "elesMtw")])

process.stopTreeMaker.varsInt.append(cms.InputTag("prodJets", "nJets"))
process.stopTreeMaker.vectorTLorentzVector.append(cms.InputTag("prodJets", "jetsLVec"))
process.stopTreeMaker.vectorInt.append(cms.InputTag("prodJets", "recoJetsFlavor"))
process.stopTreeMaker.vectorDouble.append(cms.InputTag("prodJets", "recoJetsBtag"))

process.stopTreeMaker.vectorString.append(cms.InputTag("prodGenInfo", "genDecayStrVec"))
process.stopTreeMaker.vectorInt.extend([cms.InputTag("prodGenInfo", "genDecayIdxVec"), cms.InputTag("prodGenInfo", "genDecayPdgIdVec"), cms.InputTag("prodGenInfo", "genDecayMomIdxVec"), cms.InputTag("prodGenInfo", "WemuVec"), cms.InputTag("prodGenInfo", "WtauemuVec"), cms.InputTag("prodGenInfo", "WtauprongsVec")])
process.stopTreeMaker.vectorIntNamesInTree.extend(["prodGenInfo:WemuVec|W_emuVec", "prodGenInfo:WtauemuVec|W_tau_emuVec", "prodGenInfo:WtauprongsVec|W_tau_prongsVec"])
process.stopTreeMaker.vectorTLorentzVector.append(cms.InputTag("prodGenInfo", "genDecayLVec"))

process.stopTreeMaker.vectorTLorentzVector.append(cms.InputTag("prodIsoTrks:trksForIsoVetoLVec"))
process.stopTreeMaker.vectorDouble.extend([cms.InputTag("prodIsoTrks:trksForIsoVetocharge"), cms.InputTag("prodIsoTrks:trksForIsoVetodz"), cms.InputTag("prodIsoTrks:looseisoTrkscharge"), cms.InputTag("prodIsoTrks:looseisoTrksdz"), cms.InputTag("prodIsoTrks:looseisoTrksiso"), cms.InputTag("prodIsoTrks:looseisoTrksmtw")])
process.stopTreeMaker.vectorDoubleNamesInTree.extend(["prodIsoTrks:trksForIsoVetocharge|trksForIsoVeto_charge", "prodIsoTrks:trksForIsoVetodz|trksForIsoVeto_dz", "prodIsoTrks:looseisoTrkscharge|loose_isoTrks_charge", "prodIsoTrks:looseisoTrksdz|loose_isoTrks_dz", "prodIsoTrks:looseisoTrksiso|loose_isoTrks_iso", "prodIsoTrks:looseisoTrksmtw|loose_isoTrks_mtw"])
process.stopTreeMaker.vectorInt.extend([cms.InputTag("prodIsoTrks:trksForIsoVetopdgId"), cms.InputTag("prodIsoTrks:trksForIsoVetoidx"), cms.InputTag("prodIsoTrks:looseisoTrkspdgId"), cms.InputTag("prodIsoTrks:looseisoTrksidx"), cms.InputTag("prodIsoTrks:forVetoIsoTrksidx")])
process.stopTreeMaker.vectorIntNamesInTree.extend(["prodIsoTrks:trksForIsoVetopdgId|trksForIsoVeto_pdgId", "prodIsoTrks:trksForIsoVetoidx|trksForIsoVeto_idx", "prodIsoTrks:looseisoTrkspdgId|loose_isoTrks_pdgId", "prodIsoTrks:looseisoTrksidx|loose_isoTrks_idx"])
process.stopTreeMaker.vectorTLorentzVector.append(cms.InputTag("prodIsoTrks:looseisoTrksLVec"))
process.stopTreeMaker.vectorTLorentzVectorNamesInTree.append("prodIsoTrks:looseisoTrksLVec|loose_isoTrksLVec")
process.stopTreeMaker.varsInt.extend([cms.InputTag("prodIsoTrks:loosenIsoTrks"), cms.InputTag("prodIsoTrks:nIsoTrksForVeto")])
process.stopTreeMaker.varsIntNamesInTree.extend(["prodIsoTrks:loosenIsoTrks|loose_nIsoTrks", "prodIsoTrks:nIsoTrksForVeto|nIsoTrks_CUT"])

process.stopTreeMaker.varsDouble.extend([cms.InputTag("ak4stopmhtPFchs:mht"), cms.InputTag("ak4stopmhtPFchs:mhtphi")])

process.stopTreeMaker.varsDouble.append(cms.InputTag("ak4stophtPFchs"))
process.stopTreeMaker.varsDoubleNamesInTree.append("ak4stophtPFchs|ht")

process.stopTreeMaker.varsInt.append(cms.InputTag("ak4nJetsForSkimsStop:nJets"))
process.stopTreeMaker.varsIntNamesInTree.append("ak4nJetsForSkimsStop:nJets|nJets_CUT")

process.stopTreeMaker.varsDouble.extend([cms.InputTag("prodMET:met"), cms.InputTag("prodMET:metphi")])

process.stopTreeMaker.vectorDouble.append(cms.InputTag("ak4jetMHTDPhiForSkimsStop:jetMHTDPhiVec"))
process.stopTreeMaker.vectorDoubleNamesInTree.append("ak4jetMHTDPhiForSkimsStop:jetMHTDPhiVec|dPhis_CUT")

process.stopTreeMaker.varsInt.extend([cms.InputTag("prodEventInfo:vtxSize"), cms.InputTag("prodEventInfo:npv"), cms.InputTag("prodEventInfo:nm1"), cms.InputTag("prodEventInfo:n0"), cms.InputTag("prodEventInfo:np1")])
process.stopTreeMaker.varsDouble.extend([cms.InputTag("prodEventInfo:trunpv"), cms.InputTag("prodEventInfo:avgnpv")])
process.stopTreeMaker.varsDoubleNamesInTree.extend(["prodEventInfo:trunpv|tru_npv", "prodEventInfo:avgnpv|avg_npv"])

process.stopTreeMaker.varsInt.extend([cms.InputTag("type3topTagger:bestTopJetIdx"), cms.InputTag("type3topTagger:pickedRemainingCombfatJetIdx")])
process.stopTreeMaker.varsDouble.extend([cms.InputTag("type3topTagger:bestTopJetMass"), cms.InputTag("type3topTagger:MT2"), cms.InputTag("type3topTagger:mTbestTopJet"), cms.InputTag("type3topTagger:mTbJet"), cms.InputTag("type3topTagger:linearCombmTbJetPlusmTbestTopJet"), cms.InputTag("type3topTagger:mTbestWJet"), cms.InputTag("type3topTagger:mTbestbJet"), cms.InputTag("type3topTagger:mTremainingTopJet")])
process.stopTreeMaker.varsBool.append(cms.InputTag("type3topTagger:remainPassCSVS"))

process.stopTreeMaker.varsDouble.append(cms.InputTag("weightProducer:weight"))
process.stopTreeMaker.varsDoubleNamesInTree.append("weightProducer:weight|evtWeight")

if options.selSMSpts == True:
   process.stopTreeMaker.vectorString.extend([cms.InputTag("smsModelFilter:fileNameStr"), cms.InputTag("smsModelFilter:smsModelStr")])
   process.stopTreeMaker.varsDouble.extend([cms.InputTag("smsModelFilter:smsMotherMass"), cms.InputTag("smsModelFilter:smsDaughterMass")])

process.ak4Stop_Path = cms.Path(
                                   process.comb_seq * 
                                   process.printDecayPythia8 *
                                   process.prodMuons * process.prodElectrons * process.prodJets * process.prodMET * process.prodGenInfo * process.prodIsoTrks * process.prodEventInfo *
                                   process.type3topTagger *
                                   process.stopTreeMaker
)

if options.selSMSpts == True:
   process.ak4Stop_Path.replace(process.hltFilter, process.hltFilter*process.smsModelFilter)

###-- Dump config ------------------------------------------------------------
file = open('allDump_cfg.py','w')
file.write(str(process.dumpPython()))
file.close()
