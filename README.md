# frame_diff-PYNQ
## 梗概：

本实验的目的是在PYNQ-Z2上实现行人检测。
根据论文《基于快速级联分类器的行人检测方法研究》中基于帧间差分算法和haarcascade的思想进行行人检测。并且将帧间差分算法部署到PYNQ-Z2的PL端。

## 架构：

- *frame_diff_haar*：软件部分。
  - *framep.py*：参考别人的帧间差分算法。
  - *pedestrian_detect.py*：参考别人的基于haarcascade的行人检测。
  - *frame_cas.py*：自己改写的基于帧间差分算法和haarcascade的行人检测。
- *hls*：
  - *top.cpp*、*top.h*：source文件。
  - *test.cpp*：测试文件。
  - *xilinx_com_hls_hls_counter_color1_1_0*帧间差分算法的IP核。
- *vivado*：*fd.tcl*、*fd.bit*。
- *results*：测试结果。
  - *hls_simulation*.jpg：hls中的仿真结果。
  - *frame_diff haar*.mp4：软件测试结果。
  - *block design.png*：block design通路。

## 设计相关：

hls部分：

1.hls加速可以调用opencv库中某些函数，可以很方便的对图像预处理的算法部分进行加速。

2.函数的通过AXI总线设置3种接口类型包括AXI4-Stream(axis)、AXI4-Lite(s_axilite)、AXI4-Master(m_axi)。其中AXI4-Stream可以定义为任何类型的输入或着输出参数的接口（仅传输数据不传输地址），而不定义输入输出接口；AXI4-Lite可以定义为除数组外的任意参数的接口；AXI4-Master只能定义为数组或者指针的接口。本设计使用AXI4-Stream来传输图像的像素值。

3.输入数据的格式要转换为mat。

4.加速函数的主要指令是inline off dataflow flatten off。

5.ip核生成前要经过编译、c仿真、c和RTL联合仿真。

block design部分：

1.要实现整个功能需要搭建硬件通路。

2.传输图像可以使用DMA来实现直接内存读取，速度快。

3.自定义ip不通，可以逐块分析（例如本设计使用多个DMA连接图像处理ip，可以只连接单个dma，测试dma是否可以通信，进而排除错误）。

## 设计步骤：

硬件部分：

1.hls部分：编写硬件实现，综合，定义引脚，仿真，生成IP。

2.vivado部分：添加IP，完成block design，验证通路。

3.jupyter notebooks部分：编写驱动并检验效果。

软件部分：

结合两个代码进行修改，得到新算法，基于帧间差分算法和haarcascade的思想进行行人检测，测试结果。



## 还原步骤：

1.在hls中生成IP核。

2.在vivado中source fd.tcl

## 未完成部分：

IP核得到验证，block design通路实现，但是无法驱动来达到帧间差分算法的效果。

## 参考：

文献：高嵩, 杜晴岚, 陈超波. 基于快速级联分类器的行人检测方法研究[J]. 计算机工程与科学, 2015, 37(6):1183-1188.

BibTeX:

> @article{高嵩2015基于快速级联分类器的行人检测方法研究,
> title={基于快速级联分类器的行人检测方法研究},
> author={高嵩 and 杜晴岚 and 陈超波},
> journal={计算机工程与科学},
> volume={37},
> number={6},
> pages={1183-1188},
> year={2015},
> }

代码：

> *framep.py*、*pedestrian_detect.py*
