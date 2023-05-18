#include "DistanceViewer.h"
#include "TGaxis.h"

void DistanceViewer::SetHistoFrame() {
  h1_truedistance = new TH1F("h1_truedistance", "Truth Distance From PV; Truth distance[m]; Entries", 10, 0, 5);
  ((TGaxis*)h1_truedistance->GetYaxis())->SetMaxDigits(4);

  h1_truedistance_CCQE    = new TH1F("h1_truedistance_CCQE", "", 10, 0, 5);
  h1_truedistance_CC2p2h  = new TH1F("h1_truedistance_CC2p2h", "", 10, 0, 5);
  h1_truedistance_CCOther = new TH1F("h1_truedistance_CCOther", "", 10, 0, 5);
  h1_truedistance_CCnonQE = new TH1F("h1_truedistance_CCnonQE", "", 10, 0, 5);
  h1_truedistance_NC      = new TH1F("h1_truedistance_NC", "", 10, 0, 5);

  h1_truedistance_nu_n      = new TH1F("h1_truedistance_nu_n", "Truth Distance From PV; Truth distance[m]; Number of Neutron Events", 50, 0, DistanceMax);
  h1_truedistance_mu_n      = new TH1F("h1_truedistance_mu_n", "Truth Distance From PV; Truth distance[m]; Number of Neutron Events", 50, 0, DistanceMax);
  h1_truedistance_prm_nu_n  = new TH1F("h1_truedistance_prm_nu_n", "Truth Distance From PV; Truth distance[m]; Number of Neutron Events", 50, 0, DistanceMax);
  h1_truedistance_prm_mu_n  = new TH1F("h1_truedistance_prm_mu_n", "Truth Distance From PV; Truth distance[m]; Number of Neutron Events", 50, 0, DistanceMax);
  h1_truedistance_nu_BefSIn = new TH1F("h1_truedistance_nu_BefSIn", "Truth Distance From PV; Truth distance[m]; Number of Neutron Events", 50, 0, DistanceMax);
  h1_truedistance_nu_SIn    = new TH1F("h1_truedistance_nu_SIn", "Truth Distance From PV; Truth distance[m]; Number of Neutron Events", 50, 0, DistanceMax);
  //h1_TruePrmMuEnd_x_TagNCap = new TH1F("h1_TruePrmMuEnd_x_TagNCap", "Neutron-related distance; Distance[m]; Number of Events", 50, 0, DistanceMax);

  h1_truedistance_mudecay = new TH1F("h1_truedistance_mudecay", "Truth distance of #mu decay; Distance[m]; Number of Events", 100, 0, DistanceMax);
  h1_truedistance_pidecay = new TH1F("h1_truedistance_pidecay", "Truth distance of #pi^{+} decay; Distance[m]; Number of Events", 100, 0, DistanceMax);
  for (int i=0; i<6; i++) {
    h1_TruePrmMuEnd_x_TagNCap[i] = new TH1F(TString::Format("h1_TruePrmMuEnd_x_TagNCap_mode%d", i), "Neutron-related distance; Distance[m]; Number of Events", 50, 0, DistanceMax);
    h1_RecoPrmMuEnd_x_TagNCap[i] = new TH1F(TString::Format("h1_RecoPrmMuEnd_x_TagNCap_mode%d", i), "Neutron-related distance; Distance[m]; Number of Events", 50, 0, 5);
    h1_Erec[i] = new TH1F(TString::Format("h1_Erec_mode%d", i), "Reco. #nu Energy; Reconstructed #nu Energy[GeV]; Number of Neutrino Events", 60, 0, 3);
  }
  h1_TruePrmMuEnd_x_TagNCap_MuN   = new TH1F("h1_TruePrmMuEnd_x_TagNCap_MuN", "Neutron-related distance; Distance[m]; Number of Events", 50, 0, DistanceMax);
  h1_TruePrmMuEnd_x_TagNCap_NuN   = new TH1F("h1_TruePrmMuEnd_x_TagNCap_NuN", "Neutron-related distance; Distance[m]; Number of Events", 50, 0, DistanceMax);
  h1_RecoPrmMuEnd_x_TagNCap_MuN   = new TH1F("h1_RecoPrmMuEnd_x_TagNCap_MuN", "Neutron-related distance; Distance[m]; Number of Events", 50, 0, 5);
  h1_RecoPrmMuEnd_x_TagNCap_NuN   = new TH1F("h1_RecoPrmMuEnd_x_TagNCap_NuN", "Neutron-related distance; Distance[m]; Number of Events", 50, 0, 5);
  h2_TruePrmMuEnd_x_TagNCap_x_Pmu = new TH2F("h2_TruePrmMuEnd_x_TagNCap_x_Pmu", "Neutron-related distance; Reconstructed Muon Momemtum[MeV]; Distance[m]", 30, 0, 3, 140, 0, 14);
  h2_TruePrmMuEnd_x_TagNCap_x_Pmu -> SetStats(0);
  h2_Prm_NCap_x_MuStp_x_NCap = new TH2F("h2_Prm_NCap_x_MuStp_x_NCap", "Neutron-related distance; Distance from Primary Vertex [m]; Distance from #mu Stopping Vertex [m]", 50, 0, 10, 50, 0, 10);
  h2_Prm_NCap_x_MuStp_x_NCap -> SetStats(0);
  h1_RecoMuTrack = new TH1F("h1_RecoMuTrack", "; Distance b/w Primary and #mu Stopping Vertices[m]; Number of Events", 50, 0, 10);
  h2_MuTrack_x_MuStp_x_NCap = new TH2F("h2_MuTrack_x_MuStp_x_NCap", "; #mu Stopping Range[m]; Distance from #mu Stopping Vertex[m]", 50, 0, 10, 50, 0, 10);
  h2_MuTrack_x_MuStp_x_NCap -> SetStats(0);
  h2_MuTrack_x_Prm_NCap = new TH2F("h2_MuTrack_x_Prm_NCap", "; #mu Stopping Range[m]; Distance from Primary Vertex[m]", 50, 0, 10, 50, 0, 10);
  h2_MuTrack_x_Prm_NCap -> SetStats(0);
  h2_Enu_x_MuTrack = new TH2F("h2_Enu_x_MuTrack", "; Reconstructed #nu Energy[GeV]; #mu Stopping Range[m]", 60, 0, 3, 50, 0, 10);
  h2_Enu_x_MuTrack -> SetStats(0);
  h2_Enu_x_Prm_NCap = new TH2F("h2_Enu_x_Prm_NCap", "; Reconstructed #nu Energy[GeV]; Distance from Primary Vertex[m]", 60, 0, 3, 50, 0, 10);
  h2_Enu_x_Prm_NCap -> SetStats(0);
  h2_Enu_x_MuStp_NCap = new TH2F("h2_Enu_x_MuStp_NCap", "; Reconstructed #nu Energy[GeV]; Distance from #mu Stopping Vertex[m]", 60, 0, 3, 50, 0, 10);
  h2_Enu_x_MuStp_NCap -> SetStats(0);


  for (int i=0; i<7; i++) {
    h1_TruePrmMuEnd_x_fQDcyE[i]  = new TH1F(TString::Format("h1_TruePrmMuEnd_x_fQDcyE_mode%d", i), "Decay-e-related distance; Distance[m]; Number of Events", 100, 0, DistanceMax);
  }
  h1_TruePrmMuEnd_x_fQDcyE_MuDcy = new TH1F("h1_TruePrmMuEnd_x_fQDcyE_MuDcy", "Decay-e-related distance; Distance[m]; Number of Events", 100, 0, DistanceMax);
  h1_TruePrmMuEnd_x_fQDcyE_PiDcy = new TH1F("h1_TruePrmMuEnd_x_fQDcyE_PiDcy", "Decay-e-related distance; Distance[m]; Number of Events", 100, 0, DistanceMax);
  h2_TruePrmMuEnd_x_fQDcyE_x_Pmu = new TH2F("h2_TruePrmMuEnd_x_fQDcyE_x_Pmu", "Decay-e-related distance; Reconstructed Muon Momemtum[GeV]; Distance[m]", 30, 0, 3, 140, 0, 14);
  //h2_TruePrmMuEnd_x_fQDcyE_x_Pmu = new TH2F("h2_TruePrmMuEnd_x_fQDcyE_x_Pmu", "Decay-e-related distance; Reconstructed Muon Momemtum[GeV]; Distance[m]", 30, 0, 3, 120, 0, 6);
  //h2_TruePrmMuEnd_x_fQDcyE_x_Pmu = new TH2F("h2_TruePrmMuEnd_x_fQDcyE_x_Pmu", "Decay-e-related distance; Reconstructed Muon Momemtum[GeV]; Distance[m]", 20, 0, 0.1, 120, 0, 6);
  h2_TruePrmMuEnd_x_fQDcyE_x_Pmu -> SetStats(0);
  h2_TruePrmMuEnd_x_fQDcyE_x_Enu = new TH2F("h2_TruePrmMuEnd_x_fQDcyE_x_Enu", "Decay-e-related distance; Reconstructed Neutrino Energy[GeV]; Distance[m]", 60, 0, 3, 140, 0, 14);
  h2_TruePrmMuEnd_x_fQDcyE_x_Enu -> SetStats(0);
  

  h2_TruePmu_x_TrueRange = new TH2F("h2_TruePmu_x_TrueRange", "h2_TruePmu_x_TrueRange; Truth #mu momentum[MeV]; Truth range[m]", 1000, 0, 1000, 200, 0, 5);
  h2_TruePmu_x_TrueRange -> SetStats(0);
  h2_RecoPmu_x_RecoRange = new TH2F("h2_RecoPmu_x_RecoRange", "h2_RecoPmu_x_RecoRange; Reconstructed #mu momentum[MeV]; Reconstructed range[m]", 1000, 0, 1000, 200, 0, 5);
  h2_RecoPmu_x_RecoRange -> SetStats(0);

  h1_Candidatetruedistance = new TH1F("h1_Candidatetruedistance", "Truth Distance From PV; Truth distance[m]; Entries", 10, 0, 5);
  ((TGaxis*)h1_Candidatetruedistance->GetYaxis())->SetMaxDigits(4);

  for (int i=0; i<CUTSTEP; i++) {
    h1_Tagtruedistance[i] = new TH1F(TString::Format("h1_Tagtruedistance_thr%d", i), "Truth Distance of Tagged Truth Neutrons; Truth distance[m]; Entries", 10, 0, 5);
    ((TGaxis*)h1_Tagtruedistance[i]->GetYaxis())->SetMaxDigits(4);

    h1_NNEff_dist[i]      = new TH1F(TString::Format("h1_NNEff_dist_thr%d", i), "", 10, 0, 5);
    h1_OverallEff_dist[i] = new TH1F(TString::Format("h1_OverallEff_dist_thr%d", i), "", 10, 0, 5);
  }
  h1_PreEff_dist = new TH1F("h1_PreEff_dist", "", 10, 0, 5); 
}

