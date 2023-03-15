import numpy as np
import math
from ROOT import *
from array import array

# ### makes canvases of POT error evolution for flux dials (similar to fluxErrors.py but for flux) ####

def getRelError(i, idials, year, fit_path):
    
    '''Returns the relative error of dials[i] for a specified year'''
    file = TFile(fit_path)

    flux = file.Get('FitterEngine/postFit/Hesse/errors/Flux Systematics/valuesNorm/postFitErrors_TH1D')
    #flux = file.Get('FitterEngine/postFit/Migrad/errors/Flux Systematics/valuesNorm/postFitErrors_TH1D')

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

def plot_flux_errs(subsets, dials, idials, pot, fit_paths_wagasci):
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
        gr_temp = TGraph(len(pot), apot, rel_error_evolution(i, idials, pot, fit_paths_wagasci))
        gr_temp.SetTitle(dials[i])
        gr_temp.SetMarkerStyle(kFullCircle)
        gr_temp.SetLineWidth(2)
        gr_temp.SetLineStyle(4)
        relativeUncertainties1.Add(gr_temp)

        gr_temp2 = TGraph(len(pot), apot, rel_error_evolution(i, idials, pot, fit_paths_fgd2))
        #gr_temp2.SetTitle(dials[i])
        gr_temp2.SetMarkerStyle(kFullCircle)
        gr_temp2.SetLineWidth(2)
        gr_temp2.SetLineStyle(9)
        relativeUncertainties2.Add(gr_temp2)

        gr_temp3 = TGraph(len(pot), apot, rel_error_evolution(i, idials, pot, fit_paths_fgd2_wagasci))
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
    relativeUncertainties1.SetMaximum(2.2)
    relativeUncertainties1.SetMinimum(0)
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
    leg.AddEntry(line, "WAGASCI", "l")
    leg.AddEntry(line2, "FGD2", "l")
    leg.AddEntry(line3, "WAGASCI+FGD2", "l")
    leg.Draw()

    relativeUncertainties2.Draw("LP PLC PMC")
    relativeUncertainties3.Draw("LP PLC PMC")

    c1.Update()     
    #c1.SaveAs("plots/pot_studies/flux/WAGASCI_FGD2/{}.png".format(subsets))
    c1.SaveAs("plots/pot_studies/flux/WAGASCI_FGD2/{}_migrad.png".format(subsets))



