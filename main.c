#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#define maxitem 15
#define maxitemcap 5

typedef struct{
	char barang[50]; //10 karakter nama barang
	int stockbrg; //max 5 per item
	char jenis[7]; //jenis item makanan/minuman
	int harga;
}mesin;

typedef struct{
	int barangCart[maxitemcap];
	int totalbiaya;
	int jmlbrg[maxitemcap];
	int count; //menghitung barang belanjaan
}cart;

void shoppingCart(char);
char subMenu(mesin *);
void garis(char, int);
char menuTransaksi();
void swap(mesin *, mesin*);
void Stocks(mesin *);
char menu(mesin *);
mesin vending1[maxitem];
cart cart1;

int main(){
	Stocks(vending1);
	//printf("%d\n",vending1[0].stockbrg);
	
	char pilih='0';    //inisialisasi, pilih belum diinput dari user.
	do{
		pilih=menu(vending1); //panggil fungsi menu, hasilnya(input dari user) akan disimpan di variabel pilih
		if(pilih=='1'){ //jika pilih = 1
			system("cls");
			char plh='0';
			cart1.count=0;
			cart1.totalbiaya=0;
			do{
				plh=subMenu(vending1);
				if((plh=='N')||(plh=='n')){
					plh=menuTransaksi();
				}else if(plh!='E'){
					shoppingCart(plh);
					cart1.count++;
					if(cart1.count>maxitemcap-1){
						printf("Anda sudah memenuhi batas maksimal item\n");
						system("pause>null");
						menuTransaksi();
						cart1.count=0;
					}
				}
				//system("pause");
			}while(plh!='E');
			continue;
		}else if(pilih=='2'){  //jika pilih = 2
			printf("mencet 2\n");
			system("pause");//MenuMatikanAlat(AlatListrik,&TotalBiaya); //panggil MenuMatikanAlat
		}else{
			pilih='0';
		}
	}while(pilih!='4'); //Jika Pilih = 4, keluar dari looping while
	system("pause");  // hentikan layar, tunggu user menekan tombol
}

char menu(mesin *vending1){
	char pilih;  //deklarasi variabel lokal menu
	system("cls");  //hapus layar
	//tampilkan menu pilihan
	printf("1. Beli Makanan/Minuman \n");
	printf("2. Admin \n");
	printf("Silakan pilih (1/2) : ");
	scanf("%c",&pilih); //tampung masukan dari user ke variabel pilih
	return pilih; // kembalikan nilai variabel pilih
}

char menuTransaksi(){
	int i;
	system("cls");
	printf("|No.|%-26s| Jumlah |	\n","Item");
	for(i=0;i<maxitemcap;i++){
		printf("|%-2d |%-26s|%8d|\n",i+1,vending1[cart1.barangCart[i]].barang,cart1.jmlbrg[i]);
	}
	system("pause>null");
	return 'E';
}

void swap(mesin *a, mesin *b){
	mesin c;
	c=*a;
	*a=*b;
	*b=c;
}

void shoppingCart(char k){
	int i;
	char temp[50];
	char resp;
	int ik=k-'0'-1;
	cart1.barangCart[cart1.count]=ik;
	if(vending1[ik].stockbrg==0){
		printf("Stock habis");
		cart1.count--;
		system("pause>null");
	}else{
		printf("Masukan jumlah yang akan dibeli: "); scanf("%d",&i);
		resp=0;
		if(vending1[ik].stockbrg<i){
			printf("Stock yang tersisa: %d, ",vending1[ik].stockbrg);
			printf(" Lanjutkan membeli %d? Press 'Y' to proceed",vending1[ik].stockbrg);
			resp=getchar();
			if((resp=='Y')||(resp=='y')){
				printf("Anda menambahkan %d %s",vending1[ik].stockbrg,vending1[ik].barang);
				cart1.jmlbrg[cart1.count]=vending1[ik].stockbrg;
				vending1[ik].stockbrg-=vending1[ik].stockbrg;
				cart1.totalbiaya+=((vending1[ik].harga)*vending1[ik].stockbrg);
				system("pause>null");
			}else{
				cart1.count--;
				system("pause>null");
			}
		}else{
			printf("Anda menambahkan %d %s",i,vending1[ik].barang);
			cart1.jmlbrg[cart1.count]=i;
			vending1[ik].stockbrg-=i;
			cart1.totalbiaya+=((vending1[ik].harga)*i);
			system("pause>null");
		}
	}
}

