# THIS WORKS BUT THE COV MATRIX DOES NOT WORK IN GUNDAM BECAUSE PYTHON'S FLOAT DEFINITION IS DIFFERENT THAN C++ DOUBLE
from ROOT import TFile, TMatrixTSym

enu = [0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 1.2, 1.5, 2.0, 2.5, 3.0, 3.5, 4.0, 5.0, 7.0, 10.0]
NeutrinoCode = [14, -14]
isRHC = [-1, 0, 1, -2, -2]

fileIn = TFile("studies_sampKenj/inputs/parameters/flux/flux_cov_forjointfit.root")
fileOut = TFile("studies_sampKenj/inputs/parameters/flux/flux_cov_forjointfitNoWGRHC.root","RECREATE")

covIn = fileIn.GetKey("total_flux_cov").ReadObj()
covOut = TMatrixTSym(float)(200)

#covIn.Print()
kel = -1
for iel in range(covIn.GetNcols()):
    if iel in range(40,80):
        continue
    else:
        lel = -1
        kel += 1
        lel += 1
        for jel in range(covIn.GetNcols()):
            if jel in range(40,80):
                continue
            else:
                covOut[kel][lel] = covIn[iel][jel]
                #print("Old: ["+str(iel)+", "+str(jel)+"] = "+str(covIn[iel][jel]))
                #print("New: ["+str(kel)+", "+str(lel)+"] = "+str(covOut[kel][lel]))
                #print("Difference: "+str(covIn[iel][jel]-covOut[kel][lel])+"\n")
                lel += 1
fileOut.cd()
covOut.Write("total_flux_cov")

# open file to write binning
file = open("studies_sampKenj/inputs/parameters/flux/jointflux_binningNoWGRHC.txt","w")

# write binning variables on first line of file
file.write("variables: isRHC NeutrinoCode Enu Enu\n")
#print("variables: isRHC NeutrinoCode Enu Enu\n")

# iterate over array to write binning
for i in range(len(isRHC)):
    for j in range(len(NeutrinoCode)):
        for k in range(len(enu) - 1):
            line = str(isRHC[i]) + " " + str(NeutrinoCode[j]) + " " + str(enu[k]) + " " + str(enu[k+1]) + "\n" 
            file.write(line) 
            #print(line)

# close output file
file.close
