#include <iostream>
#include "System.h"

void example1(){
    System systema;
    PassengerGateway& mobApp=systema.getPassengersApp();
    DriverGateway& drApp=systema.getDriverApp();
    mobApp.addPassenger(Passenger("Anton","kirilin",3,cash));
    mobApp.addPassenger(Passenger("Lev","Kozlov",5,creditCard));
    order orderToAdd(coordinate(),coordinate(3,4),Business);
    mobApp.logIn(0);
    orderToAdd.setPayment(mobApp.currentPassenger().getPayMethod());
    orderToAdd.setPassenger(mobApp.currentPassenger().getSurname());
    mobApp.currentPassenger().addOrderToHistory(orderToAdd);
    mobApp.logIn(1);
    orderToAdd=order(coordinate(),coordinate(14,48),ComfortPlus);
    orderToAdd.setPayment(mobApp.currentPassenger().getPayMethod());
    mobApp.currentPassenger().addOrderToHistory(orderToAdd);
    Car comfor("BMW",Comfort);
    Car super("Tank",ComfortPlus);
    Driver driver("Mossab","Muhhamed",comfor,3,0);
    drApp.addDriver(driver);
    drApp.addDriver(Driver("Artem","Voronov",super,4,1));
    drApp.logIn(2);
    drApp.currentDriver().addOrderToHistory(orderToAdd);
    return;
}
void example2(){
    System systema;
    PassengerGateway& mobApp=systema.getPassengersApp();
    DriverGateway& drApp=systema.getDriverApp();
    drApp.logIn(2);
    vector<order> orders=drApp.currentDriver().getOrderHistory();
    for (order curOrder : orders){
        cout <<curOrder.getPassengerSurname()<<" "<<curOrder.getDriverSurname()<<endl;
        cout <<curOrder.getCarType()<<" "<<curOrder.getCost()<<" "<<curOrder.getTime();
    }
    return;
}
void example3(){

}
int main() {
    ifstream fin;
    fin.open("../Example.txt");
    int caseof;
    fin >>caseof;
    fin.close();
    ofstream fout;
    fout.open("../Example.txt");
    switch(caseof){
        case 1:
            example1();
            break;
        case 2:
            example2();
            break;
        case 3:
                example3();
                break;
        default:
            System systema;
            PassengerGateway& mobApp=systema.getPassengersApp();
            DriverGateway& drApp=systema.getDriverApp();
            Passenger passenger("Gay","Activist",5,cash);
            mobApp.addPassenger(passenger);
            Car govnovoz("govnovoz",ComfortPlus);
            Driver driver("Sergay","Pasynkov",govnovoz,5,0);
            drApp.addDriver(driver);
            caseof=0;
            break;
    }
fout <<caseof+1;
    fout.close();
    return 0;
}
