#include "NNInputVariables.h"
#include "../../../include/Const.h"
#include "../include/CommonTool.h"


void NNInputVariables::SetHistoFrame(int vartype, TString histtitle) {

#if !data
  int NNbinConf[NNVARIABLES] = {50, 70, 50, 50, 50, 40, 80, 80, 80, 80, 80, 20, 50, 20};
#endif
#if data
  int NNbinConf[NNVARIABLES] = {50, 70, 25, 25, 25, 20, 40, 40, 40, 40, 40, 20, 50, 20};
#endif

  switch (vartype) {
#if 0
  	case 0:  //NHits
  	  h1_NNvar_Gd[vartype]       = new TH1F(TString::Format("h1_NNvar_Gd_type%d", vartype),    histtitle, 50, 0, 50);
      h1_NNvar_H[vartype]        = new TH1F(TString::Format("h1_NNvar_H_type%d", vartype),     histtitle, 50, 0, 50);
      h1_NNvar_AccNoise[vartype] = new TH1F(TString::Format("h1_NNvar_AccNoise_type%d", vartype), histtitle, 50, 0, 50);
      h1_NNvar_Decaye[vartype]   = new TH1F(TString::Format("h1_NNvar_Decaye_type%d", vartype), histtitle, 50, 0, 50);
      break;
    case 1:  //N200
  	  h1_NNvar_Gd[vartype]       = new TH1F(TString::Format("h1_NNvar_Gd_type%d", vartype),    histtitle, 40, 0, 80);
      h1_NNvar_H[vartype]        = new TH1F(TString::Format("h1_NNvar_H_type%d", vartype),     histtitle, 40, 0, 80);
      h1_NNvar_AccNoise[vartype] = new TH1F(TString::Format("h1_NNvar_AccNoise_type%d", vartype), histtitle, 40, 0, 80);
      h1_NNvar_Decaye[vartype]   = new TH1F(TString::Format("h1_NNvar_Decaye_type%d", vartype), histtitle, 40, 0, 80);
      break;
    case 2:  //TRMS
  	  h1_NNvar_Gd[vartype]       = new TH1F(TString::Format("h1_NNvar_Gd_type%d", vartype),    histtitle, 50, 0, 10);
      h1_NNvar_H[vartype]        = new TH1F(TString::Format("h1_NNvar_H_type%d", vartype),     histtitle, 50, 0, 10);
      h1_NNvar_AccNoise[vartype] = new TH1F(TString::Format("h1_NNvar_AccNoise_type%d", vartype), histtitle, 50, 0, 10);
      h1_NNvar_Decaye[vartype]   = new TH1F(TString::Format("h1_NNvar_Decaye_type%d", vartype), histtitle, 50, 0, 10);
      break;
    case 3:  //DWall
  	  h1_NNvar_Gd[vartype]       = new TH1F(TString::Format("h1_NNvar_Gd_type%d", vartype),    histtitle, 50, -150, 1600);
      h1_NNvar_H[vartype]        = new TH1F(TString::Format("h1_NNvar_H_type%d", vartype),     histtitle, 50, -150, 1600);
      h1_NNvar_AccNoise[vartype] = new TH1F(TString::Format("h1_NNvar_AccNoise_type%d", vartype), histtitle, 50, -150, 1600);
      h1_NNvar_Decaye[vartype]   = new TH1F(TString::Format("h1_NNvar_Decaye_type%d", vartype), histtitle, 50, -150, 1600);
      break;
    case 4:  //DWallMeanDir
  	  h1_NNvar_Gd[vartype]       = new TH1F(TString::Format("h1_NNvar_Gd_type%d", vartype),    histtitle, 50, 0, 5000);
      h1_NNvar_H[vartype]        = new TH1F(TString::Format("h1_NNvar_H_type%d", vartype),     histtitle, 50, 0, 5000);
      h1_NNvar_AccNoise[vartype] = new TH1F(TString::Format("h1_NNvar_AccNoise_type%d", vartype), histtitle, 50, 0, 5000);
      h1_NNvar_Decaye[vartype]   = new TH1F(TString::Format("h1_NNvar_Decaye_type%d", vartype), histtitle, 50, 0, 5000);
      break;
    case 5:  //OpeningAngleMean
  	  h1_NNvar_Gd[vartype]       = new TH1F(TString::Format("h1_NNvar_Gd_type%d", vartype),    histtitle, 40, 20, 80);
      h1_NNvar_H[vartype]        = new TH1F(TString::Format("h1_NNvar_H_type%d", vartype),     histtitle, 40, 20, 80);
      h1_NNvar_AccNoise[vartype] = new TH1F(TString::Format("h1_NNvar_AccNoise_type%d", vartype), histtitle, 40, 20, 80);
      h1_NNvar_Decaye[vartype]   = new TH1F(TString::Format("h1_NNvar_Decaye_type%d", vartype), histtitle, 40, 20, 80);
      break;
    case 6:  //OpeningAngleStdev
  	  h1_NNvar_Gd[vartype]       = new TH1F(TString::Format("h1_NNvar_Gd_type%d", vartype),    histtitle, 40, 10, 30);
      h1_NNvar_H[vartype]        = new TH1F(TString::Format("h1_NNvar_H_type%d", vartype),     histtitle, 40, 10, 30);
      h1_NNvar_AccNoise[vartype] = new TH1F(TString::Format("h1_NNvar_AccNoise_type%d", vartype), histtitle, 40, 10, 30);
      h1_NNvar_Decaye[vartype]   = new TH1F(TString::Format("h1_NNvar_Decaye_type%d", vartype), histtitle, 40, 10, 30);
      break;
    case 7:  //OpeningAngleSkew
  	  h1_NNvar_Gd[vartype]       = new TH1F(TString::Format("h1_NNvar_Gd_type%d", vartype),    histtitle, 40, -150, 150);
      h1_NNvar_H[vartype]        = new TH1F(TString::Format("h1_NNvar_H_type%d", vartype),     histtitle, 40, -150, 150);
      h1_NNvar_AccNoise[vartype] = new TH1F(TString::Format("h1_NNvar_AccNoise_type%d", vartype), histtitle, 40, -150, 150);
      h1_NNvar_Decaye[vartype]   = new TH1F(TString::Format("h1_NNvar_Decaye_type%d", vartype), histtitle, 40, -150, 150);
      break;
    case 8: //MeanDirAngleMean
  	  h1_NNvar_Gd[vartype]       = new TH1F(TString::Format("h1_NNvar_Gd_type%d", vartype),    histtitle, 40, 20, 90);
      h1_NNvar_H[vartype]        = new TH1F(TString::Format("h1_NNvar_H_type%d", vartype),     histtitle, 40, 20, 90);
      h1_NNvar_AccNoise[vartype] = new TH1F(TString::Format("h1_NNvar_AccNoise_type%d", vartype), histtitle, 40, 20, 90);
      h1_NNvar_Decaye[vartype]   = new TH1F(TString::Format("h1_NNvar_Decaye_type%d", vartype), histtitle, 40, 20, 90);
      break;
    case 9: //MeanDirAngleRMS
      h1_NNvar_Gd[vartype]       = new TH1F(TString::Format("h1_NNvar_Gd_type%d", vartype),    histtitle, 40, 0, 60);
      h1_NNvar_H[vartype]        = new TH1F(TString::Format("h1_NNvar_H_type%d", vartype),     histtitle, 40, 0, 60);
      h1_NNvar_AccNoise[vartype] = new TH1F(TString::Format("h1_NNvar_AccNoise_type%d", vartype), histtitle, 40, 0, 60);
      h1_NNvar_Decaye[vartype]   = new TH1F(TString::Format("h1_NNvar_Decaye_type%d", vartype), histtitle, 40, 0, 60);
      break;
    case 10:  //Beta1
  	  h1_NNvar_Gd[vartype]       = new TH1F(TString::Format("h1_NNvar_Gd_type%d", vartype),    histtitle, 40, -0.2, 0.8);
      h1_NNvar_H[vartype]        = new TH1F(TString::Format("h1_NNvar_H_type%d", vartype),     histtitle, 40, -0.2, 0.8);
      h1_NNvar_AccNoise[vartype] = new TH1F(TString::Format("h1_NNvar_AccNoise_type%d", vartype), histtitle, 40, -0.2, 0.8);
      h1_NNvar_Decaye[vartype]   = new TH1F(TString::Format("h1_NNvar_Decaye_type%d", vartype), histtitle, 40, -0.2, 0.8);
      break;
    case 11:  //Beta5
  	  h1_NNvar_Gd[vartype]       = new TH1F(TString::Format("h1_NNvar_Gd_type%d", vartype),    histtitle, 40, -0.2, 0.4);
      h1_NNvar_H[vartype]        = new TH1F(TString::Format("h1_NNvar_H_type%d", vartype),     histtitle, 40, -0.2, 0.4);
      h1_NNvar_AccNoise[vartype] = new TH1F(TString::Format("h1_NNvar_AccNoise_type%d", vartype), histtitle, 40, -0.2, 0.4);
      h1_NNvar_Decaye[vartype]   = new TH1F(TString::Format("h1_NNvar_Decaye_type%d", vartype), histtitle, 40, -0.2, 0.4);
      break;
#endif

    case 0:  //NHits
      h1_NNvar_Gd[vartype]       = new TH1F(TString::Format("h1_NNvar_Gd_type%d", vartype),    histtitle, 50, 0, 50);
      h1_NNvar_H[vartype]        = new TH1F(TString::Format("h1_NNvar_H_type%d", vartype),     histtitle, 50, 0, 50);
      h1_NNvar_AccNoise[vartype] = new TH1F(TString::Format("h1_NNvar_AccNoise_type%d", vartype), histtitle, 50, 0, 50);
      h1_NNvar_Decaye[vartype]   = new TH1F(TString::Format("h1_NNvar_Decaye_type%d", vartype), histtitle, 50, 0, 50);
      h1_NNvar[vartype]          = new TH1F(TString::Format("h1_NNvar_type%d", vartype), histtitle, 50, 0, 50);
      break;
    case 1:  //NResHits
      h1_NNvar_Gd[vartype]       = new TH1F(TString::Format("h1_NNvar_Gd_type%d", vartype),    histtitle, 70, 0, 70);
      h1_NNvar_H[vartype]        = new TH1F(TString::Format("h1_NNvar_H_type%d", vartype),     histtitle, 70, 0, 70);
      h1_NNvar_AccNoise[vartype] = new TH1F(TString::Format("h1_NNvar_AccNoise_type%d", vartype), histtitle, 70, 0, 70);
      h1_NNvar_Decaye[vartype]   = new TH1F(TString::Format("h1_NNvar_Decaye_type%d", vartype), histtitle, 70, 0, 70);
      h1_NNvar[vartype]          = new TH1F(TString::Format("h1_NNvar_type%d", vartype), histtitle, 70, 0, 70);
      break;
    case 2:  //TRMS
      h1_NNvar_Gd[vartype]       = new TH1F(TString::Format("h1_NNvar_Gd_type%d", vartype),    histtitle, 25, 0, 10);
      h1_NNvar_H[vartype]        = new TH1F(TString::Format("h1_NNvar_H_type%d", vartype),     histtitle, 25, 0, 10);
      h1_NNvar_AccNoise[vartype] = new TH1F(TString::Format("h1_NNvar_AccNoise_type%d", vartype), histtitle, 25, 0, 10);
      h1_NNvar_Decaye[vartype]   = new TH1F(TString::Format("h1_NNvar_Decaye_type%d", vartype), histtitle, 25, 0, 10);
      h1_NNvar[vartype]          = new TH1F(TString::Format("h1_NNvar_type%d", vartype), histtitle, 25, 0, 10);
      break;
    case 3:  //DWall
      h1_NNvar_Gd[vartype]       = new TH1F(TString::Format("h1_NNvar_Gd_type%d", vartype),    histtitle, 25, -150, 1600);
      h1_NNvar_H[vartype]        = new TH1F(TString::Format("h1_NNvar_H_type%d", vartype),     histtitle, 25, -150, 1600);
      h1_NNvar_AccNoise[vartype] = new TH1F(TString::Format("h1_NNvar_AccNoise_type%d", vartype), histtitle, 25, -150, 1600);
      h1_NNvar_Decaye[vartype]   = new TH1F(TString::Format("h1_NNvar_Decaye_type%d", vartype), histtitle, 25, -150, 1600);
      h1_NNvar[vartype]          = new TH1F(TString::Format("h1_NNvar_type%d", vartype), histtitle, 25, -150, 1600);
      break;
    case 4:  //DWallMeanDir
      h1_NNvar_Gd[vartype]       = new TH1F(TString::Format("h1_NNvar_Gd_type%d", vartype),    histtitle, 25, 0, 5000);
      h1_NNvar_H[vartype]        = new TH1F(TString::Format("h1_NNvar_H_type%d", vartype),     histtitle, 25, 0, 5000);
      h1_NNvar_AccNoise[vartype] = new TH1F(TString::Format("h1_NNvar_AccNoise_type%d", vartype), histtitle, 25, 0, 5000);
      h1_NNvar_Decaye[vartype]   = new TH1F(TString::Format("h1_NNvar_Decaye_type%d", vartype), histtitle, 25, 0, 5000);
      h1_NNvar[vartype]          = new TH1F(TString::Format("h1_NNvar_type%d", vartype), histtitle, 25, 0, 5000);
      break;
    case 5:  //OpeningAngleStdev
      h1_NNvar_Gd[vartype]       = new TH1F(TString::Format("h1_NNvar_Gd_type%d", vartype),    histtitle, 40, 10, 30);
      h1_NNvar_H[vartype]        = new TH1F(TString::Format("h1_NNvar_H_type%d", vartype),     histtitle, 40, 10, 30);
      h1_NNvar_AccNoise[vartype] = new TH1F(TString::Format("h1_NNvar_AccNoise_type%d", vartype), histtitle, 40, 10, 30);
      h1_NNvar_Decaye[vartype]   = new TH1F(TString::Format("h1_NNvar_Decaye_type%d", vartype), histtitle, 40, 10, 30);
      h1_NNvar[vartype]          = new TH1F(TString::Format("h1_NNvar_type%d", vartype), histtitle, 40, 10, 30);
      break;
    /*case 6: //Beta1
      h1_NNvar_Gd[vartype]       = new TH1F(TString::Format("h1_NNvar_Gd_type%d", vartype),    histtitle, 40, -0.2, 0.8);
      h1_NNvar_H[vartype]        = new TH1F(TString::Format("h1_NNvar_H_type%d", vartype),     histtitle, 40, -0.2, 0.8);
      h1_NNvar_AccNoise[vartype] = new TH1F(TString::Format("h1_NNvar_AccNoise_type%d", vartype), histtitle, 40, -0.2, 0.8);
      h1_NNvar_Decaye[vartype]   = new TH1F(TString::Format("h1_NNvar_Decaye_type%d", vartype), histtitle, 40, -0.2, 0.8);
      break;
    case 7:  //Beta2
      h1_NNvar_Gd[vartype]       = new TH1F(TString::Format("h1_NNvar_Gd_type%d", vartype),    histtitle, 40, -0.2, 0.8);
      h1_NNvar_H[vartype]        = new TH1F(TString::Format("h1_NNvar_H_type%d", vartype),     histtitle, 40, -0.2, 0.8);
      h1_NNvar_AccNoise[vartype] = new TH1F(TString::Format("h1_NNvar_AccNoise_type%d", vartype), histtitle, 40, -0.2, 0.8);
      h1_NNvar_Decaye[vartype]   = new TH1F(TString::Format("h1_NNvar_Decaye_type%d", vartype), histtitle, 40, -0.2, 0.8);
      break;
    case 8:  //Beta3
      h1_NNvar_Gd[vartype]       = new TH1F(TString::Format("h1_NNvar_Gd_type%d", vartype),    histtitle, 40, -0.2, 0.4);
      h1_NNvar_H[vartype]        = new TH1F(TString::Format("h1_NNvar_H_type%d", vartype),     histtitle, 40, -0.2, 0.4);
      h1_NNvar_AccNoise[vartype] = new TH1F(TString::Format("h1_NNvar_AccNoise_type%d", vartype), histtitle, 40, -0.2, 0.4);
      h1_NNvar_Decaye[vartype]   = new TH1F(TString::Format("h1_NNvar_Decaye_type%d", vartype), histtitle, 40, -0.2, 0.4);
      break;
    case 9:  //Beta4
      h1_NNvar_Gd[vartype]       = new TH1F(TString::Format("h1_NNvar_Gd_type%d", vartype),    histtitle, 40, -0.2, 0.4);
      h1_NNvar_H[vartype]        = new TH1F(TString::Format("h1_NNvar_H_type%d", vartype),     histtitle, 40, -0.2, 0.4);
      h1_NNvar_AccNoise[vartype] = new TH1F(TString::Format("h1_NNvar_AccNoise_type%d", vartype), histtitle, 40, -0.2, 0.4);
      h1_NNvar_Decaye[vartype]   = new TH1F(TString::Format("h1_NNvar_Decaye_type%d", vartype), histtitle, 40, -0.2, 0.4);
      break;
    case 10:  //Beta5
      h1_NNvar_Gd[vartype]       = new TH1F(TString::Format("h1_NNvar_Gd_type%d", vartype),    histtitle, 40, -0.2, 0.4);
      h1_NNvar_H[vartype]        = new TH1F(TString::Format("h1_NNvar_H_type%d", vartype),     histtitle, 40, -0.2, 0.4);
      h1_NNvar_AccNoise[vartype] = new TH1F(TString::Format("h1_NNvar_AccNoise_type%d", vartype), histtitle, 40, -0.2, 0.4);
      h1_NNvar_Decaye[vartype]   = new TH1F(TString::Format("h1_NNvar_Decaye_type%d", vartype), histtitle, 40, -0.2, 0.4);
      break;*/
    case 6: //Beta1
      h1_NNvar_Gd[vartype]       = new TH1F(TString::Format("h1_NNvar_Gd_type%d", vartype),    histtitle, 40, -0.2, 0.8);
      h1_NNvar_H[vartype]        = new TH1F(TString::Format("h1_NNvar_H_type%d", vartype),     histtitle, 40, -0.2, 0.8);
      h1_NNvar_AccNoise[vartype] = new TH1F(TString::Format("h1_NNvar_AccNoise_type%d", vartype), histtitle, 40, -0.2, 0.8);
      h1_NNvar_Decaye[vartype]   = new TH1F(TString::Format("h1_NNvar_Decaye_type%d", vartype), histtitle, 40, -0.2, 0.8);
      h1_NNvar[vartype]          = new TH1F(TString::Format("h1_NNvar_type%d", vartype), histtitle, 40, -0.2, 0.8);
      break;
    case 7:  //Beta2
      h1_NNvar_Gd[vartype]       = new TH1F(TString::Format("h1_NNvar_Gd_type%d", vartype),    histtitle, 40, -0.2, 0.8);
      h1_NNvar_H[vartype]        = new TH1F(TString::Format("h1_NNvar_H_type%d", vartype),     histtitle, 40, -0.2, 0.8);
      h1_NNvar_AccNoise[vartype] = new TH1F(TString::Format("h1_NNvar_AccNoise_type%d", vartype), histtitle, 40, -0.2, 0.8);
      h1_NNvar_Decaye[vartype]   = new TH1F(TString::Format("h1_NNvar_Decaye_type%d", vartype), histtitle, 40, -0.2, 0.8);
      h1_NNvar[vartype]          = new TH1F(TString::Format("h1_NNvar_type%d", vartype), histtitle, 40, -0.2, 0.8);
      break;
    case 8:  //Beta3
      h1_NNvar_Gd[vartype]       = new TH1F(TString::Format("h1_NNvar_Gd_type%d", vartype),    histtitle, 40, -0.2, 0.8);
      h1_NNvar_H[vartype]        = new TH1F(TString::Format("h1_NNvar_H_type%d", vartype),     histtitle, 40, -0.2, 0.8);
      h1_NNvar_AccNoise[vartype] = new TH1F(TString::Format("h1_NNvar_AccNoise_type%d", vartype), histtitle, 40, -0.2, 0.8);
      h1_NNvar_Decaye[vartype]   = new TH1F(TString::Format("h1_NNvar_Decaye_type%d", vartype), histtitle, 40, -0.2, 0.8);
      h1_NNvar[vartype]          = new TH1F(TString::Format("h1_NNvar_type%d", vartype), histtitle, 40, -0.2, 0.8);
      break;
    case 9:  //Beta4
      h1_NNvar_Gd[vartype]       = new TH1F(TString::Format("h1_NNvar_Gd_type%d", vartype),    histtitle, 40, -0.2, 0.8);
      h1_NNvar_H[vartype]        = new TH1F(TString::Format("h1_NNvar_H_type%d", vartype),     histtitle, 40, -0.2, 0.8);
      h1_NNvar_AccNoise[vartype] = new TH1F(TString::Format("h1_NNvar_AccNoise_type%d", vartype), histtitle, 40, -0.2, 0.8);
      h1_NNvar_Decaye[vartype]   = new TH1F(TString::Format("h1_NNvar_Decaye_type%d", vartype), histtitle, 40, -0.2, 0.8);
      h1_NNvar[vartype]          = new TH1F(TString::Format("h1_NNvar_type%d", vartype), histtitle, 40, -0.2, 0.8);
      break;
    case 10:  //Beta5
      h1_NNvar_Gd[vartype]       = new TH1F(TString::Format("h1_NNvar_Gd_type%d", vartype),    histtitle, 40, -0.2, 0.8);
      h1_NNvar_H[vartype]        = new TH1F(TString::Format("h1_NNvar_H_type%d", vartype),     histtitle, 40, -0.2, 0.8);
      h1_NNvar_AccNoise[vartype] = new TH1F(TString::Format("h1_NNvar_AccNoise_type%d", vartype), histtitle, 40, -0.2, 0.8);
      h1_NNvar_Decaye[vartype]   = new TH1F(TString::Format("h1_NNvar_Decaye_type%d", vartype), histtitle, 40, -0.2, 0.8);
      h1_NNvar[vartype]          = new TH1F(TString::Format("h1_NNvar_type%d", vartype), histtitle, 40, -0.2, 0.8);
      break;
    case 11:  //BurstRatio
      h1_NNvar_Gd[vartype]       = new TH1F(TString::Format("h1_NNvar_Gd_type%d", vartype),    histtitle, 20, 0, 1);
      h1_NNvar_H[vartype]        = new TH1F(TString::Format("h1_NNvar_H_type%d", vartype),     histtitle, 20, 0, 1);
      h1_NNvar_AccNoise[vartype] = new TH1F(TString::Format("h1_NNvar_AccNoise_type%d", vartype), histtitle, 20, 0, 1);
      h1_NNvar_Decaye[vartype]   = new TH1F(TString::Format("h1_NNvar_Decaye_type%d", vartype), histtitle, 20, 0, 1);
      h1_NNvar[vartype]          = new TH1F(TString::Format("h1_NNvar_type%d", vartype), histtitle, 20, 0, 1);
      break;
    case 12:  //FitGoodness
      h1_NNvar_Gd[vartype]       = new TH1F(TString::Format("h1_NNvar_Gd_type%d", vartype),    histtitle, 25, 0, 1);
      h1_NNvar_H[vartype]        = new TH1F(TString::Format("h1_NNvar_H_type%d", vartype),     histtitle, 25, 0, 1);
      h1_NNvar_AccNoise[vartype] = new TH1F(TString::Format("h1_NNvar_AccNoise_type%d", vartype), histtitle, 25, 0, 1);
      h1_NNvar_Decaye[vartype]   = new TH1F(TString::Format("h1_NNvar_Decaye_type%d", vartype), histtitle, 25, 0, 1);
      h1_NNvar[vartype]          = new TH1F(TString::Format("h1_NNvar_type%d", vartype), histtitle, 25, 0, 1);
      break;
    case 13: //DarkLikelihood
      h1_NNvar_Gd[vartype]       = new TH1F(TString::Format("h1_NNvar_Gd_type%d", vartype),    histtitle, 20, 0, 1);
      h1_NNvar_H[vartype]        = new TH1F(TString::Format("h1_NNvar_H_type%d", vartype),     histtitle, 20, 0, 1);
      h1_NNvar_AccNoise[vartype] = new TH1F(TString::Format("h1_NNvar_AccNoise_type%d", vartype), histtitle, 20, 0, 1);
      h1_NNvar_Decaye[vartype]   = new TH1F(TString::Format("h1_NNvar_Decaye_type%d", vartype), histtitle, 20, 0, 1);
      h1_NNvar[vartype]          = new TH1F(TString::Format("h1_NNvar_type%d", vartype), histtitle, 20, 0, 1);
      break;
  }

  //only once
  //if (vartype==0) h1_AllNHits = new TH1F("h1_AllNHits", "", 10, 0, 10000);
}

