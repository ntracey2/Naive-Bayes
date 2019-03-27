#pragma once

#include <array>
#include <map>
#include <iostream>
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
	void UpdateMatrix(array<array<char, kImageSize>, kImageSize> image_matrix);
	void ComputeSmoothProbabilities();
	void ComputeLogProbabilities();

	ClassProbability(int num, int total_images);
	ClassProbability(int num);
	ClassProbability();

	array<array<double, kImageSize>, kImageSize> get_white_probabilities();
	array<array<double, kImageSize>, kImageSize> get_black_probabilities();

	void set_white_probabilities(array<array<double, kImageSize>, kImageSize> arr);
	void set_black_probabilities(array<array<double, kImageSize>, kImageSize> arr);
	void set_num_appearances(int num);

	int get_label();
	int get_num_appearances();
	double get_appearance_probability();

	friend std::ostream& operator<<(std::ostream& os, const ClassProbability& class_prob);
};