#include <iostream>

#include <core/rename_this_file.h>
#include <fstream>
#include <core/images.h>
#include <core/model.h>

int main() {

  //parse data by getting rid of empty lines. One image consists of 28*28 chars + 1 char for the actual value. To parse
  //images we should loop through the txt file in increments of 28*28 + 1 and instantiate an images object from it.
  naivebayes::Images train(28);
  std::string file_path = "/Users/jonah/Desktop/SP2021/Cinder/my-projects/naive-bayes-jonahtjandra/data/trainingimagesandlabels.txt";
  std::string save_file_path = "/Users/jonah/Desktop/SP2021/Cinder/my-projects/naive-bayes-jonahtjandra/data/savedmodel.txt";
  std::ifstream input_file(file_path);
  std::ofstream output_file(save_file_path);

  if (input_file.is_open()) {
      input_file >> train;
      input_file.close();
  }

  naivebayes::model model;
  model.Train(train);

  if (output_file.is_open()) {
    output_file << model;
  }

  std::cout << "Welcome to " << naivebayes::Placeholder().GetBestClass()
            << std::endl;
  return 0;
}
