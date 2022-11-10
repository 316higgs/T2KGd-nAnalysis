#include "../include/NeutrinoEvents.h"
#include "DecayeBox.h"
#include "TGaxis.h"

void DecayeBox::SetHistoFrame() {
  h1_TaggedDecaye = new TH1F("h1_TaggedDecaye", "h1_TaggedDecaye; Number of Tagged Decay-e; Number of Neutrino Events", 6, 0, 6);
  h1_TaggedDecaye_CCQE = new TH1F("h1_TaggedDecaye_CCQE", "h1_TaggedDecaye@CCQE; Number of Tagged Decay-e; Number of Neutrino Events", 6, 0, 6);
  h1_TaggedDecaye_CCpi = new TH1F("h1_TaggedDecaye_CCpi", "h1_TaggedDecaye@CCPi; Number of Tagged Decay-e; Number of Neutrino Events", 6, 0, 6);
  h1_mintimediff       = new TH1F("h1_mintimediff", "h1_mintimediff; dt-tscnd[#musec]; Number of Events", 100, 0.8, 1.2);
  h1_pscnd             = new TH1F("h1_pscnd", "h1_pscnd; pscnd[MeV]; Number of Events", 80, -80, 80);
  h1_iprtscnd          = new TH1F("h1_iprtscnd", "h1_iprtscnd; iprtscnd; Number of Events", 2490, 10, 2500);

  h2_reso_x_pscnd = new TH2F("h2_reso_x_pscnd", "h2_reso_x_pscnd; dt - tscnd[#musec]; pscnd[MeV]", 100, 0.8, 1.2, 40, 0, 80);
  h2_reso_x_pscnd -> SetStats(0);
  h2_reso_x_iprtscnd = new TH2F("h2_reso_x_iprtscnd", "h2_reso_x_iprtscnd; dt[#musec]; iprtscnd", 50, 0., 5., 2490, 10, 2500);
  h2_reso_x_iprtscnd -> SetStats(0);
  h2_reso_x_lmecscnd = new TH2F("h2_reso_x_lmecscnd", "h2_reso_x_lmecscnd; dt[#musec]; lmecscnd", 50, 0., 5., 25, 5, 30);
  h2_reso_x_lmecscnd -> SetStats(0);
  h2_iprtscnd_lmecscnd = new TH2F("h2_iprtscnd_lmecscnd", "h2_iprtscnd_lmecscnd; iprtscnd; lmecscnd", 2490, 10, 2500, 25, 5, 30);
  h2_iprtscnd_lmecscnd -> SetStats(0);

  h2_dtn50 = new TH2D("h2_dtn50", "dt vs N50; dt[#musec]; N50", 100, 0, 50, 40, 0, 400);
  h2_dtn50 -> SetTitleOffset(1.3, "Y");
  h2_dtn50 -> SetTitleSize(0.035, "Y");
  h2_dtn50 -> SetLabelSize(0.035, "Y");
  h2_dtn50 -> SetTitleSize(0.035, "X");
  h2_dtn50 -> SetLabelSize(0.035, "X");
  h2_dtn50 -> SetStats(0);
  ((TGaxis*)h2_dtn50->GetXaxis())->SetMaxDigits(3);
}

void DecayeBox::SetHistoFormat() {
  h1_TaggedDecaye      -> SetLineWidth(2);
  h1_TaggedDecaye_CCQE -> SetLineWidth(2);
  h1_TaggedDecaye_CCpi -> SetLineWidth(2);
}


