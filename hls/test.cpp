#include "top.h"

#include "hls_opencv.h"

#include "iostream"



using namespace std;

using namespace cv;

const int N = 2;



int main(int argc, char** argv) {

    for (int i = 0; i < N; i++) {

       //��ȡͼ������

       IplImage* src1 = cvLoadImage(INPUT_IMAGE1);

       IplImage* src2 = cvLoadImage(INPUT_IMAGE2);

       IplImage* dst1 = cvCreateImage(cvGetSize(src1), 8,1);

       AXI_STREAM_IN src_axi1;

       AXI_STREAM_IN src_axi2;

       AXI_STREAM_OUT dst_axi;

       IplImage2AXIvideo(src1, src_axi1);

       IplImage2AXIvideo(src2, src_axi2);

       hls_counter_color1(src_axi1, src_axi2, dst_axi, src1->height,

               src1->width);

       AXIvideo2IplImage(dst_axi, dst1);

       cvSaveImage(OUTPUT_IMAGE, dst1);



       //�ͷ��ڴ�

       cvReleaseImage (&src1);

       cvReleaseImage (&src2);

       cvReleaseImage (&dst1);

    }

}
