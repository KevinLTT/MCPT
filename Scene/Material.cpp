#include <iostream>
#include <string>

#include <glm/glm.hpp>
#include <assimp/Importer.hpp>

#include "Material.h"

glm::vec3 aiColor3DtoGlmVec3( aiColor3D );

Material::Material( aiMaterial* aMaterial )
{
    aiString aName;
    aMaterial->Get( AI_MATKEY_NAME, aName );
    this->name = std::string( aName.C_Str() );

    aiColor3D ka, kd, ks, emi;
    aMaterial->Get( AI_MATKEY_COLOR_AMBIENT, ka );
    aMaterial->Get( AI_MATKEY_COLOR_DIFFUSE, kd );
    aMaterial->Get( AI_MATKEY_COLOR_SPECULAR, ks );
    aMaterial->Get( AI_MATKEY_COLOR_EMISSIVE, emi );
    this->ambient = aiColor3DtoGlmVec3( ka );
    this->diffuse = aiColor3DtoGlmVec3( kd );
    this->specular = aiColor3DtoGlmVec3( ks );
    this->emission = aiColor3DtoGlmVec3( emi );

    float tf;
    aMaterial->Get( AI_MATKEY_COLOR_TRANSPARENT, tf );
    this->transparent = tf;

    float ni;
    aMaterial->Get( AI_MATKEY_REFRACTI, ni );
    this->opticalDensity = ni;

    float ns;
    aMaterial->Get( AI_MATKEY_SHININESS, ns );
    this->shininess = ns;
}

void Material::show()
{
    std::cout << "-----" << name << "-----" << std::endl;
    std::cout << "Ambient: " << ambient.x << ", " << ambient.y << ", " << ambient.z << std::endl;
    std::cout << "Diffuse: " << diffuse.x << ", " << diffuse.y << ", " << diffuse.z << std::endl;
    std::cout << "Specular: " << specular.x << ", " << specular.y << ", " << specular.z << std::endl;
    std::cout << "Transparent: " << transparent << std::endl;
    std::cout << "Optical Density: " << opticalDensity << std::endl;
    std::cout << "Emission: " << emission.x << ", " << emission.y << ", " << emission.z << std::endl;
    std::cout << "Shinimess: " << shininess << std::endl;
}

glm::vec3 aiColor3DtoGlmVec3( aiColor3D aColor )
{
    glm::vec3 result;
    result.x = aColor.r;
    result.y = aColor.g;
    result.z = aColor.b;

    return result;
}
