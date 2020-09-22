#ifndef GENERATOR_H_
#define GENERATOR_H_

class Generator
{
public:
    Generator(int kernel, double lambda, double p);
    virtual ~Generator();

    double Rand();
    double Rand(double min, double max);
    double RndExp();
    bool RndZeroOne();

    double RoundToTwoDecimalPlaces(double number);
    int get_kernel() { return kernel_; };
private:
    int kernel_;
    double lambda_;
    double p_;
    const double kM = 2147483647.0;
    static const int kA = 16807;
    static const int kQ = 127773;
    static const int kR = 2836;
};

#endif
