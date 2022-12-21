std::vector<double> enu = {0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 1.2, 1.5, 2.0, 2.5, 3.0, 3.5, 4.0, 5.0, 7.0, 10.0};
std::vector<int> NeutrinoCode = {14, -14};
std::vector<int> isRHC = {-3, -1 , 0, 1, -2, -2};

void generate_fluxparams()
{
    TFile *output = new TFile("studies_sampKenj/inputs/parameters/flux/flux_cov_forjointfit.root","RECREATE");
    TFile *input = new TFile("studies_sampKenj/inputs/parameters/flux/total_flux_covariance.root");

    // Get input matrix using keys, then cut out a part of the matrix using getsub
    TMatrixTSym<double> *covIn = (TMatrixTSym<double>*)input->GetKey("total_flux_cov")->ReadObj();
    // returning matrix of getsub is not a pointer CAREFUL
    TMatrixTSym<double> covOut(covIn->GetSub(80,319,80,319)); 
    //covOut.Print();

    output->cd();
    covOut.Write("total_flux_cov");
    
	ofstream file;
	//file.open("studies_sampKenj/inputs/samples/binning/simple_binning.txt");
	file.open("studies_sampKenj/inputs/parameters/flux/jointflux_binning.txt");
	
    //std::cout << "variables: SelectedSample NeutrinoCode isRHC Enu Enu\n";
    file << "variables: isRHC NeutrinoCode Enu Enu\n";
	for(int i = 0; i < isRHC.size(); i++) {
		for(int j = 0; j < NeutrinoCode.size(); j++) {
            for(int k = 0; k < (enu.size() - 1); k++) {
                //file << bins1[i] << " " << bins1[i+1] << "\n"; 
                //std::cout << SelectedSample[i] << " " << NeutrinoCode[j] << " " << isRHC[k] << " " << enu[l] << " " << enu[l+1] << "\n"; 
                file << isRHC[i] << " " << NeutrinoCode[j] << " " << enu[k] << " " << enu[k+1] << "\n"; 
            }
        }
    }
	
	file.close();
}