void NNInputVariables::SetHistoFormat(int vartype, TString histtitle) {
  h1_NNvar_Gd[vartype]       -> SetLineWidth(1);
  h1_NNvar_H[vartype]        -> SetLineWidth(1);
  h1_NNvar_AccNoise[vartype] -> SetLineWidth(1);
  h1_NNvar_Decaye[vartype]   -> SetLineWidth(1);
  h1_NNvar[vartype]          -> SetLineWidth(1);

  h1_NNvar_Gd[vartype]       -> SetLineColor(kTeal-5);
  h1_NNvar_H[vartype]        -> SetLineColor(kAzure-4);
  h1_NNvar_AccNoise[vartype] -> SetLineColor(kGray+2);
  h1_NNvar_Decaye[vartype]   -> SetLineColor(kYellow-3);
  h1_NNvar[vartype]          -> SetLineColor(kViolet+2);

  h1_NNvar_Gd[vartype]       -> SetTitleOffset(1.3, "Y");
  h1_NNvar_H[vartype]        -> SetTitleOffset(1.3, "Y");
  h1_NNvar_AccNoise[vartype] -> SetTitleOffset(1.3, "Y");
  h1_NNvar_Decaye[vartype]   -> SetTitleOffset(1.3, "Y");
  h1_NNvar[vartype]          -> SetTitleOffset(1.3, "Y");

  h1_NNvar_Gd[vartype]       -> SetTitleSize(0.035, "Y");
  h1_NNvar_H[vartype]        -> SetTitleSize(0.035, "Y");
  h1_NNvar_AccNoise[vartype] -> SetTitleSize(0.035, "Y");
  h1_NNvar_Decaye[vartype]   -> SetTitleSize(0.035, "Y");
  h1_NNvar[vartype]          -> SetTitleSize(0.035, "Y");

  h1_NNvar_Gd[vartype]       -> SetLabelSize(0.035, "Y");
  h1_NNvar_H[vartype]        -> SetLabelSize(0.035, "Y");
  h1_NNvar_AccNoise[vartype] -> SetLabelSize(0.035, "Y");
  h1_NNvar_Decaye[vartype]   -> SetLabelSize(0.035, "Y");
  h1_NNvar[vartype]          -> SetLabelSize(0.035, "Y");
}

