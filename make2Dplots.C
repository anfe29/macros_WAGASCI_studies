void make2Dplots()
{
    // initialize file and tree
    //TFile *infile = new TFile("studies_sampKenj/inputs/samples/sample_rootfiles/wagasci_sample_kenji.root");
    //TFile *infile = new TFile("studies_sampKenj/inputs/samples/sample_rootfiles/splines_event_by_event.root");
    TFile *outfile = new TFile("plots/2Dhist/2Dplot_WG.root","RECREATE");
    TFile *infile = new TFile("studies_sampKenj/inputs/samples/sample_rootfiles/splines_event_by_event_CCcorrected.root");
    TTree *tree = (TTree*)infile->Get("sample_sum");

    // set parameters and variables
    const int SAMPLES = 35;
    float WGpmu, WGcs, WGpeso;
    int sample;
    int nevent = tree->GetEntries();

    // set branches
    tree->SetBranchAddress("Pmu", &pmu);
    tree->SetBranchAddress("CosThetamu", &cs);
    tree->SetBranchAddress("POTWeight", &peso);
    tree->SetBranchAddress("SelectedSample", &sample);
    
    int nsamp[SAMPLES] = {
        // FHC WAGASCI
        151, 152, 153, 154, 155, 157, 158};

    std::string nhist[SAMPLES] = {
        "FHC WAGASCI PM-WMRD #nu_{#mu} CC-0#pi", 
        "FHC WAGASCI PM-BM #nu_{#mu} CC-0#pi",
        "FHC WAGASCI PM #nu_{#mu} CC-1#pi", 
        "FHC WAGASCI UWG-WMRD #nu_{#mu} CC-0#pi", 
        "FHC WAGASCI UWG-BM #nu_{#mu} CC-0#pi",
        "FHC WAGASCI DWG-BM #nu_{#mu} CC-0#pi", 
        "FHC WAGASCI WG #nu_{#mu} CC-1#pi"};

    // min/max entries per histo

    // create histos
    std::vector<TH2D*> h;
    for(int isample = 0; isample < SAMPLES; isample++){
        std::string nam = "h"+to_string(isample);
        h.push_back(new TH2D(nam.c_str(), nhist[isample].c_str(), 200, -1, 1, 300, 0, 30000));
        h[isample]->SetXTitle("cos #theta_{#mu}");
        h[isample]->SetYTitle("P_{#mu}");
    }
    
    // fill histos per sample for ND280
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

    }

    TTree *WGtree = (TTree*)WGfile->Get("sample_sum");

    nevent = WGtree->GetEntries();

    // set branches
    WGtree->SetBranchAddress("Pmu", &WGpmu);
    WGtree->SetBranchAddress("CosThetamu", &WGcs);
    WGtree->SetBranchAddress("POTWeight", &WGpeso);
    WGtree->SetBranchAddress("SelectedSample", &WGsample);
    // fill histos per sample for WAGASCI
    for(int ientry = 0; ientry < nevent; ientry++) {
        WGtree->GetEntry(ientry);

        int isample = 0; 
        for(int n = 0; n < SAMPLES; n++) {
            if ( WGsample == nsamp[n] ) {
                isample = n;
                break;
            }
        }
        std::cout << "Sample: " << WGsample << "\tPmu: " << WGpmu << "\tCosThetamu: " << WGcs << "\tPOTWeight: " << WGpeso << std::endl;
        
        h[isample]->Fill(WGcs, WGpmu, WGpeso);

    }
    // draw and save plots
    //TCanvas *c1 = new TCanvas();
    gStyle->SetOptStat(0);
    outfile->cd();
    for(int isample = 0; isample < SAMPLES; isample++){
        h[isample]->SetOption("LEGO2");
        h[isample]->Write();
    }
    outfile->Close();
}
