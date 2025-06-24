#include "map_generator.h"
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

cv::Mat generateMap(int width, int height) {
    // Create blank occupancy grid (0 = free space)
    cv::Mat map(height, width, CV_8UC1, cv::Scalar(0));

//convex shapes

    // Rectangle
    cv::rectangle(map, cv::Point(10, 10), cv::Point(25, 25), cv::Scalar(100), cv::FILLED);

    // Triangle
    std::vector<cv::Point> triangle = {{60, 10}, {70, 25}, {50, 25}};
    cv::fillConvexPoly(map, triangle, cv::Scalar(100));

    // Parallelogram
    std::vector<cv::Point> parallelogram = {{75, 35}, {85, 35}, {80, 45}, {70, 45}};
    cv::fillConvexPoly(map, parallelogram, cv::Scalar(100));

    // Circle
    cv::circle(map, cv::Point(20, 45), 7, cv::Scalar(100), cv::FILLED);

//nonconvex shapes

    // Concave Zigzag
    std::vector<cv::Point> zigzag = {
        {20, 60}, {30, 60}, {30, 65}, {35, 65}, {35, 70},
        {25, 70}, {25, 75}, {20, 75}
    };
    cv::drawContours(map, std::vector<std::vector<cv::Point>>{zigzag}, 0, cv::Scalar(100), cv::FILLED);

    // C-shape
    std::vector<cv::Point> c_shape = {
        {40, 30}, {50, 30}, {50, 35}, {45, 35}, {45, 40},
        {50, 40}, {50, 45}, {40, 45}
    };
    cv::drawContours(map, std::vector<std::vector<cv::Point>>{c_shape}, 0, cv::Scalar(100), cv::FILLED);

    // Inward Dent Polygon
    std::vector<cv::Point> dented = {
        {80, 60}, {95, 60}, {95, 75}, {88, 70}, {80, 75}
    };
    cv::drawContours(map, std::vector<std::vector<cv::Point>>{dented}, 0, cv::Scalar(100), cv::FILLED);

    // ===============================
    // DILATION: Add a safety margin
    // ===============================
    cv::Mat dilated;
    int kernelSize = 1;
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT,
                                               cv::Size(2 * kernelSize + 1, 2 * kernelSize + 1));
    cv::dilate(map, dilated, kernel);

    return dilated;
}
