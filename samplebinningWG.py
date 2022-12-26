# define bins
bin1 = [0, 500, 700, 900, 1100, 1500, 30000]
#bin2  =[]

# open output file 
file = open("studies_sampKenj/inputs/samples/binning/WAGASCI.txt","w")


# write binning variables on first line of file
file.write("variables: Pmu Pmu \n")
#print("variables: Pmu Pmu")

# iterate over array to write binning
for i in range(len(bin1) - 1):
    line = str(bin1[i]) + " " + str(bin1[i+1]) + "\n" 
    file.write(line) 
    #print(bin1[i], bin1[i+1],sep=" ")

# close output file
file.close
