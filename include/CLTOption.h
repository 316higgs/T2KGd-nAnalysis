#include "src/TreeManager/inc/TreeManager.h"

bool etagmode = false;
bool nosample = false;
bool ntaginfo = true;
//SampleChannel channel;

enum OscChan::E_OSC_CHAN CLTOptionOscMode(TString OscKeyWord, TString Osc) {
  enum OscChan::E_OSC_CHAN eOscMode = eNUMU;
  if (OscKeyWord=="-OSCCH") {
    if (Osc=="NUMU" || Osc=="numu") eOscMode = eNUMU;                     //numu_x_numu
    else if (Osc=="NUMUBAR" || Osc=="numubar") eOscMode = eNUMUBAR;       //numubar_x_numubar
    else if (Osc=="NUESIG" || Osc=="nuesig") eOscMode = eNUESIG;          //numu_x_nue
    else if (Osc=="NUEBARSIG" || Osc=="nuebarsig") eOscMode = eNUEBARSIG; //numubar_x_nuebar
    else if (Osc=="NUE" || Osc=="nue") eOscMode = eNUE;                   //nue_x_nue
    else if (Osc=="NUEBAR" || Osc=="nuebar") eOscMode = eNUEBAR;          //nuebar_x_nuebar
    else {
      std::cout << " " << std::endl;
      std::cout << "\e[38;5;A0m\e[1m[!!!CLT error!!!] Oscillation channel can not be found. --- input NUMU/NUMUBAR\e[0m" << std::endl;
      exit(-1);
    }
  }
  return eOscMode;
}

enum BeamMode::E_BEAM_MODE CLTOptionBeamMode(TString BeamKeyWord, TString Beam) {
  enum BeamMode::E_BEAM_MODE eBeamMode = eFHC;
  if (BeamKeyWord=="-BEAMMODE") {
    if (Beam=="FHC") eBeamMode = eFHC;
    else if (Beam=="RHC") eBeamMode = eRHC;
    else {
      std::cout << " " << std::endl;
      std::cout << "\e[38;5;A0m\e[1m[!!!CLT error!!!] Oscillation channel can not be found. --- input FHC or RHC\e[0m" << std::endl;
      exit(-1);
    }
  }
  return eBeamMode;
}

void CLTOptionETAG(TString ETAGKeyword, TString ETAG) {
  if (ETAGKeyword=="-ETAG") {
    if (ETAG=="ON" || ETAG=="On" || ETAG=="on") etagmode = true;
    else if (ETAG=="OFF" || ETAG=="Off" || ETAG=="off") etagmode = false;
    else {
      std::cout << " " << std::endl;
      std::cout << "\e[38;5;A0m\e[1m[!!!CLT error!!!] Decay-e tagging mode can not be found. --- input ON or OFF\e[0m" << std::endl;
      exit(-1);
    }
  }
}

void CLTOptionPrePara(TString PreParaKeyword, TString PrePara) {
  if (PreParaKeyword=="-TWIDTH" || PreParaKeyword=="-NHITSTH") {
    std::cout << "\e[38;5;03m\e[1m[### CLT Option Summary ###] " << PreParaKeyword << ": " << PrePara << std::endl;
  }
  else {
    std::cout << "\e[38;5;A0m\e[1m[!!!CLT error!!!] Pre-selection parameter should be specified at command line.\e[0m" << std::endl;
    std::cout << "\e[38;5;A0m\e[1m                  Please specify values with " << PreParaKeyword << " option.\e[0m" << std::endl;
    exit(-1);
  }
}

void CLTOptionWindow(TString WINDOWKeyword, TString WINDOW) {
  if (WINDOWKeyword=="-WINDOW") {
    std::cout << "\e[38;5;03m\e[1m[### CLT Option Summary ###] " << WINDOWKeyword << ": " << WINDOW << std::endl;
  }
  else {
    std::cout << "\e[38;5;A0m\e[1m[!!!CLT error!!!] Window size should be specified at command line.\e[0m" << std::endl;
    std::cout << "\e[38;5;A0m\e[1m                  Please specify values with " << WINDOWKeyword << " option.\e[0m" << std::endl;
    exit(-1);
  }
}