idialsset = [
        [1, 2, 3, 4, 5],  
        [6, 7, 8, 9, 10],  
        [11, 12, 13, 14, 15],  
        [16, 17, 18, 19, 20],  
        [21, 22, 23, 24, 25],
        [26, 27, 28, 29, 30],
        [31, 32, 33, 34, 35],
        [36, 37, 38, 39, 40],  
        [41, 42, 43, 44, 45],
        [46, 47, 48, 49, 50],
        [51, 52, 53, 54, 55],
        [56, 57, 58, 59, 60],  
        [61, 62, 63, 64, 65],
        [66, 67, 68, 69, 70],
        [71, 72, 73, 74, 75],
        [76, 77, 78, 79, 80],
        [81, 82, 83, 84, 85],
        [86, 87, 88, 89, 90],
        [91, 92, 93, 94, 95],
        [96, 97, 98, 99, 100],
        [101, 102, 103, 104, 105],
        [106, 107, 108, 109, 110],
        [111, 112, 113, 114, 115],
        [116, 117, 118, 119, 120],  
        [121, 122, 123, 124, 125],
        [126, 127, 128, 129, 130],
        [131, 132, 133, 134, 135],
        [136, 137, 138, 139, 140],  
        [141, 142, 143, 144, 145],
        [146, 147, 148, 149, 150],
        [151, 152, 153, 154, 155],
        [156, 157, 158, 159, 160],  
        [161, 162, 163, 164, 165],
        [166, 167, 168, 169, 170],
        [171, 172, 173, 174, 175],
        [176, 177, 178, 179, 180],  
        [181, 182, 183, 184, 185],
        [186, 187, 188, 189, 190],
        [191, 192, 193, 194, 195],
        [196, 197, 198, 199, 200],  
        [201, 202, 203, 204, 205],
        [206, 207, 208, 209, 210],
        [211, 212, 213, 214, 215],
        [216, 217, 218, 219, 220],  
        [221, 222, 223, 224, 225],
        [226, 227, 228, 229, 220],
        [221, 222, 223, 224, 225],
        [226, 227, 228, 239, 240],  
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
        ["Enu:[0, 0.1]", "Enu:[0.1, 0.2]", "Enu:[0.2, 0.3]", "Enu:[0.3, 0.4]", "Enu:[0.4, 0.5]"], # 
        ["Enu:[0.5, 0.6]", "Enu:[0.6, 0.7]", "Enu:[0.7, 0.8]", "Enu:[0.8, 0.9]", "Enu:[0.9, 1]"], # 
        ["Enu:[1, 1.2]", "Enu:[1.2, 1.5]", "Enu:[1.5, 2]", "Enu:[2, 2.5]", "Enu:[2.5, 3]"], # 
        ["Enu:[3, 3.5]", "Enu:[3.5, 4]", "Enu:[4, 5]", "Enu:[5, 7]", "Enu:[7, 10]"], # 
        ["Enu:[0, 0.1]", "Enu:[0.1, 0.2]", "Enu:[0.2, 0.3]", "Enu:[0.3, 0.4]", "Enu:[0.4, 0.5]"], # 
        ["Enu:[0.5, 0.6]", "Enu:[0.6, 0.7]", "Enu:[0.7, 0.8]", "Enu:[0.8, 0.9]", "Enu:[0.9, 1]"], # 
        ["Enu:[1, 1.2]", "Enu:[1.2, 1.5]", "Enu:[1.5, 2]", "Enu:[2, 2.5]", "Enu:[2.5, 3]"], # 
        ["Enu:[3, 3.5]", "Enu:[3.5, 4]", "Enu:[4, 5]", "Enu:[5, 7]", "Enu:[7, 10]"], # 
        ["Enu:[0, 0.1]", "Enu:[0.1, 0.2]", "Enu:[0.2, 0.3]", "Enu:[0.3, 0.4]", "Enu:[0.4, 0.5]"], # 
        ["Enu:[0.5, 0.6]", "Enu:[0.6, 0.7]", "Enu:[0.7, 0.8]", "Enu:[0.8, 0.9]", "Enu:[0.9, 1]"], # 
        ["Enu:[1, 1.2]", "Enu:[1.2, 1.5]", "Enu:[1.5, 2]", "Enu:[2, 2.5]", "Enu:[2.5, 3]"], # 
        ["Enu:[3, 3.5]", "Enu:[3.5, 4]", "Enu:[4, 5]", "Enu:[5, 7]", "Enu:[7, 10]"], # 
        ["Enu:[0, 0.1]", "Enu:[0.1, 0.2]", "Enu:[0.2, 0.3]", "Enu:[0.3, 0.4]", "Enu:[0.4, 0.5]"], # 
        ["Enu:[0.5, 0.6]", "Enu:[0.6, 0.7]", "Enu:[0.7, 0.8]", "Enu:[0.8, 0.9]", "Enu:[0.9, 1]"], # 
        ["Enu:[1, 1.2]", "Enu:[1.2, 1.5]", "Enu:[1.5, 2]", "Enu:[2, 2.5]", "Enu:[2.5, 3]"], # 
        ["Enu:[3, 3.5]", "Enu:[3.5, 4]", "Enu:[4, 5]", "Enu:[5, 7]", "Enu:[7, 10]"], # 
        ["Enu:[0, 0.1]", "Enu:[0.1, 0.2]", "Enu:[0.2, 0.3]", "Enu:[0.3, 0.4]", "Enu:[0.4, 0.5]"], # 
        ["Enu:[0.5, 0.6]", "Enu:[0.6, 0.7]", "Enu:[0.7, 0.8]", "Enu:[0.8, 0.9]", "Enu:[0.9, 1]"], # 
        ["Enu:[1, 1.2]", "Enu:[1.2, 1.5]", "Enu:[1.5, 2]", "Enu:[2, 2.5]", "Enu:[2.5, 3]"], # 
        ["Enu:[3, 3.5]", "Enu:[3.5, 4]", "Enu:[4, 5]", "Enu:[5, 7]", "Enu:[7, 10]"], # 
        ["Enu:[0, 0.1]", "Enu:[0.1, 0.2]", "Enu:[0.2, 0.3]", "Enu:[0.3, 0.4]", "Enu:[0.4, 0.5]"], # 
        ["Enu:[0.5, 0.6]", "Enu:[0.6, 0.7]", "Enu:[0.7, 0.8]", "Enu:[0.8, 0.9]", "Enu:[0.9, 1]"], # 
        ["Enu:[1, 1.2]", "Enu:[1.2, 1.5]", "Enu:[1.5, 2]", "Enu:[2, 2.5]", "Enu:[2.5, 3]"], # 
        ["Enu:[3, 3.5]", "Enu:[3.5, 4]", "Enu:[4, 5]", "Enu:[5, 7]", "Enu:[7, 10]"], # 
        ["Enu:[0, 0.1]", "Enu:[0.1, 0.2]", "Enu:[0.2, 0.3]", "Enu:[0.3, 0.4]", "Enu:[0.4, 0.5]"], # 
        ["Enu:[0.5, 0.6]", "Enu:[0.6, 0.7]", "Enu:[0.7, 0.8]", "Enu:[0.8, 0.9]", "Enu:[0.9, 1]"], # 
        ["Enu:[1, 1.2]", "Enu:[1.2, 1.5]", "Enu:[1.5, 2]", "Enu:[2, 2.5]", "Enu:[2.5, 3]"], # 
        ["Enu:[3, 3.5]", "Enu:[3.5, 4]", "Enu:[4, 5]", "Enu:[5, 7]", "Enu:[7, 10]"], # 
        ["Enu:[0, 0.1]", "Enu:[0.1, 0.2]", "Enu:[0.2, 0.3]", "Enu:[0.3, 0.4]", "Enu:[0.4, 0.5]"], # 
        ["Enu:[0.5, 0.6]", "Enu:[0.6, 0.7]", "Enu:[0.7, 0.8]", "Enu:[0.8, 0.9]", "Enu:[0.9, 1]"], # 
        ["Enu:[1, 1.2]", "Enu:[1.2, 1.5]", "Enu:[1.5, 2]", "Enu:[2, 2.5]", "Enu:[2.5, 3]"], # 
        ["Enu:[3, 3.5]", "Enu:[3.5, 4]", "Enu:[4, 5]", "Enu:[5, 7]", "Enu:[7, 10]"], # 
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
        "bin 21-25 FHC WAGASCI #bar{#nu}_{#mu} Low Enu", 
        "bin 26-30 FHC WAGASCI #bar{#nu}_{#mu} Low Enu", 
        "bin 31-35 FHC WAGASCI #bar{#nu}_{#mu} High Enu", 
        "bin 36-40 FHC WAGASCI #bar{#nu}_{#mu} High Enu", 
        "bin 41-45 RHC WAGASCI #nu_{#mu} Low Enu", 
        "bin 46-50 RHC WAGASCI #nu_{#mu} Low Enu", 
        "bin 51-55 RHC WAGASCI #nu_{#mu} High Enu", 
        "bin  56-60 RHC WAGASCI #nu_{#mu} High Enu", 
        "bin 61-65 RHC WAGASCI #bar{#nu}_{#mu} Low Enu", 
        "bin 66-70 RHC WAGASCI #bar{#nu}_{#mu} Low Enu", 
        "bin 71-75 RHC WAGASCI #bar{#nu}_{#mu} High Enu", 
        "bin 76-80 RHC WAGASCI #bar{#nu}_{#mu} High Enu", 
        "bin 81-85 FHC ND280 #nu_{#mu} Low Enu", 
        "bin 86-90 FHC ND280 #nu_{#mu} Low Enu", 
        "bin 91-95 FHC ND280 #nu_{#mu} High Enu", 
        "bin 96-100 FHC ND280 #nu_{#mu} High Enu", 
        "bin 101-105 FHC ND280 #bar{#nu}_{#mu} Low Enu", 
        "bin 106-110 FHC ND280 #bar{#nu}_{#mu} Low Enu", 
        "bin 111-115 FHC ND280 #bar{#nu}_{#mu} High Enu", 
        "bin 116-120 FHC ND280 #bar{#nu}_{#mu} High Enu", 
        "bin 121-125 RHC ND280 #nu_{#mu} Low Enu", 
        "bin 126-130 RHC ND280 #nu_{#mu} Low Enu", 
        "bin 131-135 RHC ND280 #nu_{#mu} High Enu", 
        "bin 136-140 RHC ND280 #nu_{#mu} High Enu", 
        "bin 141-145 RHC ND280 #bar{#nu}_{#mu} Low Enu", 
        "bin 146-150 RHC ND280 #bar{#nu}_{#mu} Low Enu", 
        "bin 151-155 RHC ND280 #bar{#nu}_{#mu} High Enu", 
        "bin 156-160 RHC ND280 #bar{#nu}_{#mu} High Enu", 
        "bin 161-165 FHC SK #nu_{#mu} Low Enu", 
        "bin 166-170 FHC SK #nu_{#mu} Low Enu", 
        "bin 171-175 FHC SK #nu_{#mu} High Enu", 
        "bin 176-180 FHC SK #nu_{#mu} High Enu", 
        "bin 181-185 FHC SK #bar{#nu}_{#mu} Low Enu", 
        "bin 186-190 FHC SK #bar{#nu}_{#mu} Low Enu", 
        "bin 191-195 FHC SK #bar{#nu}_{#mu} High Enu", 
        "bin 196-200 FHC SK #bar{#nu}_{#mu} High Enu", 
        "bin 201-205 RHC SK #nu_{#mu} Low Enu", 
        "bin 206-210 RHC SK #nu_{#mu} Low Enu", 
        "bin 211-215 RHC SK #nu_{#mu} High Enu", 
        "bin 216-220 RHC SK #nu_{#mu} High Enu", 
        "bin 221-225 RHC SK #bar{#nu}_{#mu} Low Enu", 
        "bin 226-230 RHC SK #bar{#nu}_{#mu} Low Enu", 
        "bin 231-235 RHC SK #bar{#nu}_{#mu} High Enu", 
        "bin 236-240 RHC SK #bar{#nu}_{#mu} High Enu", 
]

