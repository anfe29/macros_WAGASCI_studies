from ROOT import TFile, TH2, TGraph, TCanvas

path = "plots/2Dhist/2Dplot.root"
f = TFile(path)

hist = []

# define key and iterator
key = TKey()
keyList = TIter(dir_samp.GetListOfKeys())

# add canvas to array
for key in keyList:
    hist.append(key.ReadObj())
    name = hist[-1].GetTitle()
    hist[-1].GetXaxis().SetMaximum(hist[-1].GetXaxis().GetXmax())
    hist[-1].GetXaxis().SetMinimum(hist[-1].GetXaxis().GetXmin())
    hist[-1].GetYaxis().SetMaximum(hist[-1].GetYaxis().GetYmax())
    hist[-1].GetYaxis().SetMinimum(hist[-1].GetYaxis().GetYmin())
    hist[-1].Draw("colz")
    hist[-1].SavAs("2D_hist_"+name+".png")

