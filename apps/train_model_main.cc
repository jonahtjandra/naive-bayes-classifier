#include <iostream>

#include <core/rename_this_file.h>
#include <fstream>
#include <core/train.h>

// TODO: You may want to change main's signature to take in argc and argv
int main() {
  // TODO: Replace this with code that reads the training data, trains a model,
  // and saves the trained model to a file.

  //parse data by getting rid of empty lines. One image consists of 28*28 chars + 1 char for the actual value. To parse
  //images we should loop through the txt file in increments of 28*28 + 1 and instantiate an images object from it.
  naivebayes::Train train;
  std::string file_path = "/Users/jonah/Desktop/SP2021/Cinder/my-projects/naive-bayes-jonahtjandra/data/trainingimagesandlabels.txt";
  std::ifstream input_file(file_path);

  if (input_file.is_open()) {
      input_file >> train;
      input_file.close();
  }

  std::cout << "Welcome to " << naivebayes::Placeholder().GetBestClass()
            << std::endl;
  return 0;
}
