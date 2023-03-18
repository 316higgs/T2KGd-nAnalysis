#pragma once

//#include "/disk02/usr6/rakutsu/t2k/tmp/t2ksk-neutronh/anat2ksk/src/cc0pinumu/inc/CC0PiNumu.h"
#include "/disk02/usr6/sedi/anat2ksk/src/cc0pinumu/inc/CC0PiNumu.h"
#include "TTree.h"
#include "TFile.h"


//=== Tree ===
TTree* AnaTuple;
TTree* Ntuple;
TTree* woTagNtuple;
TTree* wTagNtuple;


//=== Tree Branch ===
int iclass_NoNTag;
int iclass_woTagN;
int iclass_wTagN;

int Ibound_NoNTag;
int Ibound_woTagN;
int Ibound_wTagN;

int mode_NoNTag;
int mode_woTagN;
int mode_wTagN;

// === vector variables at neutrino interaction
int numnu_NoNTag;
int numnu_woTagN;
int numnu_wTagN;

Float_t pnu_NoNTag[100];
Float_t pnu_woTagN[100];
Float_t pnu_wTagN[100];

int ipnu_NoNTag[100];
int ipnu_woTagN[100];
int ipnu_wTagN[100];

Float_t dirnu_NoNTag[100][3];
Float_t dirnu_woTagN[100][3];
Float_t dirnu_wTagN[100][3];

Int_t npar_NoNTag;
Int_t npar_woTagN;
Int_t npar_wTagN;

Float_t dirv_NoNTag[100][3];
Float_t dirv_woTagN[100][3];
Float_t dirv_wTagN[100][3];

Float_t wallv_NoNTag;
Float_t wallv_woTagN;
Float_t wallv_wTagN;

Double_t wgtosc_NoNTag;
Double_t wgtosc_woTagN;
Double_t wgtosc_wTagN;

Float_t pi0like_NoNTag[2];
Float_t pi0like_woTagN[2];
Float_t pi0like_wTagN[2];

Float_t pi0_e_NoNTag[2][2];
Float_t pi0_e_woTagN[2][2];
Float_t pi0_e_wTagN[2][2];

Float_t pi0_dir_NoNTag[2][2][3];
Float_t pi0_dir_woTagN[2][2][3];
Float_t pi0_dir_wTagN[2][2][3];

Float_t pi0mass_NoNTag[2];
Float_t pi0mass_woTagN[2];
Float_t pi0mass_wTagN[2];

Int_t nmue_NoNTag;
Int_t nmue_woTagN;
Int_t nmue_wTagN;

Int_t ipv_NoNTag[100];
Int_t ipv_woTagN[100];
Int_t ipv_wTagN[100];

Float_t posv_NoNTag[3];
Float_t posv_woTagN[3];
Float_t posv_wTagN[3];

Float_t pmomv_NoNTag[100];
Float_t pmomv_woTagN[100];
Float_t pmomv_wTagN[100];

Int_t nscndprt_NoNTag;
Int_t nscndprt_woTagN;
Int_t nscndprt_wTagN;

Int_t itrkscnd_NoNTag[1000];
Int_t itrkscnd_woTagN[1000];
Int_t itrkscnd_wTagN[1000];

Float_t vtxscnd_NoNTag[1000][3];
Float_t vtxscnd_woTagN[1000][3];
Float_t vtxscnd_wTagN[1000][3];

Float_t pscnd_NoNTag[1000][3];
Float_t pscnd_woTagN[1000][3];
Float_t pscnd_wTagN[1000][3];

Int_t iprtscnd_NoNTag[1000];
Int_t iprtscnd_woTagN[1000];
Int_t iprtscnd_wTagN[1000];

Float_t tscnd_NoNTag[1000];
Float_t tscnd_woTagN[1000];
Float_t tscnd_wTagN[1000];

Int_t iprntprt_NoNTag[1000];
Int_t iprntprt_woTagN[1000];
Int_t iprntprt_wTagN[1000];

Int_t lmecscnd_NoNTag[1000];
Int_t lmecscnd_woTagN[1000];
Int_t lmecscnd_wTagN[1000];

Int_t iprnttrk_NoNTag[1000];
Int_t iprnttrk_woTagN[1000];
Int_t iprnttrk_wTagN[1000];

Int_t iorgprt_NoNTag[1000];
Int_t iorgprt_woTagN[1000];
Int_t iorgprt_wTagN[1000];

Int_t iflgscnd_NoNTag[1000];
Int_t iflgscnd_woTagN[1000];
Int_t iflgscnd_wTagN[1000];

