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

for ientry in range(len(amatrix.GetNcols())):
    for jentry in range(len(amatrix.GetNcols())):
        #amatrix[ientry][jentry] -= gmatrix.GetBin(ientry, jentry)
        print("xsllhFitter output matrix: "+str(amatrix[ientry][jentry]))
        print("GUNDAM output matrix: "+str(gmatrix.GetBin(ientry, jentry)))
