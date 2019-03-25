#pragma once

#include <array>
#include <map>
#include "Constants.h"

using std::array;
using std::map;

class ClassProbability {
private:
	int label;
	int num_appearances = 0;
	int total_training_images;

	array<array<double, kImageSize>, kImageSize> white_probabilities;
	array<array<double, kImageSize>, kImageSize> black_probabilities;

public:
	void UpdateMatrix(int i, int j, bool color);
	void ComputeSmoothProbabilities();
	void ComputeLogProbabilities();

	ClassProbability(int num, int total_images);

	array<array<double, kImageSize>, kImageSize> get_white_probabilities();
	array<array<double, kImageSize>, kImageSize> get_black_probabilities();
	int get_label();
	double get_appearance_probability();
};