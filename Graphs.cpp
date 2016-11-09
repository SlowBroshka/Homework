//
// Created by slowbro on 21.10.16.
//
#include "Graphs.h"

int getFileSize(FILE* inFile)
{
    int fileSize = 0;
    fseek(inFile, 0, SEEK_END);

    fileSize = ftell(inFile);

    fseek(inFile, 0, SEEK_SET);
    return fileSize;
}

void CreateFreaqGrapg(FILE *inputData, size_t size, std::string filename)//Draw graph from inputdata to filename with datasizeperbit
{
    int const MAXSIZEofDATA = 32767;
    int ReadBytes;
    short *Buffer = new short[BUFFER_SIZE];
    std::vector<short> Data;
    //std::cout<<"CreateFreqGraph  "<< sizeof(inputData)<<std::endl;
    while((ReadBytes = fread(Buffer, size, BUFFER_SIZE, inputData)) > 0){
        //std::cout<<"Read Bytes= "<<ReadBytes<<std::endl;
        for (size_t i = 0; i < ReadBytes; i++){
            Data.push_back(Buffer[i]);
        }
    }
    size_t BlockSize = Data.size() / XSize;
    //std::cout<<"Data.size() = "<<Data.size()<<std::endl;
    IplImage *NewGraph = cvCreateImage(CvSize(XSize, YSize), IPL_DEPTH_8U, 1);
    cvSet(NewGraph, CvScalar(255));
    int StartPointX = 0;
    int StartPointY = 0;
    for (size_t i = 0; i < XSize; i++) {
        float MAX = 0;
        float MIN = 0;
        float MAXmean = 0;
        float MINmean = 0;
        int MAXmeancount = 0;
        int MINmeancount = 0;
        for (size_t j = 0; j < BlockSize; j++) {
            if (MAX < Data[i * BlockSize + j]) {
                MAX = Data[i * BlockSize + j];
            }
            if (MIN > Data[i * BlockSize + j]) {
                MIN = Data[i * BlockSize + j];
            }
            if (0 < Data[i * BlockSize + j]) {
                MAXmean += Data[i * BlockSize + j];
                MAXmeancount++;
            }else if (0 > Data[i * BlockSize + j]) {
                MINmean += Data[i * BlockSize + j];
                MINmeancount++;
            }
        }
        MAXmean = MAXmean / MAXmeancount;
        MINmean = MINmean / MINmeancount;
        int YMAX = int((float(MAX) * float(YSize / 2) / float(MAXSIZEofDATA)));
        int YMIN = int((float(MIN) * float(YSize / 2) / float(MAXSIZEofDATA)));
        int YMAXmean = int((float(MAXmean) * float(YSize / 2) / float(MAXSIZEofDATA)));
        int YMINmean = int((float(MINmean) * float(YSize / 2) / float(MAXSIZEofDATA)));

        cvLine(NewGraph, CvPoint(i, YSize / 2), CvPoint(i, YSize / 2 + YMAX), CvScalar(128), 1, 1, 0);
        cvLine(NewGraph, CvPoint(i, YSize / 2), CvPoint(i, YSize / 2 + YMIN), CvScalar(128), 1, 1, 0);
        cvLine(NewGraph, CvPoint(i, YSize / 2), CvPoint(i, YSize / 2 + YMAXmean), CvScalar(0), 1, 1, 0);
        cvLine(NewGraph, CvPoint(i, YSize / 2), CvPoint(i, YSize / 2 + YMINmean), CvScalar(0), 1, 1, 0);
    }
    cvSaveImage(filename.c_str(), NewGraph);
    cvReleaseImage(&NewGraph);
}
void CreateFreaqGrapg(std::vector<short>&Data, size_t size, std::string filename)//Draw graph from inputdata to filename with datasizeperbit
{
    std::cout<<"Graph Start"<<std::endl;
    int const MAXSIZEofDATA = 20;
    int ReadBytes;
    size_t BlockSize = Data.size() / XSize;
    /*if (XSize <= Data.size()) {
        BlockSize = Data.size() / XSize;
    }*/
    //std::cout<<"Data.size() = "<<Data.size()<<std::endl;
    IplImage *NewGraph = cvCreateImage(CvSize(XSize, YSize), IPL_DEPTH_8U, 1);
    cvSet(NewGraph, CvScalar(255));
    int StartPointX = 0;
    int StartPointY = 0;
    for (size_t i = 0; i < XSize; i++) {
        float MAX = 0;
        float MIN = 0;
        float MAXmean = 0;
        float MINmean = 0;
        int MAXmeancount = 0;
        int MINmeancount = 0;
        for (size_t j = 0; j < BlockSize; j++) {
            if (MAX < Data[i * BlockSize + j]) {
                MAX = Data[i * BlockSize + j];
            }
            if (MIN > Data[i * BlockSize + j]) {
                MIN = Data[i * BlockSize + j];
            }
            if (0 < Data[i * BlockSize + j]) {
                MAXmean += Data[i * BlockSize + j];
                MAXmeancount++;
            }else if (0 > Data[i * BlockSize + j]) {
                MINmean += Data[i * BlockSize + j];
                MINmeancount++;
            }
        }
        MAXmean = MAXmean / MAXmeancount;
        MINmean = MINmean / MINmeancount;
        int YMAX = int((float(MAX) * float(YSize / 2) / float(MAXSIZEofDATA)));
        int YMIN = int((float(MIN) * float(YSize / 2) / float(MAXSIZEofDATA)));
        int YMAXmean = int((float(MAXmean) * float(YSize / 2) / float(MAXSIZEofDATA)));
        int YMINmean = int((float(MINmean) * float(YSize / 2) / float(MAXSIZEofDATA)));

        cvLine(NewGraph, CvPoint(i, YSize / 2), CvPoint(i, YSize / 2 + YMAX), CvScalar(128), 1, 1, 0);
        cvLine(NewGraph, CvPoint(i, YSize / 2), CvPoint(i, YSize / 2 + YMIN), CvScalar(128), 1, 1, 0);
        cvLine(NewGraph, CvPoint(i, YSize / 2), CvPoint(i, YSize / 2 + YMAXmean), CvScalar(0), 1, 1, 0);
        cvLine(NewGraph, CvPoint(i, YSize / 2), CvPoint(i, YSize / 2 + YMINmean), CvScalar(0), 1, 1, 0);
    }
    cvSaveImage(filename.c_str(), NewGraph);
    cvReleaseImage(&NewGraph);
    std::cout<<"Graph END"<<std::endl;
}
