from ROOT import TFile 
import numpy as np


# # Estimate the new covariance

def correlation_from_covariance(covariance):
    v = np.sqrt(np.diag(covariance))
    outer_v = np.outer(v, v)
    correlation = covariance / outer_v
    correlation[covariance == 0] = 0
    return correlation
#                         C p      C s    C SRC    O p12    O p32      O s    O SRC
nom_cov = np.array([[0.20**2,      0.,      0.,      0.,      0.,      0.,      0.],
                    [     0., 0.45**2,      0.,      0.,      0.,      0.,      0.],
                    [     0.,      0., 2.00**2,      0.,      0.,      0.,      0.],
                    [     0.,      0.,      0., 0.25**2,      0.,      0.,      0.],
                    [     0.,      0.,      0.,      0., 0.45**2,      0.,      0.],
                    [     0.,      0.,      0.,      0.,      0., 0.75**2,      0.],
                    [     0.,      0.,      0.,      0.,      0.,      0., 2.00**2]])

'''
nom_corr_pb = np.array([[1.00, 0.80, 0.00, 0.00],
                        [0.80, 1.00, 0.00, 0.00],
                        [0.00, 0.00, 1.00, 0.80],
                        [0.00, 0.00, 0.80, 1.00],
                       ])

var_pb = np.array([1.00, 1.00, 1.00, 1.00])
'''

# print(nom_cov_pb)

Ntoys = 5000000
# approx 20% correlations
precision = 1.97
# approx 30% correlations
#precision = 1.73
# approx 40% correlations
#precision = 1.54
# approx 50% correlations
#precision = 1.40
# approx 60% correlations
#precision = 1.26
# approx 95% correlations
#precision = 0.5

toys = np.random.multivariate_normal(np.zeros(7), nom_cov, size=Ntoys)
remaining_toys = []

for i in range(Ntoys):
    if (i%1000000 == 0): print("Throw ", i, ":")
    #if (i%100000 == 0): print(toys[i])

    if (np.abs(toys[i][0]/nom_cov[0, 0]**.5 - toys[i][3]/nom_cov[3, 3]**.5) > precision*np.abs(toys[i][0]/nom_cov[0, 0]**.5) or
        np.abs(toys[i][0]/nom_cov[0, 0]**.5 - toys[i][4]/nom_cov[4, 4]**.5) > precision*np.abs(toys[i][0]/nom_cov[0, 0]**.5) or
        np.abs(toys[i][1]/nom_cov[1, 1]**.5 - toys[i][5]/nom_cov[5, 5]**.5) > precision*np.abs(toys[i][1]/nom_cov[1, 1]**.5) or
        np.abs(toys[i][2]/nom_cov[2, 2]**.5 - toys[i][6]/nom_cov[6, 6]**.5) > precision*np.abs(toys[i][2]/nom_cov[2, 2]**.5)):
        continue
    
    remaining_toys.append(toys[i])
    
print(len(remaining_toys))
#print(remaining_toys)

covv = np.cov(np.array(remaining_toys).T)
corr = correlation_from_covariance(covv)
for i in range(len(corr)):
    for j in range(len(corr)):
        print("{c:.2f}".format(c=corr[i,j]), end=" , ")
    print()

'''
covv = np.cov(np.array(remaining_toys).T)
corr = correlation_from_covariance(covv)
for i in range(len(nom_corr_pb)):
    for j in range(len(nom_corr_pb)):
        print("{c:.2f}".format(c=corr[i,j]), end=" , ")
    print()
'''


#print(np.linalg.eigvals(corr))


# # Put in the covariance


file = TFile("studies_sampKenj/inputs/parameters/xsec/xsec_covariance_banff_2021a_v13_noFlux_050122_Mirror2p2hShape_MirrorRESEb_splineRS_COcorr30.root", "UPDATE")

xsec_cov = file.Get("xsec_cov")
#xsec_cov = file.GetKey("xsec_cov").ReadObj()
names = file.Get("xsec_param_names")

# check index of params we want to change
'''
for i in range(xsec_cov.GetNrows()):
    print(i, "  -  ", names[i].GetName())

'''

# change xsec cov matrix with new correlations
indices = [11, 12, 13, 16, 17, 18, 19]
for i in range(len(indices)):
    for j in range(len(indices)):
        xsec_cov[indices[i]][indices[j]] = covv[i, j]

#xsec_cov.Print()
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


for i in range(len(corr)):
    for j in range(len(corr)):
        print("{c:.2f}".format(c=new_cov[i,j]), end=" , ")
    print()


for i in range(names.GetEntries()):
    print(str(i) + "  " + names[i].GetName())

'''
