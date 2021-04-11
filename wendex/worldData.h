#ifndef WENDEX_WORLDDATA_H
#define WENDEX_WORLDDATA_H
#include <cmath>
using namespace std;

enum payments{
    cash,
    creditCard,
    cheque
};
enum carType{
    Economy=10,
    Comfort=20,
    ComfortPlus=25,
    Business=40
};
class coordinate{
private:
    int x;
    int y;
public:
    coordinate(){
        x=0;
        y=0;
    }
    coordinate(int a,int b){
        x=a;
        y=b;
    }
    void setXCoord(int a){
        x=a;
    }
    void setYCoord(int a){
        y=a;
    }
    int getXCoord(){
        return x;
    }
    int getYCoord(){
        return y;
    }
    int Distance(coordinate second){
       int dis=(int)sqrt(pow((second.getXCoord()-x),2)+pow((second.getYCoord()-y),2));
        return dis;
    }
};

class order{
private:
    carType typeOfCar;
    bool completed;
    int cost;
    payments payMethod;
    int time;
    coordinate From;
    coordinate To;
public:
    order(coordinate from,coordinate to,carType car){
        time=0;
        From=from;
        To=to;
        completed=false;
    }
    coordinate getToPlace(){
        return To;
    }
    coordinate getFromPlace(){
        return From;
    }
    void setPayment(payments pay){
        payMethod=pay;
    }
    payments getPayMethod(){
        return payMethod;
    }
    int getDistance(){
        return To.Distance(From);
    }
};
class Car{
private:
    carType typeOfCar;
    coordinate currentLocation;
    string model;
    int numberOfCar;
    static inline int numberCars=0;
public:
    Car(){

    }
    Car(string mod,carType type){
        numberOfCar=++numberCars;
        model=mod;
        typeOfCar=type;
    }
    carType getCarType(){
        return typeOfCar;
    }
    int getCarNumber(){
        return numberOfCar;
    }
    string getModel(){
        return model;
    }
    void setLocation(coordinate cor){
        currentLocation=cor;
    }
    coordinate getLocation(){
        return currentLocation;
    }
};

#endif //WENDEX_WORLDDATA_H
