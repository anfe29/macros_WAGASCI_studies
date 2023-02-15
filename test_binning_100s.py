# define bins
pmu = [0 , 400, 500, 600, 700, 800, 900, 1000, 1100, 1200, 15000] # 100s

# sample name array
samples = ["WAGASCI_PM-WMRD_CC-0pi", "WAGASCI_PM-BM_CC-0pi",  "WAGASCI_PM_CC-1pi","WAGASCI_UWG-WMRD_CC-0pi", "WAGASCI_UWG-BM_CC-0pi", "WAGASCI_DWG-BM_CC-0pi", "WAGASCI_WG_CC-1pi"]

for samp in range(len(samples)):
    # open output file 
    file = open("studies_sampKenj/inputs/samples/binning/"+ samples[samp] +".txt","w")

    # write binning variables on first line of file
    file.write("variables: Pmu Pmu\n")

    # iterate over array to write binning
    for i in range(len(pmu) - 1):
        line = str(str(pmu[i]) + " " + str(pmu[i+1]) + "\n")
        file.write(line) 

    # close output file 
    file.close
