# Adapted from https://github.com/t2k-software/BANFF/blob/OA2020/app/MakeParameterPlotsForComparisonMaCh3.py

from ROOT import *
import sys
import math
from numpy import *
from array import array

gStyle.SetOptStat(0)
gStyle.SetLabelSize(0.055)
gStyle.SetPadBottomMargin(0.3)

gROOT.SetBatch(kTRUE)

# Check number of arguments
if (len(sys.argv) != 4):
    print('Usage: python MakeParameterPlotsForComparisonMaCh3 \\')
    print('\t postfitFileWithAllParameters \\')
    print('\t gundamPostfitFile \\')
    print('\t outputfile.pdf')
else:
    print('Processing BANFF and GUNDAM files')

# Load input files
infile1 = TFile(sys.argv[1]) #BANFF
infile2 = TFile(sys.argv[2]) #GUNDAM

name = infile1.GetName()
name = name[12:-5]


# Get BANFF postfit parameters, covariance, and errors
banff_prefit_params  = infile1.Get('prefit_params')
banff_postfit_params = infile1.Get('postfit_params')
banff_param_list     = infile1.Get('param_list')
banff_postfit_cov    = infile1.Get('postfit_cov')
banff_postfit_err    = TVectorD(banff_postfit_params.GetNrows())

# Get GUNDAM parameters and errors
gundam_postfit_flux    = infile2.Get('FitterEngine/postFit/Hesse/errors/Flux Systematics/values/postFitErrors_TH1D')
gundam_postfit_det     = infile2.Get('FitterEngine/postFit/Hesse/errors/ND280 Detector Systematics/values/postFitErrors_TH1D')
gundam_postfit_xsecbin = infile2.Get('FitterEngine/postFit/Hesse/errors/Cross-Section Systematics (binned splines)/values/postFitErrors_TH1D')
gundam_postfit_xsecfsi = infile2.Get('FitterEngine/postFit/Hesse/errors/Cross-Section FSI Systematics/values/postFitErrors_TH1D')
gundam_postfit_xsec    = infile2.Get('FitterEngine/postFit/Hesse/errors/Cross-Section Systematics/values/postFitErrors_TH1D')
gundam_prefit_flux    = infile2.Get('FitterEngine/postFit/Hesse/errors/Flux Systematics/values/preFitErrors_TH1D')
gundam_prefit_det     = infile2.Get('FitterEngine/postFit/Hesse/errors/ND280 Detector Systematics/values/preFitErrors_TH1D')
gundam_prefit_xsecbin = infile2.Get('FitterEngine/postFit/Hesse/errors/Cross-Section Systematics (binned splines)/values/preFitErrors_TH1D')
gundam_prefit_xsecfsi = infile2.Get('FitterEngine/postFit/Hesse/errors/Cross-Section FSI Systematics/values/preFitErrors_TH1D')
gundam_prefit_xsec    = infile2.Get('FitterEngine/postFit/Hesse/errors/Cross-Section Systematics/values/preFitErrors_TH1D')

NFLUX = gundam_prefit_flux.GetNbinsX()
NOBSNORM = gundam_prefit_det.GetNbinsX()
NXSEC = gundam_prefit_xsec.GetNbinsX()

# Filling the BANFF postfit error vector
for i in range(0, banff_postfit_err.GetNrows()):
    banff_postfit_err[i] = math.sqrt(banff_postfit_cov[i][i])

banff_params_flux    = TVectorD(NFLUX)
banff_params_det     = TVectorD(NOBSNORM)
banff_params_xsec    = TVectorD(NXSEC)
banff_params_xsecbin = TVectorD(4)

banff_err_flux    = TVectorD(NFLUX)
banff_err_det     = TVectorD(NOBSNORM)
banff_err_xsec    = TVectorD(NXSEC)
banff_err_xsecbin = TVectorD(4)

banff_hist_flux    = TH1D(banff_params_flux)
banff_hist_det     = TH1D(banff_params_det)
banff_hist_xsec    = TH1D(banff_params_xsec)
banff_hist_xsecbin = TH1D(banff_params_xsecbin)

gundam_labels_xsec = gundam_prefit_xsec.GetXaxis().GetLabels()

for i in range(0, NFLUX):
    banff_hist_flux.SetBinContent(i+1,banff_postfit_params[i])
    banff_hist_flux.SetBinError(i+1, math.sqrt(banff_postfit_cov[i][i]))

