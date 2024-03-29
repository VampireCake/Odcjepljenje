#include <bits/stdc++.h>
#include "fje_poker.cpp"

using namespace std;

int main(){
    cout<<"Unesite broj igrača: ";
    int igraci = brojIgraca();
    bool ispravnaRuka = true;
    char znakKarte [5];
    int brojKarte [5];
    int kartePoRedoslijedu[5];
    long double score[6]={0, 0, 0, 0, 0, 0}; 
    cout<<"Unosite svoje karte."<<endl;

    while(ispravnaRuka){
        for(int i=0; i<=4; i++){
            cout<<"Unesite znak "<< i+1 <<". karte:"<<endl;
            znakKarte[i] = unosZnakaKarte();
            cout<<"Unesite broj "<< i+1 <<". karte:"<<endl;
            brojKarte[i] = unosBrojaKarte();
            kartePoRedoslijedu[i] = brojKarte[i];
        }
        cout<<endl;

        for(int j=0; j<=4; j++){
            if((znakKarte[j]==znakKarte[j-1] && brojKarte[j]==brojKarte[j-1]) ||
               (znakKarte[j]==znakKarte[j-2] && brojKarte[j]==brojKarte[j-2]) ||
               (znakKarte[j]==znakKarte[j-3] && brojKarte[j]==brojKarte[j-3]) ||
               (znakKarte[j]==znakKarte[j-4] && brojKarte[j]==brojKarte[j-4]) ){
                cout<<"Nije moguće imati dvije iste karte u ruci, unesite ponovo karte!"<<endl;
                break;
            }
            else{
                ispravnaRuka = false;
            }
        }
    }

    sort(kartePoRedoslijedu, kartePoRedoslijedu + 5);

    if(sviZnakoviIsti(znakKarte)){
        if(royalFlush(kartePoRedoslijedu)){
            cout<<"Imate Royal Flush"<<endl;
            score[0] = 10;
        }
        else if (straightFlush(kartePoRedoslijedu)){
            cout<<"Imate Straight Flush"<<endl;
            score[0] = 9;
            score[1] = snagaSF(kartePoRedoslijedu);
        }
        else{
            cout<<"Imate Flush"<<endl;
            score[0] = 6;
            score[1] = snaga1F(acesInFront(kartePoRedoslijedu));
            score[2] = snaga2F(acesInFront(kartePoRedoslijedu));
            score[3] = snaga3F(acesInFront(kartePoRedoslijedu));
            score[4] = snaga4F(acesInFront(kartePoRedoslijedu));
            score[5] = snaga5F(acesInFront(kartePoRedoslijedu));
        }

    }
    else{
        if(fourOfAKind(kartePoRedoslijedu)){
            cout<<"Imate Four Of A Kind"<<endl;
            score[0] = 8;
            score[1] = snagaFOAK(kartePoRedoslijedu);
            if (score[1] == 1){
                score[1] = 15;
            }
            score[2] = snaga2FOAK(kartePoRedoslijedu, kojiFOAK(kartePoRedoslijedu));
        }

        else{
            if(fullHouse(kartePoRedoslijedu)){
                cout<<"Imate Full House"<<endl;
                score[0] = 7;
                score[1] = snagaFH(kartePoRedoslijedu);
                if (score[1] == 1){
                    score[1] = 15;
                }
            }
            else if(straight(kartePoRedoslijedu)){
                cout<<"Imate Straight"<<endl;
                score[0] = 5;
                if(kartePoRedoslijedu[1]==2){
                    score[1] = snagaS(kartePoRedoslijedu);
                }
                else{
                    score[1]= snagaS(acesInFront(kartePoRedoslijedu));
                }
            }
            else{
                if(threeOfAKind(kartePoRedoslijedu)){
                    cout<<"Imate Three Of A Kind"<<endl;
                    score[0] = 4;
                    score[1] = snagaTOAK(kartePoRedoslijedu);
                    if (score[1] == 1){
                        score[1] = 15;
                    }
                }
                else if(twoPair(kartePoRedoslijedu)){
                    cout<<"Imate Two Pair"<<endl;
                    score[0] = 3;
                    score[1] = snaga1TP(acesInFront(kartePoRedoslijedu));
                    score[2] = snaga2TP(acesInFront(kartePoRedoslijedu));
                    score[3] = snaga3TP(acesInFront(kartePoRedoslijedu), kojiTP(kartePoRedoslijedu));
                }
                else{
                    if(onePair(kartePoRedoslijedu)){
                        cout<<"Imate Pair"<<endl;
                        score[0] = 2;
                        score[1] = snaga1P(acesInFront(kartePoRedoslijedu), kojiP(kartePoRedoslijedu));  
                        score[2] = snaga2P(acesInFront(kartePoRedoslijedu), kojiP(kartePoRedoslijedu));
                        score[3] = snaga3P(acesInFront(kartePoRedoslijedu), kojiP(kartePoRedoslijedu));
                        score[4] = snaga4P(acesInFront(kartePoRedoslijedu), kojiP(kartePoRedoslijedu));
                    }
                    else{
                        cout<<"Imate High Card"<<endl;
                        score[0] = 1;
                        score[1] = acesInFront(kartePoRedoslijedu)[4];    
                        score[2] = acesInFront(kartePoRedoslijedu)[3];
                        score[3] = acesInFront(kartePoRedoslijedu)[2];
                        score[4] = acesInFront(kartePoRedoslijedu)[1];
                        score[5] = acesInFront(kartePoRedoslijedu)[0];
                        if(score[1] == 7){
                            cout<<"IMATE KITU"<<endl;
                        }
                    }         
                }
            }
        }
    }                    // treba sad uraditi matematiku za procjenu pobjede
                        // treba napraviti 12 13 14 da J Q K (mozda 1 da je A)
                       // malo napraviti i unos da je ljepsi

    long double šansaZaPobjedu;

    cout<<score[0]<<endl<<score[1]<<endl<<score[2]<<endl<<score[3]<<endl<<score[4]<<endl<<score[5]<<endl;


    cout<<evaluacija(score);
}
