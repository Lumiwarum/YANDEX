#include <iostream>
#include "worldData.h"
#include "System.h"
#include <fstream>

using namespace std;

void paymentMethod(int i){
    switch (i) {
        case 0:
            cout <<"cash";
            break;
        case 1:
            cout <<"credit card";
            break;
        case 2:
            cout <<"cheque";
            break;
        default:
            break;
    }
}
void loginPassenger(PassengerGateway& mobApp){
    cout <<"Enter Your Name and Surname"<<endl;
    string name,surname;
    cin >>name>>surname;
    Passenger user(name,surname,4,cash);
    int i;
    i= mobApp.searchForPerson(user);
    if (i<0){
        cout <<"There is no such user"<<endl;
        return;}
    mobApp.logIn(i);
    while(mobApp.isLogged()){
        cout <<"Type what do you want"<<endl;
        cout <<"1 : see payment method"<<endl;
        cout <<"2 : change payment method"<<endl;
        cout <<"3 : see pinned address"<<endl;
        cout <<"4 : update pinned address"<<endl;
        cout <<"5 : check price and time for a ride"<<endl;
        cout <<"6 : order a ride"<<endl;
        cout <<"7 : log out"<<endl;
        int pcase;
        cin >>pcase;
        switch (pcase) {
            case 1:{
                int method=mobApp.currentPassenger().getPayMethod();
                cout <<"Your current payment method: ";
                paymentMethod(method);
                cout <<endl;
                break;
            }
            case 2:{
                cout <<"Type preferable Payment method"<<endl;
                cout <<"1 : cash"<<endl<<"2 : credit card"<<endl<<"3 : cheque"<<endl;
                int paymen;
                cin >>paymen;
                Passenger user;
                switch (paymen) {
                    case 1: {
                        mobApp.currentPassenger().setPayMethod(cash);
                        break;
                    }
                    case 2: {
                        mobApp.currentPassenger().setPayMethod(creditCard);
                        break;
                    }
                    case 3: {
                        mobApp.currentPassenger().setPayMethod(cheque);
                        break;
                    }
                    default:
                        cout <<"incorrect data, return to previous question"<<endl;
                        return;
                }
                break;
            }
            case 3:{
                vector<coordinate> addresses=mobApp.currentPassenger().getPinnedAddresses();
                cout <<"Your pinned addresses:"<<endl;
                for (coordinate curCord : addresses){
                    cout <<"X: "<<curCord.getXCoord()<<" Y: "<<curCord.getYCoord()<<endl;
                }
                break;
            }
            case 4:{
                cout <<"Type X and Y coordinates of new address"<<endl;
                int x,y;
                cin >>x>>y;
                coordinate pin(x,y);
                mobApp.currentPassenger().addPinnedAddress(pin);
                cout <<"address added"<<endl;
                break;
            }
            case 5:{
                cout <<"Type coordinates X and Y of FROM point"<<endl;
                int x,y;
                cin >>x>>y;
                coordinate from(x,y);
                cout <<"Type coordinates X and Y of TO point"<<endl;
                cin >>x>>y;
                coordinate to(x,y);
                cout <<"Choose type of car"<<endl;
                cout <<"1 : economy"<<endl<<"2 : comfort"<<endl<<"3 : comfortPlus"<<endl<<"4 : business"<<endl;
                int i,price,time;
                cin >>i;
                switch (i){
                    case 1:{
                        price=mobApp.seePrice(from,to,Economy);
                        time=mobApp.seeTime(from,to,Economy);
                        break;
                    }
                    case 2:{
                        price=mobApp.seePrice(from,to,Comfort);
                        time=mobApp.seeTime(from,to,Comfort);
                        break;
                    }
                    case 3:{
                        price=mobApp.seePrice(from,to,ComfortPlus);
                        time=mobApp.seeTime(from,to,ComfortPlus);
                        break;
                    }
                    case 4:{
                        price=mobApp.seePrice(from,to,Business);
                        time=mobApp.seeTime(from,to,Business);
                        break;
                    }
                }
                cout <<"Price will be: "<<price<<endl;
                cout <<"Time will be: "<<time<<endl;
                break;
            }
            case 6:{cout <<"Type coordinates X and Y of FROM point"<<endl;
                int x,y;
                cin >>x>>y;
                coordinate from(x,y);
                cout <<"Type coordinates X and Y of TO point"<<endl;
                cin >>x>>y;
                coordinate to(x,y);
                cout <<"Choose type of car"<<endl;
                cout <<"1 : economy"<<endl<<"2 : comfort"<<endl<<"3 : comfortPlus"<<endl<<"4 : business"<<endl;
                int i,price,time;
                cin >>i;
                switch (i){
                    case 1:{
                        mobApp.orderRide(from,to,Economy);
                        break;
                    }
                    case 2:{
                        mobApp.orderRide(from,to,Comfort);
                        break;
                    }
                    case 3:{
                        mobApp.orderRide(from,to,ComfortPlus);
                        break;
                    }
                    case 4:{
                        mobApp.orderRide(from,to,Business);
                        break;
                    }
                }
                cout <<"You've ordered a ride"<<endl;
                break;
            }
            case 7:{
                mobApp.logOut();
                return;
            }
            default:
                cout <<"incorrect value, please try again"<<endl;
                break;
        }
    }
}

