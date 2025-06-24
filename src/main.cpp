#include <opencv2/opencv.hpp>
#include "map_generator.h"
#include "planner.h"
#include "visualizer.h"

int main() {
    int width = 100, height = 100;
    cv::Mat map = generateMap(width, height);

    if (map.empty()) {
        std::cerr << "Map generation failed.\n";
        return -1;
    }

    std::vector<cv::Point> fullPath = planCoverage(map);

    //std::cout << "Planned path length: " << fullPath.size() << std::endl;

    animatePath(map, fullPath, 5);  // Lower delay for faster playback

    return 0;
}
