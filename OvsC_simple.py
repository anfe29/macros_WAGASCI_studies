#!/usr/bin/env python
# coding: utf-8

# In[1]:


import ROOT
import numpy as np


# # Estimate the new covariance

# In[2]:


def correlation_from_covariance(covariance):
    v = np.sqrt(np.diag(covariance))
    outer_v = np.outer(v, v)
    correlation = covariance / outer_v
    correlation[covariance == 0] = 0
    return correlation


# In[4]:


#                         C p      C s    C SRC    O p12    O p32      O s    O SRC
nom_cov = np.array([[0.20**2,      0.,      0.,      0.,      0.,      0.,      0.],
                    [     0., 0.45**2,      0.,      0.,      0.,      0.,      0.],
                    [     0.,      0., 2.00**2,      0.,      0.,      0.,      0.],
                    [     0.,      0.,      0., 0.20**2,      0.,      0.,      0.],
                    [     0.,      0.,      0.,      0., 0.45**2,      0.,      0.],
                    [     0.,      0.,      0.,      0.,      0., 0.75**2,      0.],
                    [     0.,      0.,      0.,      0.,      0.,      0., 2.00**2]])

nom_corr_pb = np.array([[1.00, 0.80, 0.00, 0.00],
                        [0.80, 1.00, 0.00, 0.00],
                        [0.00, 0.00, 1.00, 0.80],
                        [0.00, 0.00, 0.80, 1.00],
                       ])
var_pb = np.array([1.00, 1.00, 1.00, 1.00])

# print(nom_cov_pb)

Ntoys = 5000000
precision = 0.5


# In[5]:


toys = np.random.multivariate_normal(np.zeros(7), nom_cov, size=Ntoys)
remaining_toys = []

for i in range(Ntoys):
    if (i%1000000 == 0): print("Throw ", i, ":")
#     if (i%100000 == 0): print(toys[i])

    if (np.abs(toys[i][0]/nom_cov[0, 0]**.5 - toys[i][3]/nom_cov[3, 3]**.5) > precision*np.abs(toys[i][0]/nom_cov[0, 0]**.5) or
        np.abs(toys[i][0]/nom_cov[0, 0]**.5 - toys[i][4]/nom_cov[4, 4]**.5) > precision*np.abs(toys[i][0]/nom_cov[0, 0]**.5) or
        np.abs(toys[i][1]/nom_cov[1, 1]**.5 - toys[i][5]/nom_cov[5, 5]**.5) > precision*np.abs(toys[i][1]/nom_cov[1, 1]**.5) or
        np.abs(toys[i][2]/nom_cov[2, 2]**.5 - toys[i][6]/nom_cov[6, 6]**.5) > precision*np.abs(toys[i][2]/nom_cov[2, 2]**.5)):
        continue
    
    remaining_toys.append(toys[i])
    
print(len(remaining_toys))


# In[9]:


covv = np.cov(np.array(remaining_toys).T)
corr = correlation_from_covariance(covv)
for i in range(len(corr)):
    for j in range(len(corr)):
        print("{c:.2f}".format(c=corr[i,j]), end=" , ")
    print()


# In[20]:


covv = np.cov(np.array(remaining_toys).T)
corr = correlation_from_covariance(covv)
for i in range(len(nom_corr_pb)):
    for j in range(len(nom_corr_pb)):
        print("{c:.2f}".format(c=corr[i,j]), end=" , ")
    print()


# In[16]:


np.linalg.eigvals(corr)


# # Put in the covariance

# In[18]:


file = ROOT.TFile("/sps/t2k/jchakran/gundam/inputconfig/OA2022/GundamInputOA2021withSFGD/inputs/parameters/xsec/xsec_covariance_banff_2021a_v13_noFlux_050122_Mirror2p2hShape_MirrorRESEb_splineRS_simpleCOcorr95.root", "UPDATE")

xsec_cov = file.Get("xsec_cov")
names = file.Get("xsec_param_names")

for i in range(xsec_cov.GetNrows()):
    print(i, "  -  ", names[i].GetName())


# In[21]:


indices = [23, 25, 24, 26]
for i in range(len(indices)):
    for j in range(len(indices)):
        xsec_cov[indices[i]][indices[j]] = covv[i, j]

xsec_cov.Write("xsec_cov", 2) # Overwrite


# In[22]:


file.ls()


# In[23]:


file.Close()


# In[10]:


indices = [11, 12, 13, 16, 17, 18, 19]
for i in range(len(indices)):
    for j in range(len(indices)):
        xsec_cov[indices[i]][indices[j]] = new_cov[i, j]

xsec_cov.Write("xsec_cov", 2) # Overwrite


# ## Check 

# In[24]:


file = ROOT.TFile("/sps/t2k/jchakran/gundam/inputconfig/OA2022/GundamInputOA2021withSFGD/inputs/parameters/xsec/xsec_covariance_banff_2021a_v13_noFlux_050122_Mirror2p2hShape_MirrorRESEb_splineRS_simpleCOcorr95.root", "READ")

# file.ls()

xsec_cov = file.Get("xsec_cov")
for i in range(len(indices)):
    for j in range(len(indices)):
        print("{c:.5f}".format(c=xsec_cov[indices[i]][indices[j]]), end=" , ")
    print()

file.Close()


# In[ ]:


for i in range(len(corr)):
    for j in range(len(corr)):
        print("{c:.2f}".format(c=new_cov[i,j]), end=" , ")
    print()


# In[ ]:


for i in range(names.GetEntries()):
    print(str(i) + "  " + names[i].GetName())


# In[ ]:




