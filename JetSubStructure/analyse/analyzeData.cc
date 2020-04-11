#include <iostream>
#include <fstream>
#include <vector>
#include <TFile.h>
#include <TTree.h>
#include <TH1D.h>
//#include "Event.h"
#include <TMVA/Reader.h>

int main() {

// Set up an output file and book some histograms

  TFile* histFile = new TFile("analysis.root", "RECREATE");
  TH1D* hMLPSig = new TH1D("hMLPSig", "BDT, signal", 100, -10., 10.);
  TH1D* hMLPBkg = new TH1D("hMLPBkg", "BDT, background", 100, -10., 10.);

// Set up the TMVA Reader object.
// The names in AddVariable must be same as in the input (weight) file.

  TMVA::Reader* reader = new TMVA::Reader();
  float x,y,z;// TMVA needs float, not double
  reader->AddVariable("qpTD", &x);
  reader->AddVariable("qSigma2", &z);
  reader->AddVariable("qMulti", &y);
  std::string dir    = "../train/dataset/weights/";
  std::string prefix = "tmvaTest";
  reader->BookMVA("MLP", dir + prefix + "_BDT200.weights.xml");

// Open input file, get the TTrees, put into a vector

  TFile* inputFile = new TFile("../data/TestFile.root");
  inputFile->ls();
  TTree* sig = dynamic_cast<TTree*>(inputFile->Get("TreeQ"));
  TTree* bkg = dynamic_cast<TTree*>(inputFile->Get("TreeG"));
  std::vector<TTree*> treeVec;
  treeVec.push_back(sig);
  treeVec.push_back(bkg);

// Loop over TTrees

  int nSigAccFish = 0;
  int nBkgAccFish = 0;
  int nSig, nBkg;
  const double tCutFisher = 0.0;
  const double tCutMLP = 0.5;
  for (int i=0; i<treeVec.size(); i++){

    treeVec[i]->Print();
    //Event evt;
    float qpTD;
    int qMulti;
    float qSigma2;
    treeVec[i]->SetBranchAddress("qpTD", &qpTD);
    treeVec[i]->SetBranchAddress("qMulti", &qMulti);
    treeVec[i]->SetBranchAddress("qSigma2", &qSigma2);
    int numEntries = treeVec[i]->GetEntries();
    if ( i == 0 ) { nSig = numEntries; }
    if ( i == 1 ) { nBkg = numEntries; }
    std::cout << "number of entries = " << numEntries << std::endl;

// Loop over events.  The test statistic is identified by the first 
// argument used above in BookMVA (below, e.g., "MLP").

    for (int j=0; j<numEntries; j++){
      treeVec[i]->GetEntry(j);// sets evt
      
      x = qpTD;                              // set variables of reader
      y = qMulti;
      //z = evt.z;

      double tMLP = reader->EvaluateMVA("MLP");
      if ( i == 0 ){                       // signal
        hMLPSig->Fill(tMLP);
      }
      else if ( i == 1 ){                  // background
        hMLPBkg->Fill(tMLP);
      }

      // ADD YOUR CODE HERE TO INCLUDE OTHER CLASSIFIERS SUCH AS MLP
      // AND COUNT THE NUMBERS OF SELECTED EVENTS (COMPARE CLASSIFIER
      // VALUE TFISHER, ETC., TO TCUT).




    }

  }


  histFile->Write();
  histFile->Close();
  return 0;

}
