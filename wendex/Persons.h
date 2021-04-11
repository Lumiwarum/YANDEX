#ifndef WENDEX_PERSONS_H
#define WENDEX_PERSONS_H
#include "worldData.h"
#include <vector>

using namespace std;

class person {
private:
    string name;
    string surname;
public:
    person(string name,string surname){
        this->name=name;
        this->surname=surname;
    }
    string getName(){
        return name;
    }
    string getSurname(){
        return surname;
    }
};

class Passenger: public person{
private:
    int rating;
    payments paymentMethod;
    vector<coordinate> pinnedAddresses;
    vector<order> orderHistory;
public:
    Passenger(string name,string surname,int rate,payments pay): person(name,surname){
        rating=rate;
        paymentMethod=pay;
    }
    Passenger(): person("Ivan","Ivanov"){

    }
    int getRating(){
        return rating;
    }
    payments getPayMethod(){
        return paymentMethod;
    }
    void setPayMethod(payments newpay){
        paymentMethod=newpay;
    }
    void addPinnedAddress(coordinate cord){
        pinnedAddresses.push_back(cord);
    }
    vector<coordinate> getPinnedAddresses(){
        return pinnedAddresses;
    }
};

class Driver: public person{
private:
    Car taxi;
    int rating;
    bool working;
    bool driving;
    vector<order> orderHistory;
public:
    Driver(string Name,string Surname,Car car,int rate): person(Name,Surname){
        taxi=car;
        rating=rate;
        working = true;
        driving= false;
    }
    Car getCar(){
        return taxi;
    }
    int getRating(){
        return  rating;
    }
    bool isDriving(){
        return driving;
    }
};
#endif //WENDEX_PERSONS_H
