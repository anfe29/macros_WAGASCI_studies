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

corr = [0, 30, 95]
#corr = [0, 20, 30, 40, 50, 60, 70, 80, 95]
#corr = [0, 10, 20, 30, 40, 50, 60, 70, 80, 90]

pot = [0.33, 1.3, 2.3, 3.3, 4.3, 5.3, 6.3, 7.3]

fits = ["FGD_onlyFHC", "FGD_SFGD_onlyFHC", "WAGASCI_FGD_SFGD_onlyFHC"]

path_to_errors = "FitterEngine/postFit/Migrad/errors/Cross-Section Systematics/valuesNorm/postFitErrors_TH1D"
#path_to_errors = "FitterEngine/postFit/Hesse/errors/Cross-Section Systematics/valuesNorm/postFitErrors_TH1D"
path_to_outputs = "studies_sampKenj/outputs/prelim_jointfit/pot_fhc/corr/FHC_COcorr"
#path_to_outputs = "studies_sampKenj/outputs/prelim_jointfit/pot_fhc/corr_fix/FHC_COcorr"


for iparam in range(len(param_name)):
    print(param_name[iparam])
    c1 = TCanvas()
    gr = [TGraph() for icorr in range(len(corr))]

    for icorr in range(len(corr)):
        path_to_corr = path_to_outputs+str(corr[icorr])+"/"
        #print(corr[i])
        print(path_to_corr)
        leg = TLegend(0.75, 0.85, 0.95, 0.95)
        #for ifit in range(len(fits)):
        for ipot in range(len(pot)):

            path_to_fits = path_to_corr+fits[2]+"/pot"+str(pot[ipot])+".root"
            print("\t"+path_to_fits)

            f = TFile(path_to_fits)
            err_hist = f.Get(path_to_errors)
            #err = err_hist.GetBinError(dial_pos[iparam])
            gr[icorr].SetMarkerStyle(kFullCircle)
            gr[icorr].SetLineWidth(2)
            gr[icorr].SetLineStyle(9)
            gr[icorr].AddPoint(pot[ipot],err_hist.GetBinError(dial_pos[iparam]))
            #print("\tError: "+str(err))
            #print(os.listdir(path_to_fits))
            #for ifile in range(len(os.listdir(path_to_fits))):

    leg.AddEntry(gr[0],str(corr[0])+"%","l")
    leg.AddEntry(gr[1],str(corr[1])+"%","l")
    leg.AddEntry(gr[2],str(corr[2])+"%","l")
    for icorr in range(len(corr)):
        if icorr == 0:
            gr[icorr].SetTitle(param_name[iparam])
            gr[icorr].GetXaxis().SetTitle("x10^{21} POT")
            gr[icorr].GetXaxis().SetTitleOffset(0.8)
            gr[icorr].GetXaxis().SetTitleSize(0.045)
            gr[icorr].GetXaxis().SetLabelSize(0.04)
            gr[icorr].GetYaxis().SetTitle("#sigma_{postfit}/#sigma_{prefit}")
            if gr[0].GetYaxis().GetXmax() > gr[1].GetYaxis().GetXmax():
                gr[icorr].SetMaximum(gr[0].GetYaxis().GetXmax()*1.05)
            else:
                gr[icorr].SetMaximum(gr[1].GetYaxis().GetXmax()*1.05)
            gr[icorr].SetMinimum(gr[2].GetYaxis().GetXmin()*0.95)
            gr[icorr].Draw("LAP PLC PMC")
        else:
            gr[icorr].Draw("LP PLC PMC")
            
    leg.Draw()
    c1.Update()
    #c1.SaveAs("plots/err_corr/{}.png".format(param_name[iparam]))
    #c1.SaveAs("plots/err_corr_fix/{}.png".format(param_name[iparam]))
    c1.SaveAs("plots/err_corr_pot/{}_{}.png".format(param_name[iparam],fits[2]))
