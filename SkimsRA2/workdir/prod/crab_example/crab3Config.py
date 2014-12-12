from WMCore.Configuration import Configuration
config = Configuration()

config.section_("General")
config.General.requestName = 'PHYS14_PU20bx25_TTJets'

config.section_("JobType")
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'treeMaker_stopRA2.py'
config.JobType.allowNonProductionCMSSW = False

config.section_("Data")
config.Data.inputDataset = '/TTJets_MSDecaysCKM_central_Tune4C_13TeV-madgraph-tauola/Phys14DR-PU20bx25_PHYS14_25_V1-v1/MINIAODSIM'
config.Data.dbsUrl = 'https://cmsweb.cern.ch/dbs/prod/global/DBSReader/'
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 5
config.Data.publication = False
config.Data.publishDbsUrl = 'https://cmsweb.cern.ch/dbs/prod/phys03/DBSWriter/'
config.Data.publishDataName = 'PHYS14_PU20bx25_PHYS14_25_V1-FLAT'
config.Data.outlfn = '/store/user/lpcsusyhad/PHYS14/PU20bx25_TTJets_MSDecaysCKM_madgraph-tauola/'

config.Data.ignoreLocality = False

config.section_("Site")
config.Site.storageSite = 'T3_US_FNALLPC'