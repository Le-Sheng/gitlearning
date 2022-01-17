#pragma once
#include "window.hpp"
#include "Image.hpp"

class filter
{
public:
    int _n;
    window _w;

    filter() : _n(0), _w(_n){};
    filter(const int n) : _n(n), _w(_n){};
    void setwindow(const int n)
    {
        _n = n, _w.setwindow(n);
    }
    virtual std::shared_ptr<Image> filtering(const Image &image) = 0;
    virtual ~filter(){};
};

class median_filter : public filter
{
public:
    //using filter::filter;

    median_filter() : filter(){};
    median_filter(const int n) : filter(n){};
    ~median_filter(){};

    std::shared_ptr<Image> filtering(const Image &image) override
    {
        //std::vector<std::vector<int>> res;
        std::shared_ptr<Image> median_res = std::make_shared<Image>(image);
        std::vector<std::vector<int>> &R = median_res->_R;
        std::vector<std::vector<int>> &G = median_res->_G;
        std::vector<std::vector<int>> &B = median_res->_B;
        for (int i = 0; i < median_res->_row - _n + 1; i++)
        {
            for (int j = 0; j < median_res->_col - _n + 1; j++)
            {
                _w.get_window_from(i, j, R);
                R[i + 1][j + 1] = _w.get_mid();
                median_res->_image.at<cv::Vec3b>(i + 1, j + 1)[0] = R[i + 1][j + 1];

                _w.get_window_from(i, j, G);
                G[i + 1][j + 1] = _w.get_mid();
                median_res->_image.at<cv::Vec3b>(i + 1, j + 1)[1] = G[i + 1][j + 1];

                _w.get_window_from(i, j, B);
                B[i + 1][j + 1] = _w.get_mid();
                median_res->_image.at<cv::Vec3b>(i + 1, j + 1)[2] = B[i + 1][j + 1];

                //_image.at<uchar>(i+1,j+1)=res[i+1][j+1];
                median_res->_gray[i + 1][j + 1] = p * median_res->_R[i + 1][j + 1] + q * median_res->_G[i + 1][j + 1] + t * median_res->_B[i + 1][j + 1];
            }
        }

        //cv::applyColorMap(_image, _image,COLORMAP_AUTUMN);

        return median_res;
    }
};

class average_filter : public filter
{
public:
    //using filter::filter;

    average_filter() : filter(){};
    average_filter(const int n) : filter(n){};
    ~average_filter(){};

    std::shared_ptr<Image> filtering(const Image &image) override
    {
        //std::vector<std::vector<int>> res;
        std::shared_ptr<Image> average_res = std::make_shared<Image>(image);
        std::vector<std::vector<int>> &R = average_res->_R;
        std::vector<std::vector<int>> &G = average_res->_G;
        std::vector<std::vector<int>> &B = average_res->_B;
        for (int i = 0; i < average_res->_row - _n + 1; i++)
        {
            for (int j = 0; j < average_res->_col - _n + 1; j++)
            {
                _w.get_window_from(i, j, R);
                R[i + 1][j + 1] = _w.get_average();
                average_res->_image.at<cv::Vec3b>(i + 1, j + 1)[0] = R[i + 1][j + 1];

                _w.get_window_from(i, j, G);
                G[i + 1][j + 1] = _w.get_average();
                average_res->_image.at<cv::Vec3b>(i + 1, j + 1)[1] = G[i + 1][j + 1];

                _w.get_window_from(i, j, B);
                B[i + 1][j + 1] = _w.get_average();
                average_res->_image.at<cv::Vec3b>(i + 1, j + 1)[2] = B[i + 1][j + 1];

                //_image.at<uchar>(i+1,j+1)=res[i+1][j+1];
                average_res->_gray[i + 1][j + 1] = p * average_res->_R[i + 1][j + 1] + q * average_res->_G[i + 1][j + 1] + t * average_res->_B[i + 1][j + 1];
            }
        }

        //cv::applyColorMap(_image, _image,COLORMAP_AUTUMN);

        return average_res;
    }
};

class gauss_filter : public filter
{
public:
    gauss_filter() : filter(){};
    gauss_filter(const int n, const double sigma) : filter(n), _sigma(sigma) {}
    ~gauss_filter() {}

    std::shared_ptr<Image> filtering(const Image &image) override
    {
        //std::vector<std::vector<int>> res;
        std::shared_ptr<Image> gauss_res = std::make_shared<Image>(image);
        std::vector<std::vector<int>> &R = gauss_res->_R;
        std::vector<std::vector<int>> &G = gauss_res->_G;
        std::vector<std::vector<int>> &B = gauss_res->_B;
        for (int i = 0; i < gauss_res->_row - _n + 1; i++)
        {
            for (int j = 0; j < gauss_res->_col - _n + 1; j++)
            {
                _w.get_window_from(i, j, R);
                R[i + 1][j + 1] = _w.get_gauss(_sigma);
                gauss_res->_image.at<cv::Vec3b>(i + 1, j + 1)[0] = R[i + 1][j + 1];

                _w.get_window_from(i, j, G);
                G[i + 1][j + 1] = _w.get_gauss(_sigma);
                gauss_res->_image.at<cv::Vec3b>(i + 1, j + 1)[1] = G[i + 1][j + 1];

                _w.get_window_from(i, j, B);
                B[i + 1][j + 1] = _w.get_gauss(_sigma);
                gauss_res->_image.at<cv::Vec3b>(i + 1, j + 1)[2] = B[i + 1][j + 1];

                //_image.at<uchar>(i+1,j+1)=res[i+1][j+1];
                gauss_res->_gray[i + 1][j + 1] = p * gauss_res->_R[i + 1][j + 1] + q * gauss_res->_G[i + 1][j + 1] + t * gauss_res->_B[i + 1][j + 1];
            }
        }

        //cv::applyColorMap(_image, _image,COLORMAP_AUTUMN);

        return gauss_res;
    }

private:
    double _sigma;
};