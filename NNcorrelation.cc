#include <iostream>

#include "TChain.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TROOT.h"
#include "TGaxis.h"
#include "TPaveStats.h"
#include "TGraphErrors.h"

//#include "CC0PiNumu.h"
#include "DefBeamMode.h"
//#include "DefOscChannels.h"

#include "include/CLTOption.h"
#include "include/NNcorrelation.h"


int main(int argc, char **argv) {

  //int type   = *argv[1]-'0';    //True label
  float type   = *argv[1]-'0';    //True label
  int   varid1 = atoi(argv[2]);   //1st variable ID
  int   varid2 = atoi(argv[3]);   //2nd variable ID
  int   file   = atoi(argv[4]);   //file counter (label output files)
  TString NtagFileName   = argv[5];
  TString MCTypeKeyword  = argv[6];
  TString MCType         = argv[7];
  TString ETAGKeyword    = argv[8];
  TString ETAG           = argv[9];
  TString BeamKeyword    = argv[10];
  TString Beam           = argv[11];
  TString OscKeyword     = argv[12];
  TString Osc            = argv[13];

  enum BeamMode::E_BEAM_MODE eMode;
  enum OscChan::E_OSC_CHAN eOsc;
  eMode = CLTOptionBeamMode(BeamKeyword, Beam);
  eOsc  = CLTOptionOscMode(OscKeyword, Osc);
  CLTOptionETAG(ETAGKeyword, ETAG);
  

  //=========  NTag output (TTree: ntag)  ============
  TChain *tchntag = new TChain("ntag");
  int ntagFiles = tchntag->Add( NtagFileName );
  if (ntagFiles==0) {
    std::cout << "[### analysis1Rmu ###]  Cannot load ntag tree from: " << NtagFileName << std::endl;
    std::cout << "[### analysis1Rmu ###]  -> EXIT " << std::endl;
    exit(-1);
  }
  const int ntagEntries = tchntag->GetEntries();
  
  const char* varname1;
  const char* varname2;
  bool empty = false;

  //variable ID
  switch(varid1) {
    case 1:
      varname1 = "NHits";  //float
      break;
    case 2:
      varname1 = "N200";   //float
      break;
    case 3:
      varname1 = "TRMS";   //float
      break;
    case 4:
      varname1 = "DWall";  //float
      break;
    case 5:
      varname1 = "DWallMeanDir";  //float
      break;
    case 6:
      varname1 = "OpeningAngleMean";  //float
      break;
    case 7:
      varname1 = "OpeningAngleStdev";  //float
      break;
    case 8:
      varname1 = "OpeningAngleSkew";  //float
      break;
    case 9:
      varname1 = "MeanDirAngleMean";  //float
      break;
    case 10:
      varname1 = "MeanDirAngleRMS";  //float
      break;
    case 11:
      varname1 = "Beta1";  //float
      break;
    case 12:
      varname1 = "Beta5";  //float
      break;
    default:
      varname1 = "NONE";
      break;
  }

  switch(varid2) {
    case 1:
      varname2 = "NHits";
      break;
    case 2:
      varname2 = "N200";
      break;
    case 3:
      varname2 = "TRMS";
      break;
    case 4:
      varname2 = "DWall";
      break;
    case 5:
      varname2 = "DWallMeanDir";
      break;
    case 6:
      varname2 = "OpeningAngleMean";
      break;
    case 7:
      varname2 = "OpeningAngleStdev";
      break;
    case 8:
      varname2 = "OpeningAngleSkew";
      break;
    case 9:
      varname2 = "MeanDirAngleMean";
      break;
    case 10:
      varname2 = "MeanDirAngleRMS";
      break;
    case 11:
      varname2 = "Beta1";
      break;
    case 12:
      varname2 = "Beta5";
      break;
    default:
      varname2 = "NONE";
      break;
  }


  //Correlation
  Double_t col = 0;
  
  if (varid2==0) {
    std::cout << "\e[38;5;70m\e[1m" << varname1 << " vs " << varname1 << "\e[0m";
    col = GetMatrixElementF(type, tchntag, ntagEntries, varname1);
  }
  else {
    std::cout << "\e[38;5;70m\e[1m" << varname1 << " vs " << varname2 << "\e[0m";
    col = GetMatrixElementFF(type, tchntag, ntagEntries, varname1, varname2);
  }


  if (varid2==0) h2_matrix -> Fill(varid1-1, varid1-1, col);
  else h2_matrix -> Fill(varid1-1, varid2-1, col);


  TFile* outfile = new TFile(TString::Format("./tmp/output%d.root", file), "RECREATE");
  outfile -> cd();
  TCanvas* c = new TCanvas("c", "c", 1600, 800);
  h2_matrix -> SetStats(0);
  h2_matrix -> SetMarkerColor(kWhite);
  h2_matrix -> Write("textCol");

}
