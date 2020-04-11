#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <TFile.h>
#include <TString.h>
#include <TMVA/Factory.h>

int main() {  

// Create ouput file, factory object and open the input file

  TFile* outputFile = TFile::Open( "TMVA.root", "RECREATE" );
  TMVA::Factory* factory = new TMVA::Factory("tmvaTest", outputFile, "");
  TMVA::DataLoader* dataloader = new TMVA::DataLoader("dataset");
  // TFile* trainingFile = new TFile("../generate/trainingData.root");
  // TFile* testFile = new TFile("../generate/testData.root");
  TFile* inputFile = new TFile("../data/Test_File.root");
// get the TTree objects from the input files

  TTree* sigTrain = (TTree*)inputFile->Get("TreeQ");
  TTree* bkgTrain = (TTree*)inputFile->Get("TreeG");
  int nSigTrain = sigTrain->GetEntries();
  int nBkgTrain = bkgTrain->GetEntries();

  TTree* sigTest = (TTree*)inputFile->Get("TreeQ");
  TTree* bkgTest = (TTree*)inputFile->Get("TreeG");
  int nSigTest = sigTest->GetEntries();
  int nBkgTest = bkgTest->GetEntries();

// global event weights (see below for setting event-wise weights)

  double sigWeight = 1.0;
  double bkgWeight = 1.0;
  dataloader->AddSignalTree(sigTrain, sigWeight, TMVA::Types::kTraining);
  dataloader->AddBackgroundTree(bkgTrain, bkgWeight, TMVA::Types::kTraining);
  dataloader->AddSignalTree(sigTest, sigWeight, TMVA::Types::kTesting);
  dataloader->AddBackgroundTree(bkgTest, bkgWeight, TMVA::Types::kTesting);
   
// Define the input variables that shall be used for the MVA training
// (the variables used in the expression must exist in the original TTree).

  dataloader->AddVariable("qpTD", 'F');
  dataloader->AddVariable("qMulti", 'I');
  //dataloader->AddVariable("z", 'F');

  // TCut cut1="";
  // dataloader->PrepareTrainingAndTestTree("", "",
  // 					 "nTest_Signal=1"
  // 					 ":nTest_Background=1"
  // 					 ":SplitMode=Random"
  // 					 ":NormMode=NumEvents"
  // 					 ":!V");
  //dataloader->PrepareTrainingAndTestTree(cut1,"nTest_Signal=1:nTest_Background=1:SplitMode=Random:NormMode=NumEvents:!V");
  // Book MVA methods (see TMVA manual).  

  factory->BookMethod(dataloader,TMVA::Types::kFisher, "Fisher", "H:!V:Fisher");  

// Train, test and evaluate all methods

  factory->TrainAllMethods();
  factory->TestAllMethods();
  factory->EvaluateAllMethods();    

// Save the output and finish up

  outputFile->Close();
  std::cout << "==> wrote root file TMVA.root" << std::endl;
  std::cout << "==> TMVAnalysis is done!" << std::endl; 

  delete factory;
  return 0;

}
