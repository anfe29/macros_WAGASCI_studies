// macro for showing binning, bin content and bin resolution for binning analysis and refinement
void binningAnal()
{
    // initialize file and tree
    TFile *infile = new TFile("studies_sampKenj/inputs/samples/sample_rootfiles/splines_event_by_event.root");
    //TFile *infile = new TFile("studies_sampKenj/inputs/samples/sample_rootfiles/wagasci_sample_kenji.root");
    TTree *tree = (TTree*)infile->Get("spline_tree");
    //TTree *tree = (TTree*)infile->Get("selectedEvents");

    // set parameters from tree
    const int SAMPLES = 7;
    //const int MAXCOSBIN = 5;
    //const int MAXPMUBIN = 12;
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
        {12, 12, 12, 12, 12}, {12, 12, 12, 12, 12}, {12, 12, 12, 12, 12}, {12, 12, 12, 12, 12}, {12, 12, 12, 12, 12}, {12, 12, 12, 12, 12}, {12, 12, 12, 12, 12}, 
    };

    // define binning arrays
    std::vector<std::vector<double>> bincos = {
        {0., 0.4, 0.5, 0.6 , 0.7 , 1}, 
        {0., 0.9, 0.95, 0.98, 0.99, 1}, 
        {0., 0.6 , 0.85 , 0.95, 0.99, 1}, 
        {0., 0.5 , 0.6 , 0.7, 0.8, 1},
        {0., 0.92, 0.96, 0.97, 0.99, 1},
        {0., 0.65, 0.85, 0.9 , 0.95, 1},
        {0., 0.6 , 0.85, 0.93, 0.98, 1} };

    std::vector<std::vector<std::vector<double>>> binpmu = {
        {   //FHC WAGASCI PM-WMRD #nu_{#mu} CC 0#pi 
            {0, 400, 450, 500, 550, 600, 650, 700, 750, 800, 850, 900, 15000},
            {0, 400, 450, 500, 550, 600, 650, 700, 750, 800, 850, 900, 15000},
            {0, 400, 450, 500, 550, 600, 650, 700, 750, 800, 850, 900, 15000},
            {0, 400, 450, 500, 550, 600, 650, 700, 750, 800, 850, 900, 15000},
            {0, 400, 450, 500, 550, 600, 650, 700, 750, 800, 850, 900, 15000}
        }, 
        {   //FHC WAGASCI PM-BM #nu_{#mu} CC 0#pi
            {0, 400, 450, 500, 550, 600, 650, 700, 750, 800, 850, 900, 15000},
            {0, 400, 450, 500, 550, 600, 650, 700, 750, 800, 850, 900, 15000},
            {0, 400, 450, 500, 550, 600, 650, 700, 750, 800, 850, 900, 15000},
            {0, 400, 450, 500, 550, 600, 650, 700, 750, 800, 850, 900, 15000},
            {0, 400, 450, 500, 550, 600, 650, 700, 750, 800, 850, 900, 15000}
        },
        {   //FHC WAGASCI PM #nu_{#mu} CC 1#pi 
            {0, 400, 450, 500, 550, 600, 650, 700, 750, 800, 850, 900, 15000},
            {0, 400, 450, 500, 550, 600, 650, 700, 750, 800, 850, 900, 15000},
            {0, 400, 450, 500, 550, 600, 650, 700, 750, 800, 850, 900, 15000},
            {0, 400, 450, 500, 550, 600, 650, 700, 750, 800, 850, 900, 15000},
            {0, 400, 450, 500, 550, 600, 650, 700, 750, 800, 850, 900, 15000}
        },
        {   //FHC WAGASCI UWG-WMRD #nu_{#mu} CC 0#pi 
            {0, 400, 450, 500, 550, 600, 650, 700, 750, 800, 850, 900, 15000},
            {0, 400, 450, 500, 550, 600, 650, 700, 750, 800, 850, 900, 15000},
            {0, 400, 450, 500, 550, 600, 650, 700, 750, 800, 850, 900, 15000},
            {0, 400, 450, 500, 550, 600, 650, 700, 750, 800, 850, 900, 15000},
            {0, 400, 450, 500, 550, 600, 650, 700, 750, 800, 850, 900, 15000}
        },
        {   //FHC WAGASCI UWG-BM #nu_{#mu} CC 0#pi
            {0, 400, 450, 500, 550, 600, 650, 700, 750, 800, 850, 900, 15000},
            {0, 400, 450, 500, 550, 600, 650, 700, 750, 800, 850, 900, 15000},
            {0, 400, 450, 500, 550, 600, 650, 700, 750, 800, 850, 900, 15000},
            {0, 400, 450, 500, 550, 600, 650, 700, 750, 800, 850, 900, 15000},
            {0, 400, 450, 500, 550, 600, 650, 700, 750, 800, 850, 900, 15000}
        },
        {   //FHC WAGASCI DWG-BM #nu_{#mu} CC 0#pi 
            {0, 400, 450, 500, 550, 600, 650, 700, 750, 800, 850, 900, 15000},
            {0, 400, 450, 500, 550, 600, 650, 700, 750, 800, 850, 900, 15000},
            {0, 400, 450, 500, 550, 600, 650, 700, 750, 800, 850, 900, 15000},
            {0, 400, 450, 500, 550, 600, 650, 700, 750, 800, 850, 900, 15000},
            {0, 400, 450, 500, 550, 600, 650, 700, 750, 800, 850, 900, 15000}
        },
        {   //FHC WAGASCI WG #nu_{#mu} CC 1#pi
            {0, 400, 450, 500, 550, 600, 650, 700, 750, 800, 850, 900, 15000},
            {0, 400, 450, 500, 550, 600, 650, 700, 750, 800, 850, 900, 15000},
            {0, 400, 450, 500, 550, 600, 650, 700, 750, 800, 850, 900, 15000},
            {0, 400, 450, 500, 550, 600, 650, 700, 750, 800, 850, 900, 15000},
            {0, 400, 450, 500, 550, 600, 650, 700, 750, 800, 850, 900, 15000}
        },
    };

    // create histos for binning
    std::vector<TH1D*> hcs;
    std::vector<TH1D*> hcs_res;
    std::vector<std::vector<TH1D*>> hpmu(SAMPLES);
    std::vector<std::vector<TH1D*>> hpmu_res;
     
    // create histo instances
    for(int isample = 0; isample < SAMPLES; isample++) {

        // initialize histogram for costhetamu
        hcs.push_back(new TH1D("", "", nbinscos[isample], &bincos[isample][0]));

        //hpmu_res.resize(nbinscos[isample]);
        // create hist for resolution and pmu per bin, then initialize them
       for(int i = 0; i < nbinscos[isample]; i++) {
            hpmu[isample].push_back(new TH1D("", "", nbinspmu[isample][i], &binpmu[isample][i][0]));
            hcs_res.push_back(new TH1D("", "", 100 , -1, 1));
            //for(int j = 0; j < nbinspmu[isample][i]; j++) {
                //hpmu_res[i].push_back(new TH1D("", "", 100 , 0, 15000));
            //}
        }
    }

        // loop over events
    for(int ientry = 0; ientry < nevent; ientry++) {
        tree->GetEntry(ientry);

        std::cout << ientry << "\n";
        int isample = 0; 
        for(int n = 0; n < SAMPLES; n++) {
            if ( sample == nsamp[n] ) {
                isample = n;
                break;
            }
        }

        std::cout << isample << "\n";
        hcs[isample]->Fill(cs,peso);
        //hcs[isample]->Fill(cs);
        // fill resolution hist and pmu hist using bin edges
        for(int i = 0; i < nbinscos[isample]; i++) {
            //std::cout << i << "\n";
            if(cs >= hcs[isample]->GetXaxis()->GetBinLowEdge(i+1) && cs < hcs[isample]->GetXaxis()->GetBinUpEdge(i+1)) {
                //std::cout << "Filling bin : [" << hcs[isample]->GetXaxis()->GetBinLowEdge(i+1) << ", " << hcs[isample]->GetXaxis()->GetBinUpEdge(i+1) << "] : " << pmu << "\n";
                hcs_res[i]->Fill((cs-trucs)/trucs,peso);
                //hpmu[i]->Fill(pmu,peso);
                hpmu[isample][i]->Fill(pmu,peso);
                //for(int j = 0; j < nbinspmu[isample][i]; j++) {
                    //std::cout << j << "\n";
                    //if(pmu >= hpmu[isample][i]->GetXaxis()->GetBinLowEdge(j+1) && pmu < hpmu[isample][i]->GetXaxis()->GetBinUpEdge(j+1)) {
                        //std::cout << "Filling bin : [" << hpmu[isample][i]->GetXaxis()->GetBinLowEdge(j+1) << ", " << hpmu[isample][i]->GetXaxis()->GetBinUpEdge(j+1) << "] : " << pmu << "\n";
                        //hpmu_res[i][j]->Fill((pmu-trupmu)/trupmu,peso);
                    //}
                //}
            }
        }
    }

    for(int isample = 0; isample < SAMPLES; isample++) {

        // when applying weights to histos use integral instead of gebincontents to get the right number of entries
        std::cout << "\n\nFor " << nhist[isample] << " bin contents are:\nTotal entries in sample : " << hcs[isample]->Integral() << "\n";

        // Show bin contents
        for(int ibin = 1; ibin < hcs[isample]->GetNbinsX() + 1; ibin++) {

            std::cout << "\nCosThetamu: Bin [" << hcs[isample]->GetXaxis()->GetBinLowEdge(ibin) << ", " << hcs[isample]->GetXaxis()->GetBinUpEdge(ibin);
            std::cout << "] : " << hcs[isample]->GetBinContent(ibin) << "\t";
            //std::cout << "] : " << hcs[isample]->Integral(ibin,ibin) << "\t";
            // standard deviation is calculated with binned entries so underflow and overflows are not considered
            std::cout << "Resolution : " << hcs_res[ibin-1]->GetStdDev()*2 << " \t";
            std::cout << "Width : " << hcs[isample]->GetBinWidth(ibin) << "\t";
            std::cout << "Error : " << hcs[isample]->GetBinError(ibin) << "\n";

            // show contents per bin and per sample for pmu
            for(int jbin = 1; jbin < hpmu[isample][ibin-1]->GetNbinsX() + 1; jbin++) {
                std::cout << "\tPmu: Bin [" << hpmu[isample][ibin-1]->GetXaxis()->GetBinLowEdge(jbin) << ", " << hpmu[isample][ibin-1]->GetXaxis()->GetBinUpEdge(jbin);
                std::cout << "] : " << hpmu[isample][ibin-1]->GetBinContent(jbin) << "\t";
                std::cout << "Width : " << hpmu[isample][ibin-1]->GetBinWidth(jbin) << "\t";
                std::cout << "Error : " << hpmu[isample][ibin-1]->GetBinError(jbin) << "\n";
                //std::cout << "] : " << hpmu[ibin-1]->Integral() << "\t";
                //std::cout << "Resolution : " << hpmu_res[ibin-1][jbin-1]->GetStdDev()*2 << " \n";
            }
        }
    }
}