void NNInputVariables::SetNNinputHisto() {
  TString histtitle;
  for (int vartype=0; vartype<NNVARIABLES; vartype++) {
  	switch (vartype) {
#if 0
  	  case 0:
  	    histtitle = "NHits; NHits; Area Normalized";
  	    break;
  	  case 1:
  	    histtitle = "N200; N200; Area Normalized";
  	    break;
  	  case 2:
  	    histtitle = "TRMS; TRMS; Area Normalized";
  	    break;
      case 3:
  	    histtitle = "DWall; DWall; Area Normalized";
  	    break;
  	  case 4:
  	    histtitle = "DWallMeanDir; DWallMeanDir; Area Normalized";
  	    break;
  	  case 5:
  	    histtitle = "OpeningAngleMean; OpeningAngleMean; Area Normalized";
  	    break;
      case 6:
  	    histtitle = "OpeningAngleStdev; OpeningAngleStdev; Area Normalized";
  	    break;
  	  case 7:
  	    histtitle = "OpeningAngleSkew; OpeningAngleSkew; Area Normalized";
  	    break;
  	  case 8:
  	    histtitle = "MeanDirAngleMean; MeanDirAngleMean; Area Normalized";
  	    break;
  	  case 9:
  	    histtitle = "MeanDirAngleRMS; MeanDirAngleRMS; Area Normalized";
  	    break;
  	  case 10:
  	    histtitle = "Beta1; Beta1; Area Normalized";
  	    break;
  	  case 11:
  	    histtitle = "Beta5; Beta5; Area Normalized";
  	    break;
#endif

      case 0:
        histtitle = "NHits; NHits; Area Normalized";
        break;
      case 1:
        histtitle = "NResHits; NResHits; Area Normalized";
        break;
      case 2:
        histtitle = "TRMS; TRMS; Area Normalized";
        break;
      case 3:
        histtitle = "DWall; DWall; Area Normalized";
        break;
      case 4:
        histtitle = "DWallMeanDir; DWallMeanDir; Area Normalized";
        break;
      case 5:
        histtitle = "OpeningAngleStdev; OpeningAngleStdev; Area Normalized";
        break;
      case 6:
        histtitle = "Beta1; Beta1; Area Normalized";
        break;
      case 7:
        histtitle = "Beta2; Beta2; Area Normalized";
        break;
      case 8:
        histtitle = "Beta3; Beta3; Area Normalized";
        break;
      case 9:
        histtitle = "Beta4; Beta4; Area Normalized";
        break;
      case 10:
        histtitle = "Beta5; Beta5; Area Normalized";
        break;
      case 11:
        histtitle = "BurstRatio; BurstRatio; Area Normalized";
        break;
      case 12:
        histtitle = "FitGoodness; FitGoodness; Area Normalized";
        break;
      case 13:
        histtitle = "DarkLikelihood; DarkLikelihood; Area Normalized";
        break;
  	}
  	this->SetHistoFrame(vartype, histtitle);
  	this->SetHistoFormat(vartype, histtitle);
  }

  for (int i=0; i<4; i++) {
    h1_NTagOut[i] = new TH1F(TString::Format("h1_NTagOut_type%d", i), "", 20, 0, 1);
    h1_NTagOut[i] -> SetLineWidth(2);
  }
  h1_NTagOut[0] -> SetLineColor(kGray+2);
  h1_NTagOut[1] -> SetLineColor(kYellow-3);
  h1_NTagOut[2] -> SetLineColor(kAzure-4);
  h1_NTagOut[3] -> SetLineColor(kTeal-5);

  h1_NTagOut[0] -> SetFillColor(kGray+2);
  h1_NTagOut[1] -> SetFillColor(kYellow-3);
  h1_NTagOut[2] -> SetFillColor(kAzure-4);
  h1_NTagOut[3] -> SetFillColor(kTeal-5);

  h1_AllNTagOut = new TH1F("h1_AllNTagOut", "", 12, 0.6, 1.2);

  h1_Beta1 = new TH1F("h1_Beta1", "", 40, -0.2, 1.2);
  h1_Beta2 = new TH1F("h1_Beta2", "", 40, -0.2, 1.2);
  h1_Beta3 = new TH1F("h1_Beta3", "", 40, -0.2, 1.2);
  h1_Beta4 = new TH1F("h1_Beta4", "", 40, -0.2, 1.2);
  h1_Beta5 = new TH1F("h1_Beta5", "", 40, -0.2, 1.2);


  h1_FitT_NHitsExcess = new TH1F("h1_FitT_NHitsExcess", "h1_FitT_NHitsExcess; FitT[#musec]; Entries", 80, 0, 20);

  h1_FitT_NHitsExcess -> SetLineWidth(2);

  h1_IntID = new TH1F("h1_IntID", "", 25, 5, 30);
  h1_KE = new TH1F("h1_KE", "h1_KE; E_{#gamma}[MeV]; Area Normalized", 20, 0, 10);
  h1_timediff = new TH1F("h1_timediff", "h1_timediff; t^{true} - t^{reco}[#musec]; Area Normalized", 50, -0.02, 0.02);

  h1_MuNeutronMultiplicity = new TH1F("h1_MuNeutronMultiplicity", "", 5, 0, 5);
}




