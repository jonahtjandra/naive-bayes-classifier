#include <visualizer/naive_bayes_app.h>

namespace naivebayes {

    namespace visualizer {

        NaiveBayesApp::NaiveBayesApp()
                : sketchpad_(glm::vec2(kMargin, kMargin), kImageDimension,
                             kWindowSize - 2 * kMargin) {
            ci::app::setWindowSize((int) kWindowSize, (int) kWindowSize);
            //loading the model
            std::string file_path = "/Users/jonah/Desktop/SP2021/Cinder/my-projects/naive-bayes-jonahtjandra/data/savedmodel.txt";
            std::ifstream input_file(file_path);
            if (input_file.is_open()) {
                input_file >> model_;
                input_file.close();
            }
            //loading validation data set
            std::string test_path = "/Users/jonah/Desktop/SP2021/Cinder/my-projects/naive-bayes-jonahtjandra/data/testimagesandlabels.txt";
            std::ifstream test_file(test_path);
            if (test_file.is_open()) {
                test_file >> test_images_;
                test_file.close();
            }
        }

        void NaiveBayesApp::draw() {
            ci::Color8u background_color(130,130,130);  // light yellow
            ci::gl::clear(background_color);

            sketchpad_.Draw();

            ci::gl::drawStringCentered(
                    "Press Delete to clear the sketchpad. Press Enter to make a prediction.",
                    glm::vec2(kWindowSize / 2, kMargin / 2), ci::Color("black"));

            ci::gl::drawStringCentered(
                    "Prediction: " + std::to_string(current_prediction_),
                    glm::vec2(kWindowSize / 2, kWindowSize - kMargin / 2), ci::Color("black"));
        }

        void NaiveBayesApp::mouseDown(ci::app::MouseEvent event) {
            sketchpad_.HandleBrush(event.getPos());
        }

        void NaiveBayesApp::mouseDrag(ci::app::MouseEvent event) {
            sketchpad_.HandleBrush(event.getPos());
        }

        void NaiveBayesApp::keyDown(ci::app::KeyEvent event) {
            //calculating model's accuracy
            if (event.getChar() == 'i') {
                std::cout << model_.CalculateAccuracy(test_images_) << "%";
            }
            switch (event.getCode()) {
                case ci::app::KeyEvent::KEY_RETURN:
                    current_prediction_ = model_.Predict(sketchpad_.GetPixels());
                    break;

                case ci::app::KeyEvent::KEY_BACKSPACE:
                    sketchpad_.Clear();
                    break;
            }
        }

    }  // namespace visualizer

}  // namespace naivebayes