char subMenu(mesin *vending1){
	int i;
	char pilih;
	system("cls");
	garis('-',40);
	printf("%27s","List of items\n");
	garis('-',40);	
	garis('=',40);
	printf("|No.|%-26s| Harga |	\n","Makanan");
	garis('=',40);
	for(i=0;i<=maxitem;i++){
		if((vending1[i].stockbrg==0)&&(vending1[i].harga!=0)){
			printf("|%-2d |%-26s|%7s|\n",i+1,vending1[i].barang,"<Out of Stock>");
		}else if(strcmp(vending1[i].jenis,"Makanan")==0){
			printf("|%-2d |%-26s|%7d|\n",i+1,vending1[i].barang,vending1[i].harga);
		}
	}
	garis('=',40);
	printf("|No.|%-26s| Harga |	\n","Minuman");
	garis('=',40);
	int count = 0;
	for(i=0;i<maxitem;i++){
		if(strcmp(vending1[i].jenis,"Minuman")==0){
			printf("|%-2d |%-26s|%7d|\n",i+1,vending1[i].barang,vending1[i].harga);
			count=i+1;
		}
	}
	garis('=',40);
	printf("Press 'N' for next, Press 'E' to cancel\n");
	printf("Silahkan pilih item(%d): ",count);
	scanf("%s",&pilih); //tampung masukan dari user ke variabel pilih
	getchar();
	return pilih; // kembalikan nilai variabel pilih
}

void Stocks(mesin *vending1){
	system("cls");
	int i;
	strcpy(vending1[0].barang,"Kacang Garuda");
	strcpy(vending1[0].jenis,"Makanan");
	vending1[0].harga=10000;
	vending1[0].stockbrg=maxitemcap;
	strcpy(vending1[1].barang,"Taro");
	strcpy(vending1[1].jenis,"Makanan");
	vending1[1].harga=8000;
	vending1[1].stockbrg=maxitemcap;
	strcpy(vending1[2].barang,"Roma Kelapa");
	strcpy(vending1[2].jenis,"Makanan");
	vending1[2].harga=10000;
	vending1[2].stockbrg=maxitemcap;
	strcpy(vending1[3].barang,"Oreo");
	strcpy(vending1[3].jenis,"Makanan");
	vending1[3].harga=9000;
	vending1[3].stockbrg=maxitemcap;
	strcpy(vending1[4].barang,"Keripik Maicih");
	strcpy(vending1[4].jenis,"Makanan");
	vending1[4].harga=17000;
	vending1[4].stockbrg=maxitemcap;
	strcpy(vending1[5].barang,"Lays");
	strcpy(vending1[5].jenis,"Makanan");
	vending1[5].harga=8000;
	vending1[5].stockbrg=maxitemcap;
	strcpy(vending1[6].barang,"Fanta");
	strcpy(vending1[6].jenis,"Minuman");
	vending1[6].harga=5000;
	vending1[6].stockbrg=maxitemcap;
	strcpy(vending1[7].barang,"Sprite");
	strcpy(vending1[7].jenis,"Minuman");
	vending1[7].harga=5000;
	vending1[7].stockbrg=maxitemcap;
	strcpy(vending1[8].barang,"Coca-Cola");
	strcpy(vending1[8].jenis,"Minuman");
	vending1[8].harga=5000;
	vending1[8].stockbrg=maxitemcap;
	strcpy(vending1[9].barang,"Good Day");
	strcpy(vending1[9].jenis,"Minuman");
	vending1[9].harga=6500;
	vending1[9].stockbrg=maxitemcap;
	strcpy(vending1[10].barang,"Pepsi");
	strcpy(vending1[10].jenis,"Minuman");
	vending1[10].harga=4000;
	vending1[10].stockbrg=maxitemcap;
}

void garis(char a, int b){
	int i;
	for(i=0;i<b;i++){
	    printf("%c",a);
	}
	printf("\n");
}
