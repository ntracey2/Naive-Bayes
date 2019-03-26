#include <fstream>
#include <iomanip>
#include <sstream>
#include <iostream>
#include "TrainingModel.h"
#include "ClassProbability.h"



TrainingModel::TrainingModel(string file_name, string labels_file_name) {
	image_labels = GetLabelVector(labels_file_name);

	for (int i = 0; i <= 9; i++) {
		ClassProbability c(i, image_labels.size());
		prob_map.insert(std::pair<int, ClassProbability>(i, c));
	}
}

void TrainingModel::ParseImageFile(string images_file_name) {
	ifstream image_file(images_file_name);
	string line;

	int line_num = 0;
	int image_num = 0;
	array<array<char, kImageSize>, kImageSize> current_image;

	if (!image_file) {
		std::cout << "Invalid file" << std::endl;
	} else {
		while (std::getline(image_file, line)) {
			for (int i = 0; i < line.length(); i++) {
				current_image[line_num][i] = line.at(i);
			}
			if (line_num != 0 && line_num % 27 == 0) {
				line_num = 0;
				prob_map.at(image_labels.at(image_num)).UpdateMatrix(current_image); //revisit
				image_num++;
			} else {
				line_num++;
			}
		}
	}
	image_file.close();
}

void TrainingModel::ComputeProbabilities() {
	for (int i = 0; i < prob_map.size(); i++) {
		prob_map.at(i).ComputeSmoothProbabilities();
		prob_map.at(i).ComputeLogProbabilities();
	}
}

vector<int> TrainingModel::GetLabelVector(string file_name) {
	ifstream label_file(file_name);
	vector<int> labels;
	string line;

	if (!label_file) {
		std::cout << "Invalid file" << std::endl;
	} else {
		while (std::getline(label_file, line)) {
			labels.push_back(std::stoi(line));
		}
	}
	label_file.close();

	return labels;
}

void TrainingModel::SaveToFile(string file_name) {
	ofstream file;
	file.open(file_name);
	for (int i = 0; i < prob_map.size(); i++) {
		file << prob_map.at(i) << std::endl;
	}
	file.close();
}

map<int, ClassProbability> TrainingModel::get_prob_map()
{
	return prob_map;
}
