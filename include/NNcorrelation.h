#include "TH2D.h"
#include "TH1.h"
#include "TAxis.h"
#include "TColor.h"
#include <iomanip>

#define VARNUM 12

TH2D* h2_matrix = new TH2D("h2_matrix", "", VARNUM, 0, VARNUM, VARNUM, 0, VARNUM);


//Template of Correlation calculation
Double_t GetCorrelation(int N, Double_t* var1, Double_t* var2) {

  Double_t sum1 = 0.;
  Double_t sum2 = 0.;
  for (int i=0; i<N; i++) {
  	sum1 += var1[i];
  	sum2 += var2[i];
  }
  //std::cout << "sum1 = " << sum1 << ", sum2 = " << sum2 << std::endl;

  Double_t ave1 = sum1/N;
  Double_t ave2 = sum2/N;
  //std::cout << "ave1 = " << ave1 << ", ave2 = " << ave2 << std::endl;

  Double_t s1 = 0.;
  Double_t s2 = 0.;
  Double_t s12 = 0.;
  for (int i=0; i<N; i++) {
    s1  += (var1[i] - ave1)*(var1[i] - ave1);
    s2  += (var2[i] - ave2)*(var2[i] - ave2);
    s12 += (var1[i] - ave1)*(var2[i] - ave2);
  }
  Double_t r = s12/(std::sqrt(s1) * std::sqrt(s2));
  //std::cout << "Sample Correlation Coefficient = " << r << std::endl;

  return r; 
}



//int self correlation
Double_t GetMatrixElementI(int type, TChain* tchntag, const int ntagEntries, const char* varname) {
  //=========  Variables in TTree  ============
  //=========  TTree ntvar variables  ============
  std::vector<int> *CaptureType = 0;
  TBranch *bCaptureType = 0;
  std::vector<int> *NNvar = 0;
  TBranch *bNNvar = 0;

  tchntag->SetBranchAddress("CaptureType", &CaptureType, &bCaptureType);
  tchntag->SetBranchAddress(varname, &NNvar, &bNNvar);
  
  //std::cout << "Loading 1st NN input variable: " << varname << std::endl;
  //std::cout << "Loading 2nd NN input variable: " << varname << std::endl;

  int arraysize = 0;
  int noisesize = 0;
  int hsize     = 0;
  int gdsize    = 0;

  //Get array size of each type
  for (Int_t ientry=0; ientry<ntagEntries; ientry++) {

    tchntag ->GetEntry(ientry);

    Long64_t tentry = tchntag->LoadTree(ientry);
    bNNvar        -> GetEntry(tentry);
    bCaptureType  -> GetEntry(tentry);

    for (UInt_t jentry=0; jentry<NNvar->size(); jentry++) {

      arraysize++;
      if (CaptureType->at(jentry)==0) noisesize++;
      if (CaptureType->at(jentry)==1) hsize++;
      if (CaptureType->at(jentry)==2) gdsize++;
    }
  }


  int entries;
  switch(type) {
    case 0:
      entries = noisesize;
      break;
    case 1:
      entries = hsize;
      break;
    case 2:
      entries = gdsize;
      break;
    default:
      entries = arraysize;
  }

  //Array for NN input variables
  Double_t var[entries]; 
  //std::cout << "Array size: " << entries << std::endl;
  for (int i=0; i<entries; i++) {
    var[i] = 0;
  }


  //Array filling
  int element = 0;
  for (Int_t ientry=0; ientry<ntagEntries; ientry++) {

    tchntag -> GetEntry(ientry);

    Long64_t tentry = tchntag->LoadTree(ientry);
    bNNvar        -> GetEntry(tentry);
    bCaptureType  -> GetEntry(tentry);

    for (UInt_t jentry=0; jentry<NNvar->size(); jentry++) {

      if (type==0) {
        if (CaptureType->at(jentry)==0) {
          var[element] = NNvar->at(jentry);
          element++;
        }
      }
      else if (type==1) {
        if (CaptureType->at(jentry)==1) {
          var[element] = NNvar->at(jentry);
          element++;
        }
      }
      else if (type==2) {
        if (CaptureType->at(jentry)==2) {
          var[element] = NNvar->at(jentry);
          element++;
        }
      }
      else if (type!=0 && type!=1 && type!=2) {
        var[element] = NNvar->at(jentry);
        element++;
      }

    }
  }

  //Get correlation factor between var itself
  std::cout << " Correlation factor       : " << GetCorrelation(entries, var, var) << std::endl;
  return GetCorrelation(entries, var, var);
}



