//2021.06.02
//Auther Hiroshi Yoshida
//Ardutracer受信モジュール用のプログラム

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <ESP8266WebServer.h>
#include <Ticker.h>
#include <SoftwareSerial.h>

#ifndef WIFI_SSID
#define WIFI_SSID "esptracer"
#define WIFI_PSW  "esptracer"
#endif

char wifibuff[200];       //受信するデータ
IPAddress ip(192, 168, 1, 124);
IPAddress subnet(255, 255, 255, 0);
unsigned int localPort = 8100;      // local port to listen on
WiFiUDP Udp;

void setup() {


  //ピンモード設定
  pinMode(LED_BUILTIN, OUTPUT);       //LED_BUILTIN pinを出力で設定
  digitalWrite(LED_BUILTIN,LOW);
  delay(1500);

  Serial.begin(115200);
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(ip, ip, subnet);
  WiFi.softAP(WIFI_SSID, WIFI_PSW);
  Udp.begin(localPort);

  //ビルトインＬＥＤの初期化のための消灯
  digitalWrite(LED_BUILTIN,HIGH);
}


void loop() {
  //受信データ　パケットサイズの取得
  int packetSize = Udp.parsePacket();

  //udpパケット監視　正ならばif内処理の実行
  if(packetSize >0 ){
    Udp.read(wifibuff, packetSize);   //データ受信
    Serial.println(wifibuff);
    Udp.flush();
  }
}
