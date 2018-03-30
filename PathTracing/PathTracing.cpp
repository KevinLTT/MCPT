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
    //for( unsigned int i = 0; i < sampleRayNum; i++ )
    //{
        if( inter.material->transparent >= 0 ) //not transparent, only reflectance
        {
            float diffuseComponent = glm::dot(inter.material->diffuse, glm::vec3(1, 1, 1) );
            float specularComponent = glm::dot( inter.material->specular, glm::vec3( 1, 1, 1) );
            glm::vec3 sampleDirection;
            Ray sampleRay;
            float theta, pdf;
            glm::vec3 illum( 0, 0, 0 );
            //if( RussianRulette( diffuseComponent / (specularComponent+diffuseComponent) ) )
            if( true )
            {
                //diffuse win
                sampleDirection = importanceSample( inter.getNormal() );
                sampleDirection = uniformSampleHemisphere( inter.getNormal()  );
                sampleRay = Ray( inter.getPosition(), sampleDirection );
                Color3f sampleIllumination = MCtrace( obj, sampleRay, depth+1 );
                theta = acos( sampleDirection.y );
                pdf = sinf(theta) * cosf(theta) / M_PI;
                indirectIllumination = inter.material->diffuse * sampleIllumination;
            }
            else
            {
                //specular win
                sampleDirection = importanceSample( inter.getNormal(), inter.material->shininess );
                sampleRay = Ray( inter.getPosition(), sampleDirection );
                Color3f sampleIllumination = MCtrace( obj, sampleRay, depth+1 );
                theta = acos( sampleDirection.y );
                pdf = (inter.material->shininess+1)*powf( cosf(theta), inter.material->shininess ) * sinf( theta ) / ( 2 * M_PI );
                indirectIllumination = inter.material->specular * sampleIllumination;
            }
            /*if( inter.material->shininess != 0 ) {
                float specularK = powf(
                        fabs(glm::dot(ray.direction.getNormal(), sampleRay.reflectDirection(inter.getNormal()))),
                        inter.material->shininess);
                illum += inter.material->specular * sampleIllumination * specularK;
            }*/
            //illum += inter.material->diffuse * sampleIllumination * cosf( theta ) / (float)M_PI;
            //illum /= pdf * cosf(theta) ;
            //indirectIllumination += illum;
        }

    //}
    //indirectIllumination /= sampleRayNum;
    //indirectIllumination /= sampleRayNum;

    //return inter.material->emission / (float)50 + indirectIllumination;
    return inter.material->emission + indirectIllumination + inter.material->ambient*ambientLight;

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

    float r1 = genRandom();
    float r2 = genRandom();
    glm::vec3 localSample = uniformSampleHemisphere( r1, r2 );

    return local2world( N, localSample );
}

glm::vec3 PathTracing::importanceSample(Normal N, float n) {
    float r1 = genRandom();
    float r2 = genRandom();

    float phi = r1 * 2 * M_PI;
    float theta = n < 0 ? asin(sqrtf(r2)) : acos( powf( r2, (float)1 / (n+1) ));
    glm::vec3 localSample( sin(theta)*cos(phi), cos(theta), sin(theta)*sin(phi) );

    return local2world( N, localSample );
}

glm::vec3 PathTracing::local2world(Normal N, glm::vec3 localSample) {
    Normal Nt, Nb;
    createCoordinateSystem( N, Nt, Nb );
    glm::mat3x3 transform( Nb.getNormal(), N.getNormal(), Nt.getNormal() );
    return transform*localSample;
}

void PathTracing::generateNoise( float& x, float& y )
{
    x += genRandom() - 0.5;
    y += genRandom() - 0.5;
    return;
}

bool PathTracing::RussianRulette(float p) {
    return genRandom() < p ? true : false;
}

float PathTracing::genRandom()
{
    return uniformDistribution( generator );
}
