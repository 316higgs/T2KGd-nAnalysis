
#include "CommonTool.h"

#define NA 6.0221409
#define FV 22.5
//#define POTSCALE 1.96  //Run1-10 FHC
//#define POTSCALE 1.63  //Run1-10 RHC
#define POTSCALE 0.17


void CalPOTnorm() {
  
  for (int isample=0; isample<SAMPLES; isample++) {
    TString fname = OutDir+BeamMode+"."+OscMode[isample]+"."+Prefix+".root";
    fin_MC[isample] = new TFile(fname);
  }

  // #neutrino events
#if 0
  float genNumList[SAMPLES] = {6044.42,
                               194.320,
                               12968.6,
                               265.095,
                               280.300,
                               182.070};
#endif

// #nlike
#if 0
  float genNumList[SAMPLES] = {28318.6,
                               8904.72,
                               43871.5,
                               10398.8,
                               62824.3,
                               73338.2};
#endif

// #nlike (Gd)
#if 0
  float genNumList[SAMPLES] = {26610.9,
                               8400.42,
                               41306,
                               9810.1,
                               59195.6,
                               69259.3};
#endif

// #nlike (H)
#if 0
  float genNumList[SAMPLES] = {1494.74,
                               450.848,
                               2248.65,
                               517.635,
                               3148.36,
                               3661.95};
#endif

// #nlike (decaye)
#if 0
  float genNumList[SAMPLES] = {23.791,
                               5.30049,
                               70.5246,
                               5.01398,
                               41.1304,
                               16.9504};
#endif

// #nlike (noise)
#if 0
  float genNumList[SAMPLES] = {189.147,
                               48.194,
                               246.453,
                               66.0718,
                               439.067,
                               400.078};
#endif

//////////////////////////////////////////////

// #elike
#if 0
  float genNumList[SAMPLES] = {3320.98,
                               414.854,
                               5869.23,
                               490.18,
                               4165.71,
                               1634.86};
#endif

// #elike (Gd)
#if 0
  float genNumList[SAMPLES] = {18.5648,
                               0.323309,
                               19.7293,
                               6.24122,
                               30.4549,
                               36.7057};
#endif

// #elike (H)
#if 0
  float genNumList[SAMPLES] = {0,
                               2,
                               0.579588,
                               0,
                               0.998832,
                               0};
#endif

// #elike (decaye)
#if 0
  float genNumList[SAMPLES] = {3297.76,
                               412.531,
                               5837.8,
                               483.939,
                               4134.25,
                               1597.17};
#endif

// #elike (noise)
#if 0
  float genNumList[SAMPLES] = {4.65126,
                               0,
                               11.1213,
                               0,
                               0,
                               0.983902};
#endif

//////////////////////////////////////////////

// N1 acc
#if 0
  float genNumList[SAMPLES] = {26.9994,
                               0.433372,
                               12.3573,
                               0.22731,
                               8.76214,
                               8.87491};
#endif 

// N1 dcye
#if 0
  float genNumList[SAMPLES] = {22.8931,
                               5.23611,
                               57.4208,
                               5.01398,
                               34.3422,
                               13.954};
#endif   

// N1 H
#if 0
  float genNumList[SAMPLES] = {179.131,
                               64.6552,
                               298.31,
                               71.3005,
                               408.947,
                               428.248};
#endif  

// N1 Gd
#if 0
  float genNumList[SAMPLES] = {3290.66,
                               1061.55,
                               5084.16,
                               1256.58,
                               7259.15,
                               8649.55};
#endif                         
 
//////////////////////////////////////////////

// N2 acc
#if 0
  float genNumList[SAMPLES] = {159.436,
                               47.443,
                               231.543,
                               65.7685,
                               428.308,
                               387.24};
#endif 

// N2 dcye
#if 0
  float genNumList[SAMPLES] = {0,
                               0,
                               0,
                               0,
                               0,
                               0};
#endif   

// N2 H
#if 0
  float genNumList[SAMPLES] = {1315.61,
                               386.192,
                               1950.34,
                               446.334,
                               2739.41,
                               3233.71};
#endif  

// N2 Gd
#if 0
  float genNumList[SAMPLES] = {23174.4,
                               7299.03,
                               36044.6,
                               8515.03,
                               51663.4,
                               60290.3};
#endif

//////////////////////////////////////////////

// N3 acc
#if 0
  float genNumList[SAMPLES] = {4.65126,
                               0,
                               11.1213,
                               0,
                               0,
                               0.983902};
#endif 

// N3 dcye
#if 0
  float genNumList[SAMPLES] = {3298.66,
                               412.539,
                               5844.31,
                               483.939,
                               4138.14,
                               1600.17};
#endif   

// N3 H
#if 0
  float genNumList[SAMPLES] = {0,
                               2,
                               0.579588,
                               0,
                               0.998832,
                               0};
#endif  

// N3 Gd
#if 1
  float genNumList[SAMPLES] = {22.4096,
                               1.3865,
                               26.185,
                               7.29524,
                               41.185,
                               50.4576};
#endif  

//////////////////////////////////////////////

// N4 acc
#if 0
  float genNumList[SAMPLES] = {2.71206,
                               0.317695,
                               2.55267,
                               0.0759317,
                               1.9968,
                               3.96355};
#endif 

// N4 dcye
#if 0
  float genNumList[SAMPLES] = {0,
                               0.0559095,
                               6.59536,
                               0,
                               2.90384,
                               0};
#endif   

// N4 H
#if 0
  float genNumList[SAMPLES] = {0,
                               0,
                               0,
                               0,
                               0,
                               0};
#endif  

// N4 Gd
#if 0
  float genNumList[SAMPLES] = {142.07,
                               38.7621,
                               170.551,
                               37.5173,
                               262.177,
                               305.175};
#endif     

  ApplyNormforSamples(genNumList);
}




