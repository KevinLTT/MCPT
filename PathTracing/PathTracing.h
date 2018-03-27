#ifndef _PATH_TRACING_H
#define _PATH_TRACING_H

#include <vector>
#include <memory>
#include <glm/glm.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>

#include "../Accelerate/Object.h"
#include "../Camera/Camera.h"
#include "../Ray/Ray.h"

class PathTracing
{
public:
    PathTracing() = default;
    cv::Mat render( std::shared_ptr<Object> obj, Camera camera );
};

#endif
