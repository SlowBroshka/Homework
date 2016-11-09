

#include <iostream>
#include <string>
#include <fstream>
#include <cstdint>


#include "WavHeader.h"
#include "WavData.h"
#include "Constants.h"
#include "Graphs.h"
#include "Fixed.h"

using namespace cv;

using std::cin;
using std::cout;
using std::endl;
using std::fstream;
using std::string;
using std::vector;
//using FIXEDPOINTLIBRARY_FIXED_H;

/*
    cout << "RIFF " <<sizeof(wavHeader.RIFF)<<endl;
    cout << "ChunkSize " << sizeof(wavHeader.ChunkSize)<<endl;
    cout << "WAVE " << sizeof(wavHeader.WAVE)<<endl;
    cout << "fmt " << sizeof(wavHeader.fmt)<<endl;
    cout << "Subchunk1Size " << sizeof(wavHeader.Subchunk1Size)<<endl;
    cout << "AudioFormat " << sizeof(wavHeader.AudioFormat)<<endl;
    cout << "NumOfChan " << sizeof(wavHeader.NumOfChan)<<endl;
    cout << "SamplesPerSec " << sizeof(wavHeader.SamplesPerSec)<<endl;
    cout << "bytesPerSec " << sizeof(wavHeader.bytesPerSec)<<endl;
    cout << "blockAlign " << sizeof(wavHeader.blockAlign)<<endl;
    cout << "bitsPerSample " << sizeof(wavHeader.bitsPerSample)<<endl;
    cout << "Subchunk2ID " << sizeof(wavHeader.Subchunk2ID)<<endl;
    cout << "Subchunk2Size " << sizeof(wavHeader.Subchunk2Size)<<endl;
*/

// Function prototypes


