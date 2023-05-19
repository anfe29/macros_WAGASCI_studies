from ROOT import *
import sys

# could be any spline file, they all have the same format
path = "CC0pi_fitting_materials/pmu/splines/splines_pmu_MAQE.root"
infile = TFile(path)

key = TKey()
keyList = TIter(infile.GetListOfKeys())

file = open("spline_index.txt","w")
file.write("Spline index\t Spline name\n")

i = 0
for key in keyList:

    gr = key.ReadObj()
    line = str(i)+"\t"+gr.GetName()+"\n"
    file.write(line)
    #print(str(i)+"\t"+gr.GetName())
    i += 1

file.close()
