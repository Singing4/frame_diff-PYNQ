#include "top.h"

#include "hls_math.h"

#include "hls_video.h"

void hls_counter_color1(AXI_STREAM_IN& INPUT_STREAM1,AXI_STREAM_IN& INPUT_STREAM2, AXI_STREAM_OUT& OUTPUT_STREAM, int rows, int cols)
{

#pragma HLS INTERFACE axis port=INPUT_STREAM1

#pragma HLS INTERFACE axis port=INPUT_STREAM2

#pragma HLS INTERFACE axis port=OUTPUT_STREAM



#pragma HLS RESOURCE core=AXI_SLAVE variable=rows metadata="-bus_bundle CONTROL_BUS"

#pragma HLS RESOURCE core=AXI_SLAVE variable=cols metadata="-bus_bundle CONTROL_BUS"

#pragma HLS RESOURCE core=AXI_SLAVE variable=return metadata="-bus_bundle CONTROL_BUS"



#pragma HLS INTERFACE ap_stable port=rows

#pragma HLS INTERFACE ap_stable port=cols



    RGB_IMAGE img_01(rows, cols);

    RGB_IMAGE img_02(rows, cols);

    GRAY_IMAGE img_1(rows, cols);

    GRAY_IMAGE img_2(rows, cols);

    GRAY_IMAGE img_3(rows, cols);

    GRAY_IMAGE img_4(rows, cols);

    GRAY_IMAGE img_5(rows, cols);




#pragma HLS dataflow

    hls::AXIvideo2Mat(INPUT_STREAM1, img_01);

    hls::AXIvideo2Mat(INPUT_STREAM2, img_02);

    hls::CvtColor<HLS_RGB2GRAY>(img_01, img_1);

    hls::CvtColor<HLS_RGB2GRAY>(img_02, img_2);

    hls::AbsDiff(img_1,img_2,img_3);

    hls::Threshold(img_3,img_4,25,255,HLS_THRESH_BINARY);

    hls::Dilate(img_4,img_5);


    hls::Mat2AXIvideo(img_5, OUTPUT_STREAM);

}
