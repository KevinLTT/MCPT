#ifndef _PATH_TRACING_H
#define _PATH_TRACING_H

#include <vector>
#include <memory>
#include <glm/glm.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <cmath>
#include <ctime>
#include <omp.h>

#include "../Accelerate/Object.h"
#include "../Camera/Camera.h"
#include "../Ray/Ray.h"
#include "../Scene/Scene.h"
#include "../Scene/Normal.h"
#include "../Config/config.h"


class PathTracing
{
private:
    unsigned int maxDepth;
    unsigned int sampleRayNum;
    glm::vec3 ambientLight;

public:
    PathTracing() 
    { 
        maxDepth = 1; 
        sampleRayNum = 10; 
        ambientLight = glm::vec3( 0.2, 0.2, 0.2 );
    }
    cv::Mat render( std::shared_ptr<Object> obj, Camera camera );
    glm::vec3 MCtrace( std::shared_ptr<Object> obj, Ray ray, unsigned int depth = 0 );
    glm::vec3 uniformSampleHemisphere( const float r1, const float r2 );
    void createCoordinateSystem( Normal N, Normal& Nt, Normal& Nb );
    glm::vec3 uniformSampleHemisphere( Normal N );
};

#endif