void createPassenger(PassengerGateway& mobApp){
    cout <<"Enter Your Name and Surname"<<endl;
    string name,surname;
    cin >>name>>surname;
    cout <<"Type preferable Payment method"<<endl;
    cout <<"1 : cash"<<endl<<"2 : credit card"<<endl<<"3 : cheque"<<endl;
    int paymen;
    cin >>paymen;
    Passenger user;
    switch (paymen) {
        case 1: {
            Passenger pu(name, surname, 5, cash);
            user = pu;
            break;
        }
        case 2: {
            Passenger pu(name, surname, 5, creditCard);
            user = pu;
            break;
        }
        case 3: {
            Passenger pu(name, surname, 5, cheque);
            user = pu;
            break;
        }
        default:
            cout <<"incorrect data, return to previous question"<<endl;
            return;
    }
    mobApp.addPassenger(user);
    return;
}

void shutdownSystem(PassengerGateway& mobApp){
    ofstream fout;
    fout.open("../Data.txt");
    vector<Passenger> passengers;
    passengers=mobApp.getPassengers();
    fout <<passengers.size()<<endl;
    for (Passenger curPassenger : passengers){
        fout<<curPassenger.getName()<<" "<<curPassenger.getSurname()<<" "<<curPassenger.getRating()<<" ";
        fout<<curPassenger.getPayMethod()<<endl;
    }
    fout.close();
}

int main() {
    ifstream fin("../Data.txt");
    vector<Passenger> passengers;
    int n=0,rate,pay; string name,surname;
    if (fin.peek()!='\0'){fin >>n;}
    for (int i = 0;i<n;i++){
        fin >>name>>surname>>rate>>pay;
        switch (pay+1){
            case 1: {
                Passenger pu(name, surname, 5, cash);
                passengers.push_back(pu);
                break;
            }
            case 2: {
                Passenger pu(name, surname, 5, creditCard);
                passengers.push_back(pu);
                break;
            }
            case 3: {
                Passenger pu(name, surname, 5, cheque);
                passengers.push_back(pu);
                break;
            }
            default:
                break;
        }

    }
    PassengerGateway mobApp(passengers);
    bool programWorking=true; 
    while (programWorking){
        cout <<"Welcome to Wendex Taxi, type what do you want"<<endl;
        cout <<"1 : Log in the system as passenger"<<endl;
        cout <<"2 : Log in the system as driver"<<endl;
        cout <<"3 : Create passenger account"<<endl;
        cout <<"4 : Create driver account"<<endl;
        cout <<"5 : Shutdown system"<<endl;
        int type;
        cin >>type;
        switch (type) {
            case 1:
                loginPassenger(mobApp);
                break;
            case 2:
                break;
            case 3:
                createPassenger(mobApp);
                break;
            case 4:
                break;
            case 5:
                cout <<" Saving data, deactivating system"<<endl;
                shutdownSystem(mobApp);
                return 0;
            default:
                cout <<"incorrect data, system is deactivated, data wasn't saved"<<endl;
                return 0;
        }
    }
}
