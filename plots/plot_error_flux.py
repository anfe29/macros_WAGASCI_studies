import numpy as np
import math
from ROOT import *
from array import array

# ### makes canvases of POT error evolution for flux dials (similar to fluxErrors.py but for flux) ####

def getRelError(i, idials, year, fit_path):
    
    '''Returns the relative error of dials[i] for a specified year'''
    file = TFile(fit_path)

    #flux = file.Get('FitterEngine/postFit/Hesse/errors/Flux Systematics/valuesNorm/postFitErrors_TH1D')
    flux = file.Get('FitterEngine/postFit/Migrad/errors/Flux Systematics/valuesNorm/postFitErrors_TH1D')

    err = flux.GetBinError(idials[i])
    return err

def rel_error_evolution(i, idials, pot, fit_paths):
    '''returns an array of relative flux errors for a dial i, with length = number of pot'''
    err_evol = array('d')
    j = 0
    for y in pot:
        err_evol.append(getRelError(i, idials, y, fit_paths[j]))
        j += 1
    return err_evol

def plot_flux_errs(file, subsets, dials, idials, pot, fit_paths_fgd_fhc):
    '''plots the relative & absolute flux errors of all dials, and saves the plots in two canvases'''
    if (len(idials) <= 4): gStyle.SetPalette(kBlueGreenYellow)
    else: gStyle.SetPalette(kRainBow)
    gStyle.SetLegendBorderSize(3)
    gStyle.SetLegendTextSize(0.03)
    
    c1 = TCanvas("c1", "c1", 700, 1200)
    c1.cd()
    
    gPad.SetMargin(0.13, 0.05, 0.06, 0.5)
    gPad.SetFrameBorderSize(0)
    relativeUncertainties1 = TMultiGraph()
    relativeUncertainties2 = TMultiGraph()
    relativeUncertainties3 = TMultiGraph()
    apot = array('d', pot)
    for i in range(len(dials)):
        gr_temp = TGraph(len(pot), apot, rel_error_evolution(i, idials, pot, fit_paths_fgd_fhc))
        gr_temp.SetTitle(dials[i])
        gr_temp.SetMarkerStyle(kFullCircle)
        gr_temp.SetLineWidth(2)
        gr_temp.SetLineStyle(4)
        relativeUncertainties1.Add(gr_temp)

        gr_temp2 = TGraph(len(pot), apot, rel_error_evolution(i, idials, pot, fit_paths_sfgd_fhc))
        #gr_temp2.SetTitle(dials[i])
        gr_temp2.SetMarkerStyle(kFullCircle)
        gr_temp2.SetLineWidth(2)
        gr_temp2.SetLineStyle(9)
        relativeUncertainties2.Add(gr_temp2)

        gr_temp3 = TGraph(len(pot), apot, rel_error_evolution(i, idials, pot, fit_paths_sfgd_wagasci_fhc))
        #gr_temp2.SetTitle(dials[i])
        gr_temp3.SetMarkerStyle(kFullCircle)
        gr_temp3.SetLineWidth(2)
        relativeUncertainties3.Add(gr_temp3)

    relativeUncertainties1.GetXaxis().SetTitle("x10^{21} POT")
    relativeUncertainties1.GetXaxis().SetTitleOffset(0.6)
    relativeUncertainties1.GetXaxis().SetTitleSize(0.045)
    relativeUncertainties1.GetXaxis().SetLabelSize(0.045)
    relativeUncertainties1.GetXaxis().SetLabelOffset(-0.01)
    relativeUncertainties1.GetYaxis().SetTitle("#sigma_{postfit}/#sigma_{prefit}")
    relativeUncertainties1.GetYaxis().SetTitleSize(0.045)
    relativeUncertainties1.GetYaxis().SetLabelSize(0.04505)
    relativeUncertainties1.SetMaximum(1.)
    relativeUncertainties1.SetMinimum(0.2)
    relativeUncertainties1.Draw("LAP PLC PMC")
    gPad.BuildLegend(0.06, 0.52, 0.96, 0.52+(0.99-0.52)*((len(idials))/7.0))
    
    leg = TLegend(0.65, 0.75, 0.95, 0.55)
    line = TH1D("h", "", 1, 0, 1)
    line.SetLineColor(kBlack)
    line.SetLineWidth(2)
    line.SetLineStyle(4)
    line2 = TH1D("hh", "", 1, 0, 1)
    line2.SetLineColor(kBlack)
    line2.SetLineWidth(2)
    line2.SetLineStyle(9)
    line3 = TH1D("hhh", "", 1, 0, 1)
    line3.SetLineColor(kBlack)
    line3.SetLineWidth(2)
    line3.SetTitleSize(1)
    leg.AddEntry(line, "FGD FHC", "l")
    leg.AddEntry(line2, "FGD+SFGD FHC", "l")
    leg.AddEntry(line3, "WG+FGD+SFGD FHC", "l")
    leg.Draw()

    relativeUncertainties2.Draw("LP PLC PMC")
    relativeUncertainties3.Draw("LP PLC PMC")

    c1.Update()     
    #c1.SaveAs("plots/pot_studies/flux/WAGASCI_FGD_onlyFHC/{}_hesse.png".format(subsets))
    c1.SaveAs("plots/pot_studies/flux/WAGASCI_FGD_onlyFHC/{}_migrad.png".format(subsets))
    file.cd()
    c1.SetName("{}_migrad".format(subsets))
    c1.Write()



