//
// Created by slowbro on 21.10.16.
//
#ifndef SIGNALENCODING_GRAPHS_H
#define SIGNALENCODING_GRAPHS_H
#include <cv.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/core/types_c.h>
#include <iostream>
#include <string>
#include <fstream>
#include <cstdint>
#include "Constants.h"


int getFileSize(FILE* inFile);

void CreateFreaqGrapg(FILE *inputData, size_t size, std::string filename);
void CreateFreaqGrapg(std::vector<short>&Data, size_t size, std::string filename);
template <typename T>
void AdaptiveCreateFreaqGrapg(std::vector<T>&Data, size_t size, std::string filename)//Draw graph from inputdata to filename with datasizeperbit
{
    std::cout<<"Graph Start"<<std::endl;

    IplImage *NewGraph = cvCreateImage(CvSize(XSize, YSize), IPL_DEPTH_8U, 1);
    cvSet(NewGraph, CvScalar(255));

    T MAXSIZEofDATA = abs(Data[0]);
    size_t lgh = Data.size();
    for (size_t i = 0; i < lgh; i++){
        if (MAXSIZEofDATA < abs(Data[i])){
            MAXSIZEofDATA = abs(Data[i]);
        }
    }
    if (lgh >= XSize) {
        size_t BlockSize = lgh / XSize;
        for (size_t i = 0; i < XSize; i++) {
            float MAX = 0;
            float MIN = 0;
            float MAXmean = 0;
            float MINmean = 0;
            size_t MAXmeancount = 0;
            size_t MINmeancount = 0;
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
                } else if (0 > Data[i * BlockSize + j]) {
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

            cvLine(NewGraph, CvPoint(i, YSize / 2), CvPoint(i, YSize / 2 - YMAX), CvScalar(128), 1, 1, 0);
            cvLine(NewGraph, CvPoint(i, YSize / 2), CvPoint(i, YSize / 2 - YMIN), CvScalar(128), 1, 1, 0);
            cvLine(NewGraph, CvPoint(i, YSize / 2), CvPoint(i, YSize / 2 - YMAXmean), CvScalar(0), 1, 1, 0);
            cvLine(NewGraph, CvPoint(i, YSize / 2), CvPoint(i, YSize / 2 - YMINmean), CvScalar(0), 1, 1, 0);
        }
    }else{
        cvLine(NewGraph, CvPoint(0, YSize / 2), CvPoint(XSize, YSize / 2), CvScalar(0), 1, 1, 0);
        float BlockSize = float(XSize) / float(lgh);
        for(size_t i = 0; i < lgh; i++){
            T Y0 = int((float(Data[i]) * float(YSize/2)) / float(MAXSIZEofDATA));
            T Y1 = int((float(Data[i+1]) * float(YSize/2)) / float(MAXSIZEofDATA));
            int X0 = int(i * BlockSize);
            int X1 = int((i+1) * BlockSize);
            //std::cout<<"X0= "<<X0<<" "<<"Y0= "<<Y0<<std::endl;
            //std::cout<<"X1= "<<X0<<" "<<"Y1= "<<Y0<<std::endl;
            cvLine(NewGraph, CvPoint(X0, YSize / 2), CvPoint(X0, YSize / 2 - Y0), CvScalar(128), 1, 1, 0);
            cvLine(NewGraph, CvPoint(X1, YSize / 2), CvPoint(X1, YSize / 2 - Y1), CvScalar(128), 1, 1, 0);

            cvLine(NewGraph, CvPoint(X0, YSize / 2 - Y0), CvPoint(X1, YSize / 2 - Y1), CvScalar(0), 1, 1, 0);
        }
    }
    cvSaveImage(filename.c_str(), NewGraph);
    cvReleaseImage(&NewGraph);
    std::cout<<"Graph END"<<std::endl;
}

