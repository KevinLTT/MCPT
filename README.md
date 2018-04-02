# 蒙特卡洛路径追踪

## 开发环境
* 操作系统：Ubuntu 16.04
* CPU： Intel i7-6800K
* 内存：64G

## 依赖库
* GLM 0.9.8( https://glm.g-truc.net/0.9.8/index.html ), 用于向量表示与计算
* Assimp 4.1.0( https://github.com/assimp/assimp ), 用于模型文件的读取
* OpenCV 3.4.0( https://opencv.org/ ), 用于图片的显示和保存

## 安装与运行
```bash
cd /path/to/MCPT
mkdir build && cd build
cmake ..
make 
./demo /path/to/objfile number_of_ssp
```
生成的结果将保存在模型文件同路径下, 命名方式为somemodel.obj_ssp.jpg. 

## 数据结构说明

### Accelearte
* Object: 用于表示物体的基类. 包含一个intersect方法, 用于提供统一的光线求交接口. 子类继承时均需实现各自的intersect方法. 
	* Primitive: 继承自Object, 为图元的基类.
		* Triangle: 继承自Primitive, 用于表示模型中的三角形面片. 记录了三角形的顶点信息. 
	* BoundingBox: 继承自Object, 为各种包围盒的基类. 
		* AABB: 继承自BoundingBox, 为其内部的一个Object提供包围盒, 加速求交.
		* KdTree: 继承自BoundingBox, 通过一个平面将空间划分为左右两部分, 并将子空间的信息存储至左右子结点中. 叶子节点中存放Object.

### Camera
* Camera: 用于设定相机位置, 以及根据像素点位置产生对应光线. 

### Ray

* Ray: 通过一个顶点以及一个方向向量表示光线, 包含计算折射方向反射方向的方法.
* Intersection: 记录光线与场景的求交结果.

### Scene
* Loader: 用于从obj等模型文件中读取场景信息, 通过Assimp库来实现.
* Vertex: 顶点信息, 包括地顶点位置及法向等.
* Material: 材质信息, 包括反射率、高光系数等.
* Mesh: 存放从模型文件中读取到的网格信息, 主要为包括顶点序列, 材质信息, 索引信息.
* Normal: 单位向量.

## PathTracing
* PathTracing: 蒙特卡洛路径追踪的实现, 通过输入相机及Object返回图片.

## 运行结果
见results文件夹
