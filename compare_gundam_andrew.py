from ROOT import TFile, TH1, TGraph
import sys

# Check number of arguments
if (len(sys.argv) != 3):
    print("Usage: python compare_gundam_andrew.py")
    print("\t xsLLhFitterpostfitFile")
    print("\t gundamPostfitFile")
    #print("\t outputfolder")
    exit()
else:
    print("Processing xsLLhFitter and GUNDAM files")

apath = sys.argv[1]
gpath = sys.argv[2]

afile = TFile(apath)
gfile = TFile(gpath)

if afile.IsZombie() or gfile.IsZombie():
    print("File does not exist")
    exit()
else:
    print("Files found!\n")

hist_name = ["pm_wm_cc0pi", "pm_bm_cc0pi", "pm_cc1pi", "wg_cc0pi_uwg_wm", "wg_cc0pi_uwg_bm" ,"wg_cc0pi_dwg_bm" , "wg_cc1pi"]
ahist = []
ghist = []

for i in range(len(hist_name)):
    aname = "evhist_sam"+str(i)+"_iter0_mc"
    gname = "FitterEngine/preFit/samples/histograms/"+hist_name[i]+"/Raw/MC_TH1D"

    ahist.append(afile.Get(aname))
    ghist.append(gfile.Get(gname))

    #print("Kenji hist name: "+ahist[i].GetTitle())
    #print("GUNDAM hist name: "+ghist[i].GetTitle()+"\n")
    print("Sample: "+hist_name[i])
    for ibin in range(ahist[i].GetNbinsX()+1):
        #print("\txsLLhFitter: Bin content for bin "+str(ibin)+str(ahist[i].Integral(ibin,ibin+1)))
        #print("\tGUNDAM: Bin content for bin "+str(ibin)+str(ghist[i].Integral(ibin,ibin+1)))
        print("\tDifference for bin "+str(ibin+1)+": "+str(abs((ahist[i].Integral(ibin,ibin+1)-ghist[i].Integral(ibin,ibin+1))/ghist[i].Integral(ibin,ibin+1)))+"%")
    #print()
    print("Total difference: "+str(abs((ahist[i].Integral()-ghist[i].Integral())/ghist[i].Integral()))+"%\n")

