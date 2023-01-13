// macro for showing binning, bin content and bin resolution for binning analysis and refinement
void binningAnal()
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

    // define sample names
    std::vector<std::string> nhist = {
        "FHC WAGASCI PM-WMRD #nu_{#mu} CC 0#pi", 
        "FHC WAGASCI PM-BM #nu_{#mu} CC 0#pi",
        "FHC WAGASCI PM #nu_{#mu} CC 1#pi", 
        "FHC WAGASCI UWG-WMRD #nu_{#mu} CC 0#pi", 
        "FHC WAGASCI UWG-BM #nu_{#mu} CC 0#pi",
        "FHC WAGASCI DWG-BM #nu_{#mu} CC 0#pi", 
        "FHC WAGASCI WG #nu_{#mu} CC 1#pi"};

    // define SelecetedSample array
    std::vector<int> nsamp = {151, 152, 153, 154, 155, 157, 158};

    // define number of bins array for costhetamu
    std::vector<int> nbins = {3, 3, 3, 3, 3, 3, 3};

    // define binning arrays
    double binpmu[7] = {0, 500, 700, 900, 1100, 1500, 30000};
    std::vector<double> bincos[7] = {
        {0.25, 0.49, 0.63, 1}, 
        {0.45, 0.92, 0.97, 1}, 
        {0.  , 0.63, 0.94, 1}, 
        {0.25, 0.6 , 0.75, 1},
        {0.25, 0.94, 0.98, 1},
        {0.25, 0.73, 0.89, 1},
        {0.25, 0.79, 0.93, 1} };

    // create histo for binning
    TH1D *hcs = NULL;

    // loop over events per samples in tree
    for(int isample = 0; isample < nsamp.size(); isample++) {

        // initialize histogram for costhetamu
        hcs = new TH1D("", "", nbins[isample], &bincos[isample][0]);

        // create hist for resolution and pmu per bin, then initialize them
        std::vector<TH1D*> hres(nbins[isample]);
        std::vector<TH1D*> hpmu(nbins[isample]);
        for(int i = 0; i < nbins[isample]; i++) {
            hres[i] = new TH1D("", "", 100 , -1, 1);
            hpmu[i] = new TH1D("", "", 6, binpmu);
        }

        // loop over events
        for(int ientry = 0; ientry < nevent; ientry++) {
            tree->GetEntry(ientry);

            if ( sample == nsamp[isample] ) {
                hcs->Fill(cs/*, pmu*/);

                // fill resolution hist and pmu hist using bin edges
                for(int i = 0; i < nbins[isample]; i++) {
                    if(cs > hcs->GetXaxis()->GetBinLowEdge(i+1) && cs < hcs->GetXaxis()->GetBinUpEdge(i+1)) {
                        hres[i]->Fill((cs-trucs)/trucs);
                        hpmu[i]->Fill(pmu);
                    }
                }
            }
        }

        // Rescale bin content with POT
        hcs->Scale(peso);

        std::cout << "\nFor " << nhist[isample] << " bin contents are:\nTotal events in sample : " << hcs->GetEntries()*peso << "\n";
        //std::cout << "Number of events per bin: " << (hcs->GetEntries()*peso)/nbins[isample] << "\n";

        // Show bin contents
        for(int ibin = 1; ibin < hcs->GetNbinsX() + 1; ibin++) {

            std::cout << "CosThetamu: Bin [" << hcs->GetXaxis()->GetBinLowEdge(ibin) << ", " << hcs->GetXaxis()->GetBinUpEdge(ibin);
            std::cout << "] : " << hcs->GetBinContent(ibin) << "\t";
            // standard deviation is calculated with binned entries so underflow and overflows are not considered
            std::cout << "Resolution : " << hres[ibin-1]->GetStdDev()*2 << " \n";

            hpmu[ibin-1]->Scale(peso);
            // show contents per bin and per sample for pmu
            for(int jbin = 1; jbin < hpmu[ibin-1]->GetNbinsX() + 1; jbin++) {
                std::cout << "\t\tPmu: Bin [" << hpmu[ibin-1]->GetXaxis()->GetBinLowEdge(jbin) << ", " << hpmu[ibin-1]->GetXaxis()->GetBinUpEdge(jbin);
                std::cout << "] : " << hpmu[ibin-1]->GetBinContent(jbin) << "\n";
            }
        }
    }
}
