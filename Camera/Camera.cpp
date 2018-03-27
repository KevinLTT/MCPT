#include "Camera.h"

Camera::Camera( int Width, int Height, float Fov ):
    position( glm::vec4( 0.0f, 0.0f, 0.0f, 1.0f ) ), 
    width( Width ), height( Height ), 
    fov( Fov ), 
    aspectRatio( (float)Width/(float)Height ),
    camera2world( glm::mat4( 1.0f ) )
{}

Ray Camera::generateRay( int Px, int Py )
{
    float px, py;
    px = ( 2 * ( (Px+0.5) / (float)width ) - 1 ) * tan( deg2rad(fov) / 2 ) * aspectRatio;
    py = ( 1 - 2 * ( (Py+0.5) / (float)height ) ) * tan( deg2rad(fov) / 2 );

    glm::vec4 dir4f( px, py, -1, 1 );
    dir4f = camera2world * dir4f;

    Normal dir( glm::vec3( dir4f.x/dir4f.w, dir4f.y/dir4f.w, dir4f.z/dir4f.w ) );
    Ray ray( Vertex( glm::vec3( position.x, position.y, position.z ) ), dir );

    return ray;
}

void Camera::transform( glm::mat4x4 t )
{
    position = glm::vec4( 0.0f, 0.0f, 0.0f, 1.0f );
    camera2world = glm::mat4( 1.0f );
    
    camera2world = t * camera2world;
    position = camera2world*position;
    position = position / position.w;
}
    

