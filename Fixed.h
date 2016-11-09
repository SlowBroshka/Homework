//
// Created by slowbro on 09.11.16.
//

#ifndef SIGNALENCODING_FIXED_H
#define SIGNALENCODING_FIXED_H


#include <iostream>
#include <stdio.h>
#include <cstddef>
#include <math.h>
#include <cmath>
#include <vector>

using std::cout;
using std::endl;
using std::vector;
//template <size_t I, size_t F>
class Fixed;

//template  <size_t I, size_t F>
class Fixed{
public:
    size_t fractional_dec;
    size_t integer_dec;
    size_t total_dec;

public:
    bool Sign = true;                   //false - minus || true-plus
    vector<int> fractional;
    vector<int> integer;

public:
    Fixed(){
        fractional_dec = 1;
        integer_dec = 1;
        total_dec = 2;
        Sign = true;
    }
    Fixed(const size_t int_dec, const size_t frac_dec, const vector<int> &integer_, const vector<int> &fractional_){
        this->integer_dec = int_dec;
        this->fractional_dec = frac_dec;
        this->total_dec = this->integer_dec + this->fractional_dec;
        for (size_t i = 0; i < this->integer_dec; i++){
            integer.push_back(integer_[i]);
        }
        for (size_t i = 0; i < this->fractional_dec; i++){
            fractional.push_back(fractional_[i]);
        }
        Sign = true;
    }
    Fixed(const int i, const int f){
        integer_dec = static_cast<size_t >(abs(i));
        fractional_dec = static_cast<size_t>(abs(f));
        total_dec = integer_dec + fractional_dec;
        Sign = true;
    }
    Fixed(const size_t i, const size_t f){
        integer_dec = i;
        fractional_dec = f;
        total_dec = integer_dec + fractional_dec;
        Sign = true;
    }
    Fixed(const int N){
        fractional_dec = static_cast<size_t>(abs(N));
        integer_dec = static_cast<size_t>(abs(N));
        total_dec = integer_dec + fractional_dec;
        Sign = true;
    }
    Fixed(const size_t N){
        fractional_dec = N;
        integer_dec = N;
        total_dec = integer_dec + fractional_dec;
        Sign = true;
    }
    Fixed(const Fixed& Fx){
        integer_dec = Fx.integer_dec;
        fractional_dec = Fx.fractional_dec;
        Sign = Fx.Sign;
        integer.clear();
        fractional.clear();
        for (size_t i = 0; i < fractional_dec; i++){
            fractional.push_back(Fx.fractional[i]);
        }
        for (size_t i = 0; i < integer_dec; i++){
            integer.push_back(Fx.integer[i]);
        }

    }

public:
    size_t GetIntegerDec() const ;
    size_t GetFractionalDec() const;
    bool GetSign() const;
    void resize(size_t const &I, size_t const &F);
    void print()const ;
    int GetIntegerByIndex(size_t const &Num) const;
    int GetFractionalByIndex(size_t const &Num) const;

    Fixed & operator=(const Fixed & Fx);

    void appoint(float fNumeric){
        float fNumericInteger;
        float fNumericFloat = std::modf(fNumeric,&fNumericInteger);
        PushIntegerPath(fNumeric, integer_dec);
        PushFractionalPath(fNumericFloat, fractional_dec);
        PushSignPath(fNumeric);
    }
    void appoint(int i, int f){
        PushIntegerPath(i, integer_dec);
        PushFractionalPath(f, fractional_dec);
        PushSignPath(i);
    }
    void appoint(char* const s[1], size_t i, size_t f){
        PushIntegerPath(static_cast<int>(i), integer_dec);
        PushFractionalPath(static_cast<int>(f), fractional_dec);
        if (s[0] == "+"){
            this->Sign = true;
        }else{
            this->Sign = false;
        }
    }
private:

