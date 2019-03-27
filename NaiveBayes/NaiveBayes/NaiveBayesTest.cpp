#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "Classify.h"
#include "TrainingModel.h"
#include "ClassProbability.h"
#include "Constants.h"



TEST_CASE("Test classification accuracy") {
	//TrainingModel model("trainingimages", "traininglabels");
	//model.ParseImageFile("trainingimages");
	TrainingModel model("model_data");
	//model.ComputeProbabilities();

	ParseTestImageFile("testimages", model);

	array<array<double, 10>, 10> confusion_matrix = GetConfusionMatrix("testlabels");

	for (int i = 0; i <= 9; i++) {
		REQUIRE(confusion_matrix[i][i] > 0.60);
	}

	//model.SaveToFile("model_data");
}

TEST_CASE("Test loading model from file") {
	TrainingModel model("model_data");

	SECTION("Get total num images") {
		REQUIRE(model.get_num_images() == 5000);
	}
	SECTION("Get num appearances for label") {
		REQUIRE(model.get_prob_map()[0].get_num_appearances() == 479);
	}
	SECTION("Get white probability array") {
		REQUIRE(model.get_prob_map()[0].get_white_probabilities()[0][0] == -0.0102776);
	}
	SECTION("Get black probability array") {
		REQUIRE(model.get_prob_map()[0].get_black_probabilities()[0][0] == -4.58292);
	}
}

TEST_CASE("Test ClassProbability") {
	SECTION("Array initialization") {
		ClassProbability c(0, 5);
		for (int i = 0; i < kImageSize; i++) {
			for (int j = 0; j < kImageSize; j++) {
				REQUIRE(c.get_white_probabilities()[i][j] == 0 && c.get_black_probabilities()[i][j] == 0);
			}
		}
	}



	ClassProbability c(0, 5);
	c.set_num_appearances(2);
	array<array<char, kImageSize>, kImageSize> example_image;
	example_image[0][0] = '#';
	c.UpdateMatrix(example_image);

	SECTION("Update matrix") {
		REQUIRE(c.get_black_probabilities()[0][0] == 1);
	}
	SECTION("Compute smooth probabilities") {
		c.ComputeSmoothProbabilities();
		REQUIRE(c.get_black_probabilities()[0][0] == ((double)6 / 12));
	}
	SECTION("Compute log probabilites") {
		c.ComputeLogProbabilities();
		REQUIRE(c.get_black_probabilities()[0][0] == log((double)6 / 12));
	}
}

TEST_CASE("Test file input output") {
	TrainingModel model("trainingimages", "traininglabels");
	model.ParseImageFile("trainingimages");
	model.ComputeProbabilities();
	model.SaveToFile("testing_file");
	TrainingModel new_model("testing_file");

	SECTION("Test black probabilities") {
		for (int i = 0; i < model.get_prob_map().size(); i++) {
			REQUIRE(model.get_prob_map().at(i).get_black_probabilities() == (new_model.get_prob_map().at(i).get_black_probabilities()));
		}
	}
	SECTION("Test white probabilities") {
		for (int i = 0; i < model.get_prob_map().size(); i++) {
			REQUIRE(model.get_prob_map().at(i).get_white_probabilities() == (new_model.get_prob_map().at(i).get_white_probabilities()));
		}
	}
	SECTION("Test num appearances") {
		for (int i = 0; i < model.get_prob_map().size(); i++) {
			REQUIRE(model.get_prob_map().at(i).get_num_appearances() == (new_model.get_prob_map().at(i).get_num_appearances()));
		}
	}
}