// macro for showing binning, bin content and bin resolution for binning analysis and refinement
void binningAnal_WG()
{
    // initialize file and tree
    TFile *infile = new TFile("studies_sampKenj/inputs/samples/sample_rootfiles/splines_event_by_event_CCcorrected.root");
    //TFile *infile = new TFile("studies_sampKenj/inputs/samples/sample_rootfiles/wagasci_sample_kenji.root");
    TTree *tree = (TTree*)infile->Get("sample_sum");
    //TTree *tree = (TTree*)infile->Get("selectedEvents");


    // set parameters from tree
    const int SAMPLES = 7;
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
        "FHC WAGASCI PM-WMRD #nu_{#mu} CC-0#pi", 
        "FHC WAGASCI PM-BM #nu_{#mu} CC-0#pi",
        "FHC WAGASCI PM #nu_{#mu} CC-1#pi", 
        "FHC WAGASCI UWG-WMRD #nu_{#mu} CC-0#pi", 
        "FHC WAGASCI UWG-BM #nu_{#mu} CC-0#pi",
        "FHC WAGASCI DWG-BM #nu_{#mu} CC-0#pi", 
        "FHC WAGASCI WG #nu_{#mu} CC-1#pi"};

    // define SelectedSample array
    int nsamp[SAMPLES] = {
        // FHC WAGASCI
        151, 152, 153, 154, 155, 157, 158
    };

    // define binning arrays
    std::vector<std::vector<double>> bincos = {
        //FHC WAGASCI PM-WMRD #nu_{#mu} CC 0#pi 
        {0, 0.425, 0.525, 0.65, 0.75, 0.9, 1},    
        //FHC WAGASCI PM-BM #nu_{#mu} CC 0#pi
        {0, 0.85, 0.9, 0.94, 0.96, 0.98, 1},   
        //FHC WAGASCI PM #nu_{#mu} CC 1#pi 
        {0, 0.5, 0.63, 0.72, 0.87, 0.98, 1}, 
        //FHC WAGASCI UWG-WMRD #nu_{#mu} CC 0#pi 
        {0, 0.5, 0.64, 0.7, 0.85, 1},
        //FHC WAGASCI UWG-BM #nu_{#mu} CC 0#pi     
        {0, 0.9, 0.94, 0.96, 0.98, 1},            
        //FHC WAGASCI DWG-BM #nu_{#mu} CC 0#pi  
        {0, 0.75, 0.85, 0.9, 0.94, 0.96, 0.98, 1}, 
        //FHC WAGASCI WG #nu_{#mu} CC 1#pi 
        {0, 0.67, 0.77, 0.84, 0.9, 0.95, 0.98, 1} 
    };

    std::vector<std::vector<double>> binpmu = {
        //FHC WAGASCI PM-WMRD #nu_{#mu} CC 0#pi 
        {0, 450, 500, 550, 600, 650, 30000},
        //FHC WAGASCI PM-BM #nu_{#mu} CC 0#pi
        {0, 600, 650, 700, 800, 900, 30000},
        //FHC WAGASCI PM #nu_{#mu} CC 1#pi 
        {0, 400, 500, 550, 600, 650, 30000},
        //FHC WAGASCI UWG-WMRD #nu_{#mu} CC 0#pi 
        {0, 400, 450, 500, 550, 600, 650, 700, 30000},
        //FHC WAGASCI UWG-BM #nu_{#mu} CC 0#pi
        {0, 600, 650, 700, 750, 800, 900, 1100, 30000},
        //FHC WAGASCI DWG-BM #nu_{#mu} CC 0#pi 
        {0, 400, 450, 500, 550, 600, 650, 700, 800, 900, 1100, 1400, 30000},
        //FHC WAGASCI WG #nu_{#mu} CC 1#pi
        {0, 400, 500, 550, 600, 650, 700, 750, 800, 900, 1100, 30000},
    };

    // create histos for binning
    std::vector<TH1D*> hpmu;
    std::vector<std::vector<TH1D*>> hcs(SAMPLES);
    std::vector<std::vector<TH1D*>> hpmu_res(SAMPLES);
    std::vector<std::vector<std::vector<TH1D*>>> hcs_res(SAMPLES);
     
    // create histo instances
    std::cout << "Initializing histograms\n";
    for(int isample = 0; isample < SAMPLES; isample++) {

        // initialize histogram for costhetamu and pmu
        hpmu.push_back(new TH1D("", "", binpmu[isample].size()-1, &binpmu[isample][0]));

        hcs_res[isample].resize(binpmu[isample].size());
        for(int i = 0; i < binpmu[isample].size()-1; i++) {
            hcs[isample].push_back(new TH1D("", "", bincos[isample].size()-1, &bincos[isample][0]));
            hpmu_res[isample].push_back(new TH1D("", "", 100 , -1, 1));
            for(int j = 0; j < bincos[isample].size()-1; j++) {
                hcs_res[isample][i].push_back(new TH1D("", "", 100 , -1, 1));
            }
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
        // fill resolution hist and pmu hist using bin edges
        for(int i = 0; i < binpmu[isample].size()-1; i++) {
            //std::cout << i << "\n";
            if(pmu >= hpmu[isample]->GetXaxis()->GetBinLowEdge(i+1) && pmu < hpmu[isample]->GetXaxis()->GetBinUpEdge(i+1)) {
                //std::cout << "Filling bin : [" << hpmu[isample][i]->GetXaxis()->GetBinLowEdge(j+1) << ", " << hpmu[isample][i]->GetXaxis()->GetBinUpEdge(j+1) << "] : " << pmu << "\n";
                hcs[isample][i]->Fill(cs,peso);
                hpmu_res[isample][i]->Fill((pmu-trupmu)/trupmu,peso);
                for(int j = 0; j < bincos[isample].size()-1; j++) {
                    //std::cout << j << "\n";
                    if(cs >= hcs[isample][i]->GetXaxis()->GetBinLowEdge(j+1) && cs < hcs[isample][i]->GetXaxis()->GetBinUpEdge(j+1)) {
                        //std::cout << "Filling bin : [" << hcs[isample]->GetXaxis()->GetBinLowEdge(i+1) << ", " << hcs[isample]->GetXaxis()->GetBinUpEdge(i+1) << "] : " << pmu << "\n";
                        hcs_res[isample][i][j]->Fill((cs-trucs)/trucs,peso);
                    }
                }
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
        std::cout << "*********************************************************************";

        // Show bin contents
        for(int ibin = 1; ibin < hpmu[isample]->GetNbinsX() + 1; ibin++) {

            tmp = "Distribution cos #theta_{#mu} for pmu bin "+to_string(ibin)+" "+nhist[isample];
            hcs[isample][ibin-1]->SetNameTitle("samp_cos",tmp.c_str());
            hcs[isample][ibin-1]->GetXaxis()->SetTitle("cos #theta_{#mu}");
            hcs[isample][ibin-1]->GetYaxis()->SetTitle("Events");
            hcs[isample][ibin-1]->SetOption("HISTE");
            hcs[isample][ibin-1]->SetFillColor(kBlue);
            hcs[isample][ibin-1]->SetFillStyle(3004);
            suba->cd();
            hcs[isample][ibin-1]->Write();

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

            std::cout << std::endl
            << setw(12) << "Pmu"
            << " [" << setw(5) << hpmu[isample]->GetXaxis()->GetBinLowEdge(ibin) << "," << setw(5) << hpmu[isample]->GetXaxis()->GetBinUpEdge(ibin) << "]" 
            << setw(10) << hpmu[isample]->GetBinContent(ibin)
            << setw(15) << hpmu_res[isample][ibin-1]->GetStdDev()*2
            << setw(8) << hpmu[isample]->GetBinWidth(ibin)
            << setw(11) << hpmu[isample]->GetBinError(ibin) << std::endl;
        // show contents per sample for pmu
            for(int jbin = 1; jbin < hcs[isample][ibin-1]->GetNbinsX() + 1; jbin++) {

                tmp = "res_cos_bin"+to_string(ibin)+"_"+to_string(jbin);
                hcs_res[isample][ibin-1][jbin-1]->SetName(tmp.c_str());
                tmp = "Resolution cos #theta_{#mu} for bin "+to_string(jbin);
                hcs_res[isample][ibin-1][jbin-1]->SetTitle(tmp.c_str());
                hcs_res[isample][ibin-1][jbin-1]->GetXaxis()->SetTitle("#frac{CosThetamu - TrueCosThetamu}{TrueCosThetamu}");
                hcs_res[isample][ibin-1][jbin-1]->GetYaxis()->SetTitle("Events");
                hcs_res[isample][ibin-1][jbin-1]->SetOption("HISTE");
                hcs_res[isample][ibin-1][jbin-1]->SetFillColor(kRed);
                hcs_res[isample][ibin-1][jbin-1]->SetFillStyle(3004);
                subc->cd();
                hcs_res[isample][ibin-1][jbin-1]->Write();

                std::cout 
                << setw(12) << "CosThetamu"
                << " [" << setw(5)<< hcs[isample][ibin-1]->GetXaxis()->GetBinLowEdge(jbin) << "," << setw(5) << hcs[isample][ibin-1]->GetXaxis()->GetBinUpEdge(jbin) << "]" 
                << setw(10) << hcs[isample][ibin-1]->GetBinContent(jbin)
                << setw(15) << hcs_res[isample][ibin-1][jbin-1]->GetStdDev()*2
                << setw(8) << hcs[isample][ibin-1]->GetBinWidth(jbin)
                << setw(11) << hcs[isample][ibin-1]->GetBinError(jbin) << std::endl;

            }
        }
        outfile->Close();
    }
}
