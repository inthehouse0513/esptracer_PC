//2021.06.02
//Auther Hiroshi Yoshida
//Ardutracer受信モジュール用のプログラム

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <ESP8266WebServer.h>
#ifndef STASSID
#define STASSID "esptracer"
#define STAPSK  "esptracer"
#define num 255
#endif

//IPAddress myIP(192,168,1,101);  // 自分のIPアドレス
//IPAddress gateway(192,168,1,1);  // GW
//IPAddress subnet(255,255,255,0);  // subnet
char wifibuff[num];       //受信するデータ
unsigned int localPort = 8100;      // local port to listen on
WiFiUDP Udp;


void setup() {
  //ピンモード設定
  pinMode(LED_BUILTIN, OUTPUT);       //LED_BUILTIN pinを出力で設定
  digitalWrite(LED_BUILTIN,LOW);
  delay(100);

  Serial.begin(115200);
//  WiFi.config(myIP,gateway,subnet);
  WiFi.mode(WIFI_STA);
  WiFi.begin(STASSID, STAPSK);

  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.print("Connected at");
  Serial.println(WiFi.localIP());
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
    Udp.flush();
    Serial.print(wifibuff);
    Serial.print("...");
    Serial.println(packetSize);

    //転送後にバッファをクリア
    for(int i=0 ; i<num ; i++){
      wifibuff[i] = 0;
    }
  }


}
