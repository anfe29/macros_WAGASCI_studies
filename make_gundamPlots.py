import sys,os
from optparse import OptionParser
from ROOT import TFile, TH1, TGraph

parser = OptionParser()
parser.add_option("-p","--path",dest="path",help="Path to file where plots will be extracted from")
parser.add_option("-n",default=-1,type=int,help="N files")
parser.add_option("-t","--mktrees",action="store_true",dest="mktree",default=False,help="Make analysis trees before running analysis") 
# implement option to write output into log file, maybe
# implement option to run all, with glob
(options,args) = parser.parse_args()

directory = []
run = options.run
directory = os.listdir()
path = os.path.abspath(os.getcwd()) + "/"


if options.n == -1:
  nmax = len(directory)
else:
    if options.n < len(directory):
        nmax = options.n
    else:
        nmax = len(directory)

  
count = 0
print("Starting to process "+str(nmax)+" directories")

for i in range(nmax):
  if options.mktree: # might have become obsolete
    os.chdir(path+run+directory[i])
    print("Making analysis tree from run "+directory[i])
    os.system("lar -c pandora_analysis.fcl reco*view*.root > output_analysis.txt")
    os.chdir(path)
  print(str(i+1)+" Adding "+directory[i]+" to chain")
  chain.Add(path+run+directory[i]+"/pandoraAnalysis.root")


print("Begin running analysis.C on chain")
chain.Process("analysis.C")
#chain.Merge("test.root")
print("Finished processing chain")

#os.system("mv analysis.png analysis_"+run[:-1]+".png") 
os.system("mv hist.root hist_"+run[:-1]+".root") 
os.system("mv hist*.root histos/")
#os.system("mv analysis*.log logs/")
#os.system("rm analysis.png hist.root")
