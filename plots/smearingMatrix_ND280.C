void smearingMatrix_ND280()
{
    // initialize file and tree

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
    TFile *outfile = new TFile("plots/2Dhist/smearing_ND280/plots.root","RECREATE");

    // set parameters and variables
    const int SAMPLES = 30;
    double pmu, trupmu, cs, trucs, peso;
    int sample;
    int nbin = 100;
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
        //FHC SFGD #nu_{#mu} CC 1#pi Np
        {-1, 0.6, 0.68, 0.74, 0.79, 0.85, 0.9, 0.91, 0.92, 0.93, 0.94, 0.95, 0.96, 0.97, 0.98, 0.99, 1},
        //RHC SFGD #bar{#nu}_{#mu} CC 0#pi 0n
        {-1, 0.6, 0.7, 0.8, 0.85, 0.9, 0.92, 0.93, 0.94, 0.95, 0.96, 0.965, 0.97, 0.975, 0.98, 0.985, 0.99, 0.995, 1},
        //RHC SFGD #bar{#nu}_{#mu} CC 0#pi Nn
        {-1, 0.6, 0.7, 0.8, 0.85, 0.9, 0.92, 0.93, 0.94, 0.95, 0.96, 0.965, 0.97, 0.975, 0.98, 0.985, 0.99, 0.995, 1},
        //RHC SFGD #bar{#nu}_{#mu} CC 1#pi 0n
        {-1, 0.7, 0.8, 0.9, 0.94, 0.96, 0.98, 0.99, 1},
        //RHC SFGD #bar{#nu}_{#mu} CC 1#pi Nn
        {-1, 0.7, 0.8, 0.9, 0.94, 0.96, 0.98, 0.99, 1}
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
        //FHC SFGD #nu_{#mu} CC 1#pi Np
        {0, 300, 350, 400, 500, 600, 650, 700, 750, 800, 900, 1000, 1100, 1200, 1500, 2000,5000, 30000},
        //RHC SFGD #bar{#nu}_{#mu} CC 0#pi 0n
        {0, 300, 400, 500, 550, 600, 650, 700, 750, 800, 900, 1000, 1100, 1200, 1500, 2000, 4000, 30000},
        //RHC SFGD #bar{#nu}_{#mu} CC 0#pi Nn
        {0, 300, 400, 500, 550, 600, 650, 700, 750, 800, 900, 1000, 1100, 1200, 1500, 2000, 4000, 30000},
        //RHC SFGD #bar{#nu}_{#mu} CC 1#pi 0n
        {0, 500, 700, 900, 1300, 2500, 30000},
        //RHC SFGD #bar{#nu}_{#mu} CC 1#pi Nn
        {0, 500, 700, 900, 1300, 2500, 30000}
    };
    int nevent = tree->GetEntries();

    // set branches
    tree->SetBranchAddress("Pmu", &pmu);
    tree->SetBranchAddress("TruePmu", &trupmu);
    tree->SetBranchAddress("CosThetamu", &cs);
    tree->SetBranchAddress("TrueCosThetamu", &trucs);
    tree->SetBranchAddress("POTWeight", &peso);
    tree->SetBranchAddress("SelectedSample", &sample);
    
    int nsamp[SAMPLES] = {
        // FHC FGD
        7, 8, 10, 12, 13, 31, 32, 34, 36, 37, 
        // RHC FGD
        59, 60, 61, 65, 66, 67, 71, 72, 73, 77, 78, 79, 
        // FHC SFGD
        101, 102, 103, 104,
        // RHC SFGD
        111, 112, 113, 114
    };

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
        "FHC SFGD #nu_{#mu} CC 1#pi Np",
        "RHC SFGD #bar{#nu}_{#mu} CC 0#pi 0n",
        "RHC SFGD #bar{#nu}_{#mu} CC 0#pi Nn",
        "RHC SFGD #bar{#nu}_{#mu} CC 1#pi 0n"
        "RHC SFGD #bar{#nu}_{#mu} CC 1#pi Nn"
    };

    // create histos
    std::vector<TH2D*> hpmu;
    std::vector<TH2D*> hpmubin;
    std::vector<TH2D*> hcs;
    std::vector<TH2D*> hcsbin;

    // initialize histos
    for(int isample = 0; isample < SAMPLES; isample++){
        hpmu.push_back(new TH2D("", nhist[isample].c_str(), nbin, 0, 3000, nbin, 0, 3000));
        hcs.push_back(new TH2D("", nhist[isample].c_str(), nbin, 0.3, 1, nbin, 0.3, 1));
        hpmubin.push_back(new TH2D("", nhist[isample].c_str(), binpmu[isample].size()-1, &binpmu[isample][0], binpmu[isample].size()-1, &binpmu[isample][0]));
        hcsbin.push_back(new TH2D("", nhist[isample].c_str(), bincos[isample].size()-1, &bincos[isample][0], bincos[isample].size()-1, &bincos[isample][0]));
        hpmu[isample]->SetXTitle("P_{#mu} True");
        hpmu[isample]->SetYTitle("P_{#mu} Reco");
        hcs[isample]->SetXTitle("cos #theta_{#mu} True");
        hcs[isample]->SetYTitle("cos #theta_{#mu} Reco");
        hpmubin[isample]->SetXTitle("P_{#mu} True");
        hpmubin[isample]->SetYTitle("P_{#mu} Reco");
        hcsbin[isample]->SetXTitle("cos #theta_{#mu} True");
        hcsbin[isample]->SetYTitle("cos #theta_{#mu} Reco");
    }
    
    for(int ientry = 0; ientry < nevent; ientry++) {
        tree->GetEntry(ientry);

        // identify sample
        int isample = 0; 
        for(int n = 0; n < SAMPLES; n++) {
            if ( sample == nsamp[n] ) {
                isample = n;
                break;
            }
        }
        // output
        std::cout << "Sample: " << sample <<  "\tPmu Reco: " << pmu << "\tPmu True: " << trupmu 
        << "\tCosThetamu Reco: " << cs << "\tCosThetamu True: " << trucs << "\tPOTWeight: " << peso << std::endl;
        
        // to work around the prob of large bins, put all large/small values in one bin
        //if(pmu > 1500) pmu = 1499;
        //if(trupmu > 1500) trupmu = 1499;
        //if(cs < 0.3) cs = 0.31;
        //if(trucs < 0.3) trucs = 0.31;


        // fill histos
        hpmu[isample]->Fill(trupmu, pmu, peso);
        hcs[isample]->Fill(trucs, cs, peso);
        hpmubin[isample]->Fill(trupmu, pmu, peso);
        hcsbin[isample]->Fill(trucs, cs, peso);
        //hpmu[isample]->Fill(trupmu, pmu);
        //hcs[isample]->Fill(trucs, cs);
        //hpmubin[isample]->Fill(trupmu, pmu);
        //hcsbin[isample]->Fill(trucs, cs);

    }

    TCanvas *c1 = new TCanvas();
    std::string path = "plots/2Dhist/smearing_ND280/";
    //std::string path = "plots/2Dhist/smearing_without_weight/";
    std::string nfile;
    gStyle->SetOptStat(0);
    outfile->cd();
    for(int isample = 0; isample < SAMPLES; isample++){
    // rescale bins using truth parameters, divide by bin content per column
        double trubin = 0;
        // for finely binned matrices
        for(int i = 0; i<nbin; i++) {
            for(int j = 0; j<nbin; j++) {
                trubin = hpmu[isample]->Integral(i+1,i+1,1,nbin);
                if(hpmu[isample]->GetBinContent(i+1,j+1) == 0) {
                    hpmu[isample]->SetBinContent(i+1,j+1,0);
                }
                else {
                    hpmu[isample]->SetBinContent(i+1,j+1,hpmu[isample]->GetBinContent(i+1,j+1)/trubin);
                }
                trubin = hcs[isample]->Integral(i+1,i+1,1,nbin);
                if(hcs[isample]->GetBinContent(i+1,j+1) == 0) {
                    hcs[isample]->SetBinContent(i+1,j+1,0);
                }
                else {
                    hcs[isample]->SetBinContent(i+1,j+1,hcs[isample]->GetBinContent(i+1,j+1)/trubin);
                }
            }
        }
        // for matrices using my binning
        // pmu matrices
        //std::cout << "Pmu: Sample: " << nhist[isample] << "\n";
        for(int i = 0; i<binpmu[isample].size()-1; i++) {
            trubin = hpmubin[isample]->Integral(i+1,i+1,1,binpmu[isample].size()-1);
            for(int j = 0; j<binpmu[isample].size()-1; j++) {
                if(hpmubin[isample]->GetBinContent(i+1,j+1) == 0) {
                    hpmubin[isample]->SetBinContent(i+1,j+1,0);
                }
                else {
                    hpmubin[isample]->SetBinContent(i+1,j+1,hpmubin[isample]->GetBinContent(i+1,j+1)/trubin);
                    //std::cout << "xbin: " << i+1 << " " << "ybin: " << j+1 << "\n";
                    //std::cout << "True bin content: " << trubin << "\n";
                    //std::cout << "Old bin content: " << hpmubin[isample]->GetBinContent(i+1,j+1) << "\n";
                    //std::cout << "New bin content: " << hpmubin[isample]->GetBinContent(i+1,j+1)/trubin << "\n\n";
                }
            }
        }
        // cos matrices
        //std::cout << "Cos: Sample: " << nhist[isample] << "\n";
        for(int i = 0; i<bincos[isample].size()-1; i++) {
            trubin = hcsbin[isample]->Integral(i+1,i+1,1,bincos[isample].size()-1);
            for(int j = 0; j<bincos[isample].size()-1; j++) {
                if(hcsbin[isample]->GetBinContent(i+1,j+1) == 0) {
                    hcsbin[isample]->SetBinContent(i+1,j+1,0);
                }
                else {
                    hcsbin[isample]->SetBinContent(i+1,j+1,hcsbin[isample]->GetBinContent(i+1,j+1)/trubin);
                    //std::cout << "xbin: " << i+1 << " " << "ybin: " << j+1 << "\n";
                    //std::cout << "True bin content: " << trubin << "\n";
                    //std::cout << "Old bin content: " << hcsbin[isample]->GetBinContent(i+1,j+1) << "\n";
                    //std::cout << "New bin content: " << hcsbin[isample]->GetBinContent(i+1,j+1)/trubin << "\n\n";
                }
            }
        }

        // draw and save plots
        c1->cd();
        hpmu[isample]->Draw("COLZ");
        nfile = path+"unbinned/pmu/plotpmu_"+nhist[isample]+".png";
        c1->SaveAs(nfile.c_str());
        c1->Write();
        hcs[isample]->Draw("COLZ");
        nfile = path+"unbinned/cos/plotcos_"+nhist[isample]+".png";
        c1->SaveAs(nfile.c_str());
        c1->Write();
        //c2->cd();
        hpmubin[isample]->Draw("COLZ");
        nfile = path+"binned/pmu/plotpmubin_"+nhist[isample]+".png";
        c1->SaveAs(nfile.c_str());
        c1->Write();
        hcsbin[isample]->Draw("COLZ");
        nfile = path+"binned/cos/plotcsbin_"+nhist[isample]+".png";
        c1->SaveAs(nfile.c_str());
        c1->Write();
    }
    outfile->Close();
}
