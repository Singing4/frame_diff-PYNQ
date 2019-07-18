# -*- coding: utf-8 -*-
"""
Created on Fri Jul 12 21:58:02 2019

@author: DELL
"""

# 导入必要的软件包

import datetime
import imutils
import time
import cv2
 

 
#读取摄像头
camera = cv2.VideoCapture("/home/xilinx/jupyter_notebooks//pynq_pedestrian/vtest.avi")
time.sleep(1)
  
# 初始化视频流的第一帧



# 遍历视频的每一帧
while True:
    # 获取当前帧
    time.sleep(0.08)
    (grabbed, frame) = camera.read()
    (grabbed, frame_next) = camera.read() 
    if grabbed == False:
        break
    # 调整该帧的大小，转换为灰阶图像并且对其进行高斯模糊
    frame = imutils.resize(frame, width=500)
    frame_next = imutils.resize(frame_next, width=500)    
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    gray_next = cv2.cvtColor(frame_next, cv2.COLOR_BGR2GRAY)
    #gray = cv2.GaussianBlur(gray, (21, 21), 0)         #可以加速
    #gray_next = cv2.GaussianBlur(gray_next, (21, 21), 0)         #可以加速    
    #作差
    frame_delta = cv2.absdiff(gray_next, gray)
    # 如果第一帧是None，对其进行初始化
    # 计算当前帧和第一帧的不同
    thresh = cv2.threshold(frame_delta, 25, 255, cv2.THRESH_BINARY)[1] #二值化函数,使用这个函数可以获取轮廓图案
 
    # 扩展阈值图像填充孔洞，然后找到阈值图像上的轮廓
    thresh = cv2.dilate(thresh, None, iterations=2)  
    m,cnts,b= cv2.findContours(thresh.copy(), cv2.RETR_EXTERNAL,cv2.CHAIN_APPROX_SIMPLE)
 
    # 遍历轮廓
    for c in cnts:
        # 如果轮廓太小，请忽略它
        if cv2.contourArea(c) < 500:
            continue
 
        # 计算轮廓的边界框，在框架上绘制，并更新文本
        # 计算轮廓的边界框，在当前帧中画出该框
        (x, y, w, h) = cv2.boundingRect(c)
        '''
        print(x)
        print(y)
        print(w)
        print(h)
       '''
        cv2.rectangle(frame, (x, y), (x + w, y + h), (0, 255, 0), 2)
   # print('hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh')
    #显示当前帧
    cv2.imshow("Security Feed", frame)
    #cv2.imshow("Thresh", thresh)
    #cqv2.imshow("Frame Delta", frameDelta)

    
    key = cv2.waitKey(1)
 
    # 如果q键被按下，跳出循环
    if key == ord("q"):
        break
 
# 清理摄像机资源并关闭打开的窗口
camera.release()
cv2.destroyAllWindows()
