#include "visualizer.h"
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

void animatePath(cv::Mat& map, const std::vector<cv::Point>& path, int delay_ms) {
    for (size_t i = 0; i < path.size(); ++i) {
        
        cv::Mat display;
        cv::cvtColor(map, display, cv::COLOR_GRAY2BGR);
        
        for (size_t j = 0; j < i; ++j) {
            cv::circle(display, path[j], 1, cv::Scalar(255, 0, 0), -1); // blue current pos
        }
        cv::circle(display, path[i], 1, cv::Scalar(0, 255, 0), -1); // green head marker
        
        // Scale up for better visibility
        cv::Mat scaled;
        cv::resize(display, scaled, cv::Size(), 5, 5, cv::INTER_NEAREST);
        
        cv::imshow("Coverage in 2D space", scaled);
        int key = cv::waitKey(delay_ms);
        if (key == 27) break;
    }

    cv::waitKey(0); // Wait at the end
}
