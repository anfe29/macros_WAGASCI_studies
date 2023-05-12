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
gdir = gfile.Get("FitterEngine/preFit/scan/llh")

if afile.IsZombie() or gfile.IsZombie():
    print("File does not exist")
    exit()
else:
    print("Files found!\n")

# corresponding scan position in xsllhfitter with respect to gundam scan output
scan_no = [6, 7, 8, 9, 10, 11, 0, 1, 2, 3, 4, 5, # template CH then H2O
           12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, # flux
           59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, # detector
           32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58] # xsec
           #32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58] # no Res Eb

agraph = []
ggraph = []
c1 = TCanvas()

key = TKey(gdir)
keyList = TIter(gdir.GetListOfKeys())

i = 0
for key in keyList:
    #aname = "par_scan_"+str(scan_no[i])
    aname = "par_scan_"+str(scan_no[i])
    #print(aname)

    ggraph.append(key.ReadObj())
    agraph.append(afile.Get(aname))

    c1.cd()

    ggraph[i].Draw()
    ggraph[i].SetLineWidth(2)
    ggraph[i].SetLineColor(kBlue-1)
    ggraph[i].SetMarkerColor(kBlue-1)

    agraph[i].SetLineWidth(2)
    agraph[i].SetLineColor(kCyan+2)
    agraph[i].SetMarkerColor(kCyan+2)
    agraph[i].SetMarkerStyle(kFullCircle)
    agraph[i].Draw("LP SAME")
    #print(ggraph[-1].IsA())

    leg = TLegend()
    leg.AddEntry(ggraph[i], "GUNDAM", "l")
    leg.AddEntry(agraph[i], "xsllhfitter", "l")
    leg.Draw()

    c1.Update()
    c1.SaveAs("plots/llh_scans/scans_"+str(scan_no[i])+".png")
    c1.Clear()
    i += 1

