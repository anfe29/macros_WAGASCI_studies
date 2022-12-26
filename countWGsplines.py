# import necessary classes
from ROOT import TFile, TKey, TIter, TObjArray

# open file where splines will be read from
f = TFile("studies_sampKenj/inputs/splines/pmu_splines.root")

# define key and iterator
key = TKey()
keyList = TIter(f.GetListOfKeys())

# for every object array print out its name and number of splines
for key in keyList:
    obj = TObjArray(key.ReadObj());
    out = "Number of splines in " + key.GetName() + " : " + str(obj.GetEntries())
    print(out)
