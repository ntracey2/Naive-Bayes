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
using std::ifstream;
using std::ofstream;

class TrainingModel {
private:
	array<ClassProbability, 10> prob_map; //stores 10 (0-9) ClassProbability objects, each holds black/white probability arrays
	int num_images; //set in constructor
	vector<int> image_labels;
public:
	TrainingModel(string images_file_name, string labels_file_name);
	TrainingModel(string file_name);

	void ParseImageFile(string images_file_name);
	void ComputeProbabilities();
	vector<int> GetLabelVector(string file_name);
	void SaveToFile(string file_name);

	array<ClassProbability, 10> get_prob_map();
	int get_num_images();
};