//float self correlation
Double_t GetMatrixElementF(int type, TChain* tchntag, const int ntagEntries, const char* varname) {
  //=========  Variables in TTree  ============
  //=========  TTree ntvar variables  ============
  //std::vector<int> *CaptureType = 0;
  std::vector<float> *Label = 0;
  TBranch *bLabel = 0;
  std::vector<float> *NNvar = 0;
  TBranch *bNNvar = 0;

  //tchntag->SetBranchAddress("CaptureType", &CaptureType, &bCaptureType);
  tchntag->SetBranchAddress("Label", &Label, &bLabel);
  tchntag->SetBranchAddress(varname, &NNvar, &bNNvar);
  
  //std::cout << "Loading 1st NN input variable: " << varname << std::endl;
  //std::cout << "Loading 2nd NN input variable: " << varname << std::endl;

  int arraysize = 0;
  int noisesize = 0;
  int dcyesize  = 0;
  int hsize     = 0;
  int gdsize    = 0;

  //Get array size of each type
  for (Int_t ientry=0; ientry<ntagEntries; ientry++) {

    tchntag ->GetEntry(ientry);

    Long64_t tentry = tchntag->LoadTree(ientry);
    bNNvar        -> GetEntry(tentry);
    //bCaptureType  -> GetEntry(tentry);
    bLabel        -> GetEntry(tentry);

    for (UInt_t jentry=0; jentry<NNvar->size(); jentry++) {

      arraysize++;
      if (Label->at(jentry)==0) noisesize++;
      if (Label->at(jentry)==1) dcyesize++;
      if (Label->at(jentry)==2) hsize++;
      if (Label->at(jentry)==3) gdsize++;
    }
  }


  int entries;
  switch(type) {
    case 0:
      entries = noisesize;
      break;
    case 1:
      entries = dcyesize;
      break;
    case 2:
      entries = hsize;
      break;
    case 3:
      entries = gdsize;
      break;
    default:
      entries = arraysize;
  }

  //Array for NN input variables
  Double_t var[entries]; 
  //std::cout << "Array size: " << entries << std::endl;
  for (int i=0; i<entries; i++) {
    var[i] = 0;
  }


  //Array filling
  int element = 0;
  for (Int_t ientry=0; ientry<ntagEntries; ientry++) {

    tchntag -> GetEntry(ientry);

    Long64_t tentry = tchntag->LoadTree(ientry);
    bNNvar        -> GetEntry(tentry);
    //bCaptureType  -> GetEntry(tentry);
    bLabel        -> GetEntry(tentry);

    for (UInt_t jentry=0; jentry<NNvar->size(); jentry++) {

      if (Label->at(jentry)==type) {
        var[element] = NNvar->at(jentry);
        element++;
      }
      else if (type!=0 && type!=1 && type!=2 && type!=3) {
        var[element] = NNvar->at(jentry);
        element++;
      }

      /*if (type==0) {
        if (CaptureType->at(jentry)==0) {
          var[element] = NNvar->at(jentry);
          element++;
        }
      }
      else if (type==1) {
        if (CaptureType->at(jentry)==1) {
          var[element] = NNvar->at(jentry);
          element++;
        }
      }
      else if (type==2) {
        if (CaptureType->at(jentry)==2) {
          var[element] = NNvar->at(jentry);
          element++;
        }
      }
      else if (type!=0 && type!=1 && type!=2) {
        var[element] = NNvar->at(jentry);
        element++;
      }*/

    }
  }

  //Get correlation factor between var itself
  std::cout << " Correlation factor       : " << GetCorrelation(entries, var, var) << std::endl;
  return GetCorrelation(entries, var, var);
}



