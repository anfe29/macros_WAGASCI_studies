#include <fstream>
#include <iostream>
#include <filesystem>

////////////////////////////////////////////////////
// Old macro used to get a covariance matrix from//
// Kenji's file, now use generate_xsecparams.C   //
//////////////////////////////////////////////////

TFile *f_output = NULL;
TObjArray *xsec_param_name = NULL;
std::vector<std::string> name_dials;

bool isRootfile(std::string a)
{
	// returns true if root file
	int found = a.find(".root");
	if(found != std::string::npos) return true;
	else return false;
}

void fillSplineNames(std::string directory)
{
	int dir_len = directory.length();
	xsec_param_name = new TObjArray();
	std::vector<TObjString*> name;

	// get spline names and add to tobjectarray
	for(auto& p: std::filesystem::directory_iterator(directory)) {
		std::string path_str = p.path().string();
		if(isRootfile(path_str)) {
			std::string str =  path_str.substr(dir_len + 12,(path_str.find(".root") - (dir_len + 12)));
			// for filling vectors

			name_dials.push_back(str);
			name.push_back(new TObjString);
			name.back()->SetString(str.c_str());
			//std::cout << "Adding " << path_str.substr(dir_len,(path_str.find(".root") - dir_len)) << " to array \n";
			//std::cout << "Adding " << name->GetString() << " to array\n";
			xsec_param_name->Add(name.back());
			//std::cout << "Entries in array: " << xsec_param_name->GetEntries() << "\n";
		}
	}
	//std::cout << "\nChecking string array contents: \n";
	//xsec_param_name->Print();
	//std::cout << "Writing object to file \n";
	f_output->WriteObject(xsec_param_name,"xsec_param_names");
	name.clear();
}

void fillMatrix(std::string path)
{
	TFile *f = new TFile(path.c_str());
	//std::cout << "Reading matrix from " << path << "\n";
	auto cov = f->Get("xsec_cov");

	//std::cout << "\nChecking matrix contents: \n";
	//cov->Print();
	f_output->cd();
	//std::cout << "Writing object to file \n";
	f_output->WriteObject(cov,"xsec_cov");
	f->Close();
}