for i in range(0, NOBSNORM):
    banff_hist_det.SetBinContent(i+1, banff_postfit_params[NFLUX+i])
    banff_hist_det.SetBinError(i+1, math.sqrt(banff_postfit_cov[NFLUX+i][NFLUX+i]))

passed = False
for i in range(0, gundam_prefit_xsec.GetNbinsX()):
    if (i < gundam_prefit_xsec.GetNbinsX()-4 and "2p2h_Edep" in str(gundam_labels_xsec[i])): 
        passed = True
        continue
    if (passed): j = i-4
    else: j=i
    print("i = " + str(i) + " ; j = " + str(j) + " ; ")
    banff_hist_xsec.SetBinContent(i+1,banff_postfit_params[j+NFLUX+NOBSNORM])
    banff_hist_xsec.SetBinError(i+1, math.sqrt(banff_postfit_cov[j+NFLUX+NOBSNORM][j+NFLUX+NOBSNORM]))

for i in range(0, 4):
    print("i = " + str(i))
    banff_hist_xsecbin.SetBinContent(i+1, banff_postfit_params[banff_postfit_params.GetNrows()-4+i])
    banff_hist_xsecbin.SetBinError(i+1, math.sqrt(banff_postfit_cov[banff_postfit_params.GetNrows()-4+i][banff_postfit_params.GetNrows()-4+i]))


paramRange = [[0, 0+24], [0+25,0+49], # ND280
              [0+50, 0+74], [0+75, 0+99], # SK
              [0, 4], # FSI 
              [5, NXSEC], # XSEC
              [0, 4] # EB
             ] 

yRange = [[0.8,1.2], [0.8,1.2],
          [0.8,1.2], [0.8,1.2],
          [0.0,2.0], [0.0,2.6], [0.0,2.6]]

binLabels_flux    = []
binLabels_det     = []
binLabels_xsec    = ['' for i in range(0, NXSEC)]
binLabels_xsecbin = ['' for i in range(0, 4)]

for i in range(0, NFLUX):
    binLabels_flux.append('')
    if (i == 0):
        binLabels_flux[i] = 'ND280 FHC #nu_{#mu}'
    elif (i == 11):
        binLabels_flux[i] = 'ND280 FHC #bar{#nu}_{#mu}'
    elif (i == 16):
        binLabels_flux[i] = 'ND280 FHC #nu_{e}'
    elif (i == 23):
        binLabels_flux[i] = 'ND280 FHC #bar{#nu}_{e}'
    elif (i == 25):
        binLabels_flux[i] = 'ND280 RHC #nu_{#mu}'
    elif (i == 30):
        binLabels_flux[i] = 'ND280 RHC #bar{#nu}_{#mu}'
    elif (i == 41):
        binLabels_flux[i] = 'ND280 RHC #nu_{e}'
    elif (i == 43):
        binLabels_flux[i] = 'ND280 RHC #bar{#nu}_{e}'
    elif (i == 50):
        SKFHCNUMU = i
        binLabels_flux[i] = 'SK FHC #nu_{#mu}'
    elif (i == 61):
        binLabels_flux[i] = 'SK FHC #bar{#nu}_{#mu}'
    elif (i == 66):
        binLabels_flux[i] = 'SK FHC #nu_{e}'
    elif (i == 73):
        binLabels_flux[i] = 'SK FHC #bar{#nu}_{e}'
    elif (i == 75):
        binLabels_flux[i] = 'SK RHC #nu_{#mu}'
    elif (i == 80):
        binLabels_flux[i] = 'SK RHC #bar{#nu}_{#mu}'
    elif (i == 91):
        binLabels_flux[i] = 'SK RHC #nu_{e}'
    elif (i == 93):
        binLabels_flux[i] = 'SK RHC #bar{#nu}_{e}'

# print(binLabels_flux)

histoTypes = ['ND280 NuMode Flux', 'ND280 ANuMode Flux',
              'SK NuMode Flux', 'SK ANuMode Flux']

