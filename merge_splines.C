#include <fstream>
#include <iostream>
//#include <filesystem>
#include <dirent.h>
#include <stdio.h>

std::vector<std::string> name_spline;
std::vector<int> sampl;
std::vector<int> target;
std::vector<int> reaction;
//std::vector<double> pmu = {0., 500., 700., 900., 1100., 1500., 30000.};
std::vector<double> cs = {0.34, 1.0};
std::vector<double> pmu = {0., 500., 700., 900., 1100., 1500., 5000.};
std::vector<std::string> word_array = {"sam","tar","reac"};
std::string dir_pm = "files_kenji/pm/pm/pmu/";
std::string dir_wg = "files_kenji/wg/wg/pmu/";
TFile *f_output = NULL;
TObjArray *grapharray = NULL;

bool isRootfile(std::string a)
{
	// returns true if root file
	int found = a.find(".root");
	if(found != std::string::npos) return true;
	else return false;
}

void fillStringArray(std::string n_spline)
{
	// add numbers using spline names for binning
	char substr[word_array.size()];
	int num[word_array.size()];
	for(int n = 0; n < word_array.size(); n++){
		substr[n] = n_spline.at(n_spline.find(word_array[n]) + word_array[n].length());
		num[n] = substr[n] - 48;
	}
		// ignore sample 0, not relevant
		//if(strcmp(&substr[0], "0") == 0) break;
		if(num[0] != 0) {
			sampl.push_back(num[0]);
			target.push_back(num[1]);
			reaction.push_back(num[2]);
		}

	//std::cout << "Checking string vector contents " << sampl.back() << " " << target.back() << " " << reaction.back() << "\n";
}

void fillSplineNames()
{
	// read parameter names from csv file and put it into a string objarray
	std::ifstream file("files_kenji/WAGASCI-BabyMIND_cc0pi_analysis_CorrMatrix.csv");

	if (!file) {
		std::cerr << "not working";
		return 1;
	}

	std::vector<TObjString*> name;
	std::string tmp;
	while (std::getline(file, tmp)) {
		name_spline.push_back(tmp.substr(0, tmp.find_first_of(",")));
		//std::cout << "Name params: " << name_spline.back() << "\n";
	}
	file.close();
}

std::string FindPath2Spline(std::string path, std::string name)
{
    //std::cout << "DEBUG: PATH IS " << path.c_str() << "\n";
    DIR* dir = opendir(path.c_str());
    
    if(dir == NULL) return "OPENDIR FAILED";

    std::cout << "Directory contents: \n";
    struct dirent* entry;
    while ((entry = readdir(dir)) != NULL) {
        std::string path_str = entry->d_name;
		if(path_str.find(name) != std::string::npos) return path+path_str;	
    }

    // Close the directory
    closedir(dir);
    return "NO MATCH";
}

bool Ignore(std::string title, bool isWG)
{
	std::string sample = title.substr(title.find("sam"), 4);

	if(isWG) {
		if(strcmp(sample.c_str(),"sam0") == 0 || strcmp(sample.c_str(),"sam1") == 0 ||strcmp(sample.c_str(),"sam2") == 0 || strcmp(sample.c_str(),"sam3") == 0) return true;
		else return false;
	}
	else {
		if(strcmp(sample.c_str(),"sam0") == 0 || strcmp(sample.c_str(),"sam4") == 0 ||strcmp(sample.c_str(),"sam5") == 0 || strcmp(sample.c_str(),"sam6") == 0 || strcmp(sample.c_str(),"sam7") == 0 || strcmp(sample.c_str(),"sam8") == 0) return true;
		else return false;
	}
}

