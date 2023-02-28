# define bins
pmu = [
    #FHC WAGASCI PM-WMRD #nu_{#mu] CC 0#pi 
    [0, 450, 500, 550, 600, 650, 700, 750, 800, 900, 1100, 30000],
   #FHC WAGASCI PM-BM #nu_{#mu] CC 0#pi
    [0, 600, 650, 700, 800, 900, 1200, 1400, 1700, 30000],
   #FHC WAGASCI PM #nu_{#mu] CC 1#pi 
    [0, 400, 500, 550, 600, 650, 700, 800, 900, 1400, 1700, 30000],
   #FHC WAGASCI UWG-WMRD #nu_{#mu] CC 0#pi 
    [0, 400, 450, 500, 550, 600, 650, 700, 800, 900, 1100, 30000],
   #FHC WAGASCI UWG-BM #nu_{#mu] CC 0#pi
    [0, 600, 650, 700, 750, 800, 900, 1100, 1400, 1800, 30000],
   #FHC WAGASCI DWG-BM #nu_{#mu] CC 0#pi 
    [0, 400, 450, 500, 550, 600, 650, 700, 800, 900, 1100, 1400, 30000],
   #FHC WAGASCI WG #nu_{#mu] CC 1#pi
    [0, 400, 500, 550, 600, 650, 700, 750, 800, 900, 1100, 1400, 1700, 30000],
    ]

cos  = [ 
       #FHC WAGASCI PM-WMRD #nu_{#mu] CC 0#pi 
    [0, 0.425, 0.525, 0.65, 0.75, 0.9, 1], 
       #FHC WAGASCI PM-BM #nu_{#mu] CC 0#pi
    [0, 0.85, 0.9, 0.94, 0.96, 0.98, 1], 
       #FHC WAGASCI PM #nu_{#mu] CC 1#pi 
    [0, 0.5, 0.63, 0.72, 0.87, 0.98, 1], 
       #FHC WAGASCI UWG-WMRD #nu_{#mu] CC 0#pi 
    [0, 0.5, 0.64, 0.7, 0.85, 1],
       #FHC WAGASCI UWG-BM #nu_{#mu] CC 0#pi
    [0, 0.9, 0.94, 0.96, 0.98, 1],
       #FHC WAGASCI DWG-BM #nu_{#mu] CC 0#pi 
    [0, 0.75, 0.85, 0.9, 0.94, 0.96, 0.98, 1],
       #FHC WAGASCI WG #nu_{#mu] CC 1#pi
    [0, 0.67, 0.77, 0.84, 0.9, 0.95, 0.98, 1] ]

# sample name array
samples = ["WAGASCI_PM-WMRD_CC-0pi", "WAGASCI_PM-BM_CC-0pi",  "WAGASCI_PM_CC-1pi","WAGASCI_UWG-WMRD_CC-0pi", "WAGASCI_UWG-BM_CC-0pi", "WAGASCI_DWG-BM_CC-0pi", "WAGASCI_WG_CC-1pi"]

for samp in range(len(samples)):
    # open output file 
    file = open("studies_sampKenj/inputs/samples/binning/"+ samples[samp] +".txt","w")

    # write binning variables on first line of file
    #file.write("variables: CosThetamu CosThetamu Pmu Pmu\n")
    file.write("variables: Pmu Pmu CosThetamu CosThetamu\n")

    # iterate over array to write binning
    for i in range(len(pmu[samp]) - 1):
        #for j in range(len(pmu[samp][i]) - 1):
        for j in range(len(cos[samp]) - 1):
        #for j in range(len(pmu) - 1):
            #line = str(cos[samp][i]) + " " + str(cos[samp][i+1]) + " " + str(pmu[samp][i][j]) + " " + str(pmu[samp][i][j+1]) + "\n" 
            line = str(pmu[samp][i]) + " " + str(pmu[samp][i+1]) + " " + str(cos[samp][j]) + " " + str(cos[samp][j+1]) + "\n" 
            #line = str(cos[samp][i]) + " " + str(cos[samp][i+1]) + " " + str(pmu[j]) + " " + str(pmu[j+1]) + "\n" 
            file.write(line) 

    # close output file 
    file.close
