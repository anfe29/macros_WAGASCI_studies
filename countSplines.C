void countSplines()
{
	TFile f("studies_sampKenj/inputs/splines/pmu_splines.root");
	TKey *key;

	TIter keyList(f.GetListOfKeys());
	while ((key = (TKey*)keyList())) {
		TObjArray *a = (TObjArray*)key->ReadObj();
		std::cout << "Number of splines in " << key->GetName() << " : " << a->GetEntries() << "\n";
	}
}
