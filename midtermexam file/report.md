# Report


## 1. Analisis Ukuran Jendela (Window) yang Ideal

Tujuan pertama adalah menentukan ukuran jendela pemindaian yang optimal. Ukuran jendela **3x3 piksel** dipilih sebagai yang paling ideal karena beberapa alasan teknis:

* **Informasi Kontekstual Minimum**: Jendela 3x3 adalah unit terkecil yang menyediakan informasi kontekstual lengkap tentang sebuah piksel. Ia mencakup piksel itu sendiri (pusat) dan delapan tetangga terdekatnya. Informasi ini cukup untuk menentukan properti dasar seperti konektivitas dan orientasi lokal.


* **Efisiensi Komputasi**: Ukuran yang lebih besar (misalnya, 5x5) akan meningkatkan kompleksitas komputasi secara eksponensial (dari 8 menjadi 24 tetangga untuk diperiksa per piksel), tanpa memberikan keuntungan informasi yang signifikan untuk deteksi segmen garis sederhana.


* **Sensitivitas terhadap Noise**: Jendela yang lebih besar lebih rentan terhadap "noise" atau fitur lain di dekatnya, yang dapat mengganggu deteksi garis tipis. Jendela 3x3 bersifat sangat lokal dan fokus, sehingga lebih robust terhadap gangguan.

## 2. Evolusi Metode : Dari Pola Kaku ke Heuristik Fleksibel

Tujuan kedua adalah mengembangkan metode yang andal untuk mengidentifikasi segmen. Proses ini melalui dua tahap evolusi.

### Tahap 1: Kegagalan Pendekatan Pencocokan Pola (Pattern Matching)

Pendekatan awal adalah mendefinisikan pola-pola 3x3 yang "ideal" untuk garis horizontal, vertikal, dan diagonal. Namun, pengujian menunjukkan bahwa metode ini **gagal total** dalam mendeteksi garis diagonal.

**Akar Masalah: Rasterisasi Garis**. Kegagalan ini bukan disebabkan oleh kesalahan logika, melainkan oleh sifat fundamental dari grafika komputer. Ketika komputer menggambar garis (terutama yang diagonal) pada grid piksel, ia menggunakan algoritma seperti **Algoritma Garis Bresenham**. Algoritma ini tidak menghasilkan garis diagonal yang sempurna, melainkan aproksimasi berbentuk "tangga" dari piksel-piksel. Akibatnya, tidak ada satu pun area 3x3 di sepanjang garis diagonal yang benar-benar cocok dengan pola "ideal" yang kaku.

### Tahap 2: Implementasi Algoritma Heuristik Berbasis Konektivitas

Menyadari keterbatasan di atas, sebuah algoritma heuristik yang lebih cerdas dan fleksibel dikembangkan. Metode ini tidak mencari pola yang sempurna, melainkan menganalisis **konektivitas** sebuah piksel dengan tetangganya.

**Logika Inti Algoritma**:
Sebuah piksel `P` dianggap sebagai kandidat segmen jika dan hanya jika dua kondisi berikut terpenuhi:
1.  **Piksel `P` harus aktif**: Piksel tersebut harus merupakan bagian dari garis yang digambar (bukan latar belakang).
2.  **Jumlah tetangga aktif `N` harus logis**: Jumlah piksel tetangga yang aktif di sekeliling `P` harus berada dalam rentang `1 <= N <= 2`.
    * **N = 1 (Satu Tetangga Aktif)**: Kondisi ini secara khas mengidentifikasi **ujung dari sebuah segmen garis**. Piksel di ujung hanya terhubung ke satu piksel lain dalam garis tersebut.
    * **N = 2 (Dua Tetangga Aktif)**: Kondisi ini secara khas mengidentifikasi **bagian tengah dari sebuah segmen garis**. Piksel di tengah terhubung ke piksel sebelumnya dan piksel sesudahnya.
    * **N > 2 (Lebih dari Dua Tetangga Aktif)**: Kondisi ini diabaikan karena biasanya menandakan **persimpangan antar garis**, garis yang lebih tebal dari 1 piksel, atau noise. Dengan mengabaikannya, algoritma menjadi fokus pada deteksi segmen garis tunggal yang bersih.

Metode heuristik ini terbukti sangat berhasil karena ia "memahami" struktur sebuah garis sederhana tanpa bergantung pada orientasi atau kesempurnaan polanya, sehingga memenuhi semua tujuan dari tugas ini.