//int vs int
Double_t GetMatrixElementII(int type, TChain* tchntag, const int ntagEntries, const char* varname1, const char* varname2) {
  //=========  Variables in TTree  ============
  //=========  TTree ntvar variables  ============
  std::vector<int> *CaptureType = 0;
  TBranch *bCaptureType = 0;
  std::vector<int> *NNvar1 = 0;
  TBranch *bNNvar1 = 0;
  std::vector<int> *NNvar2 = 0;
  TBranch *bNNvar2 = 0;

  tchntag->SetBranchAddress("CaptureType", &CaptureType, &bCaptureType);
  tchntag->SetBranchAddress(varname1, &NNvar1, &bNNvar1);
  tchntag->SetBranchAddress(varname2, &NNvar2, &bNNvar2);
  
  //std::cout << "Loading 1st NN input variable: " << varname1 << std::endl;
  //std::cout << "Loading 2nd NN input variable: " << varname2 << std::endl;

  int arraysize = 0;
  int noisesize = 0;
  int hsize     = 0;
  int gdsize    = 0;

  //Get array size of each type
  for (Int_t ientry=0; ientry<ntagEntries; ientry++) {

    tchntag ->GetEntry(ientry);

    Long64_t tentry = tchntag->LoadTree(ientry);
    bNNvar1       -> GetEntry(tentry);
    bCaptureType  -> GetEntry(tentry);

    for (UInt_t jentry=0; jentry<NNvar1->size(); jentry++) {

      arraysize++;
      if (CaptureType->at(jentry)==0) noisesize++;
      if (CaptureType->at(jentry)==1) hsize++;
      if (CaptureType->at(jentry)==2) gdsize++;
    }
  }


  int entries;
  switch(type) {
    case 0:
      entries = noisesize;
      break;
    case 1:
      entries = hsize;
      break;
    case 2:
      entries = gdsize;
      break;
    default:
      entries = arraysize;
  }

  //Array for NN input variables
  Double_t var1[entries]; 
  Double_t var2[entries];
  //std::cout << "Array size: " << entries << std::endl;
  for (int i=0; i<entries; i++) {
    var1[i] = 0;
    var2[i] = 0;
  }


  //Array filling
  int element = 0;
  for (Int_t ientry=0; ientry<ntagEntries; ientry++) {

    tchntag -> GetEntry(ientry);

    Long64_t tentry = tchntag->LoadTree(ientry);
    bNNvar1       -> GetEntry(tentry);
    bNNvar2       -> GetEntry(tentry);
    bCaptureType  -> GetEntry(tentry);

    for (UInt_t jentry=0; jentry<NNvar1->size(); jentry++) {

      if (type==0) {
        if (CaptureType->at(jentry)==0) {
          var1[element] = NNvar1->at(jentry);
          var2[element] = NNvar2->at(jentry);
          element++;
        }
      }
      else if (type==1) {
        if (CaptureType->at(jentry)==1) {
          var1[element] = NNvar1->at(jentry);
          var2[element] = NNvar2->at(jentry);
          element++;
        }
      }
      else if (type==2) {
        if (CaptureType->at(jentry)==2) {
          var1[element] = NNvar1->at(jentry);
          var2[element] = NNvar2->at(jentry);
          element++;
        }
      }
      else if (type!=0 && type!=1 && type!=2) {
        var1[element] = NNvar1->at(jentry);
        var2[element] = NNvar2->at(jentry);
        element++;
      }

    }
  }

  //Get correlation factor between var1 and var2
  std::cout << " Correlation factor       : " << GetCorrelation(entries, var1, var2) << std::endl;
  return GetCorrelation(entries, var1, var2);
}



