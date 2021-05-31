#include <iostream>
#include<fstream>
#include<string.h>

using namespace std;

struct agacdugum{
	struct agacdugum *soldal;
	int data;
	struct agacdugum *sagdal;
};

struct agac{
    agacdugum *kok;
    int elemansayisi;
    void agacKur();
    void ogrenciSil(agacdugum *);
    void ekle(agacdugum *);
    void yazdir();
    void preorder(agacdugum *);
    void inorder(agacdugum *);
    void postorder(agacdugum *);
};

void agac::agacKur(){
    kok = NULL;
    elemansayisi = 0;
    cout << "Agac olusturuldu ;) " <<endl;
}

void agac::ekle(agacdugum *eklenecek){
	char ogrno[15],ad[30],soyad[30],satirAl[75];
	char *ptr;
	ifstream dosya1("data1.txt");
	dosya1.getline(satirAl,75);			
	for(int i=0;i<75;i++){				//satır sonundaki '\r' karakterini, '\0' karakteri ile değiştirme
		if(satirAl[i]=='\r')	
			satirAl[i]='\0';
		}
	while(dosya1){					//while döngüsü içinde dosyayı sonuna kadar satır satır okuma ve okunan satırları boşluklara göre parçalayıp, 
		ptr=strtok(satirAl,"\t");//	j sayacının değerine göre değişkenlere atama
		int j=0;
		while(ptr!=NULL){
			if(j==0)
				strcpy(ogrno,ptr);
			if(j==1)
				strcpy(ad,ptr);
			if(j==2)
				strcpy(soyad,ptr);
			if(j==3){			//bir ad ve bir soyad okunmasına rağmen satır sonu gelmedi ise öğrencinin iki adı var demektir,
				strcat(ad," ");		//	bu iki ad arada bir boşluk bırakılarak öğrenci değişkenine atanır ve soyadı tekrar okunur
				strcat(ad,soyad);
				strcpy(soyad,ptr);
				}
			ptr=strtok(NULL," ");						
			j++;
			}
		//ekle(&kok1,ogrno,ad,soyad);
		cout << ogrno << "--" << ad << "--" << soyad << endl;
		dosya1.getline(satirAl,75);
		for(int i=0;i<75;i++){
			if(satirAl[i]=='\r')	
				satirAl[i]='\0';
			}
		}
	dosya1.close();
}
	
































// struct agacdugum * dugumekle(struct agacdugum* agacptr, int veri) 
// { 
//     if(agacptr==NULL){ 
//     agacptr = malloc(sizeof (agacdugum*)); 
//     if (agacptr!=NULL){
//         agacptr->data = veri;
//         agacptr->soldal = NULL; 
//         agacptr->sagdal= NULL; }
//     else 
//         printf("%d eklenemedi. Bellek yetersiz.\n",veri); }
//     else{ 
//         if(veri < agacptr->data){
//         printf("Aðaçýn soluna veri eklendi\n ");     
//         agacptr->soldal = dugumekle(agacptr->soldal,veri); }
// 	else{
// 	    if(veri > agacptr->data){
// 	        printf("Aðaçýn saðýna veri eklendi\n ");
// 	        agacptr->sagdal = dugumekle(agacptr->sagdal,veri); 
// 	    }
// 		else
// 	    printf("Eþit olduðu için alýnmadý\n "); 
// 		} 
// 		} 
// 		return agacptr; 
// 		}

// void inorder(struct agacdugum * agacptr) {
//     if (agacptr != NULL) { inorder(agacptr->soldal); 
//     printf("%3d",agacptr->data); 
//     inorder(agacptr->sagdal);} 
//     } 

// void preorder(struct agacdugum * agacptr)  { 
//     if (agacptr != NULL) {
//     printf("%3d",agacptr->data); 
//     preorder(agacptr->soldal);
//     preorder(agacptr->sagdal); } 
//     } 

// void postorder(struct agacdugum * agacptr) { 
//     if (agacptr != NULL) {       
//     postorder(agacptr->soldal);        
// 	postorder(agacptr->sagdal);       
//     printf("%3d",agacptr->data);   }
//     }



// void ilkDerinlikAra();
// void ilkGenişlikAra();
// void dosyayaYaz();


// int main()
// { 
// int i, dugum;
// struct agacdugum * agacptr = NULL; 
// for(i=0; i<12; ++i){ 
// scanf("%d",&dugum); printf("\n"); 
// agacptr = dugumekle(agacptr, dugum); 
// } 
// printf("\n");
// printf("Aðacýn preorder dolaþýlmasý :\n"); 
// preorder(agacptr); printf("\n");
// printf("Aðacýn inorder dolaþýlmasý :\n");
// inorder(agacptr); printf("\n");
// printf("Aðacýn postorder dolaþýlmasý :\n"); 
// postorder(agacptr); printf("\n");
// return 0;

// }