FEFQELOC = 0
binLabels_xsec[FEFQELOC] = "FSI QE Scatter Low E"
binLabels_xsec[FEFQELOC+1] = "FSI QE Scatter High E"
binLabels_xsec[FEFQELOC+2] = "FSI Hadron Prod."
binLabels_xsec[FEFQELOC+3] = "FSI #pi Absorption"
binLabels_xsec[FEFQELOC+4] = "FSI Charge Ex. Low E"

MAQELOC = 5
gundam_prefit_xsec.SetBinContent(5+1, gundam_prefit_xsec.GetBinContent(5+1)+1)
gundam_postfit_xsec.SetBinContent(5+1, gundam_postfit_xsec.GetBinContent(5+1)+1)

binLabels_xsec[MAQELOC] = "M^{A}_{QE}"
binLabels_xsec[MAQELOC+1] = "2p2h Norm #nu"
binLabels_xsec[MAQELOC+2] = "2p2h Norm #bar{#nu}"
binLabels_xsec[MAQELOC+3] = "2p2h Norm C to O"
binLabels_xsec[MAQELOC+4] = "2p2h Shape C"
gundam_prefit_xsec.SetBinContent(MAQELOC+5, gundam_prefit_xsec.GetBinContent(MAQELOC+5)+1)
gundam_postfit_xsec.SetBinContent(MAQELOC+5, gundam_postfit_xsec.GetBinContent(MAQELOC+5)+1)
binLabels_xsec[MAQELOC+5] = "2p2h Shape O"
gundam_prefit_xsec.SetBinContent(MAQELOC+6, gundam_prefit_xsec.GetBinContent(MAQELOC+6)+1)
gundam_postfit_xsec.SetBinContent(MAQELOC+6, gundam_postfit_xsec.GetBinContent(MAQELOC+6)+1)
binLabels_xsec[MAQELOC+6] = "2p2h Edep. low E_{#nu}"
binLabels_xsec[MAQELOC+7] = "2p2h Edep. high E_{#nu}"
binLabels_xsec[MAQELOC+8] = "2p2h Edep. low E_{#bar{#nu}}"
binLabels_xsec[MAQELOC+9] = "2p2h Edep. high E_{#bar{#nu}}"
binLabels_xsec[MAQELOC+10] = "CCQE Q^{2} Mod. 0"
binLabels_xsec[MAQELOC+11] = "CCQE Q^{2} Mod. 1"
binLabels_xsec[MAQELOC+12] = "CCQE Q^{2} Mod. 2"
binLabels_xsec[MAQELOC+13] = "CCQE Q^{2} Mod. 3"
binLabels_xsec[MAQELOC+14] = "CCQE Q^{2} Mod. 4"
binLabels_xsec[MAQELOC+15] = "CCQE Q^{2} Mod. 5"
binLabels_xsec[MAQELOC+16] = "CCQE Q^{2} Mod. 6"
binLabels_xsec[MAQELOC+17] = "CCQE Q^{2} Mod. 7"