//int vs float
Double_t GetMatrixElementIF(int type, TChain* tchntag, const int ntagEntries, const char* varname1, const char* varname2) {
  //=========  Variables in TTree  ============
  //=========  TTree ntvar variables  ============
  std::vector<int> *CaptureType = 0;
  TBranch *bCaptureType = 0;
  std::vector<int> *NNvar1 = 0;
  TBranch *bNNvar1 = 0;
  std::vector<float> *NNvar2 = 0;
  TBranch *bNNvar2 = 0;

  tchntag->SetBranchAddress("CaptureType", &CaptureType, &bCaptureType);
  tchntag->SetBranchAddress(varname1, &NNvar1, &bNNvar1);
  tchntag->SetBranchAddress(varname2, &NNvar2, &bNNvar2);
  
  //std::cout << "Loading 1st NN input variable: " << varname1 << std::endl;
  //std::cout << "Loading 2nd NN input variable: " << varname2 << std::endl;

  int arraysize = 0;
  int noisesize = 0;
  int hsize     = 0;
  int gdsize    = 0;

  //Get array size of each type
  for (Int_t ientry=0; ientry<ntagEntries; ientry++) {

    tchntag ->GetEntry(ientry);

    Long64_t tentry = tchntag->LoadTree(ientry);
    bNNvar1       -> GetEntry(tentry);
    bCaptureType  -> GetEntry(tentry);

    for (UInt_t jentry=0; jentry<NNvar1->size(); jentry++) {

      arraysize++;
      if (CaptureType->at(jentry)==0) noisesize++;
      if (CaptureType->at(jentry)==1) hsize++;
      if (CaptureType->at(jentry)==2) gdsize++;
    }
  }


  int entries;
  switch(type) {
    case 0:
      entries = noisesize;
      break;
    case 1:
      entries = hsize;
      break;
    case 2:
      entries = gdsize;
      break;
    default:
      entries = arraysize;
  }

  //Array for NN input variables
  Double_t var1[entries]; 
  Double_t var2[entries];
  //std::cout << "Array size: " << entries << std::endl;
  for (int i=0; i<entries; i++) {
    var1[i] = 0;
    var2[i] = 0;
  }


  //Array filling
  int element = 0;
  for (Int_t ientry=0; ientry<ntagEntries; ientry++) {

    tchntag -> GetEntry(ientry);

    Long64_t tentry = tchntag->LoadTree(ientry);
    bNNvar1       -> GetEntry(tentry);
    bNNvar2       -> GetEntry(tentry);
    bCaptureType  -> GetEntry(tentry);

    for (UInt_t jentry=0; jentry<NNvar1->size(); jentry++) {

      if (type==0) {
        if (CaptureType->at(jentry)==0) {
          var1[element] = NNvar1->at(jentry);
          var2[element] = NNvar2->at(jentry);
          element++;
        }
      }
      else if (type==1) {
        if (CaptureType->at(jentry)==1) {
          var1[element] = NNvar1->at(jentry);
          var2[element] = NNvar2->at(jentry);
          element++;
        }
      }
      else if (type==2) {
        if (CaptureType->at(jentry)==2) {
          var1[element] = NNvar1->at(jentry);
          var2[element] = NNvar2->at(jentry);
          element++;
        }
      }
      else if (type!=0 && type!=1 && type!=2) {
        var1[element] = NNvar1->at(jentry);
        var2[element] = NNvar2->at(jentry);
        element++;
      }

    }
  }

  //Get correlation factor between var1 and var2
  std::cout << " Correlation factor       : " << GetCorrelation(entries, var1, var2) << std::endl;
  return GetCorrelation(entries, var1, var2);
}



