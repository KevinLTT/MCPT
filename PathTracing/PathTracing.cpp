#include "PathTracing.h"
#include "../Scene/Normal.h"

cv::Mat PathTracing::render( std::shared_ptr<Object> obj, Camera camera )
{
    cv::Mat img( camera.getHeight(), camera.getWidth(), CV_32FC3, cv::Scalar( 0, 0, 0 ) );
    //cv::Mat img( camera.getWidth(), camera.getHeight(), CV_32FC3, cv::Scalar( 0, 0, 0 ) );

    Intersection inter;
    int hitNum = 0;
    #pragma omp parallel
    for( int i = 0; i < camera.getHeight(); i++ )
        for( int j = 0; j < camera.getWidth(); j++ )
        {
            Ray ray = camera.generateRay( j, i );
            glm::vec3 color = MCtrace( obj, ray, 1 );
            if( obj->intersect( ray, inter ) )
            {
                img.at<cv::Vec3f>( i, j )[2] = color.x;
                img.at<cv::Vec3f>( i, j )[1] = color.y;
                img.at<cv::Vec3f>( i, j )[0] = color.z;
                //imageBuffer.at(i).at(j)= inter.material->diffuse;
                hitNum++;
            }
            std::cout << "i: " << i << " j: " << j << std::endl;
        }

    std::cout << "hit: " << hitNum << std::endl;
    return img;
}

glm::vec3 PathTracing::MCtrace( std::shared_ptr<Object> obj, Ray ray, unsigned int depth )
{
    if( depth > maxDepth )
        return glm::vec3( 0, 0, 0 );

    Intersection inter;
    if( obj->intersect( ray, inter ) == false )
        return glm::vec3( 0, 0, 0 );

    glm::vec3 diffuse( 0, 0, 0 );
    Vertex interPoint = inter.point;
    float pdf = (float)1 / 2*M_PI;
    for( unsigned int i = 0; i < sampleRayNum; i++ )
    {
        Ray sampleRay( interPoint.getPosition(), interPoint.getNormal() );
        float cosTheta = glm::dot( interPoint.getNormal(), sampleRay.getDirection().getNormal() );
        diffuse += MCtrace( obj, sampleRay, depth+1 ) * cosTheta;
    }
    diffuse = diffuse / ( pdf * sampleRayNum );

    glm::vec3 color = inter.material->emission + diffuse * inter.material->diffuse;
    return color;
}

glm::vec3 PathTracing::uniformSampleHemisphere( const float r1, const float r2 )
{
    float sinTheta = sqrtf( 1 - r1*r1 );
    float phi = 2*M_PI*r2;
    float x = sinTheta * cosf( phi );
    float z = sinTheta * sinf( phi );
    return glm::vec3( x, r1, z );
}

void PathTracing::createCoordinateSystem(  Normal N, Normal& Nt, Normal& Nb )
{
    if( std::fabs( N.getNormal(X_AXIS) ) > std::fabs( N.getNormal(Y_AXIS) ) )
        Nt = Normal( glm::vec3( N.getNormal(Z_AXIS), 0, -1*N.getNormal(X_AXIS) ) );
    else
        Nt = Normal( glm::vec3( 0, -1*N.getNormal(Z_AXIS), N.getNormal(Y_AXIS) ) );
    Nb = Normal( glm::vec3( glm::cross( N.getNormal(), Nt.getNormal() ) ) );
}

glm::vec3 PathTracing::uniformSampleHemisphere( Normal N )
{
    std::mersenne_twister_engine<std::uint_fast32_t, 32, 624, 397, 31,
                             0x9908b0df, 11,
                             0xffffffff, 7,
                             0x9d2c5680, 15,
                             0xefc60000, 18, 1812433253> generator(time(0));

    std::uniform_real_distribution<float> distribution( 0, 1 );

    float r1 = distribution( generator );
    float r2 = distribution( generator );
    glm::vec3 localSample = uniformSampleHemisphere( r1, r2 );

    Normal Nt, Nb;
    createCoordinateSystem( N, Nt, Nb );
    glm::mat3x3 transform( Nb.getNormal(), N.getNormal(), Nt.getNormal() );

    glm::vec3 sample = transform*localSample;

    return sample;
}

