# README

# 资源层 资源管理

## 模型导入

使用Assimp管理模型

Assimp-Open Assest Import Library

Assimp能够导入很多种不同的模型文件格式（并也能够导出部分的格式），它会将所有的模型数据加载至Assimp的通用数据结构中。

![img](https://learnopengl-cn.github.io/img/03/01/assimp_structure.png)

读入的数据的默认坐标系是右手坐标系，和OpenGL是一样的

## Texture导入

一开始使用的是stb_image来处理图片，之后使用assimp处理模型的时候，就使用assimp来处理texture

assimp中有对应的函数来处理纹理

# 功能层

## GameObject和Component

游戏中的所有物体都被视为gameobject，由不同的组件组成

为了能够让游戏世界运转，增加tick函数，每个组件包含tick函数

### ECS（Entity-Component-System）

ECS 是 Entity-Component-System 的缩写,它是一种流行的游戏开发架构模式。

ECS 的核心思想是将游戏对象分解为三个基本元素:

Entity（实体）：表示游戏中的对象，如玩家、敌人、道具等。Entity 本身只是一个唯一标识符,没有任何行为或属性。
Component（组件）：定义实体的属性和行为,如 Position、Velocity、Health 等。组件是独立的数据容器,不包含任何逻辑。
System（系统）：处理对应组件的逻辑,如移动系统、渲染系统、碰撞检测系统等。系统会遍历所有拥有相关组件的实体,对它们进行处理。
ECS 架构的优势包括：

高度模块化和可扩展性：组件和系统是独立的,可以很容易地添加、删除或修改。
数据驱动：组件只包含数据,不包含逻辑,使得数据和行为分离。
高性能：系统专注于处理特定组件,避免了传统面向对象架构中的虚函数调用开销。
并行处理：不同的系统可以并行执行,充分利用现代多核 CPU。
ECS 模式被广泛应用于游戏引擎和框架中,如 Unity、Unreal Engine、Godot 等。它为游戏开发提供了一种高效、灵活的架构模式。

# 渲染

## 阴影

shadow map算法是一个两趟的算法，那么根据这个特性可以将shadow map的实现和光照模型部分分开实现。使用一个类来描述阴影，并且通过传递参数和布尔值来改变阴影的类型和对象。

## 相机

### unity的相机处理

在unity中，相机作为一种component处理

包含以下功能：

- skybox
- 处理没有skybox的时候剩下的像素的颜色
- culling mask 这也是我们的相机要实现的东西

You can create multiple Cameras and assign each one to a different **Depth**. Cameras are drawn from low **Depth** to high **Depth**. In other words, a Camera with a **Depth** of 2 will be drawn on top of a Camera with a depth of 1. You can adjust the values of the **Normalized View Port Rectangle** property to resize and position the Camera’s view onscreen. This can create multiple mini-views like missile cams, map views, rear-view mirrors, etc.



# LOG

2024/5/13

模型渲染出来的申鹤偏白，应该是亮度太高的缘故。

2024/5/20

加入rttr库，看看如何构筑反射机制

2024/5/26

完成了Transform

理想的情况肯定是有一个gameobj，然后add component（模型），add componetn（transformer），就去跑渲染。

2024/6/2

![image-20240602023822604](C:\Users\87784\AppData\Roaming\Typora\typora-user-images\image-20240602023822604.png)

这是model创建时的问题，也就是说这个时候this指针是空的，但是如果没有继承component就没有这个问题。

2024/6/2

![image-20240602180933700](C:\Users\87784\AppData\Roaming\Typora\typora-user-images\image-20240602180933700.png)

转换是失败的。这里会输出bad_cast

更换为static_cast，能够强制转换，但是对象会出现问题。

可以尝试采用shared_ptr来处理

2024/6/8

通过添加一个新的modelComponent来处理当前的componet继承问题

- 这样的操作是成功的，通过增加一个modelCompoment来管理Component可以避免直接和复杂的Component接触，使用一个指针来直接管理一个Component实例。

2024/6/11

增加了一个application类，现在的想法是这样的，在app的初始化函数中，准备好相机、渲染这样的管线，实际上的模型加载和别的什么应该是运行的时候的东西，在这之前要准备好处理input的类，app中包含tick函数，还有logic tick 和render tick这样的东西

最后的目标是在main里面有一个app::Init这样的调用，然后在一个循环里面不断的去处理这样。

2024/6/18

考虑处理transform类和camera

教程做了一个多相机渲染，能看出来应该是想要做一个正交的和一个透视的不同的相机

这里通过给物体打上标记让相机来判断物体的标记是否和自己的标记相同，那么现在相机需要的功能就是根据tag来判断物体是否要被渲染，ui相机只渲染ui，game相机渲染game
