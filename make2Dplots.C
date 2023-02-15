void make2Dplots()
{
    // initialize file and tree
    //TFile *infile = new TFile("studies_sampKenj/inputs/samples/sample_rootfiles/wagasci_sample_kenji.root");
    TFile *infile = new TFile("studies_sampKenj/inputs/samples/sample_rootfiles/splines_event_by_event.root");
    TFile *outfile = new TFile("plots/2Dhist/2Dplot.root","RECREATE");
    //TTree *tree = (TTree*)infile->Get("selectedEvents");
    TTree *tree = (TTree*)infile->Get("spline_tree");

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
    TH2D *h1 = new TH2D("h1", "FHC PM-WMRD #nu_{#mu} CC 0#pi", 40, xmin, xmax, 100, ymin, ymax);
    h1->SetXTitle("cos #theta_{#mu}");
    h1->SetYTitle("P_{#mu}");

    TH2D *h2 = new TH2D("h2", "FHC PM-BM #nu_{#mu} CC 0#pi", 40, xmin, xmax, 100, ymin, ymax);
    h2->SetXTitle("cos #theta_{#mu}");
    h2->SetYTitle("P_{#mu}");
    
    TH2D *h3 = new TH2D("h3", "FHC PM #nu_{#mu} CC 1#pi", 40, xmin, xmax, 100, ymin, ymax);
    h3->SetXTitle("cos #theta_{#mu}");
    h3->SetYTitle("P_{#mu}");
    
    TH2D *h4 = new TH2D("h4", "FHC UWG-WMRD #nu_{#mu} CC 0#pi", 40, xmin, xmax, 100, ymin, ymax);
    h4->SetXTitle("cos #theta_{#mu}");
    h4->SetYTitle("P_{#mu}");
    
    TH2D *h5 = new TH2D("h5", "FHC UWG-BM #nu_{#mu} CC 0#pi", 40, xmin, xmax, 100, ymin, ymax);
    h5->SetXTitle("cos #theta_{#mu}");
    h5->SetYTitle("P_{#mu}");

    TH2D *h6 = new TH2D("h6", "FHC DWG-BM #nu_{#mu} CC 0#pi", 40, xmin, xmax, 100, ymin, ymax);
    h6->SetXTitle("cos #theta_{#mu}");
    h6->SetYTitle("P_{#mu}");

    TH2D *h7 = new TH2D("h7", "FHC WG #nu_{#mu} CC 1#pi", 40, xmin, xmax, 100, ymin, ymax);
    h7->SetXTitle("cos #theta_{#mu}");
    h7->SetYTitle("P_{#mu}");
    
    // fill histos per sample
    for(int ientry = 0; ientry < nevent; ientry++) {
        tree->GetEntry(ientry);

        //if(peso > 10) peso = 1;
        
        if ( sample == 151 ) h1->Fill(cs, pmu, peso);

        if ( sample == 152 ) h2->Fill(cs, pmu, peso);

        if ( sample == 153 ) h3->Fill(cs, pmu, peso);

        if ( sample == 154 ) h4->Fill(cs, pmu, peso);

        if ( sample == 155 ) h5->Fill(cs, pmu, peso);

        if ( sample == 157 ) h6->Fill(cs, pmu, peso);

        if ( sample == 158 ) h7->Fill(cs, pmu, peso);
    }

    // draw and save plots
    //TCanvas *c1 = new TCanvas();
    gStyle->SetOptStat(0);
/*
    h1->Draw("colz");
    c1->Print("plots/2Dhist/samp1.png");

    h2->Draw("colz");
    c1->Print("plots/2Dhist/samp2.png");

    h3->Draw("colz");
    c1->Print("plots/2Dhist/samp3.png");

    h4->Draw("colz");
    c1->Print("plots/2Dhist/samp4.png");

    h5->Draw("colz");
    c1->Print("plots/2Dhist/samp5.png");

    h6->Draw("colz");
    c1->Print("plots/2Dhist/samp6.png");

    h7->Draw("colz");
    c1->Print("plots/2Dhist/samp7.png");
*/
    outfile->cd();
    h1->SetOption("LEGO2");
    h1->Write();
    
    h2->SetOption("LEGO2");
    h2->Write();
    
    h3->SetOption("LEGO2");
    h3->Write();
    
    h4->SetOption("LEGO2");
    h4->Write();
    
    h5->SetOption("LEGO2");
    h5->Write();
    
    h6->SetOption("LEGO2");
    h6->Write();
    
    h7->SetOption("LEGO2");
    h7->Write();
    
    outfile->Close();
}
