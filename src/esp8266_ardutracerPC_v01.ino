//2021.06.02
//Auther Hiroshi Yoshida
//Ardutracer受信モジュール用のプログラム
//こちらがアクセスポイント

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <ESP8266mDNS.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#ifndef STASSID
#define STASSID "esptracer"
#define STAPSK  "esptracer"
#define num 255
#endif

IPAddress myIP(192,168,1,101);  // 自分のIPアドレス
IPAddress gateway(192,168,1,1);  // GW
IPAddress subnet(255,255,255,0);  // subnet
char wifibuff[num];       //受信するデータ
unsigned int localPort = 8100;      // local port to listen on
WiFiUDP Udp;


void setup() {
  //ピンモード設定
  pinMode(LED_BUILTIN, OUTPUT);       //LED_BUILTIN pinを出力で設定
  digitalWrite(LED_BUILTIN,LOW);
  delay(100);

  WiFi.mode(WIFI_AP);   //WiFi.mode(WIFI_STA);
  WiFi.softAPConfig(myIP, WiFi.gatewayIP(), subnet); //WiFi.config(myIP,gateway,subnet);
  delay(100);
  WiFi.softAP(STASSID, STAPSK); //WiFi.begin(STASSID, STAPSK);

  Serial.begin(115200);
/*
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.print("Connected at");
  Serial.println(WiFi.localIP());
*/
  Udp.begin(localPort);

  delay(200);
  Serial.print("\n") ;
  Serial.print("esptracer START") ;
  //ビルトインＬＥＤの初期化のための消灯
  delay(200);
  digitalWrite(LED_BUILTIN,HIGH);
}


void loop() {

  //受信データ　パケットサイズの取得
  int packetSize = Udp.parsePacket();

  //udpパケット監視　正ならばif内処理の実行
  if(packetSize > 0){
    Udp.read(wifibuff, packetSize);   //データ受信
    Udp.flush();  //これを入れるとネットワークに0.0.0.0あての謎のメッセージを発信する
    Serial.print(wifibuff);
    Serial.print("..");
    Serial.println(millis());
 //   Serial.print("..");
 //   Serial.println(packetSize);

    //転送後にバッファをクリア
    for(int i=0 ; i<num ; i++){
      wifibuff[i] = 0;
    }
    delay(3);

  }
}
