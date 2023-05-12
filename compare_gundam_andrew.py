from ROOT import *
import sys

gROOT.SetBatch(True)

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
c1 = TCanvas()
#c1.SetLogy()

for i in range(len(hist_name)):
    aname = "evhist_sam"+str(i)+"_iter0_mc"
    gname = "FitterEngine/preFit/samples/histograms/"+hist_name[i]+"/Raw/MC_TH1D"

    ahist.append(afile.Get(aname))
    ghist.append(gfile.Get(gname))

    c1.cd()

    ghist[i].Draw("HISTE")
    ghist[i].SetLineWidth(2)
    ghist[i].SetLineColor(kBlue-1)
    ghist[i].SetFillColor(kBlue-1)
    ghist[i].SetMarkerColor(kBlue-1)

    ahist[i].SetLineWidth(2)
    ahist[i].SetLineColor(kCyan+2)
    ahist[i].SetFillColor(kCyan+2)
    ahist[i].SetMarkerColor(kCyan+2)
    ahist[i].SetMarkerStyle(kFullCircle)
    ahist[i].Draw("HISTE SAME")

    leg = TLegend(0.75, 0.85, 0.95, 0.95)
    leg.AddEntry(ghist[i], "GUNDAM", "l")
    leg.AddEntry(ahist[i], "xsllhfitter", "l")
    leg.Draw()

    c1.Update()
    c1.SaveAs("plots/hist_compare/hist_"+str(hist_name[i])+".png")
    c1.Clear()

    #print("Kenji hist name: "+ahist[i].GetTitle())
    #print("GUNDAM hist name: "+ghist[i].GetTitle()+"\n")
    print("Sample: "+hist_name[i])
    for ibin in range(ahist[i].GetNbinsX()+1):
        #print("\txsLLhFitter: Bin content for bin "+str(ibin)+": "+str(ahist[i].Integral(ibin,ibin+1)))
        #print("\tGUNDAM: Bin content for bin "+str(ibin)+": "+str(ghist[i].Integral(ibin,ibin+1)))
        print("\tDifference for bin "+str(ibin+1)+": "+str((abs((ahist[i].Integral(ibin,ibin+1)-ghist[i].Integral(ibin,ibin+1))/ghist[i].Integral(ibin,ibin+1)))*100)+"%")
        #print("\tDifference for bin "+str(ibin+1)+": "+str(ahist[i].Integral(ibin,ibin+1)-ghist[i].Integral(ibin,ibin+1)))
    #print()
    print("Total difference: "+str((abs((ahist[i].Integral()-ghist[i].Integral())/ghist[i].Integral()))*100)+"%\n")
    #print("\txsLLhFitter: Total bin content:"+str(ahist[i].Integral()))
    #print("\tGUNDAM: Total bin content:"+str(ghist[i].Integral()))

