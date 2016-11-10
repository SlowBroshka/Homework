//
// Created by slowbro on 09.11.16.
//
#include "Fixed.h"

vector<int> swap(vector<int> &V);
bool AbsBigger(const Fixed & Fx1, const Fixed & Fx2);
Fixed AbsPlus(Fixed const &Fx1, Fixed const &Fx2);
Fixed AbsMinus(const Fixed &Fx1, const Fixed &Fx2);


size_t Fixed::GetIntegerDec() const{
    return Fixed::integer_dec;
}
size_t Fixed::GetFractionalDec()const {
    return Fixed::fractional_dec;
}
bool Fixed::GetSign() const{
    if (Fixed::Sign){
        return true;
    }else{
        return false;
    }
}

int Fixed::GetIntegerByIndex(size_t const &Num) const{
    return integer[Num];
}
int Fixed::GetFractionalByIndex(size_t const &Num) const{
    return fractional[Num];
}
void Fixed::resize(size_t const &I, size_t const &F) {
    vector<int> IBuff;
    vector<int> FBuff;

    if (this->integer_dec <= I) {
        for (size_t i = 0; i < I - this->integer_dec; i++) {
            IBuff.push_back(0);
        }
        for(size_t i = I - this->integer_dec, k = 0; i < I; i++){
            IBuff.push_back(this->integer[k++]);
        }
    }else{
        size_t k = 0;
        while((k < this->integer_dec) && (this->integer[k] == 0)){
            k++;
        }
        for(size_t i = 0; i < I; i++){
            IBuff.push_back(this->integer[k + i]);
        }/*
        if (this->integer[I] >= 5){
            //++
        }*/
    }
    if(this->fractional_dec < F) {
        for (size_t i = 0; i < this->fractional_dec; i++) {
            FBuff.push_back(this->fractional[i]);
        }
        for(size_t i = this->fractional_dec; i < F; i++){
            FBuff.push_back(0);
        }

    }else{//F <= frac_dec
        for(size_t i = 0; i < F; i++){
            FBuff.push_back(this->fractional[i]);
        }
    }
    this->integer_dec = I;
    this->fractional_dec = F;
    this->integer.clear();
    this->fractional.clear();
    this->integer = IBuff;
    this->fractional = FBuff;
}
void Fixed::print() const {
    std::cout << (Fixed::Sign ? "+" : "-");
    for (size_t i = 0; i < this->integer.size(); i++) {
        std::cout << this->integer[i];
    }
    std::cout<<".";
    for (size_t i = 0; i < this->fractional.size(); i++) {
        std::cout << this->fractional[i];
    }
}

