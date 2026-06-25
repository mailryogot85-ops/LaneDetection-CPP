# LaneDetection-CPP

OpenCVとC++を用いて、道路画像から白線候補を検出するための画像処理プロトタイプです。

現在は静止画像を対象とした学習・実験用の実装であり、グレースケール変換、Gaussian Blur、Cannyエッジ検出、Hough変換を用いた古典的な白線検知パイプラインを構成しています。

---

## Overview

このプロジェクトでは、車載カメラ風の道路画像に対して、以下の処理を行います。

1. 入力画像の読み込み
2. グレースケール変換
3. Gaussian Blurによるノイズ低減
4. Cannyエッジ検出
5. Hough変換による直線候補の検出
6. 検出した線分の描画
7. 結果画像の出力

目的は、完全な自動運転システムを作ることではなく、画像処理によって道路上の線分をどのように抽出できるのかを理解し、パラメータ調整や検出結果の変化を観察することです。

---

## Motivation

このプロジェクトは、C++とOpenCVを用いて実世界に近い画像を処理する練習として制作しました。

白線検知では、Cannyエッジ検出やHough変換のパラメータによって結果が大きく変化します。
そのため、単に白線を検出するだけでなく、

* どのパラメータが検出結果に影響するのか
* 誤検出はどこで発生するのか
* 入力画像の条件によって結果がどのように変化するのか
* 手作業でのパラメータ調整にはどのような限界があるのか

を確認することを重視しています。

このパラメータ調整の難しさが、後に制作した `SBPE (Set-Based Parameter Explorer)` の開発動機にもつながっています。

---

## Demo

![Lane Detection Demo](output_final.jpg)

---

## Features

* C++による画像処理パイプラインの実装
* OpenCVを用いた画像読み込み・前処理・描画
* Gaussian Blurによるノイズ低減
* Cannyエッジ検出による輪郭抽出
* Hough変換による直線候補の検出
* 検出結果の画像出力
* パラメータ変更による検出結果の比較・検証

---

## Tech Stack

* C++20
* OpenCV 4.x
* CMake

---

## Build

```bash
mkdir build
cd build
cmake ..
make
./LaneDetection
```

または、環境によっては以下の形式でもビルドできます。

```bash
cmake -S . -B build
cmake --build build
./build/LaneDetection
```

---

## Input / Output

デフォルトでは、以下の画像を入力として読み込みます。

```text
../test_image.jpg
```

処理結果は以下のファイルとして出力されます。

```text
output_final.jpg
```

---

## Processing Flow

現在の実装では、主に以下の流れで白線候補を検出しています。

```text
Input Image
    ↓
Grayscale Conversion
    ↓
Gaussian Blur
    ↓
Canny Edge Detection
    ↓
Hough Line Transform
    ↓
Line Drawing
    ↓
Output Image
```

---

## Parameters

検出結果は、主に以下のパラメータに影響されます。

### Gaussian Blur

* kernel size

### Canny Edge Detection

* lower threshold
* upper threshold

### Hough Transform

* rho
* theta
* threshold
* minLineLength
* maxLineGap

これらの値を変更することで、検出される線分の数や位置、誤検出の量が変化します。

---

## Current Limitations

現在の実装には、以下の制約があります。

* 静止画像のみを対象としている
* 動画入力やリアルタイム処理には未対応
* 道路環境や画像条件によって検出結果が大きく変化する
* 曲線道路や影、夜間画像、雨天画像への対応は限定的
* パラメータ調整は手動で行う必要がある
* 現時点ではROIによる道路領域の絞り込みは未実装

このため、現時点では実用的な白線検知システムというより、画像処理パイプラインとパラメータ依存性を理解するためのプロトタイプとして位置づけています。

---

## Related Project

### SBPE: Set-Based Parameter Explorer

LaneDetection-CPPの開発中に、Cannyエッジ検出やHough変換のパラメータ調整を手作業で行う非効率さを感じました。

その課題をもとに、2次元パラメータ空間を探索・可視化するC++製プロトタイプとして、`SBPE` を制作しました。

SBPEでは、唯一の最適値だけを見るのではなく、許容できるパラメータ領域全体を可視化することを目指しています。

Repository:
https://github.com/mailryogot85-ops/sbpe-terminal

---

## Future Work

今後は以下の改善を予定しています。

* ROI（関心領域）の設計
* 動画入力への対応
* フレーム間での検出結果の安定化
* パラメータ探索の自動化
* SBPEとの連携
* Canny/Houghパラメータの探索・可視化
* 検出結果の定量評価
* CSV出力や比較実験の整備
* 曲線道路やノイズの多い画像への対応

---

## Goal

このプロジェクトの目的は、OpenCVを使って白線を検出することだけではありません。

画像処理パイプラインを自分で実装し、パラメータ調整・誤検出・入力画像の条件変化といった問題を観察することで、実世界の画像を扱うソフトウェアの難しさを理解することを目的としています。

将来的には、SBPEと組み合わせることで、手作業に頼っているパラメータ探索をより体系的に行えるようにすることを目指しています。
