import FWCore.ParameterSet.Config as cms
import os

from FWCore.ParameterSet.VarParsing import VarParsing

options = VarParsing ('python')

options.register('reportEvery', 100,
    VarParsing.multiplicity.singleton,
    VarParsing.varType.int,
    "Report every N events (default is N=100)"
)
options.register('wantSummary', True,
    VarParsing.multiplicity.singleton,
    VarParsing.varType.bool,
    "Print out trigger and timing summary"
)
options.register('useInputDir', False,
    VarParsing.multiplicity.singleton,
    VarParsing.varType.bool,
    "Use input directory"
)

## 'maxEvents' is already registered by the Framework, changing default value
options.setDefault('maxEvents', 1000)

options.parseArguments()

process = cms.Process("USER")

process.load("SimGeneral.HepPDTESSource.pythiapdt_cfi")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = options.reportEvery
process.MessageLogger.cerr.default.limit = 10

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(options.maxEvents) )

process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(options.wantSummary) )


inputDir = '/eos/uscms/store/user/ferencek/noreplica/Stop2ToStop1H_TuneCUETP8M1_13TeV-madgraph-pythia8/RunIISpring15DR74_MiniAOD/150613_192348/0000/'
inputFiles = []
for f in os.listdir(inputDir):
    if not os.path.isfile(os.path.join(inputDir,f)) or not f.endswith('.root'):
        continue
    inputFiles.append( os.path.join(inputDir.replace('/eos/uscms',''),f) )

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
        # MiniAOD
        '/store/user/ferencek/noreplica/Stop2ToStop1H_TuneCUETP8M1_13TeV-madgraph-pythia8/RunIISpring15DR74_MiniAOD/150613_192348/0000/Stop2ToStop1H_TuneCUETP8M1_13TeV-madgraph-pythia8_MiniAOD_Asympt25ns_1.root'
        # AOD
        #'/store/user/ferencek/noreplica/Stop2ToStop1H_TuneCUETP8M1_13TeV-madgraph-pythia8/RunIISpring15DR74_AODSIM/150612_162933/0000/Stop2ToStop1H_TuneCUETP8M1_13TeV-madgraph-pythia8_AODSIM_Asympt25ns_1.root'
    ),
    #eventsToProcess = cms.untracked.VEventRange('1:19')
    #eventsToProcess = cms.untracked.VEventRange('1:25')
    #eventsToProcess = cms.untracked.VEventRange('1:23')
)
if options.useInputDir:
    process.source.fileNames = cms.untracked.vstring()
    process.source.fileNames.extend( inputFiles ) # see https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuidePoolInputSources#Example_3_More_than_255_input_fi


process.filter = cms.EDFilter('LHEEventFilter',
    src   = cms.InputTag('source'),
    model = cms.string('stop2_1000.0_400_225')
)

process.p = cms.Path(
    process.filter
)
