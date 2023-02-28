import numpy as np
import math
from ROOT import *
from array import array

# ### makes canvases of POT error evolution for xsec dials (similar to fluxErrors.py but for xsec) ####

def getRelError(i, idials, year, fit_path, xsectype=""):
    
    '''Returns the relative error of dials[i] for a specified year'''
    #print(fit_path)
    file = TFile(fit_path)
    #print(file)
    if (xsectype == "CCQE_EB"):
        xsec = file.Get('FitterEngine/postFit/Hesse/errors/Cross-Section (binned) Systematics/valuesNorm/postFitErrors_TH1D')
    elif (xsectype == "FSI"):
        xsec = file.Get('FitterEngine/postFit/Hesse/errors/Cross-Section FSI Systematics/valuesNorm/postFitErrors_TH1D')
    else:
        xsec = file.Get('FitterEngine/postFit/Hesse/errors/Cross-Section Systematics/valuesNorm/postFitErrors_TH1D')
        
    err = xsec.GetBinError(idials[i])
    return err

def rel_error_evolution(i, idials, years, fit_paths, xsectype=""):
    '''returns an array of relative xsec errors for a dial i, with length = number of years'''
    err_evol = array('d')
    j = 0
    for y in years:
        err_evol.append(getRelError(i, idials, y, fit_paths[j], xsectype))
        j += 1
    return err_evol

def plot_xsec_errs(subsets, dials, idials, years, mini, maxi, fit_paths_ndup, fit_paths_fgd12, fit_paths_ndup_pmucthmu):
    '''plots the relative & absolute xsec errors of all dials, and saves the plots in two canvases'''
    if (len(idials) <= 4): gStyle.SetPalette(kBlueGreenYellow)
    else: gStyle.SetPalette(kRainBow)
    #gStyle.SetNdivisions(6)
    gStyle.SetLegendBorderSize(0)
    gStyle.SetLegendTextSize(0.05)
    
    c1 = TCanvas("c1", "c1", 600, 1000)
    c1.cd()
    xsectype = ""
    if ("FSI" in subsets): xsectype = "FSI"
    elif ("CCQE_EB" in subsets): xsectype = "CCQE_EB"
    else: xsectype = ""
    
    gPad.SetMargin(0.15, 0.1, 0.08, 0.5)
    relativeUncertainties1 = TMultiGraph()
    relativeUncertainties2 = TMultiGraph()
    relativeUncertainties3 = TMultiGraph()
    ayears = array('d', years)
    for i in range(len(dials)):
        gr_temp = TGraph(len(years), ayears, rel_error_evolution(i, idials, years, fit_paths_ndup, xsectype))
        gr_temp.SetTitle(dials[i])
        gr_temp.SetMarkerStyle(kFullCircle)
        gr_temp.SetLineWidth(2)
        relativeUncertainties1.Add(gr_temp)

        gr_temp2 = TGraph(len(years), ayears, rel_error_evolution(i, idials, years, fit_paths_fgd12, xsectype))
        #gr_temp2.SetTitle(dials[i])
        gr_temp2.SetMarkerStyle(kFullCircle)
        gr_temp2.SetLineWidth(2)
        gr_temp2.SetLineStyle(7)
        relativeUncertainties2.Add(gr_temp2)

        gr_temp3 = TGraph(len(years), ayears, rel_error_evolution(i, idials, years, fit_paths_ndup_pmucthmu, xsectype))
        #gr_temp2.SetTitle(dials[i])
        #gr_temp3.SetMarkerStyle(kFullCircle)
        gr_temp3.SetLineWidth(2)
        gr_temp3.SetLineStyle(3)
        relativeUncertainties3.Add(gr_temp3)

        #relativeUncertainties1.SetTitle("Rel. Xsec Syst. for "+subsets+ ";years;#sigma_{postfit}/#sigma_{prefit}")
    relativeUncertainties1.GetXaxis().SetTitle("x10^{21} POT")
    relativeUncertainties1.GetXaxis().SetTitleOffset(0.6)
    relativeUncertainties1.GetXaxis().SetTitleSize(0.045)
    relativeUncertainties1.GetXaxis().SetLabelSize(0.045)
    relativeUncertainties1.GetXaxis().SetLabelOffset(-0.01)
    relativeUncertainties1.GetYaxis().SetTitle("#sigma_{postfit}/#sigma_{prefit}")
    relativeUncertainties1.GetYaxis().SetTitleSize(0.045)
    relativeUncertainties1.GetYaxis().SetLabelSize(0.04505)
