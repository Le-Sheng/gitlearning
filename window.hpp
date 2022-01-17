#pragma once

#include <vector>
#include <algorithm>

class window
{
public:
    window() : _n(0) {}
    window(int n) : _n(n)
    {
        v.resize(n * n);
    }

    window(const window &w) : _n(w._n), v(w.v) {}

    ~window() 
    {
        
    }
    void setwindow(const int n)
    {
        _n = n;
    }
    void get_window_from(int x, int y, const std::vector<std::vector<int>> &m)
    {
        int row = m.size();
        int col = m[0].size();
        int index = 0;
        for (int i = 0; i < _n && i + x < row; i++)
        {
            for (int j = 0; j < _n && j + y < col; j++)
                v[index++] = m[i + x][j + y];
        }
    }

    int get_mid()
    {
        std::vector<int> count(_n * _n, 0);
        //int res=0;
        for (int i = 0; i < _n * _n; i++)
        {
            for (int j = i + 1; j < _n * _n; j++)
            {
                if (v[i] >= v[j])
                    count[i]++;
                else
                    count[j]++;
            }

            if (count[i] == (_n * _n) / 2)
            {
                return v[i];
            }
        }
        //std::sort(v.begin(),v.end());

        return 0;

        // return -1;
    }

    int get_average() const
    {
        int sum = 0;
        for (int num : v)
            sum += num;
        return sum / (_n * _n);
    }

    int get_gauss(const double sigma) const
    {
        const double PI=3.1415926;
        int center=_n/2;
        std::vector<double> w(_n*_n);
        double g=2*PI*sigma*sigma;
        
        int index=0;
        double sum=0;
        for(int i=0;i<_n;i++)
        {
            double x=pow(i-center,2);
            for(int j=0;j<_n;j++)
            {
                double y=pow(j-center,2);
                w[index]=exp(-(x+y)/(2*sigma*sigma))/g;
                sum+=w[index];
                index++;
            }
        }
        double res=0;
        for(int i=0;i<_n*_n;i++)
        {
            res+=(w[i]*v[i]/sum);
        }

        return (int)res;
        
    }

private:
    int _n;
    std::vector<int> v;
};