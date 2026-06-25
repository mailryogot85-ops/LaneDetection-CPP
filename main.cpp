#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>

int main()
{
    const std::string input_path = "../test_image.jpg";
    const std::string output_path = "output_final.jpg";

    // Load input image.
    cv::Mat input_image = cv::imread(input_path);
    if (input_image.empty()) {
        std::cerr << "Error: failed to load image from " << input_path << std::endl;
        return -1;
    }

    // Preprocess the image for edge detection.
    cv::Mat gray_image;
    cv::Mat blurred_image;
    cv::Mat edge_image;

    cv::cvtColor(input_image, gray_image, cv::COLOR_BGR2GRAY);
    cv::GaussianBlur(gray_image, blurred_image, cv::Size(5, 5), 0);
    cv::Canny(blurred_image, edge_image, 50, 150);

    // Detect line segments from the edge image using probabilistic Hough transform.
    std::vector<cv::Vec4i> lines;
    cv::HoughLinesP(
        edge_image,
        lines,
        1,
        CV_PI / 180,
        100,
        50,
        10
    );

    // Draw detected line segments on the original image.
    cv::Mat result_image = input_image.clone();
    for (const auto& line : lines) {
        cv::Point start_point(line[0], line[1]);
        cv::Point end_point(line[2], line[3]);

        cv::line(
            result_image,
            start_point,
            end_point,
            cv::Scalar(0, 0, 255),
            3,
            cv::LINE_AA
        );
    }

    // Save the result image.
    cv::imwrite(output_path, result_image);

    std::cout << "Lane detection completed. Output saved to: "
              << output_path << std::endl;

    return 0;
}
