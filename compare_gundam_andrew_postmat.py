import os
import numpy as np
from ROOT import *
import uproot
import sys

gROOT.SetBatch(True)

apath = "/sps/t2k/buizza/ND280/AndrewFitter/Wagasci/xsLLhFitter/outputs/xsecKenji_asimov_template-flux-det-xsec_noeigen_nosplinebug.root"
gpath = "/sps/t2k/buizza/ND280/GUNDAM/feb2023/inputs_WAGASCIxsec/xsecKenji_test_template-flux-det-xsec_OPok_fakeSplineBinning_newTempPars.root"
#apath = "xsecKenji_asimov_template-flux-det-xsec_noeigen_nosplinebug.root"
#gpath = "xsecKenji_test_template-flux-det-xsec_OPok_fakeSplineBinning_newTempPars.root"
opath = "per_margherita/cov_postfit.root"

if not os.path.exists(apath):
    apath = input("Enter xsllhFitter ouput file: ")
if not os.path.exists(gpath):
    gpath = input("Enter GUDAM ouput file: ")

# with pyroot
afile = TFile(apath)
gfile = TFile(gpath)

amatrix = TH2D(afile.Get("res_cov_matrix"))
gmatrix = gfile.Get("FitterEngine/postFit/Hesse/hessian/postfitCovarianceOriginal_TH2D")

if amatrix.GetNbinsY() != gmatrix.GetNbinsY():
    print("Matrices not the same size!")
    exit()

nbins = amatrix.GetNbinsX()
omatrix = TH2D("diff_cov", "Difference between xsllhFitter and GUNDAM postfit matrices", nbins, 0, nbins, nbins, 0, nbins)
omatrix1 = TH2D("reldiff_cov", "Relative Difference between xsllhFitter and GUNDAM postfit matrices", nbins, 0, nbins, nbins, 0, nbins)

for ientry in range(nbins):
    for jentry in range(nbins):
        aval = amatrix.GetBinContent(amatrix.GetBin(ientry, jentry))
        gval = gmatrix.GetBinContent(gmatrix.GetBin(ientry, jentry))
        oval = aval - gval
        omatrix.SetBinContent(omatrix.GetBin(ientry, jentry), oval)
        if aval != 0:
            omatrix1.SetBinContent(omatrix1.GetBin(ientry, jentry), oval/aval)
        else:
            omatrix1.SetBinContent(omatrix1.GetBin(ientry, jentry), 0)
        print("Matrix element: [ " + str(ientry) + " , " + str(jentry) + " ]")
        print("\txsllhFitter output matrix entry: "+str(aval))
        print("\tGUNDAM output matrix entry: "+str(gval))
        print("\tAbsolute Difference: "+str(abs(oval)))
        if aval != 0:
            print("\tRelative Difference normalized with Kenji's output: "+str(oval/aval))
        else:
            print("\tRelative Difference normalized with Kenji's output:"+str(0))


#print(omatrix)

if not os.path.exists("per_margherita"):
    #opath = input("Enter ouput file: ")
    os.makedirs("per_margherita")

# save to file
ofile = TFile(opath, "RECREATE")
amatrix.Write("kenji_postfit_cov")
gmatrix.Write("gundam_postfit_cov")
omatrix.Write()
omatrix1.Write()
ofile.Close()

# Draw and save to pdf
gStyle.SetOptStat(0)
gStyle.SetLegendTextSize(0.03)
c1 = TCanvas()
omatrix.Draw("colz")
c1.SaveAs("per_margherita/diff_cov.pdf")
omatrix1.Draw("colz")
c1.SaveAs("per_margherita/reldiff_cov.pdf")
