#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <string>
#include <windows.h>
using namespace std;
#define AD_UZUNLUK 30
#define ogrNO_UZUNLUK 15
#define syd_UZUNLUK 30

int dugumsayisi = 0;
struct dugum
{
	char ad[AD_UZUNLUK];
	char soyad[syd_UZUNLUK];
	int ogrno;
	dugum *sol;
	dugum *sag;
};

struct agac
{
	dugum *kok;
	string dosya;
	int elemansayisi;
	ofstream outfile;
	void dosyadan_oku(string dosyaadi);
	void inorder_yaz(dugum *p);
	void agacolustur();
	void ekle(dugum *);
	void yazdir();
	void sil(int ogrno);
	void sill(dugum **);
	void preorder(dugum *);
	void inorder(dugum *);
	void postorder(dugum *);
	void search(int ogrno);
	void setup();
};

typedef agac veriyapisi;
veriyapisi kayit;

void agac::preorder(dugum *p)
{
	if (p)
	{
		cout << p->ad << "  " << p->soyad << "  " << p->ogrno << "  " << endl;
		preorder(p->sol);
		preorder(p->sag);
	}
}

void agac::inorder(dugum *p)
{
	if (p)
	{
		inorder(p->sol);
		cout << p->ad << "  " << p->soyad << "  " << p->ogrno << " " << endl;
		inorder(p->sag);
	}
}

void agac::postorder(dugum *p)
{
	if (p)
	{
		postorder(p->sol);
		postorder(p->sag);
		cout << p->ad << "  " << p->soyad << "  " << p->ogrno << "  " << endl;
	}
}

void agac::agacolustur()
{
	kok = NULL;
	elemansayisi = 0;
	cout << "Agac olusturuldu!!" << endl;
	Sleep(1500);
	system("CLS");
}

void agac::ekle(dugum *eklenecek)
{
	bool eklendi = false;
	dugum *tara;
	dugum *yeni = new dugum;
	tara = kok;
	*yeni = *eklenecek;
	yeni->sol = NULL;
	yeni->sag = NULL;
	if (kok == NULL)
	{
		kok = yeni;
		//cout << "Ilk eleman eklendi !" << endl;
		elemansayisi++;
		return;
	}
	while ((tara != NULL) && (!eklendi))
	{
		if (tara->ogrno > yeni->ogrno)
		{
			if (tara->sol != NULL)
			{
				tara = tara->sol;
			}
			else
			{
				//cout << tara->ad << " dugumunun soluna " << yeni->ad << " elemanini ekledim, sanirim :D" << endl;
				tara->sol = yeni;
				eklendi = true;
			}
		}
		else if (tara->ogrno < yeni->ogrno)
		{
			if (tara->sag != NULL)
				tara = tara->sag;
			else
			{
				//cout << tara->ad << " dugumunun sagina " << yeni->ad << " elemanini ekledim, sanirim :D " << endl;
				tara->sag = yeni;
				eklendi = true;
			}
		}
		else
		{
			//cout << "Kopya" << endl;
			return;
		}
	}
	if (eklendi == true)
	{
		elemansayisi++;
	}
	//cout << "Eleman sayisi : " << elemansayisi << endl;
	//cout << "PREORDER :\t\t";
	//preorder(kok);
	//cout << endl;
	//cout << "INORDER :\t\t";
	//inorder(kok);
	//cout << endl;
	//cout << "POSTORDER :\t\t";
	//postorder(kok);
	//cout << endl;
}

void agac::dosyadan_oku(string dosyaadi)
{
	dugum newkayit;
	char satirAl[75];
	char *ptr;
	ifstream dosya1(dosyaadi);
	dosya1.getline(satirAl, 75);
	for (int i = 0; i < 75; i++)
	{
		if (satirAl[i] == '\r')
			satirAl[i] = '\0';
	}
	while (dosya1)
	{
		ptr = strtok(satirAl, "\t");
		int j = 0;
		while (ptr != NULL)
		{
			if (j == 0)
				newkayit.ogrno = stoi(ptr);
			if (j == 1)
				strcpy(newkayit.ad, ptr);
			if (j == 2)
				strcpy(newkayit.soyad, ptr);
			if (j == 3)
			{
				strcat(newkayit.ad, " ");
				strcat(newkayit.ad, newkayit.soyad);
				strcpy(newkayit.soyad, ptr);
			}
			ptr = strtok(NULL, " ");
			j++;
		}
		kayit.ekle(&newkayit);
		//cout << newkayit.ogrno << "--" << newkayit.ad << "--" << newkayit.soyad << endl;
		dosya1.getline(satirAl, 75);
		for (int i = 0; i < 75; i++)
		{
			if (satirAl[i] == '\r')
				satirAl[i] = '\0';
		}
	}
	dosya1.close();
}

void agac::inorder_yaz(dugum *p)
{
	if (p)
	{
		inorder_yaz(p->sol);
		kayit.outfile.open(kayit.dosya, std::fstream::app);
		kayit.outfile << p->ogrno << "\t" << p->ad << " " << p->soyad << endl;
		kayit.outfile.close();
		inorder_yaz(p->sag);
	}
}