int DecayeBox::GetDecayeInBox(CC0PiNumu* numu, 
	                            BeamMode::E_BEAM_MODE eMode, 
	                            OscChan::E_OSC_CHAN eOsc,
	                            float dtCut,
	                            float N50CutMin,
	                            float N50CutMax,
                              bool histofill) 
{
  int Decaye = 0;
  const int nse = numu->var<int>("fqnse");
  //int mode = TMath::Abs(numu->var<int>("mode"));

  //bool fillthem = false;  //for checking of naturalness of dt scan results
  //int fillcounter = 0;    //for checking of naturalness of dt scan results
  for (int jsub=1; jsub<nse; jsub++) {
    float dt  = numu->var<float>("fq1rt0", 1, jsub) - numu->var<float>("fq1rt0", 2, 0);
    float N50 = numu->var<int>("fqn50", jsub);
    //if (histofill==true) std::cout << " [subevent# " << jsub << "]  dt = " << dt/1000. << " us, N50 = " << N50 << std::endl;
    //if (histofill==true && mode==1 && nse==2) h2_dtn50 -> Fill(dt/1000., N50);
    //if (histofill==true) h2_dtn50 -> Fill(dt/1000., N50);
    if (histofill==true) h2_dtn50 -> Fill(dt/1000., N50);
    TaggedDecaye++;

    //if (dt/1000. > 15. && dt/1000. < 20.) fillthem = true;
    //if (dt/1000. > 15. && dt/1000. < 20. && N50 >=50 && N50 <= 400) fillcounter++;

    if (dt/1000. < dtCut && N50 >= N50CutMin && N50 <= N50CutMax) 
      Decaye++;
    if (dt/1000. > 0. && dt/1000. < 5. && N50 > 0. && N50 < 50.)
      NumHotSpot++;
  }

  TaggedDecayeinBox += Decaye;


  //for checking of naturalness of dt scan results
  //if (fillcounter==2) fillthem = true;
  //else if (fillcounter==2) std::cout << "#decay-e in box: " << fillcounter << std::endl;

  /*for (int jsub=1; jsub<nse; jsub++) {
    float dt  = numu->var<float>("fq1rt0", 1, jsub) - numu->var<float>("fq1rt0", 2, 0);
    float N50 = numu->var<int>("fqn50", jsub);
    if (histofill==true && fillthem==true) h2_dtn50 -> Fill(dt/1000., N50);
  }*/
  return Decaye;
}


/*int DecayeBox::GetDecayeTagPurity(CC0PiNumu* numu,
                                  std::vector<float> *tscndlist, 
                                  float dtCut,
                                  float N50CutMin,
                                  float N50CutMax) {*/