int main(int argc, char* argv[]) {
    wav_hdr wavHeader;


    int headerSize = sizeof(wavHeader), filelength = 0;

    const char *filePath;
    string input;
    /*if (argc <= 1)
    {
        cout << "Input wave file name: ";
        cin >> input;
        cin.get();
        filePath = input.c_str();
    }
    else
    {
        filePath = argv[1];
        cout << "Input wave file name: " << filePath << endl;
    }*/

    filePath = "/home/slowbro/Myprograming/Song1.wav";
    std::string Puth = ("/home/slowbro/ClionProjects/SignalEncoding/Outputs/chan_");
    FILE *wavFile = fopen(filePath, "r");
    FILE *wavread = fopen("/home/slowbro/ClionProjects/SignalEncoding/Outputs/1", "w");

    std::vector<float> DatesFromFile;
    vector<Fixed> FixedPoints;
    int DatesFromFilecount = 0;

    if (wavFile == nullptr) {
        fprintf(stderr, "Unable to open wave file: %s\n", filePath);
        return 1;
    }

    size_t bytesRead = fread(&wavHeader, 1, headerSize, wavFile);
    FILE **ToWrite = new FILE *[wavHeader.NumOfChan];
    for (size_t i = 0; i < wavHeader.NumOfChan; i++) {
        std::string tmp = (Puth + std::to_string(i) + ".txt");
        ToWrite[i] = fopen(tmp.c_str(), "wr");
    }
    cout << "Header Read " << bytesRead << " bytes." << endl;
    if (bytesRead > 0) {
        //Read the data
        unsigned short bytesPerSample = wavHeader.bitsPerSample / 8;      //Number     of bytes per sample
        unsigned long numSamples = wavHeader.ChunkSize / bytesPerSample; //How many samples are in the wav file?
        cout << "Number of bytes per sample: " << bytesPerSample << endl;
        cout << "How many samples are in the wav file: " << numSamples << endl;


        short *buffer = new short[BUFFER_SIZE]; //Number of bits used нужен размер
        short **dates = new short *[BUFFER_SIZE];

        for (size_t i = 0; i < wavHeader.NumOfChan; i++) {
            cout << "dates= " << i << endl;
            dates[i] = new short[BUFFER_SIZE];
        }
        int *intdata = new int[BUFFER_SIZE];

        int count = 0;
        while ((bytesRead = fread(buffer, wavHeader.bitsPerSample / 8, BUFFER_SIZE, wavFile)) > 0) {

            size_t indx = 0;
            for (size_t d = 0; d < bytesRead; d += wavHeader.NumOfChan) {//(wavHeader.bitsPerSample / 8)
                for (size_t ch = 0; ch < wavHeader.NumOfChan; ch++) {
                    // for(size_t i = 0; i < (wavHeader.bitsPerSample / 8); i++){
                    dates[ch][indx] = buffer[d + ch];
                    intdata[indx] = buffer[d];
                    // }
                }
                //DatesFromFile.push_back(dates[0][indx] / 100);
                indx++;
            }
            for (size_t i = 0; i < wavHeader.NumOfChan; i++) {
                fwrite(dates[i], sizeof(dates[0][0]), indx, ToWrite[i]);
            }
            fwrite(buffer, sizeof buffer[0], bytesRead, wavread);
            cout << count++ << " Read " << " " << bytesRead << " bytes." << endl;
        }

        delete[] buffer;
        buffer = nullptr;
        filelength = getFileSize(wavFile);

        cout << "File is                    :" << filelength << " bytes." << endl;
        cout << "RIFF header                :" << wavHeader.RIFF[0] << wavHeader.RIFF[1] << wavHeader.RIFF[2]
             << wavHeader.RIFF[3] << endl;
        cout << "WAVE header                :" << wavHeader.WAVE[0] << wavHeader.WAVE[1] << wavHeader.WAVE[2]
             << wavHeader.WAVE[3] << endl;
        cout << "FMT                        :" << wavHeader.fmt[0] << wavHeader.fmt[1] << wavHeader.fmt[2]
             << wavHeader.fmt[3] << endl;
        cout << "Data size                  :" << wavHeader.ChunkSize << endl;

        // Display the sampling Rate from the header
        cout << "Sampling Rate              :" << wavHeader.SamplesPerSec << endl;
        cout << "Number of bits used        :" << wavHeader.bitsPerSample << endl;
        cout << "Number of channels         :" << wavHeader.NumOfChan << endl;
        cout << "Number of bytes per second :" << wavHeader.bytesPerSec << endl;
        cout << "Data length                :" << wavHeader.Subchunk2Size << endl;
        cout << "Audio Format               :" << wavHeader.AudioFormat << endl;
        // Audio format 1=PCM,6=mulaw,7=alaw, 257=IBM Mu-Law, 258=IBM A-Law, 259=ADPCM

        cout << "Block align                :" << wavHeader.blockAlign << endl;
        cout << "Data string                :" << wavHeader.Subchunk2ID[0] << wavHeader.Subchunk2ID[1]
             << wavHeader.Subchunk2ID[2] << wavHeader.Subchunk2ID[3] << endl;

        cout << wavHeader.Subchunk2Size / wavHeader.NumOfChan / (wavHeader.bitsPerSample / 8) << endl;

        for (size_t i = 0; i < wavHeader.NumOfChan; i++) {
            delete[] dates[i];
        }
        delete[] dates;
    }
    float fDurationSeconds = 1.f * wavHeader.Subchunk2Size / (wavHeader.bitsPerSample / 8) / wavHeader.NumOfChan /
                             wavHeader.SamplesPerSec;
    cout << "Sec: " << fDurationSeconds << endl;
    fclose(wavFile);
    fclose(wavread);
    for (size_t i = 0; i < wavHeader.NumOfChan; i++) {
        fclose(ToWrite[i]);
    }/*
    for(size_t i = 0; i < wavHeader.NumOfChan; i++){
        std::string tmp = (Puth + std::to_string(i) + ".txt");
        ToWrite[i] = fopen(tmp.c_str(), "r");
        CreateFreaqGrapg(ToWrite[i], wavHeader.bitsPerSample/8, std::string(Puth + std::to_string(i) + ".jpg"));
        fclose(ToWrite[i]);
    }*/
    delete[] ToWrite;
    int Step = 3;
    int MAX = 1 << Step;
    std::vector<float> Ad;
    std::vector<float> Raz;

    for (size_t i = 0; i < MAX; i++){
        float SinBuff = cos(0.15*(i%360)) * 4;
        DatesFromFile.push_back(SinBuff);
        Fixed Fx1(4, 13);
        Fixed Fx2(4, 4);
        Fx1.appoint(SinBuff);
        Fx2.appoint(SinBuff);
        Fixed Minus= Fx1 + Fx2;
        FixedPoints.push_back(Minus);
        //DatesFromFile.push_back((4 >= i%8 ? -i : i));
        //DatesFromFile.push_back(i);
    }

    AdaptiveCreateFreaqGrapg(DatesFromFile, 2, std::string(Puth + "inp.jpg"));
    int size = 1 << 8;
    //cout<<"Data.size()= "<<DatesFromFile.size()<<endl<<"size= "<<size<<endl;
    //cin>> size;
    for (size_t i = 0; i < DatesFromFile.size(); i++) {
        cout << DatesFromFile[i] << " ";
        Fixed Buff(4, 6);
        Buff.appoint(DatesFromFile[i]);
        cout<<Buff<<endl;
        Ad.push_back(DatesFromFile[i]);
    }
    cout<<endl<<"Fixed POints"<<endl;
    for (size_t i =0; i < FixedPoints.size(); i++){
        //cout<<FixedPoints[i]<<" ";
        cout<<FixedPoints[i]<<" ";
    }
    cout<<endl<<"Fixed POints END"<<endl;
    Adamar(Step, Ad);
    AdaptiveCreateFreaqGrapg(Ad, 2, std::string(Puth + "Adamar1.jpg"));
    /*cout<<endl;
    for(size_t i =0; i < DatesFromFile.size(); i++)
        cout<<DatesFromFile[i]<<" ";
    cout<<endl;*/
    Adamar(Step, Ad);
    AdapriveCreate2FreqGraph(DatesFromFile, Ad, 2, std::string(Puth + "AdANDinp.jpg"));
    /*for(size_t i =0; i < Ad.size(); i++){
        cout<<i<<" ";
        long long buff = DatesFromFile[i] == 0 ? 0 : Ad[i] / DatesFromFile[i];
        Raz.push_back(buff);
    }*/
    AdaptiveCreateFreaqGrapg(Ad, 2, std::string(Puth + "Adamar22.jpg"));
    //AdaptiveCreateFreaqGrapg(Raz, 2, std::string(Puth + "Raz.jpg"));


    return 0;
}
///отсчение битов чтоб было как в исходном тип и посмотрим погрешность лул
