

float CalMeanN(float NtagN, float N1Rmu, float TagEff, float rnoise);
float CalMeanNStatErr(float NtagN, float TagEff, float N1Rmu);


void CalStatError() {
  
  /////  input variables  ////
#if 0
  ////  Table 8.12 0 < Pt < 0.25  ////
  float N1Rmu  = 55.;
  float NtagN  = 8.;
  float TagEff = 0.204;
  float rnoise = 0.02;
#endif

#if 1
  ////  Generated  ////
  float N1Rmu  = 20201.8;
  float NtagN  = 23298.5;
  float TagEff = 0.441;
  float rnoise = 0.0135;
#endif

#if 0
  ////  Run11 POT normalized  ////
  float N1Rmu  = 27.1;
  float NtagN  = 22.1;
  float TagEff = 0.436;
  float rnoise = 0.0134;
#endif

#if 0
  ////  0 < Pt < 0.25  ////
  float N1Rmu  = 8.82774;
  float NtagN  = 5.23244;
  float TagEff = 0.431173;
  float rnoise = 0.0135;
#endif

#if 0
  ////  0.25 < Pt < 0.5  ////
  float N1Rmu  = 11.9545;
  float NtagN  = 9.04081;
  float TagEff = 0.441699;
  float rnoise = 0.0135;
#endif

#if 0
  ////  0.5 < Pt < 0.75  ////
  float N1Rmu  = 4.9224;
  float NtagN  = 5.29716;
  float TagEff = 0.441699;
  float rnoise = 0.0135;
#endif

#if 0
  ////  Pt > 0.75  ////
  float N1Rmu  = 1.42219;
  float NtagN  = 2.52017;
  float TagEff = 0.440070;
  float rnoise = 0.0135;
#endif


  /////  Mean neutron multiplicity  /////
  float M = CalMeanN(NtagN, N1Rmu, TagEff, rnoise);

  /////  Stat. error  /////
  float dM = CalMeanNStatErr(NtagN, TagEff, N1Rmu);

  std::cout << "Mean neutron multiplicity: " << M << " +/- " << dM << "  (fractional error: " << ( dM/M )*100. << " %)" << std::endl;
}


float CalMeanN(float NtagN, float N1Rmu, float TagEff, float rnoise) {
  float M = 1./TagEff * ( NtagN - rnoise*N1Rmu ) / N1Rmu;
  return M;
}

float CalMeanNStatErr(float NtagN, float TagEff, float N1Rmu) {
  float dM = std::sqrt( NtagN ) / ( TagEff * N1Rmu );
  return dM;
}