bool CLTOptionSample(TString SampleKeyword, TString Sample) {
  if (SampleKeyword=="-SAMPLE") {
    std::cout << "\e[38;5;03m\e[1m[### CLT Option Summary ###] " << SampleKeyword << ": " << Sample << std::endl;
    if (Sample=="NO" || Sample=="No" || Sample=="no") nosample = false;
    else nosample = true;
  }
  else {
    std::cout << "\e[38;5;A0m\e[1m[!!!CLT error!!!] Existence of input files should be specified at command line.\e[0m" << std::endl;
    std::cout << "\e[38;5;A0m\e[1m                  Please specify values with " << SampleKeyword << " option.\e[0m" << std::endl;
    exit(-1);
  }
  return nosample;
}

bool CLTOptionNTagInfo(TString NTagInfoKeyword, TString NTagInfo) {
  if (NTagInfoKeyword=="-NTAGINFO") {
    std::cout << "\e[38;5;03m\e[1m[### CLT Option Summary ###] " << NTagInfoKeyword << ": " << NTagInfo << std::endl;
    if (NTagInfo=="NO" || NTagInfo=="No" || NTagInfo=="no") ntaginfo = false;
    else ntaginfo = true;
  }
  else {
    std::cout << "\e[38;5;A0m\e[1m[!!!CLT error!!!] Existence of input files should be specified at command line.\e[0m" << std::endl;
    std::cout << "\e[38;5;A0m\e[1m                  Please specify values with " << NTagInfoKeyword << " option.\e[0m" << std::endl;
    exit(-1);
  }
  return ntaginfo;
}

/*void CLTOptionChannel(TString SampleChKeyword, TString SampleCh) {
  if (SampleChKeyword=="-SAMPLECH") {
    std::cout << "[### CLT Option Summary ###] " << SampleChKeyword << " : " << SampleCh << std::endl;
    switch (SampleCh) {
      case numu_x_numu:
        channel = numu_x_numu;
        break;
      case numubar_x_numubar:
        channel = numubar_x_numubar;
        break;
      case numu_x_nue:
        channel = numu_x_nue;
        break;
      case numubar_x_nuebar:
        channel = numubar_x_nuebar;
        break;
      case nue_x_nue:
        channel = nue_x_nue;
        break;
      case nuebar_x_nuebar:
        channel = nuebar_x_nuebar;
        break;
      default:
        channel = numu_x_numu;
        break;
    }
    std::cout << "[### CLT Option Summary ###] Oscillation channel: " << channel << std::endl;
  }
  else {
    std::cout << "[!!!CLT error!!!] Oscillation channel should be specified at command line." << std::endl;
    std::cout << "                  Please specify values with " << SampleChKeyword << " option." << std::endl;
    exit(-1);
  }
}*/


void CLTOptionSummary(TString ETAGKeyword, TString ETAG,
                      TString MCTypeKeyword, TString MCType) 
{
  bool etagoption = false;
  if (ETAGKeyword=="-ETAG") {
    etagoption = true;
    std::cout << "\e[38;5;03m\e[1m[### CLT Option Summary ###] e-tagging: " << ETAG << std::endl;
  }
  bool mctypeoption = false;
  if (MCTypeKeyword=="-MCType") {
    mctypeoption = true;
    std::cout << "\e[38;5;03m\e[1m[### CLT Option Summary ###] MC type: " << MCType << std::endl;
  }

  if (etagoption==false && mctypeoption==false) {
    std::cout << " " << std::endl;
    std::cout << "\e[38;5;03m\e[1m[### CLT Option Summary ###] No option" << std::endl;
  }
  
}
  