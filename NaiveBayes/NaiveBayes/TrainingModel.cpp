#include <fstream>
#include <iomanip>
#include <sstream>
#include <iostream>
#include "TrainingModel.h"
#include "ClassProbability.h"



TrainingModel::TrainingModel(string file_name, string labels_file_name) {
	image_labels = GetLabelVector(labels_file_name);
	num_images = image_labels.size();
	for (int i = 0; i <= 9; i++) {
		ClassProbability c(i, image_labels.size());
		prob_map[i] = c;
	}
}

TrainingModel::TrainingModel(string file_name) {




	ifstream image_file(file_name);
	string line;

	if (!image_file) {
		std::cout << "Invalid file" << std::endl;
	} else {
		int image_num = 0;
		int line_num = 0;
		array<array<double, kImageSize>, kImageSize> arr;
		while (std::getline(image_file, line)) {
			if (line_num == 0) {
				num_images = std::stoi(line);
				for (int i = 0; i <= 9; i++) {
					ClassProbability c(i, num_images);
					prob_map[i] = c;
				}
				
			}
			else if (line_num == 1) {
				image_num = std::stoi(line);
			}
			else if (line_num == 2) {
				prob_map[image_num].set_num_appearances(std::stoi(line));
			}
			else if (line_num == 3 || line_num == 4) {
				std::stringstream stream(line);
				string new_line;
				vector<double> probs;
				
				while (std::getline(stream, new_line, ',')) {
					probs.push_back(std::stod(new_line));
				}
				int j = 0;
				for (int i = 0; i < probs.size(); i++) {
					if (i != 0 && i % 28 == 0) {
						j++;
					}
					arr[j][i % 28] = probs.at(i);					
				}
				if (line_num == 3) {
					prob_map[image_num].set_white_probabilities(arr);
				} else {
					prob_map[image_num].set_black_probabilities(arr);
				}
				
			}
			line_num++;
			if (line_num == 5) {
				line_num = 1;
				//image_num++;
			}
		}
	}
	image_file.close();
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
				prob_map[image_labels.at(image_num)].UpdateMatrix(current_image); //revisit
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
	file << num_images << std::endl;
	for (int i = 0; i < prob_map.size(); i++) {
		file << prob_map[i] << std::endl;
	}
	file.close();
}

array<ClassProbability, 10> TrainingModel::get_prob_map()
{
	return prob_map;
}

int TrainingModel::get_num_images()
{
	return num_images;
}
