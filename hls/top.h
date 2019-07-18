#ifndef _TOP_H_

#define _TOP_H_



#include "hls_video.h"

//#include "ap_int.h"

//#include <math.h>



#define MAX_WIDTH  2048

#define MAX_HEIGHT 1536



#define INPUT_IMAGE1 "01.jpg"

#define INPUT_IMAGE2 "02.jpg"

//#define INPUT_IMAGE           "test_1080p.bmp"

#define OUTPUT_IMAGE "result_1080p.jpg"

#define OUTPUT_IMAGE_GOLDEN   "result_1080p_golden.bmp"



// typedef video library core structures

typedef hls::stream<ap_axiu<24,1,1,1> > AXI_STREAM_IN;

typedef hls::stream<ap_axiu<24,1,1,1> > AXI_STREAM_OUT;

typedef hls::Mat<MAX_HEIGHT, MAX_WIDTH, HLS_8UC3> RGB_IMAGE;

typedef hls::Mat<MAX_HEIGHT, MAX_WIDTH, HLS_8UC1> GRAY_IMAGE;



//�����ۺϺ���

void hls_counter_color1(AXI_STREAM_IN& src_axi1,AXI_STREAM_IN& src_axi2, AXI_STREAM_OUT& dst_axi, int rows, int cols);



#endif