idialsset = [
        [1, 2, 3, 4, 5],  
        [6, 7, 8, 9, 10],  
        [11, 12, 13, 14, 15],  
        [16, 17, 18, 19, 20],  
        [21, 22, 23, 24, 25],
        [26, 27, 28, 29, 30],
        [31, 32, 33, 34, 35],
        [36, 37, 38, 39, 40],  
]

dialsset = [
        ["Enu:[0, 0.1]", "Enu:[0.1, 0.2]", "Enu:[0.2, 0.3]", "Enu:[0.3, 0.4]", "Enu:[0.4, 0.5]"], # 
        ["Enu:[0.5, 0.6]", "Enu:[0.6, 0.7]", "Enu:[0.7, 0.8]", "Enu:[0.8, 0.9]", "Enu:[0.9, 1]"], # 
        ["Enu:[1, 1.2]", "Enu:[1.2, 1.5]", "Enu:[1.5, 2]", "Enu:[2, 2.5]", "Enu:[2.5, 3]"], # 
        ["Enu:[3, 3.5]", "Enu:[3.5, 4]", "Enu:[4, 5]", "Enu:[5, 7]", "Enu:[7, 10]"], # 
        ["Enu:[0, 0.1]", "Enu:[0.1, 0.2]", "Enu:[0.2, 0.3]", "Enu:[0.3, 0.4]", "Enu:[0.4, 0.5]"], # 
        ["Enu:[0.5, 0.6]", "Enu:[0.6, 0.7]", "Enu:[0.7, 0.8]", "Enu:[0.8, 0.9]", "Enu:[0.9, 1]"], # 
        ["Enu:[1, 1.2]", "Enu:[1.2, 1.5]", "Enu:[1.5, 2]", "Enu:[2, 2.5]", "Enu:[2.5, 3]"], # 
        ["Enu:[3, 3.5]", "Enu:[3.5, 4]", "Enu:[4, 5]", "Enu:[5, 7]", "Enu:[7, 10]"], # 
]


subsets = [
        "bin 1-5 FHC WAGASCI #nu_{#mu} Low Enu", 
        "bin 6-10 FHC WAGASCI #nu_{#mu} Low Enu", 
        "bin 11-15 FHC WAGASCI #nu_{#mu} High Enu", 
        "bin 16-20 FHC WAGASCI #nu_{#mu} High Enu", 
        "bin 21-25  FHC ND280 #nu_{#mu} Low Enu", 
        "bin 26-30  FHC ND280 #nu_{#mu} Low Enu", 
        "bin 31-35  FHC ND280 #nu_{#mu} High Enu", 
        "bin 36-40  FHC ND280 #nu_{#mu} High Enu", 
]

pot = [0.33, 1.3, 2.3, 3.3, 4.3, 5.3, 6.3, 7.3]
#pot = [0.33, 1.3, 2.3, 3.3]

fit_paths_fgd_fhc = [
    "studies_sampKenj/outputs/prelim_jointfit/pot_fhc/FGD_onlyFHC/pot0.33.root",
    "studies_sampKenj/outputs/prelim_jointfit/pot_fhc/FGD_onlyFHC/pot1.3.root",
    "studies_sampKenj/outputs/prelim_jointfit/pot_fhc/FGD_onlyFHC/pot2.3.root",
    "studies_sampKenj/outputs/prelim_jointfit/pot_fhc/FGD_onlyFHC/pot3.3.root",
    "studies_sampKenj/outputs/prelim_jointfit/pot_fhc/FGD_onlyFHC/pot4.3.root",
    "studies_sampKenj/outputs/prelim_jointfit/pot_fhc/FGD_onlyFHC/pot5.3.root",
    "studies_sampKenj/outputs/prelim_jointfit/pot_fhc/FGD_onlyFHC/pot6.3.root",
    "studies_sampKenj/outputs/prelim_jointfit/pot_fhc/FGD_onlyFHC/pot7.3.root",
]

