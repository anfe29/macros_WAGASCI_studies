import os
import numpy as np
from ROOT import *
import uproot
import sys

gROOT.SetBatch(True)

#apath = "/sps/t2k/buizza/ND280/AndrewFitter/Wagasci/xsLLhFitter/outputs/xsecKenji_asimov_template-flux-det-xsec_noeigen_nosplinebug.root"
#gpath = "/sps/t2k/buizza/ND280/GUNDAM/feb2023/inputs_WAGASCIxsec/xsecKenji_test_template-flux-det-xsec_OPok_fakeSplineBinning_newTempPars.root"
apath = "xsecKenji_asimov_template-flux-det-xsec_noeigen_nosplinebug.root"
gpath = "xsecKenji_test_template-flux-det-xsec_OPok_fakeSplineBinning_newTempPars.root"
opath = "per_margherita/cov_postfit.root"

if not os.path.exists(apath):
    apath = input("Enter xsllhFitter ouput file: ")
if not os.path.exists(gpath):
    gpath = input("Enter GUDAM ouput file: ")

# with pyroot
afile = TFile(apath)
gfile = TFile(gpath)

icov1 = TH2D(afile.Get("res_cov_matrix"))
icov2 = gfile.Get("FitterEngine/postFit/Hesse/hessian/postfitCovarianceOriginal_TH2D")
icorr1 = TH2D(afile.Get("res_cor_matrix"))
icorr2 = gfile.Get("FitterEngine/postFit/Hesse/hessian/postfitCorrelationOriginal_TH2D")

if icov1.GetNbinsY() != icov2.GetNbinsY():
    print("Matrices not the same size!")
    exit()

nbins = icov1.GetNbinsX()
ocov1 = TH2D("diff_cov", "Difference between xsllhFitter and GUNDAM postfit cov matrices", nbins, 0, nbins, nbins, 0, nbins)
ocov2 = TH2D("reldiff_cov", "Relative Difference between xsllhFitter and GUNDAM postfit cov matrices", nbins, 0, nbins, nbins, 0, nbins)
ocorr1 = TH2D("diff_corr", "Difference between xsllhFitter and GUNDAM postfit corr matrices", nbins, 0, nbins, nbins, 0, nbins)
ocorr2 = TH2D("ratio_corr", "Ratio between xsllhFitter and GUNDAM postfit corr matrices", nbins, 0, nbins, nbins, 0, nbins)

for ientry in range(nbins):
    for jentry in range(nbins):
        aval = icov1.GetBinContent(icov1.GetBin(ientry, jentry))
        gval = icov2.GetBinContent(icov2.GetBin(ientry, jentry))
        oval = aval - gval
        ocov1.SetBinContent(ocov1.GetBin(ientry, jentry), oval)
        if aval != 0:
            ocov2.SetBinContent(ocov2.GetBin(ientry, jentry), oval/aval)
        else:
            ocov2.SetBinContent(ocov2.GetBin(ientry, jentry), 0)
        #if aval != 0:
        #if aval != 0 and (oval/aval > 10):
        #    print("Matrix element: [ " + str(ientry) + " , " + str(jentry) + " ]")
        #    print("\txsllhFitter output matrix entry: "+str(aval))
        #    print("\tGUNDAM output matrix entry: "+str(gval))
        #    print("\tDifference: "+str(abs(oval)))
        #    print("\tRelative Difference normalized with Kenji's output: "+str(oval/aval))
        #else:
        #    print("\tRelative Difference normalized with Kenji's output:"+str(0))

        aval = icorr1.GetBinContent(icorr1.GetBin(ientry, jentry))
        gval = icorr2.GetBinContent(icorr2.GetBin(ientry, jentry))
        oval = aval - gval
        ocorr1.SetBinContent(ocorr1.GetBin(ientry, jentry), oval)
        if aval != 0:
            ocorr2.SetBinContent(ocorr2.GetBin(ientry, jentry), aval/gval)
        else:
            ocorr2.SetBinContent(ocorr2.GetBin(ientry, jentry), 0)
        if aval != 0 and (aval/gval < -10):
            print("Matrix element: [ " + str(ientry) + " , " + str(jentry) + " ]")
            print("\txsllhFitter output matrix entry: "+str(aval))
            print("\tGUNDAM output matrix entry: "+str(gval))
            print("\tDifference: "+str(abs(oval)))
            #print("\tRelative Difference normalized with Kenji's output: "+str(oval/aval))
            print("\tRatio correlation matrices output: "+str(aval/gval))
        #else:
        #    print("\tRelative Difference normalized with Kenji's output:"+str(0))


#print(ocov1)

if not os.path.exists("per_margherita"):
    #opath = input("Enter ouput file: ")
    os.makedirs("per_margherita")

# save to file
ofile = TFile(opath, "RECREATE")
icov1.Write("kenji_postfit_cov")
icov2.Write("gundam_postfit_cov")
ocov1.Write()
ocov2.Write()

icorr1.Write("kenji_postfit_corr")
icorr2.Write("gundam_postfit_corr")
ocorr1.Write()
ocorr2.Write()
ofile.Close()

# Draw and save to pdf
gStyle.SetOptStat(0)
c1 = TCanvas()
ocov1.Draw("colz")
c1.SaveAs("per_margherita/diff_cov.pdf")
ocov2.Draw("colz")
c1.SaveAs("per_margherita/reldiff_cov.pdf")
ocorr1.Draw("colz")
c1.SaveAs("per_margherita/diff_corr.pdf")
ocorr2.Draw("colz")
c1.SaveAs("per_margherita/ratio_corr.pdf")
