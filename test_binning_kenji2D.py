# define bins
pmu = [0, 500, 700, 900, 1100, 1500, 30000] # KENJI

cos  = [-1, 0.57, 0.71, 0.77, 0.82, 0.87, 0.91, 0.94, 0.97, 1] # KENJI

# sample name array
samples = ["WAGASCI_PM-WMRD_CC-0pi", "WAGASCI_PM-BM_CC-0pi",  "WAGASCI_PM_CC-1pi","WAGASCI_UWG-WMRD_CC-0pi", "WAGASCI_UWG-BM_CC-0pi", "WAGASCI_DWG-BM_CC-0pi", "WAGASCI_WG_CC-1pi"]

for samp in range(len(samples)):
    # open output file 
    file = open("studies_sampKenj/inputs/samples/binning/"+ samples[samp] +".txt","w")

    # write binning variables on first line of file
    file.write("variables: CosThetamu CosThetamu Pmu Pmu\n")

    # iterate over array to write binning
    #for i in range(len(pmu) - 1):
    for i in range(len(cos) - 1):
        for j in range(len(pmu) - 1):
            line = str(cos[i]) + " " + str(cos[i+1]) + " " + str(pmu[j]) + " " + str(pmu[j+1]) + "\n" 
            file.write(line) 

    # close output file 
    file.close
