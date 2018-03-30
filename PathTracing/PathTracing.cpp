#include "PathTracing.h"
#include <cstdio>

float fresnel( float ni, float nt, float cosTheta )
{
    float f0 = ( ni - nt ) / ( ni + nt );
    f0 = f0 * f0;
    return f0 + ( 1 - f0 ) * powf( 1.0f-cosTheta, 5 );
}

cv::Mat PathTracing::render( std::shared_ptr<Object> obj, Camera camera, int SSP )
{
    //cv::Mat img( camera.getHeight(), camera.getWidth(), CV_32FC3, cv::Scalar( 0, 0, 0 ) );
    cv::Mat img( camera.getWidth(), camera.getHeight(), CV_8UC3, cv::Scalar( 0, 0, 0 ) );

    Intersection inter;
    float complete = 0;
    #pragma omp parallel for
    for( int i = 0; i < camera.getHeight(); i++ )
    {
        for( int j = 0; j < camera.getWidth(); j++ )
        {
            glm::vec3 color( 0, 0, 0 );
            for( int k = 0; k < SSP; k++ )
            {
                float px = j, py = i;
                generateNoise( px, py );
                Ray ray = camera.generateRay( px, py );
                color += MCtrace( obj, ray );
            }
            color /= SSP; 
            img.at<cv::Vec3b>( i, j )[2] = color.x >= 1.0f ? 255 : color.x*255;
            img.at<cv::Vec3b>( i, j )[1] = color.y >= 1.0f ? 255 : color.y*255;
            img.at<cv::Vec3b>( i, j )[0] = color.z >= 1.0f ? 255 : color.z*255;
        }
        complete++;
        std::cout << complete*100  / camera.getHeight() << "%" << std::endl;
        //printf( "%.2f%%\r", complete*100 / camera.getHeight() );
    }

    //for( unsigned int k = 0; k < ssp; k++ )
    //{
        //for( int i = 0; i < camera.getHeight(); i++ )
        //{
            //for( int j = 0; j < camera.getWidth(); j++ )
            //{
                //float px = j, py = i;
                //generateNoise( px, py );
                //Ray ray = camera.generateRay( px, py );
                //auto color = MCtrace( obj, ray );
                //for( int l = 0; l < 3; l++ )
                    //img.at<cv::Vec3f>( i, j )[l] = ( img.at<cv::Vec3f>( i, j )[l] * k + color.x ) / ( k+1 );
            //}
        //}
        //s++;
        //std::cout << "ssp: " << s << std::endl;
        //imshow( "render", img );
    //}

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
    int rayType = RAY_TYPE::NONE;
    glm::vec3 sampleDirection;
    bool sampled = false;

    if( inter.material->transparent < 1 )
    {
        
        float cosTheta = glm::dot( ray.getDirection().getNormal(), inter.getNormal() );

        glm::vec3 Nl;
        float ni, nt;
        if( cosTheta < 0 ) //same side
        {
            Nl = inter.getNormal();
            nt = inter.material->opticalDensity;
            ni = 1.0;
        }
        else
        {
            Nl = -1.0f*inter.getNormal();
            nt = 1.0;
            ni = inter.material->opticalDensity;
        }
    
        auto fresnelRefractionIndex = 1.0f - fresnel( ni, nt, fabs(cosTheta) );
        if( RussianRulette( fresnelRefractionIndex ) ) 
        {
            if( ray.able2refract( Nl, ni/nt, sampleDirection ) )
                rayType = RAY_TYPE::REFRACT;
            else
            {
                sampleDirection = importanceSample( ray.reflectDirection( inter.getNormal() ), inter.material->shininess );
                sampleDirection = ray.reflectDirection( inter.getNormal() );
                rayType = RAY_TYPE::REFLECT;
            }
            sampled = true;
        }
         

        /*glm::vec3 nl;
        float nc = 1.0, nt = inter.material->opticalDensity;
        float nnt;
        bool into;
        if( glm::dot( ray.getDirection().getNormal(), inter.getNormal()) < 0 )
        {
            nl = inter.getNormal();
            nnt = nc / nt;
            into = true;
        }
        else
        {
            nl = -1.0f * inter.getNormal();
            nnt = nt / nc;
            into = false;
        }
        float ddn = glm::dot( ray.getDirection().getNormal(), nl );
        
        float cos2t = 1 - nnt*nnt*( 1 - ddn*ddn );
        if( cos2t < 0 ) //Total internal reflection
        {
            sampleDirection = ray.reflectDirection( inter.getNormal() );
            rayType = RAY_TYPE::REFLECT;
            sampled = true;
        }
        else
        {
            Normal tdir( (ray.getDirection().getNormal() * nnt - inter.getNormal() * (( into?1.0f:-1.0f ) * (ddn*nnt+sqrtf(cos2t))) ) );
            glm::vec3 tdirection = tdir.getNormal();
            float a = nt-nc, b = nt+nc;
            float R0 = a*a/(b*b), c = 1 - ( into ? -ddn : glm::dot( tdirection, inter.getNormal() ) );
            float Re = R0 + ( 1- R0 ) * powf( c, 5 ), Tr = 1 - Re;
            if( RussianRulette( Tr ) )
            {
                sampleDirection = tdirection;
                rayType = RAY_TYPE::REFRACT;
            }
            else
            {
                sampleDirection = ray.reflectDirection( inter.getNormal() );
                rayType = RAY_TYPE::REFLECT;
            }
        }*/
    }
    //else
    if( !sampled )
    {
        float diffuseComponent = glm::dot(inter.material->diffuse, glm::vec3(1, 1, 1) );
        float specularComponent = glm::dot( inter.material->specular, glm::vec3( 1, 1, 1) );

        if( RussianRulette( diffuseComponent / ( diffuseComponent + specularComponent ) ) )
        {
            sampleDirection = importanceSample( inter.getNormal() );
            rayType = RAY_TYPE::DIFFUSE;
        }
        else
        {
            sampleDirection = importanceSample( ray.reflectDirection( inter.getNormal() ), inter.material->shininess  );
            rayType = RAY_TYPE::REFLECT;
        }
        sampled = true;
    }

    Ray sampleRay( inter.getPosition(), sampleDirection );
    indirectIllumination += MCtrace( obj, sampleRay, depth+1 );
    switch( rayType )
    {
        case RAY_TYPE::DIFFUSE: indirectIllumination *= inter.material->diffuse; break;
        case RAY_TYPE::REFLECT: indirectIllumination *= inter.material->specular; break;
        case REFRACT:
        case NONE: break;
    }

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