void DistanceViewer::SetHistoFormat() {
  h1_truedistance -> SetLineWidth(2);
  h1_truedistance -> SetLineColor(kAzure-4);
  h1_truedistance -> SetTitleOffset(1.4, "Y");
  h1_truedistance -> SetTitleSize(0.035, "Y");
  h1_truedistance -> SetLabelSize(0.033, "Y");

  h1_truedistance_CCQE -> SetLineWidth(2);
  h1_truedistance_CCQE -> SetLineColor(kAzure-1);
  h1_truedistance_CCQE -> SetFillColor(kAzure-1);
  h1_truedistance_CCQE -> SetTitleOffset(1.4, "Y");
  h1_truedistance_CCQE -> SetTitleSize(0.035, "Y");
  h1_truedistance_CCQE -> SetLabelSize(0.033, "Y");

  h1_truedistance_CC2p2h -> SetLineWidth(2);
  h1_truedistance_CC2p2h -> SetLineColor(kAzure-5);
  h1_truedistance_CC2p2h -> SetFillColor(kAzure-5);
  h1_truedistance_CC2p2h -> SetTitleOffset(1.4, "Y");
  h1_truedistance_CC2p2h -> SetTitleSize(0.035, "Y");
  h1_truedistance_CC2p2h -> SetLabelSize(0.033, "Y");

  h1_truedistance_CCOther -> SetLineWidth(2);
  h1_truedistance_CCOther -> SetLineColor(kCyan-6);
  h1_truedistance_CCOther -> SetFillColor(kCyan-6);
  h1_truedistance_CCOther -> SetTitleOffset(1.4, "Y");
  h1_truedistance_CCOther -> SetTitleSize(0.035, "Y");
  h1_truedistance_CCOther -> SetLabelSize(0.033, "Y");

  h1_truedistance_CCnonQE -> SetLineWidth(2);
  h1_truedistance_CCnonQE -> SetLineColor(kCyan-8);
  h1_truedistance_CCnonQE -> SetFillColor(kCyan-8);
  h1_truedistance_CCnonQE -> SetTitleOffset(1.4, "Y");
  h1_truedistance_CCnonQE -> SetTitleSize(0.035, "Y");
  h1_truedistance_CCnonQE -> SetLabelSize(0.033, "Y");

  h1_truedistance_NC -> SetLineWidth(2);
  h1_truedistance_NC -> SetLineColor(kTeal+9);
  h1_truedistance_NC -> SetFillColor(kTeal+9);
  h1_truedistance_NC -> SetTitleOffset(1.4, "Y");
  h1_truedistance_NC -> SetTitleSize(0.035, "Y");
  h1_truedistance_NC -> SetLabelSize(0.033, "Y");


  h1_truedistance_nu_n -> SetLineWidth(2);
  h1_truedistance_nu_n -> SetLineColor(kRed-8);
  h1_truedistance_nu_n -> SetTitleOffset(1.4, "Y");
  h1_truedistance_nu_n -> SetTitleSize(0.035, "Y");
  h1_truedistance_nu_n -> SetLabelSize(0.033, "Y");

  h1_truedistance_mu_n -> SetLineWidth(2);
  h1_truedistance_mu_n -> SetLineColor(kCyan-5);
  h1_truedistance_mu_n -> SetTitleOffset(1.4, "Y");
  h1_truedistance_mu_n -> SetTitleSize(0.035, "Y");
  h1_truedistance_mu_n -> SetLabelSize(0.033, "Y");

  for (int i=0; i<CUTSTEP; i++) {
    h1_NNEff_dist[i] -> SetLineWidth(2);
    h1_NNEff_dist[i] -> SetLineColor(kAzure-4);
    h1_NNEff_dist[i] -> SetStats(0);
    h1_NNEff_dist[i] -> SetTitleOffset(1.4, "Y");
    h1_NNEff_dist[i] -> SetTitleSize(0.035, "Y");
    h1_NNEff_dist[i] -> SetLabelSize(0.033, "Y");

    h1_OverallEff_dist[i] -> SetLineWidth(2);
    h1_OverallEff_dist[i] -> SetLineColor(kAzure-4);
    h1_OverallEff_dist[i] -> SetStats(0);
    h1_OverallEff_dist[i] -> SetTitleOffset(1.4, "Y");
    h1_OverallEff_dist[i] -> SetTitleSize(0.035, "Y");
    h1_OverallEff_dist[i] -> SetLabelSize(0.033, "Y");
  }
}


