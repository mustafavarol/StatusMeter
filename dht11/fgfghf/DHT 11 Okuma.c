/*
Merhaba Arkada�lar;

CCS C ile PIC16F877A kullanarak DHT11'den s�cakl�k ve nem bilgisi okuyup 
16x2 LCD ekrana yazd�raca��z.

Kullanca��m�z Malzemeler:
- PIC16F877A
- DHT 11
- 16x2 LCD

Farkl� soru ve istekleriniz i�in yorum yazabilir yada 
www.izmirteknikdestek.com sitesinden bize ula�abilirsiniz.

Video Sonunda kanal�m�za abone olarak destek olabilirsiniz.

*/


#include <16F877A.h> // Kullanacagimiz pic'in kutuphanesini ekliyoruz.

#FUSES NOWDT                    //Watch dog timer kapatiyoruz
#FUSES NOBROWNOUT               //Brownout Reset kapat�yoruz
#FUSES NOLVP                    //Dusuk voltaj programlama kapal�

#use delay(crystal=4000000) // Osilator frekans� ayarlan�yor.

#define dht11 PIN_C0
#include "DHT11.C"

//LCD Ekran Ba�lant� tan�mlamalar�
#define LCD_RS_PIN PIN_B7
#define LCD_RW_PIN PIN_B6
#define LCD_ENABLE_PIN PIN_B5
#define LCD_DATA4 PIN_B4
#define LCD_DATA5 PIN_B3
#define LCD_DATA6 PIN_B2
#define LCD_DATA7 PIN_B1

#include "lcd.c" // LCD k�t�phanesinin eklenmesi

int sicaklik,nem,eskinem,eskisicaklik; // Kullan�lan de�i�kenlerin tan�mlanmas�


void main()
{
  
   lcd_init();  // LCD'nin �al��mas� haz�rlanmas�
   
   printf(lcd_putc,"Izmir"); // Ekrana belirtilen yaz�lar�n g�nderilmesi
   printf(lcd_putc,"\nTeknik Destek"); // Yaz�n�n ba��na eklenen \n komutu bir alt sat�ra ge�mesi i�indir.
   delay_ms(1000);
   printf(lcd_putc,"\f");
   printf(lcd_putc,"DHT 11");
   printf(lcd_putc,"\nOKUMA ORNEGI");
   delay_ms(1000);


printf(lcd_putc,"\f"); // Ekran� silme komutu
 while(TRUE)
   {

read_dht(); // DHT 11'in okumas� i�in gereken fonksiyon.
delay_ms(100);
   
sicaklik = dht_dat[2]; // dht_dat[2] de�i�kenini bize s�cakl�k bilgisini verir bu bilgiyi sicaklik olarak tan�mlad���m�z de�i�kene at�yoruz
nem = dht_dat[0]; // dht_dat[0] de�i�kenini bize nem bilgisini verir bu bilgiyi nem olarak tan�mlad���m�z de�i�kene at�yoruz
   
   
if (eskisicaklik!=sicaklik) { // Ekran�n sadece s�cakl�k de�i�ti�inde yenilenmesi i�in 2. de�i�ken ile kar��la�t�r�lmas�. E�er de�i�im var ise ekran�n yenilemesi.
lcd_gotoxy(1,1); // Ekran�n yazmaya ba�lamas� i�in 1. Sat�r 1. S�tuna gitmesine yarayan fonksiyon.
printf(lcd_putc,"Sicaklik : %i C  ",sicaklik); // Ekrana sicaklik de�i�keninin yazd�r�lmas�
eskisicaklik=sicaklik; // Ekran�n sadece s�cakl�k de�i�ti�inde yenilenmesi i�in 2. bir de�i�kene at�yoruz.
}

if (eskinem!=nem) { // Ekran�n sadece nem de�i�ti�inde yenilenmesi i�in 2. de�i�ken ile kar��la�t�r�lmas�. E�er de�i�im var ise ekran�n yenilemesi.
lcd_gotoxy(1,2); // Ekran�n yazmaya ba�lamas� i�in 2. Sat�r 1. S�tuna gitmesine yarayan fonksiyon.
printf(lcd_putc,"\nNem : %% %i  ",nem); // Ekrana nem de�i�keninin yazd�r�lmas�
eskinem=nem;  // Ekran�n sadece nem de�i�ti�inde yenilenmesi i�in 2. bir de�i�kene at�yoruz.
}

delay_ms(400); // 400 ms bekliyoruz
   
   }

}

// Yaz�l�m�m�z bitti �imdi test edelim