Float_t pprnt_NoNTag[1000][3];
Float_t pprnt_woTagN[1000][3];
Float_t pprnt_wTagN[1000][3];

// === vector variables at neutrino interaction + additional info
int Npvc_NoNTag = 0;
int Npvc_woTagN = 0;
int Npvc_wTagN  = 0;

int Ipvc_NoNTag[100];
int Ipvc_woTagN[100];
int Ipvc_wTagN[100];

int Ichvc_NoNTag[100];
int Ichvc_woTagN[100];
int Ichvc_wTagN[100];

int Iflvc_NoNTag[100];
int Iflvc_woTagN[100];
int Iflvc_wTagN[100];

Int_t Iorgvc_NoNTag[100];
Int_t Iorgvc_woTagN[100];
Int_t Iorgvc_wTagN[100];

Float_t Abspvc_NoNTag[100];
Float_t Abspvc_woTagN[100];
Float_t Abspvc_wTagN[100];

Float_t Pvc_NoNTag[100][3];
Float_t Pvc_woTagN[100][3];
Float_t Pvc_wTagN[100][3];

Float_t Crsx_NoNTag;
Float_t Crsx_woTagN;
Float_t Crsx_wTagN;

Float_t Crsy_NoNTag;
Float_t Crsy_woTagN;
Float_t Crsy_wTagN;

Float_t Crsz_NoNTag;
Float_t Crsz_woTagN;
Float_t Crsz_wTagN;

Float_t Crsphi_NoNTag;
Float_t Crsphi_woTagN;
Float_t Crsphi_wTagN;

Int_t Nvert_NoNTag;
Int_t Nvert_woTagN;
Int_t Nvert_wTagN;

Float_t Posvert_NoNTag[300][3];
Float_t Posvert_woTagN[300][3];
Float_t Posvert_wTagN[300][3];

Int_t Iflgvert_NoNTag[300];
Int_t Iflgvert_woTagN[300];
Int_t Iflgvert_wTagN[300];

Int_t Nvcvert_NoNTag;
Int_t Nvcvert_woTagN;
Int_t Nvcvert_wTagN;

Float_t Dirvert_NoNTag[900][3];
Float_t Dirvert_woTagN[900][3];
Float_t Dirvert_wTagN[900][3];

Float_t Abspvert_NoNTag[900];
Float_t Abspvert_woTagN[900];
Float_t Abspvert_wTagN[900];

Float_t Abstpvert_NoNTag[900];
Float_t Abstpvert_woTagN[900];
Float_t Abstpvert_wTagN[900];

Int_t Ipvert_NoNTag[900];
Int_t Ipvert_woTagN[900];
Int_t Ipvert_wTagN[900];

Int_t Iverti_NoNTag[900];
Int_t Iverti_woTagN[900];
Int_t Iverti_wTagN[900];

Int_t Ivertf_NoNTag[900];
Int_t Ivertf_woTagN[900];
Int_t Ivertf_wTagN[900];

Float_t Fsiprob_NoNTag;
Float_t Fsiprob_woTagN;
Float_t Fsiprob_wTagN;

Int_t Numbndn_NoNTag;
Int_t Numbndn_woTagN;
Int_t Numbndn_wTagN;

Int_t Numbndp_NoNTag;
Int_t Numbndp_woTagN;
Int_t Numbndp_wTagN;

Int_t Numfrep_NoNTag;
Int_t Numfrep_woTagN;
Int_t Numfrep_wTagN;

Int_t Numatom_NoNTag;
Int_t Numatom_woTagN;
Int_t Numatom_wTagN;

Int_t Nvertsk_NoNTag;
Int_t Nvertsk_woTagN;
Int_t Nvertsk_wTagN;

Float_t Posvertsk_NoNTag[300][3];
Float_t Posvertsk_woTagN[300][3];
Float_t Posvertsk_wTagN[300][3];

Int_t Iflgvertsk_NoNTag[300];
Int_t Iflgvertsk_woTagN[300];
Int_t Iflgvertsk_wTagN[300];

Int_t Nvcvertsk_NoNTag;
Int_t Nvcvertsk_woTagN;
Int_t Nvcvertsk_wTagN;

Float_t Dirvertsk_NoNTag[900][3];
Float_t Dirvertsk_woTagN[900][3];
Float_t Dirvertsk_wTagN[900][3];

Float_t Abspvertsk_NoNTag[900];
Float_t Abspvertsk_woTagN[900];
Float_t Abspvertsk_wTagN[900];

Float_t Abstpvertsk_NoNTag[900];
Float_t Abstpvertsk_woTagN[900];
Float_t Abstpvertsk_wTagN[900];

