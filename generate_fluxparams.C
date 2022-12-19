std::vector<double> enu = {0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 1.2, 1.5, 2.0, 2.5, 3.0, 3.5, 4.0, 5.0, 7.0, 10.0};
std::vector<int> isRHC = {-2, 0, 1};
std::vector<int> SelectedSample = {101, 102, 103, 111, 112, 113, 151, 152, 153, 154, 155, 157, 158}; 

void generate_fluxparams()
{
    TFile *output = new TFile("studies_sampKenj/inputs/parameters/flux/flux_cov_forjointfit.root","RECREATE");
    TFile *input = new TFile("studies_sampKenj/inputs/parameters/flux/total_flux_covariance.root");

    TMatrixTSym<double> *cov = (TMatrixTSym<double>*)input->GetKey("total_flux_cov")->ReadObj(); 
    //cov->Print();
    // resize flux matrix to get only the dectors we want
    cov->ResizeTo(81,320,81,320);
    cov->Print();

    output->cd();
    output->WriteObject(cov,"total_flux_cov");
    
	ofstream file;
	//file.open("studies_sampKenj/inputs/samples/binning/simple_binning.txt");
	file.open("studies_sampKenj/inputs/samples/flux/jointflux_binning.txt");
	
	//file << "variables: Pmu Pmu CosThetamu CosThetamu Enu Enu Q2 Q2\n";
	file << "variables:  \n";
	for(int i = 0; i < (bins1.size() - 1); i++) {
		//for(int j = 0; j < (bins2.size() - 1); j++) {
		file << bins1[i] << " " << bins1[i+1] << "\n"; 
		//file << bins3[i] << " " << bins3[i+1] << " " << bins4[j] << " " << bins4[j+1] <<" \n";
		//}
	}
	
	file.close();
}

