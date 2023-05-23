#include <fstream>
#include <iostream>
//#include <filesystem>
#include <dirent.h>
#include <stdio.h>

std::vector<std::string> name_spline = {"MAQE","Q2_norm_5","Q2_norm_6","Q2_norm_7","Optical_Potential_O","Optical_Potential_C","2p2h_Norm_C","2p2h_Norm_O","2p2h_shape_C_NN","2p2h_shape_C_np","2p2h_shape_O_NN","2p2h_shape_O_np","PNNN_Shape","RES_Eb_C_numu","RES_Eb_O_numu","ISO_BKG","CA5","MARES","FEFABS","FEFCXH","FEFCX","FEFINEL","FEFQEH","FEFQE","Nucleon_FSI","CC_norm_nu","CC_MultiPi_norm_nu"};
std::vector<int> sampl;
std::vector<int> target;
std::vector<int> reaction;
std::vector<int> bin;
std::vector<double> cs = {-1.0, 1.0};
std::vector<double> pmu = {0., 500., 700., 900., 1100., 1500., 30000.};
std::vector<std::string> word_array = {"sam","tar","reac","bin"};
std::string dir_pmu = "CC0pi_fitting_materials/pmu/splines/";
TFile *f_output = NULL;
TObjArray *grapharray = NULL;
TSpline3 *spline = NULL;

void fillStringArray(std::string n_spline)
{
	// add numbers using spline names for binning
	char substr[word_array.size()];
	int num[word_array.size()];
	for(int n = 0; n < word_array.size(); n++){
		substr[n] = n_spline.at(n_spline.find(word_array[n]) + word_array[n].length());
		num[n] = substr[n] - 48;
	}
		//if(strcmp(&substr[0], "0") == 0) break;
        sampl.push_back(num[0]);
        target.push_back(num[1]);
        reaction.push_back(num[2]);
        bin.push_back(num[3]);
        //std::cout << "Checking string vector contents " << sampl.back() << " " << target.back() << " " << reaction.back() << "\n";

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

void write_binning(std::string param)
{
	std::string path_binning = "xsec_sampKenj/inputs/splines/xsec_" + param + "_binning.txt";

	fstream file;
	file.open(path_binning,ios::out);
	
	std::cout << "Creating binning file " << "\n\n";
	file << "variables: cut_branch target reaction D2True D2True D1True D1True \n";
	for(int i = 0; i < sampl.size(); i++){
		file << sampl[i] << " " << target[i] << " " << reaction[i] << " " << cs[0] << " " << cs[1] << " " << pmu[bin[i]] << " " << pmu[bin[i]+1] << "\n"; 
	}
	
	sampl.clear();
	target.clear();
	reaction.clear();
    bin.clear();
	file.close();
}

void combineSplines()
{
	//f_output = new TFile("xsec_sampKenj/inputs/splines/pmu_splines.root","RECREATE");
	f_output = new TFile("xsec_sampKenj/inputs/splines/pmu_splines_graphs.root","RECREATE");

	// read spline file, put graphs in object array and write them into new root file
	for(int i = 0; i < name_spline.size(); i++) {
		std::string path_spline_pmu = FindPath2Spline(dir_pmu,name_spline[i]);

		std::cout << "Reading files: " << path_spline_pmu << "\n";
		TFile *f_spline = new TFile(path_spline_pmu.c_str());
		grapharray = new TObjArray();
		std::string title_g;
		TKey *key;

		TIter keyList(f_spline->GetListOfKeys());
		// make this into function eventually
		while ((key = (TKey*)keyList())) {
			TGraph *g = (TGraph*)key->ReadObj();
			title_g = g->GetTitle();
			std::cout << "Reading: " << title_g << "\t";
			int n = 0;
			std::cout << " =>Contents of spline : ";
			for(int k = 0; k < g->GetMaxSize(); k++) {
				std::cout << g->GetPointY(k) << "  ";
				if(g->GetPointY(k) == 1) n++;
			}
            std::cout << std::endl;

             //fill tstring array for the binning 
			if(n == g->GetMaxSize()) {
				//std::cout << " => Ignoring\n";
				continue;
			}
			else {
				std::cout << " => Adding\n";
				std::cout << "Mean : " << g->GetMean(2) << " \n";
				// fill tstring array for the binning 
				fillStringArray(title_g);
				grapharray->Add(g);
                //spline = new TSpline3(title_g.c_str(), g);
				//grapharray->Add(spline);
			}
		}

		std::cout << "Writing " << name_spline[i] << " to output file \n";
        write_binning(name_spline[i]);
		f_output->cd();
		f_output->WriteObject(grapharray,name_spline[i].c_str());
	}
	//std::cout << "Checking string vector size " << sampl.size() << " " << target.size() << " " << reaction.size() << "\n";
}

void merge_splines()
{
	combineSplines();

	std::cout << "Done\n";

	//f_output->Close();
}
