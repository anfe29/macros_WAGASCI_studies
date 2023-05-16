import numpy as np
import math
import os
from ROOT import *

gROOT.SetBatch(True)

param_name = [
        "P Shell MF Norm C", "S Shell MF Norm C", "SRC Norm C", "P Shell MF p_{miss} Shape C", "S Shell MF p_{miss} Shape C", # SF Carbon
        "P_{12} Shell MF Norm O", "P_{32} Shell MF Norm O", "S Shell MF Norm O", "SRC Norm O", "P_{12} Shell MF p_{miss} Shape O", "P_{32} Shell MF p_{miss} Shape O", "S Shell MF p_{miss} Shape O" # SF Oxygen
]

dial_pos = [
        12, 13, 14, 15, 16, # SF Carbon
        17, 18, 19, 20, 21, 22, 23 # SF Oxygen
]

corr = [0, 20, 30, 40, 50, 60, 70, 80, 95]

fits = ["FGD_onlyFHC", "FGD_SFGD_onlyFHC", "WAGASCI_FGD_SFGD_onlyFHC"]

path_to_errors = "FitterEngine/postFit/Migrad/errors/Cross-Section Systematics/valuesNorm/postFitErrors_TH1D"
#path_to_errors = "FitterEngine/postFit/Hesse/errors/Cross-Section Systematics/valuesNorm/postFitErrors_TH1D"
path_to_outputs = "studies_sampKenj/outputs/prelim_jointfit/pot_fhc/corr/FHC_COcorr"


for iparam in range(len(param_name)):
    print(param_name[iparam])
    c1 = TCanvas()
    gr = [TGraph() for ifit in range(len(fits))]

    for icorr in range(len(corr)):
        path_to_corr = path_to_outputs+str(corr[icorr])+"/"
        #print(corr[i])
        print(path_to_corr)
        leg = TLegend(0.75, 0.85, 0.95, 0.95)
        for ifit in range(len(fits)):

            path_to_fits = path_to_corr+fits[ifit]+"/pot4.3.root"
            print("\t"+path_to_fits)

            f = TFile(path_to_fits)
            err_hist = f.Get(path_to_errors)
            #err = err_hist.GetBinError(dial_pos[iparam])
            gr[ifit].SetMarkerStyle(kFullCircle)
            gr[ifit].SetLineWidth(2)
            gr[ifit].SetLineStyle(9)
            gr[ifit].AddPoint(corr[icorr],err_hist.GetBinError(dial_pos[iparam]))
            #leg.AddEntry(gr[i][j],"FGD","l")
            #print("\tError: "+str(err))
            #print(os.listdir(path_to_fits))
            #for ifile in range(len(os.listdir(path_to_fits))):

    leg.AddEntry(gr[0],"FGD","l")
    leg.AddEntry(gr[1],"FGD+SFGD","l")
    leg.AddEntry(gr[2],"WG+FGD+SFGD","l")
    for ifit in range(len(fits)):
        if ifit == 0:
            gr[ifit].SetTitle(param_name[iparam])
            gr[ifit].GetXaxis().SetTitle("Correlations (%)")
            gr[ifit].GetXaxis().SetTitleOffset(0.8)
            gr[ifit].GetXaxis().SetTitleSize(0.045)
            gr[ifit].GetXaxis().SetLabelSize(0.04)
            gr[ifit].GetYaxis().SetTitle("#sigma_{postfit}/#sigma_{prefit}")
            #gr[ifit].SetMaximum(1)
            gr[ifit].SetMaximum(gr[0].GetYaxis().GetXmax()*1.05)
            gr[ifit].SetMinimum(0)
            gr[ifit].SetMinimum(gr[2].GetYaxis().GetXmin()*0.95)
            gr[ifit].Draw("LAP PLC PMC")
        else:
            gr[ifit].Draw("LP PLC PMC")
            
    leg.Draw()
    c1.Update()
    c1.SaveAs("plots/err_corr/{}.png".format(param_name[iparam]))