int DecayeBox::GetDecayeTagPurity(CC0PiNumu* numu,
                                  Float_t *tscnd, 
                                  Float_t pscnd[][3],
                                  Int_t *itrkscnd,
                                  float dtCut,
                                  float N50CutMin,
                                  float N50CutMax) {
  
  //Check the existence of secondary particles
  int nse_true = numu->var<int>("nscndprt");
  int nse_reco = numu->var<int>("fqnse");
  if (nse_true==0) return 0;
  //if (nse_reco==0 || nse_reco==1) return 0;
  if (nse_reco==1) return 0;


  //Make tscnd list
  std::vector<float> tscndlist;
  for (int jsub=0; jsub<nse_true; jsub++) {
    std::cout << "[true] push_back tscnd = " << numu->var<float>("tscnd", jsub) << " us" << std::endl;
    tscndlist.push_back( numu->var<float>("tscnd", jsub) );

    std::cout << "[true] push_back tscnd = " << tscnd[jsub]/1000. << " us" << std::endl;
    tscndlist.push_back( tscnd[jsub]/1000. );
  }

  //Make dt list
  std::vector<float> dtlist;
  for (int jsub=1; jsub<nse_reco; jsub++) {
    std::cout << "[reco] push_back dt = " << (numu->var<float>("fq1rt0", 1, jsub) - numu->var<float>("fq1rt0", 2, 0))/1000. << " us" << std::endl;
    dtlist.push_back( (numu->var<float>("fq1rt0", 1, jsub) - numu->var<float>("fq1rt0", 2, 0))/1000. );
  }

  //std::vector<int> skip_itr_reco;
  std::vector<int> fin_itr_true; //final minimum truth
  std::vector<int> fin_itr_reco; //final minimum reco
  

  int truecounter = numu->var<int>("nscndprt");
  int recocounter = numu->var<int>("fqnse") - 1; //minus means subtraction of the primary lepton
  bool loopfinisher = false;
  while (loopfinisher==false) {

    std::cout << "[### DecayeBox::GetDecayeTagPurity() ###] true:reco = " << truecounter << " : " << recocounter << std::endl;

    ///////////////////////////////////
    //
    //  1 truth -> all reco
    //
    ///////////////////////////////////
    int tmp_itr_true = 999; //pre-minimum reco
    int tmp_itr_reco = 999; //pre-minimum reco
    //Truth loop
    float pre_min = 9999999.; //minimum reco. particle for the itrue-th particle
    for (long unsigned int itrue=0; itrue<tscndlist.size(); itrue++) {
      
      //Check
      bool done_this_true = false;
      for (long unsigned int imin=0; imin<fin_itr_true.size(); imin++) {
        if (itrue == (long unsigned int)fin_itr_true.at(imin)) done_this_true = true;
      }
      if (done_this_true==true) continue;

      //std::cout << "[true# " << itrue+1 << "]";
      float this_tscnd = tscndlist.at(itrue);
      //std::cout << "  tscnd = " << this_tscnd << " us" << std::endl;

      //Reco loop
      for (long unsigned int ireco=0; ireco<dtlist.size(); ireco++) {

        //Check
        bool done_this_reco = false;
        for (long unsigned int imin=0; imin<fin_itr_reco.size(); imin++) {
          if (ireco == (long unsigned int)fin_itr_reco.at(imin)) done_this_reco = true;
        }
        if (done_this_reco==true) continue;

        //std::cout << "   [reco# " << ireco+1 << "]";
        float this_dt = dtlist.at(ireco);
        //std::cout << "  dt = " << this_dt << " us" << std::endl;

        float timediff = std::fabs( this_dt - this_tscnd );
        //std::cout << "  Time diff. = " << timediff << " us" << std::endl;

        //update
        if (pre_min > timediff) {
          pre_min = timediff;
          tmp_itr_true = itrue;
          tmp_itr_reco = ireco;
        }
      }

    }
    //std::cout << "[Pre-minimum] true:reco = " << tmp_itr_true+1 << " : " << tmp_itr_reco+1 << std::endl;
    //std::cout << "              Pre-minimum time diff. = " << pre_min << " us" << std::endl;

    ///////////////////////////////////
    //
    //  pre-minimum reco -> all truth
    //
    ///////////////////////////////////
    int tmp2_itr_true = 999; //tentative final-minimum truth
    //Truth loop
    float fin_min    = 9999999.;
    float resolution = 0.;
    float fillthem   = false; //hotspot or not
    float min_pscnd  = 0.;
    int   min_iprtscnd = 0;
    int   min_lmecscnd = 0;
    float min_dt       = 0.;
    for (long unsigned int itrue=0; itrue<tscndlist.size(); itrue++) {

      //Check
      bool done_this_true = false;
      for (long unsigned int imin=0; imin<fin_itr_true.size(); imin++) {
        if (itrue == (long unsigned int)fin_itr_true.at(imin)) done_this_true = true;
      }
      if (done_this_true==true) continue;

      float this_iprtscnd = numu->var<int>("iprtscnd", itrue);
      float this_lmecscnd = numu->var<int>("lmecscnd", itrue);
      float this_tscnd = tscndlist.at(itrue);
      if (this_iprtscnd==2112 || this_iprtscnd==22)
        std::cout << "[true# " << itrue+1 << "]  PID = " << this_iprtscnd << ", interaction code: << " << this_lmecscnd << ", Track# = " << itrkscnd[itrue] << std::endl;
      //std::cout << "  tscnd = " << this_tscnd << " us" << std::endl;

      /*float this_pscnd = std::sqrt(pscnd[itrue][0]*pscnd[itrue][0] +
                                   pscnd[itrue][1]*pscnd[itrue][1] +
                                   pscnd[itrue][2]*pscnd[itrue][2]);*/
      float this_pscnd = pscnd[itrue][0];
      

      //extract pre-minimum
      float this_dt = 999.;
      float N50     = 0.;
      for (long unsigned int ireco=0; ireco<dtlist.size(); ireco++) {
        if (ireco == (long unsigned int)tmp_itr_reco) {
          //std::cout << "   [reco# " << ireco+1 << "]";
          this_dt = dtlist.at(ireco);
          //std::cout << "  dt = " << this_dt << " us" << std::endl;
          N50 = numu->var<int>("fqn50", ireco);
        }
      }

      //if (this_dt > 0. && this_dt < 5. && N50 > 0. && N50 < 50.) fillthem = true;
      float tmp_reso = this_dt - this_tscnd;

      //Final update
      float timediff = std::fabs( this_dt - this_tscnd );
      if (fin_min > timediff) {
        fin_min       = timediff;
        tmp2_itr_true = itrue;
        resolution    = tmp_reso;
        min_pscnd     = this_pscnd;
        min_iprtscnd  = this_iprtscnd;
        min_lmecscnd  = this_lmecscnd;
        min_dt        = this_dt;

        //Focus on the hotspot
        if (this_dt > 0. && this_dt < 5. && N50 > 0. && N50 < 50.) fillthem = true;
        else fillthem = false;
      }

    }

    //Conclude the final minimum pair
    fin_itr_true.push_back(tmp2_itr_true);
    fin_itr_reco.push_back(tmp_itr_reco);
    //std::cout << "[Final-minimum] true:reco = " << tmp2_itr_true+1 << " : " << tmp_itr_reco+1 << std::endl;
    //std::cout << "                Final-minimum time diff. = " << fin_min << " us" << std::endl;
    if (fillthem==true) {
      h1_mintimediff  -> Fill(resolution);
      h1_pscnd        -> Fill(min_pscnd);
      h1_iprtscnd     -> Fill(min_iprtscnd);
      h2_reso_x_pscnd -> Fill(resolution, min_pscnd);
      //h2_reso_x_iprtscnd -> Fill(resolution, min_iprtscnd);
      h2_reso_x_iprtscnd -> Fill(min_dt, min_iprtscnd);
      h2_reso_x_lmecscnd -> Fill(min_dt, min_lmecscnd);
      h2_iprtscnd_lmecscnd -> Fill(min_iprtscnd, min_lmecscnd);
    }

    //Decrement the number of truth particles at last
    truecounter -= 1;
    recocounter -= 1;

    loopfinisher = (truecounter==0 || recocounter==0);
    std::cout << "-----------------" << std::endl; 
  }
  std::cout << " " << std::endl;

  //Get the number of tagged truth decay-e
  TaggedTrueDecaye += fin_itr_reco.size();

  //Clean up
  fin_itr_true.clear();
  fin_itr_reco.clear();

  return 0;
}


