############################ UWG-BM CC-0pi #####################################
# define bins
bin1 = [0, 500, 700, 900, 1100, 1500, 30000]
#bin1 = [0, 500, 600, 700, 750, 800, 1000, 1200, 1500]
bin2  =[-1, 0.57, 0.71, 0.77, 0.82, 0.87, 0.91, 0.94, 0.97, 1]
#bin2  =[0, 0.3, 0.8, 0.85, 0.9, 0.95, 1]

# open output file 
file = open("studies_sampKenj/inputs/samples/binning/WAGASCI_UWG-BM_CC-0pi.txt","w")

# write binning variables on first line of file
file.write("variables: Pmu Pmu CosThetamu CosThetamu\n")
#print("variables: Pmu Pmu")

# iterate over array to write binning
for i in range(len(bin1) - 1):
    for j in range(len(bin2) - 1):
        line = str(bin1[i]) + " " + str(bin1[i+1]) + " " + str(bin2[j]) + " " + str(bin2[j+1]) + "\n" 
        file.write(line) 
    #print(bin1[i], bin1[i+1],sep=" ")

# close output file and clear arrays
file.close
bin1.clear()
bin2.clear()

########################### DWG-BM CC-0pi ######################################
# define bins
bin1 = [0, 500, 700, 900, 1100, 1500, 30000]
#bin1 = [0, 375, 400, 425, 450, 475, 500, 550, 600, 650, 700, 800, 1000, 1200, 1500]
bin2  =[-1, 0.57, 0.71, 0.77, 0.82, 0.87, 0.91, 0.94, 0.97, 1]
#bin2  =[0, 0.5, 0.6, 0.7, 0.75, 0.8, 0.85, 0.9, 0.95, 1]

# open output file 
file = open("studies_sampKenj/inputs/samples/binning/WAGASCI_DWG-BM_CC-0pi.txt","w")

# write binning variables on first line of file
file.write("variables: Pmu Pmu CosThetamu CosThetamu \n")
#print("variables: Pmu Pmu")

# iterate over array to write binning
for i in range(len(bin1) - 1):
    for j in range(len(bin2) - 1):
        line = str(bin1[i]) + " " + str(bin1[i+1]) + " " + str(bin2[j]) + " " + str(bin2[j+1]) + "\n" 
        file.write(line) 
    #print(bin1[i], bin1[i+1],sep=" ")

# close output file and clear arrays
file.close
bin1.clear()
bin2.clear()

########################### UWG-WMRD CC-0pi ###################################
# define bins
bin1 = [0, 500, 700, 900, 1100, 1500, 30000]
#bin1 = [0, 400, 450, 500, 525, 575, 600, 700, 800, 1500]
bin2  =[-1, 0.57, 0.71, 0.77, 0.82, 0.87, 0.91, 0.94, 0.97, 1]
#bin2  =[0, 0.3, 0.5, 0.6, 0.7, 0.8, 1]

# open output file 
file = open("studies_sampKenj/inputs/samples/binning/WAGASCI_UWG-WMRD_CC-0pi.txt","w")

# write binning variables on first line of file
file.write("variables: Pmu Pmu CosThetamu CosThetamu \n")
#print("variables: Pmu Pmu")

# iterate over array to write binning
for i in range(len(bin1) - 1):
    for j in range(len(bin2) - 1):
        line = str(bin1[i]) + " " + str(bin1[i+1]) + " " + str(bin2[j]) + " " + str(bin2[j+1]) + "\n" 
        file.write(line) 
    #print(bin1[i], bin1[i+1],sep=" ")

# close output file and clear arrays
file.close
bin1.clear()
bin2.clear()

########################### PM-BM CC-0pi ######################################
# define bins
bin1 = [0, 500, 700, 900, 1100, 1500, 30000]
#bin1 = [0, 400, 500, 550, 575, 600, 625, 650, 700, 750, 800, 850, 900, 1000, 1200, 1500]
bin2  =[-1, 0.57, 0.71, 0.77, 0.82, 0.87, 0.91, 0.94, 0.97, 1]
#bin2  =[0, 0.8, 0.85, 0.9, 0.925, 0.95, 0.975, 1]

# open output file 
file = open("studies_sampKenj/inputs/samples/binning/WAGASCI_PM-BM_CC-0pi.txt","w")

