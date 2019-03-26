#pragma once

#include "TrainingModel.h"
#include "Constants.h"
#include <sstream>
#include <iostream>
#include <fstream>
#include <map>

using std::string;
using std::map;
using std::vector;
using std::array;

int GetImageClassification(array<array<char, kImageSize>, kImageSize> image, TrainingModel model);
void ParseTestImageFile(string file, TrainingModel model);
array<array<double, 10>, 10> GetConfusionMatrix(string test_label_file);