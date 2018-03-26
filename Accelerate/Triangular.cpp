#include "Triangular.h"

Triangular::Triangular( std::vector<Vertex> vs, std::shared_ptr<Material> m ):
    Primitive( vs, m )
{
    if( vertices.size() < 3 )
    {
        std::cout << "failed to construct Triangular." << std::endl;
        return;
    }

    A = vertices[0].position;
    B = vertices[1].position;
    C = vertices[2].position;

    vectorAB = glm::vec3( B.x - A.x, B.y - A.y, B.z - A.z );
    vectorAC = glm::vec3( C.x - A.x, C.y - A.y, C.z - A.z );
}

bool Triangular::intersect( Ray ray, Intersection& intersection )
{ 
    //std::cout << "Triangular" << std::endl; 

    glm::vec3 Dcolumn1 = glm::vec3( A.x-B.x, A.y-B.y, A.z-B.z );
    glm::vec3 Dcolumn2 = glm::vec3( A.x-C.x, A.y-C.y, A.z-C.z );
    glm::vec3 Dcolumn3 = glm::vec3( ray.getDirection( X_AXIS ),
                                    ray.getDirection( Y_AXIS ),
                                    ray.getDirection( Z_AXIS ));
    glm::vec3 Y = glm::vec3( A.x-ray.getOrigin( X_AXIS ), A.y-ray.getOrigin( Y_AXIS ), A.z-ray.getOrigin( Z_AXIS ) );
    float D = determinant3x3( Dcolumn1, Dcolumn2, Dcolumn3 );  
    float beta = determinant3x3( Y, Dcolumn2, Dcolumn3 ) / D;
    float gama = determinant3x3( Dcolumn1, Y, Dcolumn3 ) / D;
    float t = determinant3x3( Dcolumn1, Dcolumn2, Y ) / D;

    if( beta+gama < 1 && beta > EPSILON && gama > EPSILON && t > T_MIN )
    {
        Vertex intersectionPoint;
        intersectionPoint.position.x = ray.getOrigin( X_AXIS ) + t*ray.getDirection( X_AXIS );
        intersectionPoint.position.y = ray.getOrigin( Y_AXIS ) + t*ray.getDirection( Y_AXIS );
        intersectionPoint.position.z = ray.getOrigin( Z_AXIS ) + t*ray.getDirection( Z_AXIS );

        glm::vec3 interpolationNormal = (1-beta-gama)*vertices[0].getNormal() + beta*vertices[1].getNormal() + gama*vertices[2].getNormal();
        intersectionPoint.setNormal( interpolationNormal );

        intersection.point = intersectionPoint;
        intersection.material = this->material;
        intersection.t = t;

        return true;
    }
    else 
        return false; 
}
//bool Triangular::intersect(  )
//{ std::cout << "Triangular" << std::endl; return true; }

float Triangular::determinant3x3( glm::vec3 column1, glm::vec3 column2, glm::vec3 column3 )
{
    float result = 0;
    result += column1.x*column2.y*column3.z + column1.y*column2.z*column3.x + column1.z*column2.x*column3.y;
    result -= column1.z*column2.y*column3.x + column1.y*column2.x*column3.z + column1.x*column2.z*column3.y;
    return result;
}