CA5LOC = MAQELOC+17+1
binLabels_xsec[CA5LOC] = "C^{A}_{5}"
banff_hist_xsec.SetBinContent(CA5LOC+1, banff_hist_xsec.GetBinContent(CA5LOC+1)-1)
binLabels_xsec[CA5LOC+1] = "M^{A}_{RES}"
banff_hist_xsec.SetBinContent(CA5LOC+2, banff_hist_xsec.GetBinContent(CA5LOC+2)-1)
binLabels_xsec[CA5LOC+2] = "I_{1/2} non-RES Bkg. Low p_{#pi}"
banff_hist_xsec.SetBinContent(CA5LOC+3, banff_hist_xsec.GetBinContent(CA5LOC+3)-1)
binLabels_xsec[CA5LOC+3] = "I_{1/2} non RES Bkg."
banff_hist_xsec.SetBinContent(CA5LOC+4, banff_hist_xsec.GetBinContent(CA5LOC+4)-1)
binLabels_xsec[CA5LOC+4] = "CC Norm #nu"
binLabels_xsec[CA5LOC+5] = "CC Norm #bar{#nu}"
binLabels_xsec[CA5LOC+6] = "#nu_{e}/#nu_{#mu}"
binLabels_xsec[CA5LOC+7] = "#bar{#nu}_{e}/#bar{#nu}_{#mu}"
binLabels_xsec[CA5LOC+8] = "CC Bodek-Yang DIS"
gundam_prefit_xsec.SetBinContent(CA5LOC+9, gundam_prefit_xsec.GetBinContent(CA5LOC+9)+1)
gundam_postfit_xsec.SetBinContent(CA5LOC+9, gundam_postfit_xsec.GetBinContent(CA5LOC+9)+1)
binLabels_xsec[CA5LOC+9] = "CC Bodek-Yang multi-#pi"
gundam_prefit_xsec.SetBinContent(CA5LOC+10, gundam_prefit_xsec.GetBinContent(CA5LOC+10)+1)
gundam_postfit_xsec.SetBinContent(CA5LOC+10, gundam_postfit_xsec.GetBinContent(CA5LOC+10)+1)
binLabels_xsec[CA5LOC+10] = "CC AGKY multi-#pi"
gundam_prefit_xsec.SetBinContent(CA5LOC+11, gundam_prefit_xsec.GetBinContent(CA5LOC+11)+1)
gundam_postfit_xsec.SetBinContent(CA5LOC+11, gundam_postfit_xsec.GetBinContent(CA5LOC+11)+1)
binLabels_xsec[CA5LOC+11] = "CC Misc."
binLabels_xsec[CA5LOC+12] = "CC DIS multi-#pi Norm #nu"
binLabels_xsec[CA5LOC+13] = "CC DIS multi-#pi Norm #bar{#nu}"
binLabels_xsec[CA5LOC+14] = "CC Coh C"
binLabels_xsec[CA5LOC+15] = "CC Coh O"
binLabels_xsec[CA5LOC+16] = "NC Coh"
binLabels_xsec[CA5LOC+17] = "NC 1 #gamma"
binLabels_xsec[CA5LOC+18] = "NC Other Near"
binLabels_xsec[CA5LOC+19] = "NC Other Far"


XSECBINLOC = 0
binLabels_xsecbin[XSECBINLOC] = "E_{b} C #nu"
binLabels_xsecbin[XSECBINLOC+1] = "E_{b} C #bar{#nu}"
binLabels_xsecbin[XSECBINLOC+2] = "E_{b} O #nu"
binLabels_xsecbin[XSECBINLOC+3] = "E_{b} O #bar{#nu}"

gundam_prefit_flux.SetFillStyle(3003)
gundam_prefit_flux.SetFillColor(kBlack)
gundam_prefit_flux.SetMarkerColor(kBlack)
gundam_prefit_flux.SetMarkerStyle(20)
gundam_prefit_flux.SetMarkerSize(1)

gundam_prefit_xsec.SetFillStyle(3003)
gundam_prefit_xsec.SetFillColor(kBlack)
gundam_prefit_xsec.SetMarkerColor(kBlack)
gundam_prefit_xsec.SetMarkerStyle(20)
gundam_prefit_xsec.SetMarkerSize(1)

gundam_prefit_xsecbin.SetFillStyle(3003)
gundam_prefit_xsecbin.SetFillColor(kBlack)
gundam_prefit_xsecbin.SetMarkerColor(kBlack)
gundam_prefit_xsecbin.SetMarkerStyle(20)
gundam_prefit_xsecbin.SetMarkerSize(1)

gundam_prefit_xsecfsi.SetFillStyle(3003)
gundam_prefit_xsecfsi.SetFillColor(kBlack)
gundam_prefit_xsecfsi.SetMarkerColor(kBlack)
gundam_prefit_xsecfsi.SetMarkerStyle(20)
gundam_prefit_xsecfsi.SetMarkerSize(1)

gundam_postfit_flux.SetLineStyle(2)
gundam_postfit_flux.SetLineColor(kRed)
gundam_postfit_flux.SetMarkerColor(kRed)
gundam_postfit_flux.SetMarkerStyle(1)
gundam_postfit_flux.SetMarkerSize(0.5)

gundam_postfit_xsec.SetLineStyle(2)
gundam_postfit_xsec.SetLineColor(kRed)
gundam_postfit_xsec.SetMarkerColor(kRed)
gundam_postfit_xsec.SetMarkerStyle(1)
gundam_postfit_xsec.SetMarkerSize(0.5)

gundam_postfit_xsecbin.SetLineStyle(2)
gundam_postfit_xsecbin.SetLineColor(kRed)
gundam_postfit_xsecbin.SetMarkerColor(kRed)
gundam_postfit_xsecbin.SetMarkerStyle(1)
gundam_postfit_xsecbin.SetMarkerSize(0.5)

