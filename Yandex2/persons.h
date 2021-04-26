#ifndef YANDEX2_PERSONS_H
#define YANDEX2_PERSONS_H
#include "worldData.h"
#include <vector>
using namespace std;

class person {
protected:
    bool isAdmin=false;
    string name;
    string surname;
    vector<order> orderHistory;
public:
    person(string name,string surname){
        this->name=name;
        this->surname=surname;
    }
    bool personIsAdmin(){
        return isAdmin;
    }
    string getName(){
        return name;
    }
    string getSurname(){
        return surname;
    }
    virtual void addOrderToHistory(order ord){
        orderHistory.push_back(ord);
    }
    order& getOrder(int i){
        if ((i>-1)&&(i<orderHistory.size())){
            return orderHistory[i];
        }
    }
    vector<order>& getOrderHistory(){
        return orderHistory;
    }
};

class Passenger: public person, public booleans{
private:
    vector<Phone> phones;
    int rating;
    payments paymentMethod;
    vector<coordinate> pinnedAddresses;
public:
    Passenger(string name,string surname,int rate,payments pay): person(name,surname),booleans(true,false,true,false){
        rating=rate;
        paymentMethod=pay;
    }
    Passenger(): person("Ivan","Ivanov"),booleans(true,false,true,false){

    }
    int getRating(){
        return rating;
    }
    vector<Phone> getPhones(){
        return phones;
    }
    Phone getPhone(int i){
        if ((i>-1)&&(i<phones.size())){return phones[i];}
        return Phone();// invalid Phone with noName
    }
    void addPhone(Phone phoneToAdd){
        phones.push_back(phoneToAdd);
    }
    payments getPayMethod(){
        return paymentMethod;
    }
    void setPayMethod(payments newPay){
        try{
            if (!canChange()){throw -1;}
        paymentMethod=newPay;}
        catch (int i){
            cout <<"SYSTEM: "<<name<<" "<<surname<<" cannot change payment methods"<<endl;
        }
    }
    void addPinnedAddress(coordinate cord){
        pinnedAddresses.push_back(cord);
    }
    vector<coordinate> getPinnedAddresses(){
        return pinnedAddresses;
    }
    void forbidChangingPayments(person admin){
        try {
            if (admin.personIsAdmin()){
                canChangePayment=false;
            } else {throw -1;}
        } catch (int i){
            cout <<"SYSTEM: Person "<<admin.getName()<<" "<<admin.getSurname()<<" is not an admin"<<endl;
        }
    }
    void forbidOrderingRide(person admin){
        try {
            if (admin.personIsAdmin()){
                canOrderRide=false;
            } else {throw -1;}
        } catch (int i){
            cout <<"SYSTEM: Person "<<admin.getName()<<" "<<admin.getSurname()<<" is not an admin"<<endl;
        }
    }
    void letChangingPayments(person admin){
        try {
            if (admin.personIsAdmin()){
                canChangePayment=true;
            } else {throw -1;}
        } catch (int i){
            cout <<"SYSTEM: Person "<<admin.getName()<<" "<<admin.getSurname()<<" is not an admin"<<endl;
        }
    }
    void letOrderingRide(person admin){
        try {
            if (admin.personIsAdmin()){
                canOrderRide=true;
            } else {throw -1;}
        } catch (int i){
            cout <<"SYSTEM: Person "<<admin.getName()<<" "<<admin.getSurname()<<" is not an admin"<<endl;
        }
    }
};

class Driver: public person, public booleans{
private:
    vector<Car> validatedCars;
    vector<Car> notValidatedCars;
    int rating;
    bool driving;
public:
    Driver(string Name,string Surname,int rate,bool driving): person(Name,Surname),booleans(false,true,false,true){
        rating=rate;
        this->driving= driving;
    }
    void addNewCar(Car newCar){
        try{
        if (!canAddNewCar){throw -1;}
        notValidatedCars.push_back(newCar);}
        catch (int i){
            cout <<"SYSTEM: "<<name<<" "<<surname<<" cannot add new car, because admin blocked this ability"<<endl;
        }
    }
    Car getCar(int i){
        if ((i>=0)&&(i<validatedCars.size()))
        return validatedCars[i];
    }
    vector<Car> getCars(){
        return validatedCars;
    }
    vector<Car> getNonValidateCars(){
        return notValidatedCars;
    }
    void validateCar(person admin,int number){
        if (admin.personIsAdmin()){
            if ((number>-1)&&(number<notValidatedCars.size())){
                validatedCars.push_back(notValidatedCars[number]);
                notValidatedCars.erase(notValidatedCars.begin()+number);
            }
        }
    }
    void changeRiding(){
        if (driving){driving=false;}
        else {driving=true;}
    }
    int getRating(){
        return  rating;
    }
    bool isDriving(){
        return driving;
    }
    void forbidAcceptingOrders(person admin){
        try {
            if (admin.personIsAdmin()){
                canAcceptRide=false;
            } else {throw -1;}
        } catch (int i){
            cout <<"SYSTEM: Person "<<admin.getName()<<" "<<admin.getSurname()<<" is not an admin"<<endl;
        }
    }
    void letAcceptingOrders(person admin){
        try {
            if (admin.personIsAdmin()){
                canAcceptRide=true;
            } else {throw -1;}
        } catch (int i){
            cout <<"SYSTEM: Person "<<admin.getName()<<" "<<admin.getSurname()<<" is not an admin"<<endl;
        }
    }
    void forbidAddingCars(person admin){
        try {
            if (admin.personIsAdmin()){
                canAddNewCar=false;
            } else {throw -1;}
        } catch (int i){
            cout <<"SYSTEM: Person "<<admin.getName()<<" "<<admin.getSurname()<<" is not an admin"<<endl;
        }
    }
    void letAddingCars(person admin){
        try {
            if (admin.personIsAdmin()){
                canAddNewCar=true;
            } else {throw -1;}
        } catch (int i){
            cout <<"SYSTEM: Person "<<admin.getName()<<" "<<admin.getSurname()<<" is not an admin"<<endl;
        }
    }
};
class Admin: public person{
public:
    Admin(string name,string surname):person(name,surname){
        isAdmin=true;
    }

};
#endif //YANDEX2_PERSONS_H
