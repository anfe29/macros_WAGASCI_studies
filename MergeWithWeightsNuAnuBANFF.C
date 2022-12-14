#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <utility>
#include <fstream>
#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TGraph.h"
#include "THStack.h"
#include "TF1.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TTree.h"
#include "TLine.h"
#include "TTree.h"
#include "TGraphErrors.h"
#include "TMatrixDSym.h"
#include "TDecompChol.h"
#include "TMatrixD.h"
#include "TLorentzVector.h"

#include <TRandom3.h>

#include "/sps/t2k/bdouet/fitter_analysis/gitfiles/toml11/toml.hpp"

double ApplyCoulombShift(int TruePDG, int NuPDG, int target, int reaction);

void MergeWithWeightsNuAnuBANFF(){
    // TString path = gSystem->GetIncludePath();
    // path.Append("-I /sps/t2k/buizza/ND280/water_v11r31/highland2/numuCCZeroPiAnalysis/v0r0/macros/test");
    // gSystem->SetIncludePath(path);
    //Reco tree
    //Save all the needed info into human readable tree
    
    int Nmax = 2000000;
    bool mirror = false;
    
    TString foutName = "/sps/t2k/jchakran/gundam/inputconfig/OA2022/GundamInputOA2021withSFGD/inputs/mc/SFGD_BANFFFormat_anu_500k_NaturalUnits_goodq3units_flatsplines_fixRS_wCoulombCorrection.root";
    
//     TString foutName = "/sps/t2k/jchakran/xsec-fitter/xsLLhFitter130921/inputs/SFGD_BANFF_Fit/mc/SFGD_BANFFFormat_anu_500k_NaturalUnits_goodq3units.root";
//     TString foutName = "/sps/t2k/jchakran/NScovar/alldials/splines/BANFFFormat_nu_500k.root";
    
    // data (MC) file :
//     string inputfilename1 = "/sps/t2k/sdolan/generators/fromLXPlus/recoTreesForUpgradeStudies/recoTrees/june2021Update_XingyuRecon_1706/neut_sf_t2k_ch_6milStats.root";//neut_sf_t2k_ch_anu_2milStats.root" ; // neut_sf_t2k_ch_6milStats.root
    string inputfilename1 = "/sps/t2k/sdolan/generators/fromLXPlus/recoTreesForUpgradeStudies/recoTrees/june2021Update_XingyuRecon_1706/neut_sf_t2k_ch_anu_2milStats.root";//neut_sf_t2k_ch_anu_2milStats.root" ; // neut_sf_t2k_ch_6milStats.root
    
    // dials file :
//     string inputfilename2 = "/sps/t2k/jchakran/xsec-fitter/weights/fullOA2021/EventWeightGen_OA2021_neut_5.4.0_nd5_CH_SF_MA103_nu_2M_fixT2KRWbug.root" ;
    string inputfilename2 = "/sps/t2k/jchakran/xsec-fitter/weights/fullOA2021/EventWeightGen_OA2021_neut_5.4.0_nd5_CH_SF_MA103_anu_500k_fixT2KRWbug.root" ;
    
    // toml file (.toml):
    std::string config_file = "/sps/t2k/jchakran/xsec-fitter/weights/ND280_OA2021_Config_NoMirroring_Upgrade.toml";
    
    //read file, tree and take useful branches
    TFile * infile1 = new TFile(inputfilename1.c_str(), "OPEN");
    TFile * infile2= new TFile(inputfilename2.c_str(), "OPEN");
    //TTree * input_tree1 = (TTree*) infile->Get("default");
    TString treeName1 ="selectedEvents";
    TString treeName2 ="T2KRWFlatTree";
    TTree * input_tree1 = (TTree*) infile1->Get(treeName1);
    TTree * input_tree2 = (TTree*) infile2->Get(treeName2);
    
    //open root file OUTPUT and branches definition
    TFile *outfile = new TFile(foutName,"RECREATE");
    // output tree
    TTree* outtree = new TTree ("sample_sum","sample_sum");
    
  
    Int_t MAX_VERTEX = 1;
  
    Int_t NVertexID = 1;
    
    Int_t VertexID[MAX_VERTEX];
    Int_t NeutrinoCode[MAX_VERTEX];
    Double_t Enu[MAX_VERTEX];
    
    Double_t TrueNeutrinoDirX;
    Double_t TrueNeutrinoDirY;
    Double_t TrueNeutrinoDirZ;

    Int_t RunNumber;
    Int_t SubRunNumber;
    Int_t EventNumber;

    Int_t TrueLepPDG;
    Double_t TruePmu[MAX_VERTEX];
    Double_t TrueLepMom[MAX_VERTEX];
    Double_t TrueCosThetamu[MAX_VERTEX];
    Double_t TrueLepDirX;
    Double_t TrueLepDirY;
    Double_t TrueLepDirZ;
    Double_t Pmu[MAX_VERTEX];
    Double_t RecoLepMom[MAX_VERTEX];
    Double_t RecoLepDirX;
    Double_t RecoLepDirY;
    Double_t RecoLepDirZ[MAX_VERTEX];
    Double_t CosThetamu[MAX_VERTEX];

    Int_t TruePreFSIPiPDG;
    Double_t TruePreFSIPiMom;
    Double_t TruePreFSIPiDirX;
    Double_t TruePreFSIPiDirY;
    Double_t TruePreFSIPiDirZ;
    Int_t TruePostFSIPiPDG;
    Double_t TruePostFSIPiMom;
    Double_t TruePostFSIPiDirX;
    Double_t TruePostFSIPiDirY;
    Double_t TruePostFSIPiDirZ;
    Double_t RecoPiMom;
    Double_t RecoPiDirX;
    Double_t RecoPiDirY;
    Double_t RecoPiDirZ;
    Int_t RecoPi_Topo;

    Double_t TruePostFSIProtonMom;
    Double_t TruePostFSIProtonDirX;
    Double_t TruePostFSIProtonDirY;
    Double_t TruePostFSIProtonDirZ;
    Int_t TruePostFSIProton_Topo;
    Double_t RecoProtonMom;
    Double_t RecoProtonDirX;
    Double_t RecoProtonDirY;
    Double_t RecoProtonDirZ;
    Int_t RecoProton_Topo;

    Double_t  POTWeight;
    Double_t  PileUpWeight;
    Int_t  isRHC;
    Int_t  passedPsyche;

    Int_t isSRC;
    Double_t Emiss;
    Double_t Pmiss;
    //Double_t DeltaPForEMiss0;

    Double_t q3;
    Double_t q0;

    Int_t ReactionCode[MAX_VERTEX];
    Int_t NuParent[MAX_VERTEX];
    Double_t Q2[MAX_VERTEX];
    Double_t Q2QE[MAX_VERTEX];
    Bool_t HaveTruth[MAX_VERTEX];
    Int_t TgtMat[MAX_VERTEX];
    Double_t FluxWeight[MAX_VERTEX];
    Int_t TruthVtx[MAX_VERTEX];

    Int_t Run;
    int fToys = 1;

    Int_t NSamples = -999;
    Int_t SelectedSample = 0;
    double DetNomWeight;
    double NIWGWeightToy[fToys];
    Int_t iVertexID[fToys];
    
    Double_t psycheSyst_TrueEnuNom[fToys];
    Int_t psycheSyst_TrueVertexIDToy[fToys];
    Int_t psycheSyst_SelectionToy[fToys];
    Double_t psycheSyst_LeptonMomToy[fToys];
    Double_t psycheSyst_LeptonCosToy[fToys];
    Double_t psycheSyst_WeightToy[fToys];
    
    Int_t reaction;
    Double_t D1True, D2True;
    Double_t D1Reco, D2Reco;
    
    bool isConsecutiveIdenticalEvent = false;
    double PmuCoulombCorrection;
    
    // Helper variables
    
    Double_t mn = 939.56536;
    Double_t mp = 938.27203; // proton and neutron masses
    Double_t ma = 6*mn + 6*mp - 92.16; // target mass
    Double_t map = ma - mn + 27.13; // remnant mass
    Double_t ml = 105.65837 ; // lepton mass 
        
    Double_t pnuclx = 0;
    Double_t pnucly = 0;
    Double_t pnuclz = 0;
    Double_t enucl = 0;
    
    Double_t plx = 0;
    Double_t ply = 0;
    Double_t plz = 0;
    Double_t el = 0;

    /////////// part to read toml file :
    
    auto const &card_toml = toml::parse(config_file); // parse file
    auto const &reweights = toml::find(card_toml, "reweights"); // get "reweights" table
    // auto const &variations = toml::find(card_toml, "variations"); // get "variations" table (empty for now)
    
    std::vector<std::string> dial_names; // vector to store the dial names
    std::vector<std::vector<double>> dial_tweaks; // a vector of the dial values for each dial
    std::vector<std::vector<double>> dial_ToValue; // a vector of the dial values for each dial
    std::vector<TClonesArray *> dial_graphs;

    // Read from the file
    
    for (auto const &dg : toml::find<std::vector<std::string>>(reweights, "dials")) { // loop over "reweights" table first entry
        for (auto const &d : toml::find<toml::array>(reweights, dg)) { // loop over the other "reweights" table entries
            
            //auto dial_name = toml::find<std::string>(d, 0); // the first element of the entry is the dial name
            auto dial_name = dg;
            auto dial_values = toml::find<std::vector<double>>(d, 1); // the second element is an array of dial variations
            
            dial_names.push_back(dial_name);
            dial_tweaks.push_back(dial_values);
            TClonesArray *temp_graph = new TClonesArray("TGraph", MAX_VERTEX);
            dial_graphs.push_back(temp_graph);
        }
    }
    
    TTreeReader reader0("TweakMetaData", infile2); 

    for (int sys_iter = 0 ; sys_iter < dial_names.size() ; sys_iter++){
        
        TTreeReaderArray<double> dialbuff = {reader0, dial_names[sys_iter].c_str()};
        
        std::vector<double> tweaks;
        reader0.Next();
        
        for (int twk_iter = 0 ; twk_iter < dial_tweaks[sys_iter].size() ; twk_iter++){
            tweaks.push_back(dialbuff[twk_iter]);
        }
        
        std::sort(tweaks.begin(), tweaks.end());
        
        dial_ToValue.emplace_back(tweaks);
        
        reader0.Restart();

    }
    
    
    // weights : dial_values[i]
    for(auto const &name : dial_names){
        cout << name << endl;        
    }
    
    // Output tree
    TTree ssum_tree("sample_sum", "Tracker Numu Summary");

    ssum_tree.Branch("NVertexID", &NVertexID, "NVertexID/I");
    ssum_tree.Branch("MAX_VERTEX", &MAX_VERTEX, "MAX_VERTEX/I");
    ssum_tree.Branch("VertexID", VertexID, "VertexID[MAX_VERTEX]/I");
    ssum_tree.Branch("NSamples", &NSamples, "NSamples/I");
    ssum_tree.Branch("SelectedSample", &SelectedSample, "SelectedSample/I");
    ssum_tree.Branch("Run", &Run, "Run/I");

    ssum_tree.Branch("RunNumber", &RunNumber, "RunNumber/I");
    ssum_tree.Branch("SubRunNumber", &SubRunNumber, "SubRunNumber/I");
    ssum_tree.Branch("EventNumber", &EventNumber, "EventNumber/I");
    ssum_tree.Branch("DetNomWeight", &DetNomWeight, "DetNomWeight/D");

    ssum_tree.Branch("NeutrinoCode", NeutrinoCode, "NeutrinoCode[MAX_VERTEX]/I");
    ssum_tree.Branch("Enu", Enu, "Enu[MAX_VERTEX]/D");
    ssum_tree.Branch("TrueNeutrinoDirX", &TrueNeutrinoDirX, "TrueNeutrinoDirX/D");
    ssum_tree.Branch("TrueNeutrinoDirY", &TrueNeutrinoDirY, "TrueNeutrinoDirY/D");
    ssum_tree.Branch("TrueNeutrinoDirZ", &TrueNeutrinoDirZ, "TrueNeutrinoDirZ/D");

    ssum_tree.Branch("TrueLepPDG", &TrueLepPDG, "TrueLepPDG/I");
    ssum_tree.Branch("TruePmu", TruePmu, "TruePmu[MAX_VERTEX]/D");
    ssum_tree.Branch("TrueLepDirX", &TrueLepDirX, "TrueLepDirX/D");
    ssum_tree.Branch("TrueLepDirY", &TrueLepDirY, "TrueLepDirY/D");
    ssum_tree.Branch("TrueLepDirZ", &TrueLepDirZ, "TrueLepDirZ/D");
    ssum_tree.Branch("TrueCosThetamu", TrueCosThetamu,
               "TrueCosThetamu[MAX_VERTEX]/D");

    ssum_tree.Branch("Pmu", Pmu, "Pmu[MAX_VERTEX]/D");
    ssum_tree.Branch("RecoLepDirX", &RecoLepDirX, "RecoLepDirX/D");
    ssum_tree.Branch("RecoLepDirY", &RecoLepDirY, "RecoLepDirY/D");
    ssum_tree.Branch("RecoLepDirZ", RecoLepDirZ, "RecoLepDirZ[MAX_VERTEX]/D");
    ssum_tree.Branch("CosThetamu", CosThetamu, "CosThetamu[MAX_VERTEX]/D");

    ssum_tree.Branch("TruePostFSIPiPDG", &TruePostFSIPiPDG, "TruePostFSIPiPDG/I");
    ssum_tree.Branch("TruePostFSIPiMom", &TruePostFSIPiMom, "TruePostFSIPiMom/D");
    ssum_tree.Branch("TruePostFSIPiDirX", &TruePostFSIPiDirX, "TruePostFSIPiDirX/D");
    ssum_tree.Branch("TruePostFSIPiDirY", &TruePostFSIPiDirY, "TruePostFSIPiDirY/D");
    ssum_tree.Branch("TruePostFSIPiDirZ", &TruePostFSIPiDirZ, "TruePostFSIPiDirZ/D");
    ssum_tree.Branch("TruePreFSIPiPDG", &TruePreFSIPiPDG, "TruePreFSIPiPDG/I");
    ssum_tree.Branch("TruePreFSIPiMom", &TruePreFSIPiMom, "TruePreFSIPiMom/D");
    ssum_tree.Branch("TruePreFSIPiDirX", &TruePreFSIPiDirX, "TruePreFSIPiDirX/D");
    ssum_tree.Branch("TruePreFSIPiDirY", &TruePreFSIPiDirY, "TruePreFSIPiDirY/D");
    ssum_tree.Branch("TruePreFSIPiDirZ", &TruePreFSIPiDirZ, "TruePreFSIPiDirZ/D");
    ssum_tree.Branch("RecoPiMom", &RecoPiMom, "RecoPiMom/D");
    ssum_tree.Branch("RecoPiDirX", &RecoPiDirX, "RecoPiDirX/D");
    ssum_tree.Branch("RecoPiDirY", &RecoPiDirY, "RecoPiDirY/D");
    ssum_tree.Branch("RecoPiDirZ", &RecoPiDirZ, "RecoPiDirZ/D");
    ssum_tree.Branch("RecoPi_Topo", &RecoPi_Topo, "RecoPi_Topo/I");

    ssum_tree.Branch("TruePostFSIProtonMom", &TruePostFSIProtonMom, "TruePostFSIProtonMom/D");
    ssum_tree.Branch("TruePostFSIProtonDirX", &TruePostFSIProtonDirX, "TruePostFSIProtonDirX/D");
    ssum_tree.Branch("TruePostFSIProtonDirY", &TruePostFSIProtonDirY, "TruePostFSIProtonDirY/D");
    ssum_tree.Branch("TruePostFSIProtonDirZ", &TruePostFSIProtonDirZ, "TruePostFSIProtonDirZ/D");
    ssum_tree.Branch("TruePostFSIProton_Topo", &TruePostFSIProton_Topo, "TruePostFSIProton_Topo/I");
    ssum_tree.Branch("RecoProtonMom", &RecoProtonMom, "RecoProtonMom/D");
    ssum_tree.Branch("RecoProtonDirX", &RecoProtonDirX, "RecoProtonDirX/D");
    ssum_tree.Branch("RecoProtonDirY", &RecoProtonDirY, "RecoProtonDirY/D");
    ssum_tree.Branch("RecoProtonDirZ", &RecoProtonDirZ, "RecoProtonDirZ/D");
    ssum_tree.Branch("RecoProton_Topo", &RecoProton_Topo, "RecoProton_Topo/I");

    ssum_tree.Branch("POTWeight", &POTWeight, "POTWeight/D");
    ssum_tree.Branch("PileUpWeight", &PileUpWeight, "PileUpWeight/D");
    ssum_tree.Branch("isRHC", &isRHC, "isRHC/I");
    ssum_tree.Branch("passedPsyche", &passedPsyche, "passedPsyche/I");

    ssum_tree.Branch("ReactionCode", ReactionCode, "ReactionCode[MAX_VERTEX]/I");
    ssum_tree.Branch("NuParent", NuParent, "NuParent[MAX_VERTEX]/I");
    ssum_tree.Branch("Q2", Q2, "Q2[MAX_VERTEX]/D");
    ssum_tree.Branch("Q2QE", Q2QE, "Q2QE[MAX_VERTEX]/D");
    ssum_tree.Branch("HaveTruth", HaveTruth, "HaveTruth[MAX_VERTEX]/B");
    ssum_tree.Branch("TgtMat", TgtMat, "TgtMat[MAX_VERTEX]/I");
    ssum_tree.Branch("FluxWeight", FluxWeight, "FluxWeight[MAX_VERTEX]/D");
    ssum_tree.Branch("TruthVtx", TruthVtx, "TruthVtx[MAX_VERTEX]/I");

    ssum_tree.Branch("q3", &q3, "q3/D");
    ssum_tree.Branch("q0", &q0, "q0/D");

    ssum_tree.Branch("isSRC", &isSRC, "isSRC/I");
    ssum_tree.Branch("Emiss", &Emiss, "Emiss/D");
    ssum_tree.Branch("Pmiss", &Pmiss, "Pmiss/D");
    ssum_tree.Branch("reaction", &reaction, "reaction/I");
    
    ssum_tree.Branch("D1True", &D1True, "D1True/D");
    ssum_tree.Branch("D2True", &D2True, "D2True/D");
    ssum_tree.Branch("D1Reco", &D1Reco, "D1Reco/D");
    ssum_tree.Branch("D2Reco", &D2Reco, "D2Reco/D");

    ssum_tree.Branch("PmuCoulombCorrection", &PmuCoulombCorrection, "PmuCoulombCorrection/D");
    ssum_tree.Branch("isConsecutiveIdenticalEvent", &isConsecutiveIdenticalEvent, "isConsecutiveIdenticalEvent/O");

    //ssum_tree.Branch("DeltaPForEMiss0", &DeltaPForEMiss0, "DeltaPForEMiss0/D");

    /*
    ssum_tree.Branch("T2KRW_nToys", &fToys, "T2KRW_nToys/I");
    ssum_tree.Branch("T2KRW_NIWGWeightToy", NIWGWeightToy,
               "T2KRW_NIWGWeightToy[T2KRW_nToys]/D");
    ssum_tree.Branch("Toy_TrueEnuNom", &psycheSyst_TrueEnuNom,
               "psycheSyst_TrueEnuNom/D");
    ssum_tree.Branch("Toy_TrueVertexID", psycheSyst_TrueVertexIDToy,
               "psycheSyst_TrueVertexIDToy[T2KRW_nToys]/I");
    ssum_tree.Branch("Toy_Selection", psycheSyst_SelectionToy,
               "psycheSyst_SelectionToy[T2KRW_nToys]/I");
    ssum_tree.Branch("Toy_iVertexID", iVertexID,
               "psycheSyst_iVertexID[T2KRW_nToys]/I");
    ssum_tree.Branch("Toy_LeptonMom", psycheSyst_LeptonMomToy,
               "psycheSyst_LeptonMomToy[T2KRW_nToys]/D");
    ssum_tree.Branch("Toy_LeptonCos", psycheSyst_LeptonCosToy,
               "psycheSyst_LeptonCosToy[T2KRW_nToys]/D");
    ssum_tree.Branch("Toy_DetWeight", psycheSyst_WeightToy,
               "psycheSyst_WeightToy[T2KRW_nToys]/D");
*/

    for (unsigned int i = 0; i < dial_graphs.size(); i++) {
    ssum_tree.Branch(Form("%sGraph", dial_names[i].c_str()), "TClonesArray",
                 &(dial_graphs[i]), 256000, 0);
    }

    // dials branches done after TTReaderValue declaration (see below (*))
    
    // INPUT readers
    TTreeReader reader1("selectedEvents", infile1); 
    TTreeReader reader2("T2KRWFlatTree", infile2); 

    TTreeReaderValue<Int_t> Mode_1 = {reader1, "Mode"};
    TTreeReaderValue<Int_t> TargetA_1 = {reader1, "TargetA"};
    TTreeReaderValue<Int_t> TargetZ_1 = {reader1, "TargetZ"};
    TTreeReaderValue<Int_t> PDGnu_1 = {reader1, "PDGnu"};
    TTreeReaderValue<Float_t> Enu_true_1 = {reader1, "Enu_true"};
    TTreeReaderValue<Int_t> isTrueChargedLepton_1 = {reader1, "isTrueChargedLepton"};
    TTreeReaderValue<Int_t> Nleptons_1 = {reader1, "Nleptons"};
    TTreeReaderValue<Int_t> Nprotons_1 = {reader1, "Nprotons"};
    TTreeReaderValue<Int_t> Nneutrons_1 = {reader1, "Nneutrons"};
    TTreeReaderValue<Int_t> Npiplus_1 = {reader1, "Npiplus"};
    TTreeReaderValue<Int_t> Npineg_1 = {reader1, "Npineg"};
    TTreeReaderValue<Int_t> Npi0_1 = {reader1, "Npi0"};
    TTreeReaderValue<Int_t> Nother_1 = {reader1, "Nother"};
    TTreeReaderValue<Float_t> Erecoil_true_1 = {reader1, "Erecoil_true"};
    TTreeReaderValue<Float_t> Erecoil_charged_1 = {reader1, "Erecoil_charged"};
    TTreeReaderValue<Float_t> Erecoil_minerva_1 = {reader1, "Erecoil_minerva"};
    TTreeReaderValue<Float_t> Weight_1 = {reader1, "Weight"};
    TTreeReaderValue<Float_t> InputWeight_1 = {reader1, "InputWeight"};
    TTreeReaderValue<Float_t> RWWeight_1 = {reader1, "RWWeight"};
    TTreeReaderValue<Float_t> FluxWeight_1 = {reader1, "FluxWeight"};
    TTreeReaderValue<Double_t> fScaleFactor_1 = {reader1, "fScaleFactor"};
    TTreeReaderValue<TLorentzVector> nu_4mom_1 = {reader1, "nu_4mom"};
    TTreeReaderValue<TLorentzVector> pmu_4mom_1 = {reader1, "pmu_4mom"};
    TTreeReaderValue<TLorentzVector> hm_ppip_4mom_1 = {reader1, "hm_ppip_4mom"};
    TTreeReaderValue<TLorentzVector> hm_ppim_4mom_1 = {reader1, "hm_ppim_4mom"};
    TTreeReaderValue<TLorentzVector> hm_ppi0_4mom_1 = {reader1, "hm_ppi0_4mom"};
    TTreeReaderValue<TLorentzVector> hm_pprot_4mom_1 = {reader1, "hm_pprot_4mom"};
    TTreeReaderValue<TLorentzVector> shm_pprot_4mom_1 = {reader1, "shm_pprot_4mom"};
    TTreeReaderValue<TLorentzVector> hm_pneut_4mom_1 = {reader1, "hm_pneut_4mom"};
    TTreeReaderValue<TLorentzVector> hm_ppip_4mom_vect_1 = {reader1, "hm_ppip_4mom_vect"};
    TTreeReaderValue<TLorentzVector> hm_ppim_4mom_vect_1 = {reader1, "hm_ppim_4mom_vect"};
    TTreeReaderValue<TLorentzVector> hm_ppi0_4mom_vect_1 = {reader1, "hm_ppi0_4mom_vect"};
    TTreeReaderValue<TLorentzVector> hm_pprot_4mom_vect_1 = {reader1, "hm_pprot_4mom_vect"};
    TTreeReaderValue<TLorentzVector> shm_pprot_4mom_vect_1 = {reader1, "shm_pprot_4mom_vect"};
    TTreeReaderValue<TLorentzVector> hm_pneut_4mom_vect_1 = {reader1, "hm_pneut_4mom_vect"};
    TTreeReaderValue<TLorentzVector> hm_ISQE_nucl_4mom_1 = {reader1, "hm_ISQE_nucl_4mom"};
    TTreeReaderValue<TLorentzVector> pmu_reco_4mom_1 = {reader1, "pmu_reco_4mom"};
    TTreeReaderValue<TLorentzVector> hm_ppip_reco_4mom_1 = {reader1, "hm_ppip_reco_4mom"};
    TTreeReaderValue<TLorentzVector> hm_ppim_reco_4mom_1 = {reader1, "hm_ppim_reco_4mom"};
    TTreeReaderValue<TLorentzVector> hm_pprot_reco_4mom_1 = {reader1, "hm_pprot_reco_4mom"};
    TTreeReaderValue<TLorentzVector> shm_pprot_reco_4mom_1 = {reader1, "shm_pprot_reco_4mom"};
    TTreeReaderValue<TLorentzVector> hm_pneut_reco_4mom_1 = {reader1, "hm_pneut_reco_4mom"};
    TTreeReaderValue<Bool_t> isRecoChargedLepton_1 = {reader1, "isRecoChargedLepton"};
    TTreeReaderValue<Bool_t> isRecoProton_1 = {reader1, "isRecoProton"};
    TTreeReaderValue<Bool_t> isRecoNeutron_1 = {reader1, "isRecoNeutron"};
    TTreeReaderValue<Bool_t> isRecoPip_1 = {reader1, "isRecoPip"};
    TTreeReaderValue<Bool_t> isRecoPim_1 = {reader1, "isRecoPim"};
    TTreeReaderValue<Bool_t> flagCCINC_1 = {reader1, "flagCCINC"};
    TTreeReaderValue<Bool_t> flagNCINC_1 = {reader1, "flagNCINC"};
    TTreeReaderValue<Bool_t> flagCC0pi_1 = {reader1, "flagCC0pi"};
    TTreeReaderValue<Bool_t> flagNC0pi_1 = {reader1, "flagNC0pi"};
    TTreeReaderValue<Bool_t> flagCC1pip_1 = {reader1, "flagCC1pip"};
    TTreeReaderValue<Bool_t> flagNC1pip_1 = {reader1, "flagNC1pip"};
    TTreeReaderValue<Bool_t> flagCC1pim_1 = {reader1, "flagCC1pim"};
    TTreeReaderValue<Bool_t> flagNC1pim_1 = {reader1, "flagNC1pim"};
    TTreeReaderValue<Bool_t> flagCC1pi0_1 = {reader1, "flagCC1pi0"};
    TTreeReaderValue<Char_t> flagNC1pi0_1 = {reader1, "flagNC1pi0"};
    
    // Templates (weights)
    std::vector<TTreeReaderValue<std::vector<double>>> dial_input_vars;
    std::vector<std::vector<double>> dial_output_vars(dial_names.size(), std::vector<double>(dial_tweaks[0].size(), -999.9));
    std::vector<TGraph*> graphs(dial_names.size(), new TGraph());
    std::vector<TSpline3> splines(dial_names.size(), TSpline3());

    for(int i=0; i<dial_names.size(); i++){
        TTreeReaderValue<std::vector<double>> dial_input_var = {reader2, dial_names[i].c_str()};
        dial_input_vars.push_back(dial_input_var);
        std::vector<double> dial_output_var;
        dial_output_vars.push_back(dial_output_var);
        //graphs[i] = new TGraph();
        //ssum_tree.Branch((dial_names[i] + "Graph").c_str(), &graphs[i]); // graphs (*)
    }
    
    TTreeReaderValue<TLorentzVector> PISNu_2 = {reader2, "PISNu"};
    TTreeReaderValue<Float_t> Emiss_2 = {reader2, "Emiss"};
    TTreeReaderValue<Float_t> Pmiss_2 = {reader2, "Pmiss"};
    TTreeReaderValue<bool> isSRC_2 = {reader2, "isSRC"};
    

    int k = 0;
    double enu_1=0;
    while (reader1.Next() && reader2.Next()){
        k++;
        if (k > Nmax) break;

        if (k%50000 == 0) cout << PISNu_2->E()*1000 << " = " << *Enu_true_1 << " : " <<  k << "/" << Nmax << endl;

        // Match events from the two files with their Enu
        
        if (abs(PISNu_2->E()*1000 - *Enu_true_1)>1E-3){
            
            cout << "Error : two different values of neutrino energy." <<endl;
            cout << PISNu_2->E()*1000 << " != " << *Enu_true_1 << " : " <<  k << "/" << Nmax << endl;
            cout << "Let's look for the matching event." << endl;
            
            while (abs(PISNu_2->E()*1000 - *Enu_true_1)>1E-3){
                reader1.Next();
                cout << PISNu_2->E()*1000 << " != " << *Enu_true_1 << " : " <<  k << "/" << Nmax << endl;
            }
            
            cout << "Found: " <<  PISNu_2->E()*1000 << " = " << *Enu_true_1 << " : " <<  k << "/" << Nmax << endl;
        }
        
        if(!*isRecoChargedLepton_1) continue; // Skip non-CC events
        
        // Reinitialize 
        for (int sample = 0; sample < MAX_VERTEX; ++sample) {

            for (unsigned int sys_iter = 0; sys_iter < dial_names.size(); sys_iter++) {
                
                TGraph *graph = (TGraph *)dial_graphs[sys_iter]->ConstructedAt(sample);
                
                graph->SetName(Form("%s_gr", dial_names[sys_iter].c_str()));
                
                for (int piter = (graph->GetN() - 1); piter >= 0; piter--)
                    graph->RemovePoint(piter);
                
                graph->SetPoint(0, 0.0, 1.0);
            }

            VertexID[sample] = -999;
            NeutrinoCode[sample] = -999;
            Enu[sample] = -999;

            TrueLepMom[sample] = -999;
            TrueCosThetamu[sample] = -999;

            RecoLepDirZ[sample] = -999;
            RecoLepMom[sample] = -999;

            ReactionCode[sample] = -999;
            NuParent[sample] = -999;
            Q2[sample] = -999;
            Q2QE[sample] = -999;
            HaveTruth[sample] = false;
            TgtMat[sample] = -999;
            FluxWeight[sample] = -999;
            TruthVtx[sample] = -999;
        }

        for (int iToy = 0; iToy < fToys; iToy++) {
          NIWGWeightToy[iToy] = -999;
          iVertexID[iToy] = -999;
          psycheSyst_TrueVertexIDToy [iToy] = -999;
          psycheSyst_LeptonMomToy    [iToy] = -999;
          psycheSyst_LeptonCosToy    [iToy] = -999;
          psycheSyst_WeightToy       [iToy] = -999;
          psycheSyst_TrueEnuNom      [iToy] = -999;
          psycheSyst_SelectionToy    [iToy] = -999;
        }

        TrueNeutrinoDirX = -999;
        TrueNeutrinoDirY = -999;
        TrueNeutrinoDirZ = -999;

        TrueLepPDG = -999;
        TrueLepDirX = -999;
        TrueLepDirY = -999;
        TrueLepDirZ = -999;
        RecoLepDirX = -999;
        RecoLepDirY = -999;

        TruePostFSIPiPDG = -999;
        TruePostFSIPiMom = -999;
        TruePostFSIPiDirX = -999;
        TruePostFSIPiDirY = -999;
        TruePostFSIPiDirZ = -999;
        TruePreFSIPiPDG = -999;
        TruePreFSIPiMom = -999;
        TruePreFSIPiDirX = -999;
        TruePreFSIPiDirY = -999;
        TruePreFSIPiDirZ = -999;
        RecoPiMom = -999;
        RecoPiDirX = -999;
        RecoPiDirY = -999;
        RecoPiDirZ = -999;
        RecoPi_Topo = -999;

        TruePostFSIProtonMom = -9999;
        TruePostFSIProtonDirX = -9999;
        TruePostFSIProtonDirY = -9999;
        TruePostFSIProtonDirZ = -9999;
        RecoProtonMom = -999;
        RecoProtonDirX = -999;
        RecoProtonDirY = -999;
        RecoProtonDirZ = -999;
        RecoProton_Topo = -999;

        isSRC = (*isSRC_2);
        Emiss = -999;
        Pmiss =  -999;

        q0 =  -999;
        q3 =  -999;

        DetNomWeight = -999;
        POTWeight = -999;
        PileUpWeight = -999;
        isRHC = -999;
        passedPsyche = -999;

        SelectedSample = -999;
        NSamples = -999;
        
        reaction = 8;
        // Define the relevant variables
        
        // 1. isRHC
        
        isRHC = (*PDGnu_1 > 0) ? 0 : 1;
        
        // 2. SelectedSample
        
        // 101: FHC SFGD numu CC0pi 0p
        // 102: FHC SFGD numu CC0pi Np
        // 103: FHC SFGD numu CC1pi 0p
        // 104: FHC SFGD numu CC1pi Np
        // 105: FHC SFGD numu CCOth 0p
        // 106: FHC SFGD numu CCOth Np
        // 111: RHC SFGD numubar CC0pi 0n
        // 112: RHC SFGD numubar CC0pi Nn
        // 113: RHC SFGD numubar CC1pi 0n
        // 114: RHC SFGD numubar CC1pi Nn
        // 115: RHC SFGD numubar CCOth 0n
        // 116: RHC SFGD numubar CCOth Nn
        
        if (*isRecoChargedLepton_1 && !*isRecoPip_1 && !*isRecoPim_1 && *Npi0_1 == 0) {
            // CC0pi
            
            if (*PDGnu_1 == 14 && !*isRecoProton_1){
                // FHC numu CC0pi 0p
                SelectedSample = 101;
            }
            if (*PDGnu_1 == 14 && *isRecoProton_1){
                // FHC numu CC0pi Np
                SelectedSample = 102;
            }
            if (*PDGnu_1 == -14 && !*isRecoNeutron_1){
                // RHC numubar CC0pi 0n
                SelectedSample = 111;
            }
            if (*PDGnu_1 == -14 && *isRecoNeutron_1){
                // RHC numubar CC0pi Nn
                SelectedSample = 112;
            }
        }
        
        else if (*PDGnu_1 == 14 && *isRecoChargedLepton_1 &&  *isRecoPip_1 && !*isRecoPim_1 && *Npi0_1 == 0) {
            // FHC numu CC1pi+
            
            if (!*isRecoProton_1) {
                // FHC numu CC1pi+ 0p
                SelectedSample = 103;
            }
            if (*isRecoProton_1) {
                // FHC numu CC1pi+ Np
                SelectedSample = 104;
            }
        }
        
        else if (*PDGnu_1 == -14 && *isRecoChargedLepton_1 &&  !*isRecoPip_1 && *isRecoPim_1 && *Npi0_1 == 0) {
            // RHC numubar CC1pi-
            
            if (!*isRecoNeutron_1) {
                // RHC numubar CC1pi- 0p
                SelectedSample = 113;
            }
            if (*isRecoNeutron_1) {
                // RHC numubar CC1pi- Np
                SelectedSample = 114;
            }
        }
        
        else if (*PDGnu_1 == 14 && *isRecoChargedLepton_1) {
            // FHC SFGD numu CCOth
            
            if (!*isRecoProton_1) {
                // FHC SFGD numu CCOth 0p
                SelectedSample = 105;
            }
            if (*isRecoProton_1) {
                // FHC SFGD numu CCOth Np
                SelectedSample = 106;
            }
        }
        
        else if (*PDGnu_1 == -14 && *isRecoChargedLepton_1) {
            // RHC numubar CC1pi-
            
            if (!*isRecoNeutron_1) {
                // RHC numubar CC1pi- 0p
                SelectedSample = 115;
            }
            if (*isRecoNeutron_1) {
                // RHC numubar CC1pi- Np
                SelectedSample = 116;
            }            
        }
        
        else {
            SelectedSample = -999;
        }
        
        
        // All the variables
        
        for (int sample = 0; sample < MAX_VERTEX; ++sample) {
            VertexID[sample] = -999;
            
            NeutrinoCode[sample] = *PDGnu_1;
            Enu[sample] = nu_4mom_1->E() / 1000.;

            
            ReactionCode[sample] = *Mode_1;
            NuParent[sample] = -999;
            Q2[sample] = - (*pmu_4mom_1  - *nu_4mom_1).Mag2() / 1000000.;
            Q2QE[sample] = -999;
            HaveTruth[sample] = true;
            
            TgtMat[sample] = 12;
            
            FluxWeight[sample] = 1.;
            TruthVtx[sample] = -999;
            TruePmu[sample] = pmu_4mom_1->Rho();
            TrueCosThetamu[sample]  = pmu_4mom_1->Vect().CosTheta();
            Pmu[sample] = pmu_reco_4mom_1->Rho();
            CosThetamu[sample] = pmu_reco_4mom_1->Vect().CosTheta();
            //cout << pmu_reco_4mom_1->Rho() << "   " << Pmu[0] << endl;

            TrueLepMom[sample] = pmu_4mom_1->Rho() / 1000.;
            TrueCosThetamu[sample] = pmu_4mom_1->Vect().CosTheta();
            RecoLepMom[sample] = pmu_reco_4mom_1->Rho() / 1000.;
            RecoLepDirZ[sample] = pmu_reco_4mom_1->Vect().CosTheta();
        }

        PmuCoulombCorrection = Pmu[0];
        PmuCoulombCorrection += ApplyCoulombShift(Pmu[0], NeutrinoCode[0], 12, ReactionCode[0]);
        
        TrueNeutrinoDirX = nu_4mom_1->Vect().X() / nu_4mom_1->Vect().Mag();
        TrueNeutrinoDirY = nu_4mom_1->Vect().Y() / nu_4mom_1->Vect().Mag();
        TrueNeutrinoDirZ = nu_4mom_1->Vect().Z() / nu_4mom_1->Vect().Mag();

        TrueLepDirX = pmu_4mom_1->Vect().X() / pmu_4mom_1->Vect().Mag();
        TrueLepDirY = pmu_4mom_1->Vect().Y() / pmu_4mom_1->Vect().Mag();
        TrueLepDirZ = pmu_4mom_1->Vect().Z() / pmu_4mom_1->Vect().Mag();
        RecoLepDirX = pmu_reco_4mom_1->Vect().X() / pmu_reco_4mom_1->Vect().Mag();
        RecoLepDirY = pmu_reco_4mom_1->Vect().Y() / pmu_reco_4mom_1->Vect().Mag();

        Emiss = *Emiss_2;
        Pmiss = *Pmiss_2;
        
        q0 =  - (*pmu_4mom_1  - *nu_4mom_1).Vect().Mag();
        q3 =  - (*pmu_4mom_1  - *nu_4mom_1).E();

        TruePostFSIProton_Topo = (*Nprotons_1); 
        TruePostFSIProtonMom = (*Nprotons_1>0) ? hm_pprot_4mom_1->Vect().Mag() : -9999;
        TruePostFSIProtonDirX = (*Nprotons_1>0) ? hm_pprot_4mom_1->Vect().X()/hm_pprot_4mom_1->Vect().Mag() : -9999;
        TruePostFSIProtonDirY = (*Nprotons_1>0) ? hm_pprot_4mom_1->Vect().Y()/hm_pprot_4mom_1->Vect().Mag() : -9999;
        TruePostFSIProtonDirZ = (*Nprotons_1>0) ? hm_pprot_4mom_1->Vect().Z()/hm_pprot_4mom_1->Vect().Mag() : -9999;
        
        DetNomWeight = 1.;
        POTWeight = 1.;
        PileUpWeight = 1.;

        if (abs(ReactionCode[0]) < 70 && abs(ReactionCode[0]) > 30) reaction = 4;

        else if (abs(NeutrinoCode[0]) == 12) reaction = 6;

        else if (isRHC == 1 && NeutrinoCode[0] == 14 ) reaction = 5;

        else if (isRHC == 0 && NeutrinoCode[0] == -14 ) reaction = 5;

        else if (abs(NeutrinoCode[0]) == 14) {

            if (abs(ReactionCode[0]) == 1) reaction = 0;
            else if (abs(ReactionCode[0]) == 2) reaction = 9;
            else if (abs(ReactionCode[0]) < 14 && abs(ReactionCode[0]) > 10) reaction = 1;
            else if (abs(ReactionCode[0]) == 17) reaction = 1;
            else if (abs(ReactionCode[0]) == 22) reaction = 1;
            else if (abs(ReactionCode[0]) == 23) reaction = 1;
            else if (abs(ReactionCode[0]) < 30 && abs(ReactionCode[0]) > 16) reaction = 2;
            else if (abs(ReactionCode[0]) == 16) reaction = 3;

        }

        else reaction = 8;

        
        pnuclx = (*PDGnu_1 > 0) ? hm_pprot_reco_4mom_1->X() : hm_pneut_reco_4mom_1->X() ;
        pnucly = (*PDGnu_1 > 0) ? hm_pprot_reco_4mom_1->Y() : hm_pneut_reco_4mom_1->Y() ;
        pnuclz = (*PDGnu_1 > 0) ? hm_pprot_reco_4mom_1->Z() : hm_pneut_reco_4mom_1->Z() ;
        enucl  = (*PDGnu_1 > 0) ? hm_pprot_reco_4mom_1->E() : hm_pneut_reco_4mom_1->E() ;
        plx = pmu_reco_4mom_1->X();
        ply = pmu_reco_4mom_1->Y();
        plz = pmu_reco_4mom_1->Z();
        el  = pmu_reco_4mom_1->E();
        
        double mnucl = (*PDGnu_1 > 0) ? mp : mn;

        if( (*PDGnu_1 > 0 && *isRecoProton_1) || (*PDGnu_1 < 0 && *isRecoNeutron_1) ){ //if lepton and nucleon
            
            // compute stv.    
            D2Reco = TMath::Sqrt( (pnuclx + plx)*(pnuclx + plx) + (pnucly + ply )*(pnucly + ply) );
            D2True = (*PDGnu_1 > 0) ? ( hm_pprot_4mom_1->Vect() + pmu_4mom_1->Vect() ).Perp() : ( hm_pneut_4mom_1->Vect() + pmu_4mom_1->Vect() ).Perp();
            // visible energy
            D1Reco = el + enucl - mnucl;
            D1True = (*PDGnu_1 > 0) ? hm_pprot_4mom_1->E() + pmu_4mom_1->E() - mnucl : hm_pneut_4mom_1->E() + pmu_4mom_1->E() - mnucl;
        }
        
        else{
            D1Reco = PmuCoulombCorrection;
            D2Reco = CosThetamu[0];
            D1True = TruePmu[0];
            D2True = TrueCosThetamu[0];
        } 
        // Iterate through the systematics to make splines
        
        Double_t weight = 1.0;

        for(unsigned int sys_iter = 0; sys_iter < dial_graphs.size(); sys_iter++) {
            
            dial_output_vars[sys_iter] = *dial_input_vars[sys_iter].Get();
            
            TGraph *graph = (TGraph *)dial_graphs[sys_iter]->ConstructedAt(0);
            
            graph->SetName(Form("%s_gr", dial_names[sys_iter].c_str()));
            graphs[sys_iter]->SetName(Form("%s_gr", dial_names[sys_iter].c_str()));
            
            for (int piter = (graph->GetN() - 1); piter >= 0; piter--)
                graph->RemovePoint(piter);
            for (int piter = (graphs[sys_iter]->GetN() - 1); piter >= 0; piter--)
                graphs[sys_iter]->RemovePoint(piter);            
            bool isFlat = true;
            
            for (unsigned int dial_iter = 0; dial_iter < dial_tweaks[sys_iter].size(); dial_iter++) 
            {
                weight = dial_output_vars[sys_iter][dial_iter];
                
                // Check if response is flat
                if (std::fabs(weight - 1.0) > 1.e-5) isFlat = false;
                
                // Mirror some dials: To be done if needed
                if (mirror){
                
                    if (dial_names[sys_iter] == "PDD_C"    ||
                        dial_names[sys_iter] == "PDD_O"    ||
                        dial_names[sys_iter] == "PDD_C_np" ||
                        dial_names[sys_iter] == "PDD_C_NN" ||
                        dial_names[sys_iter] == "PDD_O_np" ||
                        dial_names[sys_iter] == "PDD_O_NN" ){ // 2p2h Shape
                        
                        double x_val = dial_tweaks[sys_iter][dial_iter];  
                        if (dial_iter < 3) x_val = -2-x_val;
                        if (dial_iter > 9) x_val = 2-x_val;
                        graph->SetPoint(dial_iter, x_val, weight);
                        
                    }

                    if (dial_names[sys_iter] == "RES_Eb_C_numu"    || 
                        dial_names[sys_iter] == "RES_Eb_O_numu"    || 
                        dial_names[sys_iter] == "RES_Eb_C_numubar" || 
                        dial_names[sys_iter] == "RES_Eb_O_numubar" ){ // RES Eb
                        
                        
                        
                    }
                    
                    if (dial_names[sys_iter] == "MEC_lowEnu"     || 
                        dial_names[sys_iter] == "MEC_highEnu"    || 
                        dial_names[sys_iter] == "MEC_lowEnubar"  || 
                        dial_names[sys_iter] == "MEC_highEnubar" ){ // Edep 2p2h
                        
                        
                        
                    }
                    
                    if (dial_names[sys_iter] == "Optical_Potential_C12" ||
                        dial_names[sys_iter] == "Optical_Potential_O16" ){ // Optical potential
                        
                        
                        
                    }
                    
                    if (dial_names[sys_iter] == "R_S_Delta_Decay"){

                        
                        
                    }
                    
                }
                else {
                    
                    graph->SetPoint(dial_iter, dial_ToValue[sys_iter][dial_iter], weight);
                    
                }


            }
            
            if (isFlat) {

                for (int piter = (graph->GetN() - 1); piter >= 0; piter--)
                    graph->RemovePoint(piter);

                graph->SetPoint(0, 0.0, 1.0);
            }
            
            // Fix RS Delta Decay bug
            
            if (dial_names[sys_iter] == "R_S_Delta_Decay") {
                
                if (isFlat) continue;
                
                double w0=graph->GetPointY(0), w1=graph->GetPointY(dial_tweaks[sys_iter].size()-1);
                
                for (int piter = (graph->GetN() - 1); piter >= 0; piter--)
                    graph->RemovePoint(piter);
                
                graph->SetPoint(0, 0.0, w0);
                graph->SetPoint(1, 1.0, w1);
                
                
            }
            
        }
        
        ssum_tree.Fill();
        
    }

        
     cout<<"End looping events"<<endl;
    
    ssum_tree.Print();    
    outfile->cd();
    ssum_tree.Write();
    outfile->Close();
}




