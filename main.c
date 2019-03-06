#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

typedef struct
{
    char isim[100];
    long int kod;
    long int numara;
} Telephone;

Telephone Rehber;

int Menu();
void Kayitlama();
void Listele();
void Num_arama();
void Isim_arama();
void Duzenle();
void Sil();

int main()
{
    setlocale(LC_ALL, "Turkish");
    int tercih;
    while(1)
    {
        tercih=Menu();
        switch(tercih)
        {
        case 0:
            printf("\n-------------------------\nBasarili cikis yaptiniz.\n-------------------------\n");
            exit(1);
        case 1:
            Kayitlama();
            break;
        case 2:
            Listele();
            break;
        case 3:
            Duzenle();
            break;
        case 4:
            Num_arama();
            break;
        case 5:
            Isim_arama();
            break;
        case 6:
            Sil();
            break;
        }
    }
    return 0;
}

int Menu()
{
    int giris;
    printf("\t\t  TELEFON REHBERI v3.1\n");
    printf("\t\t ***********************\n\n");
    printf("ISLEMLER\n\n");
    printf("1. KAYIT EKLEME\n");
    printf("2. KAYIT LISTELEME\n");
    printf("3. KAYIT DUZENLEME\n");
    printf("4. NUMARA ILE KAYIT BULMA\n");
    printf("5. ISIM ILE KAYIT BULMA\n");
    printf("6. KAYIT SILME\n");
    printf("0. CIKIS\n");

    do
    {
        printf("\nSECIMINIZ:");
        scanf("%d",&giris);
        if(giris<0 || giris>6)
        {
            printf("\n\nOOPSS Yanlis secim yaptiniz. \n");
            printf("\nDevam etmek icin space tusunu basin...\n\n");
            getche();
        }
    }
    while(giris<0 || giris>6);

    return giris;
}

void Kayitlama()
{
    system("cls");
    char ch;

    FILE *pDosya;
    if((pDosya=fopen("TelefonRehber.txt","ab+"))==NULL)
    {
        printf("Dosya acma hatasi...\n");
        exit(1);
    }
    do
    {
        printf("---------------\nYeni Kisi Ekle\n---------------\n\n");
        printf("Adi giriniz:");
        scanf("%s",Rehber.isim);
        printf("Kodu giriniz:");
        scanf("%ld",&Rehber.kod);
        printf("Telefon numarasini giriniz:");
        scanf("%ld",&Rehber.numara);

        fwrite(&Rehber,sizeof(Rehber),1,pDosya);

        printf("\n----------------------------------------");
        printf("\nTekrar kayit yapmak ister misin (E/H) : ");
        ch=getch();
        printf("\n----------------------------------------\n\n");
    }
    while((ch=='E') || (ch=='e'));

    fclose(pDosya);
    printf("Devam etmek icin space tusunu basin..");
    getche();
    system("cls");
}

void Listele()
{
    system("cls");
    int i,sayac=0;
    Telephone sListele;
    FILE *pDosya;
    if((pDosya=fopen("TelefonRehber.txt","rb"))==NULL)
    {
        printf("Dosya okunamadi...");
        exit(1);
    }

    printf("----------------\nMEVCUT KAYITLAR\n----------------\n\n");

    while((fread(&sListele,sizeof(sListele),1,pDosya))==1)
    {
        printf("Adi:%s\n",sListele.isim);
        printf("Kodu:%ld\n",sListele.kod);
        printf("Telefonu:%ld\n\n",sListele.numara);
        sayac++;
    }
    printf("--------------------\nToplam %d kayit var.\n--------------------\n",sayac);
    fclose(pDosya);
    printf("Devam etmek icin space tusunu basin...");
    getche();
    system("cls");
}

void Duzenle()
{
    system("cls");
    FILE *pDosya;
    char duzenlenecekAd[100];
    Telephone sDuzenle;
    if((pDosya=fopen("TelefonRehber.txt","rb+"))==0)
    {
        printf("Dosya okunamadi.");
        exit(1);
    }

    printf("----------------\nKAYIT DUZENLEME\n----------------\n\n");
    printf("Musteri adini girin: ");
    scanf("%s",&duzenlenecekAd);

    while((fread(&sDuzenle,sizeof(sDuzenle),1,pDosya))==1)
    {
        if((strcmp(sDuzenle.isim,duzenlenecekAd))==0)
            break;
    }

    if((strcmp(sDuzenle.isim,duzenlenecekAd))==0)
    {
        printf("\n--------------------------\nKayitli Musteri Bilgileri\n--------------------------\n\n");
        printf("Adi: %s\n",sDuzenle.isim);
        printf("Kodu: %ld\n",sDuzenle.kod);
        printf("Telefon: %ld\n",sDuzenle.numara);

        printf("\n-----------------------\nYeni Musteri Bilgileri\n-----------------------\n\n");
        printf("Ad: ");
        scanf("%s",&sDuzenle.isim);
        printf("Kod: ");
        scanf("%ld",&sDuzenle.kod);
        printf("Telefon: ");
        scanf("%ld",&sDuzenle.numara);

        fseek(pDosya,-1*sizeof(sDuzenle),SEEK_CUR);

        if((fwrite(&sDuzenle,sizeof(sDuzenle),1,pDosya))==1)
        {
            printf("\n\nBilgiler Baþariyla Guncellendi.\n\nDevam etmek icin space tusunu basin...");
        }
        else
            printf("OPPS Birseyler yanlis gitti!");
    }
    else
        printf("\n\nKayit Bulunamadi.\n\nYeniden arama yapmak ister misiniz ? (E/H) : ");
    if(toupper(getche())=='E')
    {
        Duzenle();
    }

    fclose(pDosya);
    system("cls");
}

