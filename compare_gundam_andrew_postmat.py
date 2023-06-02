import os
import numpy as np
from ROOT import *
import uproot
import sys

gROOT.SetBatch(True)

apath = "/sps/t2k/buizza/ND280/AndrewFitter/Wagasci/xsLLhFitter/outputs/xsecKenji_asimov_template-flux-det-xsec_noeigen_nosplinebug.root"
gpath = "/sps/t2k/buizza/ND280/GUNDAM/feb2023/inputs_WAGASCIxsec/xsecKenji_test_template-flux-det-xsec_OPok_fakeSplineBinning_newTempPars.root"
opath = "per_margherita/cov_posfit.root"

if not os.path.exists(apath):
    apath = input("Enter xsllhFitter ouput file: ")
if not os.path.exists(gpath):
    gpath = input("Enter GUDAM ouput file: ")

# with uproot
afile = uproot.open(apath)
gfile = uproot.open(gpath)

amatrix = afile["res_cov_matrix"].to_numpy()
ghist = gfile["FitterEngine/postFit/Hesse/hessian/postfitCovarianceOriginal_TH2D"].to_numpy()

# convert TH2D to Tmatrix
gmatrix= np.array(ghist)

omatrix = amatrix - gmatrix

'''
# with pyroot
afile = TFile(apath)
gfile = TFile(gpath)

amatrix = afile.Get("res_cov_matrix")
gmatrix = gfile.Get("FitterEngine/postFit/Hesse/hessian/postfitCovarianceOriginal_TH2D")

if amatrix.GetNcols() != gmatrix.GetNbinsX():
    print("Matrices not the same size!")
    exit()

nbins = amatrix.GetNcols()
omatrix = TH2D("cov_diff", "",nbinx )

for ientry in range(nbins):
    for jentry in range(nbins):
        #diff = amatrix[ientry][jentry] - gmatrix.GetBinContent(GetBin(ientry, jentry))
        print("Matrix element: [ " + str(ientry) + " , " + str(jentry) + " ]")
        print("\txsllhFitter output matrix entry: "+str(amatrix[ientry][jentry]))
        print("\tGUNDAM output matrix entry: "+str(gmatrix.GetBinContent(gmatrix.GetBin(ientry, jentry))))
        print("\tAbsolute Difference: "+str(abs(amatrix[ientry][jentry] - gmatrix.GetBinContent(gmatrix.GetBin(ientry, jentry)))))
'''
if not os.path.exists(apath):
    opath = input("Enter ouput file: ")

with uproot.create(opath) as file:
    file["kenji_postfit_cov" ] = uproot.newtree({"kenji_postfit_cov" : "TMatrixD"})
    file["gundam_postfit_cov"] = uproot.newtree({"gundam_postfit_cov": "TMatrixD"})
    file["diff_cov"          ] = uproot.newtree({"diff_cov"          : "TMatrixD"})

    file["kenji_postfit_cov" ].extend({"kenji_postfit_cov" : amatrix})
    file["gundam_postfit_cov"].extend({"gundam_postfit_cov": gmatrix})
    file["diff_cov"          ].extend({"diff_cov"          : omatrix})
