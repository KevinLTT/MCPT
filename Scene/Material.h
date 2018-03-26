#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include <string>

#include <glm/glm.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class Material
{
public:
    std::string name; //材质名称
    glm::vec3 ambient; //环境光系数
    glm::vec3 diffuse; //漫反射系数
    glm::vec3 specular; //高光系数
    float transparent; //1为完全不透明, 0为完全透明
    float opticalDensity; //光密度

public:
    Material( aiMaterial* aMaterial );
    Material() = default;
    
    /*glm::vec3 getAmbient();
    glm::vec3 getDiffuse();
    glm::vec3 getSpecular();
    float getTransparent();
    float getOpticalDensity();
    std::string getName();*/
    void show();
};

#endif