float DistanceViewer::TakeDistance(float *Vtx1, float *Vtx2) {
  //std::cout << "Vtx1 = [" << Vtx1[0] << ", " << Vtx1[1] << ", " << Vtx1[2] << "]" << std::endl;
  //std::cout << "Vtx2 = [" << Vtx2[0] << ", " << Vtx2[1] << ", " << Vtx2[2] << "]" << std::endl;
  float d_x = Vtx1[0] - Vtx2[0];
  float d_y = Vtx1[1] - Vtx2[1];
  float d_z = Vtx1[2] - Vtx2[2];
  float d   = std::sqrt( d_x*d_x + d_y*d_y + d_z*d_z ); 
  //std::cout << "Distance: " << d << std::endl;
  return d;
}

float DistanceViewer::TakeTransversalDistance(float *Dir, float *Vtx1, float *Vtx2) {
  float d_x = Vtx1[0] - Vtx2[0];
  float d_y = Vtx1[1] - Vtx2[1];
  float d_z = Vtx1[2] - Vtx2[2];
  float d   = std::sqrt( d_x*d_x + d_y*d_y + d_z*d_z );
  //std::cout << " norm: " << std::sqrt( Dir[0]*Dir[0] + Dir[1]*Dir[1] + Dir[2]*Dir[2] ) << std::endl;
  float InnerProd = d_x*Dir[0] + d_y*Dir[1] + d_z*Dir[2];
  float dT = d * std::sin( std::acos( InnerProd / d ) );
  return dT;
}