int DecayeBox::GetTaggedDecaye(CC0PiNumu* numu) {
  int mode = TMath::Abs(numu->var<int>("mode"));
  //All interactions
  h1_TaggedDecaye -> Fill(numu->var<int>("fqdcye"));

  //CCQE
  if (mode==1) h1_TaggedDecaye_CCQE -> Fill(numu->var<int>("fqdcye"));

  //CC pion productions
  if (mode==11 || mode==12 || mode==13 || mode==21) h1_TaggedDecaye_CCpi -> Fill(numu->var<int>("fqdcye"));

  return numu->var<int>("fqdcye");
}


void DecayeBox::cdDecayeBox(TFile* fout) {
  fout -> mkdir("DecayeBox");
  fout -> cd("DecayeBox");
}


void DecayeBox::WritePlots() {
  Double_t tot_decaye = h1_TaggedDecaye->Integral();
  h1_TaggedDecaye -> Scale(1./tot_decaye);
  h1_TaggedDecaye -> Write();

  Double_t tot_decaye_CCQE = h1_TaggedDecaye_CCQE->Integral();
  h1_TaggedDecaye_CCQE -> Scale(1./tot_decaye_CCQE);
  h1_TaggedDecaye_CCQE -> Write();

  Double_t tot_decaye_CCpi = h1_TaggedDecaye_CCpi->Integral();
  h1_TaggedDecaye_CCpi -> Scale(1./tot_decaye_CCpi);
  h1_TaggedDecaye_CCpi -> Write();

  h1_mintimediff -> Write();
  h1_pscnd       -> Write();
  h1_iprtscnd    -> Write();

  h2_reso_x_pscnd -> Write();
  h2_reso_x_iprtscnd -> Write();
  h2_reso_x_lmecscnd -> Write();
  h2_iprtscnd_lmecscnd -> Write();

  h2_dtn50 -> Scale(1./SelectedParentNeutrinos[5]);
  h2_dtn50 -> Write();
}
