#include "ClassProbability.h"
#include "Constants.h"

void ClassProbability::UpdateMatrix(int i, int j, bool color) {
	if (color) {
		black_probabilities[i][j]++;
	} else {
		white_probabilities[i][j]++;
	}
}

void ClassProbability::ComputeSmoothProbabilities() {
	for (int i = 0; i < kImageSize; i++) {
		for (int j = 0; j < kImageSize; j++) {
			white_probabilities[i][j] = (kSmoothingConstant + white_probabilities[i][j]) / ((2 * kSmoothingConstant) + num_appearances);
			black_probabilities[i][j] = (kSmoothingConstant + black_probabilities[i][j]) / ((2 * kSmoothingConstant) + num_appearances);
		}
	}
}

void ClassProbability::ComputeLogProbabilities() {
	for (int i = 0; i < kImageSize; i++) {
		for (int j = 0; j < kImageSize; j++) {
			white_probabilities[i][j] = log(white_probabilities[i][j]);
			black_probabilities[i][j] = log(black_probabilities[i][j]);
		}
	}

}

ClassProbability::ClassProbability(int num, int total_images) {
	label = num;
	total_training_images = total_images;
}

array<array<double, kImageSize>, kImageSize> ClassProbability::get_white_probabilities() {
	return white_probabilities;
}

array<array<double, kImageSize>, kImageSize> ClassProbability::get_black_probabilities() {
	return black_probabilities;
}

int ClassProbability::get_label() {
	return label;
}

double ClassProbability::get_appearance_probability() {
	return num_appearances / total_training_images;
}
