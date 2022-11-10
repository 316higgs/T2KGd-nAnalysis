#include "TreeManager.h"
#include "TGaxis.h"

//TagID=0 for w/o tagged neutron sample, TagID=1 for w/ tagged neutron sample
void TreeManager::SetBranch(int TagID) {

  if (TagID==0) {
    woTagNtuple -> Branch("iclass", &iclass_woTagN, "iclass/I");

    //vector variables at neutrino interaction
    woTagNtuple -> Branch("Ibound", &Ibound_woTagN, "Ibound/I");
    woTagNtuple -> Branch("mode", &mode_woTagN, "mode/I");
    woTagNtuple -> Branch("numnu", &numnu_woTagN, "numnu/I");
    woTagNtuple -> Branch("pnu", pnu_woTagN, "pnu[numnu]/F");
    woTagNtuple -> Branch("ipnu", ipnu_woTagN, "ipnu[numnu]/I");
    woTagNtuple -> Branch("dirnu", dirnu_woTagN, "dirnu[numnu][3]/F");
    woTagNtuple -> Branch("npar", &npar_woTagN, "npar/I");
    woTagNtuple -> Branch("dirv", dirv_woTagN, "dirv[npar][3]");                //For MakeRF
    woTagNtuple -> Branch("wallv", &wallv_woTagN, "wallv/F");                   //For T2KReWeight
    woTagNtuple -> Branch("wgtosc", &wgtosc_woTagN, "wgtosc/D");                //For MakeRF
    woTagNtuple -> Branch("pi0like", pi0like_woTagN, "pi0like[2]/F");           //For T2KReWeight
    woTagNtuple -> Branch("pi0_e", pi0_e_woTagN, "pi0_e[2][2]/F");              //For T2KReWeight
    woTagNtuple -> Branch("pi0_dir", pi0_dir_woTagN, "pi0_dir[2][2][3]/F");     //For T2KReWeight
    woTagNtuple -> Branch("pi0mass", pi0mass_woTagN, "pi0mass[2]/F");           //For T2KReWeight
    woTagNtuple -> Branch("nmue", &nmue_woTagN, "nmue/I");                      //For T2KReWeight
    woTagNtuple -> Branch("ipv", ipv_woTagN, "ipv[npar]/i");                    //For T2KReWeight
    woTagNtuple -> Branch("posv", posv_woTagN, "posv[3]/F");                    //For T2KReWeight
    woTagNtuple -> Branch("pmomv", pmomv_woTagN, "pmomv[npar]/F");              //For T2KReWeight
    woTagNtuple -> Branch("nscndprt", &nscndprt_woTagN, "nscndprt/I");          //For T2KReWeight
    woTagNtuple -> Branch("itrkscnd", itrkscnd_woTagN, "itrkscnd[nscndprt]/I"); //For T2KReWeight
    woTagNtuple -> Branch("vtxscnd", vtxscnd_woTagN, "vtxscnd[nscndprt][3]/F"); //For T2KReWeight
    woTagNtuple -> Branch("pscnd", pscnd_woTagN, "pscnd[nscndprt][3]/F");       //For T2KReWeight
    woTagNtuple -> Branch("iprtscnd", iprtscnd_woTagN, "iprtscnd[nscndprt]/I"); //For T2KReWeight
    woTagNtuple -> Branch("tscnd", tscnd_woTagN, "tscnd[nscndprt]/F");          //For T2KReWeight
    woTagNtuple -> Branch("iprntprt", iprntprt_woTagN, "iprntprt[nscndprt]/I"); //For T2KReWeight
    woTagNtuple -> Branch("lmecscnd", lmecscnd_woTagN, "lmecscnd[nscndprt]/I"); //For T2KReWeight
    woTagNtuple -> Branch("iprnttrk", iprnttrk_woTagN, "iprnttrk[nscndprt]/I"); //For T2KReWeight
    woTagNtuple -> Branch("iorgprt", iorgprt_woTagN, "iorgprt[nscndprt]/I");    //For T2KReWeight
    woTagNtuple -> Branch("iflgscnd", iflgscnd_woTagN, "iflgscnd[nscndprt]/I"); //For T2KReWeight
    woTagNtuple -> Branch("pprnt", pprnt_woTagN, "pprnt[nscndprt][3]/F");       //For T2KReWeight

    //vector variables at neutrino interaction + additional info
    woTagNtuple -> Branch("Npvc", &Npvc_woTagN, "Npvc/I");
    woTagNtuple -> Branch("Ipvc", Ipvc_woTagN, "Ipvc[Npvc]/I");
    woTagNtuple -> Branch("Ichvc", Ichvc_woTagN, "Ichvc[Npvc]/I");
    woTagNtuple -> Branch("Iflvc", Iflvc_woTagN, "Iflvc[Npvc]/I");
    woTagNtuple -> Branch("Iorgvc", Iorgvc_woTagN, "Iorgvc[Npvc]/I");             //For T2KReWeight
    woTagNtuple -> Branch("Abspvc", Abspvc_woTagN, "Abspvc[Npvc]/F");             //For T2KReWeight
    woTagNtuple -> Branch("Pvc", Pvc_woTagN, "Pvc[Npvc]/F");                      //For T2KReWeight
    woTagNtuple -> Branch("Crsx", &Crsx_woTagN, "Crsx/F");                        //For T2KReWeight
    woTagNtuple -> Branch("Crsy", &Crsy_woTagN, "Crsy/F");                        //For T2KReWeight
    woTagNtuple -> Branch("Crsz", &Crsz_woTagN, "Crsz/F");                        //For T2KReWeight
    woTagNtuple -> Branch("Crsphi", &Crsphi_woTagN, "Crsphi/F");                  //For T2KReWeight
    woTagNtuple -> Branch("Nvert", &Nvert_woTagN, "Nvert/I");                     //For T2KReWeight
    woTagNtuple -> Branch("Posvert", Posvert_woTagN, "Posvert[Nvert][3]/F");      //For T2KReWeight
    woTagNtuple -> Branch("Iflgvert", Iflgvert_woTagN, "Iflgvert[Nvert]/I");      //For T2KReWeight
    woTagNtuple -> Branch("Nvcvert", &Nvcvert_woTagN, "Nvcvert/I");               //For T2KReWeight
    woTagNtuple -> Branch("Dirvert", Dirvert_woTagN, "Dirvert[Nvcvert][3]/F");    //For T2KReWeight
    woTagNtuple -> Branch("Abspvert", Abspvert_woTagN, "Abspvert[Nvcvert]/F");    //For T2KReWeight
    woTagNtuple -> Branch("Abstpvert", Abstpvert_woTagN, "Abstpvert[Nvcvert]/F"); //For T2KReWeight
    woTagNtuple -> Branch("Ipvert", Ipvert_woTagN, "Ipvert[Nvcvert]/I");          //For T2KReWeight
    woTagNtuple -> Branch("Iverti", Iverti_woTagN, "Iverti[Nvcvert]/I");          //For T2KReWeight
    woTagNtuple -> Branch("Ivertf", Ivertf_woTagN, "Ivertf[Nvcvert]/I");          //For T2KReWeight
    woTagNtuple -> Branch("Fsiprob", &Fsiprob_woTagN, "Fsiprob/F");               //For T2KReWeight
    woTagNtuple -> Branch("Numbndn", &Numbndn_woTagN, "Numbndn/I");               //For T2KReWeight
    woTagNtuple -> Branch("Numbndp", &Numbndp_woTagN, "Numbndp/I");               //For T2KReWeight
    woTagNtuple -> Branch("Numfrep", &Numfrep_woTagN, "Numfrep/I");               //For T2KReWeight
    woTagNtuple -> Branch("Numatom", &Numatom_woTagN, "Numatom/I");               //For T2KReWeight
    woTagNtuple -> Branch("Nvertsk", &Nvertsk_woTagN, "Nvertsk/I");                     //For T2KReWeight
    woTagNtuple -> Branch("Posvertsk", Posvertsk_woTagN, "Posvertsk[Nvert][3]/F");      //For T2KReWeight
    woTagNtuple -> Branch("Iflgvertsk", Iflgvertsk_woTagN, "Iflgvertsk[Nvert]/I");      //For T2KReWeight
    woTagNtuple -> Branch("Nvcvertsk", &Nvcvertsk_woTagN, "Nvcvertsk/I");               //For T2KReWeight
    woTagNtuple -> Branch("Dirvertsk", Dirvertsk_woTagN, "Dirvertsk[Nvcvert][3]/F");    //For T2KReWeight
    woTagNtuple -> Branch("Abspvertsk", Abspvertsk_woTagN, "Abspvertsk[Nvcvert]/F");    //For T2KReWeight
    woTagNtuple -> Branch("Abstpvertsk", Abstpvertsk_woTagN, "Abstpvertsk[Nvcvert]/F"); //For T2KReWeight
    woTagNtuple -> Branch("Ipvertsk", Ipvertsk_woTagN, "Ipvertsk[Nvcvert]/I");          //For T2KReWeight
    woTagNtuple -> Branch("Ivertisk", Ivertisk_woTagN, "Ivertisk[Nvcvert]/I");          //For T2KReWeight
    woTagNtuple -> Branch("Ivertfsk", Ivertfsk_woTagN, "Ivertfsk[Nvcvert]/I");          //For T2KReWeight
    woTagNtuple -> Branch("Fsiprobsk", &Fsiprobsk_woTagN, "Fsiprobsk/F");               //For T2KReWeight
    woTagNtuple -> Branch("filetype", &filetype_woTagN, "filetype/I");                  //For T2KReWeight

    //SK variables (for T2KReWeight)
    woTagNtuple -> Branch("nring", &nring_woTagN, "nring/I");
    woTagNtuple -> Branch("nev", &nev_woTagN, "nev/I");
    woTagNtuple -> Branch("nhitac", &nhitac_woTagN, "nhitac/I");
    woTagNtuple -> Branch("wall", &wall_woTagN, "wall/F");
    woTagNtuple -> Branch("evis", &evis_woTagN, "evis/F");
    woTagNtuple -> Branch("dir", dir_woTagN, "dir[nring][3]/F");

    //fiTQun variables
    // 1R fit
    woTagNtuple -> Branch("fqnse", &fqnse_woTagN, "fqnse/I");
    woTagNtuple -> Branch("fq1rdir", fq1rdir_woTagN, "fq1rdir[fqnse][7][3]/F");
    woTagNtuple -> Branch("fqmomm", &fqmomm_woTagN, "fqmomm/F");
    woTagNtuple -> Branch("fqmome", &fqmome_woTagN, "fqmome/F");
    // MR fit
    woTagNtuple -> Branch("fqnmrfit", &fqnmrfit_woTagN, "fqnmrfit/I");
    woTagNtuple -> Branch("fqmrdir", fqmrdir_woTagN, "fqmrdir[fqnmrfit][6][3]/F");
    woTagNtuple -> Branch("fqmrmom", fqmrmom_woTagN, "fqmrmom[fqnmrfit][6][3]/F");
    woTagNtuple -> Branch("ip", ip_woTagN, "ip[nring]/l");    //For T2KReWeight
    woTagNtuple -> Branch("ipp", &ipp_woTagN, "ipp/I");
    woTagNtuple -> Branch("ippp", &ippp_woTagN, "ippp/I");    //For MakeRF
    woTagNtuple -> Branch("evisible", &evisible_woTagN, "evisible/F");
    woTagNtuple -> Branch("elosssum_pipi", &elosssum_pipi_woTagN, "elosssum_pipi/F");

    //NIWG information
    //woTagNtuple -> Branch("wgts_maqeh", &wgts_maqeh_woTagN, "wgts_maqeh/I");
    woTagNtuple -> Branch("wgts_maqeh", &wgts_maqeh_woTagN, "wgts_maqeh/D");
    woTagNtuple -> Branch("DeltaPForEmiss0", &DeltaPForEmiss0_woTagN, "DeltaPForEmiss0/D");
  }
  else if (TagID==1) {
    wTagNtuple -> Branch("iclass", &iclass_wTagN, "iclass/I");

    //vector variables at neutrino interaction
    wTagNtuple -> Branch("Ibound", &Ibound_wTagN, "Ibound/I");
    wTagNtuple -> Branch("mode", &mode_wTagN, "mode/I");
    wTagNtuple -> Branch("numnu", &numnu_wTagN, "numnu/I");
    wTagNtuple -> Branch("pnu", pnu_wTagN, "pnu[numnu]/F");
    wTagNtuple -> Branch("ipnu", ipnu_wTagN, "ipnu[numnu]/I");
    wTagNtuple -> Branch("dirnu", dirnu_wTagN, "dirnu[numnu][3]/F");
    wTagNtuple -> Branch("npar", &npar_wTagN, "npar/I");
    wTagNtuple -> Branch("dirv", dirv_wTagN, "dirv[npar][3]");                //For MakeRF
    wTagNtuple -> Branch("wallv", &wallv_wTagN, "wallv/F");                   //For T2KReWeight
    wTagNtuple -> Branch("wgtosc", &wgtosc_wTagN, "wgtosc/D");                //For MakeRF
    wTagNtuple -> Branch("pi0like", pi0like_wTagN, "pi0like[2]/F");           //For T2KReWeight
    wTagNtuple -> Branch("pi0_e", pi0_e_wTagN, "pi0_e[2][2]/F");              //For T2KReWeight
    wTagNtuple -> Branch("pi0_dir", pi0_dir_wTagN, "pi0_dir[2][2][3]/F");     //For T2KReWeight
    wTagNtuple -> Branch("pi0mass", pi0mass_wTagN, "pi0mass[2]/F");           //For T2KReWeight
    wTagNtuple -> Branch("nmue", &nmue_wTagN, "nmue/I");                      //For T2KReWeight
    wTagNtuple -> Branch("ipv", ipv_wTagN, "ipv[npar]/i");                    //For T2KReWeight
    wTagNtuple -> Branch("posv", posv_wTagN, "posv[3]/F");                    //For T2KReWeight
    wTagNtuple -> Branch("pmomv", pmomv_wTagN, "pmomv[npar]/F");              //For T2KReWeight
    wTagNtuple -> Branch("nscndprt", &nscndprt_wTagN, "nscndprt/I");          //For T2KReWeight
    wTagNtuple -> Branch("itrkscnd", itrkscnd_wTagN, "itrkscnd[nscndprt]/I"); //For T2KReWeight
    wTagNtuple -> Branch("vtxscnd", vtxscnd_wTagN, "vtxscnd[nscndprt][3]/F"); //For T2KReWeight
    wTagNtuple -> Branch("pscnd", pscnd_wTagN, "pscnd[nscndprt][3]/F");       //For T2KReWeight
    wTagNtuple -> Branch("iprtscnd", iprtscnd_wTagN, "iprtscnd[nscndprt]/I"); //For T2KReWeight
    wTagNtuple -> Branch("tscnd", tscnd_wTagN, "tscnd[nscndprt]/F");          //For T2KReWeight
    wTagNtuple -> Branch("iprntprt", iprntprt_wTagN, "iprntprt[nscndprt]/I"); //For T2KReWeight
    wTagNtuple -> Branch("lmecscnd", lmecscnd_wTagN, "lmecscnd[nscndprt]/I"); //For T2KReWeight
    wTagNtuple -> Branch("iprnttrk", iprnttrk_wTagN, "iprnttrk[nscndprt]/I"); //For T2KReWeight
    wTagNtuple -> Branch("iorgprt", iorgprt_wTagN, "iorgprt[nscndprt]/I");    //For T2KReWeight
    wTagNtuple -> Branch("iflgscnd", iflgscnd_wTagN, "iflgscnd[nscndprt]/I"); //For T2KReWeight
    wTagNtuple -> Branch("pprnt", pprnt_wTagN, "pprnt[nscndprt][3]/F");       //For T2KReWeight

    //vector variables at neutrino interaction + additional info
    wTagNtuple -> Branch("Npvc", &Npvc_wTagN, "Npvc/I");
    wTagNtuple -> Branch("Ipvc", Ipvc_wTagN, "Ipvc[Npvc]/I");
    wTagNtuple -> Branch("Ichvc", Ichvc_wTagN, "Ichvc[Npvc]/I");
    wTagNtuple -> Branch("Iflvc", Iflvc_wTagN, "Iflvc[Npvc]/I");
    wTagNtuple -> Branch("Iorgvc", Iorgvc_wTagN, "Iorgvc[Npvc]/I");             //For T2KReWeight
    wTagNtuple -> Branch("Abspvc", Abspvc_wTagN, "Abspvc[Npvc]/F");             //For T2KReWeight
    wTagNtuple -> Branch("Pvc", Pvc_wTagN, "Pvc[Npvc]/F");                      //For T2KReWeight
    wTagNtuple -> Branch("Crsx", &Crsx_wTagN, "Crsx/F");                        //For T2KReWeight
    wTagNtuple -> Branch("Crsy", &Crsy_wTagN, "Crsy/F");                        //For T2KReWeight
    wTagNtuple -> Branch("Crsz", &Crsz_wTagN, "Crsz/F");                        //For T2KReWeight
    wTagNtuple -> Branch("Crsphi", &Crsphi_wTagN, "Crsphi/F");                  //For T2KReWeight
    wTagNtuple -> Branch("Nvert", &Nvert_wTagN, "Nvert/I");                     //For T2KReWeight
    wTagNtuple -> Branch("Posvert", Posvert_wTagN, "Posvert[Nvert][3]/F");      //For T2KReWeight
    wTagNtuple -> Branch("Iflgvert", Iflgvert_wTagN, "Iflgvert[Nvert]/I");      //For T2KReWeight
    wTagNtuple -> Branch("Nvcvert", &Nvcvert_wTagN, "Nvcvert/I");               //For T2KReWeight
    wTagNtuple -> Branch("Dirvert", Dirvert_wTagN, "Dirvert[Nvcvert][3]/F");    //For T2KReWeight
    wTagNtuple -> Branch("Abspvert", Abspvert_wTagN, "Abspvert[Nvcvert]/F");    //For T2KReWeight
    wTagNtuple -> Branch("Abstpvert", Abstpvert_wTagN, "Abstpvert[Nvcvert]/F"); //For T2KReWeight
    wTagNtuple -> Branch("Ipvert", Ipvert_wTagN, "Ipvert[Nvcvert]/I");          //For T2KReWeight
    wTagNtuple -> Branch("Iverti", Iverti_wTagN, "Iverti[Nvcvert]/I");          //For T2KReWeight
    wTagNtuple -> Branch("Ivertf", Ivertf_wTagN, "Ivertf[Nvcvert]/I");          //For T2KReWeight
    wTagNtuple -> Branch("Fsiprob", &Fsiprob_wTagN, "Fsiprob/F");               //For T2KReWeight
    wTagNtuple -> Branch("Numbndn", &Numbndn_wTagN, "Numbndn/I");               //For T2KReWeight
    wTagNtuple -> Branch("Numbndp", &Numbndp_wTagN, "Numbndp/I");               //For T2KReWeight
    wTagNtuple -> Branch("Numfrep", &Numfrep_wTagN, "Numfrep/I");               //For T2KReWeight
    wTagNtuple -> Branch("Numatom", &Numatom_wTagN, "Numatom/I");               //For T2KReWeight
    wTagNtuple -> Branch("Nvertsk", &Nvertsk_wTagN, "Nvertsk/I");                     //For T2KReWeight
    wTagNtuple -> Branch("Posvertsk", Posvertsk_wTagN, "Posvertsk[Nvert][3]/F");      //For T2KReWeight
    wTagNtuple -> Branch("Iflgvertsk", Iflgvertsk_wTagN, "Iflgvertsk[Nvert]/I");      //For T2KReWeight
    wTagNtuple -> Branch("Nvcvertsk", &Nvcvertsk_wTagN, "Nvcvertsk/I");               //For T2KReWeight
    wTagNtuple -> Branch("Dirvertsk", Dirvertsk_wTagN, "Dirvertsk[Nvcvert][3]/F");    //For T2KReWeight
    wTagNtuple -> Branch("Abspvertsk", Abspvertsk_wTagN, "Abspvertsk[Nvcvert]/F");    //For T2KReWeight
    wTagNtuple -> Branch("Abstpvertsk", Abstpvertsk_wTagN, "Abstpvertsk[Nvcvert]/F"); //For T2KReWeight
    wTagNtuple -> Branch("Ipvertsk", Ipvertsk_wTagN, "Ipvertsk[Nvcvert]/I");          //For T2KReWeight
    wTagNtuple -> Branch("Ivertisk", Ivertisk_wTagN, "Ivertisk[Nvcvert]/I");          //For T2KReWeight
    wTagNtuple -> Branch("Ivertfsk", Ivertfsk_wTagN, "Ivertfsk[Nvcvert]/I");          //For T2KReWeight
    wTagNtuple -> Branch("Fsiprobsk", &Fsiprobsk_wTagN, "Fsiprobsk/F");               //For T2KReWeight
    wTagNtuple -> Branch("filetype", &filetype_wTagN, "filetype/I");                  //For T2KReWeight

    //SK variables (for T2KReWeight)
    wTagNtuple -> Branch("nring", &nring_wTagN, "nring/I");
    wTagNtuple -> Branch("nev", &nev_wTagN, "nev/I");
    wTagNtuple -> Branch("nhitac", &nhitac_wTagN, "nhitac/I");
    wTagNtuple -> Branch("wall", &wall_wTagN, "wall/F");
    wTagNtuple -> Branch("evis", &evis_wTagN, "evis/F");
    wTagNtuple -> Branch("dir", dir_wTagN, "dir[nring][3]/F");

    //fiTQun variables
    // 1R fit
    wTagNtuple -> Branch("fqnse", &fqnse_wTagN, "fqnse/I");
    wTagNtuple -> Branch("fq1rdir", fq1rdir_wTagN, "fq1rdir[fqnse][7][3]/F");
    wTagNtuple -> Branch("fqmomm", &fqmomm_wTagN, "fqmomm/F");
    wTagNtuple -> Branch("fqmome", &fqmome_wTagN, "fqmome/F");
    // MR fit
    wTagNtuple -> Branch("fqnmrfit", &fqnmrfit_wTagN, "fqnmrfit/I");
    wTagNtuple -> Branch("fqmrdir", fqmrdir_wTagN, "fqmrdir[fqnmrfit][6][3]/F");
    wTagNtuple -> Branch("fqmrmom", fqmrmom_wTagN, "fqmrmom[fqnmrfit][6][3]/F");
    wTagNtuple -> Branch("ip", ip_wTagN, "ip[nring]/l");    //For T2KReWeight
    wTagNtuple -> Branch("ipp", &ipp_wTagN, "ipp/I");
    wTagNtuple -> Branch("ippp", &ippp_wTagN, "ippp/I");    //For MakeRF
    wTagNtuple -> Branch("evisible", &evisible_wTagN, "evisible/F");
    wTagNtuple -> Branch("elosssum_pipi", &elosssum_pipi_wTagN, "elosssum_pipi/F");

    //NIWG information
    //wTagNtuple -> Branch("wgts_maqeh", &wgts_maqeh_wTagN, "wgts_maqeh/I");
    wTagNtuple -> Branch("wgts_maqeh", &wgts_maqeh_wTagN, "wgts_maqeh/D");
    wTagNtuple -> Branch("DeltaPForEmiss0", &DeltaPForEmiss0_wTagN, "DeltaPForEmiss0/D");
  }
  else {
    Ntuple -> Branch("iclass", &iclass_NoNTag, "iclass/I");

    //vector variables at neutrino interaction
    Ntuple -> Branch("Ibound", &Ibound_NoNTag, "Ibound/I");
    Ntuple -> Branch("mode", &mode_NoNTag, "mode/I");
    Ntuple -> Branch("numnu", &numnu_NoNTag, "numnu/I");
    Ntuple -> Branch("pnu", pnu_NoNTag, "pnu[numnu]/F");
    Ntuple -> Branch("ipnu", ipnu_NoNTag, "ipnu[numnu]/I");
    Ntuple -> Branch("dirnu", dirnu_NoNTag, "dirnu[numnu][3]/F");
    Ntuple -> Branch("npar", &npar_NoNTag, "npar/I");
    Ntuple -> Branch("dirv", dirv_NoNTag, "dirv[npar][3]");                //For MakeRF
    Ntuple -> Branch("wallv", &wallv_NoNTag, "wallv/F");                   //For T2KReWeight
    Ntuple -> Branch("wgtosc", &wgtosc_NoNTag, "wgtosc/D");                //For MakeRF
    Ntuple -> Branch("pi0like", pi0like_NoNTag, "pi0like[2]/F");           //For T2KReWeight
    Ntuple -> Branch("pi0_e", pi0_e_NoNTag, "pi0_e[2][2]/F");              //For T2KReWeight
    Ntuple -> Branch("pi0_dir", pi0_dir_NoNTag, "pi0_dir[2][2][3]/F");     //For T2KReWeight
    Ntuple -> Branch("pi0mass", pi0mass_NoNTag, "pi0mass[2]/F");           //For T2KReWeight
    Ntuple -> Branch("nmue", &nmue_NoNTag, "nmue/I");                      //For T2KReWeight
    Ntuple -> Branch("ipv", ipv_NoNTag, "ipv[npar]/i");                    //For T2KReWeight
    Ntuple -> Branch("posv", posv_NoNTag, "posv[3]/F");                    //For T2KReWeight
    Ntuple -> Branch("pmomv", pmomv_NoNTag, "pmomv[npar]/F");              //For T2KReWeight
    Ntuple -> Branch("nscndprt", &nscndprt_NoNTag, "nscndprt/I");          //For T2KReWeight
    Ntuple -> Branch("itrkscnd", itrkscnd_NoNTag, "itrkscnd[nscndprt]/I"); //For T2KReWeight
    Ntuple -> Branch("vtxscnd", vtxscnd_NoNTag, "vtxscnd[nscndprt][3]/F"); //For T2KReWeight
    Ntuple -> Branch("pscnd", pscnd_NoNTag, "pscnd[nscndprt][3]/F");       //For T2KReWeight
    Ntuple -> Branch("iprtscnd", iprtscnd_NoNTag, "iprtscnd[nscndprt]/I"); //For T2KReWeight
    Ntuple -> Branch("tscnd", tscnd_NoNTag, "tscnd[nscndprt]/F");          //For T2KReWeight
    Ntuple -> Branch("iprntprt", iprntprt_NoNTag, "iprntprt[nscndprt]/I"); //For T2KReWeight
    Ntuple -> Branch("lmecscnd", lmecscnd_NoNTag, "lmecscnd[nscndprt]/I"); //For T2KReWeight
    Ntuple -> Branch("iprnttrk", iprnttrk_NoNTag, "iprnttrk[nscndprt]/I"); //For T2KReWeight
    Ntuple -> Branch("iorgprt", iorgprt_NoNTag, "iorgprt[nscndprt]/I");    //For T2KReWeight
    Ntuple -> Branch("iflgscnd", iflgscnd_NoNTag, "iflgscnd[nscndprt]/I"); //For T2KReWeight
    Ntuple -> Branch("pprnt", pprnt_NoNTag, "pprnt[nscndprt][3]/F");       //For T2KReWeight

    //vector variables at neutrino interaction + additional info
    Ntuple -> Branch("Npvc", &Npvc_NoNTag, "Npvc/I");
    Ntuple -> Branch("Ipvc", Ipvc_NoNTag, "Ipvc[Npvc]/I");
    Ntuple -> Branch("Ichvc", Ichvc_NoNTag, "Ichvc[Npvc]/I");
    Ntuple -> Branch("Iflvc", Iflvc_NoNTag, "Iflvc[Npvc]/I");
    Ntuple -> Branch("Iorgvc", Iorgvc_NoNTag, "Iorgvc[Npvc]/I");             //For T2KReWeight
    Ntuple -> Branch("Abspvc", Abspvc_NoNTag, "Abspvc[Npvc]/F");             //For T2KReWeight
    Ntuple -> Branch("Pvc", Pvc_NoNTag, "Pvc[Npvc]/F");                      //For T2KReWeight
    Ntuple -> Branch("Crsx", &Crsx_NoNTag, "Crsx/F");                        //For T2KReWeight
    Ntuple -> Branch("Crsy", &Crsy_NoNTag, "Crsy/F");                        //For T2KReWeight
    Ntuple -> Branch("Crsz", &Crsz_NoNTag, "Crsz/F");                        //For T2KReWeight
    Ntuple -> Branch("Crsphi", &Crsphi_NoNTag, "Crsphi/F");                  //For T2KReWeight
    Ntuple -> Branch("Nvert", &Nvert_NoNTag, "Nvert/I");                     //For T2KReWeight
    Ntuple -> Branch("Posvert", Posvert_NoNTag, "Posvert[Nvert][3]/F");      //For T2KReWeight
    Ntuple -> Branch("Iflgvert", Iflgvert_NoNTag, "Iflgvert[Nvert]/I");      //For T2KReWeight
    Ntuple -> Branch("Nvcvert", &Nvcvert_NoNTag, "Nvcvert/I");               //For T2KReWeight
    Ntuple -> Branch("Dirvert", Dirvert_NoNTag, "Dirvert[Nvcvert][3]/F");    //For T2KReWeight
    Ntuple -> Branch("Abspvert", Abspvert_NoNTag, "Abspvert[Nvcvert]/F");    //For T2KReWeight
    Ntuple -> Branch("Abstpvert", Abstpvert_NoNTag, "Abstpvert[Nvcvert]/F"); //For T2KReWeight
    Ntuple -> Branch("Ipvert", Ipvert_NoNTag, "Ipvert[Nvcvert]/I");          //For T2KReWeight
    Ntuple -> Branch("Iverti", Iverti_NoNTag, "Iverti[Nvcvert]/I");          //For T2KReWeight
    Ntuple -> Branch("Ivertf", Ivertf_NoNTag, "Ivertf[Nvcvert]/I");          //For T2KReWeight
    Ntuple -> Branch("Fsiprob", &Fsiprob_NoNTag, "Fsiprob/F");               //For T2KReWeight
    Ntuple -> Branch("Numbndn", &Numbndn_NoNTag, "Numbndn/I");               //For T2KReWeight
    Ntuple -> Branch("Numbndp", &Numbndp_NoNTag, "Numbndp/I");               //For T2KReWeight
    Ntuple -> Branch("Numfrep", &Numfrep_NoNTag, "Numfrep/I");               //For T2KReWeight
    Ntuple -> Branch("Numatom", &Numatom_NoNTag, "Numatom/I");               //For T2KReWeight
    Ntuple -> Branch("Nvertsk", &Nvertsk_NoNTag, "Nvertsk/I");                     //For T2KReWeight
    Ntuple -> Branch("Posvertsk", Posvertsk_NoNTag, "Posvertsk[Nvert][3]/F");      //For T2KReWeight
    Ntuple -> Branch("Iflgvertsk", Iflgvertsk_NoNTag, "Iflgvertsk[Nvert]/I");      //For T2KReWeight
    Ntuple -> Branch("Nvcvertsk", &Nvcvertsk_NoNTag, "Nvcvertsk/I");               //For T2KReWeight
    Ntuple -> Branch("Dirvertsk", Dirvertsk_NoNTag, "Dirvertsk[Nvcvert][3]/F");    //For T2KReWeight
    Ntuple -> Branch("Abspvertsk", Abspvertsk_NoNTag, "Abspvertsk[Nvcvert]/F");    //For T2KReWeight
    Ntuple -> Branch("Abstpvertsk", Abstpvertsk_NoNTag, "Abstpvertsk[Nvcvert]/F"); //For T2KReWeight
    Ntuple -> Branch("Ipvertsk", Ipvertsk_NoNTag, "Ipvertsk[Nvcvert]/I");          //For T2KReWeight
    Ntuple -> Branch("Ivertisk", Ivertisk_NoNTag, "Ivertisk[Nvcvert]/I");          //For T2KReWeight
    Ntuple -> Branch("Ivertfsk", Ivertfsk_NoNTag, "Ivertfsk[Nvcvert]/I");          //For T2KReWeight
    Ntuple -> Branch("Fsiprobsk", &Fsiprobsk_NoNTag, "Fsiprobsk/F");               //For T2KReWeight
    Ntuple -> Branch("filetype", &filetype_NoNTag, "filetype/I");                  //For T2KReWeight

    //SK variables (for T2KReWeight)
    Ntuple -> Branch("nring", &nring_NoNTag, "nring/I");
    Ntuple -> Branch("nev", &nev_NoNTag, "nev/I");
    Ntuple -> Branch("nhitac", &nhitac_NoNTag, "nhitac/I");
    Ntuple -> Branch("wall", &wall_NoNTag, "wall/F");
    Ntuple -> Branch("evis", &evis_NoNTag, "evis/F");
    Ntuple -> Branch("dir", dir_NoNTag, "dir[nring][3]/F");

    //fiTQun variables
    // 1R fit
    Ntuple -> Branch("fqnse", &fqnse_NoNTag, "fqnse/I");
    Ntuple -> Branch("fq1rdir", fq1rdir_NoNTag, "fq1rdir[fqnse][7][3]/F");
    Ntuple -> Branch("fqmomm", &fqmomm_NoNTag, "fqmomm/F");
    Ntuple -> Branch("fqmome", &fqmome_NoNTag, "fqmome/F");
    // MR fit
    Ntuple -> Branch("fqnmrfit", &fqnmrfit_NoNTag, "fqnmrfit/I");
    Ntuple -> Branch("fqmrdir", fqmrdir_NoNTag, "fqmrdir[fqnmrfit][6][3]/F");
    Ntuple -> Branch("fqmrmom", fqmrmom_NoNTag, "fqmrmom[fqnmrfit][6][3]/F");
    Ntuple -> Branch("ip", ip_NoNTag, "ip[nring]/l");    //For T2KReWeight
    Ntuple -> Branch("ipp", &ipp_NoNTag, "ipp/I");
    Ntuple -> Branch("ippp", &ippp_NoNTag, "ippp/I");    //For MakeRF
    Ntuple -> Branch("evisible", &evisible_NoNTag, "evisible/F");
    Ntuple -> Branch("elosssum_pipi", &elosssum_pipi_NoNTag, "elosssum_pipi/F");

    //NIWG information
    //Ntuple -> Branch("wgts_maqeh", &wgts_maqeh, "wgts_maqeh/I");
    Ntuple -> Branch("wgts_maqeh", &wgts_maqeh_NoNTag, "wgts_maqeh/D");
    Ntuple -> Branch("DeltaPForEmiss0", &DeltaPForEmiss0_NoNTag, "DeltaPForEmiss0/D");
  }

}


