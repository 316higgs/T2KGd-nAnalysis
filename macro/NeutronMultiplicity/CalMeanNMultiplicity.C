

void CalMeanNMultiplicity() {

  #if 1
  float rNoise  = 0.0192;
  float NTagEff = 0.204;
  float N1Rmu   = 55;
  float NtagN   = 8;
  #endif

  #if 0
  float rNoise  = 0.0337133;
  float NTagEff = 0.436821;
  float N1Rmu   = 26.9307;
  float NtagN   = 22.695;
  #endif

  //  Mean neutron multiplicity
  float MeanN = (NtagN - rNoise*N1Rmu)/(N1Rmu*NTagEff);

  //  Error propagation
  float FctrN1Rmu   = NtagN/( NTagEff*N1Rmu*N1Rmu );
  float FctrNtagN   = 1./( NTagEff*N1Rmu );
  float Delta_N1Rmu = std::sqrt( N1Rmu );
  float Delta_NtagN = std::sqrt( NtagN );
  //float Delta_MeanN = std::sqrt( FctrN1Rmu*FctrN1Rmu * Delta_N1Rmu*Delta_N1Rmu 
  //                             + FctrNtagN*FctrNtagN * Delta_NtagN*Delta_NtagN );
  float Delta_MeanN = std::sqrt( FctrNtagN*FctrNtagN * Delta_NtagN*Delta_NtagN );

  std::cout << "Mean neutron multiplicity: " << MeanN << "+/-" << Delta_MeanN << std::endl;
  std::cout << "(Error: " << Delta_MeanN/MeanN*100. << " %)" << std::endl;
}