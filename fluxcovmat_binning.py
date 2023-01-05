from ROOT import TFile, TMatrixTSym

fileIn = TFile("studies_sampKenj/inputs/parameters/flux/flux_cov_forjointfit.root")
fileOut = TFile("studies_sampKenj/inputs/parameters/flux/flux_cov_forjointfitUPDATED","RECREATE")

covIn = fileIn.GetKey("total_flux_cov").ReadObj()
#covIn.Print()
#covOut = covIn.GetSub(40,239,40,239)
#covOut.Print()