double ApplyCoulombShift(int TruePDG, int NuPDG, int target, int reaction) {
  // ******************************************
  // Adapted from MaCh3

  int kNEUT_NC1pi01n = 31;
  int kTarget_C = 12;
  int kTarget_O = 16;
  // Only want CC events
  if (reaction >= kNEUT_NC1pi01n) return 0.0;

  // The amount we shift by
  double shift = 0.0;

  // Check the lepton candidate matches the neutrino PDG
  // If anti-neutrino interaction, check that NuPDG
  if (NuPDG < 0) {
    if (NuPDG != TruePDG-1) return shift;
  } else {
    if (NuPDG != TruePDG+1) return shift;
  }
  // Check PID of true particle making this lepton candidate
  // This is now done above as before. The following line is only left for historical comparison
  //if (abs(TruePDG) != 11 && abs(TruePDG) != 13 && abs(TruePDG) != 15) return 0.0;

  // Shift the lepton momentum
//   if (kKinType == kLeptonMomentum) {
  if (true) {
    // Neutrino
    if (TruePDG > 0) {
      // If target was C
      if (target == kTarget_C) {
        shift = -3.6;
        // If target was O
      } else if (target == kTarget_O) {
        shift = -4.3;
      }
      // Anti-neutrino
    } else if (TruePDG < 0) {
      // If target was C
      if (target == kTarget_C) {
        shift = 2.6;
      } else if (target == kTarget_O) {
        shift = 3.3;
      }
    }
    // Return the shiften lepton momentum
    return shift;
    // Shift the Q2 if requested
  }

  return shift;
}


