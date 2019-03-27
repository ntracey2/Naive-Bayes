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
			} else {
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

			int sum = 0;
			for (int k = 0; k < predicted_values.size(); k++) {
				if (predicted_values.at(k) == j && actual_values.at(k) == i) {
					sum++;
				}
			}

			confusion[i][j] = (double)sum / std::count(actual_values.begin(), actual_values.end(), i);
		}
	}

	return confusion;
}

int GetImageClassification(array<array<char, kImageSize>, kImageSize> image, TrainingModel model)
{
	array<double, 10> posterior_map;

	for (int i = 0; i <= 9; i++) {

		double prob = log(model.get_prob_map()[i].get_appearance_probability());
		
		for (int j = 0; j < kImageSize; j++) {
			for (int k = 0; k < kImageSize; k++) {
				if (image[j][k] == ' ') {
					prob += model.get_prob_map()[i].get_white_probabilities()[j][k];
				} else if (image[j][k] == '#' || image[j][k] == '+') {
					prob += model.get_prob_map()[i].get_black_probabilities()[j][k];
				}
			}
		}

		posterior_map[i] = prob;
	}

	int max = 0;
	for (int i = 0; i < posterior_map.size(); i++) {
		if (posterior_map[i] > posterior_map[max]) {
			max = i;
		}
	}
	return max;
}
