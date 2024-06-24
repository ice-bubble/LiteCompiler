# ROBIN

## 项目介绍：

2024年福州大学编译原理大作业，主要完成 [样例1](./test/test2) 和[样例2](./test/test11)的分析

## 文件结构

```
└── robin                           项目文件夹
    ├── CMakeLists.txt              cmake文件
    ├── fmt-10.2.1                  fmt库
    ├── main.cpp                    主函数
    ├── test                        存放一些测试用例
    ├── README.md                   本文件
    └── src                         源代码
        ├── ast                     语法树相关类的定义
        │   ├── codespace.h         代码的当前产生式空间，用于配合回填
        │   ├── production.cpp      语法树类成员和函数的定义
        │   ├── production.h        语法树中每个结点的类，一个类代表一个产生式
        │   ├── symbol.h            存放产生式相关定义
        │   ├── symboltable.h       存放符号栈相关定义
        │   ├── type.cpp            type类的成员和函数的定义
        │   ├── type.h              区分标识符和字面值具体类型的类的声明
        │   └── visit.cpp           语义分析所用的函数
        ├── common.h                一些项目用到的宏定义和头文件
        ├── debug                   debug文件
        │   ├── debug.cpp           debug函数实现
        │   └── debug.h             debug函数声明
        ├── error                   编译器错误处理模块
        │   ├── error.cpp           error函数定义
        │   └── error.h             error函数声明
        ├── lexer                   词法分析器
        │   ├── lexer.cpp           词法分析器lexer函数实现
        │   └── lexer.h             词法分析器lexer类声明
        ├── parser                  语法分析器
        │   ├── errorprocess.cpp    语法分析中的错误处理部分
        │   ├── parser.cpp          语法分析器parser函数实现
        │   ├── parser.h            语法分析器parser类声明
        │   ├── reduce.cpp          reduce函数相关定义
        │   ├── slrtableInit1.cpp   初始化SLR分析表函数1
        │   ├── slrtableInit2.cpp   初始化SLR分析表函数2
        │   ├── slrtableInit3.cpp   初始化SLR分析表函数3
        │   ├── slrtableInit4.cpp   初始化SLR分析表函数4
        │   ├── slrtableInit5.cpp   初始化SLR分析表函数5
        │   ├── slrtableInit6.cpp   初始化SLR分析表函数6
        │   ├── slrtableInit7.cpp   初始化SLR分析表函数7
        │   ├── slrtableInit8.cpp   初始化SLR分析表函数8
        │   └── slrtableInit9.cpp   初始化SLR分析表函数9
        ├── sema                    语义分析相关
        │   ├── sema.cpp            语义分析类的函数定义
        │   └── sema.h              语义分析类的声明
        └── token                   token相关
            ├── token.cpp           token类函数实现
            └── token.h             tokenType定义和token类声明
```

## 构建方法

构建平台：linux或window10及以上

所需工具：g++(支持c++17及以上)，cmake(大于3.28版本)

步骤：在robin文件夹下运行以下命令

```shell
mkdir build && cd build && cmake .. && make                          #linux平台
```

```shell
mkdir build; cd build; cmake -G "MinGW Makefiles" ..; mingw32-make   #windows平台
```

