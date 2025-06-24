#ifndef PLANNER_H
#define PLANNER_H

#include <opencv2/opencv.hpp>
#include <vector>

std::vector<cv::Point> planCoverage(const cv::Mat& map);

#endif // PLANNER_H
