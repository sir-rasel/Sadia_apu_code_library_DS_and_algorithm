long long firstDigitsOfFib(int n, int d = 9)
{
    ++n;
    long double temp = n * 0.20898764024997873 - 0.3494850021680094;
    //printf("%.9lf :: %.9lf\n", pow(10.0, temp - (int) (temp) + d-1),temp - (int) (temp) + d-1);
    return (long long) (pow(10.0, temp - (int) (temp) + d-1));
}
