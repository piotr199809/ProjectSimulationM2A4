#include "generator.h"
#include <cmath>

Generator::Generator(int kernel, double lambda, double p) : kernel_(kernel), lambda_(lambda), p_(p)
{
}

Generator::~Generator()
{
}

double Generator::Rand()
{
    int h = kernel_ / kQ;
    kernel_ = kA * (kernel_ - kQ * h) - kR * h;
    if (kernel_ < 0)
        kernel_ = kernel_ + static_cast<int>(kM);
    return kernel_ / kM;
}

double Generator::Rand(double min, double max)
{
    //return Rand() * (max - min) + min;
    return RoundToTwoDecimalPlaces(Rand() * (max - min) + min);
}

double Generator::RndExp()
{
    double k = Rand();
    //return -(1.0 / lambda_) * log(k);
    return RoundToTwoDecimalPlaces(-(1.0 / lambda_) * log(k));
}

bool Generator::RndZeroOne()
{
    double k = Rand();
    if (k < p_) return 1;
    else return 0;
}

double Generator::RoundToTwoDecimalPlaces(double number)
{
    return round(number * 100) / 100;
}