pot = [0.33, 1.3, 2.3, 3.3, 4.3, 5.3, 6.3, 7.3]
#pot = [0.33, 1.3, 2.3, 3.3]


fit_paths_wagasci = [
    "studies_sampKenj/outputs/wagasci_studies/higher_stats/pot0.33.root",
    "studies_sampKenj/outputs/wagasci_studies/higher_stats/pot1.3.root",
    "studies_sampKenj/outputs/wagasci_studies/higher_stats/pot2.3.root",
    "studies_sampKenj/outputs/wagasci_studies/higher_stats/pot3.3.root",
    "studies_sampKenj/outputs/wagasci_studies/higher_stats/pot4.3.root",
    "studies_sampKenj/outputs/wagasci_studies/higher_stats/pot5.3.root",
    "studies_sampKenj/outputs/wagasci_studies/higher_stats/pot6.3.root",
    "studies_sampKenj/outputs/wagasci_studies/higher_stats/pot7.3.root"
]

fit_paths_fgd2 = [
    "studies_sampKenj/outputs/prelim_jointfit/pot_fhc/FGD2/pot0.33.root",
    "studies_sampKenj/outputs/prelim_jointfit/pot_fhc/FGD2/pot1.3.root",
    "studies_sampKenj/outputs/prelim_jointfit/pot_fhc/FGD2/pot2.3.root",
    "studies_sampKenj/outputs/prelim_jointfit/pot_fhc/FGD2/pot3.3.root",
    "studies_sampKenj/outputs/prelim_jointfit/pot_fhc/FGD2/pot4.3.root",
    "studies_sampKenj/outputs/prelim_jointfit/pot_fhc/FGD2/pot5.3.root",
    "studies_sampKenj/outputs/prelim_jointfit/pot_fhc/FGD2/pot6.3.root",
    "studies_sampKenj/outputs/prelim_jointfit/pot_fhc/FGD2/pot7.3.root"
]

