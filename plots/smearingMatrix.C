void smearingMatrix()
{
    // initialize file and tree
    TFile *infile = new TFile("studies_sampKenj/inputs/samples/sample_rootfiles/splines_event_by_event_CCcorrected.root");
    TTree *tree = (TTree*)infile->Get("sample_sum");

    // set parameters and variables
    const int SAMPLES = 7;
    float pmu, trupmu, cs, trucs, peso;
    int sample;
    // define binning arrays
    std::vector<std::vector<double>> bincos = {
        //FHC WAGASCI PM-WMRD #nu_{#mu} CC 0#pi 
        {0, 0.425, 0.525, 0.65, 0.75, 0.9, 1},    
        //FHC WAGASCI PM-BM #nu_{#mu} CC 0#pi
        {0, 0.85, 0.9, 0.94, 0.96, 0.98, 1},   
        //FHC WAGASCI PM #nu_{#mu} CC 1#pi 
        {0, 0.5, 0.63, 0.72, 0.87, 0.98, 1}, 
        //FHC WAGASCI UWG-WMRD #nu_{#mu} CC 0#pi 
        {0, 0.5, 0.64, 0.7, 0.85, 1},
        //FHC WAGASCI UWG-BM #nu_{#mu} CC 0#pi     
        {0, 0.9, 0.94, 0.96, 0.98, 1},            
        //FHC WAGASCI DWG-BM #nu_{#mu} CC 0#pi  
        {0, 0.75, 0.85, 0.9, 0.94, 0.96, 0.98, 1}, 
        //FHC WAGASCI WG #nu_{#mu} CC 1#pi 
        {0, 0.67, 0.77, 0.84, 0.9, 0.95, 0.98, 1} 
    };

    std::vector<std::vector<double>> binpmu = {
        //FHC WAGASCI PM-WMRD #nu_{#mu} CC 0#pi 
        {0, 450, 500, 550, 600, 650, 30000},
        //FHC WAGASCI PM-BM #nu_{#mu} CC 0#pi
        {0, 600, 650, 700, 800, 900, 30000},
        //FHC WAGASCI PM #nu_{#mu} CC 1#pi 
        {0, 400, 500, 550, 600, 650, 30000},
        //FHC WAGASCI UWG-WMRD #nu_{#mu} CC 0#pi 
        {0, 400, 450, 500, 550, 600, 650, 700, 30000},
        //FHC WAGASCI UWG-BM #nu_{#mu} CC 0#pi
        {0, 600, 650, 700, 750, 800, 900, 1100, 30000},
        //FHC WAGASCI DWG-BM #nu_{#mu} CC 0#pi 
        {0, 400, 450, 500, 550, 600, 650, 700, 800, 900, 1100, 1400, 30000},
        //FHC WAGASCI WG #nu_{#mu} CC 1#pi
        {0, 400, 500, 550, 600, 650, 700, 750, 800, 900, 1100, 30000},
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
    for(int isample = 0; isample < SAMPLES; isample++){
        hpmu.push_back(new TH2D("", nhist[isample].c_str(), 100, 0, 1500, 100, 0, 1500));
        hcs.push_back(new TH2D("", nhist[isample].c_str(), 100, 0, 1, 100, 0, 1));
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

        int isample = 0; 
        for(int n = 0; n < SAMPLES; n++) {
            if ( sample == nsamp[n] ) {
                isample = n;
                break;
            }
        }
        std::cout << "Sample: " << sample <<  "\tPmu Reco: " << pmu << "\tPmu True: " << trupmu 
        << "\tCosThetamu Reco: " << cs << "\tCosThetamu True: " << trucs << "\tPOTWeight: " << peso << std::endl;
        
        hpmu[isample]->Fill(trupmu, pmu, peso);
        hcs[isample]->Fill(trucs, cs, peso);
        hpmubin[isample]->Fill(trupmu, pmu, peso);
        hcsbin[isample]->Fill(trucs, cs, peso);

    }
    // draw and save plots
    TCanvas *c1 = new TCanvas();
    TCanvas *c2 = new TCanvas();
    std::string path;
    c2->SetLogx();
    c2->SetLogy();
    gStyle->SetOptStat(0);
    for(int isample = 0; isample < SAMPLES; isample++){
        c1->cd();
        hpmu[isample]->Draw("COLZ");
        path = "plots/2Dhist/smearing/plotpmu_"+nhist[isample]+".png";
        c1->SaveAs(path.c_str());
        hcs[isample]->Draw("COLZ");
        path = "plots/2Dhist/smearing/plotcos_"+nhist[isample]+".png";
        c1->SaveAs(path.c_str());
        c2->cd();
        hpmubin[isample]->Draw("COLZ");
        path = "plots/2Dhist/smearing/plotpmubin_"+nhist[isample]+".png";
        c2->SaveAs(path.c_str());
        hcsbin[isample]->Draw("COLZ");
        path = "plots/2Dhist/smearing/plotcsbin_"+nhist[isample]+".png";
        c2->SaveAs(path.c_str());
    }
}
