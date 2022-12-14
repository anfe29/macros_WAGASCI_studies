
int NEUT2GUN(int reaction)
{
	//if(abs(reaction) == 59) return 8;

	//if(abs(reaction) == 9) return 8;

	if(abs(reaction) > 30 && abs(reaction) < 70) return 4;

	//if(abs(nutype) == 12) return 4;

	//else if(IsAntinu && nutype == 14) return 5;

	else if(reaction < 0) return 5;

	//else if(abs(nutype) == 14) {
		if(abs(reaction) == 1) return 0;
		
		if(abs(reaction) == 25) return 0;

		if(abs(reaction) == 2) return 9;

		//if(abs(reaction) == 70) return 9;

		if(abs(reaction) > 10 && abs(reaction) < 14) return 1;

		if(abs(reaction) == 17) return 1;

		if(abs(reaction) == 22) return 1;

		if(abs(reaction) == 23) return 1;

		if(abs(reaction) > 16 && abs(reaction) < 30) return 2;
		
		if(abs(reaction) == 16) return 3;

	//}

	return 8;
}

int NEUT2KENJI(int reaction) 
{

	if(abs(reaction) == 1) return 0;
	
	if(abs(reaction) == 2) return 1;

	if(abs(reaction) == 11 || abs(reaction) == 13) return 2;

	if(abs(reaction) == 12) return 3;

	if(abs(reaction) == 26) return 4;

	if(abs(reaction) == 21) return 5;

	if(abs(reaction) == 16 || abs(reaction) == 17 || abs(reaction) == 22 || abs(reaction) == 23 || abs(reaction) == 51 || abs(reaction) == 52) return 6;

	if(abs(reaction) > 30 && abs(reaction) < 47) return 7;

	return 8;
}