    unsigned int GetDecbyNum(float const fNumeric, signed int const num){
        float integer;
        float fractional = std::modf(fNumeric, &integer);
        //static_cast<size_t>(abs(static_cast<int>(trunc(fNumeric))));
        unsigned int Num=0;
        if (num > 0){
            return GetDecbyNum(static_cast<size_t>(integer), num);
        }else{
            for(size_t i = 0; i < abs(num); i++){
                fractional *= 10;
                size_t buff = static_cast<size_t>(trunc(fractional));
                Num = buff % 10;
            }
        }
        return abs(Num);
    }
    unsigned int GetDecbyNum(size_t const Numeric, signed int const num){
        size_t integer = Numeric;
        unsigned int Num;
        if (num > 0){
            size_t NumofDigits = GetSizeofNumeric(integer);
            if (num >= NumofDigits){
                return integer % 10;
            }else{
                for(size_t i = 0; i < NumofDigits - num; i++){
                    integer = integer / 10;
                    //cout<<"integer= "<<integer<<endl;
                }
                return integer % 10;
            }
        }else{
            return 0;
        }
    }
    size_t GetSizeofNumeric(size_t const Numeric){
        size_t Size = 0;
        size_t Num = Numeric;
        while(Num != 0){
            Num = Num / 10;
            Size++;
        }
        return Size;
    }
    size_t GetSizeofNumericAfterPoint(float const Numeric){
        size_t Size = 0;
        float Num = Numeric;
        float buff;
        while(std::modf(Num, &buff) != 0){
            Size++;
            Num *= 10;
        }
        return Size;
    }
    void PushIntegerPath(int const INumeric, size_t Nums){
        size_t Numeric = static_cast<size_t>(abs(INumeric));
        size_t NumSize = (Nums < GetSizeofNumeric(Numeric)) ? Nums : GetSizeofNumeric(Numeric);
        size_t NumofDigits = GetSizeofNumeric(INumeric);
        if (NumSize == integer_dec){
            for (size_t i = 0; i < integer_dec; i++){
                integer.push_back(GetDecbyNum(Numeric, i+1));
            }
        }else if(NumSize > integer_dec){
            size_t diff = integer_dec - NumSize;
            for (size_t i = 0; i < integer_dec; i++){
                integer.push_back(GetDecbyNum(Numeric, i+1));
            }
        }else if(NumSize < integer_dec){
            for(size_t i = 0; i < integer_dec - NumSize; i++){
                integer.push_back(0);
            }
            for(size_t i = 1; i <= NumSize; i++){
                integer.push_back(GetDecbyNum(Numeric, i));
            }
        }
    }
    void PushIntegerPath(float const fNumeric, size_t const Nums){
        int Numeric = static_cast<int>(abs(static_cast<int>(trunc(fNumeric))));
        PushIntegerPath(Numeric, Nums);
    }
    void PushFractionalPath(int const INumeric, size_t const Nums_){
        size_t Nums = GetSizeofNumeric(static_cast<size_t>(INumeric)) < Nums_ ? GetSizeofNumeric(static_cast<size_t>(INumeric)) : Nums_;
        if (Nums == fractional_dec){
            for(size_t i =0; i < Nums; i++){
                fractional.push_back(GetDecbyNum(static_cast<size_t>(abs(INumeric)), (i+1)));
            }
        }else if (fractional_dec < Nums){
            for(size_t i = 0; i < fractional_dec; i++){
                fractional.push_back(GetDecbyNum(static_cast<size_t>(abs(INumeric)), (i+1)));
            }
        }else if(fractional_dec > Nums){
            for(size_t i =0; i < Nums; i++){
                fractional.push_back(GetDecbyNum(static_cast<size_t>(abs(INumeric)), (i+1)));
            }
            for(size_t i = Nums; i < fractional_dec; i++){
                fractional.push_back(0);
            }
        }
    }
    void PushFractionalPath(float const fNumeric, size_t Nums){
        size_t NumSize = (Nums < GetSizeofNumericAfterPoint(fNumeric)) ? Nums : GetSizeofNumericAfterPoint(fNumeric);
        if (NumSize == fractional_dec){
            for(int i = 0; i < NumSize; i++){
                fractional.push_back(GetDecbyNum(fNumeric, -(i+1)));
            }
        }else if(NumSize > fractional_dec){
            for(size_t i = 0; i< fractional_dec; i++){
                fractional.push_back(GetDecbyNum(fNumeric, -(i+1)));
            }
        }else if(NumSize < fractional_dec){
            for(size_t i =0; i < NumSize; i++){
                fractional.push_back(GetDecbyNum(fNumeric, -(i+1)));
            }
            for(size_t i = NumSize; i < fractional_dec; i++){
                fractional.push_back(0);
            }
        }
    }
    template<typename T>
    void PushSignPath(T const Numeric){
        if (Numeric >= 0){
            Sign = true;
        }else if(Numeric < 0){
            Sign = false;
        }
    }

};

std::ostream &operator<<(std::ostream & os, Fixed const & Fx);
bool operator < (const Fixed &Fx1, const Fixed &Fx2);
bool operator >(const Fixed &Fx1, const Fixed &Fx2);
Fixed operator - (Fixed const &Fx1, Fixed const &Fx2);
Fixed operator+(const Fixed &Fx1, const Fixed &Fx2);


#endif //SIGNALENCODING_FIXED_H
