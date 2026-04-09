// Library yang digunakan
#include <WiFi.h>                 
#include <WiFiClientSecure.h>    
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>         
#include "DHT.h"             

// Deklarasi pin yang digunakan
#define LED_A 25       
#define LED_B 26    
#define LED_C 27       
#define LED_UTAMA 14   
#define MQ2 34         
#define DHTPIN 32      
#define DHTTYPE DHT22  

// Membuat objek sensor DHT
DHT dht(DHTPIN, DHTTYPE);

// Konfigurasi WiFi
const char* ssid = "Redmi Note 13";     
const char* password = "okokokok"; 

// Token bot Telegram
#define BOT_TOKEN "8211640550:AAF63M35bwfXJP1LhUUiie78ki13F51Vqvg"
WiFiClientSecure client;
UniversalTelegramBot bot(BOT_TOKEN, client);

// Variabel untuk delay pengecekan pesan Telegram
unsigned long lastTimeBotRan;
int botRequestDelay = 1000;
int gasThreshold = 2000;

// Chat ID Telegram masing-masing anggota
String anggotaA = "1356061122";
String anggotaB = "6455872589";
String anggotaC = "6157923018";

// SETUP
void setup() {

  Serial.begin(115200); 

  pinMode(LED_A, OUTPUT);
  pinMode(LED_B, OUTPUT);
  pinMode(LED_C, OUTPUT);
  pinMode(LED_UTAMA, OUTPUT);

  dht.begin();

  // Menghubungkan ESP32 ke WiFi
  WiFi.begin(ssid, password);
  client.setInsecure();
  Serial.print("Connecting WiFi");

  // Menunggu sampai WiFi terhubung
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("Connected");
}

// FUNGSI MEMBACA PESAN TELEGRAM
void handleNewMessages(int numNewMessages) {

  // Membaca semua pesan baru
  for (int i = 0; i < numNewMessages; i++) {

    // Mengambil chat id pengirim
    String chat_id = bot.messages[i].chat_id;

    // Mengambil teks pesan
    String text = bot.messages[i].text;

    Serial.println(text); // Menampilkan pesan ke serial monitor

    // PERINTAH /start
    if (text == "/start") {

      // Mengirim daftar command ke pengguna
      bot.sendMessage(chat_id,
      "Smart House Bot\n\n"
      "/ledA_on\n"
      "/ledA_off\n"
      "/ledB_on\n"
      "/ledB_off\n"
      "/ledC_on\n"
      "/ledC_off\n"
      "/led_utama_on\n"
      "/led_utama_off\n"
      "/cek_suhu\n"
      "/cek_gas", "");
    }

    // LED A
    if (text == "/ledA_on") {

      // Hanya anggota A yang boleh menyalakan
      if (chat_id == anggotaA) {
        digitalWrite(LED_A, HIGH);
        bot.sendMessage(chat_id, " LED A NYALA", "");
      } 
      else {
        bot.sendMessage(chat_id,
        " AKSES DITOLAK!\nLED hanya anggota A yang bisa akses", "");
      }
    }

    if (text == "/ledA_off") {

      // Hanya anggota A yang boleh mematikan
      if (chat_id == anggotaA) {
        digitalWrite(LED_A, LOW);
        bot.sendMessage(chat_id, " LED A DIMATIKAN", "");
      } 
      else {
        bot.sendMessage(chat_id,
        " AKSES DITOLAK!\nLED hanya anggota A yang bisa akses", "");
      }
    }

    // LED B
    if (text == "/ledB_on") {

      if (chat_id == anggotaB) {
        digitalWrite(LED_B, HIGH);
        bot.sendMessage(chat_id, " LED B NYALA", "");
      } 
      else {
        bot.sendMessage(chat_id,
        " AKSES DITOLAK!\nLED hanya anggota B yang bisa akses", "");
      }
    }

    if (text == "/ledB_off") {

      if (chat_id == anggotaB) {
        digitalWrite(LED_B, LOW);
        bot.sendMessage(chat_id, " LED B DIMATIKAN", "");
      } 
      else {
        bot.sendMessage(chat_id,
        " AKSES DITOLAK!\nLED hanya anggota B yang bisa akses", "");
      }
    }

    // LED C
    if (text == "/ledC_on") {

      if (chat_id == anggotaC) {
        digitalWrite(LED_C, HIGH);
        bot.sendMessage(chat_id, " LED C NYALA", "");
      } 
      else {
        bot.sendMessage(chat_id,
        " AKSES DITOLAK!\nLED hanya anggota C yang bisa akses", "");
      }
    }

    if (text == "/ledC_off") {

      if (chat_id == anggotaC) {
        digitalWrite(LED_C, LOW);
        bot.sendMessage(chat_id, " LED C DIMATIKAN", "");
      } 
      else {
        bot.sendMessage(chat_id,
        " AKSES DITOLAK!\nLED hanya anggota C yang bisa akses", "");
      }
    }

    // LED UTAMA (RUANG TAMU)
    if (text == "/led_utama_on") {

      digitalWrite(LED_UTAMA, HIGH);
      bot.sendMessage(chat_id,
      " Lampu Ruang Tamu NYALA", "");
    }

    if (text == "/led_utama_off") {

      digitalWrite(LED_UTAMA, LOW);
      bot.sendMessage(chat_id,
      " Lampu Ruang Tamu DIMATIKAN", "");
    }

    // CEK SUHU DAN KELEMBAPAN
    if (text == "/cek_suhu") {

      float suhu = dht.readTemperature();
      float hum = dht.readHumidity();     

      String msg = " Suhu : " + String(suhu) + " C\n";
      msg += " Kelembapan : " + String(hum) + " %";

      bot.sendMessage(chat_id, msg, "");
    }

    // CEK SENSOR GAS
    if (text == "/cek_gas") {

      int gasValue = analogRead(MQ2);

      String msg = " Sensor Gas\n";
      msg += "Nilai : " + String(gasValue);

      bot.sendMessage(chat_id, msg, "");
    }
  }
}

// LOOP PROGRAM
void loop() {

  // Membaca nilai sensor gas
  int gasValue = analogRead(MQ2);

  // Jika nilai gas melebihi batas
  if (gasValue > gasThreshold) {

    // Kirim pesan peringatan ke Telegram
    bot.sendMessage("-1003834815290",
    " PERINGATAN GAS!\n"
    " terndeteksi kebocoran gas!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!", "");
  }

  // Mengecek pesan baru dari Telegram setiap delay tertentu
  if (millis() - lastTimeBotRan > botRequestDelay) {

    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

    // Jika ada pesan baru
    while (numNewMessages) {

      handleNewMessages(numNewMessages);

      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }

    lastTimeBotRan = millis();
  }
}