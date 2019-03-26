#include "ClassProbability.h"
#include "Constants.h"

void ClassProbability::UpdateMatrix(array<array<char, kImageSize>, kImageSize> image_matrix) {
	num_appearances++;
	//std::cout << label << ": " << num_appearances << std::endl;
	for (int i = 0; i < kImageSize; i++) {
		for (int j = 0; j < kImageSize; j++) {
			if (image_matrix[i][j] == ' ') {
				white_probabilities[i][j]++;
			} else if (image_matrix[i][j] == '#' || image_matrix[i][j] == '+'){
				black_probabilities[i][j]++;
			}
		}
	}
}

void ClassProbability::ComputeSmoothProbabilities() {
	for (int i = 0; i < kImageSize; i++) {
		for (int j = 0; j < kImageSize; j++) {
			//std::cout << white_probabilities[i][j] << std::endl;
			//std::cout << num_appearances;
			white_probabilities[i][j] = (kSmoothingConstant + white_probabilities[i][j]) / ((2 * kSmoothingConstant) + num_appearances);
			//std::cout << white_probabilities[i][j] << std::endl;
			black_probabilities[i][j] = (kSmoothingConstant + black_probabilities[i][j]) / ((2 * kSmoothingConstant) + num_appearances);
		}
	}
}

void ClassProbability::ComputeLogProbabilities() {
	for (int i = 0; i < kImageSize; i++) {
		for (int j = 0; j < kImageSize; j++) {
			white_probabilities[i][j] = log(white_probabilities[i][j]);
			//std::cout << white_probabilities[i][j] << std::endl;

			black_probabilities[i][j] = log(black_probabilities[i][j]);
		}
	}

}

ClassProbability::ClassProbability(int num, int total_images) {
	label = num;
	total_training_images = total_images;

	//std::cout << total_images << std::endl;

	array<double, kImageSize> filler;
	filler.fill(0.0);

	white_probabilities.fill(filler);
	black_probabilities.fill(filler);
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
	return (double) num_appearances / total_training_images;
}

std::ostream & operator<<(std::ostream & os, const ClassProbability & class_prob)
{
	os << class_prob.label << std::endl;
	os << (class_prob.num_appearances / class_prob.total_training_images) << std::endl;
	
	for (int i = 0; i < kImageSize; i++) {
		for (int j = 0; j < kImageSize; j++) {
			os << class_prob.white_probabilities[i][j] << ',';
		}
	}
	os << std::endl;
	for (int i = 0; i < kImageSize; i++) {
		for (int j = 0; j < kImageSize; j++) {
			os << class_prob.black_probabilities[i][j] << ',';
		}
	}
	return os;
}
