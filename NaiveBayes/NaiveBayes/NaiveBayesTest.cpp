#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "Classify.h"
#include "TrainingModel.h"
#include "ClassProbability.h"
#include "Constants.h"

TEST_CASE("Test functinality") {
	TrainingModel model("trainingimages", "traininglabels");
	model.ParseImageFile("trainingimages");

	model.ComputeProbabilities();

	ParseTestImageFile("testimages", model);

	array<array<double, 10>, 10> confusion_matrix = GetConfusionMatrix("testlabels");

	for (int i = 0; i <= 9; i++) {
		for (int j = 0; j <= 9; j++) {
			std::cout << confusion_matrix[i][j];
		}
		std::cout << std::endl;
	}
}

