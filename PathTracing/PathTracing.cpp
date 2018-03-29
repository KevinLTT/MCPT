#include "PathTracing.h"

cv::Mat PathTracing::render( std::shared_ptr<Object> obj, Camera camera )
{
    cv::Mat img( camera.getHeight(), camera.getWidth(), CV_32FC3, cv::Scalar( 0, 0, 0 ) );
    //cv::Mat img( camera.getWidth(), camera.getHeight(), CV_32FC3, cv::Scalar( 0, 0, 0 ) );

    Intersection inter;
    float complete = 0;
    #pragma omp parallel for
    for( int i = 0; i < camera.getHeight(); i++ )
    {
        for( int j = 0; j < camera.getWidth(); j++ )
        {
            glm::vec3 color( 0, 0, 0 );
            for( int k = 0; k < ssp; k++ )
            {
                float px = j, py = i;
                generateNoise( px, py );
                Ray ray = camera.generateRay( px, py );
                color += MCtrace( obj, ray );

                
            }
            color /= ssp;
            img.at<cv::Vec3f>( i, j )[2] = color.x;
            img.at<cv::Vec3f>( i, j )[1] = color.y;
            img.at<cv::Vec3f>( i, j )[0] = color.z;
        }
        complete++;
        std::cout << complete*100  / camera.getHeight() << "%" << std::endl;
    }

    return img;
}

Color3f PathTracing::MCtrace( std::shared_ptr<Object> obj, Ray ray, unsigned int depth )
{

    Intersection inter;
    if( obj->intersect( ray, inter ) == false )
        return BACK_GROUND;

    else if( depth >= maxDepth )
        return inter.material->emission;

    Color3f indirectIllumination = BACK_GROUND;
    for( int i = 0; i < sampleRayNum; i++ )
    {
        int type = RAY_TYPE::DIFFUSE;
        
        if( type == RAY_TYPE::DIFFUSE )
        {
            Ray sampleRay( inter.getPosition(), uniformSampleHemisphere( inter.getNormal() ) );
        }
    }

    glm::vec3 indirectLight( 0, 0, 0 );
    Vertex interPoint = inter.point;
    glm::vec3 interPosition = inter.point.getPosition();
    //if( interPosition.y <= 11 && depth == 0)
    //    std::cout << "in" << std::endl;
    //if( inter.material->diffuse.z == 1)
        //std::cout << "haha" << std::endl;
    Normal interNormal = inter.point.getNormal();
    float pdf = (float)1 / 2*M_PI;
    bool hitIndirect = false;
    for( unsigned int i = 0; i < sampleRayNum; i++ )
    {
        Ray sampleRay( interPosition, uniformSampleHemisphere( interNormal ) );
        float cosTheta = glm::dot( interNormal.getNormal(), sampleRay.getDirection().getNormal() );
        glm::vec3 sampleColor( 0, 0, 0 );
        sampleColor = MCtrace( obj, sampleRay, depth+1 ) * cosTheta;
        /*if( sampleColor.x != 0 || sampleColor.y != 0 || sampleColor.z != 0 )
            hitIndirect = true;*/
        indirectLight = indirectLight + sampleColor * cosTheta;
    }

    /*if( hitIndirect )
    {
        indirectLight = indirectLight + glm::vec3( 1.1, 1.1, 1.1 );
    }*/
    //diffuse = diffuse / ( pdf * sampleRayNum );
    //diffuse = diffuse / ( pdf  );
    //if( diffuse.x == 0 ) diffuse.x = 0.5;
    //if( diffuse.y == 0 ) diffuse.y = 0.5;
    //if( diffuse.z == 0 ) diffuse.z = 0.5;
    //diffuse = diffuse / ( pdf );
    indirectLight /= pdf * sampleRayNum;

    glm::vec3 color = inter.material->emission + indirectLight * inter.material->diffuse + ambientLight * inter.material->ambient;
    //glm::vec3 color = inter.material->emission + diffuse * inter.material->diffuse + ambientLight * inter.material->ambient + glm::vec3( 0.1, 0.1, 0.1 );
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
    /*std::mersenne_twister_engine<std::uint_fast32_t, 32, 624, 397, 31,
                             0x9908b0df, 11,
                             0xffffffff, 7,
                             0x9d2c5680, 15,
                             0xefc60000, 18, 1812433253> generator(time(0));
*/
    //std::uniform_real_distribution<float> distribution( 0, 1 );

    float r1 = uniformDistribution( generator );
    float r2 = uniformDistribution( generator );
    glm::vec3 localSample = uniformSampleHemisphere( r1, r2 );

    Normal Nt, Nb;
    createCoordinateSystem( N, Nt, Nb );
    glm::mat3x3 transform( Nb.getNormal(), N.getNormal(), Nt.getNormal() );

    glm::vec3 sample = transform*localSample;

    return sample;
}

void PathTracing::generateNoise( float& x, float& y )
{
    x += uniformDistribution( generator ) - 0.5;
    y += uniformDistribution( generator ) - 0.5;
    return;
}
