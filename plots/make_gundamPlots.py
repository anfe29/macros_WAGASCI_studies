import sys
from ROOT import TFile, TH1, TH2, TCanvas, TKey, TIter

# pass path to root file
path = sys.argv[1] 

# CAREFUL be sure to run from ../<macros-direcotry>, might implement some fix to this constraint later
fname = path[25:-5]

# use given path to open root file
infile = TFile(path)

# get postfit errors canvas
#gun_covmatrix = infile.Get("FitterEngine/postFit/Hesse/hessian/postfitCovarianceOriginal_TH2D")
gun_fitconst_flux = infile.Get("FitterEngine/postFit/Hesse/errors/Flux Systematics/values/fitConstraints_TCanvas")
gun_fitconst_xsecfsi = infile.Get("FitterEngine/postFit/Hesse/errors/Cross-Section FSI Systematics/values/fitConstraints_TCanvas")
gun_fitconst_xsec = infile.Get("FitterEngine/postFit/Hesse/errors/Cross-Section Systematics/values/fitConstraints_TCanvas")
gun_fitconst_xsecbin = infile.Get("FitterEngine/postFit/Hesse/errors/Cross-Section (binned) Systematics/values/fitConstraints_TCanvas")
gun_fitconst_xsecwg = infile.Get("Fitterengine/postfit/Hesse/errors/Cross-Section (WAGASCI-binned) Systematics/values/fitConstraints_TCanvas")

# get sample plots
samples = []
dir_samp = infile.Get("FitterEngine/postfit/samples/canvas/Pmu/reaction")

# define key and iterator
key = TKey()
keyList = TIter(dir_samp.GetListOfKeys())

# add canvas to array
for key in keyList:
    samples.append(key.ReadObj())

# draw and save canvas
for i in len(samples):
    samples[i].Draw()
    samples[i].SavAs("plots/samples/" + fname + "_samples_" + str(i) + ".png")

# save plots as png, draw them to save
#gun_covmatrix.Draw("colz")
#gun_covmatrix.SaveAs("plots/cov_matrix/" + fname + "_covmatrix.png")

gun_fitconst_flux.Draw()
gun_fitconst_flux.SaveAs("plots/fitconst/" + fname + "_flux.png")

gun_fitconst_xsecfsi.Draw()
gun_fitconst_xsecfsi.SaveAs("plots/fitconst/" + fname + "_xsecfsi.png")

gun_fitconst_xsec.Draw()
gun_fitconst_xsec.SaveAs("plots/fitconst/" + fname + "_xsec.png")

gun_fitconst_xsecbin.Draw()
gun_fitconst_xsecbin.SaveAs("plots/fitconst/" + fname + "_xsecbin.png")

gun_fitconst_xsecwg.Draw()
gun_fitconst_xsecwg.SaveAs("plots/fitconst/" + fname + "_xsecwg.png")
