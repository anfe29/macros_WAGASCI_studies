from ROOT import TFile 
import numpy as np

#                         C p      C s    C SRC    O p12    O p32      O s    O SRC
nom_cov = np.array([[0.20**2,      0.,      0.,      0.,      0.,      0.,      0.],
                    [     0., 0.45**2,      0.,      0.,      0.,      0.,      0.],
                    [     0.,      0., 2.00**2,      0.,      0.,      0.,      0.],
                    [     0.,      0.,      0., 0.25**2,      0.,      0.,      0.],
                    [     0.,      0.,      0.,      0., 0.45**2,      0.,      0.],
                    [     0.,      0.,      0.,      0.,      0., 0.75**2,      0.],
                    [     0.,      0.,      0.,      0.,      0.,      0., 2.00**2]])

sigma = [0.20, 0.45, 2.00, 0.25, 0.45, 0.75, 2.00]
corr = 0.3

cov = np.zeros([len(sigma), len(sigma)])

for ientry in range(len(sigma)):
    for jentry in range(len(sigma)):
        # diagonal
        if ientry == jentry:
            cov[ientry][jentry] = sigma[ientry]**2

        # p-shell correlations
        if ientry == 0 and jentry == 3:
            cov[ientry][jentry] = corr*sigma[ientry]*sigma[jentry]
        if ientry == 3 and jentry == 0:
            cov[ientry][jentry] = corr*sigma[ientry]*sigma[jentry]
        if ientry == 0 and jentry == 4:
            cov[ientry][jentry] = corr*sigma[ientry]*sigma[jentry]
        if ientry == 4 and jentry == 0:
            cov[ientry][jentry] = corr*sigma[ientry]*sigma[jentry]

        # s-shell correlations
        if ientry == 1 and jentry == 5:
            cov[ientry][jentry] = corr*sigma[ientry]*sigma[jentry]
        if ientry == 5 and jentry == 1:
            cov[ientry][jentry] = corr*sigma[ientry]*sigma[jentry]

        # SRC correlations
        if ientry == 2 and jentry == 6:
            cov[ientry][jentry] = corr*sigma[ientry]*sigma[jentry]
        if ientry == 6 and jentry == 2:
            cov[ientry][jentry] = corr*sigma[ientry]*sigma[jentry]

print(cov)
# # Put in the covariance

file = TFile("studies_sampKenj/inputs/parameters/xsec/xsec_covariance_banff_2021a_v13_noFlux_050122_Mirror2p2hShape_MirrorRESEb_splineRS_COcorr30.root", "UPDATE")

xsec_cov = file.Get("xsec_cov")
#xsec_cov = file.GetKey("xsec_cov").ReadObj()
#names = file.Get("xsec_param_names")

# check index of params we want to change
'''
for i in range(xsec_cov.GetNrows()):
    print(i, "  -  ", names[i].GetName())

'''

# change xsec cov matrix with new correlations
indices = [11, 12, 13, 16, 17, 18, 19]
for i in range(len(indices)):
    for j in range(len(indices)):
        xsec_cov[indices[i]][indices[j]] = cov[i, j]

xsec_cov.Print()
xsec_cov.Write("xsec_cov", 2) # Overwrite
file.Close()


'''
# ## Check 
file = TFile("studies_sampKenj/inputs/parameters/xsec/xsec_covariance_banff_2021a_v13_noFlux_050122_Mirror2p2hShape_MirrorRESEb_splineRS_COcorr30.root", "UPDATE")

# file.ls()

xsec_cov = file.Get("xsec_cov")
for i in range(len(indices)):
    for j in range(len(indices)):
        print("{c:.5f}".format(c=xsec_cov[indices[i]][indices[j]]), end=" , ")
    print()

file.Close()
'''


'''
for i in range(len(corr)):
    for j in range(len(corr)):
        print("{c:.2f}".format(c=new_cov[i,j]), end=" , ")
    print()


for i in range(names.GetEntries()):
    print(str(i) + "  " + names[i].GetName())

'''