Int_t Ipvertsk_NoNTag[900];
Int_t Ipvertsk_woTagN[900];
Int_t Ipvertsk_wTagN[900];

Int_t Ivertisk_NoNTag[900];
Int_t Ivertisk_woTagN[900];
Int_t Ivertisk_wTagN[900];

Int_t Ivertfsk_NoNTag[900];
Int_t Ivertfsk_woTagN[900];
Int_t Ivertfsk_wTagN[900];

Float_t Fsiprobsk_NoNTag;
Float_t Fsiprobsk_woTagN;
Float_t Fsiprobsk_wTagN;

Int_t filetype_NoNTag = -1;
Int_t filetype_woTagN = -1;
Int_t filetype_wTagN  = -1;

// === SK variables (for T2KReWeight)
Int_t nring_NoNTag;
Int_t nring_woTagN;
Int_t nring_wTagN;

Int_t nev_NoNTag;
Int_t nev_woTagN;
Int_t nev_wTagN;

Int_t nhitac_NoNTag;
Int_t nhitac_woTagN;
Int_t nhitac_wTagN;

Float_t wall_NoNTag;
Float_t wall_wTagN;
Float_t wall_woTagN;

Float_t evis_NoNTag;
Float_t evis_wTagN;
Float_t evis_woTagN;

Float_t dir_NoNTag[100][3];
Float_t dir_wTagN[100][3];
Float_t dir_woTagN[100][3];

// === fiTQun variables
Int_t fqnse_NoNTag = 0;
Int_t fqnse_woTagN = 0;
Int_t fqnse_wTagN  = 0;

Float_t fq1rdir_NoNTag[100][7][3];
Float_t fq1rdir_woTagN[100][7][3];
Float_t fq1rdir_wTagN[100][7][3];

Float_t fqmomm_NoNTag;
Float_t fqmomm_woTagN;
Float_t fqmomm_wTagN;

Float_t fqmome_NoNTag;
Float_t fqmome_woTagN;
Float_t fqmome_wTagN;

Int_t fqnmrfit_NoNTag;
Int_t fqnmrfit_woTagN;
Int_t fqnmrfit_wTagN;

Float_t fqmrdir_NoNTag[100][6][3];
Float_t fqmrdir_woTagN[100][6][3];
Float_t fqmrdir_wTagN[100][6][3];

Float_t fqmrmom_NoNTag[100][6][3];
Float_t fqmrmom_woTagN[100][6][3];
Float_t fqmrmom_wTagN[100][6][3];

// === MR variables
UInt_t ip_NoNTag[100];
UInt_t ip_wTagN[100];
UInt_t ip_woTagN[100];

Int_t ipp_NoNTag;
Int_t ipp_woTagN;
Int_t ipp_wTagN;

Int_t ippp_NoNTag;
Int_t ippp_woTagN;
Int_t ippp_wTagN;

Float_t evisible_NoNTag;
Float_t evisible_woTagN;
Float_t evisible_wTagN;

Float_t elosssum_pipi_NoNTag;
Float_t elosssum_pipi_woTagN;
Float_t elosssum_pipi_wTagN;

// === NIWG information
Double_t wgts_maqeh_NoNTag;
Double_t wgts_maqeh_woTagN;
Double_t wgts_maqeh_wTagN;

Double_t DeltaPForEmiss0_NoNTag;
Double_t DeltaPForEmiss0_woTagN;
Double_t DeltaPForEmiss0_wTagN;

//----------------------------------------------------------

// === Analysis ===
Int_t ana_mode;

Float_t ana_GenBefSIE;
Float_t ana_BefSInMom[3];
Float_t ana_SInMom[3];

Float_t ana_TruePrmMuMom[3];
Float_t ana_TruePrmMuAbsMom;
Float_t ana_TrueMuEndVtx[3];
Float_t ana_RecoMuEndVtx[3];

class TreeManager {
  public:
  	TreeManager(int TagID){
  		//if (TagID==0) woTagNtuple = new TTree("woTagNtuple", "");
      //else wTagNtuple = new TTree("wTagNtuple", "");

      if (TagID==0) woTagNtuple = new TTree("mtuple", "");
      else if (TagID==1) wTagNtuple = new TTree("mtuple", "");
      else Ntuple = new TTree("mtuple", "");

      AnaTuple = new TTree("AnaTuple", "");
  	};
  	virtual ~TreeManager(){};

    void FillBrankTree(int TagID);

    void SetBranch(int TagID);
    void SetAnaBranch();
  	void FillTree(int TagID);
    void FillAnaTree();
    void WriteTree(TString OutName, int TagID);
    void WriteAnaTree();
};
