void test()
{
    // initialize file and tree
    TFile *infile = new TFile("studies_sampKenj/inputs/samples/sample_rootfiles/wagasci_sample_kenji.root");
    TTree *tree = (TTree*)infile->Get("selectedEvents");

    // set parameters from tree
    float pmu, trupmu, cs, trucs, peso;
    int sample;
    const int BINS = 5;
    int nevent = tree->GetEntries();
    double xmin = tree->GetMinimum("Costhetamu");
    double xmax = tree->GetMaximum("CosThetamu");

    // set branches
    tree->SetBranchAddress("Pmu", &pmu);
    tree->SetBranchAddress("CosThetamu", &cs);
    tree->SetBranchAddress("TruePmu", &trupmu);
    tree->SetBranchAddress("TrueCosThetamu", &trucs);
    tree->SetBranchAddress("POTWeight", &peso);
    tree->SetBranchAddress("SelectedSample", &sample);

    // create histo for binning
    TH1D *h = new TH1D("", "", BINS, xmin, xmax);
    TCanvas *c1 = new TCanvas();
    gStyle->SetOptStat(0);

    std::vector<double> var;
    // loop over events
    for(int ientry = 0; ientry < nevent; ientry++) {
        tree->GetEntry(ientry);
        if(sample == 153) {
            h->Fill(cs);
            var.push_back(cs);
        }
    }

    std::sort (var.begin(), var.end());
    double entriesbin = h->GetEntries()/BINS;
    double edges[BINS+1];
    edges[0] = xmin;
    edges[BINS] = xmax;

    for(int i = 1; i < BINS; i++) {
        edges[i] = var[std::round(entriesbin*i)];
        std::cout << edges[i] << "\n";
    }

    h = (TH1D*) h->Rebin(BINS,"",edges);
    for(std::vector<double>::iterator it = var.begin() ; it != var.end(); ++it) {
        h->Fill(*it);
    }

    h->Scale(peso);
    h->Draw("hist text65");
    std::cout << var.size() << "\n";

    for(int i=1; i<=BINS;i++){
    std::cout <<"Bin content for bin [" << h->GetXaxis()->GetBinLowEdge(i) << "," << h->GetXaxis()->GetBinUpEdge(i) << "] : " << h->GetBinContent(i)<< "\n";
    }

    c1->SaveAs("plots/test.png");
}
