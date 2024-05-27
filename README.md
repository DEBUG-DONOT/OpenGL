# README

# 资源管理

## 模型导入

使用Assimp管理模型

Assimp-Open Assest Import Library

Assimp能够导入很多种不同的模型文件格式（并也能够导出部分的格式），它会将所有的模型数据加载至Assimp的通用数据结构中。

![img](https://learnopengl-cn.github.io/img/03/01/assimp_structure.png)

读入的数据的默认坐标系是右手坐标系，和OpenGL是一样的



## Texture导入

一开始使用的是stb_image来处理图片，之后使用assimp处理模型的时候，就使用assimp来处理texture

assimp中有对应的函数来处理纹理



# 渲染

## 阴影

shadow map算法是一个两趟的算法，那么根据这个特性可以将shadow map的实现和光照模型部分分开实现。使用一个类来描述阴影，并且通过传递参数和布尔值来改变阴影的类型和对象。







# LOG

2024/5/13

模型渲染出来的申鹤偏白，应该是亮度太高的缘故。

2024/5/20

加入rttr库，看看如何构筑反射机制

2024/5/26

完成了Transform

理想的情况肯定是有一个gameobj，然后add component（模型），add componetn（transformer），就去跑渲染。
