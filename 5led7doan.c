#include <16f877a.h>
#use delay(clock=4000000)
#fuses HS, NOWDT, NOLVP, NOBROWNOUT, NOPROTECT, NOPUT
#use rs232(baud=9600,parity=n,xmit=pin_c6,rcv=pin_c7)
int8 const led7doan[10] ={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90};
int8 const char9[10] ={'0','1','2','3','4','5','6','7','8','9'};
int8  so[10] ={0,1,2,3,4,5,6,7,8,9};
#bit led1   =    0x05.0
#bit led2   =    0x05.1
#bit led3   =    0x05.2
#bit led4   =    0x05.3
#bit led5   =    0x05.5
#bit CT1    =    0x06.0
#bit CT2    =    0x06.1
#bit CT3    =    0x06.2
#bit leddon1 =   0x06.4 
#bit leddon2 =   0x06.5
#bit champhay=   0x08.7
int8 so1,so2,so3,so4,so5,menu,i,temp;
int8 temp_nhapnhay;
int8 get_gt(int8 giatri) //Chuong trinh con lay gia tri truyen tu cong COM
{
   int8 kq;
   switch (giatri) {
    case '0': kq = 0;
           break;
    case '1': kq = 1;
           break;       
    case '2': kq = 2;
           break;       
    case '3': kq = 3;
           break;       
    case '4': kq = 4;
           break;       
    case '5': kq = 5;
           break;       
    case '6': kq = 6;
           break;       
    case '7': kq = 7;
           break;
    case '8': kq = 8;
           break;       
    case '9': kq = 9;
           break;  
   }
   return kq;
}
#int_rda //Ngat Truyen Thong
void serial_isr() {
   int8 giatri_nhan;
   giatri_nhan =getc();
   if (giatri_nhan == '&') putc('&'); //Tra loi dung thiet bi
   if (giatri_nhan == '(') {leddon1 = 1; leddon2 = 1;}; //Bat led
   if (giatri_nhan == ')') {leddon1 = 0; leddon2 = 0;}; //Tat Led
   if (giatri_nhan == '@') {temp = 0; menu =0;} //Byte ket thuc du lieu
   switch (temp) {
    case 1: so1 = get_gt(giatri_nhan); temp=temp+1;
           break;
    case 2: so2 = get_gt(giatri_nhan); temp=temp+1;
           break;
    case 3: so3 = get_gt(giatri_nhan); temp=temp+1;
           break;       
    case 4: so4 = get_gt(giatri_nhan); temp=temp+1;
           break;       
    case 5: so5 = get_gt(giatri_nhan); temp=0;
           break;
   }
    if (giatri_nhan == '#') temp = 1;//Byte mo dau du lieu
}
void xuat_pc() //Chuong trinh con xuat gia tri len PC
{
   putc(char9[so1]);
   putc(char9[so2]);
   putc(char9[so3]);
   putc(char9[so4]);
   putc(char9[so5]);
   putc('@');
}
void quetled() //Chuong trinh con Quet va Tao hieu ung led 7 doan
{
   //Quet led 1
   output_a(0xff);
   if(menu == 1)
   {
      temp_nhapnhay = temp_nhapnhay + 1;
      if(temp_nhapnhay <= 50)
         output_d(0xFF);
      else
      {
         output_d(led7doan[so1]);
         if (temp_nhapnhay > 100) temp_nhapnhay = 0;
      }
      
   } else {
      output_d(led7doan[so1]);
   }
   led1 = 0;
   delay_ms(1);
   //Quet led 2
   output_a(0xff);
   if(menu == 2)
   {
      temp_nhapnhay = temp_nhapnhay + 1;
      if(temp_nhapnhay <= 50)
         output_d(0xFF);
      else
      {
         output_d(led7doan[so2]);
         champhay = 0;
         if (temp_nhapnhay > 100) temp_nhapnhay = 0;
      }
      
   } else {
      output_d(led7doan[so2]);
      champhay = 0;
   }
   led2 = 0;
   delay_ms(1);
   //Quet led 3
   output_a(0xff);
   if(menu == 3)
   {
      temp_nhapnhay = temp_nhapnhay + 1;
      if(temp_nhapnhay <= 50)
         output_d(0xFF);
      else
      {
         output_d(led7doan[so3]);
         if (temp_nhapnhay > 100) temp_nhapnhay = 0;
      }
      
   } else {
      output_d(led7doan[so3]);
   }
   led3 = 0;
   delay_ms(1);
   //Quet led 4
   output_a(0xff);
   if(menu == 4)
   {
      temp_nhapnhay = temp_nhapnhay + 1;
      if(temp_nhapnhay <= 50)
         output_d(0xFF);
      else
      {
         output_d(led7doan[so4]);
         if (temp_nhapnhay > 100) temp_nhapnhay = 0;
      }
      
   } else {
      output_d(led7doan[so4]);
   }
   led4 = 0;
   delay_ms(1);
   //Quet led 5
   output_a(0xff);
   if(menu == 5)
   {
      temp_nhapnhay = temp_nhapnhay + 1;
      if(temp_nhapnhay <= 50)
         output_d(0xFF);
      else
      {
         output_d(led7doan[so5]);
         if (temp_nhapnhay > 100) temp_nhapnhay = 0;
      }
      
   } else {
      output_d(led7doan[so5]);
   }
   led5 = 0;
   delay_ms(1);
}
void cong() //Chuong trinh con Cong gia tri
{
   switch (menu) {
    case 1: so1 = so1 + 1; if(so1 == 10) so1 = 0;
           break;
    case 2: so2 = so2 + 1; if(so2 == 10) so2 = 0;
           break;
    case 3: so3 = so3 + 1; if(so3 == 10) so3 = 0;
           break;       
    case 4: so4 = so4 + 1; if(so4 == 10) so4 = 0;
           break;       
    case 5: so5 = so5 + 1; if(so5 == 10) so5 = 0;
           break;
   }
}
void tru() //Chuong trinh con tru gia tri
{
   switch (menu) {
    case 1: if(so1 == 0) so1 = 10; so1 = so1 - 1;
           break;
    case 2: if(so2 == 0) so2 = 10; so2 = so2 - 1;
           break;
    case 3: if(so3 == 0) so3 = 10; so3 = so3 - 1;
           break;       
    case 4: if(so4 == 0) so4 = 10; so4 = so4 - 1;
           break;       
    case 5: if(so5 == 0) so5 = 10; so5 = so5 - 1;
           break;
   }   
}
void delay(int8 time) //Chuong trinh delay chong nhay led 7 doan
{
   for(i=0;i<=time;i++)
   {
      delay_ms(1);
      quetled();
   }
}
void kt_nutnhan1() //Kiem tra chong Nhieu nut bam 1
{
   delay(10);
   if(CT1 == 0)
   {
      while(CT1 == 0)
      {
         quetled();
      }
      menu = menu + 1;
      if (menu == 6) menu = 0;
   }
}
void kt_nutnhan2() //Kiem tra chong Nhieu nut bam 2
{
   delay(10);
   if(CT2 == 0)
   {
      while(CT2 == 0)
      {
         quetled();
      }
      tru();
      xuat_pc();
   }
}
void kt_nutnhan3() //Kiem tra chong Nhieu nut bam 3
{
   delay(10);
   if(CT3 == 0)
   {
      while(CT3 == 0)
      {
         quetled();
      }
      cong();
      xuat_pc();
   }
}
void main()
{
   //Cai dat ngat truyen thong
   enable_interrupts(int_rda);
   enable_interrupts(global);
   //Cai dat vao ra
   set_tris_a(0x00);
   set_tris_b(0x0f);
   set_tris_c(0xff);
   set_tris_d(0x00);
   so1 = so2 = so3 = so4 = so5 = menu = temp_nhapnhay = temp = 0;
   xuat_pc();
   while(1)
   {
      quetled();
      if(CT1 == 0) 
      {
         kt_nutnhan1();
      }
      if(CT2 == 0)
      {
         kt_nutnhan2();
      }
      if(CT3 == 0)
      {
         kt_nutnhan3();
      }
   }
}
