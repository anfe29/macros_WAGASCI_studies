void generate_fluxparams()
{
    TFile *input = new TFile("studies_sampKenj/inputs/parameters/flux/total_flux_covariance.root");
    TFile *output = new TFile("studies_sampKenj/inputs/parameters/flux/flux_cov_forjointfit.root","RECREATE");

    // Get input matrix using keys, then cut out a part of the matrix using getsub
    TMatrixTSym<double> *covIn = (TMatrixTSym<double>*)input->GetKey("total_flux_cov")->ReadObj();
    TMatrixTSym<double> covOut1(240); 
    TMatrixTSym<double> covOut2(200); 
    TMatrixTSym<double> covOut3(160); 
    TMatrixTSym<double> covOut4(40); 
    TMatrixTSym<double> covOut5(40); 

    int n = -1;
    int m = -1;
    for(int i = 0; i < covIn->GetNcols(); i++) {
        if(i < 80) continue;
        else {
            n = -1;
            m++;
            n++;
            for(int j = 0; j < covIn->GetNcols(); j++) {
                if(j < 80) continue;
                else {
                    covOut1[n][m] = (*covIn)[i][j];
                    //std::cout << "Old : [" << i << ", " << j << "] : " << (*covIn)[i][j] << "\n";
                    //std::cout << "New : [" << n << ", " << m << "] : " << covOut1[n][m] << "\n\n";
                    n++;
                }
            }
        }
    }
    //covOut1.Print();

    n = -1;
    m = -1;
    for(int i = 0; i < covIn->GetNcols(); i++) {
        if(i < 80 || (i > 119 && i < 160)) continue;
        else {
            n = -1;
            m++;
            n++;
            for(int j = 0; j < covIn->GetNcols(); j++) {
                if(j < 80 || (j > 119 && j < 160)) continue;
                else {
                    covOut2[n][m] = (*covIn)[i][j];
                    //std::cout << "Old : [" << i << ", " << j << "] : " << (*covIn)[i][j] << "\n";
                    //std::cout << "New : [" << n << ", " << m << "] : " << covOut2[n][m] << "\n\n";
                    n++;
                }
            }
        }
    }
    //covOut2.Print();

    n = -1;
    m = -1;
    for(int i = 0; i < covIn->GetNcols(); i++) {
        if(i < 160) continue;
        else {
            n = -1;
            m++;
            n++;
            for(int j = 0; j < covIn->GetNcols(); j++) {
                if(j < 160) continue;
                else {
                    covOut3[n][m] = (*covIn)[i][j];
                    //std::cout << "Old : [" << i << ", " << j << "] : " << (*covIn)[i][j] << "\n";
                    //std::cout << "New : [" << n << ", " << m << "] : " << covOut3[n][m] << "\n\n";
                    n++;
                }
            }
        }
    }
    //covOut3.Print();

    n = -1;
    m = -1;
    for(int i = 0; i < covIn->GetNcols(); i++) {
        if(i < 80 || i > 119) continue;
        else {
            n = -1;
            m++;
            n++;
            for(int j = 0; j < covIn->GetNcols(); j++) {
                if(j < 80 || j > 119) continue;
                else {
                    covOut4[n][m] = (*covIn)[i][j];
                    //std::cout << "Old : [" << i << ", " << j << "] : " << (*covIn)[i][j] << "\n";
                    //std::cout << "New : [" << n << ", " << m << "] : " << covOut4[n][m] << "\n\n";
                    n++;
                }
            }
        }
    }
    //covOut4.Print();
    
    n = -1;
    m = -1;
    for(int i = 0; i < covIn->GetNcols(); i++) {
        if(i < 80 || (i > 99 && i < 120) || i > 139) continue;
        else {
            n = -1;
            m++;
            n++;
            for(int j = 0; j < covIn->GetNcols(); j++) {
                if(j < 80 || (j > 99 && j < 120) || j > 139) continue;
                else {
                    covOut5[n][m] = (*covIn)[i][j];
                    std::cout << "Old : [" << i << ", " << j << "] : " << (*covIn)[i][j] << "\n";
                    std::cout << "New : [" << n << ", " << m << "] : " << covOut5[n][m] << "\n\n";
                    n++;
                }
            }
        }
    }
    //covOut5.Print();
    
    output->cd();
    covOut1.Write("total_flux_cov");
    covOut2.Write("partial_flux_cov_NoWGRHC");
    covOut3.Write("partial_flux_cov_NoWG");
    covOut4.Write("partial_flux_cov_OnlyWG");
    covOut5.Write("partial_flux_cov_OnlyFHC");
    output->Close();

    // Generate flux binning per cov matrix
    std::vector<double> enu = {0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 1.2, 1.5, 2.0, 2.5, 3.0, 3.5, 4.0, 5.0, 7.0, 10.0};
    std::vector<int> NeutrinoCode = {14, -14};
    std::vector<int> isRHC1 = {-1, -3, 0, 1, -2, -2};
    std::vector<int> isRHC2 = {-1, 0, 1, -2, -2};
    std::vector<int> isRHC3 = {0, 1, -2, -2};
    std::vector<int> isRHC4 = {-1};
    std::vector<int> isRHC5 = {-1, 0};

	ofstream file1, file2, file3, file4, file5;
	//file.open("studies_sampKenj/inputs/samples/binning/simple_binning.txt");
	file1.open("studies_sampKenj/inputs/parameters/flux/jointflux_binning.txt");
	file2.open("studies_sampKenj/inputs/parameters/flux/jointflux_binningNoWGRHC.txt");
	file3.open("studies_sampKenj/inputs/parameters/flux/jointflux_binningNoWG.txt");
	file4.open("studies_sampKenj/inputs/parameters/flux/jointflux_binningOnlyWG.txt");
	file5.open("studies_sampKenj/inputs/parameters/flux/jointflux_binningOnlyFHC.txt");
	
    //std::cout << "variables: SelectedSample NeutrinoCode isRHC Enu Enu\n";
    file1 << "variables: isRHC NeutrinoCode Enu Enu\n";
    file2 << "variables: isRHC NeutrinoCode Enu Enu\n";
    file3 << "variables: isRHC NeutrinoCode Enu Enu\n";
    file4 << "variables: isRHC NeutrinoCode Enu Enu\n";
    file5 << "variables: isRHC NeutrinoCode Enu Enu\n";

	for(int i = 0; i < isRHC1.size(); i++) {
		for(int j = 0; j < NeutrinoCode.size(); j++) {
            for(int k = 0; k < (enu.size() - 1); k++) {
                //file << bins1[i] << " " << bins1[i+1] << "\n"; 
                //std::cout << SelectedSample[i] << " " << NeutrinoCode[j] << " " << isRHC[k] << " " << enu[l] << " " << enu[l+1] << "\n"; 
                file1 << isRHC1[i] << " " << NeutrinoCode[j] << " " << enu[k] << " " << enu[k+1] << "\n"; 
            }
        }
    }

	for(int i = 0; i < isRHC2.size(); i++) {
		for(int j = 0; j < NeutrinoCode.size(); j++) {
            for(int k = 0; k < (enu.size() - 1); k++) {
                //file << bins1[i] << " " << bins1[i+1] << "\n"; 
                //std::cout << SelectedSample[i] << " " << NeutrinoCode[j] << " " << isRHC[k] << " " << enu[l] << " " << enu[l+1] << "\n"; 
                file2 << isRHC2[i] << " " << NeutrinoCode[j] << " " << enu[k] << " " << enu[k+1] << "\n"; 
            }
        }
    }
	

	for(int i = 0; i < isRHC3.size(); i++) {
		for(int j = 0; j < NeutrinoCode.size(); j++) {
            for(int k = 0; k < (enu.size() - 1); k++) {
                //file << bins1[i] << " " << bins1[i+1] << "\n"; 
                //std::cout << SelectedSample[i] << " " << NeutrinoCode[j] << " " << isRHC[k] << " " << enu[l] << " " << enu[l+1] << "\n"; 
                file3 << isRHC3[i] << " " << NeutrinoCode[j] << " " << enu[k] << " " << enu[k+1] << "\n"; 
            }
        }
    }
	
	for(int i = 0; i < isRHC4.size(); i++) {
		for(int j = 0; j < NeutrinoCode.size(); j++) {
            for(int k = 0; k < (enu.size() - 1); k++) {
                //file << bins1[i] << " " << bins1[i+1] << "\n"; 
                //std::cout << SelectedSample[i] << " " << NeutrinoCode[j] << " " << isRHC[k] << " " << enu[l] << " " << enu[l+1] << "\n"; 
                file4 << isRHC4[i] << " " << NeutrinoCode[j] << " " << enu[k] << " " << enu[k+1] << "\n"; 
            }
        }
    }

    for(int i = 0; i < isRHC5.size(); i++) {
        for(int k = 0; k < (enu.size() - 1); k++) {
            //file << bins1[i] << " " << bins1[i+1] << "\n"; 
            //std::cout << SelectedSample[i] << " " << NeutrinoCode[j] << " " << isRHC[k] << " " << enu[l] << " " << enu[l+1] << "\n"; 
            file5 << isRHC5[i] << " " << NeutrinoCode[0] << " " << enu[k] << " " << enu[k+1] << "\n"; 
        }
    }

	file1.close();
	file2.close();
	file3.close();
	file4.close();
	file5.close();
}

