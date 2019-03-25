#pragma once

#include<array>
#include <map>
#include <fstream>
#include <vector>
#include "ClassProbability.h"

using std::array;
using std::map;
using std::vector;
using std::string;

class TrainingModel {
private:
	map<int, ClassProbability> prob_map; //stores 10 (0-9) ClassProbability objects, each holds black/white probability arrays
	int num_images; //set in constructor
public:
	TrainingModel(string images_file_name, string labels_file_name);
};