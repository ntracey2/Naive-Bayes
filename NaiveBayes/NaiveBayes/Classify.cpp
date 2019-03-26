#include "Classify.h"

vector<int> predicted_values;
vector<int> actual_values;

void ParseTestImageFile(string file, TrainingModel model)
{
	ifstream image_file(file);
	string line;

	int line_num = 0;

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
				predicted_values.push_back(GetImageClassification(current_image, model));
				std::cout << predicted_values.at(predicted_values.size() - 1);
				//std::cout << GetImageClassification(current_image, model) << std::endl;
				//GetImageClassification(current_image, model);
			}
			else {
				line_num++;
			}
		}
	}
	image_file.close();
}

array<array<double, 10>, 10> GetConfusionMatrix(string test_label_file)
{
	array<array<double, 10>, 10> confusion;

	ifstream file(test_label_file);
	string line;

	while (std::getline(file, line)) {
		actual_values.push_back(std::stoi(line));
	}
	file.close();

	for (int i = 0; i <= 9; i++) {
		for (int j = 0; j <= 9; j++) {
			confusion[i][j] = (double) std::count(predicted_values.begin(), predicted_values.end(), j) 
										   / std::count(actual_values.begin(), actual_values.end(), i);
		}
	}

	return confusion;
}

int GetImageClassification(array<array<char, kImageSize>, kImageSize> image, TrainingModel model)
{
	map<int, double> posterior_map;

	for (int i = 0; i <= 9; i++) {

		double prob = log(model.get_prob_map().at(i).get_appearance_probability());
		
		for (int j = 0; j < kImageSize; j++) {
			for (int k = 0; k < kImageSize; k++) {
				if (image[j][k] == ' ') {
					prob += model.get_prob_map().at(i).get_white_probabilities()[j][k];
				} else if (image[j][k] == '#' || image[j][k] == '+') {
					prob += model.get_prob_map().at(i).get_black_probabilities()[j][k];
				}
			}
		}

		posterior_map.insert(std::pair<int, double>(i, prob));
	}

	//for (int j = 0; j < posterior_map.size(); j++) {
	//	std::cout << j << ": " << posterior_map.at(j) << std::endl;
	//}


	int max = 0;
	for (int i = 0; i < posterior_map.size(); i++) {
		if (posterior_map.at(i) > posterior_map.at(max)) {
			max = i;
		}
	}
	return max;
}
