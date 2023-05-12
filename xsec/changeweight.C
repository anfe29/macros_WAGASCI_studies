void changeweight()
{
    TFile *infile = new TFile("xsec_sampKenj/inputs/datasets/selection_results_input_for_pmu_binning_sample_both_sample_split_w_true_topology.root");
    TTree *intree = (TTree*) infile->Get("selectedEvents");
    
    //TFile *outfile = new TFile("xsec_sampKenj/inputs/datasets/reweight_2p2h_O.root","RECREATE");
    TFile *outfile = new TFile("xsec_sampKenj/inputs/datasets/reweight_2p2h_C.root","RECREATE");
    //TFile *outfile = new TFile("xsec_sampKenj/inputs/datasets/reweight_CCDIS.root","RECREATE");
    intree->SetBranchStatus("weight",0);
    TTree *tree = intree->CloneTree();

    int reac, tar;
    float in_weight, out_weight;

    intree->SetBranchStatus("weight",1);
    intree->SetBranchAddress("weight", &in_weight);
    intree->SetBranchAddress("target", &tar);
    intree->SetBranchAddress("reaction", &reac);

    TBranch *branch = tree->Branch("weight", &out_weight);

    int nentries = intree->GetEntries();
    for(int ientry = 0; ientry < nentries; ientry++) {
        intree->GetEntry(ientry);

        //if(tar == 0 && reac == 1) out_weight = in_weight*1.4;
        //else out_weight = in_weight;

        if(tar == 1 && reac == 1) out_weight = in_weight*1.4;
        else out_weight = in_weight;

        //if(reac == 4) out_weight = in_weight*1.4;
        //else out_weight = in_weight;

        //std::cout << "\nold weight: " << in_weight << "\n";
        //std::cout << "new weight: " << out_weight << "\n";

        branch->Fill();
    }

    //outfile->cd();
    tree->Write();
    outfile->Close(); 
    //tree->Print();
}
