void make2Dplots()
{
    // initialize file and tree
    //TFile *infile = new TFile("studies_sampKenj/inputs/samples/sample_rootfiles/wagasci_sample_kenji.root");
    //TFile *infile = new TFile("studies_sampKenj/inputs/samples/sample_rootfiles/splines_event_by_event.root");
    TFile *outfile = new TFile("plots/2Dhist/2Dplot.root","RECREATE");
    //TTree *tree = (TTree*)infile->Get("selectedEvents");
    TChain *tree = new TChain("sample_sum");
    tree->Add("studies_sampKenj/inputs/samples/sample_rootfiles/run2aMCsplines_ForSFGD.root");
    tree->Add("studies_sampKenj/inputs/samples/sample_rootfiles/run2wMCsplines_ForSFGD.root");
    tree->Add("studies_sampKenj/inputs/samples/sample_rootfiles/run3MCsplines_ForSFGD.root");
    tree->Add("studies_sampKenj/inputs/samples/sample_rootfiles/run4aMCsplines_ForSFGD.root");
    tree->Add("studies_sampKenj/inputs/samples/sample_rootfiles/run4wMCsplines_ForSFGD.root");
    tree->Add("studies_sampKenj/inputs/samples/sample_rootfiles/run5MCsplines_ForSFGD.root");
    tree->Add("studies_sampKenj/inputs/samples/sample_rootfiles/run6MCsplines_ForSFGD.root");
    tree->Add("studies_sampKenj/inputs/samples/sample_rootfiles/run7MCsplines_ForSFGD.root");
    tree->Add("studies_sampKenj/inputs/samples/sample_rootfiles/run8aMCsplines_ForSFGD.root");
    tree->Add("studies_sampKenj/inputs/samples/sample_rootfiles/run8wMCsplines_ForSFGD.root");
    tree->Add("studies_sampKenj/inputs/samples/sample_rootfiles/run9MCsplines_ForSFGD.root");
    tree->Add("studies_sampKenj/inputs/samples/sample_rootfiles/SFGD_BANFFFormat_anu_500k_NaturalUnits_goodq3units_flatsplines_fixRS_wCoulombCorrection.root");
    tree->Add("studies_sampKenj/inputs/samples/sample_rootfiles/SFGD_BANFFFormat_nu_2M_NaturalUnits_goodq3units_flatsplines_fixRS_wCoulombCorrection.root");
    //tree->Add("studies_sampKenj/inputs/samples/sample_rootfiles/splines_event_by_event_CCcorrected.root");

    // set parameters and variables
    const int SAMPLES = 35;
    double pmu, cs, peso;
    float WGpmu, WGcs, WGpeso;
    int WGsample;
    int sample;
    int nevent = tree->GetEntries();

    // set branches
    tree->SetBranchAddress("Pmu", &pmu);
    tree->SetBranchAddress("CosThetamu", &cs);
    tree->SetBranchAddress("POTWeight", &peso);
    tree->SetBranchAddress("SelectedSample", &sample);
    
    int nsamp[SAMPLES] = {
        // FHC FGD
        7, 8, 10, 12, 13, 31, 32, 34, 36, 37, 
        // RHC FGD
        59, 60, 61, 65, 66, 67, 71, 72, 73, 77, 78, 79, 
        // FHC SFGD
        101, 102, 103,
        // RHC SFGD
        111, 112, 113,
        // FHC WAGASCI
        151, 152, 153, 154, 155, 157, 158};

    std::string nhist[SAMPLES] = {
        "FHC FGD1 #nu_{#mu} CC 0#pi 0p 0#gamma",
        "FHC FGD1 #nu_{#mu} CC 0#pi Np 0#gamma",
        "FHC FGD1 #nu_{#mu} CC 1#pi 0#gamma",
        "FHC FGD1 #nu_{#mu} CC Other 0#gamma",
        "FHC FGD1 #nu_{#mu} CC #gamma",
        "FHC FGD2 #nu_{#mu} CC 0#pi 0p 0#gamma",
        "FHC FGD2 #nu_{#mu} CC 0#pi Np 0#gamma",
        "FHC FGD2 #nu_{#mu} CC 1#pi 0#gamma",
        "FHC FGD2 #nu_{#mu} CC Other 0#gamma",
        "FHC FGD2 #nu_{#mu} CC #gamma",
        "RHC FGD1 Anti #nu_{#mu} CC 0#pi",
        "RHC FGD1 Anti #nu_{#mu} CC 1#pi",
        "RHC FGD1 Anti #nu_{#mu} CC Other",
        "RHC FGD2 Anti #nu_{#mu} CC 0#pi",
        "RHC FGD2 Anti #nu_{#mu} CC 1#pi",
        "RHC FGD2 Anti #nu_{#mu} CC Other",
        "RHC FGD1 #nu_{#mu} (background) CC 0#pi in AntiNu_Mode",
        "RHC FGD1 #nu_{#mu} (background) CC 1#pi in AntiNu_Mode",
        "RHC FGD1 #nu_{#mu} (background) CC Other in AntiNu_Mode",
        "RHC FGD2 #nu_{#mu} (background) CC 0#pi in AntiNu_Mode",
        "RHC FGD2 #nu_{#mu} (background) CC 1#pi  in AntiNu_Mode",
        "RHC FGD2 #nu_{#mu} (background) CC Other  in AntiNu_Mode",
        "FHC SFGD #nu_{#mu} CC 0#pi 0p",
        "FHC SFGD #nu_{#mu} CC 0#pi Np",
        "FHC SFGD #nu_{#mu} CC 1#pi 0p",
        "RHC SFGD #bar{#nu}_{#mu} CC 0#pi 0n",
        "RHC SFGD #bar{#nu}_{#mu} CC 0#pi Nn",
        "RHC SFGD #bar{#nu}_{#mu} CC 1#pi 0n",
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

    TFile *WGfile = new TFile("studies_sampKenj/inputs/samples/sample_rootfiles/splines_event_by_event_CCcorrected.root");
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
