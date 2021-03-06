#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "core/model.h"
#include "sketchpad.h"

namespace naivebayes {

    namespace visualizer {

/**
 * Allows a user to draw a digit on a sketchpad and uses Naive Bayes to
 * classify it.
 */
        class NaiveBayesApp : public ci::app::App {
        public:
            NaiveBayesApp();

            void draw() override;

            void mouseDown(ci::app::MouseEvent event) override;

            void mouseDrag(ci::app::MouseEvent event) override;

            void keyDown(ci::app::KeyEvent event) override;

            // provided that you can see the entire UI on your screen.
            const double kWindowSize = 700;
            const double kMargin = 100;
            const size_t kImageDimension = 28;

        private:
            naivebayes::Images test_images_ = naivebayes::Images(kImageDimension);
            naivebayes::model model_ = naivebayes::model(kImageDimension);
            Sketchpad sketchpad_;
            int current_prediction_ = -1;
        };

    }  // namespace visualizer

}  // namespace naivebayes
