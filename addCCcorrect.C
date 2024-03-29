double ApplyCoulombShift(/*int TruePDG,*/int NuPDG, int target, int reaction) {

    // ******************************************

    // Adapted from MaCh3

    int kNEUT_NC1pi01n = 31;

    int kTarget_C = 12;

    int kTarget_O = 16;

    // Only want CC events

    if (reaction >= kNEUT_NC1pi01n) return 0.0;

    // The amount we shift by

    double shift = 0.0;

    // Check the lepton candidate matches the neutrino PDG

    // If anti-neutrino interaction, check that NuPDG
/*
    if (NuPDG < 0) {

        if (NuPDG != TruePDG-1) return shift;

    } else {

        if (NuPDG != TruePDG+1) return shift;

    }
*/

    // Check PID of true particle making this lepton candidate

    // This is now done above as before. The following line is only left for historical comparison

    //if (abs(TruePDG) != 11 && abs(TruePDG) != 13 && abs(TruePDG) != 15) return 0.0;

    // Shift the lepton momentum

    // if (kKinType == kLeptonMomentum) {

    if (true) {

        // Neutrino

        if (NuPDG > 0) {

            // If target was C

            if (target == kTarget_C) {

                shift = -3.6;

                // If target was O

            } else if (target == kTarget_O) {

                shift = -4.3;

            }

            // Anti-neutrino

        } else if (NuPDG < 0) {

            // If target was C

            if (target == kTarget_C) {

                shift = 2.6;

            } else if (target == kTarget_O) {

                shift = 3.3;

            }

        }

        // Return the shiften lepton momentum

        return shift;

        // Shift the Q2 if requested

    }

    return shift;

}

void addCCcorrect()
{
    TFile *infile = new TFile("studies_sampKenj/inputs/samples/sample_rootfiles/splines_event_by_event.root");
    TTree *intree = (TTree*) infile->Get("spline_tree");
    intree->SetName("sample_sum");
    
    TFile *outfile = new TFile("studies_sampKenj/inputs/samples/sample_rootfiles/splines_event_by_event_CCcorrected.root","RECREATE");
    TTree *tree = intree->CloneTree();

    int NeutrinoCode;
    int TgtMat;
    int ReactionCode;
    float Pmu,CosThetamu;
    double PmuCoulombCorrection,D1Reco,D2Reco;

    tree->SetBranchAddress("NeutrinoCode", &NeutrinoCode);
    tree->SetBranchAddress("TgtMat", &TgtMat);
    tree->SetBranchAddress("ReactionCode", &ReactionCode);
    tree->SetBranchAddress("Pmu", &Pmu);
    tree->SetBranchAddress("CosThetamu", &CosThetamu);

    TBranch *branch1 = tree->Branch("PmuCoulombCorrectionWG", &PmuCoulombCorrection);
    TBranch *branch2 = tree->Branch("D1Reco", &D1Reco);
    TBranch *branch3 = tree->Branch("D2Reco", &D2Reco);

    int nentries = tree->GetEntries();
    for(int ientry = 0; ientry < nentries; ientry++) {
        tree->GetEntry(ientry);

        PmuCoulombCorrection = Pmu;
        std::cout << "\nPmu: " << PmuCoulombCorrection << "\n";
        PmuCoulombCorrection += ApplyCoulombShift(NeutrinoCode, TgtMat, TMath::Abs(ReactionCode));
        std::cout << "PmuCoulombCorrection: " << PmuCoulombCorrection << "\n";
        D1Reco = Pmu;
        D2Reco = CosThetamu;

        branch1->Fill();
        branch2->Fill();
        branch3->Fill();
    }

    //tree->Write("sample_sum");
    tree->Write();
    outfile->Close();
}
