#ifndef VISUALIZER_H
#define VISUALIZER_H
#include <opencv2/opencv.hpp>
#include <vector>

void animatePath(cv::Mat& map, const std::vector<cv::Point>& path, int delay_ms = 30);

#endif // VISUALIZER_H
