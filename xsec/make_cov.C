void make_cov()
{
    TFile *input = new TFile("xsec_sampKenj/inputs/parameters/xsec/xsec_covmatrix_param.root");
    TFile *output = new TFile("xsec_sampKenj/inputs/parameters/xsec/2p2h_cov.root","RECREATE");

    // Get input matrix using keys, then cut out a part of the matrix using getsub
    TMatrixTSym<double> *covIn = (TMatrixTSym<double>*)input->GetKey("xsec_cov")->ReadObj();
    TMatrixTSym<double> covOut1(2); 

    int n = -1;
    int m = -1;
    for(int i = 0; i < covIn->GetNcols(); i++) {
        if(i < 6 || i > 7) continue;
        else {
            n = -1;
            m++;
            n++;
            for(int j = 0; j < covIn->GetNcols(); j++) {
                if(j < 6 || j > 7) continue;
                else {
                    covOut1[n][m] = (*covIn)[i][j];
                    std::cout << "Old : [" << i << ", " << j << "] : " << (*covIn)[i][j] << "\n";
                    std::cout << "New : [" << n << ", " << m << "] : " << covOut1[n][m] << "\n\n";
                    n++;
                }
            }
        }
    }
    covOut1.Print();
    covOut1.Write("xsec_cov");
    output->Close();
}

