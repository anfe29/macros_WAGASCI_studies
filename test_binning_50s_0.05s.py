# define bins
pmu = [0, 400, 450, 500, 550, 600, 650, 700, 750, 800, 850, 900, 950, 1000, 1500, 15000] # 50s

cos  = [-1, 0.20, 0.25, 0.30, 0.35, 0.40, 0.45, 0.55, 0.60, 0.65, 0.70, 0.75, 0.80, 0.85, 0.9, 0.95, 1] # 0.05

# sample name array
samples = ["WAGASCI_PM-WMRD_CC-0pi", "WAGASCI_PM-BM_CC-0pi",  "WAGASCI_PM_CC-1pi","WAGASCI_UWG-WMRD_CC-0pi", "WAGASCI_UWG-BM_CC-0pi", "WAGASCI_DWG-BM_CC-0pi", "WAGASCI_WG_CC-1pi"]

for samp in range(len(samples)):
    # open output file 
    file = open("studies_sampKenj/inputs/samples/binning/"+ samples[samp] +".txt","w")
    #print("studies_sampKenj/inputs/samples/binning/"+ samples[samp] +".txt")

    # write binning variables on first line of file
    file.write("variables: CosThetamu CosThetamu Pmu Pmu\n")

    # iterate over array to write binning
    for i in range(len(cos) - 1):
        for j in range(len(pmu) - 1):
            line = str(cos[i]) + " " + str(cos[i+1]) + " " + str(pmu[j]) + " " + str(pmu[j+1]) + "\n" 
            file.write(line) 

    # close output file 
    file.close
