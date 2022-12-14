#include <fstream>
#include <iostream>
#include <string>
#include <vector>

TObjArray *xsec_param_name = NULL;
TFile *f_output = NULL;

void readParams()
{
	// read parameter names from csv file and put it into a string objarray
	std::ifstream file("files_kenji/WAGASCI-BabyMIND_cc0pi_analysis_CorrMatrix.csv");
	xsec_param_name = new TObjArray();

	if (!file) {
		std::cerr << "not working";
		return 1;
	}

	std::vector<TObjString*> name;
	std::string tmp;
	while (std::getline(file, tmp)) {
		name.push_back(new TObjString);
		name.back()->SetString(tmp.substr(0, tmp.find_first_of(",")).c_str());
		//std::cout << "Adding to array: " << name.back()->GetString() << " \n";
		xsec_param_name->Add(name.back());
	}
	file.close();

}

void generate_xsecparams()
{
	// read parameters form csv file
	readParams();
	int param_num = xsec_param_name->GetEntries();
	//std::cout << "\nEntries in array: " << param_num << "\n";
	//std::cout << "\nChecking string array contents: \n";
	xsec_param_name->Print();

	// create correlation matrix
	double corr[param_num][param_num];
	// maybe parse form csv file but now lazy
	for(int i = 0; i < param_num; i++) {
		for(int j = 0; j < param_num; j++) {
			corr[i][j] = 0;
			if(i == j) corr[i][j] = 1;
			if((i == 10 && j == 12) || (i == 12 && j == 10)) corr[i][j] = 0.3;
			if((i == 11 && j == 13) || (i == 13 && j == 11)) corr[i][j] = 0.3;
			if((i == 19 && j == 20) || (i == 20 && j == 19)) corr[i][j] = -0.03;
			if((i == 20 && j == 21) || (i == 21 && j == 20)) corr[i][j] = -0.11;
			if((i == 22 && j == 24) || (i == 24 && j == 22)) corr[i][j] = -0.31;
			if((i == 22 && j == 25) || (i == 25 && j == 22)) corr[i][j] = -0.03;
			if((i == 22 && j == 26) || (i == 26 && j == 22)) corr[i][j] = 0.03;
			if((i == 22 && j == 27) || (i == 27 && j == 22)) corr[i][j] = -0.27;
			if((i == 24 && j == 25) || (i == 25 && j == 24)) corr[i][j] = -0.01;
			if((i == 24 && j == 26) || (i == 26 && j == 24)) corr[i][j] = 0.01;
			if((i == 24 && j == 26) || (i == 26 && j == 24)) corr[i][j] = -0.2;
			if((i == 25 && j == 26) || (i == 26 && j == 25)) corr[i][j] = -0.53;
			if((i == 25 && j == 27) || (i == 27 && j == 25)) corr[i][j] = 0.03;
			if((i == 26 && j == 27) || (i == 27 && j == 26)) corr[i][j] = -0.03;
			if((i == 37 && j == 38) || (i == 38 && j == 37)) corr[i][j] = 0.8;
			if((i == 39 && j == 40) || (i == 40 && j == 39)) corr[i][j] = 0.8;
		}
	}

	TMatrixT<double> corr_matrix(param_num,param_num,corr[0]); 
	std::cout << "Contents of matrix: \n";
	corr_matrix.Print();

	// fill prior vectors and their errors
	double prior[param_num], prior_err[param_num], lb[param_num], ub[param_num];
	double *a = prior;
	double *b = lb;
	double *c = ub;
	for(int i = 0; i < param_num; i++) {

            //if(strcmp(name_dials[i].c_str(),"MaCCQE") == 0) {
	    if(i == 0) {
            prior[i] = 1.03;
	    prior_err[i] = 0.06;
            lb[i] = prior[i] - 5*prior_err[i];
            ub[i] = prior[i] + 5*prior_err[i];
	}
	    //if(strcmp(name_dials[i].c_str(),"QETwk_HighQ2Weight_1") == 0) {
	    if(i == 1) {
            prior[i] = 1.00;
	    prior_err[i] = 0.11;
            lb[i] = prior[i] - 5*prior_err[i];
            ub[i] = prior[i] + 5*prior_err[i];
	}
            //if(strcmp(name_dials[i].c_str(),"QETwk_HighQ2Weight_2") == 0) {
	    if(i == 2) {
            prior[i] = 1.00;
	    prior_err[i] = 0.18;
            lb[i] = prior[i] - 5*prior_err[i];
            ub[i] = prior[i] + 5*prior_err[i];
	}
            //if(strcmp(name_dials[i].c_str(),"QETwk_HighQ2Weight_3") == 0) {
	    if(i == 3) {
            prior[i] = 1.00;
	    prior_err[i] = 0.4;
            lb[i] = prior[i] - 5*prior_err[i];
            ub[i] = prior[i] + 5*prior_err[i];
	}
            //if(strcmp(name_dials[i].c_str(),"SF_OptPotTwkDial_O16") == 0) {
	    if(i == 4) {
            prior[i] = 0.00;
	    prior_err[i] = 0.49;
            lb[i] = prior[i] - 5*prior_err[i];
            ub[i] = prior[i] + 5*prior_err[i];
	}

            //if(strcmp(name_dials[i].c_str(),"SF_OptPotTwkDial_C12") == 0) {
	    if(i == 5) {
            prior[i] = 0.00;
	    prior_err[i] = 0.49;
            lb[i] = prior[i] - 5*prior_err[i];
            ub[i] = prior[i] + 5*prior_err[i];
	}

            //if(strcmp(name_dials[i].c_str(),"MECTwkDial_Norm_C12") == 0) {
	    if(i == 6) {
            prior[i] = 1.00;
	    prior_err[i] = 0.99;
            lb[i] = prior[i] - 5*prior_err[i];
            ub[i] = prior[i] + 5*prior_err[i];
	}
	    
            //if(strcmp(name_dials[i].c_str(),"MECTwkDial_Norm_O16") == 0) {
	    if(i == 7) {
            prior[i] = 1.00;
	    prior_err[i] = 0.99;
            lb[i] = prior[i] - 5*prior_err[i];
            ub[i] = prior[i] + 5*prior_err[i];
	}

            //if(strcmp(name_dials[i].c_str(),"MECTwkDial_Norm_Other") == 0) {
	    if(i == 8) {
            prior[i] = 1.00;
	    prior_err[i] = 0.49;
            lb[i] = prior[i] - 5*prior_err[i];
            ub[i] = prior[i] + 5*prior_err[i];
	}

            //if(strcmp(name_dials[i].c_str(),"MECTwkDial_PDDWeight_C12_NN") == 0) {
	    if(i == 9) {
            prior[i] = 0.0;
	    prior_err[i] = 0.49;
            lb[i] = prior[i] - 5*prior_err[i];
            ub[i] = prior[i] + 5*prior_err[i];
	}

            //if(strcmp(name_dials[i].c_str(),"MECTwkDial_PDDWeight_C12_np") == 0) {
	    if(i == 10) {
            prior[i] = 0.0;
	    prior_err[i] = 0.49;
            lb[i] = prior[i] - 5*prior_err[i];
            ub[i] = prior[i] + 5*prior_err[i];
	}

            //if(strcmp(name_dials[i].c_str(),"MECTwkDial_PDDWeight_O16_NN") == 0) {
	    if(i == 11) {
            prior[i] = 0.0;
	    prior_err[i] = 0.49;
            lb[i] = prior[i] - 5*prior_err[i];
            ub[i] = prior[i] + 5*prior_err[i];
	}

            //if(strcmp(name_dials[i].c_str(),"MECTwkDial_PDDWeight_O16_np") == 0) {
	    if(i == 12) {
            prior[i] = 0.0;
	    prior_err[i] = 0.49;
            lb[i] = prior[i] - 5*prior_err[i];
            ub[i] = prior[i] + 5*prior_err[i];
	}

            //if(strcmp(name_dials[i].c_str(),"MECTwkDial_PNNN_Shape") == 0) {
	    if(i == 13) {
            prior[i] = 0.0;
	    prior_err[i] = 0.33;
            lb[i] = prior[i] - 5*prior_err[i];
            ub[i] = prior[i] + 5*prior_err[i];
	}
	    
            //if(strcmp(name_dials[i].c_str(),"RES_Eb_C_numu") == 0) {
	    if(i == 14) {
            prior[i] = 25.0;
	    prior_err[i] = 24.9;
            lb[i] = prior[i] - 5*prior_err[i];
            ub[i] = prior[i] + 5*prior_err[i];
	}

            //if(strcmp(name_dials[i].c_str(),"RES_Eb_O_numu") == 0) {
	    if(i == 15) {
            prior[i] = 25.0;
	    prior_err[i] = 24.9;
            lb[i] = prior[i] - 5*prior_err[i];
            ub[i] = prior[i] + 5*prior_err[i];
	}
	
            //if(strcmp(name_dials[i].c_str(),"RES_Eb_C_numubar") == 0) {
	    if(i == 16) {
            prior[i] = 25.0;
	    prior_err[i] = 24.9;
            lb[i] = prior[i] - 5*prior_err[i];
            ub[i] = prior[i] + 5*prior_err[i];
	}
        
            //if(strcmp(name_dials[i].c_str(),"RES_Eb_O_numubar") == 0) {
	    if(i == 17) {
            prior[i] = 25.0;
	    prior_err[i] = 24.9;
            lb[i] = prior[i] - 5*prior_err[i];
            ub[i] = prior[i] + 5*prior_err[i];
	}
	
            //if(strcmp(name_dials[i].c_str(),"BgSclRES") == 0) {
	    if(i == 18) {
            prior[i] = 1.3;
	    prior_err[i] = 0.15;
            lb[i] = prior[i] - 5*prior_err[i];
            ub[i] = prior[i] + 5*prior_err[i];
	}
        
            //if(strcmp(name_dials[i].c_str(),"CA5RES") == 0) {
	    if(i == 19) {
            prior[i] = 1.01;
	    prior_err[i] = 0.15;
            lb[i] = prior[i] - 5*prior_err[i];
            ub[i] = prior[i] + 5*prior_err[i];
	}
        
            //if(strcmp(name_dials[i].c_str(),"MaRES") == 0) {
	    if(i == 20) {
            prior[i] = 0.95;
	    prior_err[i] = 0.15;
            lb[i] = prior[i] - 5*prior_err[i];
            ub[i] = prior[i] + 5*prior_err[i];
	}
	
            //if(strcmp(name_dials[i].c_str(),"PionFSI_AbsProb") == 0) {
	    if(i == 21) {
            prior[i] = 1.404;
	    prior_err[i] = 0.432;
            lb[i] = prior[i] - 5*prior_err[i];
            ub[i] = prior[i] + 5*prior_err[i];
	}
	
            //if(strcmp(name_dials[i].c_str(),"PionFSI_CExHighMomProb") == 0) {
	    if(i == 22) {
            prior[i] = 1.8;
	    prior_err[i] = 0.288;
            lb[i] = prior[i] - 5*prior_err[i];
            ub[i] = prior[i] + 5*prior_err[i];
	}
	
            //if(strcmp(name_dials[i].c_str(),"PionFSI_CExLowMomProb") == 0) {
	    if(i == 23) {
            prior[i] = 0.697;
	    prior_err[i] = 0.305;
            lb[i] = prior[i] - 5*prior_err[i];
            ub[i] = prior[i] + 5*prior_err[i];
	}
	
            //if(strcmp(name_dials[i].c_str(),"PionFSI_InelProb") == 0) {
	    if(i == 24) {
            prior[i] = 1.002;
	    prior_err[i] = 1.101;
            lb[i] = prior[i] - 5*prior_err[i];
            ub[i] = prior[i] + 5*prior_err[i];
	}
	
            //if(strcmp(name_dials[i].c_str(),"PionFSI_QEHighMomProb") == 0) {
	    if(i == 25) {
            prior[i] = 1.824;
	    prior_err[i] = 0.859;
            lb[i] = prior[i] - 5*prior_err[i];
            ub[i] = prior[i] + 5*prior_err[i];
	}
	
            //if(strcmp(name_dials[i].c_str(),"PionFSI_QELowMomProb") == 0) {
	    if(i == 26) {
            prior[i] = 1.069;
	    prior_err[i] = 0.313;
            lb[i] = prior[i] - 5*prior_err[i];
            ub[i] = prior[i] + 5*prior_err[i];
	}
	
            //if(strcmp(name_dials[i].c_str(),"TwkDial_FateNucleonFSI") == 0) {
	    if(i == 27) {
            prior[i] = 0.0;
	    prior_err[i] = 0.3;
            lb[i] = prior[i] - 5*prior_err[i];
            ub[i] = prior[i] + 5*prior_err[i];
	}
	    //if(strcmp(name_dials[i].c_str(),"CC_DIS_norm_nu") == 0) {
	    if(i == 28) {
            prior[i] = 1.00;
	    prior_err[i] = 0.5;
            lb[i] = prior[i] - 5*prior_err[i];
            ub[i] = prior[i] + 5*prior_err[i];
	}
	    //if(strcmp(name_dials[i].c_str(),"CC_DIS_norm_nubar") == 0) {
	    if(i == 29) {
            prior[i] = 1.00;
	    prior_err[i] = 0.5;
            lb[i] = prior[i] - 5*prior_err[i];
            ub[i] = prior[i] + 5*prior_err[i];
	}
	    //if(strcmp(name_dials[i].c_str(),"CC_MultiPi_norm_nu") == 0) {
	    if(i == 30) {
            prior[i] = 1.00;
	    prior_err[i] = 0.5;
            lb[i] = prior[i] - 5*prior_err[i];
            ub[i] = prior[i] + 5*prior_err[i];
	}
	    //if(strcmp(name_dials[i].c_str(),"CC_MultiPi_norm_nubar") == 0) {
	    if(i == 31) {
            prior[i] = 1.00;
	    prior_err[i] = 0.5;
            lb[i] = prior[i] - 5*prior_err[i];
            ub[i] = prior[i] + 5*prior_err[i];
	}
	    //if(strcmp(name_dials[i].c_str(),"SF_P1_2Shell_MeanF_Norm_O") == 0) {
	    if(i == 32) {
            prior[i] = 1.0;
	    //prior_err[i] = 0.2;
	    prior_err[i] = 0.5;
            lb[i] = 0.0;
            ub[i] = 2.0;
	}
	    //if(strcmp(name_dials[i].c_str(),"SF_P1_2Shell_MeanF_PMissShape_O") == 0) {
	    if(i == 33) {
            prior[i] = 0.00;
	    prior_err[i] = 1.0;
            lb[i] = prior[i] - 5*prior_err[i];
            ub[i] = prior[i] + 5*prior_err[i];
	}
	    //if(strcmp(name_dials[i].c_str(),"SF_P3_2Shell_MeanF_Norm_O") == 0) {
	    if(i == 34) {
            prior[i] = 1.0;
	    //prior_err[i] = 0.2;
	    prior_err[i] = 0.5;
            lb[i] = 0.0;
            ub[i] = 2.0;
	}
	    //if(strcmp(name_dials[i].c_str(),"SF_P3_2Shell_MeanF_PMissShape_O") == 0) {
	    if(i == 35) {
            prior[i] = 0.0;
	    prior_err[i] = 1.0;
            lb[i] = prior[i] - 5*prior_err[i];
            ub[i] = prior[i] + 5*prior_err[i];
	}
	    //if(strcmp(name_dials[i].c_str(),"SF_PBTwkDial_Hybrid_C12_nu") == 0) {
	    if(i == 36) {
            prior[i] = 0.00;
	    prior_err[i] = 0.6;
            lb[i] = prior[i] - 5*prior_err[i];
            ub[i] = prior[i] + 5*prior_err[i];
	}
	    //if(strcmp(name_dials[i].c_str(),"SF_PBTwkDial_Hybrid_C12_nubar") == 0) {
	    if(i == 37) {
            prior[i] = 0.0;
	    prior_err[i] = 0.6;
            lb[i] = prior[i] - 5*prior_err[i];
            ub[i] = prior[i] + 5*prior_err[i];
	}
	    //if(strcmp(name_dials[i].c_str(),"SF_PBTwkDial_Hybrid_O16_nu") == 0) {
	    if(i == 38) {
            prior[i] = 0.00;
	    prior_err[i] = 0.6;
            lb[i] = prior[i] - 5*prior_err[i];
            ub[i] = prior[i] + 5*prior_err[i];
	}
  	    //if(strcmp(name_dials[i].c_str(),"SF_PBTwkDial_Hybrid_O16_nubar") == 0) {
	    if(i == 39) {
            prior[i] = 0.00;
	    prior_err[i] = 0.6;
            lb[i] = prior[i] - 5*prior_err[i];
            ub[i] = prior[i] + 5*prior_err[i];
	}
	    //if(strcmp(name_dials[i].c_str(),"SF_PShell_MeanF_Norm_C") == 0) {
	    if(i == 40) {
            prior[i] = 0.00;
	    prior_err[i] = 0.2;
            lb[i] = prior[i] - 5*prior_err[i];
            ub[i] = prior[i] + 5*prior_err[i];
	}
 	    //if(strcmp(name_dials[i].c_str(),"SF_PShell_MeanF_PMissShape_C") == 0) {
	    if(i == 41) {
            prior[i] = 0.00;
	    prior_err[i] = 1.0;
            lb[i] = prior[i] - 5*prior_err[i];
            ub[i] = prior[i] + 5*prior_err[i];
	}
	    //if(strcmp(name_dials[i].c_str(),"SF_SRC_Norm_C") == 0) {
	    if(i == 42) {
            prior[i] = 1.00;
	    prior_err[i] = 1.0;
            lb[i] = prior[i] - 5*prior_err[i];
            ub[i] = prior[i] + 5*prior_err[i];
	}
	    //if(strcmp(name_dials[i].c_str(),"SF_SRC_Norm_O") == 0) {
	    if(i == 43) {
            prior[i] = 1.00;
	    prior_err[i] = 1.0;
            lb[i] = prior[i] - 5*prior_err[i];
            ub[i] = prior[i] + 5*prior_err[i];
	}
	    //if(strcmp(name_dials[i].c_str(),"SF_SShell_MeanF_Norm_C") == 0) {
	    if(i == 44) {
            prior[i] = 1.0;
	    //prior_err[i] = 0.4;
	    prior_err[i] = 0.5;
            lb[i] = 0.0;
            ub[i] = 2.0;
	}
	    //if(strcmp(name_dials[i].c_str(),"SF_SShell_MeanF_Norm_O") == 0) {
	    if(i == 45) {
            prior[i] = 1.0;
	    //prior_err[i] = 0.2;
	    prior_err[i] = 0.5;
            lb[i] = 0.0;
            ub[i] = 2.0;
	}
	    //if(strcmp(name_dials[i].c_str(),"SF_SShell_MeanF_PMissShape_C") == 0) {
	    if(i == 46) {
            prior[i] = 0.0;
	    prior_err[i] = 1.0;
            lb[i] = prior[i] - 5*prior_err[i];
            ub[i] = prior[i] + 5*prior_err[i];
	}
	    //if(strcmp(name_dials[i].c_str(),"SF_SShell_MeanF_PMissShape_O") == 0) {
	    if(i == 47) {
            prior[i] = 0.00;
	    prior_err[i] = 1.0;
            lb[i] = prior[i] - 5*prior_err[i];
            ub[i] = prior[i] + 5*prior_err[i];
	}
	}

	std::cout << "Checking arrays \nPriors	lb	ub\n";
	for(int i = 0; i < param_num; i++){
		std::cout << prior[i] << "	" << lb[i] << "		" << ub[i] << "\n";
	}
	//std::cout << "Initializing vectors \n";
	TVectorT<double> xsec_param_prior(param_num,a);
	TVectorT<double> xsec_param_lb(param_num,b);
	TVectorT<double> xsec_param_ub(param_num,c);

	// create covariance matrix from correlation matrix
	double cov[param_num][param_num];
	for(int i = 0; i < param_num; i++) {
		for(int j = 0; j < param_num; j++) {
			cov[i][j] = corr[i][j] * (prior_err[i] * prior_err[j]);
		}
	}
	TMatrixT<double> cov_matrix(param_num,param_num,cov[0]); 
	std::cout << "Contents of matrix: \n";
	cov_matrix.Print();

	f_output = new TFile("studies_sampKenj/inputs/parameters/xsec/xsec_covmatrix_param.root","RECREATE");
	//f_output->WriteObject(cov_matrix,"xsec_cov");
	//f_output->WriteObject(corr_matrix,"xsec_corr");
	cov_matrix.Write("xsec_cov");
	corr_matrix.Write("xsec_corr");
	f_output->WriteObject(xsec_param_name,"xsec_param_names");
	xsec_param_prior.Write("xsec_param_prior");
	xsec_param_lb.Write("xsec_param_lb");
	xsec_param_ub.Write("xsec_param_ub");
	f_output->Close();
}