Fixed & Fixed::operator=(const Fixed & Fx) {
    if (this == &Fx) {
        return *this;
    }
    this->fractional_dec = Fx.GetFractionalDec();
    this->integer_dec = Fx.GetIntegerDec();
    this->Sign = Fx.Sign;
    this->integer.clear();
    this->fractional.clear();
    for (size_t i = 0; i < integer_dec; i++){
        this->integer.push_back(Fx.integer[i]);
    }
    for (size_t i = 0; i < fractional_dec; i++){
        this->fractional.push_back(Fx.fractional[i]);
    }
    return *this;
}
Fixed operator+(const Fixed &Fx1, const Fixed &Fx2){
    Fixed Buff;
    if (Fx1.GetSign() && Fx2.GetSign()){
        Buff = AbsPlus(Fx1, Fx2);
        Buff.Sign = true;
    }else{
        if (!Fx1.GetSign() && !Fx2.GetSign()){
            Buff = AbsPlus(Fx1, Fx2);
            Buff.Sign = false;
        }else{
            if(Fx1.GetSign() && !Fx2.GetSign()){
                if (AbsBigger(Fx1, Fx2)){
                    Buff = AbsMinus(Fx1, Fx2);
                    Buff.Sign = true;
                }else{
                    if(AbsBigger(Fx2, Fx1)){
                        Buff = AbsMinus(Fx2, Fx1);
                        Buff.Sign = false;
                        return Buff;
                    }else{
                        Buff.resize(Fx1.GetIntegerDec() >= Fx2.GetIntegerDec() ? Fx1.GetIntegerDec() : Fx2.GetIntegerDec(),
                                    Fx1.GetFractionalDec() >= Fx2.GetFractionalDec() ? Fx1.GetFractionalDec() : Fx2.GetFractionalDec());
                    }
                }
            }else {
                if (!Fx1.GetSign() && Fx2.GetSign()){
                    if (AbsBigger(Fx1, Fx2)){
                        Buff = AbsMinus(Fx1, Fx2);
                        Buff.Sign = false;
                    }else{
                        if (AbsBigger(Fx2, Fx1)){
                            Buff = AbsMinus(Fx2, Fx1);
                            Buff.Sign = true;
                        }else{
                            Buff.resize(Fx1.GetIntegerDec() >= Fx2.GetIntegerDec() ? Fx1.GetIntegerDec() : Fx2.GetIntegerDec(),
                                        Fx1.GetFractionalDec() >= Fx2.GetFractionalDec() ? Fx1.GetFractionalDec() : Fx2.GetFractionalDec());
                        }
                    }
                }
            }
        }
    }
    return Buff;
}
Fixed operator-(const Fixed &Fx1, const Fixed &Fx2) {///Dodelat
    Fixed Buff;
    if (Fx1.GetSign() && Fx2.GetSign()){
        if(AbsBigger(Fx1, Fx2)){
            Buff = AbsMinus(Fx1, Fx2);
            Buff.Sign = true;
        }else{
            if (AbsBigger(Fx2, Fx1)){
                Buff = AbsMinus(Fx2, Fx1);
                Buff.Sign = false;
            }else{
                Buff.resize(Fx1.GetIntegerDec() >= Fx2.GetIntegerDec() ? Fx1.GetIntegerDec() : Fx2.GetIntegerDec(),
                            Fx1.GetFractionalDec() >= Fx2.GetFractionalDec() ? Fx1.GetFractionalDec() : Fx2.GetFractionalDec());
            }
        }
    }else{
        if (!Fx1.GetSign() && !Fx2.GetSign()){
            Buff = AbsPlus(Fx1, Fx2);
            Buff.Sign = false;
        }else{
            if (!Fx1.GetSign() && Fx2.GetSign()){
                if (AbsBigger(Fx1, Fx2)){
                    Buff = AbsMinus(Fx1, Fx2);
                    Buff.Sign = false;
                }else{
                    if (AbsBigger(Fx2, Fx1)){
                        Buff = AbsMinus(Fx2, Fx1);
                        Buff.Sign = true;
                    }else{
                        Buff.resize(Fx1.GetIntegerDec() >= Fx2.GetIntegerDec() ? Fx1.GetIntegerDec() : Fx2.GetIntegerDec(),
                                    Fx1.GetFractionalDec() >= Fx2.GetFractionalDec() ? Fx1.GetFractionalDec() : Fx2.GetFractionalDec());
                    }
                }
            }else{
                if (Fx1.GetSign() && !Fx2.GetSign()){
                    if (AbsBigger(Fx1, Fx2)){
                        Buff = AbsMinus(Fx1, Fx2);
                        Buff.Sign = true;
                    }else{
                        if (AbsBigger(Fx2, Fx1)){
                            Buff = AbsMinus(Fx2, Fx1);
                            Buff.Sign = false;
                        }else{
                            Buff.resize(Fx1.GetIntegerDec() >= Fx2.GetIntegerDec() ? Fx1.GetIntegerDec() : Fx2.GetIntegerDec(),
                                        Fx1.GetFractionalDec() >= Fx2.GetFractionalDec() ? Fx1.GetFractionalDec() : Fx2.GetFractionalDec());
                        }
                    }
                }
            }
        }
    }
    return Buff;
}
bool operator >(const Fixed &Fx1, const Fixed &Fx2){
    if (Fx1.GetSign() && Fx2.GetSign()){
        return AbsBigger(Fx1, Fx2);
    }else{
        if (Fx1.GetSign() && !Fx2.GetSign()){
            return true;
        }else{
            if(!Fx1.GetSign() && Fx2.GetSign()){
                return false;
            }else{
                return !AbsBigger(Fx1, Fx2);
            }
        }
    }
}
bool operator < (const Fixed &Fx1, const Fixed &Fx2) {
    if (Fx2 > Fx1){
        return true;
    }else{
        return false;
    }
}
std::ostream &operator<<(std::ostream & os, Fixed const & Fx){
    os << (Fx.Sign ? "+" : "-");
    for (size_t i = 0; i < Fx.integer.size(); i++) {
        os << Fx.integer[i];
    }
    os<<".";
    for (size_t i = 0; i < Fx.fractional.size(); i++) {
        os << Fx.fractional[i];
    }
    return os;
}