//Truth distance
float DistanceViewer::GetTruthDistance(CC0PiNumu *numu,
                                       float capturevtxx,
    	                                 float capturevtxy,
    	                                 float capturevtxz,
    	                                 float primaryvtxx,
                                       float primaryvtxy,
    	                                 float primaryvtxz) 
{
  int mode = TMath::Abs(numu->var<int>("mode"));
  float d_x = std::fabs(capturevtxx - primaryvtxx);
  float d_y = std::fabs(capturevtxy - primaryvtxy);
  float d_z = std::fabs(capturevtxz - primaryvtxz);
  float d   = std::sqrt(d_x*d_x + d_y*d_y + d_z*d_z);
  h1_truedistance -> Fill(d/100.);

  if (mode==1)             h1_truedistance_CCQE    -> Fill(d/100.);
  //if ((mode>=2 && mode<=10) || (mode>=14 && mode<=30))
  if (mode>=2 && mode<=30) h1_truedistance_CCnonQE -> Fill(d/100.);
  if (mode>=2 && mode<=10) h1_truedistance_CC2p2h  -> Fill(d/100.);
  if (mode>10 && mode<=30) h1_truedistance_CCOther -> Fill(d/100.);
  if (mode>=31)            h1_truedistance_NC      -> Fill(d/100.);
  //if (mode==13)        h1_truedistance_CCRESdeltap  -> Fill(d/100.);
  //if (mode==11)        h1_truedistance_CCRESdeltapp -> Fill(d/100.);
  //if (mode==12)        h1_truedistance_CCRESdelta0  -> Fill(d/100.);
  return d;
}