#     relativeUncertainties1.SetMinimum(mini)
#     relativeUncertainties1.SetMaximum(maxi)
    relativeUncertainties1.Draw("LAP PLC PMC")
    gPad.BuildLegend(0.05, 0.52, 0.95, 0.52+(0.99-0.52)*((len(idials))/7.0))
    
    leg = TLegend(0.1, 0.4, 0.9, 0.6)
    line = TH1D("h", "", 1, 0, 1)
    line.SetLineColor(kBlack)
    line.SetLineWidth(2)
    line2 = TH1D("hh", "", 1, 0, 1)
    line2.SetLineColor(kBlack)
    line2.SetLineWidth(2)
    line2.SetLineStyle(7)
    line3 = TH1D("hhh", "", 1, 0, 1)
    line3.SetLineColor(kBlack)
    line3.SetLineWidth(2)
    line3.SetLineStyle(3)
    leg.AddEntry(line2, "FGD1+2", "l")
    leg.AddEntry(line3, "SFGD+FGD1+2 #mu only", "l")
    leg.AddEntry(line, "SFGD+FGD1+2 #mu+N", "l")

    relativeUncertainties2.Draw("LP PLC PMC")
    relativeUncertainties3.Draw("LP PLC PMC")

    c1.Update()     
    c1.SaveAs("5050_corr/{}.pdf".format(subsets))



idialsset = [
        [7, 8, 9, 10, 11], # Nucleon FSI, MAQE, Q2 norm 5, Q2 norm 6, Q2 norm 7,
        [12, 13, 14, 15, 16], # SF Carbon
        [17, 18, 19, 20, 21, 22, 23], # SF Oxygen
        [24, 25, 26, 27, 28, 29], # PB + OP
        [30, 31, 32], # 2p2h norm
        [37, 38, 39, 40, 41], # 2p2h shape
        [42, 43, 45], # CA5, MARES, BGSCL
        [46, 47, 48, 49], # RES Eb
        [50, 51, 52], # RS Delta, SPP pi0 norm
        [53, 54, 62, 65], # CC Coh C+O, CC Misc, NC other near
        [55, 56, 57, 58], # MPi TotXSec, MPi BY Vec, MPi BY Ax, MPi BY shape
        [59, 60, 61], # DIS
        [1, 2, 3, 4], # EB
        [1, 2, 3, 4, 5, 6] # FSI
]

dialsset = [
        ["Nucleon FSI", "M^{A}_{QE}", "CCQE Q^{2} Mod. 5", "CCQE Q^{2} Mod. 6", "CCQE Q^{2} Mod. 7"],
        ["P Shell MF Norm C", "S Shell MF Norm C", "SRC Norm C", "P Shell MF p_{miss} Shape C", "S Shell MF p_{miss} Shape C"], # SF Carbon
        ["P_{1/2} Shell MF Norm O", "P_{3/2} Shell MF Norm O", "S Shell MF Norm O", "SRC Norm O", "P_{1/2} Shell MF p_{miss} Shape O", "P_{3/2} Shell MF p_{miss} Shape O", "S Shell MF p_{miss} Shape O"], # SF Oxygen
        ["Pauli Blocking C #nu", "Pauli Blocking O #nu", "Pauli Blocking C #bar{#nu}", "Pauli Blocking O #bar{#nu}", "Optical Potential C", "Optical Potential O"], # PB + OP
        ["2p2h Norm #nu", "2p2h Norm #bar{#nu}", "2p2h Norm C to O"], # 2p2h norm
        ["PNNN Shape", "2p2h Shape C np", "2p2h Shape C NN", "2p2h Shape O np", "2p2h Shape O NN"], # 2p2h shape
        ["C^{A}_{5}", "M^{A}_{RES}", "I_{1/2} non RES Bkg."], # CA5, MARES, BGSCL
        ["Res. Eb C #nu_{#mu}", "Res. Eb O #nu_{#mu}", "Res. Eb C #bar{#nu}_{#mu}", "Res. Eb O #bar{#nu}_{#mu}"], # RES Eb
        ["RS Delta Decay", "SPP #pi^{0} Norm #nu_{#mu}", "SPP #pi^{0} Norm #bar{#nu}_{#mu}"], # RS Delta, SPP pi0 norm
        ["CC Coh C", "CC Coh O", "CC Misc.", "NC Other Near"], # CC Coh C+O, CC Misc, NC other near
        ["multi-#pi multiplicity total xsec", "multi-#pi Bodek-Yang Vector", "multi-#pi Bodek-Yang Axial", "multi-#pi multiplicity shape"], # MPi TotXSec, MPi BY Vec, MPi BY Ax, MPi BY shape
        ["CC Bodek-Yang DIS", "CC DIS multi-#pi Norm #nu", "CC DIS multi-#pi Norm #bar{#nu}"], # DIS
        ["E_{b} C #nu", "E_{b} C #bar{#nu}", "E_{b} O #nu", "E_{b} O #bar{#nu}"],
        ["FSI QE Scatter Low E", "FSI QE Scatter High E", "FSI Hadron Prod.", "FSI #pi Absorption", "FSI Charge Ex. Low E", "FSI Charge Ex. High E"]
]


