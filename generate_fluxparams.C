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
    TMatrixTSym<double> covOut6(60); 
    TMatrixTSym<double> covOut7(100); 
    TMatrixTSym<double> covOut8(180); 

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
        if(i < 80 || (i > 99 && i < 160) || i > 179) continue;
        else {
            n = -1;
            m++;
            n++;
            for(int j = 0; j < covIn->GetNcols(); j++) {
                if(j < 80 || (j > 99 && j < 160) || j > 179) continue;
                else {
                    covOut5[n][m] = (*covIn)[i][j];
                    //std::cout << "Old : [" << i << ", " << j << "] : " << (*covIn)[i][j] << "\n";
                    //std::cout << "New : [" << n << ", " << m << "] : " << covOut5[n][m] << "\n\n";
                    n++;
                }
            }
        }
    }
    //covOut5.Print();
    
    n = -1;
    m = -1;
    for(int i = 0; i < covIn->GetNcols(); i++) {
        if(i < 80 || (i > 99 && i < 160) || (i > 179 && i < 240) || i > 259) continue;
        else {
            n = -1;
            m++;
            n++;
            for(int j = 0; j < covIn->GetNcols(); j++) {
                if(j < 80 || (j > 99 && j < 160) || (j > 179 && j < 240) || j > 259) continue;
                else {
                    covOut6[n][m] = (*covIn)[i][j];
                    //std::cout << "Old : [" << i << ", " << j << "] : " << (*covIn)[i][j] << "\n";
                    //std::cout << "New : [" << n << ", " << m << "] : " << covOut6[n][m] << "\n\n";
                    n++;
                }
            }
        }
    }
    //covOut6.Print();
    
    n = -1;
    m = -1;
    for(int i = 0; i < covIn->GetNcols(); i++) {
        if(i < 80 || (i > 99 && i < 160) || i > 239) continue;
        else {
            n = -1;
            m++;
            n++;
            for(int j = 0; j < covIn->GetNcols(); j++) {
                if(j < 80 || (j > 99 && j < 160)|| j > 239) continue;
                else {
                    covOut7[n][m] = (*covIn)[i][j];
                    //std::cout << "Old : [" << i << ", " << j << "] : " << (*covIn)[i][j] << "\n";
                    //std::cout << "New : [" << n << ", " << m << "] : " << covOut7[n][m] << "\n\n";
                    n++;
                }
            }
        }
    }
    //covOut7.Print();
    
    n = -1;
    m = -1;
    for(int i = 0; i < covIn->GetNcols(); i++) {
        if(i < 80 || (i > 99 && i < 160)) continue;
        else {
            n = -1;
            m++;
            n++;
            for(int j = 0; j < covIn->GetNcols(); j++) {
                if(j < 80 || (j > 99 && j < 160)) continue;
                else {
                    covOut8[n][m] = (*covIn)[i][j];
                    //std::cout << "Old : [" << i << ", " << j << "] : " << (*covIn)[i][j] << "\n";
                    //std::cout << "New : [" << n << ", " << m << "] : " << covOut8[n][m] << "\n\n";
                    n++;
                }
            }
        }
    }
    //covOut8.Print();
    
    output->cd();
    // everything is without INGRID
    covOut1.Write("total_flux_cov");
    covOut2.Write("partial_flux_cov_NoWGRHC");
    covOut3.Write("partial_flux_cov_NoWG");
    covOut4.Write("partial_flux_cov_OnlyWGFHC");
    covOut5.Write("partial_flux_cov_OnlyFHC");
    covOut6.Write("partial_flux_cov_withSK_OnlyFHC");
    covOut7.Write("partial_flux_cov_WG_OnlyFHC_ND280_all");
    covOut8.Write("partial_flux_cov_WG_OnlyFHC_ND280_all_withSK");
    output->Close();

    // Generate flux binning per cov matrix
    std::vector<double> enu = {0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 1.2, 1.5, 2.0, 2.5, 3.0, 3.5, 4.0, 5.0, 7.0, 10.0};
    std::vector<int> NeutrinoCode = {14, -14}; std::vector<int> isRHC1 = {-1, -3, 0, 1, -2, -2};
    std::vector<int> isRHC2 = {-1, 0, 1, -2, -2};
    std::vector<int> isRHC3 = {0, 1, -2, -2};
    std::vector<int> isRHC4 = {-1};
    std::vector<int> isRHC5 = {-1, 0};
    std::vector<int> isRHC6 = {-1, 0, -2};
    std::vector<int> isRHC7 = {-1, 0, 1};
    std::vector<int> isRHC8 = {-1, 0, 1, -2, -2};

	ofstream file1, file2, file3, file4, file5, file6, file7, file8;
	//file.open("studies_sampKenj/inputs/samples/binning/simple_binning.txt");
	file1.open("studies_sampKenj/inputs/parameters/flux/jointflux_binning.txt");
	file2.open("studies_sampKenj/inputs/parameters/flux/jointflux_binningNoWGRHC.txt");
	file3.open("studies_sampKenj/inputs/parameters/flux/jointflux_binningNoWG.txt");
	file4.open("studies_sampKenj/inputs/parameters/flux/jointflux_binningOnlyWGFHC.txt");
	file5.open("studies_sampKenj/inputs/parameters/flux/jointflux_binningOnlyFHC.txt");
	file6.open("studies_sampKenj/inputs/parameters/flux/jointflux_binningwithSKOnlyFHC.txt");
	file7.open("studies_sampKenj/inputs/parameters/flux/jointflux_binningWG_OnlyFHC_ND280_all.txt");
	file8.open("studies_sampKenj/inputs/parameters/flux/jointflux_binningWG_OnlyFHC_ND280_all_withSK.txt");
	
    //std::cout << "variables: SelectedSample NeutrinoCode isRHC Enu Enu\n";
    file1 << "variables: isRHC NeutrinoCode Enu Enu\n";
    file2 << "variables: isRHC NeutrinoCode Enu Enu\n";
    file3 << "variables: isRHC NeutrinoCode Enu Enu\n";
    file4 << "variables: isRHC NeutrinoCode Enu Enu\n";
    file5 << "variables: isRHC NeutrinoCode Enu Enu\n";
    file6 << "variables: isRHC NeutrinoCode Enu Enu\n";
    file7 << "variables: isRHC NeutrinoCode Enu Enu\n";
    file8 << "variables: isRHC NeutrinoCode Enu Enu\n";

	for(int i = 0; i < isRHC1.size(); i++) {
		for(int j = 0; j < NeutrinoCode.size(); j++) {
            for(int k = 0; k < (enu.size() - 1); k++) {
                //std::cout << SelectedSample[i] << " " << NeutrinoCode[j] << " " << isRHC[k] << " " << enu[l] << " " << enu[l+1] << "\n"; 
                file1 << isRHC1[i] << " " << NeutrinoCode[j] << " " << enu[k] << " " << enu[k+1] << "\n"; 
            }
        }
    }

	for(int i = 0; i < isRHC2.size(); i++) {
		for(int j = 0; j < NeutrinoCode.size(); j++) {
            for(int k = 0; k < (enu.size() - 1); k++) {
                //std::cout << SelectedSample[i] << " " << NeutrinoCode[j] << " " << isRHC[k] << " " << enu[l] << " " << enu[l+1] << "\n"; 
                file2 << isRHC2[i] << " " << NeutrinoCode[j] << " " << enu[k] << " " << enu[k+1] << "\n"; 
            }
        }
    }
	

	for(int i = 0; i < isRHC3.size(); i++) {
		for(int j = 0; j < NeutrinoCode.size(); j++) {
            for(int k = 0; k < (enu.size() - 1); k++) {
                //std::cout << SelectedSample[i] << " " << NeutrinoCode[j] << " " << isRHC[k] << " " << enu[l] << " " << enu[l+1] << "\n"; 
                file3 << isRHC3[i] << " " << NeutrinoCode[j] << " " << enu[k] << " " << enu[k+1] << "\n"; 
            }
        }
    }
	
	for(int i = 0; i < isRHC4.size(); i++) {
		for(int j = 0; j < NeutrinoCode.size(); j++) {
            for(int k = 0; k < (enu.size() - 1); k++) {
                //std::cout << SelectedSample[i] << " " << NeutrinoCode[j] << " " << isRHC[k] << " " << enu[l] << " " << enu[l+1] << "\n"; 
                file4 << isRHC4[i] << " " << NeutrinoCode[j] << " " << enu[k] << " " << enu[k+1] << "\n"; 
            }
        }
    }

    for(int i = 0; i < isRHC5.size(); i++) {
        for(int k = 0; k < (enu.size() - 1); k++) {
            //std::cout << SelectedSample[i] << " " << NeutrinoCode[j] << " " << isRHC[k] << " " << enu[l] << " " << enu[l+1] << "\n"; 
            file5 << isRHC5[i] << " " << NeutrinoCode[0] << " " << enu[k] << " " << enu[k+1] << "\n"; 
        }
    }

    for(int i = 0; i < isRHC6.size(); i++) {
        for(int k = 0; k < (enu.size() - 1); k++) {
            //std::cout << SelectedSample[i] << " " << NeutrinoCode[j] << " " << isRHC[k] << " " << enu[l] << " " << enu[l+1] << "\n"; 
            file6 << isRHC6[i] << " " << NeutrinoCode[0] << " " << enu[k] << " " << enu[k+1] << "\n"; 
        }
    }

	for(int i = 0; i < isRHC7.size(); i++) {
		for(int j = 0; j < NeutrinoCode.size(); j++) {
            for(int k = 0; k < (enu.size() - 1); k++) {
                //std::cout << SelectedSample[i] << " " << NeutrinoCode[j] << " " << isRHC[k] << " " << enu[l] << " " << enu[l+1] << "\n"; 
                if(isRHC7[i] == -1) {
                file7 << isRHC7[i] << " 14 " << enu[k] << " " << enu[k+1] << "\n"; 
                }
                else {
                file7 << isRHC7[i] << " " << NeutrinoCode[j] << " " << enu[k] << " " << enu[k+1] << "\n"; 
                }
            }
        }
    }

	for(int i = 0; i < isRHC8.size(); i++) {
		for(int j = 0; j < NeutrinoCode.size(); j++) {
            for(int k = 0; k < (enu.size() - 1); k++) {
                //std::cout << SelectedSample[i] << " " << NeutrinoCode[j] << " " << isRHC[k] << " " << enu[l] << " " << enu[l+1] << "\n"; 
                if(isRHC8[i] == -1) {
                file8 << isRHC8[i] << " 14 " << enu[k] << " " << enu[k+1] << "\n"; 
                }
                else {
                file8 << isRHC8[i] << " " << NeutrinoCode[j] << " " << enu[k] << " " << enu[k+1] << "\n"; 
                }
            }
        }
    }


	file1.close();
	file2.close();
	file3.close();
	file4.close();
	file5.close();
	file6.close();
	file7.close();
	file8.close();
}