void NNInputVariables::cdNNInputVariables(TFile* fout) {
  fout -> mkdir("NNInputVariables");
  fout -> cd("NNInputVariables");
}

void NNInputVariables::WritePlots() {
  for (int i=0; i<NNVARIABLES; i++) {
    h1_NNvar_AccNoise[i] -> Write();
    h1_NNvar_Decaye[i]   -> Write();
    h1_NNvar_H[i]        -> Write();
    h1_NNvar_Gd[i]       -> Write();
    h1_NNvar[i]          -> Write();
  }
  SaveThisHist(h1_Beta1);
  SaveThisHist(h1_Beta2);
  SaveThisHist(h1_Beta3);
  SaveThisHist(h1_Beta4);
  SaveThisHist(h1_Beta5);

  //h1_AllNHits -> Write();

  h1_AllNTagOut -> Write();
  for (int i=0; i<4; i++) h1_NTagOut[i] -> Write();

  SaveThisHist(h1_FitT_NHitsExcess);

  Double_t tot_IntID  = h1_IntID->Integral();
  Double_t tot_energy = h1_KE->Integral();
  if (tot_IntID != 0) h1_IntID  -> Scale(1./tot_IntID);
  if (tot_energy != 0) h1_KE -> Scale(1./tot_energy);
  SaveThisHist(h1_IntID);
  SaveThisHist(h1_KE);
  SaveThisHist(h1_timediff);
  SaveThisHist(h1_MuNeutronMultiplicity);
}

