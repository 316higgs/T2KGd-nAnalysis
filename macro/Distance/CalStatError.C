

float CalStatFracErr(float NTrueN, float TagEff);


void CalStatError() {

#if 0
  ////  nominal MC  ////
  float NTrueN    = 52223.841;
  float NTagTrueN = 23031.667;
#endif

#if 0
  ////  -30% MC  ////
  float NTrueN    = 49724.964;
  float NTagTrueN = 21692.354;
#endif

#if 1
  ////  +30% MC  ////
  float NTrueN    = 53837.23;
  float NTagTrueN = 23638.752;
#endif


  float TagEff = NTagTrueN/NTrueN;

  std::cout << "Efficiency: " << TagEff << " %, Fractional error: " << CalStatFracErr(NTrueN, TagEff)*100. << " %)" << std::endl;
}


float CalStatFracErr(float NTrueN, float TagEff) {
  float dEff = 1./TagEff * std::sqrt( (TagEff*(1 - TagEff)) / NTrueN );
  return dEff;
}