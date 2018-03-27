#include "PathTracing.h"

cv::Mat PathTracing::render( std::shared_ptr<Object> obj, Camera camera )
{
    cv::Mat img( camera.getHeight(), camera.getWidth(), CV_32FC3, cv::Scalar( 0, 0, 0 ) );
    //cv::Mat img( camera.getWidth(), camera.getHeight(), CV_32FC3, cv::Scalar( 0, 0, 0 ) );

    Intersection inter;
    int hitNum = 0;
    for( int i = 0; i < camera.getHeight(); i++ )
        for( int j = 0; j < camera.getWidth(); j++ )
        {
            Ray ray = camera.generateRay( j, i );
            if( obj->intersect( ray, inter ) )
            {
                img.at<cv::Vec3f>( i, j )[2] = inter.material->diffuse.x;
                img.at<cv::Vec3f>( i, j )[1] = inter.material->diffuse.y;
                img.at<cv::Vec3f>( i, j )[0] = inter.material->diffuse.z;
                //imageBuffer.at(i).at(j)= inter.material->diffuse;
                hitNum++;
            }
        }

    std::cout << "hit: " << hitNum << std::endl;
    return img;
}
