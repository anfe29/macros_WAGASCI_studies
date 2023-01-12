import sys
from ROOT import TFile, TH1, TH2, TGraph, TCanvas

# path to root files to compare
path1 = sys.argv[1] 
path2 = sys.argv[2]

# name file
fname1 = path1[25:-5]
fname2 = path2[25:-5]

# initialize root files
infile1 = TFile(path1)
infile2 = TFile(path2)

# get error hist from files
postfiterr1_flux = infile1.Get("FitterEngine/postFit/Hesse/errors/Flux Systematics/values/postFitErrors_TH1D")
'''
postfiterr1_xsecfsi = infile1.Get("FitterEngine/postFit/Hesse/errors/Cross-Section FSI Systematics/values/postFitErrors_TH1D")
postfiterr1_xsec = infile1.Get("FitterEngine/postFit/Hesse/errors/Cross-Section Systematics/values/postFitErrors_TH1D")
postfiterr1_xsecbin = infile1.Get("FitterEngine/postFit/Hesse/errors/Cross-Section (binned) Systematics/values/postFitErrors_TH1D")
postfiterr1_xsecwg = infile1.Get("Fitterengine/postfit/Hesse/errors/Cross-Section (WAGASCI-binned) Systematics/values/postFitErrors_TH1D")
'''

postfiterr2_flux = infile2.Get("FitterEngine/postFit/Hesse/errors/Flux Systematics/values/postFitErrors_TH1D")
'''
postfiterr2_xsecfsi = infile2.Get("FitterEngine/postFit/Hesse/errors/Cross-Section FSI Systematics/values/postFitErrors_TH1D")
postfiterr2_xsec = infile2.Get("FitterEngine/postFit/Hesse/errors/Cross-Section Systematics/values/postFitErrors_TH1D")
postfiterr2_xsecbin = infile2.Get("FitterEngine/postFit/Hesse/errors/Cross-Section (binned) Systematics/values/postFitErrors_TH1D")
postfiterr2_xsecwg = infile2.Get("Fitterengine/postfit/Hesse/errors/Cross-Section (WAGASCI-binned) Systematics/values/postFitErrors_TH1D")
'''

# superimpose plots
c1 =TCanvas("c1", "", 1920, 1080)

postfiterr1_flux.SetTitle("Post-fit Errors comparison 1")
postfiterr1_flux.SetFillStyle(3003)
postfiterr1_flux.SetFillColor(54)
postfiterr1_flux.SetMarkerColor(54)
postfiterr1_flux.SetMarkerStyle(20)
postfiterr1_flux.SetMarkerSize(1)

postfiterr2_flux.SetTitle("Post-fit Errors comparison 2")
postfiterr2_flux.SetFillStyle(3003)
postfiterr2_flux.SetFillColor(50)
postfiterr2_flux.SetMarkerColor(50)
postfiterr2_flux.SetMarkerStyle(20)
postfiterr2_flux.SetMarkerSize(1)

postfiterr1_flux.Draw()
c1.SaveAs("plots/compErr/fluxcomptest1.png")

postfiterr2_flux.Draw()
c1.SaveAs("plots/compErr/fluxcomptest2.png")


# err ratio between fits per parameter


# relative diff between fits per parameter