void write_binning(std::string param)
{
	std::string path_binning = "studies_sampKenj/inputs/parameters/xsec/xsec_" + param + "_binning.txt";

	fstream file;
	//file.open("inputs/parameters/xsec/xsec_binning.txt");
	file.open(path_binning,ios::out);
	
	std::cout << "Creating binning file: " << path_binning << "\n\n";
	//file << "variables: sample target reaction_kenji TruePmu TruePmu \n";
	file << "variables: sample target reaction_kenji TruePmu TruePmu \n";
	int j = 0;
	for(int i = 0; i < sampl.size(); i++){
		file << sampl[i] << " " << target[i] << " " << reaction[i] << " ";
		if(j < (pmu.size() - 1)) {
			file << pmu[j] << " " << pmu[j+1] << "\n"; 
		}
		else {
			j = 0;
			file << pmu[j] << " " << pmu[j+1] << "\n"; 
		}
		j++;
	}
	
	sampl.clear();
	target.clear();
	reaction.clear();
	file.close();
}

void combineSplines()
{
	f_output = new TFile("studies_sampKenj/inputs/splines/pmu_splines.root","RECREATE");

	// read spline file, put graphs in object array and write them into new root file
	for(int i = 0; i < name_spline.size(); i++) {
		std::string path_spline_wg = FindPath2Spline(dir_wg,name_spline[i]);
		std::string path_spline_pm = FindPath2Spline(dir_pm,name_spline[i]);

		std::cout << "Reading files: " << path_spline_wg << "\n" << path_spline_pm << "\n";
		TFile *f1_spline = new TFile(path_spline_pm.c_str());
		TFile *f2_spline = new TFile(path_spline_wg.c_str());
		grapharray = new TObjArray();
		std::string title_g;
		TKey *key;

		std::cout << "Adding PM samples to ObjArray \n";
		TIter keyList1(f1_spline->GetListOfKeys());
		// make this into function eventually
		while ((key = (TKey*)keyList1())) {
			TGraph *g = (TGraph*)key->ReadObj();
			title_g = g->GetTitle();
			//std::cout << "Reading: " << title_g << ",";
			int n = 0;
			//std::cout << " =>Contents of spline : ";
			for(int k = 0; k < g->GetMaxSize(); k++) {
				//std::cout << "  " << g->GetPointY(k);
				if(g->GetPointY(k) == 1) n++;
			}

			// true for WAGASCI samples
			if((Ignore(title_g, false)) || (n == g->GetMaxSize())) {
				//std::cout << " => Ignoring\n";
				continue;
			}
			else {
				//std::cout << " => Adding\n";
				//std::cout << "Mean : " << g->GetMean(2) << " \n";
				// fill tstring array for the binning 
				fillStringArray(title_g);
				grapharray->Add(g);
			}
		}
		std::cout << "Adding WAGASCI samples to ObjArray \n";
		TIter keyList2(f2_spline->GetListOfKeys());
		while ((key = (TKey*)keyList2())) {
			TGraph *g = (TGraph*)key->ReadObj();
			title_g = g->GetTitle();
			//std::cout << "Reading: " << title_g << ",";
			int n = 0;
			//std::cout << " => Contents of spline : ";
			for(int k = 0; k < g->GetMaxSize(); k++) {
				//std::cout << "  " << g->GetPointY(k);
				if(g->GetPointY(k) == 1) n++;
			}

			if((Ignore(title_g, true)) || (n == g->GetMaxSize())) {
				//std::cout << " => Ignoring\n";
				continue;
			}
			else {
				//std::cout << " => Adding\n";
				//std::cout << "Mean : " << g->GetMean(2) << " \n";
				// fill tstring array for the binning 
				fillStringArray(title_g);
				grapharray->Add(g);
			}
		}

		std::cout << "Writing " << name_spline[i] << " to output file \n";
		f_output->cd();
		f_output->WriteObject(grapharray,name_spline[i].c_str());
		write_binning(name_spline[i]);
	}
	//std::cout << "Checking string vector size " << sampl.size() << " " << target.size() << " " << reaction.size() << "\n";
}

void merge_splines()
{
	fillSplineNames();
	combineSplines();

	std::cout << "Done\n";

	//f_output->Close();
}