gundam_postfit_xsecfsi.SetLineStyle(2)
gundam_postfit_xsecfsi.SetLineColor(kRed)
gundam_postfit_xsecfsi.SetMarkerColor(kRed)
gundam_postfit_xsecfsi.SetMarkerStyle(1)
gundam_postfit_xsecfsi.SetMarkerSize(0.5)

banff_hist_flux.SetMarkerColor(4)
banff_hist_flux.SetMarkerStyle(1)
banff_hist_flux.SetMarkerSize(0.5)
banff_hist_flux.SetLineWidth(2)

banff_hist_xsec.SetMarkerColor(4)
banff_hist_xsec.SetMarkerStyle(1)
banff_hist_xsec.SetMarkerSize(0.0)
banff_hist_xsec.SetLineWidth(2)

banff_hist_xsecbin.SetMarkerColor(4)
banff_hist_xsecbin.SetMarkerStyle(1)
banff_hist_xsecbin.SetMarkerSize(0.5)
banff_hist_xsecbin.SetLineWidth(3)

gStyle.SetEndErrorSize(5)

c1 = TCanvas()
c1.cd()
c1.Print(sys.argv[3] + "[")

for i in range(0, len(histoTypes)):
    for j in range(paramRange[i][0], paramRange[i][1]+1):
        gundam_prefit_flux.GetXaxis().SetBinLabel(j+1, binLabels_flux[j])

for i in range(0, len(histoTypes)):

    stack = THStack("pStack", histoTypes[i])
    stack.Add(gundam_prefit_flux, "E2")
    stack.Add(banff_hist_flux, "E1P")
    stack.Add(gundam_postfit_flux, "E1P")
    
    c1.cd()
    stack.Draw("NOSTACK")

    #Set the range to the desired parameters that want (low end to topend + 1)
    stack.GetXaxis().SetRangeUser(paramRange[i][0], paramRange[i][1] + 1)
    stack.SetMinimum(yRange[i][0])
    stack.SetMaximum(yRange[i][1])

    leg = TLegend(0.68,0.84,0.88,0.98)
    leg.SetFillColor(0)
    leg.AddEntry(gundam_prefit_flux, "prefit", "FEP")
    leg.AddEntry(gundam_postfit_flux, "GUNDAM", "LEP")
    leg.AddEntry(banff_hist_flux, "BANFF", "ELP")
    leg.Draw()

    line = TLine(paramRange[i][0], 1, paramRange[i][1]+1, 1)
    line.SetLineColor(kBlack)
    line.SetLineStyle(2)
    #line.Draw("SAME")

    for j in range(paramRange[i][0], paramRange[i][1]+1):
        stack.GetXaxis().SetBinLabel(j+1, binLabels_flux[j])
    
    stack.GetXaxis().LabelsOption("v")

    c1.Modified()
    c1.Update()
    c1.Print(sys.argv[3])
    c1.Print("BANFF_GUNDAM_"+name+histoTypes[i]+'.png')




"""
binLabels[50] = "0, 400 MeV"
binLabels[51] = "400, 500 Mev"
binLabels[52] = "500, 600 Mev"
binLabels[53] = "600, 700 Mev"
binLabels[54] = "700, 1000 Mev"
binLabels[55] = "1, 1.5 Gev"
binLabels[56] = "1.5, 2 Gev"
binLabels[57] = "2, 3.5 Gev"
binLabels[58] = "3.5, 5 Gev"
binLabels[59] = "5, 7 Gev"
binLabels[60] = "7, 30 Gev"
"""

histoTypes = ["FSI parameters", "CC0#pi parameters", "Q^{2} parameters", "CC1#pi parameters", "Other Parameters"]
paramRange = [[0,0+4], [5,10], [15, 22], [23, 26], [27, 42]]
yRange     = [[-1.2,1.2], [-0.5, 2.7], [0.0, 2.0], [-1.5, 1.5], [-1.0, 3.0]]
#histoTypes = ["test"]
#paramRange = [[0, 42]]
c1.cd()

for i in range(0, len(histoTypes)):
    for j in range(paramRange[i][0], paramRange[i][1]+1):
        if (i==0): gundam_prefit_xsecfsi.GetXaxis().SetBinLabel(j+1, binLabels_xsec[j])
        else: gundam_prefit_xsec.GetXaxis().SetBinLabel(j+1, binLabels_xsec[j])

