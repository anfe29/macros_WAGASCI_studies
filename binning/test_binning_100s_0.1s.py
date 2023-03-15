# define bins
pmu = [0 , 400, 500, 600, 700, 800, 900, 1000, 1100, 1200, 15000] # 100s

cos  = [-1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.81, 0.9, 1] # 0.1s

# sample name array
samples = ["WAGASCI_PM-WMRD_CC-0pi", "WAGASCI_PM-BM_CC-0pi",  "WAGASCI_PM_CC-1pi","WAGASCI_UWG-WMRD_CC-0pi", "WAGASCI_UWG-BM_CC-0pi", "WAGASCI_DWG-BM_CC-0pi", "WAGASCI_WG_CC-1pi"]

for samp in range(len(samples)):
    # open output file 
    file = open("studies_sampKenj/inputs/samples/binning/"+ samples[samp] +".txt","w")

    # write binning variables on first line of file
    file.write("variables: CosThetamu CosThetamu Pmu Pmu\n")

    # iterate over array to write binning
    for i in range(len(cos) - 1):
        for j in range(len(pmu) - 1):
            line = str(cos[i]) + " " + str(cos[i+1]) + " " + str(pmu[j]) + " " + str(pmu[j+1]) + "\n" 
            file.write(line) 

    # close output file 
    file.close
