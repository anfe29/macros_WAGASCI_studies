int calcbin(int samp)
{
    std::cout << "Number of events: " << samp << "\tNumber of bins calculated: " << std::round(std::pow(2*samp, 0.4)) << "\tNumber of events per bin: " << samp/(std::round(std::pow(2*samp, 0.4))) << "\n";
    return std::round(std::pow(2*samp, 0.4));
}

void make2Dplots()
{
    // initialize file and tree
    TFile *infile = new TFile("studies_sampKenj/inputs/samples/sample_rootfiles/wagasci_sample_kenji.root");
    TTree *tree = (TTree*)infile->Get("selectedEvents");

    // set parameters and variables
    float pmu, cs, peso;
    int sample;
    int nevent = tree->GetEntries();

    // set branches
    tree->SetBranchAddress("Pmu", &pmu);
    tree->SetBranchAddress("CosThetamu", &cs);
    tree->SetBranchAddress("POTWeight", &peso);
    tree->SetBranchAddress("SelectedSample", &sample);

    // min/max entries per histo
    int xmax = tree->GetMaximum("cs");
    int xmin = tree->GetMinimum("cs");

    int ymax = tree->GetMaximum("pmu");
    int ymin = tree->GetMinimum("pmu");

    // create histos
    TH2D *h1 = new TH2D("h1", "FHC PM-WMRD #nu_{#mu} CC 0#pi", calcbin(tree->GetEntries("SelectedSample == 151")), xmin, xmax, calcbin(tree->GetEntries("SelectedSample == 151")), ymin, ymax);
    h1->SetXTitle("cos #theta_{#mu}");
    h1->SetYTitle("P_{#mu}");

    TH2D *h2 = new TH2D("h2", "FHC PM-BM #nu_{#mu} CC 0#pi", calcbin(tree->GetEntries("SelectedSample == 152")), xmin, xmax, calcbin(tree->GetEntries("SelectedSample == 152")), ymin, ymax);
    h2->SetXTitle("cos #theta_{#mu}");
    h2->SetYTitle("P_{#mu}");
    
    TH2D *h3 = new TH2D("h3", "FHC PM #nu_{#mu} CC 1#pi", calcbin(tree->GetEntries("SelectedSample == 153")), xmin, xmax, calcbin(tree->GetEntries("SelectedSample == 153")), ymin, ymax);
    h3->SetXTitle("cos #theta_{#mu}");
    h3->SetYTitle("P_{#mu}");
    
    TH2D *h4 = new TH2D("h4", "FHC UWG-WMRD #nu_{#mu} CC 0#pi", calcbin(tree->GetEntries("SelectedSample == 154")), xmin, xmax, calcbin(tree->GetEntries("SelectedSample == 154")), ymin, ymax);
    h4->SetXTitle("cos #theta_{#mu}");
    h4->SetYTitle("P_{#mu}");
    
    TH2D *h5 = new TH2D("h5", "FHC UWG-BM #nu_{#mu} CC 0#pi", calcbin(tree->GetEntries("SelectedSample == 155")), xmin, xmax, calcbin(tree->GetEntries("SelectedSample == 155")), ymin, ymax);
    h5->SetXTitle("cos #theta_{#mu}");
    h5->SetYTitle("P_{#mu}");

    TH2D *h6 = new TH2D("h6", "FHC DWG-BM #nu_{#mu} CC 0#pi", calcbin(tree->GetEntries("SelectedSample == 157")), xmin, xmax, calcbin(tree->GetEntries("SelectedSample == 157")), ymin, ymax);
    h6->SetXTitle("cos #theta_{#mu}");
    h6->SetYTitle("P_{#mu}");

    TH2D *h7 = new TH2D("h7", "FHC WG #nu_{#mu} CC 1#pi", calcbin(tree->GetEntries("SelectedSample == 158")), xmin, xmax, calcbin(tree->GetEntries("SelectedSample == 158")), ymin, ymax);
    h7->SetXTitle("cos #theta_{#mu}");
    h7->SetYTitle("P_{#mu}");
    
    // fill histos per sample
    for(int ientry = 0; ientry < nevent; ientry++) {
        tree->GetEntry(ientry);

        if ( sample == 151 ) h1->Fill(cs, pmu);

        if ( sample == 152 ) h2->Fill(cs, pmu);

        if ( sample == 153 ) h3->Fill(cs, pmu);

        if ( sample == 154 ) h4->Fill(cs, pmu);

        if ( sample == 155 ) h5->Fill(cs, pmu);

        if ( sample == 157 ) h6->Fill(cs, pmu);

        if ( sample == 158 ) h7->Fill(cs, pmu);
    }

    // draw and save plots
    TCanvas *c1 = new TCanvas();
    gStyle->SetOptStat(0);

    h1->Scale(peso);
    h1->Draw("colz");
    c1->Print("plots/2Dhist/samp1.png");

    h2->Scale(peso);
    h2->Draw("colz");
    c1->Print("plots/2Dhist/samp2.png");

    h3->Scale(peso);
    h3->Draw("colz");
    c1->Print("plots/2Dhist/samp3.png");

    h4->Scale(peso);
    h4->Draw("colz");
    c1->Print("plots/2Dhist/samp4.png");

    h5->Scale(peso);
    h5->Draw("colz");
    c1->Print("plots/2Dhist/samp5.png");

    h6->Scale(peso);
    h6->Draw("colz");
    c1->Print("plots/2Dhist/samp6.png");

    h7->Scale(peso);
    h7->Draw("colz");
    c1->Print("plots/2Dhist/samp7.png");
}
