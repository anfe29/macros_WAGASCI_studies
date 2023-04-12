from ROOT import TFile, TH1, TGraph
import sys

# Check number of arguments
if (len(sys.argv) != 2):
    print("Usage: python compare_gundam_andrew.py \\")
    print("\t xsLLhFitterpostfitFile \\")
    print("\t gundamPostfitFile \\")
    print("\t outputfolder")
else:
    print("Processing xsLLhFitter and GUNDAM files")
