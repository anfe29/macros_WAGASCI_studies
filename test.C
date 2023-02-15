void test()
{
    // initialize file and tree
    TFile *infile = new TFile("studies_sampKenj/inputs/samples/sample_rootfiles/splines_event_by_event.root");
    TTree *tree = (TTree*)infile->Get("spline_tree");

    // set parameters from tree
    float pmu, trupmu, cs, trucs, peso;
    int sample;
    const int BINS = 5;
    int nevent = tree->GetEntries();
    double xmin = tree->GetMinimum("Costhetamu");
    double xmax = tree->GetMaximum("CosThetamu");
    std::vector<double> binarr;

    // set branches
    tree->SetBranchAddress("Pmu", &pmu);
    tree->SetBranchAddress("CosThetamu", &cs);
    tree->SetBranchAddress("TruePmu", &trupmu);
    tree->SetBranchAddress("TrueCosThetamu", &trucs);
    tree->SetBranchAddress("POTWeight", &peso);
    tree->SetBranchAddress("SelectedSample", &sample);

    // create histo for binning
    TH1D *h = new TH1D("", "", 50, xmin, xmax);

    // loop over events
    for(int ientry = 0; ientry < nevent; ientry++) {
        tree->GetEntry(ientry);
        if(peso > 10) peso = 1;
        if(sample == 153) {
            h->Fill(cs,peso);
        }
    }

    double entriesbin = h->GetEntries()/BINS;

    while(h->GetNbins() < BINS) {
        for(ibin = 1; ibin < h->GetNbins()+1; ibin++) {
            if(h->GetBinContent(ibin) == 0)
            if()
            if()

        }
        double edges[binarr.size()];
        for(std::vector<double>::iterator it = binarr.begin() ; it != binarr.end(); ++it) {
            h->Fill(*it);
        }
        //h->Reset();
        h = (TH1D*) h->Rebin(binarr.size(),"",edges);
    }

    for(int i=1; i<=BINS;i++){
    std::cout <<"Bin content for bin [" << h->GetXaxis()->GetBinLowEdge(i) << "," << h->GetXaxis()->GetBinUpEdge(i) << "] : " << h->GetBinContent(i)<< "\n";
    }

    TCanvas *c1 = new TCanvas();
    gStyle->SetOptStat(0);
    h->Draw("HISTTEXT65");
    c1->SaveAs("plots/test.png");
}
