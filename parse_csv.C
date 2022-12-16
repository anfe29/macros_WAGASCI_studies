void parse_csv()
{
	// read parameters from csv file and put it into a matrix 
	std::ifstream file("files_kenji/WAGASCI-BabyMIND_cc0pi_analysis_CorrMatrix.csv");

	if (!file) {
		std::cerr << "not working";
		return 1;
	}

	std::vector<std::string> coor;
	std::string line, word, tmp;
    int i = 1;
    while(getline(file, line)) {
        coor.clear();
        //std::cout << "Line to parse:\n" << line << "\n";
        std::stringstream s(line);
        while(std::getline(s, word,',')) {
                //std::string substr = tmp.substr(0, tmp.find_first_of(",",j));
                //double num = std::stod(substr);
                coor.push_back(word);
        }
        for(int j = 1; j < coor.size(); j++) {
            //std::cout << "Reading column " << j << ":" << coor[i] << "\n";
            //std::cout << "Reading coordinate (" << i << "," << j << ") : " << coor[j] << "\n";
            if(i != 48 and j == 48) break;
            if(coor[j] != "" || i==j) std::cout << "Reading coordinate (" << i << "," << j << ") : " << coor[j] << "\n";
        }
    i++;
    }
    file.close();
}