subsets = [
        "CCQE", # Nucleon FSI, MAQE, Q2 norm 5, Q2 norm 6, Q2 norm 7,
        "SF_Carbon", # SF Carbon
        "SF_Oxygen", # SF Oxygen
        "PB_OP", # PB + OP
        "2p2h_norm", # 2p2h norm
        "2p2h_shape", # 2p2h shape
        "CCRES", # CA5, MARES, BGSCL
        "CCRES_EB", # RES Eb
        "SPP", # RS Delta, SPP pi0 norm
        "Other", # CC Coh C+O, CC Misc, NC other near
        "MPi", # MPi TotXSec, MPi BY Vec, MPi BY Ax, MPi BY shape
        "DIS", # DIS
        "CCQE_EB", # EB
        "Pi_FSI" # FSI
]
mini = [0.07, 0.00, 0.12, 0.02, 0.00, 0.00, 0.15, 0.12, 0.00, 0.12, 0.02, 0.00, 0.00, 0.15, 0.12]

maxi = [0.96, 0.97, 1.025, 0.43, 0.70, 0.82, 0.66, 0.56, 0.00, 0.12, 0.02, 0.00, 0.00, 0.15, 0.12]
# subsets = ["PBOP"]
# dialsset = [dials4]
# idialsset = [idials4]
#years = [2022, 2023, 2024, 2025, 2026, 2027]
years = [3.82, 4.90, 6.08, 7.40, 9.06, 10.8]


fit_paths_ndup = [
    "/sps/t2k/jchakran/gundam/inputconfig/OA2022/GundamInputOA2021withSFGD/outputs/fit21Nov_5050_COcorr95_noSFGD_2022.root",
    "/sps/t2k/jchakran/gundam/inputconfig/OA2022/GundamInputOA2021withSFGD/outputs/fit21Nov_5050_COcorr95_withSFGD_evisdpt_2023.root",
    "/sps/t2k/jchakran/gundam/inputconfig/OA2022/GundamInputOA2021withSFGD/outputs/fit21Nov_5050_COcorr95_withSFGD_evisdpt_2024.root",
    "/sps/t2k/jchakran/gundam/inputconfig/OA2022/GundamInputOA2021withSFGD/outputs/fit21Nov_5050_COcorr95_withSFGD_evisdpt_2025.root",
    "/sps/t2k/jchakran/gundam/inputconfig/OA2022/GundamInputOA2021withSFGD/outputs/fit21Nov_5050_COcorr95_withSFGD_evisdpt_2026.root",
    "/sps/t2k/jchakran/gundam/inputconfig/OA2022/GundamInputOA2021withSFGD/outputs/fit21Nov_5050_COcorr95_withSFGD_evisdpt_2027.root"
]


fit_paths_fgd12 = [
    "/sps/t2k/jchakran/gundam/inputconfig/OA2022/GundamInputOA2021withSFGD/outputs/fit21Nov_5050_COcorr95_noSFGD_2022.root",
    "/sps/t2k/jchakran/gundam/inputconfig/OA2022/GundamInputOA2021withSFGD/outputs/fit21Nov_5050_COcorr95_noSFGD_2023.root",
    "/sps/t2k/jchakran/gundam/inputconfig/OA2022/GundamInputOA2021withSFGD/outputs/fit21Nov_5050_COcorr95_noSFGD_2024.root",
    "/sps/t2k/jchakran/gundam/inputconfig/OA2022/GundamInputOA2021withSFGD/outputs/fit21Nov_5050_COcorr95_noSFGD_2025.root",
    "/sps/t2k/jchakran/gundam/inputconfig/OA2022/GundamInputOA2021withSFGD/outputs/fit21Nov_5050_COcorr95_noSFGD_2026.root",
    "/sps/t2k/jchakran/gundam/inputconfig/OA2022/GundamInputOA2021withSFGD/outputs/fit21Nov_5050_COcorr95_noSFGD_2027.root"
]