void merge_trees() 
{
	// Open target root files
	TFile *file1 = new TFile("/home/amunoz/WAGASCI/files_kenji/rootfiles/selection_results_input_for_xsLLhFitter_w_yasu_pmu_sample_split_h2o.root");
	TFile *file2 = new TFile("/home/amunoz/WAGASCI/files_kenji/rootfiles/selection_results_input_for_xsLLhFitter_w_yasu_pmu_sample_split.root");
	
	// Create new root file
	TFile *file = new TFile("/home/amunoz/WAGASCI/studies_sampKenj/inputs/wagasci_sample_kenji.root","recreate");

	// Define trees
	TTree *t1 = (TTree*) file1->Get("selectedEvents"); 
	TTree *t2 = (TTree*) file2->Get("selectedEvents");
	TTree *t = new TTree("selectedEvents","selectedEvents");

	// input define variables
	// 1st tree
	int nutype1;
	int cut_branch1;
	int topology1;
	int reaction1;
	int target1;
	// costhetamu
	float D2True1;
	float D2Reco1;
	// pmu
	float D1True1;
	float D1Reco1;
	float q2_true1;
	float q2_reco1;
	float enu_true1;
	float enu_reco1;
	float weight1;

	// 2nd tree
	int nutype2;
	int cut_branch2;
	int topology2;
	int reaction2;
	int target2;
	float D2True2;
	float D2Reco2;
	float D1True2;
	float D1Reco2;
	float q2_true2;
	float q2_reco2;
	float enu_true2;
	float enu_reco2;
	float weight2;

	// define output variables
	// variables from WAGASCI
	int nutype;
	int cut_branch;
	int topology;
	int reaction;
	int reaction_kenji;
	int target;
	float D2True;
	float D2Reco;
	float D1True;
	float D1Reco;
	float q2_true;
	float q2_reco;
	float Enu;
	float enu_reco;
	float weight;
	int sample;
	
	// variables needed by GUNDAM, careful with naming
        int MAX_VERTEX = 1;
  
        int NVertexID = 1;
        
        int VertexID;
        int NeutrinoCode;
        
        double TrueNeutrinoDirX;
        double TrueNeutrinoDirY;
        double TrueNeutrinoDirZ;

        int RunNumber;
        int SubRunNumber;
        int EventNumber;

        int TrueLepPDG;
        double TruePmu;
        double TrueLepMom;
        double TrueCosThetamu;
        double TrueLepDirX;
        double TrueLepDirY;
        double TrueLepDirZ;
        double RecoLepMom;
        double RecoLepDirX;
        double RecoLepDirY;
        double RecoLepDirZ;
        //double CosThetamu;

        int TruePreFSIPiPDG;
        double TruePreFSIPiMom;
        double TruePreFSIPiDirX;
        double TruePreFSIPiDirY;
        double TruePreFSIPiDirZ;
        int TruePostFSIPiPDG;
        double TruePostFSIPiMom;
        double TruePostFSIPiDirX;
        double TruePostFSIPiDirY;
        double TruePostFSIPiDirZ;
        double RecoPiMom;
        double RecoPiDirX;
        double RecoPiDirY;
        double RecoPiDirZ;
        int RecoPi_Topo;

        double TruePostFSIProtonMom;
        double TruePostFSIProtonDirX;
        double TruePostFSIProtonDirY;
        double TruePostFSIProtonDirZ;
        int TruePostFSIProton_Topo;
        double RecoProtonMom;
        double RecoProtonDirX;
        double RecoProtonDirY;
        double RecoProtonDirZ;
        int RecoProton_Topo;

        double  PileUpWeight;
        //int  isRHC;
        int  passedPsyche;

        int isSRC;
        double Emiss;
        double Pmiss;

        double q3;
        double q0;

        int ReactionCode;
        int NuParent;
        //double Q2;
        double Q2QE;
        bool HaveTruth;
        int TgtMat;
        double FluxWeight;
        int TruthVtx;

        int Run;

        int NSamples = -999;
        int SelectedSample = 0;
        double DetNomWeight;
        
        bool isConsecutiveIdenticalEvent = false;
        double PmuCoulombCorrection;
	
 	// create branches 
	t->Branch("SelectedSample",&cut_branch);
	t->Branch("topology",&topology);
	t->Branch("target",&target);
	// CosThetamu
	t->Branch("D2True",&D2True);
	t->Branch("D2Reco",&D2Reco);
	// Pmu
	t->Branch("D1True",&D1True);
	t->Branch("D1Reco",&D1Reco);
	t->Branch("Q2",&q2_true);
	t->Branch("q2_reco",&q2_reco);
	t->Branch("Enu_reco",&enu_reco);
	t->Branch("POTWeight",&weight);
	t->Branch("Enu",&Enu);
	t->Branch("sample",&sample);
	t->Branch("isRHC",&nutype);
	
	// branches for necessary for gundam inputs
       	t->Branch("NVertexID", &NVertexID);
        t->Branch("MAX_VERTEX", &MAX_VERTEX);
        t->Branch("VertexID", VertexID);
        t->Branch("NSamples", &NSamples);
        t->Branch("SelectedSample", &SelectedSample);
        t->Branch("Run", &Run);
        t->Branch("RunNumber", &RunNumber);
        t->Branch("SubRunNumber", &SubRunNumber);
        t->Branch("EventNumber", &EventNumber);
        t->Branch("DetNomWeight", &DetNomWeight);
        t->Branch("NeutrinoCode", &NeutrinoCode);

        t->Branch("TrueNeutrinoDirX", &TrueNeutrinoDirX);
        t->Branch("TrueNeutrinoDirY", &TrueNeutrinoDirY);
        t->Branch("TrueNeutrinoDirZ", &TrueNeutrinoDirZ);
        t->Branch("TrueLepPDG", &TrueLepPDG);
        t->Branch("TruePmu", &TruePmu);
        t->Branch("TrueLepDirX", &TrueLepDirX);
        t->Branch("TrueLepDirY", &TrueLepDirY);
        t->Branch("TrueLepDirZ", &TrueLepDirZ);
        t->Branch("TrueCosThetamu", &TrueCosThetamu,"TrueCosThetamu/D");

        t->Branch("RecoLepDirX", &RecoLepDirX);
        t->Branch("RecoLepDirY", &RecoLepDirY);
        t->Branch("RecoLepDirZ", &RecoLepDirZ);
	
        t->Branch("TruePostFSIPiPDG", &TruePostFSIPiPDG);
        t->Branch("TruePostFSIPiMom", &TruePostFSIPiMom);
        t->Branch("TruePostFSIPiDirX", &TruePostFSIPiDirX);
        t->Branch("TruePostFSIPiDirY", &TruePostFSIPiDirY);
        t->Branch("TruePostFSIPiDirZ", &TruePostFSIPiDirZ);
        t->Branch("TruePreFSIPiPDG", &TruePreFSIPiPDG);
        t->Branch("TruePreFSIPiMom", &TruePreFSIPiMom);
        t->Branch("TruePreFSIPiDirX", &TruePreFSIPiDirX);
        t->Branch("TruePreFSIPiDirY", &TruePreFSIPiDirY);
        t->Branch("TruePreFSIPiDirZ", &TruePreFSIPiDirZ);

        t->Branch("RecoPiMom", &RecoPiMom);
        t->Branch("RecoPiDirX", &RecoPiDirX);
        t->Branch("RecoPiDirY", &RecoPiDirY);
        t->Branch("RecoPiDirZ", &RecoPiDirZ);
        t->Branch("RecoPi_Topo", &RecoPi_Topo);

        t->Branch("TruePostFSIProtonMom", &TruePostFSIProtonMom);
        t->Branch("TruePostFSIProtonDirX", &TruePostFSIProtonDirX);
        t->Branch("TruePostFSIProtonDirY", &TruePostFSIProtonDirY);
        t->Branch("TruePostFSIProtonDirZ", &TruePostFSIProtonDirZ);
        t->Branch("TruePostFSIProton_Topo", &TruePostFSIProton_Topo);

        t->Branch("RecoProtonMom", &RecoProtonMom);
        t->Branch("RecoProtonDirX", &RecoProtonDirX);
        t->Branch("RecoProtonDirY", &RecoProtonDirY);
        t->Branch("RecoProtonDirZ", &RecoProtonDirZ);
        t->Branch("RecoProton_Topo", &RecoProton_Topo);
        t->Branch("PileUpWeight", &PileUpWeight);
        t->Branch("passedPsyche", &passedPsyche);
	t->Branch("ReactionCode",&ReactionCode);
        t->Branch("NuParent", NuParent);

        t->Branch("Q2QE", &Q2QE);
        t->Branch("HaveTruth", &HaveTruth);
        t->Branch("TgtMat", TgtMat);
        t->Branch("FluxWeight", &FluxWeight);
        t->Branch("TruthVtx", TruthVtx);
        t->Branch("q3", &q3);
        t->Branch("q0", &q0);
        t->Branch("isSRC", &isSRC);
        t->Branch("Emiss", &Emiss);
        t->Branch("Pmiss", &Pmiss);
	t->Branch("reaction",&reaction);
	t->Branch("reaction_kenji",&reaction_kenji);
        
        t->Branch("PmuCoulombCorrection", &PmuCoulombCorrection);
        t->Branch("isConsecutiveIdenticalEvent", &isConsecutiveIdenticalEvent);
	
	// set existing branches
	t1->SetBranchAddress("nutype",&nutype1);
	t1->SetBranchAddress("cut_branch",&cut_branch1);
	t1->SetBranchAddress("topology",&topology1);
	t1->SetBranchAddress("reaction",&reaction1);
	t1->SetBranchAddress("target",&target1);
	t1->SetBranchAddress("D2True",&D2True1);
	t1->SetBranchAddress("D2Reco",&D2Reco1);
	t1->SetBranchAddress("D1True",&D1True1);
	t1->SetBranchAddress("D1Reco",&D1Reco1);
	t1->SetBranchAddress("q2_true",&q2_true1);
	t1->SetBranchAddress("q2_reco",&q2_reco1);
	t1->SetBranchAddress("enu_true",&enu_true1);
	t1->SetBranchAddress("enu_reco",&enu_reco1);
	t1->SetBranchAddress("weight",&weight1);

	t2->SetBranchAddress("nutype",&nutype2);
	t2->SetBranchAddress("cut_branch",&cut_branch2);
	t2->SetBranchAddress("topology",&topology2);
	t2->SetBranchAddress("reaction",&reaction2);
	t2->SetBranchAddress("target",&target2);
	t2->SetBranchAddress("D2True",&D2True2);
	t2->SetBranchAddress("D2Reco",&D2Reco2);
	t2->SetBranchAddress("D1True",&D1True2);
	t2->SetBranchAddress("D1Reco",&D1Reco2);
	t2->SetBranchAddress("q2_true",&q2_true2);
	t2->SetBranchAddress("q2_reco",&q2_reco2);
	t2->SetBranchAddress("enu_true",&enu_true2);
	t2->SetBranchAddress("enu_reco",&enu_reco2);
	t2->SetBranchAddress("weight",&weight2);

	// fill with first tree
	for(int i = 0; i < t1->GetEntries(); i++) {
		
		t1->GetEntry(i);
		nutype = nutype1;
		cut_branch = 150 + cut_branch1;
		topology = topology1;
		reaction = NEUT2GUN(reaction1);
		reaction_kenji = NEUT2KENJI(reaction1);
		ReactionCode = reaction1;
		target = target1;
		D2True = D2True1;
		D1True = D1True1;
		D2Reco = D2Reco1;
		D1Reco = D1Reco1;
		q2_true = q2_true1;
		q2_reco = q2_reco1;
		Enu = enu_true1/1000;
		enu_reco = enu_reco1;
		weight = weight1;
		sample = cut_branch1;

                Run = -999;
                RunNumber = -999;
                SubRunNumber = -999;
                EventNumber = -999;
                DetNomWeight = 1;
                NeutrinoCode = 14;

                TrueNeutrinoDirX = -999;
                TrueNeutrinoDirY = -999;
                TrueNeutrinoDirZ = -999;
                TrueLepPDG = -999;
                TruePmu = -999;
                TrueLepDirX = -999;
                TrueLepDirY = -999;
                TrueLepDirZ = -999;
                TrueCosThetamu = -999;

                RecoLepDirX = -999;
                RecoLepDirY = -999;
                RecoLepDirZ = -999;
                
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

                TruePostFSIProtonMom = -999;
                TruePostFSIProtonDirX = -999;
                TruePostFSIProtonDirY = -999;
                TruePostFSIProtonDirZ = -999;
                TruePostFSIProton_Topo = -999;

                RecoProtonMom = -999;
                RecoProtonDirX = -999;
                RecoProtonDirY = -999;
                RecoProtonDirZ = -999;
                RecoProton_Topo = -999;
                PileUpWeight = 1;
                passedPsyche = 1;
                NuParent = -999;

                Q2QE = -999;
                HaveTruth = 1;
                TgtMat = -999;
                FluxWeight = 1;
                TruthVtx = -999;
                q3 = -999;
                q0 = -999;
                isSRC = -999;
                Emiss = -999;
                Pmiss = -999;
                
                PmuCoulombCorrection = -999;

		t->Fill();
	}
	
	// fill with second tree
	for(int i = 0; i < t2->GetEntries(); i++) {
		
		t2->GetEntry(i);
		nutype = nutype2;
		cut_branch = 150 + cut_branch2;
		topology = topology2;
		reaction = NEUT2GUN(reaction2);
		reaction_kenji = NEUT2KENJI(reaction2);
		ReactionCode = reaction2;
		target = target2;
		D2True = D2True2;
		D2Reco = D2Reco2;
		D1True = D1True2;
		D1Reco = D1Reco2;
		q2_true = q2_true2;
		q2_reco = q2_reco2;
		Enu = enu_true2/1000;
		enu_reco = enu_reco2;
		weight = weight2;
		sample = cut_branch2;

                Run = -999;
                RunNumber = -999;
                SubRunNumber = -999;
                EventNumber = -999;
                DetNomWeight = 1;
                NeutrinoCode = 14;

                TrueNeutrinoDirX = -999;
                TrueNeutrinoDirY = -999;
                TrueNeutrinoDirZ = -999;
                TrueLepPDG = -999;
                TruePmu = -999;
                TrueLepDirX = -999;
                TrueLepDirY = -999;
                TrueLepDirZ = -999;
                TrueCosThetamu = -999;

                RecoLepDirX = -999;
                RecoLepDirY = -999;
                RecoLepDirZ = -999;
                
                TruePostFSIPiPDG = -999;
                TruePostFSIPiMom = -999;
                TruePostFSIPiDirX = -999;
                TruePostFSIPiDirY = -999;
                TruePostFSIPiDirZ = -999;
                TruePreFSIPiPDG = -999;
                TruePreFSIPiDirY = -999;
                TruePreFSIPiDirZ = -999;

                RecoPiMom = -999;
                RecoPiDirX = -999;
                RecoPiDirY = -999;
                RecoPiDirZ = -999;
                RecoPi_Topo = -999;

                TruePostFSIProtonMom = -999;
                TruePostFSIProtonDirX = -999;
                TruePostFSIProtonDirY = -999;
                TruePostFSIProtonDirZ = -999;
                TruePostFSIProton_Topo = -999;

                RecoProtonMom = -999;
                RecoProtonDirX = -999;
                RecoProtonDirY = -999;
                RecoProtonDirZ = -999;
                RecoProton_Topo = -999;
                PileUpWeight = 1;
                passedPsyche = 1;
                NuParent = -999;

                Q2QE = -999;
                HaveTruth = 1;
                TgtMat = -999;
                FluxWeight = 1;
                TruthVtx = -999;
                q3 = -999;
                q0 = -999;
                isSRC = -999;
                Emiss = -999;
                Pmiss = -999;
                
                PmuCoulombCorrection = -999;

		t->Fill();
	}

	// write tree
	t->Write();
}
