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







# 问题

遇到了一个问题，其实也是比较滑稽。

在写mesh和model的时候，Draw函数没有传引用（Shader&）而是传了Shader，导致多次调用shader的构造函数，使得模型的渲染时混乱的。

