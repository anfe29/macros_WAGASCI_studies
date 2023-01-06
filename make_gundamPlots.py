import sys
from ROOT import TFile, TH1, TH2, TCanvas

# pass path to root file
path = sys.argv[1] 
print(sys.argv[1])
# CAREFUL be sure to run from ../<macros-direcotry>, might implement some fix to this constraint later
fname = path[25:-5]
print(fname)

infile = TFile(path)

# get postfit errors canvas
gun_covmatrix = infile.Get("FitterEngine/postFit/Hesse/Hessian/postfitCovarianceOriginal_TH2D")
gun_fitconst_flux = infile.Get("FitterEngine/postFit/Hesse/errors/Flux Systematics/values/fitConstraints_TCanvas")
gun_fitconst_xsecfsi = infile.Get("FitterEngine/postFit/Hesse/errors/Cross-Section FSI Systematics/values/fitConstraints_TCanvas")
gun_fitconst_xsec = infile.Get("FitterEngine/postFit/Hesse/errors/Cross-Section Systematics/values/fitConstraints_TCanvas")
gun_fitconst_xsecbin = infile.Get("FitterEngine/postFit/Hesse/errors/Cross-Section (binned) Systematics/values/fitConstraints_TCanvas")
gun_fitconst_xsecwg = infile.Get("FitterEngine/postFit/Hesse/errors/Cross-Section (WAGASCI-binned) Systematics/values/fitConstraints_TCanvas")

# save plots as png
gun_covmatrix.SaveAs("plots/cov_matrix/" + fname + "covmatrix.png")
gun_fitconst_flux.SaveAs("plots/fitconst/" + fname + "flux.png")
gun_fitconst_xsecfsi.SaveAs("plots/fitconst/" + fname + "xsecfsi.png")
gun_fitconst_xsec.SaveAs("plots/fitconst/" + fname + "xsec.png")
gun_fitconst_xsecbin.SaveAs("plots/fitconst/" + fname + "xsecbin.png")
gun_fitconst_xsecwg.SaveAs("plots/fitconst/" + fname + "xsecwg.png")
