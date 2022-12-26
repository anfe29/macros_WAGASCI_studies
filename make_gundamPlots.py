import sys, getopt
from ROOT import TFile, TH1, TGraph, TCanvas

path = "studies_sampKenj/outputs/wagasci_sampKenj.root"
fname = path[25:-5]

infile = TFile(path)
#outfile = TFile("plots/plots_"+fname+".root","recreate")

infile.cd("FitterEngine/postFit/samples/canvas/D1True/reaction/")
infile.ls()
sample = infile.GetKey("sample_n0_TCanvas").ReadObj()
sample.Draw()
#samples.SaveAs(fname+"samples_n0.png")
'''
def getPlots(path):
    # cut out file name out of the input path
    #fname = path[8:-5]
    path = "studies_sampKenj/outputs/wagasci_sampKenj.root"
    fname = path[25:-5]

    infile = TFile(path)
    outfile = TFile("plots/"+fname+".root","recreate")

def parse_args():
    # intiate input variables form commande line
    path = None 

    # store arguments
    argv = sys.argv[1:]
    try:
        opts, args = getopt.getopt(argv, "p:h:", ["path =",""])
    except getopt.GetoptError as err:
        print(err)
        usage()
        sys.exit(2)

    for opt, arg in opts:
        if opt in ['-p', '--path']:
            path = arg
        if opt in ['-h', '--help']:
            print("Macro used to extract plots from output GUNDAM files found in /outputs\n
            Use the argument -p or --path and the path of the file you want to extract plots from.\n
            Plots will be stored in the \plots directory.")

    getPlots(path)

# call function to parse input arguments
parse_args()
'''