void TreeManager::FillBrankTree(int TagID) {

  //Make empty 100 events
  for (int ientry=0; ientry<10; ientry++) {

    //=== w/o tagged-n sample ===
    if (TagID==0) {
      iclass_woTagN = 1302112;
      //iclass_woTagN = 0;
      mode_woTagN   = 1;
      Ibound_woTagN = 1;
      numnu_woTagN  = 10; //default
      for (Int_t ivc=0; ivc<numnu_woTagN; ivc++) {
        pnu_woTagN[ivc]  = 0.6;
        ipnu_woTagN[ivc] = 12;

        dirnu_woTagN[ivc][0] = 0.669764;
        dirnu_woTagN[ivc][1] = -0.742179;
        dirnu_woTagN[ivc][2] = 0.0242228;
      }

      Npvc_woTagN = 10; //default
      for (Int_t ivc=0; ivc<Npvc_woTagN; ivc++) {
        Ipvc_woTagN[ivc]   = 1;
        Ichvc_woTagN[ivc]  = 1;
        Iflvc_woTagN[ivc]  = 1;
        Iorgvc_woTagN[ivc] = 1;
        Abspvc_woTagN[ivc] = 0.1;
        for (int idir=0; idir<3; idir++) Pvc_woTagN[ivc][idir] = 0.1;
      }
      Crsx_woTagN   = -1.;
      Crsy_woTagN   = -1.;
      Crsz_woTagN   = -1.;
      Crsphi_woTagN = -1.;

      Nvert_woTagN = 10; //default
      for (int iv=0; iv<Nvert_woTagN; iv++) {
        Iflgvert_woTagN[iv] = 1;
        for (int idir=0; idir<3; idir++) Posvert_woTagN[iv][idir] = 0.1;
      }

      Nvcvert_woTagN = 10; //default
      for (int ivc=0; ivc<Nvcvert_woTagN; ivc++) {
        Abspvert_woTagN[ivc]  = 0.1;
        Abstpvert_woTagN[ivc] = 0.1;
        Ipvert_woTagN[ivc]    = 1;
        Iverti_woTagN[ivc]    = 1;
        Ivertf_woTagN[ivc]    = 1;
        for (int idir=0; idir<3; idir++) {
          Dirvert_woTagN[ivc][idir] = 0.1;
        }
      }
      Fsiprob_woTagN = 1.;

      Numbndn_woTagN = 8;
      Numbndp_woTagN = 8;
      Numfrep_woTagN = 2;
      Numatom_woTagN = 16; //Numatom = Numbndn + Numbndp

      Nvertsk_woTagN = 10; //default
      for (int iv=0; iv<Nvertsk_woTagN; iv++) {
        Iflgvertsk_woTagN[iv] = 1;
        for (int idir=0; idir<3; idir++) Posvertsk_woTagN[iv][idir] = 0.1;
      }

      Nvcvertsk_woTagN = 10; //default
      for (int ivc=0; ivc<Nvcvertsk_woTagN; ivc++) {
        Abspvertsk_woTagN[ivc]  = 0.1;
        Abstpvertsk_woTagN[ivc] = 0.1;
        Ipvertsk_woTagN[ivc]    = 1;
        Ivertisk_woTagN[ivc]    = 1;
        Ivertfsk_woTagN[ivc]    = 1;
        for (int idir=0; idir<3; idir++) {
          Dirvertsk_woTagN[ivc][idir] = 0.1;
        }
      }
      Fsiprobsk_woTagN = 0.1;


      npar_woTagN = 10; //default
      for (int iv=0; iv<npar_woTagN; iv++) {
        ipv_woTagN[iv]   = 1;
        pmomv_woTagN[iv] = 0.1;

        dirv_woTagN[iv][0] = 0.669764;
        dirv_woTagN[iv][1] = -0.742179;
        dirv_woTagN[iv][2] = 0.0242228;
        /*for (int idir=0; idir<3; idir++) {
          dirv_woTagN[iv][idir] = 0.;
        }*/
      }
      for (int idir=0; idir<3; idir++) posv_woTagN[idir] = 0.1;
      wallv_woTagN  = 0.1;
      wgtosc_woTagN = 0.2;
      for (int ipi=0; ipi<2; ipi++) {
        pi0like_woTagN[ipi] = 0.1;
        pi0mass_woTagN[ipi] = 0.1;
        for (int jpi=0; jpi<2; jpi++) {
          pi0_e_woTagN[ipi][jpi] = 0.1;

          pi0_dir_woTagN[ipi][jpi][0] = 0.669764;
          pi0_dir_woTagN[ipi][jpi][1] = -0.742179;
          pi0_dir_woTagN[ipi][jpi][2] = 0.0242228;
          /*for (int idir=0; idir<3; idir++) {
            pi0_dir_woTagN[ipi][jpi][idir] = 0.;
          }*/
        }
      }
      nmue_woTagN = 1;

      nscndprt_woTagN = 10; //default
      for (int iscnd=0; iscnd<nscndprt_woTagN; iscnd++) {
        itrkscnd_woTagN[iscnd] = 1;
        iprtscnd_woTagN[iscnd] = 1;
        tscnd_woTagN[iscnd]    = 0.1;
        iprntprt_woTagN[iscnd] = 1;
        lmecscnd_woTagN[iscnd] = 1;
        iprnttrk_woTagN[iscnd] = 1;
        iorgprt_woTagN[iscnd]  = 1;
        iflgscnd_woTagN[iscnd] = 1;
        for (int idir=0; idir<3; idir++) {
          vtxscnd_woTagN[iscnd][idir] = 0.1;
          pscnd_woTagN[iscnd][idir]   = 0.1;
          pprnt_woTagN[iscnd][idir]   = 0.1;
        }
      }

      
      nring_woTagN  = 2; //default
      nev_woTagN    = 1;
      nhitac_woTagN = 1;
      wall_woTagN   = 0.1;
      evis_woTagN   = 0.1;

      fqnse_woTagN = 10;  //default
      for (Int_t ifq=0; ifq<fqnse_woTagN; ifq++) {
        for (int ihyp=0; ihyp<7; ihyp++) {

          fq1rdir_woTagN[ifq][ihyp][0] = 0.669764;
          fq1rdir_woTagN[ifq][ihyp][1] = -0.742179;
          fq1rdir_woTagN[ifq][ihyp][2] = 0.0242228;
          /*for (int idir=0; idir<3; idir++) {
            //fqmrdir_wTagN[ifq][ihyp][idir] = 0.;
            //fqmrmom_wTagN[ifq][ihyp][idir] = 0.;
            fq1rdir_woTagN[ifq][ihyp][idir] = 0.;
          }*/
        }
      }
      fqmome_woTagN = 0.1;
      fqmomm_woTagN = 0.1;

      fqnmrfit_woTagN = 2; //default
      for (Int_t ifq=0; ifq<fqnmrfit_woTagN; ifq++) {
        //ipp_wTagN[ifq] = fqmrifit[ifq];
        for (int ihyp=0; ihyp<6; ihyp++) {

          fqmrdir_woTagN[ifq][ihyp][0] = 0.669764;
          fqmrdir_woTagN[ifq][ihyp][1] = -0.742179;
          fqmrdir_woTagN[ifq][ihyp][2] = 0.0242228;
          for (int idir=0; idir<3; idir++) {
            //fqmrdir_woTagN[ifq][ihyp][idir] = 0.;
            fqmrmom_woTagN[ifq][ihyp][idir] = 0.1;
          }
        }
      }

      /*for (int iring=0; iring<nring_woTagN; iring++) {
        ip_woTagN[iring] = 0;
        for (int idir=0; idir<3; idir++) {
          dir_woTagN[iring][idir] = 0.;
        }
      }*/
      if (nring_woTagN==0) {
        for (int iring=0; iring<10; iring++) {
          ip_woTagN[iring] = 1;

          dir_woTagN[iring][0] = 0.669764;
          dir_woTagN[iring][1] = -0.742179;
          dir_woTagN[iring][2] = 0.0242228;
          /*for (int idir=0; idir<3; idir++) {
            dir_woTagN[iring][idir] = 0.;
          }*/
        }
      }
      else {
        for (int iring=0; iring<nring_woTagN; iring++) {
          ip_woTagN[iring] = 1;

          dir_woTagN[iring][0] = 0.669764;
          dir_woTagN[iring][1] = -0.742179;
          dir_woTagN[iring][2] = 0.0242228;
          /*for (int idir=0; idir<3; idir++) {
            dir_woTagN[iring][idir] = 0.;
          }*/
        }
      }
      ipp_woTagN           = -1;
      ippp_woTagN          = -1;
      evisible_woTagN      = -1;
      elosssum_pipi_woTagN = -1;

      wgts_maqeh_woTagN = 1.;
      DeltaPForEmiss0_woTagN = 0.1;

    }
    //=== w/ tagged-n sample ===
    else if (TagID==1) {
      iclass_wTagN = 1312112;
      //iclass_wTagN = 0;
      mode_wTagN   = 1;
      Ibound_wTagN = 1;
      numnu_wTagN  = 10; //default
      for (Int_t ivc=0; ivc<numnu_wTagN; ivc++) {
        pnu_wTagN[ivc]  = 0.6;
        ipnu_wTagN[ivc] = 12;

        dirnu_wTagN[ivc][0] = 0.669764;
        dirnu_wTagN[ivc][1] = -0.742179;
        dirnu_wTagN[ivc][2] = 0.0242228;
      }

      Npvc_wTagN = 10;  //default
      for (Int_t ivc=0; ivc<Npvc_wTagN; ivc++) {
        Ipvc_wTagN[ivc]   = 1;
        Ichvc_wTagN[ivc]  = 1;
        Iflvc_wTagN[ivc]  = 1;
        Iorgvc_wTagN[ivc] = 1;
        Abspvc_wTagN[ivc] = 0.1;
        for (int idir=0; idir<3; idir++) Pvc_wTagN[ivc][idir] = 0.1;
      }
      Crsx_wTagN   = -1.;
      Crsy_wTagN   = -1.;
      Crsz_wTagN   = -1.;
      Crsphi_wTagN = -1.;

      Nvert_wTagN = 10; //default
      for (int iv=0; iv<Nvert_wTagN; iv++) {
        Iflgvert_wTagN[iv] = 1;
        for (int idir=0; idir<3; idir++) Posvert_wTagN[iv][idir] = 0.1;
      }

      Nvcvert_wTagN = 10; //default
      for (int ivc=0; ivc<Nvcvert_wTagN; ivc++) {
        Abspvert_wTagN[ivc]  = 0.1;
        Abstpvert_wTagN[ivc] = 0.1;
        Ipvert_wTagN[ivc]    = 1;
        Iverti_wTagN[ivc]    = 1;
        Ivertf_wTagN[ivc]    = 1;
        for (int idir=0; idir<3; idir++) {
          Dirvert_wTagN[ivc][idir] = 0.1;
        }
      }
      Fsiprob_wTagN = 1.;

      Numbndn_wTagN = 8;
      Numbndp_wTagN = 8;
      Numfrep_wTagN = 2;
      Numatom_wTagN = 16; //Numatom = Numbndn + Numbndp

      Nvertsk_wTagN = 10; //default
      for (int iv=0; iv<Nvertsk_wTagN; iv++) {
        Iflgvertsk_wTagN[iv] = 1;
        for (int idir=0; idir<3; idir++) Posvertsk_wTagN[iv][idir] = 0.1;
      }

      Nvcvertsk_wTagN = 10;  //default
      for (int ivc=0; ivc<Nvcvertsk_wTagN; ivc++) {
        Abspvertsk_wTagN[ivc]  = 0.1;
        Abstpvertsk_wTagN[ivc] = 0.1;
        Ipvertsk_wTagN[ivc]    = 1;
        Ivertisk_wTagN[ivc]    = 1;
        Ivertfsk_wTagN[ivc]    = 1;
        for (int idir=0; idir<3; idir++) {
          Dirvertsk_wTagN[ivc][idir] = 0.1;
        }
      }
      Fsiprobsk_wTagN = 0.1;


      npar_wTagN = 10; //default
      for (int iv=0; iv<npar_wTagN; iv++) {
        ipv_wTagN[iv]   = 1;
        pmomv_wTagN[iv] = 0.1;

        dirv_wTagN[iv][0] = 0.669764;
        dirv_wTagN[iv][1] = -0.742179;
        dirv_wTagN[iv][2] = 0.0242228;
        /*for (int idir=0; idir<3; idir++) {
          dirv_wTagN[iv][idir] = 0.;
        }*/
      }
      for (int idir=0; idir<3; idir++) posv_wTagN[idir] = 0.1;
      wallv_wTagN  = 0.1;
      wgtosc_wTagN = 0.2;
      for (int ipi=0; ipi<2; ipi++) {
        pi0like_wTagN[ipi] = 0.1;
        pi0mass_wTagN[ipi] = 0.1;
        for (int jpi=0; jpi<2; jpi++) {
          pi0_e_wTagN[ipi][jpi] = 0.1;

          pi0_dir_wTagN[ipi][jpi][0] = 0.669764;
          pi0_dir_wTagN[ipi][jpi][1] = -0.742179;
          pi0_dir_wTagN[ipi][jpi][2] = 0.0242228;
          /*for (int idir=0; idir<3; idir++) {
            pi0_dir_wTagN[ipi][jpi][idir] = 0.;
          }*/
        }
      }
      nmue_woTagN = 1;

      nscndprt_wTagN = 10; //default
      for (int iscnd=0; iscnd<nscndprt_wTagN; iscnd++) {
        itrkscnd_wTagN[iscnd] = 1;
        iprtscnd_wTagN[iscnd] = 1;
        tscnd_wTagN[iscnd]    = 0.1;
        iprntprt_wTagN[iscnd] = 1;
        lmecscnd_wTagN[iscnd] = 1;
        iprnttrk_wTagN[iscnd] = 1;
        iorgprt_wTagN[iscnd]  = 1;
        iflgscnd_wTagN[iscnd] = 1;
        for (int idir=0; idir<3; idir++) {
          vtxscnd_wTagN[iscnd][idir] = 0.1;
          pscnd_wTagN[iscnd][idir]   = 0.1;
          pprnt_wTagN[iscnd][idir]   = 0.1;
        }
      }
      
      nring_wTagN  = 2; //default
      nev_wTagN    = 1;
      nhitac_wTagN = 1;
      wall_wTagN   = 0.1;
      evis_wTagN   = 0.1;

      fqnse_wTagN = 10; //default
      for (Int_t ifq=0; ifq<fqnse_wTagN; ifq++) {
        for (int ihyp=0; ihyp<7; ihyp++) {

          fq1rdir_wTagN[ifq][ihyp][0] = 0.669764;
          fq1rdir_wTagN[ifq][ihyp][1] = -0.742179;
          fq1rdir_wTagN[ifq][ihyp][2] = 0.0242228;
          /*for (int idir=0; idir<3; idir++) {
            //fqmrdir_wTagN[ifq][ihyp][idir] = 0.;
            //fqmrmom_wTagN[ifq][ihyp][idir] = 0.;
            fq1rdir_wTagN[ifq][ihyp][idir] = 0.;
          }*/
        }
      }
      fqmome_wTagN = 0.1;
      fqmomm_wTagN = 0.1;

      fqnmrfit_wTagN = 2; //default
      for (Int_t ifq=0; ifq<fqnmrfit_wTagN; ifq++) {
        //ipp_wTagN[ifq] = fqmrifit[ifq];
        for (int ihyp=0; ihyp<6; ihyp++) {

          fqmrdir_wTagN[ifq][ihyp][0] = 0.669764;
          fqmrdir_wTagN[ifq][ihyp][1] = -0.742179;
          fqmrdir_wTagN[ifq][ihyp][2] = 0.0242228;
          for (int idir=0; idir<3; idir++) {
            //fqmrdir_wTagN[ifq][ihyp][idir] = 0.;
            fqmrmom_wTagN[ifq][ihyp][idir] = 0.1;
          }
        }
      }

      /*for (int iring=0; iring<nring_wTagN; iring++) {
        ip_wTagN[iring] = 0;
        for (int idir=0; idir<3; idir++) {
          dir_wTagN[iring][idir] = 0.;
        }
      }*/
      if (nring_wTagN==0) {
        for (int iring=0; iring<10; iring++) {
          ip_wTagN[iring] = 1;

          dir_wTagN[iring][0] = 0.669764;
          dir_wTagN[iring][1] = -0.742179;
          dir_wTagN[iring][2] = 0.0242228;
          /*for (int idir=0; idir<3; idir++) {
            dir_wTagN[iring][idir] = 0.;
          }*/
        }
      }
      else {
        for (int iring=0; iring<nring_wTagN; iring++) {
          ip_wTagN[iring] = 1;

          dir_wTagN[iring][0] = 0.669764;
          dir_wTagN[iring][1] = -0.742179;
          dir_wTagN[iring][2] = 0.0242228;
          /*for (int idir=0; idir<3; idir++) {
            dir_wTagN[iring][idir] = 0.;
          }*/
        }
      }
      ipp_wTagN           = -1;
      ippp_wTagN          = -1;
      evisible_wTagN      = -1;
      elosssum_pipi_wTagN = -1;

      wgts_maqeh_wTagN = 1.;
      DeltaPForEmiss0_wTagN = 0.1;
    }
    else {
      iclass_NoNTag = 13;
      //iclass = 0;
      mode_NoNTag   = 1;
      Ibound_NoNTag = 1;
      numnu_NoNTag  = 10; //default
      for (Int_t ivc=0; ivc<numnu_NoNTag; ivc++) {
        pnu_NoNTag[ivc]  = 0.6;
        ipnu_NoNTag[ivc] = 12;

        dirnu_NoNTag[ivc][0] = 0.669764;
        dirnu_NoNTag[ivc][1] = -0.742179;
        dirnu_NoNTag[ivc][2] = 0.0242228;
      }

      Npvc_NoNTag = 10; //default
      for (Int_t ivc=0; ivc<Npvc_NoNTag; ivc++) {
        Ipvc_NoNTag[ivc]   = 1;
        Ichvc_NoNTag[ivc]  = 1;
        Iflvc_NoNTag[ivc]  = 1;
        Iorgvc_NoNTag[ivc] = 1;
        Abspvc_NoNTag[ivc] = 0.1;
        for (int idir=0; idir<3; idir++) Pvc_NoNTag[ivc][idir] = 0.1;
      }
      Crsx_NoNTag   = -1.;
      Crsy_NoNTag   = -1.;
      Crsz_NoNTag   = -1.;
      Crsphi_NoNTag = -1.;

      Nvert_NoNTag = 10; //default
      for (int iv=0; iv<Nvert_NoNTag; iv++) {
        Iflgvert_NoNTag[iv] = 1;
        for (int idir=0; idir<3; idir++) Posvert_NoNTag[iv][idir] = 0.1;
      }

      Nvcvert_NoNTag = 10; //default
      for (int ivc=0; ivc<Nvcvert_NoNTag; ivc++) {
        Abspvert_NoNTag[ivc]  = 0.1;
        Abstpvert_NoNTag[ivc] = 0.1;
        Ipvert_NoNTag[ivc]    = 1;
        Iverti_NoNTag[ivc]    = 1;
        Ivertf_NoNTag[ivc]    = 1;
        for (int idir=0; idir<3; idir++) {
          Dirvert_NoNTag[ivc][idir] = 0.1;
        }
      }
      Fsiprob_NoNTag = 1.;

      Numbndn_NoNTag = 8;
      Numbndp_NoNTag = 8;
      Numfrep_NoNTag = 2;
      Numatom_NoNTag = 16; //Numatom = Numbndn + Numbndp

      Nvertsk_NoNTag = 10; //default
      for (int iv=0; iv<Nvertsk_NoNTag; iv++) {
        Iflgvertsk_NoNTag[iv] = 1;
        for (int idir=0; idir<3; idir++) Posvertsk_NoNTag[iv][idir] = 0.1;
      }

      Nvcvertsk_NoNTag = 10; //default
      for (int ivc=0; ivc<Nvcvertsk_NoNTag; ivc++) {
        Abspvertsk_NoNTag[ivc]  = 0.1;
        Abstpvertsk_NoNTag[ivc] = 0.1;
        Ipvertsk_NoNTag[ivc]    = 1;
        Ivertisk_NoNTag[ivc]    = 1;
        Ivertfsk_NoNTag[ivc]    = 1;
        for (int idir=0; idir<3; idir++) {
          Dirvertsk_NoNTag[ivc][idir] = 0.1;
        }
      }
      Fsiprobsk_NoNTag = 0.1;


      npar_NoNTag = 10; //default
      for (int iv=0; iv<npar_NoNTag; iv++) {
        ipv_NoNTag[iv]   = 1;
        pmomv_NoNTag[iv] = 0.1;

        dirv_NoNTag[iv][0] = 0.669764;
        dirv_NoNTag[iv][1] = -0.742179;
        dirv_NoNTag[iv][2] = 0.0242228;
        /*for (int idir=0; idir<3; idir++) {
          dirv_NoNTag[iv][idir] = 0.;
        }*/
      }
      for (int idir=0; idir<3; idir++) posv_NoNTag[idir] = 0.1;
      wallv_NoNTag  = 0.1;
      wgtosc_NoNTag = 0.2;
      for (int ipi=0; ipi<2; ipi++) {
        pi0like_NoNTag[ipi] = 0.1;
        pi0mass_NoNTag[ipi] = 0.1;
        for (int jpi=0; jpi<2; jpi++) {
          pi0_e_NoNTag[ipi][jpi] = 0.1;

          pi0_dir_NoNTag[ipi][jpi][0] = 0.669764;
          pi0_dir_NoNTag[ipi][jpi][1] = -0.742179;
          pi0_dir_NoNTag[ipi][jpi][2] = 0.0242228;
          /*for (int idir=0; idir<3; idir++) {
            pi0_dir_NoNTag[ipi][jpi][idir] = 0.;
          }*/
        }
      }
      nmue_NoNTag = 1;

      nscndprt_NoNTag = 10; //default
      for (int iscnd=0; iscnd<nscndprt_NoNTag; iscnd++) {
        itrkscnd_NoNTag[iscnd] = 1;
        iprtscnd_NoNTag[iscnd] = 1;
        tscnd_NoNTag[iscnd]    = 0.1;
        iprntprt_NoNTag[iscnd] = 1;
        lmecscnd_NoNTag[iscnd] = 1;
        iprnttrk_NoNTag[iscnd] = 1;
        iorgprt_NoNTag[iscnd]  = 1;
        iflgscnd_NoNTag[iscnd] = 1;
        for (int idir=0; idir<3; idir++) {
          vtxscnd_NoNTag[iscnd][idir] = 0.1;
          pscnd_NoNTag[iscnd][idir]   = 0.1;
          pprnt_NoNTag[iscnd][idir]   = 0.1;
        }
      }
      
      nring_NoNTag  = 2; //default
      nev_NoNTag    = 1;
      nhitac_NoNTag = 1;
      wall_NoNTag   = 0.1;
      evis_NoNTag   = 0.1;

      fqnse_NoNTag = 10; //default
      for (Int_t ifq=0; ifq<fqnse_NoNTag; ifq++) {
        for (int ihyp=0; ihyp<7; ihyp++) {

          fq1rdir_NoNTag[ifq][ihyp][0] = 0.669764;
          fq1rdir_NoNTag[ifq][ihyp][1] = -0.742179;
          fq1rdir_NoNTag[ifq][ihyp][2] = 0.0242228;
          /*for (int idir=0; idir<3; idir++) {
            //fqmrdir_NoNTag[ifq][ihyp][idir] = 0.;
            //fqmrmom_NoNTag[ifq][ihyp][idir] = 0.;
            fq1rdir_NoNTag[ifq][ihyp][idir] = 0.;
          }*/
        }
      }
      fqmome_NoNTag = 0.1;
      fqmomm_NoNTag = 0.1;

      fqnmrfit_NoNTag = 2; //default
      for (Int_t ifq=0; ifq<fqnmrfit_NoNTag; ifq++) {
        //ipp_wTagN[ifq] = fqmrifit[ifq];
        for (int ihyp=0; ihyp<6; ihyp++) {

          fqmrdir_NoNTag[ifq][ihyp][0] = 0.669764;
          fqmrdir_NoNTag[ifq][ihyp][1] = -0.742179;
          fqmrdir_NoNTag[ifq][ihyp][2] = 0.0242228;
          for (int idir=0; idir<3; idir++) {
            //fqmrdir_NoNTag[ifq][ihyp][idir] = 0.;
            fqmrmom_NoNTag[ifq][ihyp][idir] = 0.1;
          }
        }
      }

      /*for (int iring=0; iring<nring_NoNTag; iring++) {
        ip_NoNTag[iring] = 0;
        for (int idir=0; idir<3; idir++) {
          dir_NoNTag[iring][idir] = 0.;
        }
      }*/
      if (nring_NoNTag==0) {
        for (int iring=0; iring<10; iring++) {
          ip_NoNTag[iring] = 1;

          dir_NoNTag[iring][0] = 0.669764;
          dir_NoNTag[iring][1] = -0.742179;
          dir_NoNTag[iring][2] = 0.0242228;
          /*for (int idir=0; idir<3; idir++) {
            dir_NoNTag[iring][idir] = 0.;
          }*/
        }          
      }
      else {
        for (int iring=0; iring<nring_NoNTag; iring++) {
          ip_NoNTag[iring] = 1;

          dir_NoNTag[iring][0] = 0.669764;
          dir_NoNTag[iring][1] = -0.742179;
          dir_NoNTag[iring][2] = 0.0242228;
          /*for (int idir=0; idir<3; idir++) {
            dir_NoNTag[iring][idir] = 0.;
          }*/
        }
      }
      ipp_NoNTag           = -1;
      ippp_NoNTag          = -1;
      evisible_NoNTag      = -1;
      elosssum_pipi_NoNTag = -1;

      wgts_maqeh_NoNTag = 1.;
      DeltaPForEmiss0_NoNTag = 0.1;
    }

    this -> FillTree(TagID);
  }
  
}


void TreeManager::FillTree(int TagID) {
  if (TagID==0) woTagNtuple -> Fill();
  else if (TagID==1) wTagNtuple -> Fill();
  else Ntuple -> Fill();
}

void TreeManager::WriteTree(TString OutName, int TagID) {
  TFile* fout = new TFile(OutName, "RECREATE");
  fout -> cd();
  if (TagID==0) woTagNtuple -> Write();
  else if (TagID==1) wTagNtuple -> Write();
  else Ntuple -> Write();
}