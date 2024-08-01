# RayTracingSample
这是一个C++ 编写的光线追踪案例

# 运行方式
构建程序
```shell
cmake --build build --config release
```

运行并将结果输出到 image.ppm 文件
```shell
.\build\Release\RayTracingSample.exe > image.ppm 
```

使用ppm工具打开，如果发现格式化错误，请使用转化为utf-8编码格式保存

# 抗锯齿
对采样点周边进行多次随机采样积分，这并不是最好的技术但是一个简单有效的示例。
![alt text](autialiasing.png)

# 漫反射
漫反射照明遵循兰伯特定律：反射光的强度与表面法线与光线之间的角度的余弦成正比。
散射方向，使用一个与入射点相切的单位球体，随机发送光线。