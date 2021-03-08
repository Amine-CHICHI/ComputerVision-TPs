
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "OpenCV_Fct.hpp"

using namespace cv;
using namespace std;

int main()
{

    Mat source = imread("lena.jpg", 1);

    if (source.empty())
    {
        cout << "Img loading failed" << endl;
        return -1;
    }

    // display img
    namedWindow("image source", WINDOW_KEEPRATIO);
    resizeWindow("image source", source.rows, source.cols);
    imshow("image source", source);

    // number of rows and cols
    cout << "Ligne : " << source.rows << "  Colonnes : " << source.cols << endl;

    //show grayscale img using cvtColor
    Mat dest;
    cvtColor(source, dest, COLOR_RGB2GRAY);
    namedWindow("dest gray cvFunc", WINDOW_KEEPRATIO);
    resizeWindow("dest gray cvFunc", dest.rows, dest.cols);
    imshow("dest gray cvFunc", dest);
    Calc::plot_histograme(Calc::calc_histogram(dest), Scalar(145, 145, 145), "cvtColor grayscal version Histogram");
    cout << "Average of cvtColor Grayscal img : " << Calc::avg_color(dest) << endl;

    //show grayscale img using the luminosity formula
    Mat dest1;
    Vec3b pixel;
    int i, j;
    dest1.create(source.size(), CV_8UC1);

    for (i = 0; i < source.rows; i++)
    {
        for (j = 0; j < source.cols; j++)
        {
            pixel = source.at<Vec3b>(i, j);
            // dest1.at<uchar>(i, j) = (uchar)(pixel.val[0] * 0.33 + pixel.val[1] * 0.59 + pixel.val[2] * 0.11);
            dest1.at<uchar>(i, j) = (uchar)(pixel.val[0] + pixel.val[1] + pixel.val[2]) / 3;
        }
    }

    namedWindow("dest gray fromula", WINDOW_KEEPRATIO);
    resizeWindow("dest gray fromula", dest1.rows, dest1.cols);
    imshow("dest gray fromula", dest1);
    Calc::plot_histograme(Calc::calc_histogram(dest1), Scalar(145, 145, 145), "luminosity grayscal version Histogram");
    cout << "Average of Luminosity method Grayscal img : " << Calc::avg_color(dest1) << endl;

    //calculation of average colors and histograms manually
    Mat hist[3];

    for (int i = 0; i < 3; i++)
    {
        hist[i] = Mat::zeros(256, 1, CV_32F);
    }

    Vec3f moyenbgr;
    moyenbgr.val[0] = 0;
    moyenbgr.val[1] = 0;
    moyenbgr.val[2] = 0;

    for (i = 0; i < source.rows; i++)
    {
        for (j = 0; j < source.cols; j++)
        {
            pixel = source.at<Vec3b>(i, j); // mcha l pixel li kayn f coordone i j bima ana img colour
            hist[0].at<float>(pixel.val[0])++;
            hist[1].at<float>(pixel.val[1])++;
            hist[2].at<float>(pixel.val[2])++; // hist[0] is an array his[0][65]++

            moyenbgr.val[0] += pixel.val[0]; // moyenbgr.val[0] la somme de tout les intensite blue de tout les pixel de l'image
            moyenbgr.val[1] += pixel.val[1];
            moyenbgr.val[2] += pixel.val[2];
        }
    }

    cout << "MoyenB :" << moyenbgr.val[0] / (source.rows * source.cols) << endl;
    cout << "MoyenG :" << moyenbgr.val[1] / (source.rows * source.cols) << endl;
    cout << "MoyenR :" << moyenbgr.val[2] / (source.rows * source.cols) << endl;

    // Draw histograms using the calculated histogram manually
    Calc::plot_histograme(hist[0], Scalar(255, 0, 0), "Blue histogram");
    Calc::plot_histograme(hist[1], Scalar(0, 255, 0), "Green histogram");
    Calc::plot_histograme(hist[2], Scalar(0, 0, 255), "Red histogram");
    // Draw histograms using split the multichannel image to single channel arrays then draw the histograms
    Mat rgbchannel[3];
    split(source, rgbchannel);
    Calc::plot_histograme(Calc::calc_histogram(rgbchannel[0]), Scalar(255, 0, 0), "Blue splitFCT histogram");
    Calc::plot_histograme(Calc::calc_histogram(rgbchannel[1]), Scalar(0, 255, 0), "Green splitFCT histogram");
    Calc::plot_histograme(Calc::calc_histogram(rgbchannel[2]), Scalar(0, 0, 255), "Red splitFCT histogram");
    //Calculate average of colors using split functions;
    cout << "Average of Blue color using split : " << Calc::avg_color(rgbchannel[0]) << endl;
    cout << "Average of Green color using split : " << Calc::avg_color(rgbchannel[1]) << endl;
    cout << "Average of Red color using split : " << Calc::avg_color(rgbchannel[2]) << endl;

    waitKey(0);
    system("pause");
    return 0;
}