fit_paths_fgd2_wagasci = [
    "studies_sampKenj/outputs/prelim_jointfit/pot_fhc/WAGASCI_FGD2/pot0.33.root",
    "studies_sampKenj/outputs/prelim_jointfit/pot_fhc/WAGASCI_FGD2/pot1.3.root",
    "studies_sampKenj/outputs/prelim_jointfit/pot_fhc/WAGASCI_FGD2/pot2.3.root",
    "studies_sampKenj/outputs/prelim_jointfit/pot_fhc/WAGASCI_FGD2/pot3.3.root",
    "studies_sampKenj/outputs/prelim_jointfit/pot_fhc/WAGASCI_FGD2/pot4.3.root",
    "studies_sampKenj/outputs/prelim_jointfit/pot_fhc/WAGASCI_FGD2/pot5.3.root",
    "studies_sampKenj/outputs/prelim_jointfit/pot_fhc/WAGASCI_FGD2/pot6.3.root",
    "studies_sampKenj/outputs/prelim_jointfit/pot_fhc/WAGASCI_FGD2/pot7.3.root"
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


for i in range(len(subsets)):
    print("Processing subset :"+subsets[i])
    plot_flux_errs(subsets[i], dialsset[i], idialsset[i], pot, fit_paths_wagasci)

print("Done")