//float vs float
Double_t GetMatrixElementFF(int type, TChain* tchntag, const int ntagEntries, const char* varname1, const char* varname2) {
  //=========  Variables in TTree  ============
  //=========  TTree ntag variables  ============
  /*std::vector<int> *CaptureType = 0;
  TBranch *bCaptureType = 0;*/
  std::vector<float> *Label = 0;
  TBranch *bLabel = 0;
  std::vector<float> *NNvar1 = 0;
  TBranch *bNNvar1 = 0;
  std::vector<float> *NNvar2 = 0;
  TBranch *bNNvar2 = 0;

  //tchntag->SetBranchAddress("CaptureType", &CaptureType, &bCaptureType);
  tchntag->SetBranchAddress("Label", &Label, &bLabel);
  tchntag->SetBranchAddress(varname1, &NNvar1, &bNNvar1);
  tchntag->SetBranchAddress(varname2, &NNvar2, &bNNvar2);
  
  //std::cout << "Loading 1st NN input variable: " << varname1 << std::endl;
  //std::cout << "Loading 2nd NN input variable: " << varname2 << std::endl;

  int arraysize = 0;
  int noisesize = 0;
  int dcyesize  = 0;
  int hsize     = 0;
  int gdsize    = 0;

  //Get array size of each type
  for (Int_t ientry=0; ientry<ntagEntries; ientry++) {

    tchntag ->GetEntry(ientry);

    Long64_t tentry = tchntag->LoadTree(ientry);
    bNNvar1       -> GetEntry(tentry);
    //bCaptureType  -> GetEntry(tentry);
    bLabel        -> GetEntry(tentry);

    for (UInt_t jentry=0; jentry<NNvar1->size(); jentry++) {

      arraysize++;
      /*if (CaptureType->at(jentry)==0) noisesize++;
      if (CaptureType->at(jentry)==1) hsize++;
      if (CaptureType->at(jentry)==2) gdsize++;*/
      if (Label->at(jentry)==0) noisesize++;
      if (Label->at(jentry)==1) dcyesize++;
      if (Label->at(jentry)==2) hsize++;
      if (Label->at(jentry)==3) gdsize++;
    }
  }


  int entries;
  /*switch(type) {
    case 0:
      entries = noisesize;
      break;
    case 1:
      entries = hsize;
      break;
    case 2:
      entries = gdsize;
      break;
    default:
      entries = arraysize;
  }*/
  switch(type) {
    case 0:
      entries = noisesize;
      break;
    case 1:
      entries = dcyesize;
      break;
    case 2:
      entries = hsize;
      break;
    case 3:
      entries = gdsize;
      break;
    default:
      entries = arraysize;
  }

  //Array for NN input variables
  Double_t var1[entries]; 
  Double_t var2[entries];
  //std::cout << "Array size: " << entries << std::endl;
  for (int i=0; i<entries; i++) {
    var1[i] = 0;
    var2[i] = 0;
  }


  //Array filling
  int element = 0;
  for (Int_t ientry=0; ientry<ntagEntries; ientry++) {

    tchntag -> GetEntry(ientry);

    Long64_t tentry = tchntag->LoadTree(ientry);
    bNNvar1       -> GetEntry(tentry);
    bNNvar2       -> GetEntry(tentry);
    //bCaptureType  -> GetEntry(tentry);
    bLabel        -> GetEntry(tentry);

    for (UInt_t jentry=0; jentry<NNvar1->size(); jentry++) {

      if (Label->at(jentry)==type) {
        var1[element] = NNvar1->at(jentry);
        var2[element] = NNvar2->at(jentry);
        element++;
      }
      else if (type!=0 && type!=1 && type!=2 && type!=3) {
        var1[element] = NNvar1->at(jentry);
        var2[element] = NNvar2->at(jentry);
        element++;
      }

      /*
      if (type==0) {
        if (CaptureType->at(jentry)==0) {
          var1[element] = NNvar1->at(jentry);
          var2[element] = NNvar2->at(jentry);
          element++;
        }
      }
      else if (type==1) {
        if (CaptureType->at(jentry)==1) {
          var1[element] = NNvar1->at(jentry);
          var2[element] = NNvar2->at(jentry);
          element++;
        }
      }
      else if (type==2) {
        if (CaptureType->at(jentry)==2) {
          var1[element] = NNvar1->at(jentry);
          var2[element] = NNvar2->at(jentry);
          element++;
        }
      }
      else if (type==3) {
        if (CaptureType->at(jentry)==2) {
          var1[element] = NNvar1->at(jentry);
          var2[element] = NNvar2->at(jentry);
          element++;
        }
      }
      else if (type!=0 && type!=1 && type!=2) {
        var1[element] = NNvar1->at(jentry);
        var2[element] = NNvar2->at(jentry);
        element++;
      }
      */

    }
  }

  //Get correlation factor between var1 and var2
  std::cout << " Correlation factor       : " << GetCorrelation(entries, var1, var2) << std::endl;
  return GetCorrelation(entries, var1, var2);
}

