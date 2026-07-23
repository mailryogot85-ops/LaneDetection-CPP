#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>

int main() {
    cv::Mat img = cv::imread("../test_image.jpg");
    if (img.empty()) {
        std::cerr << "エラー: 画像が見つかりません" << std::endl;
        return -1;
    }

    // グレースケール化 → ぼかしでノイズ除去 → Cannyでエッジ検出
    cv::Mat gray_img, blur_img, edge_img;
    cv::cvtColor(img, gray_img, cv::COLOR_BGR2GRAY);
    cv::GaussianBlur(gray_img, blur_img, cv::Size(5, 5), 0);
    cv::Canny(blur_img, edge_img, 50, 150);

    // Hough変換でエッジから直線を検出
    std::vector<cv::Vec4i> lines;
    cv::HoughLinesP(edge_img, lines, 1, CV_PI / 180, 100, 50, 10);

    // 検出した直線を元画像に赤で描画
    cv::Mat result_img = img.clone();
    for (size_t i = 0; i < lines.size(); i++) {
        cv::Vec4i l = lines[i];
        cv::line(result_img, cv::Point(l[0], l[1]), cv::Point(l[2], l[3]),
                 cv::Scalar(0, 0, 255), 3, cv::LINE_AA);
    }

    cv::imwrite("output_final.jpg", result_img);
    std::cout << "処理完了。output_final.jpg を確認してください。" << std::endl;

    return 0;
}