//Pre-selection efficiency as a function of the distance
void DistanceViewer::GetPreEffDistance(int tagindex,
                                       UInt_t matchtrue,
                                       float capturevtxx,
                                       float capturevtxy,
                                       float capturevtxz,
                                       float primaryvtxx,
                                       float primaryvtxy,
                                       float primaryvtxz) 
{
  //Find matchtrue match with tagindex
  if (tagindex!=-1 && matchtrue==(UInt_t)tagindex) {
    float d_x = std::fabs(capturevtxx - primaryvtxx);
    float d_y = std::fabs(capturevtxy - primaryvtxy);
    float d_z = std::fabs(capturevtxz - primaryvtxz);
    float d   = std::sqrt(d_x*d_x + d_y*d_y + d_z*d_z);
    h1_Candidatetruedistance -> Fill(d/100.);

    h1_PreEff_dist -> Fill(d/100.);
  }
}

//NN and overall tagging efficiencies as a function of the distance
void DistanceViewer::GetOverallEffDistance(int ith,
                                           int tagindex,
                                           UInt_t matchtrue,
                                           float capturevtxx,
                                           float capturevtxy,
                                           float capturevtxz,
                                           float primaryvtxx,
                                           float primaryvtxy,
                                           float primaryvtxz)
{

  //Find kentry match with jentry
  if (tagindex!=-1 && matchtrue==(UInt_t)tagindex) {
    float d_x = std::fabs(capturevtxx - primaryvtxx);
    float d_y = std::fabs(capturevtxy - primaryvtxy);
    float d_z = std::fabs(capturevtxz - primaryvtxz);
    float d   = std::sqrt(d_x*d_x + d_y*d_y + d_z*d_z);

    h1_Tagtruedistance[ith] -> Fill(d/100.);

    h1_OverallEff_dist[ith] -> Fill(d/100.);
    h1_NNEff_dist[ith]      -> Fill(d/100.);
  }

}


