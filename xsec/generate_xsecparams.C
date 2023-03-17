#include <fstream>
#include <iostream>
#include <string>
#include <vector>

std::vector<std::string> name_spline = {"MAQE","Q2_norm_5","Q2_norm_6","Q2_norm_7","Optical_Potential_O","Optical_Potential_C","2p2h_Norm_C","2p2h_Norm_O","2p2h_shape_C_NN","2p2h_shape_C_np","2p2h_shape_O_NN","2p2h_shape_O_np","PNNN_Shape","RES_Eb_C_numu","RES_Eb_O_numu","ISO_BKG","CA5","MARES","FEFABS","FEFCXH","FEFCX","FEFINEL","FEFQEH","FEFQE","Nucleon_FSI","CC_norm_nu","CC_MultiPi_norm_nu"};
TObjArray *xsec_param_name = NULL;
TFile *f_output = NULL;

void fillnames()
{
    xsec_param_name = new TObjArray();
	std::vector<TObjString*> name;
    for(int i = 0; i < name_spline.size(); i++) {
		name.push_back(new TObjString);
		name[i]->SetString(name_spline[i].c_str());
		std::cout << "Adding to array: " << name[i]->GetString() << " \n";
		xsec_param_name->Add(name[i]);
	}
}

void generate_xsecparams()
{
	fillnames();
	int param_num = xsec_param_name->GetEntries();
	//std::cout << "\nEntries in array: " << param_num << "\n";
	//std::cout << "\nChecking string array contents: \n";
	xsec_param_name->Print();

	// fill prior vectors and their errors
	double prior[param_num], prior_err[param_num], lb[param_num], ub[param_num];
	double *a = prior;
	double *b = lb;
	double *c = ub;
    for(int i = 0; i < param_num; i++) {

        //if(strcmp(name_dials[i].c_str(),"MAQE") == 0) {
        if(i == 0) {
            prior[i] = 1.00;
            lb[i] = 0.0;
            ub[i] = 2.0;
        }
        //if(strcmp(name_dials[i].c_str(),"Q2_norm_1") == 0) {
        if(i == 1) {
            prior[i] = 1.00;
            lb[i] = 0.0;
            ub[i] = 2.0;
        }
        //if(strcmp(name_dials[i].c_str(),"Q2_norm_2") == 0) {
        if(i == 2) {
            prior[i] = 1.00;
            lb[i] = 0.0;
            ub[i] = 2.0;
        }
        //if(strcmp(name_dials[i].c_str(),"Q2_norm_3") == 0) {
        if(i == 3) {
            prior[i] = 1.00;
            lb[i] = 0.0;
            ub[i] = 2.0;
        }
        //if(strcmp(name_dials[i].c_str(),"Optical_Potential_O") == 0) {
        if(i == 4) {
            prior[i] = 1.00;
            lb[i] = 0.0;
            ub[i] = 2.0;
        }

        //if(strcmp(name_dials[i].c_str(),"Optical_Potential_C") == 0) {
        if(i == 5) {
            prior[i] = 1.00;
            lb[i] = 0.0;
            ub[i] = 2.0;
        }

        //if(strcmp(name_dials[i].c_str(),"2p2h_Norm_C") == 0) {
        if(i == 6) {
            prior[i] = 1.00;
            lb[i] = 0.0;
            ub[i] = 2.0;
        }

        //if(strcmp(name_dials[i].c_str(),"2p2h_Norm_O") == 0) {
        if(i == 7) {
            prior[i] = 1.00;
            lb[i] = 0.0;
            ub[i] = 2.0;
        }

        //if(strcmp(name_dials[i].c_str(),"2p2h_shape_C_NN") == 0) {
        if(i == 8) {
            prior[i] = 1.0;
            lb[i] = 0.0;
            ub[i] = 2.0;
        }

        //if(strcmp(name_dials[i].c_str(),"2p2h_shape_C_np") == 0) {
        if(i == 9) {
            prior[i] = 1.0;
            lb[i] = 0.0;
            ub[i] = 2.0;
        }

        //if(strcmp(name_dials[i].c_str(),"2p2h_shape_O_NN") == 0) {
        if(i == 10) {
            prior[i] = 1.0;
            lb[i] = 0.0;
            ub[i] = 2.0;
        }

        //if(strcmp(name_dials[i].c_str(),"2p2h_shape_O_np") == 0) {
        if(i == 11) {
            prior[i] = 1.0;
            lb[i] = 0.0;
            ub[i] = 2.0;
        }

        //if(strcmp(name_dials[i].c_str(),"PNNN_Shape") == 0) {
        if(i == 12) {
            prior[i] = 1.0;
            lb[i] = 0.0;
            ub[i] = 2.0;
        }

        //if(strcmp(name_dials[i].c_str(),"RES_Eb_C_numu") == 0) {
        if(i == 13) {
            prior[i] = 0.0;
            lb[i] = 0.0;
            ub[i] = 2.0;
        }

        //if(strcmp(name_dials[i].c_str(),"RES_Eb_O_numu") == 0) {
        if(i == 14) {
            prior[i] = 0.0;
            lb[i] = -0.5;
            ub[i] = 2.0;
        }
        //if(strcmp(name_dials[i].c_str(),"ISO_BKG") == 0) {
        if(i == 15) {
            prior[i] = 1.0;
            lb[i] = -0.5;
            ub[i] = 2.0;
        }

        //if(strcmp(name_dials[i].c_str(),"CA5") == 0) {
        if(i == 16) {
            prior[i] = 1.0;
            lb[i] = 0.0;
            ub[i] = 2.0;
        }

        //if(strcmp(name_dials[i].c_str(),"MARES") == 0) {
        if(i == 17) {
            prior[i] = 1.0;
            lb[i] = 0.0;
            ub[i] = 2.0;
        }

        //if(strcmp(name_dials[i].c_str(),"FEFABS") == 0) {
        if(i == 18) {
            prior[i] = 1.0;
            lb[i] = 0.0;
            ub[i] = 2.0;
        }

        //if(strcmp(name_dials[i].c_str(),"FEFCXH") == 0) {
        if(i == 19) {
            prior[i] = 1.0;
            lb[i] = 0.0;
            ub[i] = 2.0;
        }

        //if(strcmp(name_dials[i].c_str(),"FEFCX") == 0) {
        if(i == 20) {
            prior[i] = 1.0;
            lb[i] = 0.0;
            ub[i] = 2.0;
        }

        //if(strcmp(name_dials[i].c_str(),"FEFINEL") == 0) {
        if(i == 21) {
            prior[i] = 1.0;
            lb[i] = 0.0;
            ub[i] = 2.0;
        }

        //if(strcmp(name_dials[i].c_str(),"FEFQEH") == 0) {
        if(i == 22) {
            prior[i] = 1.0;
            lb[i] = 0.0;
            ub[i] = 2.0;
        }

        //if(strcmp(name_dials[i].c_str(),"FEFQE") == 0) {
        if(i == 23) {
            prior[i] = 1.00;
            lb[i] = 0.0;
            ub[i] = 2.0;
        }

        //if(strcmp(name_dials[i].c_str(),"Nucleon_FSI") == 0) {
        if(i == 24) {
            prior[i] = 1.0;
            lb[i] = 0.0;
            ub[i] = 2.0;
        }
        //if(strcmp(name_dials[i].c_str(),"CC_norm_nu") == 0) {
        if(i == 25) {
            prior[i] = 1.00;
            lb[i] = 0.0;
            ub[i] = 2.0;
        }
        //if(strcmp(name_dials[i].c_str(),"CC_MultiPi_norm_nu") == 0) {
        if(i == 26) {
            prior[i] = 1.00;
            lb[i] = 0.0;
            ub[i] = 2.0;
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

	// get covariance matrix from Kenji's files
    TFile *input = new TFile("CC0pi_fitting_materials/pmu/covariance/wagasci_xsec_cov_cc0pi_both.root");
	TMatrixTSym<double> *cov_matrix = (TMatrixTSym<double>*)input->GetKey("xsec_cov")->ReadObj(); 
	std::cout << "Contents of matrix: \n";
	cov_matrix->Print();

	f_output = new TFile("xsec_sampKenj/inputs/parameters/xsec/xsec_covmatrix_param.root","RECREATE");
	//f_output->WriteObject(cov_matrix,"xsec_cov");
	//f_output->WriteObject(corr_matrix,"xsec_corr");
	cov_matrix->Write("xsec_cov");
	f_output->WriteObject(xsec_param_name,"xsec_param_names");
	xsec_param_prior.Write("xsec_param_prior");
	xsec_param_lb.Write("xsec_param_lb");
	xsec_param_ub.Write("xsec_param_ub");
	f_output->Close();
}
