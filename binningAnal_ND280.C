// macro for showing binning, bin content and bin resolution for binning analysis and refinement
void binningAnal_ND280()
{
    // initialize file and tree
    //TFile *infile = new TFile("studies_sampKenj/inputs/samples/sample_rootfiles/splines_event_by_event_CCcorrected.root");
    //TFile *infile = new TFile("studies_sampKenj/inputs/samples/sample_rootfiles/wagasci_sample_kenji.root");
    //TTree *tree = (TTree*)infile->Get("sample_sum");
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

    // set parameters from tree
    const int SAMPLES = 28;
    double pmu, trupmu, cs, trucs, peso;
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
        "RHC SFGD #bar{#nu}_{#mu} CC 1#pi 0n"};

    // define SelectedSample array
    int nsamp[SAMPLES] = {
        // FHC FGD
        7, 8, 10, 12, 13, 31, 32, 34, 36, 37, 
        // RHC FGD
        59, 60, 61, 65, 66, 67, 71, 72, 73, 77, 78, 79, 
        // FHC SFGD
        101, 102, 103,
        // RHC SFGD
        111, 112, 113
    };

    // define binning arrays
    std::vector<std::vector<double>> bincos = {
        //FHC FGD1 #nu_{#mu} CC 0#pi 0p 0#gamma
        {-1, 0.5, 0.6, 0.68, 0.72, 0.76, 0.82, 0.84, 0.86, 0.88, 0.9, 0.91, 0.92, 0.93, 0.94, 0.95, 0.955, 0.96, 0.965, 0.97, 0.975, 0.98, 0.985, 0.99, 0.995, 1},
        //FHC FGD1 #nu_{#mu} CC 0#pi Np 0#gamma
        {-1, 0.55, 0.65, 0.75, 0.8, 0.85, 0.88, 0.9, 0.92, 0.93, 0.94, 0.95, 0.96, 0.97, 0.98, 0.988, 1},
        //FHC FGD1 #nu_{#mu} CC 1#pi 0#gamma
        {-1, 0.6, 0.68, 0.74, 0.79, 0.85, 0.9, 0.91, 0.92, 0.93, 0.94, 0.95, 0.96, 0.97, 0.98, 0.99, 1},
        //FHC FGD1 #nu_{#mu} CC Other 0#gamma
        {-1, 0.6, 0.7, 0.8, 0.85, 0.88, 0.9, 0.92, 0.94, 0.96, 0.98, 1},
        //FHC FGD1 #nu_{#mu} CC #gamma
        {-1, 0.6, 0.7, 0.76, 0.8, 0.84, 0.86, 0.88, 0.89, 0.9, 0.91, 0.92, 0.93, 0.94, 0.95, 0.96, 0.97, 0.98, 0.99, 0.995, 1},
        //FHC FGD2 #nu_{#mu} CC 0#pi 0p 0#gamma
        {-1, 0.5, 0.6, 0.68, 0.72, 0.76, 0.82, 0.84, 0.86, 0.88, 0.9, 0.91, 0.92, 0.93, 0.94, 0.95, 0.955, 0.96, 0.965, 0.97, 0.975, 0.98, 0.985, 0.99, 0.995, 1},
        //FHC FGD2 #nu_{#mu} CC 0#pi Np 0#gamma
        {-1, 0.55, 0.65, 0.75, 0.8, 0.85, 0.88, 0.9, 0.92, 0.93, 0.94, 0.95, 0.96, 0.97, 0.98, 0.988, 1},
        //FHC FGD2 #nu_{#mu} CC 1#pi 0#gamma
        {-1, 0.6, 0.68, 0.74, 0.79, 0.85, 0.9, 0.91, 0.92, 0.93, 0.94, 0.95, 0.96, 0.97, 0.98, 0.99, 1},
        //FHC FGD2 #nu_{#mu} CC Other 0#gamma
        {-1, 0.6, 0.7, 0.8, 0.85, 0.88, 0.9, 0.92, 0.94, 0.96, 0.98, 1},
        //FHC FGD2 #nu_{#mu} CC #gamma
        {-1, 0.6, 0.7, 0.76, 0.8, 0.84, 0.86, 0.88, 0.89, 0.9, 0.91, 0.92, 0.93, 0.94, 0.95, 0.96, 0.97, 0.98, 0.99, 0.995, 1},
        //RHC FGD1 Anti #nu_{#mu} CC 0#pi
        {-1, 0.6, 0.7, 0.8, 0.85, 0.9, 0.92, 0.93, 0.94, 0.95, 0.96, 0.965, 0.97, 0.975, 0.98, 0.985, 0.99, 0.995, 1},
        //RHC FGD1 Anti #nu_{#mu} CC 1#pi
        {-1, 0.7, 0.8, 0.9, 0.94, 0.96, 0.98, 0.99, 1},
        //RHC FGD1 Anti #nu_{#mu} CC Other
        {-1, 0.7, 0.8, 0.85, 0.9, 0.93, 0.95, 0.97, 0.98, 0.99, 1},
        //RHC FGD2 Anti #nu_{#mu} CC 0#pi
        {-1, 0.6, 0.7, 0.8, 0.85, 0.9, 0.92, 0.93, 0.94, 0.95, 0.96, 0.965, 0.97, 0.975, 0.98, 0.985, 0.99, 0.995, 1},
        //RHC FGD2 Anti #nu_{#mu} CC 1#pi
        {-1, 0.7, 0.8, 0.9, 0.94, 0.96, 0.98, 0.99, 1},
        //RHC FGD2 Anti #nu_{#mu} CC Other
        {-1, 0.7, 0.8, 0.85, 0.9, 0.93, 0.95, 0.97, 0.98, 0.99, 1},
        //RHC FGD1 #nu_{#mu} (background) CC 0#pi in AntiNu_Mode
        {-1, 0.7, 0.8, 0.85, 0.88, 0.9, 0.92, 0.94, 0.96, 0.97, 0.98, 0.99, 1},
        //RHC FGD1 #nu_{#mu} (background) CC 1#pi in AntiNu_Mode
        {-1, 0.7, 0.8, 0.86, 0.9, 0.94, 0.96, 0.97, 0.98, 0.99, 1},
        //RHC FGD1 #nu_{#mu} (background) CC Other in AntiNu_Mode
        {-1, 0.7, 0.8, 0.86, 0.9, 0.93, 0.95, 0.97, 0.99, 1},
        //RHC FGD2 #nu_{#mu} (background) CC 0#pi in AntiNu_Mode
        {-1, 0.7, 0.8, 0.85, 0.88, 0.9, 0.92, 0.94, 0.96, 0.97, 0.98, 0.99, 1},
        //RHC FGD2 #nu_{#mu} (background) CC 1#pi  in AntiNu_Mode
        {-1, 0.7, 0.8, 0.86, 0.9, 0.94, 0.96, 0.97, 0.98, 0.99, 1},
        //RHC FGD2 #nu_{#mu} (background) CC Other  in AntiNu_Mode
        {-1, 0.7, 0.8, 0.86, 0.9, 0.93, 0.95, 0.97, 0.99, 1},
        //FHC SFGD #nu_{#mu} CC 0#pi 0p
        {-1, 0.5, 0.6, 0.68, 0.72, 0.76, 0.82, 0.84, 0.86, 0.88, 0.9, 0.91, 0.92, 0.93, 0.94, 0.95, 0.955, 0.96, 0.965, 0.97, 0.975, 0.98, 0.985, 0.99, 0.995, 1},
        //FHC SFGD #nu_{#mu} CC 0#pi Np
        {-1, 0.55, 0.65, 0.75, 0.8, 0.85, 0.88, 0.9, 0.92, 0.93, 0.94, 0.95, 0.96, 0.97, 0.98, 0.988, 1},
        //FHC SFGD #nu_{#mu} CC 1#pi 0p
        {-1, 0.6, 0.68, 0.74, 0.79, 0.85, 0.9, 0.91, 0.92, 0.93, 0.94, 0.95, 0.96, 0.97, 0.98, 0.99, 1},
        //RHC SFGD #bar{#nu}_{#mu} CC 0#pi 0n
        {-1, 0.6, 0.7, 0.8, 0.85, 0.9, 0.92, 0.93, 0.94, 0.95, 0.96, 0.965, 0.97, 0.975, 0.98, 0.985, 0.99, 0.995, 1},
        //RHC SFGD #bar{#nu}_{#mu} CC 0#pi Nn
        {-1, 0.6, 0.7, 0.8, 0.85, 0.9, 0.92, 0.93, 0.94, 0.95, 0.96, 0.965, 0.97, 0.975, 0.98, 0.985, 0.99, 0.995, 1},
        //RHC SFGD #bar{#nu}_{#mu} CC 1#pi 0n
        {-1, 0.7, 0.8, 0.9, 0.94, 0.96, 0.98, 0.99, 1},
    };

    std::vector<std::vector<double>> binpmu = {
        //FHC FGD1 #nu_{#mu} CC 0#pi 0p 0#gamma
        {0, 200, 300, 350, 400, 450, 500, 550, 600, 650, 700, 750, 800, 850, 900, 950, 1000, 1100, 1200, 1300, 1500, 1750, 2000, 2500, 3000, 5000, 30000},
        //FHC FGD1 #nu_{#mu} CC 0#pi Np 0#gamma
        {0., 250., 350., 400., 450., 500., 550., 600., 650., 700., 800., 900., 1000., 1100., 1200., 1300., 1500., 1600., 1750., 2000., 2750., 5000., 30000.},
        //FHC FGD1 #nu_{#mu} CC 1#pi 0#gamma
        {0, 300, 350, 400, 500, 600, 650, 700, 750, 800, 900, 1000, 1100, 1200, 1500, 2000,5000, 30000},
        //FHC FGD1 #nu_{#mu} CC Other 0#gamma
        {0, 350, 500, 600, 650, 700, 800, 900, 1000, 1150, 1250, 1500, 2000, 5000, 30000},
        //FHC FGD1 #nu_{#mu} CC #gamma
        {0., 300., 400., 500., 600., 650., 700., 750., 800., 900., 1000., 1100., 1250., 1500., 1600., 1750., 2000., 2500., 3000., 5000., 30000.},
        //FHC FGD2 #nu_{#mu} CC 0#pi 0p 0#gamma
        {0, 200, 300, 350, 400, 450, 500, 550,  600, 650, 700, 750, 800, 850, 900, 950, 1000, 1100, 1200, 1300, 1500, 1750, 2000, 2500, 3000, 5000, 30000},
        //FHC FGD2 #nu_{#mu} CC 0#pi Np 0#gamma
        {0., 250., 350., 400., 450., 500., 550., 600., 650., 700., 800., 900., 1000., 1100., 1200., 1300., 1500., 1600., 1750., 2000., 2750., 5000., 30000.},
        //FHC FGD2 #nu_{#mu} CC 1#pi 0#gamma
        {0., 250., 350., 400., 450., 500., 550., 600., 650., 700., 800., 900., 1000., 1100., 1200., 1300., 1500., 1600., 1750., 2000., 2750., 5000., 30000.},
        //FHC FGD2 #nu_{#mu} CC Other 0#gamma
        {0, 350, 500, 600, 650, 700, 800, 900, 1000, 1150, 1250, 1500, 2000, 5000, 30000},
        //FHC FGD2 #nu_{#mu} CC #gamma
        {0., 300., 400., 500., 600., 650., 700., 750., 800., 900., 1000., 1100., 1250., 1500., 1600., 1750., 2000., 2500., 3000., 5000., 30000.},
        //RHC FGD1 Anti #nu_{#mu} CC 0#pi
        {0, 300, 400, 500, 550, 600, 650, 700, 750, 800, 900, 1000, 1100, 1200, 1500, 2000, 4000, 30000},
        //RHC FGD1 Anti #nu_{#mu} CC 1#pi
        {0, 500, 700, 900, 1300, 2500, 30000},
        //RHC FGD1 Anti #nu_{#mu} CC Other
        {0, 600, 800, 1000, 1250, 1500, 2000, 4000, 30000},
        //RHC FGD2 Anti #nu_{#mu} CC 0#pi
        {0, 300, 400, 500, 550, 600, 650, 700, 750, 800, 900, 1000, 1100, 1200, 1500, 2000, 4000, 30000},
        //RHC FGD2 Anti #nu_{#mu} CC 1#pi
        {0, 500, 700, 900, 1300, 2500, 30000},
        //RHC FGD2 Anti #nu_{#mu} CC Other
        {0, 600, 800, 1000, 1250, 1500, 2000, 4000, 30000},
        //RHC FGD1 #nu_{#mu} (background) CC 0#pi in AntiNu_Mode
        {0, 300, 500, 700, 800, 900, 1250, 1500, 2000, 4000, 30000},
        //RHC FGD1 #nu_{#mu} (background) CC 1#pi in AntiNu_Mode
        {0, 600, 800, 1500, 30000},
        //RHC FGD1 #nu_{#mu} (background) CC Other in AntiNu_Mode
        {0, 600, 1000, 1250, 2000, 4000, 30000},
        //RHC FGD2 #nu_{#mu} (background) CC 0#pi in AntiNu_Mode
        {0, 300, 500, 700, 800, 900, 1250, 1500, 2000, 4000, 30000},
        //RHC FGD2 #nu_{#mu} (background) CC 1#pi  in AntiNu_Mode
        {0, 600, 800, 1500, 30000},
        //RHC FGD2 #nu_{#mu} (background) CC Other  in AntiNu_Mode
        {0, 600, 1000, 1250, 2000, 4000, 30000},
        //FHC SFGD #nu_{#mu} CC 0#pi 0p
        {0, 200, 300, 350, 400, 450, 500, 550, 600, 650, 700, 750, 800, 850, 900, 950, 1000, 1100, 1200, 1300, 1500, 1750, 2000, 2500, 3000, 5000, 30000},
        //FHC SFGD #nu_{#mu} CC 0#pi Np
        {0., 250., 350., 400., 450., 500., 550., 600., 650., 700., 800., 900., 1000., 1100., 1200., 1300., 1500., 1600., 1750., 2000., 2750., 5000., 30000.},
        //FHC SFGD #nu_{#mu} CC 1#pi 0p
        {0, 300, 350, 400, 500, 600, 650, 700, 750, 800, 900, 1000, 1100, 1200, 1500, 2000,5000, 30000},
        //RHC SFGD #bar{#nu}_{#mu} CC 0#pi 0n
        {0, 300, 400, 500, 550, 600, 650, 700, 750, 800, 900, 1000, 1100, 1200, 1500, 2000, 4000, 30000},
        //RHC SFGD #bar{#nu}_{#mu} CC 0#pi Nn
        {0, 300, 400, 500, 550, 600, 650, 700, 750, 800, 900, 1000, 1100, 1200, 1500, 2000, 4000, 30000},
        //RHC SFGD #bar{#nu}_{#mu} CC 1#pi 0n
        {0, 500, 700, 900, 1300, 2500, 30000},
    };

    // create histos for binning
    std::vector<TH1D*> hpmu;
    std::vector<TH1D*> hcs;
    std::vector<std::vector<TH1D*>> hpmu_res(SAMPLES);
    std::vector<std::vector<TH1D*>> hcs_res(SAMPLES);
     
    // create histo instances
    std::cout << "Initializing histograms\n";
    for(int isample = 0; isample < SAMPLES; isample++) {

        // initialize histogram for costhetamu and pmu
        hpmu.push_back(new TH1D("", "", binpmu[isample].size()-1, &binpmu[isample][0]));
        hcs.push_back(new TH1D("", "", bincos[isample].size()-1, &bincos[isample][0]));

        for(int i = 0; i < binpmu[isample].size()-1; i++) {
            hpmu_res[isample].push_back(new TH1D("", "", 100 , -1, 1));
        }
        for(int j = 0; j < bincos[isample].size()-1; j++) {
            hcs_res[isample].push_back(new TH1D("", "", 100 , -1, 1));
        }
    }

        // loop over events
    std::cout << "Looping over events\n";
    for(int ientry = 0; ientry < nevent; ientry++) {
        tree->GetEntry(ientry);

        // cut large values of weight
        //if(peso > 10) peso = 1;
        //std::cout << ientry << "\n";
        int isample = 0; 
        for(int n = 0; n < SAMPLES; n++) {
            if ( sample == nsamp[n] ) {
                isample = n;
                break;
            }
        }

        std::cout << "Sample: " << sample <<  "\tPmu: " << pmu << "\tCosThetamu: " << cs << "\tPOTWeight: " << peso << std::endl;
        //std::cout << isample << "\n";
        hpmu[isample]->Fill(pmu,peso);
        hcs[isample]->Fill(cs,peso);
        // fill resolution hist and pmu hist using bin edges
        for(int i = 0; i < binpmu[isample].size()-1; i++) {
            //std::cout << i << "\n";
            if(pmu >= hpmu[isample]->GetXaxis()->GetBinLowEdge(i+1) && pmu < hpmu[isample]->GetXaxis()->GetBinUpEdge(i+1)) {
                //std::cout << "Filling bin : [" << hpmu[isample][i]->GetXaxis()->GetBinLowEdge(j+1) << ", " << hpmu[isample][i]->GetXaxis()->GetBinUpEdge(j+1) << "] : " << pmu << "\n";
                hpmu_res[isample][i]->Fill((pmu-trupmu)/trupmu,peso);
            }
        }
        for(int i = 0; i < bincos[isample].size()-1; i++) {
            //std::cout << j << "\n";
            if(cs >= hcs[isample]->GetXaxis()->GetBinLowEdge(i+1) && cs < hcs[isample]->GetXaxis()->GetBinUpEdge(i+1)) {
                //std::cout << "Filling bin : [" << hcs[isample]->GetXaxis()->GetBinLowEdge(i+1) << ", " << hcs[isample]->GetXaxis()->GetBinUpEdge(i+1) << "] : " << pmu << "\n";
                hcs_res[isample][i]->Fill((cs-trucs)/trucs,peso);
            }
        }
    }
 
    // output and saving hist
    // use to turn off display when drawing hist
    // use to shut ROOT the f***k up
    gROOT->SetBatch(kTRUE);
    gErrorIgnoreLevel = kError;

    std::string tmp;
    for(int isample = 0; isample < SAMPLES; isample++) {

        tmp = "plots/binningAnalysis/analysisplots_samp"+to_string(nsamp[isample])+".root";
        TFile *outfile = new TFile(tmp.c_str(),"RECREATE");
        TDirectory *dir1 = outfile->mkdir("samp_hist");
        TDirectory *dir2 = outfile->mkdir("res_hist");
        TDirectory *suba = dir1->mkdir("cos");
        TDirectory *subb = dir1->mkdir("pmu");
        TDirectory *subc = dir2->mkdir("cos");
        TDirectory *subd = dir2->mkdir("pmu");

        tmp = "Distribution P_{#mu}  "+nhist[isample];
        hpmu[isample]->SetNameTitle("samp_pmu",tmp.c_str());
        hpmu[isample]->SetTitle(tmp.c_str());
        hpmu[isample]->GetXaxis()->SetTitle("P_{#mu}");
        hpmu[isample]->GetYaxis()->SetTitle("Events");
        hpmu[isample]->SetOption("HISTE");
        hpmu[isample]->SetFillColor(kGreen);
        hpmu[isample]->SetFillStyle(3004);
        subb->cd();
        hpmu[isample]->Write();

        tmp = "Distribution cos #theta_{#mu} "+nhist[isample];
        hcs[isample]->SetNameTitle("samp_cos",tmp.c_str());
        hcs[isample]->GetXaxis()->SetTitle("cos #theta_{#mu}");
        hcs[isample]->GetYaxis()->SetTitle("Events");
        hcs[isample]->SetOption("HISTE");
        hcs[isample]->SetFillColor(kBlue);
        hcs[isample]->SetFillStyle(3004);
        suba->cd();
        hcs[isample]->Write();

        // when applying weights to histos use integral instead of gebincontents to get the right number of entries
        std::cout << "\n\nSample :  " << nhist[isample] << " bin analysis :"
            << "\nTotal entries in sample : " << hpmu[isample]->Integral();

        std::cout << std::endl << "*********************************************************************" << std::endl;
        std::cout << std::endl
            << setw(12) << "Variable"       
            << setw(14) << "Bin"
            << setw(10) << "Events"
            << setw(15) << "Resolution"    
            << setw(8) << "Width"
            << setw(11) << "Bin Error " << std::endl;
        std::cout << "*********************************************************************" << std::endl;

        // Show bin contents
        for(int ibin = 1; ibin < hpmu[isample]->GetNbinsX() + 1; ibin++) {

            tmp = "res_pmu_bin"+to_string(ibin);
            hpmu_res[isample][ibin-1]->SetName(tmp.c_str());
            tmp = "Resolution P_{#mu} for bin "+to_string(ibin);
            hpmu_res[isample][ibin-1]->SetTitle(tmp.c_str());
            hpmu_res[isample][ibin-1]->GetXaxis()->SetTitle("#frac{Pmu - TruePmu}{TruePmu}");
            hpmu_res[isample][ibin-1]->GetYaxis()->SetTitle("Events");
            hpmu_res[isample][ibin-1]->SetOption("HISTE");
            hpmu_res[isample][ibin-1]->SetFillColor(kViolet);
            hpmu_res[isample][ibin-1]->SetFillStyle(3004);
            subd->cd();
            hpmu_res[isample][ibin-1]->Write();

            std::cout 
                << setw(12) << "Pmu"
                << " [" << setw(5) << hpmu[isample]->GetXaxis()->GetBinLowEdge(ibin) << "," << setw(5) << hpmu[isample]->GetXaxis()->GetBinUpEdge(ibin) << "]" 
                << setw(10) << hpmu[isample]->GetBinContent(ibin)
                << setw(15) << hpmu_res[isample][ibin-1]->GetStdDev()*2
                << setw(8) << hpmu[isample]->GetBinWidth(ibin)
                << setw(11) << hpmu[isample]->GetBinError(ibin) << std::endl;
            // show contents per sample for pmu
        }
        for(int jbin = 1; jbin < hcs[isample]->GetNbinsX() + 1; jbin++) {

            tmp = "res_cos_bin"+to_string(jbin);
            hcs_res[isample][jbin-1]->SetName(tmp.c_str());
            tmp = "Resolution cos #theta_{#mu} for bin "+to_string(jbin);
            hcs_res[isample][jbin-1]->SetTitle(tmp.c_str());
            hcs_res[isample][jbin-1]->GetXaxis()->SetTitle("#frac{CosThetamu - TrueCosThetamu}{TrueCosThetamu}");
            hcs_res[isample][jbin-1]->GetYaxis()->SetTitle("Events");
            hcs_res[isample][jbin-1]->SetOption("HISTE");
            hcs_res[isample][jbin-1]->SetFillColor(kRed);
            hcs_res[isample][jbin-1]->SetFillStyle(3004);
            subc->cd();
            hcs_res[isample][jbin-1]->Write();

            std::cout 
                << setw(12) << "CosThetamu"
                << " [" << setw(5)<< hcs[isample]->GetXaxis()->GetBinLowEdge(jbin) << "," << setw(5) << hcs[isample]->GetXaxis()->GetBinUpEdge(jbin) << "]" 
                << setw(10) << hcs[isample]->GetBinContent(jbin)
                << setw(15) << hcs_res[isample][jbin-1]->GetStdDev()*2
                << setw(8) << hcs[isample]->GetBinWidth(jbin)
                << setw(11) << hcs[isample]->GetBinError(jbin) << std::endl;

        }
        outfile->Close();
    }
}
