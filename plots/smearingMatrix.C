void smearingMatrix()
{
    // initialize file and tree
    TFile *infile = new TFile("studies_sampKenj/inputs/samples/sample_rootfiles/splines_event_by_event_CCcorrected.root");
    TTree *tree = (TTree*)infile->Get("sample_sum");
    TFile *outfile = new TFile("plots/2Dhist/smearing/plots.root","RECREATE");

    // set parameters and variables
    const int SAMPLES = 7;
    float pmu, trupmu, cs, trucs, peso;
    int sample;
    int nbin = 100;
    // define binning arrays
    std::vector<std::vector<double>> bincos = {
        //FHC WAGASCI PM-WMRD #nu_{#mu} CC 0#pi 
        {0., 0.425, 0.525, 0.65, 0.75, 0.9},    
        //FHC WAGASCI PM-BM #nu_{#mu} CC 0#pi
        {0.5, 0.85, 0.9, 0.94, 0.96, 0.98, 1},   
        //FHC WAGASCI PM #nu_{#mu} CC 1#pi 
        {0., 0.5, 0.63, 0.72, 0.87, 0.98, 1}, 
        //FHC WAGASCI UWG-WMRD #nu_{#mu} CC 0#pi 
        {0., 0.5, 0.64, 0.7, 0.9},
        //FHC WAGASCI UWG-BM #nu_{#mu} CC 0#pi     
        {0.7, 0.9, 0.94, 0.96, 0.98, 1},            
        //FHC WAGASCI DWG-BM #nu_{#mu} CC 0#pi  
        {0., 0.75, 0.85, 0.9, 0.94, 0.96, 0.98, 1}, 
        //FHC WAGASCI WG #nu_{#mu} CC 1#pi 
        {0., 0.67, 0.77, 0.84, 0.9, 0.95, 0.98, 1} 
    };

    std::vector<std::vector<double>> binpmu = {
        //FHC WAGASCI PM-WMRD #nu_{#mu} CC 0#pi 
        {200, 450, 500, 550, 600, 650, 1000},
        //FHC WAGASCI PM-BM #nu_{#mu} CC 0#pi
        {200, 600, 650, 700, 800, 900, 2000},
        //FHC WAGASCI PM #nu_{#mu} CC 1#pi 
        {200, 400, 500, 550, 600, 650, 2000},
        //FHC WAGASCI UWG-WMRD #nu_{#mu} CC 0#pi 
        {200, 450, 500, 550, 600, 650, 700, 1000},
        //FHC WAGASCI UWG-BM #nu_{#mu} CC 0#pi
        {200, 650, 700, 750, 800, 900, 1100, 2000},
        //FHC WAGASCI DWG-BM #nu_{#mu} CC 0#pi 
        {200, 400, 450, 500, 550, 600, 650, 700, 800, 900, 1100, 1400, 2000},
        //FHC WAGASCI WG #nu_{#mu} CC 1#pi
        {200, 400, 500, 550, 600, 650, 700, 750, 800, 900, 1100, 2000},
    };
    int nevent = tree->GetEntries();

    // set branches
    tree->SetBranchAddress("Pmu", &pmu);
    tree->SetBranchAddress("TruePmu", &trupmu);
    tree->SetBranchAddress("CosThetamu", &cs);
    tree->SetBranchAddress("TrueCosThetamu", &trucs);
    tree->SetBranchAddress("POTWeight", &peso);
    tree->SetBranchAddress("SelectedSample", &sample);
    
    int nsamp[SAMPLES] = {
        // FHC WAGASCI
        151, 152, 153, 154, 155, 157, 158
    };

    std::string nhist[SAMPLES] = {
        "FHC WAGASCI PM-WMRD #nu_{#mu} CC-0#pi", 
        "FHC WAGASCI PM-BM #nu_{#mu} CC-0#pi",
        "FHC WAGASCI PM #nu_{#mu} CC-1#pi", 
        "FHC WAGASCI UWG-WMRD #nu_{#mu} CC-0#pi", 
        "FHC WAGASCI UWG-BM #nu_{#mu} CC-0#pi",
        "FHC WAGASCI DWG-BM #nu_{#mu} CC-0#pi", 
        "FHC WAGASCI WG #nu_{#mu} CC-1#pi"
    };

    // create histos
    std::vector<TH2D*> hpmu;
    std::vector<TH2D*> hpmubin;
    std::vector<TH2D*> hcs;
    std::vector<TH2D*> hcsbin;

    // initialize histos
    for(int isample = 0; isample < SAMPLES; isample++){
        hpmu.push_back(new TH2D("", nhist[isample].c_str(), nbin, 0, 3000, nbin, 0, 3000));
        hcs.push_back(new TH2D("", nhist[isample].c_str(), nbin, 0.3, 1, nbin, 0.3, 1));
        hpmubin.push_back(new TH2D("", nhist[isample].c_str(), binpmu[isample].size()-1, &binpmu[isample][0], binpmu[isample].size()-1, &binpmu[isample][0]));
        hcsbin.push_back(new TH2D("", nhist[isample].c_str(), bincos[isample].size()-1, &bincos[isample][0], bincos[isample].size()-1, &bincos[isample][0]));
        hpmu[isample]->SetXTitle("P_{#mu} True");
        hpmu[isample]->SetYTitle("P_{#mu} Reco");
        hcs[isample]->SetXTitle("cos #theta_{#mu} True");
        hcs[isample]->SetYTitle("cos #theta_{#mu} Reco");
        hpmubin[isample]->SetXTitle("P_{#mu} True");
        hpmubin[isample]->SetYTitle("P_{#mu} Reco");
        hcsbin[isample]->SetXTitle("cos #theta_{#mu} True");
        hcsbin[isample]->SetYTitle("cos #theta_{#mu} Reco");
    }
    
    for(int ientry = 0; ientry < nevent; ientry++) {
        tree->GetEntry(ientry);

        // identify sample
        int isample = 0; 
        for(int n = 0; n < SAMPLES; n++) {
            if ( sample == nsamp[n] ) {
                isample = n;
                break;
            }
        }
        // output
        std::cout << "Sample: " << sample <<  "\tPmu Reco: " << pmu << "\tPmu True: " << trupmu 
        << "\tCosThetamu Reco: " << cs << "\tCosThetamu True: " << trucs << "\tPOTWeight: " << peso << std::endl;
        
        // to work around the prob of large bins, put all large/small values in one bin
        //if(pmu > 1500) pmu = 1499;
        //if(trupmu > 1500) trupmu = 1499;
        //if(cs < 0.3) cs = 0.31;
        //if(trucs < 0.3) trucs = 0.31;


        // fill histos
        hpmu[isample]->Fill(trupmu, pmu, peso);
        hcs[isample]->Fill(trucs, cs, peso);
        hpmubin[isample]->Fill(trupmu, pmu, peso);
        hcsbin[isample]->Fill(trucs, cs, peso);
        //hpmu[isample]->Fill(trupmu, pmu);
        //hcs[isample]->Fill(trucs, cs);
        //hpmubin[isample]->Fill(trupmu, pmu);
        //hcsbin[isample]->Fill(trucs, cs);

    }

    TCanvas *c1 = new TCanvas();
    std::string path = "plots/2Dhist/smearing/";
    //std::string path = "plots/2Dhist/smearing_without_weight/";
    std::string nfile;
    gStyle->SetOptStat(0);
    outfile->cd();
    for(int isample = 0; isample < SAMPLES; isample++){
    // rescale bins using truth parameters, divide by bin content per column
        double trubin = 0;
        // for finely binned matrices
        for(int i = 0; i<nbin; i++) {
            for(int j = 0; j<nbin; j++) {
                trubin = hpmu[isample]->Integral(i+1,i+1,1,nbin);
                if(hpmu[isample]->GetBinContent(i+1,j+1) == 0) {
                    hpmu[isample]->SetBinContent(i+1,j+1,0);
                }
                else {
                    hpmu[isample]->SetBinContent(i+1,j+1,hpmu[isample]->GetBinContent(i+1,j+1)/trubin);
                }
                trubin = hcs[isample]->Integral(i+1,i+1,1,nbin);
                if(hcs[isample]->GetBinContent(i+1,j+1) == 0) {
                    hcs[isample]->SetBinContent(i+1,j+1,0);
                }
                else {
                    hcs[isample]->SetBinContent(i+1,j+1,hcs[isample]->GetBinContent(i+1,j+1)/trubin);
                }
            }
        }
        // for matrices using my binning
        // pmu matrices
        //std::cout << "Pmu: Sample: " << nhist[isample] << "\n";
        for(int i = 0; i<binpmu[isample].size()-1; i++) {
            trubin = hpmubin[isample]->Integral(i+1,i+1,1,binpmu[isample].size()-1);
            for(int j = 0; j<binpmu[isample].size()-1; j++) {
                if(hpmubin[isample]->GetBinContent(i+1,j+1) == 0) {
                    hpmubin[isample]->SetBinContent(i+1,j+1,0);
                }
                else {
                    hpmubin[isample]->SetBinContent(i+1,j+1,hpmubin[isample]->GetBinContent(i+1,j+1)/trubin);
                    //std::cout << "xbin: " << i+1 << " " << "ybin: " << j+1 << "\n";
                    //std::cout << "True bin content: " << trubin << "\n";
                    //std::cout << "Old bin content: " << hpmubin[isample]->GetBinContent(i+1,j+1) << "\n";
                    //std::cout << "New bin content: " << hpmubin[isample]->GetBinContent(i+1,j+1)/trubin << "\n\n";
                }
            }
        }
        // cos matrices
        //std::cout << "Cos: Sample: " << nhist[isample] << "\n";
        for(int i = 0; i<bincos[isample].size()-1; i++) {
            trubin = hcsbin[isample]->Integral(i+1,i+1,1,bincos[isample].size()-1);
            for(int j = 0; j<bincos[isample].size()-1; j++) {
                if(hcsbin[isample]->GetBinContent(i+1,j+1) == 0) {
                    hcsbin[isample]->SetBinContent(i+1,j+1,0);
                }
                else {
                    hcsbin[isample]->SetBinContent(i+1,j+1,hcsbin[isample]->GetBinContent(i+1,j+1)/trubin);
                    //std::cout << "xbin: " << i+1 << " " << "ybin: " << j+1 << "\n";
                    //std::cout << "True bin content: " << trubin << "\n";
                    //std::cout << "Old bin content: " << hcsbin[isample]->GetBinContent(i+1,j+1) << "\n";
                    //std::cout << "New bin content: " << hcsbin[isample]->GetBinContent(i+1,j+1)/trubin << "\n\n";
                }
            }
        }

        // draw and save plots
        c1->cd();
        hpmu[isample]->Draw("COLZ");
        nfile = path+"unbinned/pmu/plotpmu_"+nhist[isample]+".png";
        c1->SaveAs(nfile.c_str());
        c1->Write();
        hcs[isample]->Draw("COLZ");
        nfile = path+"unbinned/cos/plotcos_"+nhist[isample]+".png";
        c1->SaveAs(nfile.c_str());
        c1->Write();
        //c2->cd();
        hpmubin[isample]->Draw("COLZ");
        nfile = path+"binned/pmu/plotpmubin_"+nhist[isample]+".png";
        c1->SaveAs(nfile.c_str());
        c1->Write();
        hcsbin[isample]->Draw("COLZ");
        nfile = path+"binned/cos/plotcsbin_"+nhist[isample]+".png";
        c1->SaveAs(nfile.c_str());
        c1->Write();
    }
    outfile->Close();
}
