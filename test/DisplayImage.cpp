#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;

int main(int argc, char **argv)
{

    Mat image[6];

    std::string original_link = "/home/bhoopesh/CGT_Project/Graphs/original.png";

    Mat original = imread(original_link, IMREAD_GRAYSCALE);

    if (original.empty())
    {
        std::cout << "Image File "
                  << "Not Found" << std::endl;

        std::cin.get();
        return -1;
    }

    imshow("Window Name", original);

    waitKey(2000);

    for (int i = 0; i <= 5; i++)
    {

        std::string link = "/home/bhoopesh/CGT_Project/Graphs/img" + std::to_string(i) + ".png";

        image[i] = imread(link, IMREAD_GRAYSCALE);

        if (image[i].empty())
        {
            std::cout << "Image File "
                      << "Not Found" << std::endl;

            std::cin.get();
            return -1;
        }

        imshow("Window Name", image[i]);

        // Wait for any keystroke
        waitKey(1000);
    }

    std::string final_link = "/home/bhoopesh/CGT_Project/Graphs/final.png";

    Mat final = imread(final_link, IMREAD_GRAYSCALE);

    if (final.empty())
    {
        std::cout << "Image File "
                  << "Not Found" << std::endl;

        std::cin.get();
        return -1;
    }

    imshow("Window Name", final);

    waitKey(2000);

    return 0;
}