# write binning variables on first line of file
file.write("variables: Pmu Pmu CosThetamu CosThetamu \n")
#print("variables: Pmu Pmu")

# iterate over array to write binning
for i in range(len(bin1) - 1):
    for j in range(len(bin2) - 1):
        line = str(bin1[i]) + " " + str(bin1[i+1]) + " " + str(bin2[j]) + " " + str(bin2[j+1]) + "\n" 
        file.write(line) 
    #print(bin1[i], bin1[i+1],sep=" ")

# close output file and clear arrays
file.close
bin1.clear()
bin2.clear()

########################### PM-WMRD CC-0pi ####################################
# define bins
bin1 = [0, 500, 700, 900, 1100, 1500, 30000]
#bin1 = [0, 300, 350, 375, 400, 425, 450, 475, 500, 550, 600, 650, 800, 1500]
bin2  =[-1, 0.57, 0.71, 0.77, 0.82, 0.87, 0.91, 0.94, 0.97, 1]
#bin2  =[0, 0.2, 0.3, 0.35, 0.4, 0.45, 0.5, 0.55, 0.6, 0.65, 0.7, 0.8, 1]

# open output file 
file = open("studies_sampKenj/inputs/samples/binning/WAGASCI_PM-WMRD_CC-0pi.txt","w")

# write binning variables on first line of file
file.write("variables: Pmu Pmu CosThetamu CosThetamu \n")
#print("variables: Pmu Pmu")

# iterate over array to write binning
for i in range(len(bin1) - 1):
    for j in range(len(bin2) - 1):
        line = str(bin1[i]) + " " + str(bin1[i+1]) + " " + str(bin2[j]) + " " + str(bin2[j+1]) + "\n" 
        file.write(line) 
    #print(bin1[i], bin1[i+1],sep=" ")

# close output file and clear arrays
file.close
bin1.clear()
bin2.clear()

########################### PM CC-1pi #########################################
# define bins
bin1 = [0, 500, 700, 900, 1100, 1500, 30000]
#bin1 = [0, 350, 400, 475, 450, 475, 500, 525, 550, 600, 650, 700, 800, 1000, 1200, 1500]
bin2  =[-1, 0.57, 0.71, 0.77, 0.82, 0.87, 0.91, 0.94, 0.97, 1]
#bin2  =[0, 0.2, 0.25, 0.3, 0.35, 0.4, 0.45, 0.5, 0.6, 0.7, 0.9, 0.95, 1]

# open output file 
file = open("studies_sampKenj/inputs/samples/binning/WAGASCI_PM_CC-1pi.txt","w")

# write binning variables on first line of file
file.write("variables: Pmu Pmu CosThetamu CosThetamu \n")
#print("variables: Pmu Pmu")

# iterate over array to write binning
for i in range(len(bin1) - 1):
    for j in range(len(bin2) - 1):
        line = str(bin1[i]) + " " + str(bin1[i+1]) + " " + str(bin2[j]) + " " + str(bin2[j+1]) + "\n" 
        file.write(line) 
    #print(bin1[i], bin1[i+1],sep=" ")

# close output file and clear arrays
file.close
bin1.clear()
bin2.clear()

########################### WG CC-1pi #########################################
# define bins
bin1 = [0, 500, 700, 900, 1100, 1500, 30000]
#bin1 = [0, 375, 400, 450, 500, 550, 600, 700, 800, 1200, 1500]
bin2  =[-1, 0.57, 0.71, 0.77, 0.82, 0.87, 0.91, 0.94, 0.97, 1]
#bin2  =[0, 0.4, 0.6, 0.7, 0.8, 0.85, 0.9, 0.95, 1]

# open output file 
file = open("studies_sampKenj/inputs/samples/binning/WAGASCI_WG_CC-1pi.txt","w")

# write binning variables on first line of file
file.write("variables: Pmu Pmu CosThetamu CosThetamu \n")
#print("variables: Pmu Pmu")

# iterate over array to write binning
for i in range(len(bin1) - 1):
    for j in range(len(bin2) - 1):
        line = str(bin1[i]) + " " + str(bin1[i+1]) + " " + str(bin2[j]) + " " + str(bin2[j+1]) + "\n" 
        file.write(line) 
    #print(bin1[i], bin1[i+1],sep=" ")

# close output file and clear arrays
file.close
bin1.clear()
bin2.clear()
