# esptracer_PC
Wifiモジュール（ESP-12 nodeMCU）を使ってライントレーサの走行データを無線伝送する

構成
esptracer_tracer
  ・機体に搭載するWifiモジュールのプログラム
  ・マルチレシーブを想定し、APモードで利用する。

esptracer_PC　←これ。
  ・PC側に使用するWifiモジュールのプログラム
  ・PCのWifiチップ利用でもよいので必須ではないが、何となく。