fit_paths_ndup_pmucthmu = [
    "/sps/t2k/jchakran/gundam/inputconfig/OA2022/GundamInputOA2021withSFGD/outputs/fit21Nov_5050_COcorr95_noSFGD_2022.root",
    "/sps/t2k/jchakran/gundam/inputconfig/OA2022/GundamInputOA2021withSFGD/outputs/fit21Nov_5050_COcorr95_withSFGD_evisdpt_2023.root",
    "/sps/t2k/jchakran/gundam/inputconfig/OA2022/GundamInputOA2021withSFGD/outputs/fit21Nov_5050_COcorr95_withSFGD_evisdpt_2024.root",
    "/sps/t2k/jchakran/gundam/inputconfig/OA2022/GundamInputOA2021withSFGD/outputs/fit21Nov_5050_COcorr95_withSFGD_evisdpt_2025.root",
    "/sps/t2k/jchakran/gundam/inputconfig/OA2022/GundamInputOA2021withSFGD/outputs/fit21Nov_5050_COcorr95_withSFGD_evisdpt_2026.root",
    "/sps/t2k/jchakran/gundam/inputconfig/OA2022/GundamInputOA2021withSFGD/outputs/fit21Nov_5050_COcorr95_withSFGD_evisdpt_2027.root"
]
# fit_paths_ndup = [
#     "/sps/t2k/jchakran/gundam/inputconfig/OA2022/GundamInputOA2021withSFGD/outputs/fit10Nov_5050_noSFGD_2022.root",
#     "/sps/t2k/jchakran/gundam/inputconfig/OA2022/GundamInputOA2021withSFGD/outputs/fit10Nov_5050_withSFGD_evisdpt_2023.root",
#     "/sps/t2k/jchakran/gundam/inputconfig/OA2022/GundamInputOA2021withSFGD/outputs/fit10Nov_5050_withSFGD_evisdpt_2024.root",
#     "/sps/t2k/jchakran/gundam/inputconfig/OA2022/GundamInputOA2021withSFGD/outputs/fit10Nov_5050_withSFGD_evisdpt_2025.root",
#     "/sps/t2k/jchakran/gundam/inputconfig/OA2022/GundamInputOA2021withSFGD/outputs/fit10Nov_5050_withSFGD_evisdpt_2026.root",
#     "/sps/t2k/jchakran/gundam/inputconfig/OA2022/GundamInputOA2021withSFGD/outputs/fit10Nov_5050_withSFGD_evisdpt_2027.root"
# ]


# fit_paths_fgd12 = [
#     "/sps/t2k/jchakran/gundam/inputconfig/OA2022/GundamInputOA2021withSFGD/outputs/fit10Nov_5050_noSFGD_2022.root",
#     "/sps/t2k/jchakran/gundam/inputconfig/OA2022/GundamInputOA2021withSFGD/outputs/fit10Nov_5050_noSFGD_2023.root",
#     "/sps/t2k/jchakran/gundam/inputconfig/OA2022/GundamInputOA2021withSFGD/outputs/fit10Nov_5050_noSFGD_2024.root",
#     "/sps/t2k/jchakran/gundam/inputconfig/OA2022/GundamInputOA2021withSFGD/outputs/fit10Nov_5050_noSFGD_2025.root",
#     "/sps/t2k/jchakran/gundam/inputconfig/OA2022/GundamInputOA2021withSFGD/outputs/fit10Nov_5050_noSFGD_2026.root",
#     "/sps/t2k/jchakran/gundam/inputconfig/OA2022/GundamInputOA2021withSFGD/outputs/fit10Nov_5050_noSFGD_2027.root"
# ]


# fit_paths_ndup_pmucthmu = [
#     "/sps/t2k/jchakran/gundam/inputconfig/OA2022/GundamInputOA2021withSFGD/outputs/fit10Nov_5050_noSFGD_2022.root",
#     "/sps/t2k/jchakran/gundam/inputconfig/OA2022/GundamInputOA2021withSFGD/outputs/fit10Nov_5050_withSFGD_pmucthmu_2023.root",
#     "/sps/t2k/jchakran/gundam/inputconfig/OA2022/GundamInputOA2021withSFGD/outputs/fit10Nov_5050_withSFGD_pmucthmu_2024.root",
#     "/sps/t2k/jchakran/gundam/inputconfig/OA2022/GundamInputOA2021withSFGD/outputs/fit10Nov_5050_withSFGD_pmucthmu_2025.root",
#     "/sps/t2k/jchakran/gundam/inputconfig/OA2022/GundamInputOA2021withSFGD/outputs/fit10Nov_5050_withSFGD_pmucthmu_2026.root",
#     "/sps/t2k/jchakran/gundam/inputconfig/OA2022/GundamInputOA2021withSFGD/outputs/fit10Nov_5050_withSFGD_pmucthmu_2027.root"
# ]

# the python macro assumes that 2022-2027 fits are in 'fit_path' and named: 0703_banffsfgd****_datacorrect_2M.root
# if this is no longer the case, change 'fit_path' or the names in getRelError() and getAbsError()

# ### if you want to call only one of the xsec subsets, either change lists above or function call below ####
# ### canvas.Save() names are automatically adjusted for the different subsets ####

gROOT.SetBatch(kFALSE)

print(len(subsets))
print(len(dialsset))
print(len(idialsset))
print(len(years))


for i in range(len(subsets)):
    print(i)
    plot_xsec_errs(subsets[i], dialsset[i], idialsset[i], years, mini[i], maxi[i], fit_paths_ndup, fit_paths_fgd12, fit_paths_ndup_pmucthmu)

print("Done")