#fit_paths_fgd_wagasci_fhc  = [
#    "studies_sampKenj/outputs/prelim_jointfit/pot_fhc/WAGASCI_FGD_onlyFHC/pot0.33.root",
#    "studies_sampKenj/outputs/prelim_jointfit/pot_fhc/WAGASCI_FGD_onlyFHC/pot1.3.root",
#    "studies_sampKenj/outputs/prelim_jointfit/pot_fhc/WAGASCI_FGD_onlyFHC/pot2.3.root",
#    "studies_sampKenj/outputs/prelim_jointfit/pot_fhc/WAGASCI_FGD_onlyFHC/pot3.3.root",
#    "studies_sampKenj/outputs/prelim_jointfit/pot_fhc/WAGASCI_FGD_onlyFHC/pot4.3.root",
#    "studies_sampKenj/outputs/prelim_jointfit/pot_fhc/WAGASCI_FGD_onlyFHC/pot5.3.root",
#    "studies_sampKenj/outputs/prelim_jointfit/pot_fhc/WAGASCI_FGD_onlyFHC/pot6.3.root",
#    "studies_sampKenj/outputs/prelim_jointfit/pot_fhc/WAGASCI_FGD_onlyFHC/pot7.3.root",
#]

fit_paths_sfgd_fhc  = [
    "studies_sampKenj/outputs/prelim_jointfit/pot_fhc/FGD_SFGD_onlyFHC/pot0.33.root",
    "studies_sampKenj/outputs/prelim_jointfit/pot_fhc/FGD_SFGD_onlyFHC/pot1.3.root",
    "studies_sampKenj/outputs/prelim_jointfit/pot_fhc/FGD_SFGD_onlyFHC/pot2.3.root",
    "studies_sampKenj/outputs/prelim_jointfit/pot_fhc/FGD_SFGD_onlyFHC/pot3.3.root",
    "studies_sampKenj/outputs/prelim_jointfit/pot_fhc/FGD_SFGD_onlyFHC/pot4.3.root",
    "studies_sampKenj/outputs/prelim_jointfit/pot_fhc/FGD_SFGD_onlyFHC/pot5.3.root",
    "studies_sampKenj/outputs/prelim_jointfit/pot_fhc/FGD_SFGD_onlyFHC/pot6.3.root",
    "studies_sampKenj/outputs/prelim_jointfit/pot_fhc/FGD_SFGD_onlyFHC/pot7.3.root",
]

fit_paths_sfgd_wagasci_fhc  = [
    "studies_sampKenj/outputs/prelim_jointfit/pot_fhc/WAGASCI_FGD_SFGD_onlyFHC/pot0.33.root",
    "studies_sampKenj/outputs/prelim_jointfit/pot_fhc/WAGASCI_FGD_SFGD_onlyFHC/pot1.3.root",
    "studies_sampKenj/outputs/prelim_jointfit/pot_fhc/WAGASCI_FGD_SFGD_onlyFHC/pot2.3.root",
    "studies_sampKenj/outputs/prelim_jointfit/pot_fhc/WAGASCI_FGD_SFGD_onlyFHC/pot3.3.root",
    "studies_sampKenj/outputs/prelim_jointfit/pot_fhc/WAGASCI_FGD_SFGD_onlyFHC/pot4.3.root",
    "studies_sampKenj/outputs/prelim_jointfit/pot_fhc/WAGASCI_FGD_SFGD_onlyFHC/pot5.3.root",
    "studies_sampKenj/outputs/prelim_jointfit/pot_fhc/WAGASCI_FGD_SFGD_onlyFHC/pot6.3.root",
    "studies_sampKenj/outputs/prelim_jointfit/pot_fhc/WAGASCI_FGD_SFGD_onlyFHC/pot7.3.root",
]

# the python macro assumes that 2022-2027 fits are in 'fit_path' and named: 0703_banffsfgd****_datacorrect_2M.root
# if this is no longer the case, change 'fit_path' or the names in getRelError() and getAbsError()

# ### if you want to call only one of the flux subsets, either change lists above or function call below ####
# ### canvas.Save() names are automatically adjusted for the different subsets ####

gROOT.SetBatch(kTRUE)

print("Number of subsets: "+str(len(subsets)))
print("Number of dials: "+str(len(dialsset)))
print("Number of dial: "+str(len(idialsset)))
print("Number of POT sets: "+str(len(pot)))


file = TFile("plots/pot_studies/flux/WAGASCI_FGD_onlyFHC/plots.root","RECREATE")
for i in range(len(subsets)):
    print("Processing subset :"+subsets[i])
    plot_flux_errs(file, subsets[i], dialsset[i], idialsset[i], pot, fit_paths_fgd_fhc)

print("Done")
