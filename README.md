# posttest2-praktikum-iot-unmul-2026
Posttest2-praktikum-iot-unmul-2026

# Nama Kelompok:
Kelompok 9
# Anggota:
1.	Ari Fullah (2309106085)
2.	Fathir Januarta (2309106057)
3.	Muhamad Rayhan AT (23091006050)

# Judul Studi Kasus
Smart Home Berbasis ESP32 dengan Monitoring Suhu, Kelembapan (DHT22) dan Deteksi Gas (MQ-2) Berbasis Telegram

# Deskripsi
Sistem ini merupakan implementasi Smart Home menggunakan ESP32 yang terintegrasi dengan bot Telegram untuk mengontrol perangkat dan memonitor kondisi lingkungan secara real-time.
Setiap anggota kelompok memiliki akses terbatas terhadap LED masing-masing (LED A, B, dan C), sehingga hanya dapat mengontrol perangkat miliknya sendiri. Selain itu, tersedia satu LED utama (lampu ruang tamu) yang dapat dikontrol oleh seluruh anggota.
Sistem juga dilengkapi dengan sensor MQ-2 untuk mendeteksi kebocoran gas dan sensor DHT22 untuk membaca suhu serta kelembapan. Jika terdeteksi gas melebihi ambang batas, sistem secara otomatis mengirimkan notifikasi peringatan ke grup Telegram. Seluruh anggota juga dapat mengecek suhu dan kelembapan kapan saja melalui perintah bot. 

# Pembagian Tugas
- Ari Fullah: Perancangan Sistem, Pemrograman dan Platform IoT
- Muhamad Rayhan AT: Membuat Board Schematic dan perancangan perangkat
- Fathir Januarta: Perancangan Sistem, Pemrograman dan Platform IoT

# Komponen yang Digunakan
1.	ESP32 (mikrokontroler utama) 
2.	Sensor DHT22 (suhu & kelembapan) 
3.	Sensor MQ-2 (deteksi gas) 
4.	LED (4 buah) 
•	LED A 
•	LED B 
•	LED C 
•	LED Utama (ruang tamu) 
5.	Breadboard
6.	Kabel jumper
7.	Sumber daya kabel type c

# List Komen:
1.	/ledA_on → Menyalakan LED A (khusus anggota A) 
2.	/ledA_off → Mematikan LED A (khusus anggota A) 
3.	/ledB_on → Menyalakan LED B (khusus anggota B) 
4.	/ledB_off → Mematikan LED B (khusus anggota B) 
5.	/ledC_on → Menyalakan LED C (khusus anggota C) 
6.	/ledC_off → Mematikan LED C (khusus anggota C)
7.	/led_utama_on → Menyalakan lampu ruang tamu (semua anggota bisa) 
8.	/led_utama_off → Mematikan lampu ruang tamu
9.	/cek_suhu → Menampilkan: 
•	Suhu (°C) 
•	Kelembapan (%) 
10.	/cek_gas → Menampilkan: 
•	Nilai sensor gas (MQ-2)


# Gambar Board Schematic
