#pragma once

//#include "../../../include/Const.h"

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