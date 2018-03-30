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

enum RAY_TYPE
{
DIFFUSE,
REFLECT,
REFRACT,
NONE,
};

class PathTracing
{
private:
    unsigned int maxDepth;
    glm::vec3 ambientLight;
    std::mersenne_twister_engine<std::uint_fast32_t, 32, 624, 397, 31,
        0x9908b0df, 11,
        0xffffffff, 7,
        0x9d2c5680, 15,
        0xefc60000, 18, 1812433253> generator;
    std::uniform_real_distribution<float> uniformDistribution;

public:
    PathTracing() 
    { 
        maxDepth = 10;
        ambientLight = glm::vec3( 0.2, 0.2, 0.2 );
        generator.seed( time(0) );
        uniformDistribution = std::uniform_real_distribution<float>( 0, 1 );
    }
    cv::Mat render( std::shared_ptr<Object> obj, Camera camera, int SSP = 10 );
    Color3f MCtrace( std::shared_ptr<Object> obj, Ray ray, unsigned int depth = 0 );
    Color3f trace( std::shared_ptr<Object> obj, Ray ray, unsigned int depth = 0 );
    glm::vec3 uniformSampleHemisphere( const float r1, const float r2 );
    void createCoordinateSystem( Normal N, Normal& Nt, Normal& Nb );
    glm::vec3 uniformSampleHemisphere( Normal N );
    glm::vec3 importanceSample( Normal N, float n = -1 );
    void generateNoise( float& x, float& y );
    bool RussianRulette( float p );
    float genRandom();
    glm::vec3 local2world( Normal N, glm::vec3 localSample );
};

#endif
