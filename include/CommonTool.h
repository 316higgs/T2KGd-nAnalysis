#pragma once

#include "/disk02/usr6/sedi/anat2ksk/src/cc0pinumu/inc/CC0PiNumu.h"
#include "/home/sedi/neutrontag/t2ksk-neutronh/SKGd_MC/analysis/T2KGdAnalysis/include/Const.h"

float GetDWall(float *Vtx) {
  float dwall = 0.;

  //Calculate the distance from the barrel
  float rho = TMath::Sqrt( Vtx[0]*Vtx[0] + Vtx[1]*Vtx[1] );
  float dR  = Const::tankR - rho/100.;

  //Calculate the distance from the top or bottom
  float dZ = 99999;
  if (Vtx[2]>0.) dZ = Const::tankZ - Vtx[2]/100.;
  else dZ = Const::tankZ + Vtx[2]/100.;

  //Take the minimum distance
  if (dR<dZ) dwall = dR;
  else dwall = dZ;

  return dwall;
}

float GetDWall(float VtxX, float VtxY, float VtxZ) {
  float dwall = 0.;

  //Calculate the distance from the barrel
  float rho = TMath::Sqrt( VtxX*VtxX + VtxY*VtxY );
  float dR  = Const::tankR - rho;

  //Calculate the distance from the top or bottom
  float dZ = 99999;
  if (VtxZ>0.) dZ = Const::tankZ - VtxZ;
  else dZ = Const::tankZ + VtxZ;

  //Take the minimum distance
  if (dR<dZ) dwall = dR;
  else dwall = dZ;

  return dwall;
}

float GetSimpleDistance(float *Vtx1, float *Vtx2) {
  //std::cout << "Vtx1 = [" << Vtx1[0] << ", " << Vtx1[1] << ", " << Vtx1[2] << "]" << std::endl;
  //std::cout << "Vtx2 = [" << Vtx2[0] << ", " << Vtx2[1] << ", " << Vtx2[2] << "]" << std::endl;
  float d_x = Vtx1[0] - Vtx2[0];
  float d_y = Vtx1[1] - Vtx2[1];
  float d_z = Vtx1[2] - Vtx2[2];
  float d   = std::sqrt( d_x*d_x + d_y*d_y + d_z*d_z ); 
  //std::cout << "Distance: " << d << std::endl;
  return d;
}

float GetInnerProduct(float *Vtx1, float *Vtx2) {
  float IP = Vtx1[0]*Vtx2[0] + Vtx1[1]*Vtx2[1] + Vtx1[2]*Vtx2[2];
  return IP;
}

void HistFillforMode(CC0PiNumu *numu, float value, TH1F** h1) {
  float wgt  = data ? 1. : numu->getOscWgt();
  int   mode = TMath::Abs(numu->var<int>("mode"));
  if (mode==1)             h1[0] -> Fill(value, wgt);
  if (mode>=2 && mode<=10) h1[1] -> Fill(value, wgt);
  if (mode>10 && mode<=30) h1[2] -> Fill(value, wgt);
  if (mode>=31)            h1[3] -> Fill(value);
}

void HistFillforLabel(CC0PiNumu *numu, float Label, float value, TH1F** h1) {
  float wgt  = data ? 1. : numu->getOscWgt();
  int   mode = TMath::Abs(numu->var<int>("mode"));
  if (mode<31) {
    if (Label==0) h1[0] -> Fill(value, wgt);
    if (Label==1) h1[1] -> Fill(value, wgt);
    if (Label==2) h1[2] -> Fill(value, wgt);
    if (Label==3) h1[3] -> Fill(value, wgt);
  }
  else {
    if (Label==0) h1[0] -> Fill(value);
    if (Label==1) h1[1] -> Fill(value);
    if (Label==2) h1[2] -> Fill(value);
    if (Label==3) h1[3] -> Fill(value);
  }
}

void HistFillperMode(CC0PiNumu *numu, float value, TH1F* h1) {
  float wgt  = data ? 1. : numu->getOscWgt();
  int   mode = TMath::Abs(numu->var<int>("mode"));
  if (mode<31) h1 -> Fill(value, wgt);
  else h1 -> Fill(value);
}

void SaveThisHist(TH1F* h1) {
  if (h1->GetEntries()!=0) h1 -> Write();
}

void SaveThisHist(TH2F* h2) {
  if (h2->GetEntries()!=0) h2 -> Write();
}

void AddLog(std::fstream fout, TString text) {
  fout << text << std::endl;
}