void DistanceViewer::cdDistanceViewer(TFile* fout) {
  fout -> mkdir("DistanceViewer");
  fout -> cd("DistanceViewer");
}

void DistanceViewer::WritePlots() {
  h1_truedistance         -> Write();
  h1_truedistance_CCQE    -> Write();
  h1_truedistance_CC2p2h  -> Write();
  h1_truedistance_CCOther -> Write();
  h1_truedistance_CCnonQE -> Write();
  h1_truedistance_NC      -> Write();

  h1_truedistance_mudecay   -> Write();
  h1_truedistance_pidecay   -> Write();
  h1_truedistance_nu_n      -> Write();
  h1_truedistance_mu_n      -> Write();
  h1_truedistance_prm_nu_n  -> Write();
  h1_truedistance_prm_mu_n  -> Write();
  h1_truedistance_nu_BefSIn -> Write();
  h1_truedistance_nu_SIn    -> Write();

  for (int i=0; i<6; i++) {
    h1_TruePrmMuEnd_x_TagNCap[i] -> Write();
    h1_RecoPrmMuEnd_x_TagNCap[i] -> Write();
    h1_Erec[i] -> Write();
  }
  h1_TruePrmMuEnd_x_TagNCap_MuN -> Write();
  h1_TruePrmMuEnd_x_TagNCap_NuN -> Write();
  h1_RecoPrmMuEnd_x_TagNCap_MuN -> Write();
  h1_RecoPrmMuEnd_x_TagNCap_NuN -> Write();

  for (int i=0; i<7; i++) {
    h1_TruePrmMuEnd_x_fQDcyE[i]  -> Write();
  }
  h1_TruePrmMuEnd_x_fQDcyE_MuDcy -> Write();
  h1_TruePrmMuEnd_x_fQDcyE_PiDcy -> Write();
  h2_TruePmu_x_TrueRange -> Write();
  h2_RecoPmu_x_RecoRange -> Write();
  h2_TruePrmMuEnd_x_fQDcyE_x_Enu  -> Write();
  h2_TruePrmMuEnd_x_fQDcyE_x_Pmu  -> Write();
  h2_TruePrmMuEnd_x_TagNCap_x_Pmu -> Write();
  h2_Prm_NCap_x_MuStp_x_NCap -> Write();
  h1_RecoMuTrack -> Write();
  h2_MuTrack_x_Prm_NCap -> Write();
  h2_MuTrack_x_MuStp_x_NCap -> Write();
  h2_Enu_x_MuTrack -> Write();
  h2_Enu_x_Prm_NCap -> Write();
  h2_Enu_x_MuStp_NCap -> Write();

  h1_PreEff_dist -> Sumw2();
  h1_PreEff_dist -> Divide(h1_truedistance);
  h1_PreEff_dist -> Write();
  for (int i=0; i<CUTSTEP; i++) {
    h1_Tagtruedistance[i] -> Write();

    h1_NNEff_dist[i] -> Sumw2();
    h1_NNEff_dist[i] -> Divide(h1_Candidatetruedistance);
    h1_NNEff_dist[i] -> Write();

    h1_OverallEff_dist[i] -> Sumw2();
    h1_OverallEff_dist[i] -> Divide(h1_truedistance);
    h1_OverallEff_dist[i] -> Write();
  }
}