void agac::search(int ogrno)
{
	int sayac=0;
	dugum *tara = kok, *bos = NULL;

	if (kok == NULL)
	{
		cout << "List is empty" << endl;
	}
	while ((tara != NULL))
	{
		if (tara->ogrno > ogrno)
		{
			if (tara->sol != NULL)
			{
				tara = tara->sol;
			}
			else
			{
				sayac++;
				if(sayac==3){
					cout<<"Bulunamadi"<<endl;
					break;
				}
			}
		}
		else if (tara->ogrno < ogrno)
		{
			if (tara->sag != NULL)
				tara = tara->sag;
			else
			{
				sayac++;
				if(sayac==3){
					cout<<"Bulunamadi"<<endl;
					break;
				}
			}
		}
		else
		{
			if (ogrno == tara->ogrno)
			{
				cout << "bulundu" << endl;
				cout << "Ad: " << tara->ad << " Soyad: " << tara->soyad << " Ogrno: " << tara->ogrno << endl;
				break;
			}
			else
			{
				cout << "bulunamadı" << endl;
			}
		}
	}
}

void agac::sil(int ogrno)
{
	dugum *tara, *ust;
	tara = kok;
	bool bulundu = false;
	char yon = 'k';
	while (tara && !bulundu)
	{
		if (ogrno < tara->ogrno)
		{
			ust = tara;
			yon = 'l';
			tara = tara->sol;
		}
		else if (ogrno > tara->ogrno)
		{
			ust = tara;
			yon = 'r';
			tara = tara->sag;
		}
		else
			bulundu = true;
	}
	if (bulundu)
	{
		if (yon == 'l'){
		cout<<ust->sol->ad<<" "<<ust->sol->soyad<<endl;
			sill(&ust->sol);
		}
		else if (yon == 'r'){
		cout<<ust->sag->ad<<" "<<ust->sag->soyad<<endl;
			sill(&ust->sag);
		}
		else{
		cout<<kok->ad<<" "<<kok->soyad<<endl;
			sill(&kok);
		}
	}
	else{
		cout << "Silinecek kayit"
			 << "bulunamadi." << endl;
	}
}

void agac::sill(dugum **p)
{
	
	dugum *q, *r;
	r = *p;
	if (r == NULL)
		return;
	else if (r->sag == NULL)
	{
		*p = r->sol;
		delete r;
	}
	else if (r->sol == NULL)
	{
		*p = r->sag;
		delete r;
	}
	else
	{
		for (q = r->sag; q->sol; q = q->sol)
			;
		q->sol = r->sol;
		*p = r->sag;
		delete r;
	}
	cout << "silindi" << endl;
}

void agac::setup()
{

	kayit.agacolustur();
	kayit.dosyadan_oku(dosya);
}

int main()
{
	int list, ogrno;
	bool isFileOpen = false;
	char secim;
	while (1)
	{
		while (!isFileOpen)
		{
			cout << "Data1 icin 1 \nData2 icin 2 \nData3 icin 3 \nCikis icin 4 giriniz: " << endl;
			int dosya;
			cin >> dosya;

			if (dosya == 1)
			{
				kayit.dosya = "data1.txt";
				kayit.setup();
				isFileOpen = true;
				//kayit.inorder_yaz(kayit.kok);
				break;
			}
			else if (dosya == 2)
			{
				kayit.dosya = "data2.txt";
				kayit.setup();
				isFileOpen = true;
				//kayit.inorder_yaz(kayit.kok);
				break;
			}
			else if (dosya == 3)
			{
				kayit.dosya = "data3.txt";
				kayit.setup();
				isFileOpen = true;
				//kayit.inorder_yaz(kayit.kok);
				break;
			}
			else if (dosya == 4)
			{
				return -1;
			}
			else
			{
				cout << "Yanlis giris" << endl;
			}
		}

		cout << endl<<"           "
			 << kayit.dosya
			 << endl
			 <<endl
			 << "Asagidaki islemlerden birini seciniz" << endl;
		cout << "Arama yapmak icin A" << endl
			 << "Listeyi ekrana yazdirmak icin L" << endl
			 << "Ogrenci silmek icin S" << endl
			 << "Dosyaya yazdirmak icin Y" << endl
			 << "Cikis yapmmak icin C" << endl<<"--->";
		cin >> secim;

		switch (secim)
		{
		case 'A':
			cout << endl
				 << "Aranacak ogrno:";
			cin >> ogrno;
			kayit.search(ogrno);
			break;
		case 'L':
			cout << "Preorder listeleme icin 1" << endl;
			cout << "Inorder listeleme icin 2" << endl;
			cout << "Postorder listeleme icin 3" << endl;
			cin >> list;
			switch (list)
			{
			case 1:
				kayit.preorder(kayit.kok);
				break;
			case 2:
				kayit.inorder(kayit.kok);
				break;
			case 3:
				kayit.postorder(kayit.kok);
				break;

			default:
				cout << "Gecersiz secim" << endl;
				break;
			}
			break;
		case 'S':
			cout << endl
				 << "Silinecek ogrno:";
			cin >> ogrno;
			kayit.sil(ogrno);
			break;
		case 'Y':
			kayit.outfile.open(kayit.dosya);
			kayit.outfile.close();
			kayit.inorder_yaz(kayit.kok);
			cout << "Yazdirildi" << endl;
			break;
		case 'C':
			isFileOpen = false;
			break;

		default:
			cout << "yanlis giris" << endl;
			break;
		}
		system("pause");
		system("CLS");
	}

	return 0;
}