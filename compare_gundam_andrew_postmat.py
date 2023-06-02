from ROOT import *
import sys

gROOT.SetBatch(True)

apath = "/sps/t2k/buizza/ND280/AndrewFitter/Wagasci/xsLLhFitter/outputs/xsecKenji_asimov_template-flux-det-xsec_noeigen_nosplinebug.root"
gpath = "/sps/t2k/buizza/ND280/GUNDAM/feb2023/inputs_WAGASCIxsec/xsecKenji_test_template-flux-det-xsec_OPok_fakeSplineBinning_newTempPars.root"
opath = ""

afile = TFile(apath)
gfile = TFile(gpath)

if afile.IsZombie() or gfile.IsZombie():
    print("File does not exist")
    exit()
else:
    print("Files found!\n")

amatrix = afile.Get("res_cov_matrix")
gmatrix = gfile.Get("FitterEngine/postFit/Hesse/hessian/postfitCovarianceOriginal_TH2D")

if amatrix.GetNcols() != gmatrix.GetNbinsX():
    print("Matrices not the same size!")
    exit()

#c1 = TCanvas()

for ientry in range(amatrix.GetNcols()):
    for jentry in range(amatrix.GetNcols()):
        #amatrix[ientry][jentry] -= gmatrix.GetBinContent(GetBin(ientry, jentry))
        print("Matrix element: [ " + str(ientry) + " , " + str(jentry) + " ]")
        print("\txsllhFitter output matrix entry: "+str(amatrix[ientry][jentry]))
        print("\tGUNDAM output matrix entry: "+str(gmatrix.GetBinContent(gmatrix.GetBin(ientry, jentry))))
        print("\tAbsolute Difference: "+str(abs(amatrix[ientry][jentry] - gmatrix.GetBinContent(gmatrix.GetBin(ientry, jentry)))))
