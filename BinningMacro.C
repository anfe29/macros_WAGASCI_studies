#include <iostream>
#include <fstream>

using namespace std;

std::vector<double> bins1 = {0., 500., 700., 900., 1100., 1500., 30000.};
//std::vector<double> bins2 = {-1., 0., .4, .6, .8, 1.};
//std::vector<double> bins3 = {0., 1., 2., 3., 4., 5.};
//std::vector<double> bins4 = {0., 20000., 40000., 60000., 80000., 100000.};

void BinningMacro(){

	ofstream file;
	//file.open("studies_sampKenj/inputs/samples/binning/simple_binning.txt");
	file.open("studies_sampKenj/inputs/samples/binning/WAGASCI.txt");
	
	//file << "variables: Pmu Pmu CosThetamu CosThetamu Enu Enu Q2 Q2\n";
	//file << "variables: TruePmu TruePmu \n";
	file << "variables: Pmu Pmu \n";
	for(int i = 0; i < (bins1.size() - 1); i++) {
		//for(int j = 0; j < (bins2.size() - 1); j++) {
		file << bins1[i] << " " << bins1[i+1] << "\n"; 
		//file << bins3[i] << " " << bins3[i+1] << " " << bins4[j] << " " << bins4[j+1] <<" \n";
		//}
	}
	
	file.close();
}
