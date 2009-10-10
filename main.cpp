/* 
 * File:   main.cpp
 * Author: franta
 *
 * Created on 27. září 2009, 20:09
 */

#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
#include "Polozka.h"
#include <vector>
#include <sys/times.h>
#include <ctime>
#include <time.h>
#include <algorithm>
/*
 * 
 */
int kapacita = 0;
int nejlepsiCena = 0;
int polozek = 0;
using namespace std;

clock_t startCas, konecCas;
double cpuCas;
//struct tms startBuff;
//struct tms endBuff;


void Tokenize(const string& str,
                      vector<string>& tokens,
                      const string& delimiters = " ")
{
    // Skip delimiters at beginning.
    string::size_type lastPos = str.find_first_not_of(delimiters, 0);
    // Find first "non-delimiter".
    string::size_type pos     = str.find_first_of(delimiters, lastPos);

    while (string::npos != pos || string::npos != lastPos)
    {
        // Found a token, add it to the vector.
        tokens.push_back(str.substr(lastPos, pos - lastPos));
        // Skip delimiters.  Note the "not_of"
        lastPos = str.find_first_not_of(delimiters, pos);
        // Find next "non-delimiter"
        pos = str.find_first_of(delimiters, lastPos);
    }
}


/*reads the file to 2D array*/
vector< vector<Polozka*> > nactiData(char*soubor){
    ifstream input(soubor);
    string line;
    vector<string> vekturek;
    int radek = 0;
    int iterator = 3;
    getline(input, line);
    Tokenize(line, vekturek);
    int velikostPole = atoi(vekturek[1].c_str());
    polozek = velikostPole;
    kapacita = atoi(vekturek[2].c_str());
    cout<<"velikost pole:"<<velikostPole<<endl;
    vekturek.clear();
    vector< vector< Polozka* > > pole;
    int i = 0;
    while(i<50){
        //cout<<i<<endl;
    pole.push_back( vector<Polozka*>(velikostPole));
    i++;
    }
    do{
        Tokenize(line, vekturek);
        for(int j = 0;j<velikostPole;j++){
            pole[radek][j] = new Polozka(atoi(vekturek[iterator].c_str()),atoi(vekturek[iterator+1].c_str()));
            if(j==0){cout<<radek<<": <";}
            cout<<pole[radek][j]->cena<<"/"<<pole[radek][j]->hmotnost<<"|";
            if(j==velikostPole-1){
                cout<<">"<<endl;
            }
            iterator+=2;
        }
        iterator = 3;
        radek++;
        vekturek.clear();
    }while(getline(input, line));
    input.close();

    return pole;
}

void bruteforce(int n, int zbyva, int cena, vector<Polozka*> pripad){
    //cout<<zbyva<<" cena : "<<cena<<"n: "<<n<<endl;
    if(zbyva < 0) return;
    if(cena>nejlepsiCena){
        nejlepsiCena = cena;
    }
    if(n < 0) return;
    
    bruteforce(n-1,zbyva-pripad[n]->hmotnost,cena+pripad[n]->cena,pripad);
    bruteforce(n-1,zbyva,cena,pripad);
}

void  BubbleSort(vector <Polozka *> &pole)
{
      int i, j, flag = 1;    // set flag to 1 to start first pass
      Polozka* temp;             // holding variable
      int numLength = pole.size();
      for(i = 1; (i <= numLength) && flag; i++)
     {
          flag = 0;
          for (j=0; j < (numLength-1); j++)
         {
             // cout<<(double)((double)pole[j+1]->cena/(double)pole[j+1]->hmotnost)<<" < "<<(double)((double)pole[j]->cena/(double)pole[j]->hmotnost)<<endl;
               if ((double)((double)pole[j+1]->cena/(double)pole[j+1]->hmotnost) > (double)((double)pole[j]->cena/(double)pole[j]->hmotnost))      // ascending order simply changes to <
              {
                   
                    temp = pole[j];             // swap elements
                    pole[j] = pole[j+1];
                    pole[j+1] = temp;
                    flag = 1;               // indicates that a swap occurred.
               }
          }
     }
     

     return ;   //arrays are passed to functions by address; nothing is returned
}

void greedy(vector<Polozka*> pripad){

    BubbleSort(pripad);
   /*
    for(int x = 0;x<polozek;x++){
          cout<<(double)((double)pripad[x]->cena/(double)pripad[x]->hmotnost)<<endl;
      }*/
    int greedyOut = 0;
    int zbyva = kapacita;
    for(int i = 0;i<pripad.size()&&zbyva>0;i++){
        if(zbyva-pripad[i]->hmotnost>=0){
            greedyOut+=pripad[i]->cena;
            zbyva-=pripad[i]->hmotnost;
        }
        
    }
    nejlepsiCena = greedyOut;
    //cout<<zbyva<<endl;

    return;

}



int main(int argc, char** argv) {
    cout<<argc;
    if (argc < 3 && argc > 4) {
        cerr << "syntax: command <filename> <typeOfMethod> [repetitions] \n typeOfMethod ... 0 - bruteforce, 1 - greedy\n";
    } else {
        
        
        if (strcmp(argv[2], "0") == 0) {
            cerr<<"reading data\n";

           vector< vector<Polozka*> > pole = nactiData(argv[1]);
            cerr<< kapacita;
            cerr<<"doing bruteforce\n";
            int opakovani = 1;
            if(argc == 4){
                opakovani = atoi(argv[3]);
            }
            for(int radek = 0;radek<50;++radek){
                int i = opakovani;
                startCas = clock();
                while(i>0){
            bruteforce(polozek-1,kapacita,0,pole[radek]);
            i--;
                }
                konecCas = clock();
                cpuCas = ((double(konecCas)-double(startCas))/CLOCKS_PER_SEC)/opakovani;
            cout<<radek+1<<": "<<nejlepsiCena<<" |cas: "<<cpuCas<<endl;
            nejlepsiCena = 0;
            }
        } else if (strcmp(argv[2],"1") == 0) {
            cerr<<"reading data\n";
            vector< vector<Polozka*> > pole = nactiData(argv[1]);
            cerr<<"doing greedy\n";
            int opakovani = 1;
            if(argc == 4){
                opakovani = atoi(argv[3]);
            }
            for(int radek = 0;radek<50;++radek){

                int i = opakovani;
          //      startCas = times(&startBuff);
                startCas = clock();
                while(i>0){
            greedy(pole[radek]);
            i--;
                }
                    konecCas = clock();
           // konecCas = times(&endBuff);
            cpuCas = ((double(konecCas)-double(startCas))/CLOCKS_PER_SEC)/opakovani;
            cout<<radek+1<<": "<<nejlepsiCena<<" |cas: "<<cpuCas<<endl;
            //cout<<radek+1<<": "<<nejlepsiCena<<" |cas: "<<(double)(endBuff.tms_utime-startBuff.tms_utime)*10000/CLOCKS_PER_SEC<<endl;
            nejlepsiCena = 0;
            }
        } else {
            cerr << "syntax: command <filename> <typeOfMethod>\n typeOfMethod ... 0 - bruteforce, 1 - greedy\n";
        }
    }
    return (EXIT_SUCCESS);
}

