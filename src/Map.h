#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "Player.h"

using namespace std;

class MapLoader {
    public:
		MapLoader();
		MapLoader(MapLoader&);
		MapLoader& operator=(MapLoader& h);

        virtual bool checkValidity(string _inputFileStream);
        virtual Map* readMapFile(string _inputFileStream); //stores all information into map
		virtual vector<string> readMapFileForContinents(string _inputFileStream, vector<string> _continentList); //reads file & return list of continents
		virtual vector<vector<Territory*>> readMapFileForBorders(string _inputFileStream, vector<vector<Territory*>> _bordersList, vector<Territory*> _countryList); //reads file & return list of borders for each country
		virtual vector<Territory*> readMapFileForCountries(string _inputFileStream, vector<Territory*> _countryList); //reads file & return list of countries
		vector<string> getContinentList(); 
		vector<Territory*> getCountryList();
		vector<vector<Territory*>> getBordersList();
		vector<int> getContinentNb();

		friend ostream& operator << (ostream& out, MapLoader& hps);
	
		virtual Map* combineInfos(vector<string> _continentList, vector<Territory*> _countryList, vector<vector<Territory*>> _bordersList); //stores all information into map

    private:
        
};

class Map {
    
};