for i in range(0, len(histoTypes)):

    stack = THStack("pStack", histoTypes[i])
    if (i==0): stack.Add(gundam_prefit_xsecfsi, "E2P")
    else: stack.Add(gundam_prefit_xsec, "E2P")
    stack.Add(banff_hist_xsec, "E1")
    if (i==0): stack.Add(gundam_postfit_xsecfsi, "E1")
    else: stack.Add(gundam_postfit_xsec, "E1")
    
    #gundam_prefit_xsec.SetMarkerSize(0.5)

    c1.cd()
    stack.Draw("NOSTACK 0")

    #Set the range to the desired parameters that want (low end to topend + 1)
    stack.GetXaxis().SetRangeUser(paramRange[i][0], paramRange[i][1] + 1)
    stack.SetMinimum(yRange[i][0])
    stack.SetMaximum(yRange[i][1])

    leg = TLegend(0.73,0.84,0.93,0.98)
    leg.SetFillColor(0)
    leg.AddEntry(gundam_prefit_xsec, "prefit", "FEP")
    leg.AddEntry(gundam_postfit_xsec, "GUNDAM", "LEP")
    leg.AddEntry(banff_hist_xsec, "BANFF", "ELP")
    leg.Draw()

    #for j in range(paramRange[i][0], paramRange[i][1]+1):
    #    stack.GetXaxis().SetBinLabel(j+1, binLabels_flux[j])
    
    stack.GetXaxis().LabelsOption("v")

    c1.Modified()
    c1.Update()
    c1.Print(sys.argv[3])
    c1.Print("BANFF_GUNDAM_"+name+histoTypes[i]+'.png')


histoTypes = ["CCQE E_{b} Parameters"]
paramRange = [[0, 3]]
yRange     = [[-7.0, 12.0]]
for i in range(0, len(histoTypes)):
    for j in range(paramRange[i][0], paramRange[i][1]+1):
        gundam_prefit_xsecbin.GetXaxis().SetBinLabel(j+1, binLabels_xsecbin[j])


shift = 0.05*gundam_prefit_xsecbin.GetBinWidth(1);
#gundam_postfit_xsecbin.GetXaxis().SetLimits(gundam_postfit_xsecbin.GetXaxis().GetXmin()+shift, gundam_postfit_xsecbin.GetXaxis().GetXmax()+shift)
#banff_hist_xsecbin.GetXaxis().SetLimits(banff_hist_xsecbin.GetXaxis().GetXmin()-shift, banff_hist_xsecbin.GetXaxis().GetXmax()-shift)

for i in range(0, len(histoTypes)):

    stack = THStack("pStack", histoTypes[i])
    stack.Add(gundam_prefit_xsecbin, "E2P")
    stack.Add(banff_hist_xsecbin, "E1")
    stack.Add(gundam_postfit_xsecbin, "E1")
    
    #gundam_prefit_xsec.SetMarkerSize(0.5)

    c1.cd()
    stack.Draw("NOSTACK 0")

    #Set the range to the desired parameters that want (low end to topend + 1)
    stack.GetXaxis().SetRangeUser(paramRange[i][0], paramRange[i][1] + 1)
    stack.SetMinimum(yRange[i][0])
    stack.SetMaximum(yRange[i][1])

    leg = TLegend(0.68,0.84,0.88,0.98)
    leg.SetFillColor(0)
    leg.AddEntry(gundam_prefit_xsecbin, "prefit", "FEP")
    leg.AddEntry(gundam_postfit_xsecbin, "GUNDAM", "LEP")
    leg.AddEntry(banff_hist_xsecbin, "BANFF", "ELP")
    leg.Draw()

    #for j in range(paramRange[i][0], paramRange[i][1]+1):
    #    stack.GetXaxis().SetBinLabel(j+1, binLabels_flux[j])
    
    stack.GetXaxis().LabelsOption("v")

    c1.Modified()
    c1.Update()
    c1.Print(sys.argv[3])
    c1.Print("BANFF_GUNDAM_"+name+histoTypes[i]+'.png')

c1.Print(sys.argv[3] + "]")

# print(str(NFLUX) + "   " + str() + "   " + )


