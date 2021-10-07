#include "Map.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using std::cout;
using std::endl;
using std::vector;
using std::getline;
using std::string;
using std::ifstream;
using std::stringstream;
using std::stoi; //conversion string to integer
using std::distance;

bool MapLoader::checkValidity(string _inputFileStream) {
	cout << "\nChecking validity of map..." << endl;

	string line;
	ifstream ifs(_inputFileStream);

	string currentLine;

	while (getline(ifs, currentLine) && currentLine != "[continents]")
	{
		//While current line isn't equal to [Continents] skip 
	}

	if (currentLine != "[continents]")
	{
		ifs.close();
		ifs.clear();
		cout << "Missing [continents] tag. Exiting program...\n\n";
		exit(0);
	}

	while (getline(ifs, currentLine) && currentLine != "[countries]")
	{
		//While current line isn't equal to [Territories] skip 
	}

	if (currentLine != "[countries]")
	{
		ifs.close();
		ifs.clear();
		cout << "Missing [countries] tag. Exiting program...\n\n";
		exit(0);
	}

	while (getline(ifs, currentLine) && currentLine != "[borders]")
	{
		//While current line isn't equal to [Territories] skip 
	}

	if (currentLine != "[borders]")
	{
		ifs.close();
		ifs.clear();
		cout << "Missing [borders] tag. Exiting program...\n\n";
		exit(0);
	}

	ifs.close();
	ifs.clear();

	cout << "Map is VALID and ready to be parsed." << endl;

	return true;
}

Map* MapLoader::readMapFile(string _inputFileStream) {
    Map* map = new Map();

    //Check validity
	bool isValid = checkValidity(_inputFileStream);
	if (isValid) {
		std::cout << "Map file is valid." << endl;

		//Add continents
		vector<string> continentList = {};
		continentList = readMapFileForContinents(_inputFileStream, continentList);

		//Add countries
		vector<Territory*> countryList = {};
		countryList = readMapFileForCountries(_inputFileStream, countryList);

		//Add borders
		vector<vector<Territory*>> bordersList = {};
		bordersList = readMapFileForBorders(_inputFileStream, bordersList, countryList);

		//Create the map
		if (!continentList.empty() && !countryList.empty() && !bordersList.empty() ) {
			map = combineInfos(continentList, countryList, bordersList);
            return map;
		}
	}
	else {
        //TODO: throw exception?
		cout << "\nMap file is invalid. Cannot create map." << endl;
	}
}

Map* MapLoader::combineInfos(vector<string> _continentList, vector<Territory*> _countryList, vector<vector<Territory*>> _bordersList)
{
	Map* map = new Map();
	int currContinentNb;

	for (int i = 0; i < _countryList.size(); i++)
	{
		map->addTerritory(_countryList[i], _bordersList[i]);
		currContinentNb = continentNb[i] - 1;
		map->registerWithContinent(_continentList[currContinentNb], _countryList[i]);
	}
	cout << "\n";
	cout << "\n";
	return map;
}

vector<string> MapLoader::readMapFileForContinents(string _inputFileStream) {
	cout << "\nREGISTERING CONTINENTS" << endl;
	string line;
	ifstream inputFileStream(_inputFileStream);

    vector<string> continentList;
	string territoryName, continentName;

	if (inputFileStream.is_open()) {

		inputFileStream.clear();
		inputFileStream.seekg(0, inputFileStream.beg);

		while (getline(inputFileStream, line) && line != "[continents]") {
		};

		//first line
		inputFileStream >> continentName;
		string continent = string(continentName);
		continentList.push_back(continent);

		while (getline(inputFileStream, line) && line != "[continents]") {
			inputFileStream >> continentName;

			if (continentName == "[countries]")
			{
				break;
			}
			string continent = string(continentName);
			continentList.push_back(continent);
		}

		inputFileStream.close();
		inputFileStream.clear();

		return continentList;
	}

	cout << "File is not open " << "\n";
}

vector<Territory*> MapLoader::readMapFileForCountries(string _inputFileStream, vector<Territory*> _countryList) {
	cout << "\nREGISTERING COUNTRIES" << endl;
	string line;
	ifstream inputFileStream(_inputFileStream);

	int index, continent, x, y;
	string territoryName;

	if (inputFileStream.is_open()) {

		while (getline(inputFileStream, line) && line != "[countries]") {};

		//first line
		inputFileStream >> index >> territoryName >> continent >> x >> y;
		Territory* country = new Territory(territoryName);
		continentNb.push_back(continent);
		_countryList.push_back(country);

		while (getline(inputFileStream, line) && line != "[countries]") {

			inputFileStream >> index >> territoryName >> continent >> x >> y;
			if (territoryName == "[borders]" || territoryName == _countryList.at(_countryList.size() - 1)->getName())
			{
				break;
			}

			Territory* country = new Territory(territoryName);
			continentNb.push_back(continent);
			_countryList.push_back(country);
		}

		inputFileStream.close();
		inputFileStream.clear();
		cout << "Country list size: " << _countryList.size() << endl;
		return _countryList;
	}

	cout << "File is not open " << "\n";
	exit(0);
}

vector<vector<Territory*>> MapLoader::readMapFileForBorders(string _inputFileStream, vector<vector<Territory*>> _bordersList, vector<Territory*> _countryList) {
	cout << "\nREGISTERING BORDERS" << endl;

	string line;
	ifstream inputFileStream(_inputFileStream);

	vector<Territory*> nList;
	int i_subs;
	string::size_type sz;
	string subs;

	if (inputFileStream.is_open()) {

		inputFileStream.clear();
		inputFileStream.seekg(0, inputFileStream.beg);

		while (getline(inputFileStream, line) && line != "[borders]") {}

		//first number
		inputFileStream >> line;
		i_subs = stoi(line, &sz);
		Territory* current = _countryList[i_subs - 1];
		nList.push_back(current);


		while (getline(inputFileStream, line) && line.find("[borders]") == std::string::npos) {
			nList = {};
			istringstream iss(line);

			do {
				iss >> subs;
				i_subs = stoi(subs, &sz);
				Territory* current = _countryList[i_subs - 1];
				nList.push_back(current);

			} while (iss);

			if (nList.at(nList.size() - 1)->getName() == nList.at(nList.size() - 2)->getName())
			{
				nList.pop_back();
			}

			_bordersList.push_back(nList);
		}

		inputFileStream.close();
		inputFileStream.clear();

		cout << "Borders list size: " << _bordersList.size() << endl;
		return _bordersList;
	}

	cout << "File is not open " << "\n";
	exit(0);
}
