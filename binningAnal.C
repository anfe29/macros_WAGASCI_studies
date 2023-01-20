// macro for showing binning, bin content and bin resolution for binning analysis and refinement
void binningAnal()
{
    // initialize file and tree
    TFile *infile = new TFile("studies_sampKenj/inputs/samples/sample_rootfiles/wagasci_sample_kenji.root");
    TTree *tree = (TTree*)infile->Get("selectedEvents");

    // set parameters from tree
    const int SAMPLES = 7;
    const int MAXCOSBIN = 5;
    const int MAXPMUBIN = 12;
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
    std::string nhist[SAMPLES] = {
        "FHC WAGASCI PM-WMRD #nu_{#mu} CC 0#pi", 
        "FHC WAGASCI PM-BM #nu_{#mu} CC 0#pi",
        "FHC WAGASCI PM #nu_{#mu} CC 1#pi", 
        "FHC WAGASCI UWG-WMRD #nu_{#mu} CC 0#pi", 
        "FHC WAGASCI UWG-BM #nu_{#mu} CC 0#pi",
        "FHC WAGASCI DWG-BM #nu_{#mu} CC 0#pi", 
        "FHC WAGASCI WG #nu_{#mu} CC 1#pi"};

    // define SelectedSample array
    int nsamp[SAMPLES] = {151, 152, 153, 154, 155, 157, 158};

    // define number of bins array 
    int nbinscos[SAMPLES] = {5, 5, 5, 5, 5, 5, 5};

    std::vector<std::vector<int>> nbinspmu = {
        {5, 7, 6, 6, 2}, {7, 9, 9, 7, 6}, {3, 5, 3, 2, 2}, {3, 4, 7, 4, 3}, {4, 5, 3, 5, 2}, {9, 12, 5, 9, 11}, {5, 7, 6, 6, 5}, 
    };

    // define binning arrays
    std::vector<std::vector<double>> bincos = {
        {0.25, 0.44, 0.55, 0.65 , 0.8 , 1}, 
        {0.45, 0.83, 0.93, 0.96, 0.98, 1}, 
        {0.  , 0.5 , 0.8 , 0.95, 0.98, 1}, 
        {0.25, 0.5 , 0.6 , 0.75, 0.85, 1},
        {0.25, 0.90, 0.95, 0.97, 0.99, 1},
        {0.25, 0.65, 0.85, 0.9 , 0.95, 1},
        {0.25, 0.6 , 0.85, 0.93, 0.98, 1} };

    std::vector<std::vector<std::vector<double>>> binpmu = {
        {
            {0, 400, 450, 500, 600, 15000},
            {0, 350, 400, 450, 500, 550, 600, 15000},
            {0, 350, 400, 450, 500, 600, 15000},
            {0, 400, 450, 500, 550, 600, 15000},
            {0, 700, 15000}
        }, 
        {
            {0, 500, 550, 600, 650, 700, 800, 15000},
            {0, 450, 500, 550, 600, 650, 700, 750, 900, 15000},
            {0, 500, 550, 600, 650, 700, 800, 900, 1100, 2000},
            {0, 500, 600, 700, 800, 900, 1100, 15000},
            {0, 700, 900, 1100, 1500, 2000, 15000}
        },
        {
            {0, 450, 550, 15000},
            {0, 400, 500, 550, 600, 15000},
            {0, 600, 900, 15000},
            {0, 800, 15000},
            {0, 800, 15000}
        },
        {
            {0, 500, 600, 15000},
            {0, 400, 500, 600, 15000},
            {0, 450, 500, 550, 600, 700, 800, 15000},
            {0, 500, 600, 800, 15000},
            {0, 700, 15000}
        },
        {
            {0, 600, 700, 800, 15000},
            {0, 600, 700, 800, 900, 15000},
            {0, 700, 900, 15000},
            {0, 700, 900, 1000, 1500, 15000},
            {0, 1500, 15000}
        },
        {
            {200, 350, 400, 425, 450, 475, 500, 550, 600, 15000},
            {200, 325, 350, 375, 400, 450, 500, 525, 550, 575, 600, 700, 15000},
            {200, 400, 500, 600, 700, 15000},
            {200, 400, 450, 500, 550, 600, 650, 700, 1000, 15000},
            {300, 400, 450, 500, 550, 600, 700, 900, 1000, 1200, 1500, 2000}
        },
        {
            {0, 300, 600, 700, 2000, 15000},
            {200, 350, 500, 600, 700, 900, 2000, 15000},
            {200, 500, 600, 700, 900, 2000, 15000},
            {0, 500, 700, 1500, 2000, 3000, 15000},
            {0, 700, 1000, 2000, 3000, 15000}
        },
    };

    // create histo for binning
    TH1D *hcs = NULL;

    // loop over events per samples in tree
    for(int isample = 0; isample < SAMPLES; isample++) {

        // initialize histogram for costhetamu
        hcs = new TH1D("", "", nbinscos[isample], &bincos[isample][0]);

        // create hist for resolution and pmu per bin, then initialize them
        std::vector<TH1D*> hcs_res;
        std::vector<std::vector<TH1D*>> hpmu_res;
        std::vector<TH1D*> hpmu;
        for(int i = 0; i < nbinscos[isample]; i++) {
            hcs_res.push_back(new TH1D("", "", 100 , -1, 1));
            hpmu_res[isample].push_back(new TH1D("", "", 100 , 0, 15000));
            hpmu.push_back(new TH1D("", "", nbinspmu[isample][i], &binpmu[isample][i][0]));
        }

        // loop over events
        for(int ientry = 0; ientry < nevent; ientry++) {
            tree->GetEntry(ientry);

            if ( sample == nsamp[isample] ) {
                hcs->Fill(cs/*, pmu*/);

                // fill resolution hist and pmu hist using bin edges
                for(int i = 0; i < nbinscos[isample]; i++) {
                    if(cs > hcs->GetXaxis()->GetBinLowEdge(i+1) && cs < hcs->GetXaxis()->GetBinUpEdge(i+1)) {
                        hcs_res[i]->Fill((cs-trucs)/trucs);
                        hpmu[i]->Fill(pmu);
                        for(int j = 0; j < nbinspmu[isample][nbinscos[isample]]; j++) {
                            if(pmu > hpmu[i]->GetXaxis()->GetBinLowEdge(j+1) && pmu < hpmu[i]->GetXaxis()->GetBinUpEdge(j+1)) {
                                hpmu_res[i][j]->Fill((pmu-trupmu)/trupmu);
                            }
                        }
                    }
                }
            }
        }

        // Rescale bin content with POT
        hcs->Scale(peso);

        std::cout << "\nFor " << nhist[isample] << " bin contents are:\nTotal events in sample : " << hcs->GetEntries()*peso << "\n";
        //std::cout << "Number of events per bin: " << (hcs->GetEntries()*peso)/nbinscos[isample] << "\n";

        // Show bin contents
        for(int ibin = 1; ibin < hcs->GetNbinsX() + 1; ibin++) {

            std::cout << "CosThetamu: Bin [" << hcs->GetXaxis()->GetBinLowEdge(ibin) << ", " << hcs->GetXaxis()->GetBinUpEdge(ibin);
            std::cout << "] : " << hcs->GetBinContent(ibin) << "\t";
            // standard deviation is calculated with binned entries so underflow and overflows are not considered
            std::cout << "Resolution : " << hcs_res[ibin-1]->GetStdDev()*2 << " \n";

            hpmu[ibin-1]->Scale(peso);
            // show contents per bin and per sample for pmu
            for(int jbin = 1; jbin < hpmu[ibin-1]->GetNbinsX() + 1; jbin++) {
                std::cout << "\t\tPmu: Bin [" << hpmu[ibin-1]->GetXaxis()->GetBinLowEdge(jbin) << ", " << hpmu[ibin-1]->GetXaxis()->GetBinUpEdge(jbin);
                std::cout << "] : " << hpmu[ibin-1]->GetBinContent(jbin) << "\t";
                std::cout << "Resolution : " << hpmu_res[ibin-1][jbin-1]->GetStdDev()*2 << " \n";
            }
        }
    }
}
