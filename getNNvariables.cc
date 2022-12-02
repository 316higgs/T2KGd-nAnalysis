#include <iostream>
#include <unistd.h>
#include "TChain.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TROOT.h"
#include "TGaxis.h"
#include "TPaveStats.h"
#include "THStack.h"
//#include "CC0PiNumu.h"  //src: /disk02/usr6/rakutsu/t2k/tmp/t2ksk-neutronh/anat2ksk/src/cc0pinumu
#include "DefBeamMode.h"
#include "DefOscChannels.h"

#include "include/NeutrinoEvents.h"
#include "include/NTagVariables.h"
#include "include/CLTOption.h"
#include "include/ResultSummary.h"

#include "src/DecayeBox/inc/DecayeBox.h"
#include "src/Gd1RmuonSelection/inc/Gd1RmuonSelection.h"
#include "src/NeutrinoOscillation/inc/NeutrinoOscillation.h"
#include "src/DistanceViewer/inc/DistanceViewer.h"
#include "src/NTagAnalysis/inc/NTagAnalysis.h"
#include "src/NNInputVariables/inc/NNInputVariables.h"

#define NLIKETHRESHOLD 0.75


int main(int argc, char **argv) {

  TString fiTQunFileName = argv[1];
  TString NtagFileName   = argv[2];
  TString OutputRootName = argv[3];
  TString ResultSummary  = argv[4];
  TString NTagSummary    = argv[5];
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

  //=========  fiTQun output (TTree: h1)  ============
  TChain *tchfQ = new TChain("h1");
  int nfQFiles = tchfQ->Add( fiTQunFileName );
  if ( nfQFiles==0 ) {
    std::cout << "[### analysis1Rmu ###]  Cannot load TTree h1 from: " << fiTQunFileName << std::endl;
    std::cout << "[### analysis1Rmu ###]  -> EXIT " << std::endl;
    exit(-1);
  }
  //=========  Event info (TTree: event)  ============
  TChain *tchev = new TChain("event");
  int nevFiles = tchev->Add( NtagFileName );
  if ( nevFiles==0 ) {
    std::cout << "[### analysis1Rmu ###]  Cannot load TTree event from: " << NtagFileName << std::endl;
    std::cout << "[### analysis1Rmu ###]  -> EXIT " << std::endl;
    exit(-1);
  }
  //=========  Event info (TTree: particle)  ============
  TChain *tchpar = new TChain("particle");
  int nparFiles = tchpar->Add( NtagFileName );
  if ( nparFiles==0 ) {
    std::cout << "[### analysis1Rmu ###]  Cannot load TTree particle from: " << NtagFileName << std::endl;
    std::cout << "[### analysis1Rmu ###]  -> EXIT " << std::endl;
    exit(-1);
  }
  //=========  Delayed info (TTree: taggable)  ============
  TChain *tchtaggable = new TChain("taggable");
  int ntaggableFiles = tchtaggable->Add( NtagFileName );
  if ( ntaggableFiles==0 ) {
    std::cout << "[### analysis1Rmu ###]  Cannot load TTree taggable from: " << NtagFileName << std::endl;
    std::cout << "[### analysis1Rmu ###]  -> EXIT " << std::endl;
    exit(-1);
  }
  //=========  NTag output (TTree: ntag)  ============
  TChain *tchntag = new TChain("ntag");
  int ntagFiles = tchntag->Add( NtagFileName );
  if ( ntagFiles==0 ) {
    std::cout << "[### analysis1Rmu ###]  Cannot load TTree ntag from: " << NtagFileName << std::endl;
    std::cout << "[### analysis1Rmu ###]  -> EXIT " << std::endl;
    exit(-1);
  }
  //Load succeed
  std::cout << "[### analysis1Rmu ###]  Loaded " << nfQFiles       << " files from: " << fiTQunFileName << std::endl;
  std::cout << "[### analysis1Rmu ###]  Loaded " << nevFiles       << " files from: " << NtagFileName   << std::endl;
  std::cout << "[### analysis1Rmu ###]  Loaded " << nparFiles      << " files from: " << NtagFileName   << std::endl;
  std::cout << "[### analysis1Rmu ###]  Loaded " << ntaggableFiles << " files from: " << NtagFileName   << std::endl;
  std::cout << "[### analysis1Rmu ###]  Loaded " << ntagFiles      << " files from: " << NtagFileName   << std::endl;


  const int nfQEntries       = tchfQ->GetEntries();       //total entries of TTree h1
  const int nevEntries       = tchev->GetEntries();       //total entries of TTree event
  const int nparEntries      = tchpar->GetEntries();       //total entries of TTree particle
  const int ntaggableEntries = tchtaggable->GetEntries(); //total entries of TTree taggable
  const int ntagEntries      = tchntag->GetEntries();     //total entries of TTree ntag
  std::cout << "[### analysis1Rmu ###]  fiTQun output     : Processing " << nfQEntries       <<" entries..." << std::endl;
  std::cout << "[### analysis1Rmu ###]  Event info        : Processing " << nevEntries       <<" entries..." << std::endl;
  std::cout << "[### analysis1Rmu ###]  Particle info     : Processing " << nparEntries      <<" entries..." << std::endl;
  std::cout << "[### analysis1Rmu ###]  Delayed info      : Processing " << ntaggableEntries <<" entries..." << std::endl;
  std::cout << "[### analysis1Rmu ###]  NTag output       : Processing " << ntagEntries      <<" entries..." << std::endl;


  //=========  TTree event variables  ============
  float NTrueN = 0.;
  float vecvx  = 0.;
  float vecvy  = 0.;
  float vecvz  = 0.;
  tchev->SetBranchAddress("NTrueN", &NTrueN);
  tchev->SetBranchAddress("vecvx", &vecvx);
  tchev->SetBranchAddress("vecvy", &vecvy);
  tchev->SetBranchAddress("vecvz", &vecvz);
  //=========  TTree taggable variables  ============
  std::vector<int> *Type = 0;
  TBranch *bType = 0;
  std::vector<float> *E = 0;
  TBranch *bE = 0;
  std::vector<float> *t = 0;
  TBranch *bt = 0;
  tchtaggable->SetBranchAddress("Type", &Type, &bType);
  tchtaggable->SetBranchAddress("E", &E, &bE);
  tchtaggable->SetBranchAddress("t", &t, &bt);
  //=========  TTree partilce variables  ============
  std::vector<int> *PID = 0;
  TBranch *bPID = 0;
  std::vector<int> *ParentPID = 0;
  TBranch *bParentPID = 0;
  std::vector<int> *ParentIndex = 0; //avalable at NTag1.1.2
  TBranch *bParentIndex = 0;         //avalable at NTag1.1.2
  std::vector<int> *IntID = 0;
  TBranch *bIntID = 0;
  std::vector<float> *par_t = 0;
  TBranch *bpar_t = 0;
  std::vector<float> *par_x = 0;
  TBranch *bpar_x = 0;
  std::vector<float> *par_y = 0;
  TBranch *bpar_y = 0;
  std::vector<float> *par_z = 0;
  TBranch *bpar_z = 0;
  tchpar->SetBranchAddress("PID", &PID, &bPID);
  tchpar->SetBranchAddress("ParentPID", &ParentPID, &bParentPID);
  tchpar->SetBranchAddress("ParentIndex", &ParentIndex, &bParentIndex); //avalable at NTag1.1.2
  tchpar->SetBranchAddress("IntID", &IntID, &bIntID);
  tchpar->SetBranchAddress("t", par_t);
  tchpar->SetBranchAddress("t", &par_t, &bpar_t);
  tchpar->SetBranchAddress("x", &par_x, &bpar_x);
  tchpar->SetBranchAddress("y", &par_y, &bpar_y);
  tchpar->SetBranchAddress("z", &par_z, &bpar_z);
  //=========  TTree ntag variables  ============
  std::vector<float> *Label = 0;
  TBranch *bLabel = 0;
  std::vector<float> *TagClass = 0;
  TBranch *bTagClass = 0;
  std::vector<float> *FitT = 0;
  TBranch *bFitT = 0;
  std::vector<float> *TagIndex = 0;
  TBranch *bTagIndex = 0;
  std::vector<float> *NHits = 0;
  TBranch *bNHits = 0;
  std::vector<float> *N200 = 0;
  TBranch *bN200 = 0;
  std::vector<float> *TRMS = 0;
  TBranch *bTRMS = 0;
  std::vector<float> *DWall = 0;
  TBranch *bDWall = 0;
  std::vector<float> *DWallMeanDir = 0;
  TBranch *bDWallMeanDir = 0;
  std::vector<float> *OpeningAngleMean = 0;
  TBranch *bOpeningAngleMean = 0;
  std::vector<float> *OpeningAngleSkew = 0;
  TBranch *bOpeningAngleSkew = 0;
  std::vector<float> *OpeningAngleStdev = 0;
  TBranch *bOpeningAngleStdev = 0;
  std::vector<float> *MeanDirAngleMean = 0;
  TBranch *bMeanDirAngleMean = 0;
  std::vector<float> *MeanDirAngleRMS = 0;
  TBranch *bMeanDirAngleRMS = 0;
  std::vector<float> *Beta1 = 0;
  TBranch *bBeta1 = 0;
  std::vector<float> *Beta5 = 0;
  TBranch *bBeta5 = 0;
  std::vector<float> *TagOut = 0;
  TBranch *bTagOut = 0;
  tchntag->SetBranchAddress("Label", &Label, &bLabel);
  tchntag->SetBranchAddress("TagClass", &TagClass, &bTagClass);
  tchntag->SetBranchAddress("FitT", &FitT, &bFitT);
  tchntag->SetBranchAddress("TagIndex", &TagIndex, &bTagIndex);
  tchntag->SetBranchAddress("NHits", &NHits, &bNHits);
  tchntag->SetBranchAddress("N200", &N200, &bN200);
  tchntag->SetBranchAddress("TRMS", &TRMS, &bTRMS);
  tchntag->SetBranchAddress("DWall", &DWall, &bDWall);
  tchntag->SetBranchAddress("DWallMeanDir", &DWallMeanDir, &bDWallMeanDir);
  tchntag->SetBranchAddress("OpeningAngleMean", &OpeningAngleMean, &bOpeningAngleMean);
  tchntag->SetBranchAddress("OpeningAngleSkew", &OpeningAngleSkew, &bOpeningAngleSkew);
  tchntag->SetBranchAddress("OpeningAngleStdev", &OpeningAngleStdev, &bOpeningAngleStdev);
  tchntag->SetBranchAddress("MeanDirAngleMean", &MeanDirAngleMean, &bMeanDirAngleMean);
  tchntag->SetBranchAddress("MeanDirAngleRMS", &MeanDirAngleRMS, &bMeanDirAngleRMS);
  tchntag->SetBranchAddress("Beta1", &Beta1, &bBeta1);
  tchntag->SetBranchAddress("Beta5", &Beta5, &bBeta5);
  tchntag->SetBranchAddress("TagOut", &TagOut, &bTagOut);

  
  CC0PiNumu *numu=new CC0PiNumu(eMode, eOsc); 
  numu->resisterDefaultAllStacks();
  numu->seth1Tree(tchfQ);
  
  //=========  TTree h1 variables  ============
  //===== It should be called after numu ======
  Int_t   Npvc;             //Number of primary particles
  Int_t   Ipvc[100];        //PID of primary particles
  Float_t Pvc[100][3];      //Momentum of primary particles
  Int_t   Iflvc[100];       //Flag of final states
  Int_t   Ichvc[100];       //Chase at detector simulation or not(1: chase/0: not chase)
  Int_t   nscndprt;         //Number of secondary particles
  Int_t   iprtscnd[1000];   //PID of the secondary particle
  Float_t tscnd[1000];      //Generated time of secondary particles
  Int_t   iprntprt[1000];   //PID of the parent of this secondary particle
  Int_t   lmecscnd[1000];   //Interaction code of secondary particles based on GEANT
  Float_t pscnd[1000][3];   //Momentum of the secondary particle
  tchfQ -> SetBranchAddress("Npvc", &Npvc);
  tchfQ -> SetBranchAddress("Pvc", Pvc);
  tchfQ -> SetBranchAddress("Ipvc", Ipvc);
  tchfQ -> SetBranchAddress("Ichvc", Ichvc);
  tchfQ -> SetBranchAddress("Iflvc", Iflvc);
  tchfQ -> SetBranchAddress("nscndprt", &nscndprt);
  tchfQ -> SetBranchAddress("iprtscnd", iprtscnd);
  tchfQ -> SetBranchAddress("tscnd", tscnd);
  tchfQ -> SetBranchAddress("iprntprt", iprntprt);
  tchfQ -> SetBranchAddress("lmecscnd", lmecscnd);
  tchfQ -> SetBranchAddress("pscnd", pscnd);

  ResetNeutrinoEvents();

  //Histograms
  DecayeBox decayebox;
  decayebox.SetHistoFrame();

  Gd1RmuonSelection prmsel;
  prmsel.SetHistoFrame();
  prmsel.SetHistoFormat();

  NNInputVariables nninputs;
  nninputs.SetNNinputHisto();

  DistanceViewer ndistance;
  ndistance.SetHistoFrame();
  ndistance.SetHistoFormat();


  //Total event number of muon
  int NumberMu = 0;

  //Number of neutrons from mu-
  int NumberMuN = 0;

  //Number of neutrons from neutrino
  int NumberNuN = 0;

  int expNumberNuN = 0;

  int NumberGdn = 0;


  //Process
  CLTOptionSummary(ETAGKeyword, ETAG, MCTypeKeyword, MCType);

  for (int ientry=0; ientry<ntagEntries; ientry++) {

  	//Progress meter
    if(ientry>100 && ientry%100==0) std::cout << "[### analysis1Rmu ###]  Progress: " << 100.*ientry/ntagEntries << "%" << std::endl;

    tchfQ       -> GetEntry(ientry);
    tchev       -> GetEntry(ientry);
    tchpar      -> GetEntry(ientry);
    tchtaggable -> GetEntry(ientry);
    tchntag     -> GetEntry(ientry);

    Long64_t tentry = tchntag->LoadTree(ientry);
    bPID        -> GetEntry(tentry);
    bParentPID  -> GetEntry(tentry);
    bParentIndex -> GetEntry(tentry);  //avalable at NTag1.1.2
    bIntID      -> GetEntry(tentry);
    bpar_t      -> GetEntry(tentry);
    bpar_x      -> GetEntry(tentry);
    bpar_y      -> GetEntry(tentry);
    bpar_z      -> GetEntry(tentry);
    bType       -> GetEntry(tentry);
    bE          -> GetEntry(tentry);
    bLabel      -> GetEntry(tentry);
    bTagClass   -> GetEntry(tentry);
    bFitT       -> GetEntry(tentry);
    bNHits             -> GetEntry(tentry);
    bN200              -> GetEntry(tentry);
    bTRMS              -> GetEntry(tentry);
    bDWall             -> GetEntry(tentry);
    bDWallMeanDir      -> GetEntry(tentry);
    bOpeningAngleMean  -> GetEntry(tentry);
    bOpeningAngleSkew  -> GetEntry(tentry);
    bOpeningAngleStdev -> GetEntry(tentry);
    bMeanDirAngleMean  -> GetEntry(tentry);
    bMeanDirAngleRMS   -> GetEntry(tentry);
    bBeta1             -> GetEntry(tentry);
    bBeta5             -> GetEntry(tentry);
    bTagIndex   -> GetEntry(tentry);
    bTagOut     -> GetEntry(tentry);


    numu->computeCC0PiVariables();
    numu->applyfQ1RCC0PiNumuCut();
    const EvSelVar_t evsel = numu->getEvSelVar();


    //New 1R muon selection
    if (prmsel.Apply1RmuonSelection(evsel, numu, decayebox, eMode, eOsc, 20., 50., 400., true)) {
      GetSelectedModeEvents(numu);

      //truth secondary loop
      /*for (Int_t itruth=0; itruth<nscndprt; itruth++) {
    
        //Gamma from mu- (not mu+!)
        if (iprntprt[itruth]==13 && std::abs(iprtscnd[itruth])==22) {
        //if (std::abs(iprntprt[itruth])==13 && std::abs(iprtscnd[itruth])==22) {
          h1_tscnd_capture -> Fill(tscnd[itruth]/1000.);

          float gammaenergy = std::sqrt( pscnd[itruth][0]*pscnd[itruth][0] + pscnd[itruth][1]*pscnd[itruth][1] + pscnd[itruth][2]*pscnd[itruth][2] );
          h1_energy_capture -> Fill(gammaenergy);
        }
      }*/


      int reco = 0;
      float reco_mucaptime = 0.;
      for (UInt_t jentry=0; jentry<Label->size(); ++jentry) {

        float NNVar = 0.;
        for (int ivar=0; ivar<NNVARIABLES; ivar++) {
          switch (ivar) {
            case 0:
              NNVar = NHits->at(jentry);
              break;
            case 1:
              NNVar = N200->at(jentry);
              break;
            case 2:
              NNVar = TRMS->at(jentry);
              break;
            case 3:
              NNVar = DWall->at(jentry);
              break;
            case 4:
              NNVar = DWallMeanDir->at(jentry);
              break;
            case 5:
              NNVar = OpeningAngleMean->at(jentry);
              break;
            case 6:
              NNVar = OpeningAngleStdev->at(jentry);
              break;
            case 7:
              NNVar = OpeningAngleSkew->at(jentry);
              break;
            case 8:
              NNVar = MeanDirAngleMean->at(jentry);
              break;
            case 9:
              NNVar = MeanDirAngleRMS->at(jentry);
              break;
            case 10:
              NNVar = Beta1->at(jentry);
              break;
            case 11:
              NNVar = Beta5->at(jentry);
              break;
            default:
              NNVar = 0.;
              break;  
          }

          //Pre-NN
#if 1
          if (Label->at(jentry)==0) h1_NNvar_AccNoise[ivar] -> Fill(NNVar);
          if (Label->at(jentry)==1) h1_NNvar_Decaye[ivar]   -> Fill(NNVar);
          if (Label->at(jentry)==2) h1_NNvar_H[ivar]        -> Fill(NNVar);
          if (Label->at(jentry)==3) h1_NNvar_Gd[ivar]       -> Fill(NNVar);
#endif

          //Post-NN
#if 0
          if (Label->at(jentry)==0 && TagOut->at(jentry) > NLIKETHRESHOLD) h1_NNvar_AccNoise[ivar] -> Fill(NNVar);
          if (Label->at(jentry)==1 && TagOut->at(jentry) > NLIKETHRESHOLD) h1_NNvar_Decaye[ivar]   -> Fill(NNVar);
          if (Label->at(jentry)==2 && TagOut->at(jentry) > NLIKETHRESHOLD) h1_NNvar_H[ivar]        -> Fill(NNVar);
          if (Label->at(jentry)==3 && TagOut->at(jentry) > NLIKETHRESHOLD) h1_NNvar_Gd[ivar]       -> Fill(NNVar);
#endif
        }

        //TMVA output
        if (Label->at(jentry)==0) h1_NTagOut[0] -> Fill(TagOut->at(jentry));
        if (Label->at(jentry)==1) h1_NTagOut[1] -> Fill(TagOut->at(jentry));
        if (Label->at(jentry)==2) h1_NTagOut[2] -> Fill(TagOut->at(jentry));
        if (Label->at(jentry)==3) h1_NTagOut[3] -> Fill(TagOut->at(jentry));


        //Excess of NHits for numu MC
        if (Label->at(jentry)==0 && (NHits->at(jentry) > 30 && NHits->at(jentry) < 80)) {
          h1_FitT_NHitsExcess -> Fill(FitT->at(jentry));
          reco++;
          reco_mucaptime = FitT->at(jentry);
          //NHitsExcess = true;
        }
      }


      //NHits excess check
      int truth = 0;
      float truth_mucaptime = 0.;
      //Truth particles loop
      //std::cout << "Npvc(" << Npvc << ") + nscndprt(" << nscndprt << "): " << Npvc+nscndprt << std::endl;
      for (UInt_t jentry=0; jentry<PID->size(); ++jentry) {
        //std::cout << "[" << jentry+1 << "] PID: " << PID->at(jentry) << " --- ParentPID: " << ParentPID->at(jentry) << std::endl;

        //Truth gamma from muon
        if (PID->at(jentry)==22 && ParentPID->at(jentry)==13) {
          //std::cout << "[" << jentry+1 << "] PID: " << PID->at(jentry) << " --- ParentPID: " 
          //                                          << ParentPID->at(jentry) << " IntID:" 
          //                                          << IntID->at(jentry) << std::endl;
          h1_IntID -> Fill(IntID->at(jentry));

          //mu- capture
          if (IntID->at(jentry)==5) {
            truth++;
            truth_mucaptime = par_t->at(jentry);
            //std::cout << par_t[jentry] << std::endl;
          }
        }
      }

      //matching with the excess event and the truth
      if (reco==1 && reco==truth) h1_timediff -> Fill(truth_mucaptime - reco_mucaptime);
      //if (reco==1 && reco==truth) h1_timediff -> Fill(truth_mucaptime);



      //Get gamma from mu- capture and make lists of neutrons from mu- capture and neutrino interactions
      std::vector<int> MuNeutronList;
      std::vector<int> NuNeutronList;
      for (UInt_t jentry=0; jentry<PID->size(); ++jentry) {

        float d_x = std::fabs(par_x->at(jentry) - vecvx);
        float d_y = std::fabs(par_y->at(jentry) - vecvy);
        float d_z = std::fabs(par_z->at(jentry) - vecvz);
        float d   = std::sqrt(d_x*d_x + d_y*d_y + d_z*d_z);

        //Fill creation vertex of all gamma-primary vertex
        /*if (PID->at(jentry)==22) {
          h1_truedistance_particle -> Fill(d/100.);
        }*/

        //Total number of muon
        if (PID->at(jentry)==13) NumberMu++;

        //Number of neutrons from muon
        if (PID->at(jentry)==2112 && ParentPID->at(jentry)==13 && IntID->at(jentry)==5) NumberMuN++; 

        //Number of neutrons from neutrino interaction
        if (PID->at(jentry)==2112 && ParentPID->at(jentry)==0) NumberNuN++;
        //if (!(IntID->at(jentry)==5 && ParentPID->at(jentry)==13) && PID->at(jentry)==2112 && ParentPID->at(jentry)==0) NumberNuN++;

        if (PID->at(jentry)==22 && ParentPID->at(jentry)==22) NumberGdn++;

        std::cout << "[### " << ientry << " ###] Particle[" << jentry << "]=" << PID->at(jentry) 
                                       << ", ParentPID=" << ParentPID->at(jentry) 
                                       << ", ParentIndex=" << ParentIndex->at(jentry) << std::endl;

        //Products from mu- capture (either n or gamma)
        if (IntID->at(jentry)==5 && ParentPID->at(jentry)==13) {
          //h1_truedistance_mu -> Fill(d/100.);
          if (PID->at(jentry)==22) h1_truedistance_mu_gamma -> Fill(d/100.);

          if (PID->at(jentry)==2112) {
            std::cout << "----------------> MuNeutron[" << jentry << "] ParentPID: " << ParentPID->at(jentry) << std::endl;
            MuNeutronList.push_back(jentry);
          }
        }
        //Neutrons from neutrino interaction
        else {
          if (PID->at(jentry)==2112 && ParentPID->at(jentry)==0) {
            std::cout << "----------------> NuNeutron[" << jentry << "] ParentPID: " << ParentPID->at(jentry) << std::endl;
            NuNeutronList.push_back(jentry);
          }
        }
      }
      expNumberNuN += NuNeutronList.size();


      //Get gamma from neutron lists which are obtained the above loop
      /*
      int filled_mu_n = 0;
      int filled_nu_n = 0;
      for (UInt_t jentry=0; jentry<PID->size(); ++jentry) {

        float d_x = std::fabs(par_x->at(jentry) - vecvx);
        float d_y = std::fabs(par_y->at(jentry) - vecvy);
        float d_z = std::fabs(par_z->at(jentry) - vecvz);
        float d   = std::sqrt(d_x*d_x + d_y*d_y + d_z*d_z);

        //Get gamma from neutron captures
        if (PID->at(jentry)==22 && ParentPID->at(jentry)==2112) {

          //Find neutron captures (n from mu- capture)
          for (UInt_t imu=0; imu<MuNeutronList.size(); ++imu) {
            if (ParentIndex->at(jentry) == MuNeutronList.at(imu)) {
              std::cout << "[### " << jentry << " ###] ParentIndex: " << ParentIndex->at(jentry) << " --- MuNeutron[" << MuNeutronList.at(imu) << "] filled: " << filled_mu_n << std::endl;
              if (filled_mu_n==0) h1_truedistance_mu_n -> Fill(d/100.);
              filled_mu_n++;
            }
          }
          std::cout << "--------" << std::endl;

          //Find neutron captures (n from neutrino interaction)
          for (UInt_t inu=0; inu<NuNeutronList.size(); ++inu) {
            if (ParentIndex->at(jentry) == NuNeutronList.at(inu)) {
              std::cout << "[### " << jentry << " ###] ParentIndex: " << ParentIndex->at(jentry) << " --- NuNeutron[" << NuNeutronList.at(inu) << "] filled: " << filled_nu_n << std::endl;
              if (filled_nu_n==0) h1_truedistance_nu_n -> Fill(d/100.);
              filled_nu_n++;
            }
          }

        }
        
      }
      std::cout << " " << std::endl;
      */
     

      if (NuNeutronList.size()==0) {
        std::cout << " " << std::endl;
        //continue;
      }
      else {
        std::cout << "Start to find neutrons..." << std::endl;
        int done_nu_n = 0;
        while(NuNeutronList.size() - done_nu_n != 0) {
          for (UInt_t inu=0; inu<PID->size(); ++inu) {

            float d_x = std::fabs(par_x->at(inu) - vecvx);
            float d_y = std::fabs(par_y->at(inu) - vecvy);
            float d_z = std::fabs(par_z->at(inu) - vecvz);
            float d   = std::sqrt(d_x*d_x + d_y*d_y + d_z*d_z);

            if (PID->at(inu)==22 && 
                ParentPID->at(inu)==2112 && 
                ParentIndex->at(inu)==NuNeutronList[done_nu_n]) {
              std::cout << "[### " << ientry << " ###] FOUND:" << inu 
                        << " ParentIndex = " << ParentIndex->at(inu) 
                        << " --- NuNeutronList[" << done_nu_n << "] = " << NuNeutronList[done_nu_n] << std::endl;
              h1_truedistance_nu_n -> Fill(d/100.);
              break;
            }
            std::cout << "[### " << ientry << " ###] Searching neutrons from nu... List[" << done_nu_n << "]=" << NuNeutronList[done_nu_n] << " : Particle[" << inu << "]=" << ParentIndex->at(inu) << std::endl;
          }
          std::cout << "-------------------------------------------------------------------------------------" << std::endl;
          done_nu_n++;
        }
      }

      if (MuNeutronList.size()==0) {
        std::cout << " " << std::endl;
        //continue;
      }
      else {
        std::cout << "Start to find neutrons..." << std::endl;
        int done_mu_n = 0;
        while(MuNeutronList.size() - done_mu_n != 0) {
          for (UInt_t imu=0; imu<PID->size(); ++imu) {

            float d_x = std::fabs(par_x->at(imu) - vecvx);
            float d_y = std::fabs(par_y->at(imu) - vecvy);
            float d_z = std::fabs(par_z->at(imu) - vecvz);
            float d   = std::sqrt(d_x*d_x + d_y*d_y + d_z*d_z);

            if (PID->at(imu)==22 && 
                ParentPID->at(imu)==2112 && 
                ParentIndex->at(imu)==MuNeutronList[done_mu_n]) {
              std::cout << "[### " << ientry << " ###] FOUND:" << imu 
                        << " ParentIndex = " << ParentIndex->at(imu) 
                        << " --- MuNeutronList[" << done_mu_n << "] = " << MuNeutronList[done_mu_n] << std::endl;
              h1_truedistance_mu_n -> Fill(d/100.);
              break;
            }
            std::cout << "[### " << ientry << " ###] Searching neutrons from mu... List[" << done_mu_n << "]=" << MuNeutronList[done_mu_n] << " : Particle[" << imu << "]=" << ParentIndex->at(imu) << std::endl;
          }
          std::cout << "-------------------------------------------------------------------------------------" << std::endl;
          done_mu_n++;
        }
      }
      
      std::cout << " " << std::endl;

      //clean up
      MuNeutronList.clear();
      NuNeutronList.clear();

    } //1R mu selection

  } //Event loop


  std::cout << "Total number of muon events              : " << NumberMu << std::endl;
  std::cout << "Total number of neutrons from mu- capture: " << NumberMuN << std::endl;
  std::cout << "Number of Gd-n (mu- capture)             : " << h1_truedistance_mu_n->Integral() << std::endl;
  std::cout << "Total number of neutrons from neutrino   : " << NumberNuN << std::endl;
  std::cout << "Expected number of neutrons from neutrino: " << expNumberNuN << std::endl;
  std::cout << "Number of Gd-n (neutrino)                : " << h1_truedistance_nu_n->Integral() << std::endl;


  TFile* fout = new TFile(OutputRootName, "RECREATE");
  std::cout << "Output: " << OutputRootName << std::endl;
  fout -> cd();

  decayebox.cdDecayeBox(fout);
  decayebox.WritePlots();
  gDirectory -> cd("..");

  prmsel.cdGd1RmuonSelection(fout);
  prmsel.WritePlots();
  gDirectory -> cd("..");

  nninputs.cdNNInputVariables(fout);
  nninputs.WritePlots();

  ndistance.cdDistanceViewer(fout);
  ndistance.WritePlots();
  gDirectory -> cd("..");

}