void Num_arama()
{
    system("cls");

    long int aranacakTel;
    Telephone sBul;

    printf("------------------\nTELEFON ILE ARAMA\n------------------\n\n");
    printf("Aranacak Telefon Numarasini Giriniz : ");
    scanf("%ld",&aranacakTel);
    printf("\n");

    FILE *pDosya;
    if((pDosya=fopen("TelefonRehber.txt","rb"))==NULL)
    {
        printf("Dosya okunamadi...");
        exit(1);
    }

    int sayac=0;
    while((fread(&sBul,sizeof(sBul),1,pDosya))==1)
    {
        if(sBul.numara==aranacakTel)
        {
            printf("Adi:%s\n",sBul.isim);
            printf("Kodu:%ld\n",sBul.kod);
            printf("Telefon:%ld\n\n",sBul.numara);
            sayac++;
        }
    }

    if(sayac==0)
        printf("\nKayit Bulunamadi.\n\n");
    else
        printf("------------------------\nToplam %d Kayit Bulundu.\n------------------------\n",sayac);
    fclose(pDosya);
    printf("Devam etmek icin space tusunu basin...");
    getche();
    system("cls");
}

void Isim_arama()
{
    system("cls");
    char aranacakAd[100];
    Telephone sBul;

    printf("---------------\nISIM ILE ARAMA\n---------------\n\n");
    printf("Aranacak Isim : ");
    scanf("%s",&aranacakAd);
    printf("\n");

    FILE *pDosya;
    if((pDosya=fopen("TelefonRehber.txt","rb"))==NULL)
    {
        printf("Dosya okunamadi...");
        exit(1);
    }

    int sayac=0;
    while((fread(&sBul,sizeof(sBul),1,pDosya))==1)
    {
        if((strcmp(sBul.isim,aranacakAd))==0)
        {
            printf("Adi:%s\n",sBul.isim);
            printf("Kodu:%ld\n",sBul.kod);
            printf("Telefon:%ld\n\n",sBul.numara);
            sayac++;
        }
    }

    if(sayac==0)
        printf("\nKayit Bulunamadi.\n\n");
    else
        printf("------------------------\nToplam %d Kayit Bulundu.\n------------------------\n",sayac);
    fclose(pDosya);
    printf("Devam etmek icin space tusunu basin...");
    getche();
    system("cls");
}

void Sil()
{
    system("cls");
    FILE *pDosya,*SilpDosya;
    long int arananKod;
    int kontrol=0;
    Telephone sSil;
    if((pDosya=fopen("TelefonRehber.txt","rb"))==NULL)
    {
        printf("Dosya okunamadi...");
        exit(1);
    }
    if((SilpDosya=fopen("TelefonRehber2.txt","wb"))==NULL)
    {
        printf("Dosya okunamadi...");
        exit(1);
    }

    printf("------------\nKAYIT SILME\n------------\n\n");
    printf("Musteri kodunu giriniz : ");
    scanf("%ld",&arananKod);


    while((fread(&sSil,sizeof(sSil),1,pDosya))==1)
    {
        if(sSil.kod!=arananKod)
        {
            fwrite(&sSil,sizeof(sSil),1,SilpDosya);
        }
        else
        {
            printf("\n\nMusteri silindi.\n\n");
            printf("Devam etmek icin space tusunu basin...\n\n");
            getche();
            system("cls");
            kontrol++;
        }
    }

    if(kontrol==0)
    {
        printf("\n\nKayit Bulunamadi.\n\nYeniden Arama Yapmak Ister Misiniz ? (E/H) : ");
        if(toupper(getche())=='E')
        {
            fclose(pDosya);
            fclose(SilpDosya);
            remove("TelefonRehber.txt");
            rename("TelefonRehber2.txt","TelefonRehber.txt");
            Sil();
            return 0;
        }
        system("cls");
    }

    fclose(pDosya);
    fclose(SilpDosya);
    remove("TelefonRehber.txt");
    rename("TelefonRehber2.txt","TelefonRehber.txt");
}
