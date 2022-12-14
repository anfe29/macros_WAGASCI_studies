#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

// this file does not exist anymore locally anymore, careful when re running this macro
const std::string fluxRootFilePath = "pmu_binning/cov_matrix/flux/flux_covariance_wagasci_2021_total_bv21v2_20_20_bins.root";

void generateBinningFlux(){

  auto* f = TFile::Open(fluxRootFilePath.c_str());
  std::stringstream ss;
  ss << "variables: isRHC NeutrinoCode Enu Enu" << "\n";
  //file << "variables: isRHC NeutrinoCode Enu Enu" << "\n";

  TKey* key;
  TClass* classPtr;
  TAxis* axis;
  for( int iKey = 0 ; iKey < f->GetListOfKeys()->GetSize() ; iKey++ ){
    key = (TKey*) f->GetListOfKeys()->At(iKey);
    classPtr = gROOT->GetClass(key->GetClassName());
    if( not classPtr->InheritsFrom("TAxis") ) continue;
    axis = f->Get<TAxis>(f->GetListOfKeys()->At(iKey)->GetName());
    std::cout << f->GetListOfKeys()->At(iKey)->GetName() << std::endl;

    // extract information from axis title
    std::string name_axis = f->GetListOfKeys()->At(iKey)->GetName();
    std::vector<std::string> splitStr;
    std::string delimiter = "_";
    while( splitStr.size() < 3) {
	    splitStr.push_back(name_axis.substr(0, name_axis.find(delimiter)));
	    name_axis = name_axis.substr(name_axis.find(delimiter) + 1);
    }

	std::cout << "Checking string vector values: " << splitStr[0] << " " << splitStr[1] << " " << splitStr[2] << " " << splitStr[3] << " \n";



    int isRHC;
    int NeutrinoCode;

    if( splitStr[0] == "sk" ){
      // sk parameters won't affect nd280 spectra
      isRHC = -2;
      NeutrinoCode = 0;
    }
    else{
      if( splitStr[1] == "numode" ) isRHC = 0;
      if( splitStr[1] == "anumode" ) isRHC = 1;

      if( splitStr[2] == "numu" ) NeutrinoCode = 14;
      if( splitStr[2] == "numub" ) NeutrinoCode = -14;
      if( splitStr[2] == "nue" ) NeutrinoCode = 12;
      if( splitStr[2] == "nueb" ) NeutrinoCode = -12;
    }

    for( int iBin = 1 ; iBin <= axis->GetNbins() ; iBin++ ){
      ss << isRHC << " " << NeutrinoCode << " ";
      //file << isRHC << " " << NeutrinoCode << " ";
      ss << axis->GetBinLowEdge(iBin) << " " << axis->GetBinUpEdge(iBin) << "\n";
      //file << axis->GetBinLowEdge(iBin) << " " << axis->GetBinUpEdge(iBin) << "\n";
    }
  }

	std::fstream file;
	file.open("studies_sampKenj/inputs/parameters/flux/flux_binning.txt");
  	std::cout << ss.str() << "\n";
	file << ss.str();
	file.close();

}
