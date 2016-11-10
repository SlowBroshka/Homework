

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



int main(int argc, char* argv[]) {
    wav_hdr wavHeader;


    int headerSize = sizeof(wavHeader), filelength = 0;

    const char *filePath;
    string input;

    filePath = "/home/slowbro/Myprograming/Song1.wav";
    std::string Puth = ("/home/slowbro/ClionProjects/SignalEncoding/Outputs/chan_");
    FILE *wavFile = fopen(filePath, "r");
    FILE *wavread = fopen("/home/slowbro/ClionProjects/SignalEncoding/Outputs/1", "w");



    int Step = 10;
    int MAX = 1 << Step;
    std::vector<double> Ad;
    std::vector<double> Raz;
    std::vector<double> DatesFromFile;
    std::vector<double> TruncedPoints;
    std::vector<double> StandDeviation1;
    std::vector <double> StandDeviation2;
    std::vector<vector <double> > TruncSumStandDeviation;
    for (size_t i = 0; i < MAX; i++){
        double SinBuff = 10 *cos(0.1*(i));
        DatesFromFile.push_back(SinBuff);
        Ad.push_back(SinBuff);
    }
    Adamar(Step, Ad);

    for(size_t j = 1; j < 10; j++) {
        double FullDeviant1 = 0;
        for (size_t i = 0; i < MAX; i++) {
            double Fx1 = MyTrunc(Ad[i], j);
            double Minus = Ad[i] - Fx1;
            FullDeviant1 += (Minus * Minus);
            StandDeviation1.push_back(sqrt(FullDeviant1/MAX) * 100000000);
        }
        cout << "Full Deviant= " << FullDeviant1 << endl;
    }
    AdaptiveCreateFreaqGrapg(StandDeviation1, 2, std::string(Puth + "SKO_First.jpg"));

    vector<double> TruncDevians;
    vector<double> TruncPlusDevians;
    vector<double> RoundDevians;
    vector <vector<double> > Fin;
    for(size_t j = 3; j < 4; j++) {
        double FullDeviant1 = 0;
        double FullDeviant2 = 0;
        double FullDeviant3 = 0;
        for (size_t i = 0; i < MAX / 1; i++) {
            FullDeviant1 += ((Ad[i] - MyTrunc(Ad[i], j)) * (Ad[i] - MyTrunc(Ad[i], j)));
            FullDeviant2 += (Ad[i] - MyTruncPlus(Ad[i], j)) * (Ad[i] - MyTruncPlus(Ad[i], j));
            FullDeviant3 += (Ad[i] - MyRound(Ad[i], j)) * (Ad[i] - MyRound(Ad[i], j));

            TruncDevians.push_back(sqrt(FullDeviant1/(MAX/1)) * 100000);
            TruncPlusDevians.push_back(sqrt(FullDeviant2/(MAX/1)) * 100000);
            RoundDevians.push_back(sqrt(FullDeviant3/(MAX/1)) * 100000);

        }
    }
    cout<<"TruncDeviance= "<<TruncDevians[TruncDevians.size()/2-1]<<endl;
    cout<<"TruncPlusDeviance= "<<TruncPlusDevians[TruncPlusDevians.size()/2-1]<<endl;
    cout<<"RoundDeviance= "<<RoundDevians[RoundDevians.size()/2-1]<<endl;
    Fin.push_back(TruncDevians);
    Fin.push_back(TruncPlusDevians);
    Fin.push_back(RoundDevians);
    AdapriveCreateVectorFreqGraph(Fin, 2, std::string(Puth + "SKO3_DLINA_Trunc_Round_RoundPlus.jpg"));
    Fin.clear();
    TruncDevians.clear();
    TruncPlusDevians.clear();
    RoundDevians.clear();
    for(size_t j = 4; j < 8; j++) {
        double FullDeviant1 = 0;
        double FullDeviant2 = 0;
        double FullDeviant3 = 0;
        for (size_t i = 0; i < MAX; i++) {
            FullDeviant1 += ((Ad[i] - MyTrunc(Ad[i], j)) * (Ad[i] - MyTrunc(Ad[i], j)));
            FullDeviant2 += (Ad[i] - MyTruncPlus(Ad[i], j)) * (Ad[i] - MyTruncPlus(Ad[i], j));
            FullDeviant3 += (Ad[i] - MyRound(Ad[i], j)) * (Ad[i] - MyRound(Ad[i], j));
        }
        TruncDevians.push_back(sqrt(FullDeviant1/MAX) * 100000000);
        TruncPlusDevians.push_back(sqrt(FullDeviant2/MAX) * 100000000);
        RoundDevians.push_back(sqrt(FullDeviant3/MAX) * 100000000);
    }
    Fin.push_back(TruncDevians);
    Fin.push_back(TruncPlusDevians);
    Fin.push_back(RoundDevians);
    AdapriveCreateVectorFreqGraph(Fin, 2, std::string(Puth + "SKO3_N4-8_Trunc_Round_RoundPlus.jpg"));
    Fin.clear();
    TruncDevians.clear();
    TruncPlusDevians.clear();
    RoundDevians.clear();


    //AdapriveCreate2FreqGraph(StandDeviation1, StandDeviation2, 2, std::string(Puth + "Deviant.jpg"));
    AdaptiveCreateFreaqGrapg(DatesFromFile, 2, std::string(Puth + "inp.jpg"));

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
