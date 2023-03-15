void make2DplotsWG()
{
    // initialize file and tree
    //TFile *infile = new TFile("studies_sampKenj/inputs/samples/sample_rootfiles/wagasci_sample_kenji.root");
    //TFile *infile = new TFile("studies_sampKenj/inputs/samples/sample_rootfiles/splines_event_by_event.root");
    //TFile *outfile = new TFile("plots/2Dhist/2Dplot_WG.root","RECREATE");
    TFile *infile = new TFile("studies_sampKenj/inputs/samples/sample_rootfiles/splines_event_by_event_CCcorrected.root");
    TTree *tree = (TTree*)infile->Get("sample_sum");

    // set parameters and variables
    const int SAMPLES = 7;
    float pmu, cs, peso;
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
    tree->SetBranchAddress("CosThetamu", &cs);
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
    std::vector<TH2D*> h;
    std::vector<TH2D*> hbin;
    for(int isample = 0; isample < SAMPLES; isample++){
        std::string nam = "h"+to_string(isample);
        h.push_back(new TH2D("", nhist[isample].c_str(), 50, 0.2, 1, 50, 200, 1500));
        hbin.push_back(new TH2D("", nhist[isample].c_str(), bincos[isample].size()-1, &bincos[isample][0], binpmu[isample].size()-1, &binpmu[isample][0]));
        h[isample]->SetXTitle("cos #theta_{#mu}");
        h[isample]->SetYTitle("P_{#mu}");
        hbin[isample]->SetXTitle("cos #theta_{#mu}");
        hbin[isample]->SetYTitle("P_{#mu}");
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
        std::cout << "Sample: " << sample <<  "\tPmu: " << pmu << "\tCosThetamu: " << cs << "\tPOTWeight: " << peso << std::endl;
        
        h[isample]->Fill(cs, pmu, peso);
        hbin[isample]->Fill(cs, pmu, peso);

    }
    // draw and save plots
    TCanvas *c1 = new TCanvas();
    TCanvas *c2 = new TCanvas();
    c2->SetLogy();
    gStyle->SetOptStat(0);
    for(int isample = 0; isample < SAMPLES; isample++){
        c1->cd();
        h[isample]->Draw("COLZ");
        std::string path = "plots/2Dhist/plot_"+nhist[isample]+".png";
        c1->SaveAs(path.c_str());
        c2->cd();
        hbin[isample]->Draw("COLZ");
        path = "plots/2Dhist/plotbin_"+nhist[isample]+".png";
        c2->SaveAs(path.c_str());
    }
}
