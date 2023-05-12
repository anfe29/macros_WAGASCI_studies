import numpy as np
import math
import os
from ROOT import *

gROOT.SetBatch(True)

param_name = [
        "P Shell MF Norm C", "S Shell MF Norm C", "SRC Norm C", "P Shell MF p_{miss} Shape C", "S Shell MF p_{miss} Shape C", # SF Carbon
        "P_{1/2} Shell MF Norm O", "P_{3/2} Shell MF Norm O", "S Shell MF Norm O", "SRC Norm O", "P_{1/2} Shell MF p_{miss} Shape O", "P_{3/2} Shell MF p_{miss} Shape O", "S Shell MF p_{miss} Shape O" # SF Oxygen
]

dial_pos = [
        12, 13, 14, 15, 16, # SF Carbon
        17, 18, 19, 20, 21, 22, 23 # SF Oxygen
]

corr = [0, 20, 30, 40, 50, 60, 95 ]

fits = ["FGD_onlyFHC", "FGD_SFGD_onlyFHC", "WAGASCI_FGD_SFGD_onlyFHC"]

path_to_errors = "FitterEngine/postFit/Migrad/errors/Cross-Section Systematics/valuesNorm/postFitErrors_TH1D"
path_to_outputs = "studies_sampKenj/outputs/prelim_jointfit/pot_fhc/corr/FHC_COcorr"

gr = [[TGraph() for j in range(len(corr))] for i in range(len(fits))] 

for iparam in range(len(param_name)):
    print(param_name[iparam])
    c1 = TCanvas()

    for j in range(len(corr)):
        path_to_corr = path_to_outputs+str(corr[j])+"/"
        #print(corr[i])
        print(path_to_corr)
        leg = TLegend()
        for i in range(len(fits)):

            gr[i][j].SetTitle(param_name[iparam])
            gr[i][j].SetMarkerStyle(kFullCircle)
            gr[i][j].SetLineWidth(2)
            gr[i][j].SetLineStyle(9)
            gr[i][j].GetXaxis().SetTitle("Correlations (%)")
            gr[i][j].GetXaxis().SetTitleOffset(0.8)
            gr[i][j].GetXaxis().SetTitleSize(0.045)
            gr[i][j].GetXaxis().SetLabelSize(0.04)
            gr[i][j].GetYaxis().SetTitle("#sigma_{postfit}/#sigma_{prefit}")

            path_to_fits = path_to_corr+fits[i]+"/pot0.33.root"
            print("\t"+path_to_fits)

            f = TFile(path_to_fits)
            err_hist = f.Get(path_to_errors)
            #err = err_hist.GetBinError(dial_pos[iparam])
            gr[i][j].AddPoint(corr[i],err_hist.GetBinError(dial_pos[iparam]))
            #leg.AddEntry(gr[i][j],"FGD","l")
            #print("\tError: "+str(err))
            #print(os.listdir(path_to_fits))
            #for ifile in range(len(os.listdir(path_to_fits))):
            

    for row in range(len(fits)):
        for col in range(len(corr)):
            if row == 0:
                gr[row][col].Draw()
            else:
                gr[row][col].Draw("SAMES")
            
    #leg.Draw()
    c1.Update()
    c1.SaveAs("plots/err_corr/{}.png".format(param_name[iparam]))
