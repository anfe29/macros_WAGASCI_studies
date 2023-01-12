void makebinnedplots()
{
    // initialize file and tree
    TFile *infile = new TFile("studies_sampKenj/inputs/samples/sample_rootfiles/wagasci_sample_kenji.root");
    TTree *tree = (TTree*)infile->Get("selectedEvents");

    // set parameters from tree
    float pmu, trupmu, cs, trucs, peso;
    int sample;
    int nevent = tree->GetEntries();

    // set branches
    tree->SetBranchAddress("Pmu", &pmu);
    tree->SetBranchAddress("CosThetamu", &cs);
    tree->SetBranchAddress("TruePmu", &trupmu);
    tree->SetBranchAddress("TrueCosThetamu", &trucs);
    tree->SetBranchAddress("POTWeight", &peso);
    tree->SetBranchAddress("SelectedSample", &sample);

    // define binnings for CosThetamu

    // define sample names
    std::vector<std::string> nhist = {"FHC PM-WMRD #nu_{#mu} CC 0#pi", "FHC PM-BM #nu_{#mu} CC 0#pi",
        "FHC PM #nu_{#mu} CC 1#pi", "FHC UWG-WMRD #nu_{#mu} CC 0#pi", "FHC UWG-BM #nu_{#mu} CC 0#pi",
        "FHC DWG-BM #nu_{#mu} CC 0#pi", "FHC WG #nu_{#mu} CC 1#pi"};

    // define SelecetedSample array
    std::vector<int> nsamp = {151, 152, 153, 154, 155, 157, 158};

    // define number of bins array
    std::vector<int> nbins = {3, 3, 3, 3, 3, 3, 3};

    // define binning array
    std::vector<double> bin[7] = {
        {-1, 0, 0.5, 1}, 
        {-1, 0, 0.5, 1}, 
        {-1, 0, 0.5, 1}, 
        {-1, 0, 0.5, 1},
        {-1, 0, 0.5, 1},
        {-1, 0, 0.5, 1},
        {-1, 0, 0.5, 1} };

    // create histo for binning
    TH1D *h = NULL;

    // loop over samples
    for(int isample = 0; isample < nsamp.size(); isample++) {

        h = new TH1D("", "", nbins[isample], &bin[isample][0]);

        // create hist for calculating resolution
        std::vector<TH1D*> hres(nbins[isample]);
        for(int i = 0; i < hres.size(); i++) {
            hres[i] = new TH1D("", "", 100 , h->GetXaxis()->GetBinLowEdge(i+1), h->GetXaxis()->GetBinUpEdge(i+2));
        }

        for(int ientry = 0; ientry < nevent; ientry++) {
            tree->GetEntry(ientry);

            if ( sample == nsamp[isample] ) {
                h->Fill(cs/*, pmu*/);
                if( cs < 0 && cs > -1) std::cout<<cs<<"\t"<<trucs<<"\n";
                for(int j = 0; j < hres.size(); j++) hres[j]->Fill((cs-trucs)/trucs);
            }
        }

        // Rescale bin content with POT
        h->Scale(peso);

        std::cout << "\nFor " << nhist[isample] << " bin contents are:\nTotal events in sample : " << h->GetEntries()*peso << "\n";
        std::cout << "If the idea is to have an equal number of events per bin, we should consider " << (h->GetEntries()*peso)/nbins[isample] << "\n";
        // Show bin contents
        for(int ibin = 1; ibin < h->GetNbinsX() + 1; ibin++) {

            std::cout << "Bin [" << h->GetXaxis()->GetBinLowEdge(ibin) << ", " << h->GetXaxis()->GetBinUpEdge(ibin) << "] : " << h->GetBinContent(ibin) << "\t";
            // standard deviation is calculated with binned entries so underflow and overflows are not considered
            std::cout << "Resolution : " << hres[ibin-1]->GetStdDev()*2 << " \n";
        }

    }
}
