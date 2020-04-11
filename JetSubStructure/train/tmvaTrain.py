import ROOT
from ROOT import TMVA

outputFile = ROOT.TFile("TMVA.root","RECREATE")
factory = TMVA.Factory("tmvaTest", outputFile, "")
dataloader = TMVA.DataLoader("dataset")

# trainingFile = ROOT.TFile("../generate/trainingData.root")
# testFile = ROOT.TFile("../generate/testData.root")
inputFile = ROOT.TFile("../data/TrainingFile.root")

# get the TTree objects from the input files

sig = inputFile.Get("TreeQ")
bkg = inputFile.Get("TreeG")
nSig = sig.GetEntries()
nBkg = bkg.GetEntries()


# global event weights (see below for setting event-wise weights)

sigWeight = 1.0
bkgWeight = 1.0


# dataloader.AddSignalTree(sigTest, sigWeight, TMVA.Types.kTesting)
# dataloader.AddBackgroundTree(bkgTest, bkgWeight, TMVA.Types.kTesting)

dataloader.AddVariable("qpTD", 'F')
dataloader.AddVariable("qSigma2", 'F')
dataloader.AddVariable("qMulti", 'F')


dataloader.AddSignalTree(sig, sigWeight)
dataloader.AddBackgroundTree(bkg, bkgWeight)
cut1 = ROOT.TCut("JetPt > 30 && JetPt < 100")
cut2 = ROOT.TCut("") 
dataloader.PrepareTrainingAndTestTree(cut1,"SplitMode=Random:!V")

# Book MVA methods (see TMVA manual).  
#factory.BookMethod(dataloader,TMVA.Types.kMLP, "MLP", "H:!V:HiddenLayers=3");  
factory.BookMethod(dataloader,TMVA.Types.kBDT, "BDT200", "NTrees=200:BoostType=AdaBoost")
# Train, test and evaluate all methods

factory.TrainAllMethods()
factory.TestAllMethods()
factory.EvaluateAllMethods()



outputFile.Close()
print(' TMVAanalyses is done! ')

