#ifndef OpenCV_Fct
#define OpenCV_Fct
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <string>

class Calc
{
public:
    static cv::Mat calc_histogram(cv::Mat imgSrc)
    {
        cv::Mat hist;
        hist = cv::Mat::zeros(256, 1, CV_32F); // Matrix to store the frequencies of each intensity
        imgSrc.convertTo(imgSrc, CV_32F);      // Convert original matrix to a new one with the type cv_32F
        double value = 0;
        for (int i = 0; i < imgSrc.rows; i++)
        {
            for (int j = 0; j < imgSrc.cols; j++)
            {
                value = imgSrc.at<float>(i, j);                    // store the value of intensity of the pixel located at (i,j) of the source img
                hist.at<float>(value) = hist.at<float>(value) + 1; // increment the index number "value"
            }
        }
        return hist;
    }

    static void plot_histograme(cv::Mat histogram, cv::Scalar color, std::string winName)
    {
        cv::Mat histogram_image(400, 512, CV_8UC3, cv::Scalar(0, 0, 0));
        cv::Mat normalized_histogram;
        normalize(histogram, normalized_histogram, 0, 400, cv::NORM_MINMAX, -1, cv::Mat());
        for (int i = 0; i < 256; i++)
        {
            rectangle(histogram_image, cv::Point(2 * i, histogram_image.rows - normalized_histogram.at<float>(i)), cv::Point(2 * (i + 1), histogram_image.rows), color);
        }

        cv::namedWindow(winName, cv::WINDOW_GUI_NORMAL);
        cv::resizeWindow(winName, 512, 300);
        imshow(winName, histogram_image);
    }

    static int avg_color(cv::Mat img)
    {
        img.convertTo(img, CV_32F);
        float value = 0;
        for (int i = 0; i < img.rows; i++)
        {
            for (int j = 0; j < img.cols; j++)
            {
                value += img.at<float>(i, j);
            }
        }
        return value / (img.rows * img.cols);
    }
};
#endif