Fixed AbsMinus(const Fixed &Fx1, const Fixed &Fx2){
    size_t MaxFractional =Fx1.GetFractionalDec() >= Fx2.GetFractionalDec() ? Fx1.GetFractionalDec() : Fx2.GetFractionalDec();
    size_t MaxInteger = Fx1.GetIntegerDec() >= Fx2.GetIntegerDec() ? Fx1.GetIntegerDec() : Fx2.GetIntegerDec();


    Fixed BFx1 = Fx1;
    Fixed BFx2 = Fx2;

    BFx1.resize(MaxInteger, MaxFractional);
    BFx2.resize(MaxInteger, MaxFractional);
    vector<int> IBuff;
    vector<int> FBuff;

    for(size_t i = MaxFractional-1; i > 0; i--){
        int k = BFx1.GetFractionalByIndex(i) - BFx2.GetFractionalByIndex(i);
        if (k >= 0){
            FBuff.push_back(k);
        }else{
            FBuff.push_back(10 + k);
            BFx1.Fixed::fractional[i-1]--;
        }
    }
    if (BFx1.GetFractionalByIndex(0) - BFx2.GetFractionalByIndex(0) >= 0){
        FBuff.push_back(BFx1.GetFractionalByIndex(0) - BFx2.GetFractionalByIndex(0));
    }else{
        FBuff.push_back(BFx1.GetFractionalByIndex(0) - BFx2.GetFractionalByIndex(0) + 10);
        BFx1.Fixed::integer[MaxInteger-1] -= 1;
    }

    for(size_t i = 0; i < MaxInteger; i++){
        int k = BFx1.GetIntegerByIndex(MaxInteger - 1 - i) - BFx2.GetIntegerByIndex(MaxInteger - 1 - i);
        if (k >= 0){
            IBuff.push_back(k);
        }else{
            IBuff.push_back(10 + k);
            BFx1.Fixed::integer[MaxInteger - 1 - i - 1]--;
        }
    };
    Fixed Returned(MaxInteger, MaxFractional, swap(IBuff), swap(FBuff));
    return Returned;
}
Fixed AbsPlus(const Fixed &Fx1, const Fixed &Fx2){//NO SIGN
    size_t MaxInteger_dec = Fx1.integer_dec <= Fx2.integer_dec ? Fx2.integer_dec : Fx1.integer_dec;
    size_t MaxFractional_dec = Fx1.fractional_dec <= Fx2.fractional_dec ? Fx2.fractional_dec : Fx1.fractional_dec;
    size_t MinInteger_dec = Fx1.integer_dec >= Fx2.integer_dec ? Fx2.integer_dec : Fx1.integer_dec;
    size_t MinFractional_dec = Fx1.fractional_dec >= Fx2.fractional_dec ? Fx2.fractional_dec : Fx1.fractional_dec;
    cout<<Fx1<<" "<<Fx2<<endl;
    Fixed FxBuff = Fx1;
    vector<int> FBuff;
    vector<int> IBuff;

    for(size_t i = 0; i < MinFractional_dec; i++){
        FBuff.push_back(Fx2.fractional[i] + Fx1.fractional[i]);
    }
    if (MinFractional_dec != MaxFractional_dec){
        for(size_t i = MinFractional_dec; i < MaxFractional_dec; i++){
            FBuff.push_back(Fx1.fractional_dec == MaxFractional_dec ? Fx1.fractional[i] : Fx2.fractional[i]);
        }
    }
    for(size_t i = MaxFractional_dec-1; i > 0; i--){
        if (FBuff[i] > 9){
            FBuff[i-1] = FBuff[i-1] + FBuff[i] / 10;
            FBuff[i] = FBuff[i] % 10;
        }
    }
    if (FBuff[0] > 9){
        FxBuff.integer[FxBuff.GetIntegerDec() - 1]  += 1;
        FBuff[0] = FBuff[0] % 10;
    }

    if (MinInteger_dec != MaxInteger_dec){
        for(size_t i = 0; i < MaxInteger_dec -  MinInteger_dec; i++){
            IBuff.push_back(Fx1.integer_dec == MaxInteger_dec ? FxBuff.integer[i] : Fx2.integer[i]);
        }
    }
    for(size_t i = 1; i < MinInteger_dec+1 ; i++){
        IBuff.push_back(Fx2.integer[Fx2.GetIntegerDec() - i] + FxBuff.integer[FxBuff.GetIntegerDec() - i]);
    }

    for(size_t i = 0; i < MaxInteger_dec-1; i++){
        if (IBuff[i] > 9){
            IBuff[i+1] = IBuff[i+1] + IBuff[i] / 10;
            IBuff[i] = IBuff[i] % 10;
        }
    }
    if (IBuff[MaxInteger_dec - 1] > 9){
        IBuff.push_back(IBuff[MaxInteger_dec - 1] / 10);
        IBuff[MaxInteger_dec - 1] %= 10;
        MaxInteger_dec++;
    }
    IBuff = swap(IBuff);
    Fixed Returned(MaxInteger_dec, MaxFractional_dec, IBuff, FBuff);

    return Returned;
}
bool AbsBigger(const Fixed &Fx1, const Fixed &Fx2){//mdoule > module
    Fixed Buff1(Fx1);
    Fixed Buff2(Fx2);
    size_t MaxInteger_dec = Fx1.integer_dec >= Fx2.integer_dec ? Fx1.integer_dec : Fx2.integer_dec;
    size_t MinInteger_dec = Fx1.integer_dec < Fx2.integer_dec ? Fx1.integer_dec : Fx2.integer_dec;
    size_t MaxFractional_dec = Fx1.fractional_dec >= Fx2.fractional_dec ? Fx1.fractional_dec : Fx2.fractional_dec;
    size_t MinFractional_dec = Fx1.fractional_dec < Fx2.fractional_dec ? Fx1.fractional_dec : Fx2.fractional_dec;
    Buff1.resize(MaxInteger_dec, MaxFractional_dec);
    Buff2.resize(MaxInteger_dec, MaxFractional_dec);
    for (size_t i = 0; i < MaxInteger_dec; i++) {
        if (Buff1.GetIntegerByIndex(i) > Buff2.GetIntegerByIndex(i)) {
            return true;
        }else {
            if (Buff1.GetIntegerByIndex(i) < Buff2.GetIntegerByIndex(i)) {
                return false;
            }
        }
    }
    for(size_t i = 0; i < MaxFractional_dec; i++){
        if (Buff1.GetFractionalByIndex(i) > Buff2.GetFractionalByIndex(i)){
            return true;
        }else{
            if (Buff1.GetFractionalByIndex(i) < Buff2.GetFractionalByIndex(i)) {
                return false;
            }
        }
    }
    return false;
}

vector<int> swap(vector<int> &V){
    for (size_t i = 0; i < V.size() / 2; i++){
        int buff = V[i];
        V[i] = V[V.size()-1 -i];
        V[V.size()-1 -i] = buff;
    }
    return V;
}
