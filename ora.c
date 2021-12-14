#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    FILE* fp;
    fp = fopen("ora.svg", "w");     // az "ora.svg fajl letrehozasa"

    int ora, perc, masodperc;
    //int x_koord, y_koord;
    //itt most eltolasX es eltolasY megegyezik es egyenlo "eltolas"-al (lehetnenek kulonbozoek)
    int eltolas = 500 /*250*/;          /*a kor kozeppontja (0,0)-rol ide es ennyivel tolodik */
    int r /*sugar*/ = 200;

    printf("\tEz a program egy \"ora.svg\" tipusu fajlt allit elo a bemeno/input adatok alapjan.\n");
    printf("\tAz \"ora.svg\" fajl bongeszoben megjelenitve egy ora(lapo)t abrazol, \nkis-, nagy-, es percmutatoval.\n\n");
    printf("Kerem a 3 db szamot - szokozzel kozottuk\n");
    printf("(ora, perc es masodperc, pl. 17 55 43): ");

    scanf("%d %d %d", &ora, &perc, &masodperc);


    fprintf(fp, "<svg width=\"%d\" height=\"%d\" xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">\n", 2*eltolas, 2*eltolas);
    fprintf(fp, "<circle cx=\"%d\" cy=\"%d\" r=\"%d\" stroke=\"red\" stroke-width=\"3\" fill=\"black\"/>\n", eltolas, eltolas, r);
    fprintf(fp, "<circle cx=\"%d\" cy=\"%d\" r=\"5\" stroke=\"red\" fill=\"white\"/>\n", eltolas, eltolas);

    // ide kellenek a szamitasok es az ora.svg abrajanak (oralap, beosztasok es percmutatok) megrajzolasa
    // ! termeszetesen a fentiek az "ora", "perc" es "masodperc" fuggvenyeben ertendok

    int x_koord = 0, y_koord = 0;
    int x_rovatka = 0, y_rovatka = 0;
    int n = 60;

    int osztopontarany = 20;    // 20 -1 = 19 illetve  20 - 2 = 18
    // ***** ld. egy huszad illetve egy tized aranyu felosztasa a szakasznak


    for (int k = 0; k < n; k++)
    {
        //itt most eltolasX es eltolasY megegyezik es egyenlo "eltolas"-al (lehetnenek kulonbozoek)
        x_koord = (int)(r*(cos((2*acos(-1)*k)/n))/**pow((double)r, 1/n) -- nem kell*/) + eltolas;
        y_koord = (int)(r*(sin((2*acos(-1)*k)/n))) + eltolas;
        if (k%5 == 0)
        {
            // osztopont koordinatak (hosszu rovatka)
            x_rovatka = (int)((eltolas*2 + x_koord*(osztopontarany-2))/osztopontarany);
            y_rovatka = (int)((eltolas*2 + y_koord*(osztopontarany-2))/osztopontarany);

        } else
        {

            // osztopont koordinatak (rovid rovatka)
            x_rovatka = (int)((eltolas*1 + x_koord*(osztopontarany-1))/osztopontarany);
            y_rovatka = (int)((eltolas*1 + y_koord*(osztopontarany-1))/osztopontarany);
        }
        fprintf(fp, "<line x1=\"%d\" y1=\"%d\" x2=\"%d\" y2=\"%d\" stroke=\"white\" />\n",
                x_koord, y_koord, x_rovatka, y_rovatka);
    }

    // oramutatok
    int osszidomasodpercben = ora*3600 + perc*60 + masodperc;
    int teljesidomasodpercben = 12*3600;    // 12 ora, ez felel meg 2 Pi-nek
    double x_metszespont, y_metszespont;        // az alfa szog jelenti a beolvasott adatoknak megfelelo szoget; ld. a kov. sort
    double szogkismutato /* alfa */ = (2*acos(-1)*osszidomasodpercben)/teljesidomasodpercben;

    x_metszespont = eltolas + r*sin(szogkismutato);     //  tulajdonkeppen  x = xo + r*sin(alfa - Pi/2) = x0 - r*cos(alfa)
    y_metszespont = eltolas - r*cos(szogkismutato);     //  es              x = y0 + r*cos(alfa - Pi/2) = y0 + r*sin(alfa)
    // megjeleniteni kismutatokent az
    // P(x_metszespont, y_metszespont) es O(eltolas, eltolas) pontok
    // altal meghatarozott |PO| szakasz ketharmadat fogjuk (a kor kozeppontjatol)
    int x_kismut = (int)((eltolas + 2*x_metszespont)/3);
    int y_kismut = (int)((eltolas + 2*y_metszespont)/3);

    fprintf(fp, "<line x1=\"%d\" y1=\"%d\" x2=\"%d\" y2=\"%d\" stroke=\"red\" stroke-width=\"8\" />\n",
                eltolas, eltolas, x_kismut, y_kismut);

    // **********************************************************************************************************

    double szognagymutato /* beta */ = (2*acos(-1)*(perc*60 + masodperc))  /(60*60);  // 60 perc felel meg 2 Pi-nek

    x_metszespont = eltolas + r*sin(szognagymutato);
    y_metszespont = eltolas - r*cos(szognagymutato);

    int x_nagymut = (int)x_metszespont;
    int y_nagymut = (int)y_metszespont;
    fprintf(fp, "<line x1=\"%d\" y1=\"%d\" x2=\"%d\" y2=\"%d\" stroke=\"red\" stroke-width=\"4\" />\n",
                eltolas, eltolas, x_nagymut, y_nagymut);

    // **********************************************************************************************************
    double szogmasodpercmutato /* beta */ = (2*acos(-1)*masodperc)/60;  // 60 masodperc perc felel meg 2 Pi-nek

    x_metszespont = eltolas + r*sin(szogmasodpercmutato);
    y_metszespont = eltolas - r*cos(szogmasodpercmutato);

    int x_masodpercmut = (int)x_metszespont;
    int y_masodpercmut = (int)y_metszespont;
    fprintf(fp, "<line x1=\"%d\" y1=\"%d\" x2=\"%d\" y2=\"%d\" stroke=\"yellow\" stroke-width=\"1\" />\n",
                eltolas, eltolas, x_masodpercmut,  y_masodpercmut);
    // **********************************************************************************************************
    fprintf(fp, "</svg>");
    fclose(fp);             // fajl bezarasa
    return 0;
}