void fillVectors()
{
	int n = xsec_param_name->GetEntries();
	double prior[n], lb[n], ub[n];
	double *a = prior;
	double *b = lb;
	double *c = ub;
	for(int i = 0; i < n; i++) {

            if(strcmp(name_dials[i].c_str(),"MaCCQE") == 0) {
            prior[i] = 1.03;
            lb[i] = 0.30;
            ub[i] = 0.30;
	}
	    if(strcmp(name_dials[i].c_str(),"SF_PBTwkDial_Hybrid_C12_nu") == 0) {
            prior[i] = 0.00;
            lb[i] = 0.60;
            ub[i] = 2.00;
	}
  	    if(strcmp(name_dials[i].c_str(),"SF_PBTwkDial_Hybrid_O16_nubar") == 0) {
            prior[i] = 0.00;
            lb[i] = 0.60;
            ub[i] = 2.00;
	}
	    if(strcmp(name_dials[i].c_str(),"SF_SShell_MeanF_PMissShape_O") == 0) {
            prior[i] = 0.00;
            lb[i] = 1.0;
            ub[i] = 1.0;
	}
	    if(strcmp(name_dials[i].c_str(),"SF_P1_2Shell_MeanF_Norm_O") == 0) {
            prior[i] = 0.00;
            lb[i] = 0.20;
            ub[i] = 0.20;
	}
 	    if(strcmp(name_dials[i].c_str(),"SF_PShell_MeanF_PMissShape_C") == 0) {
            prior[i] = 0.00;
            lb[i] = 1.00;
            ub[i] = 1.00;
	}
	    if(strcmp(name_dials[i].c_str(),"SF_P3_2Shell_MeanF_Norm_O") == 0) {
            prior[i] = 0.00;
            lb[i] = 0.2;
            ub[i] = 0.2;
	}
	    if(strcmp(name_dials[i].c_str(),"CC_DIS_norm_nubar") == 0) {
            prior[i] = 1.00;
            lb[i] = 0.5;
            ub[i] = 0.5;
	}
	    if(strcmp(name_dials[i].c_str(),"CC_DIS_norm_nu") == 0) {
            prior[i] = 1.00;
            lb[i] = 0.5;
            ub[i] = 0.5;
	}
	    if(strcmp(name_dials[i].c_str(),"SF_P1_2Shell_MeanF_PMissShape_O") == 0) {
            prior[i] = 0.00;
            lb[i] = 1.0;
            ub[i] = 1.0;
	}
	    if(strcmp(name_dials[i].c_str(),"CC_MultiPi_norm_nubar") == 0) {
            prior[i] = 1.00;
            lb[i] = 0.5;
            ub[i] = 0.5;
	}
	    if(strcmp(name_dials[i].c_str(),"SF_SShell_MeanF_Norm_C") == 0) {
            prior[i] = 0.00;
            lb[i] = 0.4;
            ub[i] = 0.4;
	}
	    if(strcmp(name_dials[i].c_str(),"SF_PBTwkDial_Hybrid_O16_nu") == 0) {
            prior[i] = 0.00;
            lb[i] = 0.6;
            ub[i] = 2.0;
	}
	    if(strcmp(name_dials[i].c_str(),"SF_SRC_Norm_C") == 0) {
            prior[i] = 1.00;
            lb[i] = 1.0;
            ub[i] = 1.0;
	}
	    if(strcmp(name_dials[i].c_str(),"SF_PShell_MeanF_Norm_C") == 0) {
            prior[i] = 0.00;
            lb[i] = 0.2;
            ub[i] = 0.2;
	}
	    if(strcmp(name_dials[i].c_str(),"SF_P3_2Shell_MeanF_PMissShape_O") == 0) {
            prior[i] = 0.0;
            lb[i] = 1.0;
            ub[i] = 1.0;
	}
	    if(strcmp(name_dials[i].c_str(),"SF_PBTwkDial_Hybrid_C12_nubar") == 0) {
            prior[i] = 0.0;
            lb[i] = 0.6;
            ub[i] = 2.0;
	}
	    if(strcmp(name_dials[i].c_str(),"SF_SShell_MeanF_PMissShape_C") == 0) {
            prior[i] = 0.0;
            lb[i] = 1.0;
            ub[i] = 1.0;
	}
	    if(strcmp(name_dials[i].c_str(),"SF_SShell_MeanF_Norm_O") == 0) {
            prior[i] = 0.0;
            lb[i] = 0.2;
            ub[i] = 0.2;
	}
	    if(strcmp(name_dials[i].c_str(),"CC_MultiPi_norm_nu") == 0) {
            prior[i] = 1.00;
            lb[i] = 0.5;
            ub[i] = 0.5;
	}
	    if(strcmp(name_dials[i].c_str(),"SF_SRC_Norm_O") == 0) {
            prior[i] = 1.00;
            lb[i] = 1.0;
            ub[i] = 1.0;
	}
	    if(strcmp(name_dials[i].c_str(),"QETwk_HighQ2Weight_1") == 0) {
            prior[i] = 1.00;
            lb[i] = 0.11;
            ub[i] = 0.11;
	}

            if(strcmp(name_dials[i].c_str(),"QETwk_HighQ2Weight_2") == 0) {
            prior[i] = 1.00;
            lb[i] = 0.18;
            ub[i] = 0.18;
	}

            if(strcmp(name_dials[i].c_str(),"QETwk_HighQ2Weight_3") == 0) {
            prior[i] = 1.00;
            lb[i] = 0.4;
            ub[i] = 0.4;
	}

            if(strcmp(name_dials[i].c_str(),"SF_OptPotTwkDial_O16") == 0) {
            prior[i] = 0.00;
            lb[i] = 0.0;
            ub[i] = 0.49;
	}

            if(strcmp(name_dials[i].c_str(),"SF_OptPotTwkDial_C12") == 0) {
            prior[i] = 0.00;
            lb[i] = 0.0;
            ub[i] = 0.49;
	}

            if(strcmp(name_dials[i].c_str(),"MECTwkDial_Norm_C12") == 0) {
            prior[i] = 1.00;
            lb[i] = 0.99;
            ub[i] = 0.99;
	}
	    
            if(strcmp(name_dials[i].c_str(),"MECTwkDial_Norm_O16") == 0) {
            prior[i] = 1.00;
            lb[i] = 0.99;
            ub[i] = 0.99;
	}

            if(strcmp(name_dials[i].c_str(),"MECTwkDial_Norm_Other") == 0) {
            prior[i] = 1.00;
            lb[i] = 0.49;
            ub[i] = 0.49;
	}

            if(strcmp(name_dials[i].c_str(),"MECTwkDial_PDDWeight_C12_NN") == 0) {
            prior[i] = 0.0;
            lb[i] = 0.49;
            ub[i] = 0.49;
	}

            if(strcmp(name_dials[i].c_str(),"MECTwkDial_PDDWeight_C12_np") == 0) {
            prior[i] = 0.0;
            lb[i] = 0.49;
            ub[i] = 0.49;
	}

            if(strcmp(name_dials[i].c_str(),"MECTwkDial_PDDWeight_O16_NN") == 0) {
            prior[i] = 0.0;
            lb[i] = 0.49;
            ub[i] = 0.49;
	}

            if(strcmp(name_dials[i].c_str(),"MECTwkDial_PDDWeight_O16_np") == 0) {
            prior[i] = 0.0;
            lb[i] = 0.49;
            ub[i] = 0.49;
	}

            if(strcmp(name_dials[i].c_str(),"MECTwkDial_PNNN_Shape") == 0) {
            prior[i] = 0.0;
            lb[i] = 0.33;
            ub[i] = 0.33;
	}
	    
            if(strcmp(name_dials[i].c_str(),"RES_Eb_C_numu") == 0) {
            prior[i] = 25.0;
            lb[i] = 24.9;
            ub[i] = 24.9;
	}

            if(strcmp(name_dials[i].c_str(),"RES_Eb_O_numu") == 0) {
            prior[i] = 25.0;
            lb[i] = 24.9;
            ub[i] = 24.9;
	}
	
            if(strcmp(name_dials[i].c_str(),"RES_Eb_C_numubar") == 0) {
            prior[i] = 25.0;
            lb[i] = 24.9;
            ub[i] = 24.9;
	}
        
            if(strcmp(name_dials[i].c_str(),"RES_Eb_O_numubar") == 0) {
            prior[i] = 25.0;
            lb[i] = 24.9;
            ub[i] = 24.9;
	}
	
            if(strcmp(name_dials[i].c_str(),"BgSclRES") == 0) {
            prior[i] = 1.3;
            lb[i] = 0.15;
            ub[i] = 0.15;
	}
        
            if(strcmp(name_dials[i].c_str(),"CA5RES") == 0) {
            prior[i] = 1.01;
            lb[i] = 0.15;
            ub[i] = 0.15;
	}
        
            if(strcmp(name_dials[i].c_str(),"MaRES") == 0) {
            prior[i] = 0.95;
            lb[i] = 0.15;
            ub[i] = 0.15;
	}
	
            if(strcmp(name_dials[i].c_str(),"PionFSI_AbsProb") == 0) {
            prior[i] = 1.404;
            lb[i] = 0.432;
            ub[i] = 0.432;
	}
	
            if(strcmp(name_dials[i].c_str(),"PionFSI_CExHighMomProb") == 0) {
            prior[i] = 1.8;
            lb[i] = 0.288;
            ub[i] = 0.288;
	}
	
            if(strcmp(name_dials[i].c_str(),"PionFSI_CExLowMomProb") == 0) {
            prior[i] = 0.697;
            lb[i] = 0.305;
            ub[i] = 0.305;
	}
	
            if(strcmp(name_dials[i].c_str(),"PionFSI_InelProb") == 0) {
            prior[i] = 1.002;
            lb[i] = 1.101;
            ub[i] = 1.101;
	}
	
            if(strcmp(name_dials[i].c_str(),"PionFSI_QEHighMomProb") == 0) {
            prior[i] = 1.824;
            lb[i] = 0.859;
            ub[i] = 0.859;
	}
	
            if(strcmp(name_dials[i].c_str(),"PionFSI_QELowMomProb") == 0) {
            prior[i] = 1.069;
            lb[i] = 0.313;
            ub[i] = 0.313;
	}
	
            if(strcmp(name_dials[i].c_str(),"TwkDial_FateNucleonFSI") == 0) {
            prior[i] = 0.0;
            lb[i] = 0.3;
            ub[i] = 0.3;
	}

	}

	std::cout << "Checking arrays \nPriors	lb	ub\n";
	for(int i = 0; i < n; i++){
		std::cout << prior[i] << "	" << lb[i] << "		" << ub[i] << "\n";
	}
	//std::cout << "Initializing vectors \n";
	TVectorT<double> xsec_param_prior(n,a);
	TVectorT<double> xsec_param_lb(n,b);
	TVectorT<double> xsec_param_ub(n,c);

	f_output->cd();
	//std::cout << "Writing object to file \n";
	xsec_param_prior.Write("xsec_param_prior");
	xsec_param_lb.Write("xsec_param_lb");
	xsec_param_ub.Write("xsec_param_ub");
}

void generate_covmatrix()
{
	//std::string dir = "pm_pmu/pmu/";
	std::string dir = "pmu_binning/splines/";
	std::string path_covmat = "pmu_binning/cov_matrix/xsec/wagasci_xsec_cov_cc0pi.root";

	f_output = new TFile("inputs/parameters/xsec/xsec_covmatrix_param.root","RECREATE");

	fillMatrix(path_covmat);
	fillSplineNames(dir);
	fillVectors();

	//std::cout << "Closing output file \n";
	f_output->Close();
}
