#pragma once

#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>
#include <memory>
#include "window.hpp"

extern const double p = 0.299, q = 0.587, t = 0.114;

class Image
{
public:
    friend class filter;
    friend class median_filter;
    friend class average_filter;
    friend class gauss_filter;
    Image() = delete;
    Image(const std::string &s)
    {
        _image = cv::imread(s);

        //cv::cvtColor(_image, _image, CV_BGR2GRAY);
        //cv::waitKey(0);
        _row = _image.rows;
        _col = _image.cols;
        _R.resize(_row);
        _G.resize(_row);
        _B.resize(_row);
        _gray.resize(_row);

        for (int i = 0; i < _row; i++)
        {
            _R[i].resize(_col);
            _G[i].resize(_col);
            _B[i].resize(_col);
            _gray[i].resize(_col);
            for (int j = 0; j < _col; j++)
            {
                _R[i][j] = _image.at<cv::Vec3b>(i, j)[0];
                _G[i][j] = _image.at<cv::Vec3b>(i, j)[1];
                _B[i][j] = _image.at<cv::Vec3b>(i, j)[2];
                _gray[i][j] = p * _R[i][j] + q * _G[i][j] + t * _B[i][j];
            }
        }
    }

    Image(const Image &img) : _R(img._R), _G(img._G), _B(img._B), _gray(img._gray), _row(img._row), _col(img._col), _image(img._image)
    {
    }

    cv::Mat getimage() const
    {
        return _image;
    }

    void setimage(cv::Mat image)
    {
        _image = image;
    }

    void setimage(const std::string &s)
    {
        _image = cv::imread(s);
    }

    void show()
    {
        cv::imshow("show()", _image);
    }
    void show(const std::string &s)
    {
        cv::imshow(s, _image);
        cv::imwrite(s + ".jpg", _image);
    }
    std::shared_ptr<std::vector<std::vector<int>>> getR()
    {
        return std::make_shared<std::vector<std::vector<int>>>(_R);
    }
    std::shared_ptr<std::vector<std::vector<int>>> getG()
    {
        return std::make_shared<std::vector<std::vector<int>>>(_G);
    }
    std::shared_ptr<std::vector<std::vector<int>>> getB()
    {
        return std::make_shared<std::vector<std::vector<int>>>(_B);
    }
    std::shared_ptr<std::vector<std::vector<double>>> getgray()
    {
        return std::make_shared<std::vector<std::vector<double>>>(_gray);
    }

private:
    std::vector<std::vector<int>> _R;
    std::vector<std::vector<int>> _G;
    std::vector<std::vector<int>> _B;
    std::vector<std::vector<double>> _gray;
    int _row;
    int _col;
    cv::Mat _image;
};