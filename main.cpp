#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>

int main() {
    // 1. 画像の読み込み
    cv::Mat img = cv::imread("../test_image.jpg");
    if (img.empty()) {
        std::cerr << "エラー: 画像が見つかりません！" << std::endl;
        return -1;
    }

    // 2. あなたが一番美しいと言った「エッジ抽出」までの処理
    cv::Mat gray_img, blur_img, edge_img;
    cv::cvtColor(img, gray_img, cv::COLOR_BGR2GRAY);
    cv::GaussianBlur(gray_img, blur_img, cv::Size(5, 5), 0);
    cv::Canny(blur_img, edge_img, 50, 150);

    // --- 🚀 ここから最終奥義：ハフ変換 ---
    std::vector<cv::Vec4i> lines;
    
    // エッジ画像の中から「長さ50ピクセル以上」の直線を数学的に検知する
    cv::HoughLinesP(edge_img, lines, 1, CV_PI / 180, 100, 50, 10);

    // 3. 元のカラー画像の上に、見つけた直線を「真っ赤な線」で描画する
    cv::Mat result_img = img.clone();
    for (size_t i = 0; i < lines.size(); i++) {
        cv::Vec4i l = lines[i];
        // BGRなので、Scalar(0, 0, 255) は「赤色」、太さは「3」
        cv::line(result_img, cv::Point(l[0], l[1]), cv::Point(l[2], l[3]), cv::Scalar(0, 0, 255), 3, cv::LINE_AA);
    }

    // 4. 最終結果を保存
    cv::imwrite("output_final.jpg", result_img);
    
    std::cout << "最終処理完了！ output_final.jpg を確認してください。" << std::endl;

    return 0;
}