template <typename T>
void CreateGraphOnImage(IplImage *img, std::vector<T>&Data, T MAXSIZEofDATA, size_t size, CvScalar Color){
    size_t lgh = Data.size();
    if (lgh >= XSize) {
        size_t BlockSize = lgh / XSize;
        for (size_t i = 0; i < XSize; i++) {
            T MAX = 0;
            T MIN = 0;
            //T MAXmean = 0;
            //T MINmean = 0;
            //size_t MAXmeancount = 0;
            //size_t MINmeancount = 0;
            for (size_t j = 0; j < BlockSize; j++) {
                if (MAX < Data[i * BlockSize + j]) {
                    MAX = Data[i * BlockSize + j];
                }
                if (MIN > Data[i * BlockSize + j]) {
                    MIN = Data[i * BlockSize + j];
                }/*
                if (0 < Data[i * BlockSize + j]) {
                    MAXmean += Data[i * BlockSize + j];
                    MAXmeancount++;
                } else if (0 > Data[i * BlockSize + j]) {
                    MINmean += Data[i * BlockSize + j];
                    MINmeancount++;
                }*/
            }
            //MAXmean = MAXmean / MAXmeancount;
            //MINmean = MINmean / MINmeancount;
            int YMAX = int((float(MAX) * float(YSize / 2) / float(MAXSIZEofDATA)));
            int YMIN = int((float(MIN) * float(YSize / 2) / float(MAXSIZEofDATA)));
            //int YMAXmean = int((float(MAXmean) * float(YSize / 2) / float(MAXSIZEofDATA)));
            //int YMINmean = int((float(MINmean) * float(YSize / 2) / float(MAXSIZEofDATA)));

            cvLine(img, CvPoint(i, YSize / 2), CvPoint(i, YSize / 2 - YMAX), Color, 1, 1, 0);
            cvLine(img, CvPoint(i, YSize / 2), CvPoint(i, YSize / 2 - YMIN), Color, 1, 1, 0);
            //cvLine(img, CvPoint(i, YSize / 2), CvPoint(i, YSize / 2 - YMAXmean), CvScalar(255), 1, 1, 0);
            //cvLine(img, CvPoint(i, YSize / 2), CvPoint(i, YSize / 2 - YMINmean), CvScalar(255), 1, 1, 0);
        }
    }else{
        cvLine(img, CvPoint(0, YSize / 2), CvPoint(XSize, YSize / 2), Color, 1, 1, 0);
        float BlockSize = float(XSize) / float(lgh);
        for(size_t i = 0; i < lgh; i++){
            T Y0 = int((float(Data[i]) * float(YSize/2)) / float(MAXSIZEofDATA));
            T Y1 = int((float(Data[i+1]) * float(YSize/2)) / float(MAXSIZEofDATA));
            int X0 = int(i * BlockSize);
            int X1 = int((i+1) * BlockSize);
            //std::cout<<"X0= "<<X0<<" "<<"Y0= "<<Y0<<std::endl;
            //std::cout<<"X1= "<<X0<<" "<<"Y1= "<<Y0<<std::endl;
            cvLine(img, CvPoint(X0, YSize / 2), CvPoint(X0, YSize / 2 - Y0), Color, 1, 1, 0);
            cvLine(img, CvPoint(X1, YSize / 2), CvPoint(X1, YSize / 2 - Y1), Color, 1, 1, 0);
            cvLine(img, CvPoint(X0, YSize / 2 - Y0), CvPoint(X1, YSize / 2 - Y1), Color, 1, 1, 0);
        }
    }
}

template <typename T1, typename T2>
void AdapriveCreate2FreqGraph(std::vector<T1>&Data1, std::vector<T2>&Data2, size_t size, std::string filename)
{
    std::cout<<"AdapriveCreate2FreqGraph START"<<std::endl;

    IplImage *NewGraph = cvCreateImage(CvSize(XSize, YSize), IPL_DEPTH_8U, 3);
    cvSet(NewGraph, CvScalar(255, 255, 255));
    size_t lgh1 = Data1.size();
    size_t lgh2 = Data2.size();
    T1 MAXSIZEofData1 = Data1[0];
    T2 MAXSIZEofData2 = Data2[0];
    for (size_t i = 0; i < lgh1; i++){
        if (MAXSIZEofData1 < abs(Data1[i])){
            MAXSIZEofData1 = abs(Data1[i]);
        }
    }
    for (size_t i = 0; i < lgh2; i++){
        if (MAXSIZEofData2 < abs(Data2[i])){
            MAXSIZEofData2 = abs(Data2[i]);
        }
    }
    if (MAXSIZEofData1 > MAXSIZEofData2){
        //T1 MAXSIZEofDATA = MAXSIZEofData1;
        CreateGraphOnImage(NewGraph, Data1, MAXSIZEofData1, size, CvScalar(255, 0, 0));
        CreateGraphOnImage(NewGraph, Data2, MAXSIZEofData1, size, CvScalar(0, 0, 255));


    }else{
        //T2 MAXSIZEOFDATA = MAXSIZEofData2;
        CreateGraphOnImage(NewGraph, Data2, MAXSIZEofData2, size, CvScalar(255, 0, 0));
        CreateGraphOnImage(NewGraph, Data1, MAXSIZEofData2, size, CvScalar(0, 0, 255));

    }
    cvSaveImage(filename.c_str(), NewGraph);
    cvReleaseImage(&NewGraph);
    std::cout<<"AdapriveCreate2FreqGraph END"<<std::endl;
}

template <typename T>
void Adamar(int AStepsNum, std::vector<T>&AData)
{
    unsigned long DataSz;

    DataSz = 1 << AStepsNum;

    unsigned long Block = 1;
    for(size_t i = 0; i < AStepsNum; i++){
        unsigned long Pair = Block;
        Block += Block;
        for(size_t j = 0; j < DataSz; j+=Block){
            for(size_t jj = 0; jj < Pair; jj++){
                unsigned long Ind0 = j + jj;
                unsigned long Ind1 = Ind0 + Pair;
                T Item0 = AData[Ind0];
                T Item1 = AData[Ind1];
                AData[Ind0] = Item0 + Item1;
                AData[Ind1] = Item0 - Item1;
            }
        }
    }
}

#endif //SIGNALENCODING_GRAPHS_H
