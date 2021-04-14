#include <iostream>
#include "System.h"
/* Yandex Taxi
 *
 * @author Kirilin Anton
 * @version 1.0
 * @since 14.04.2021
 */
void example0(){
    System systema;
    PassengerGateway& mobApp=systema.getPassengersApp();
    DriverGateway& drApp=systema.getDriverApp();
    cout <<"This is the first launch of the program"<<endl;
    Passenger passenger("Andrey","Kuzmickiy",5,cash);
    mobApp.addPassenger(passenger);
    Car waterSupply("waterTruck",ComfortPlus);
    Driver driver("Sergay","Pasynkov",waterSupply,5,0);
    drApp.addDriver(driver);
    cout <<"At this time we added one passenger and one driver."<<endl;
    cout <<"Their names Andrey and Sergey,You can see their data saved in Data.txt"<<endl;
}
void example1(){
    System systema;
    PassengerGateway& mobApp=systema.getPassengersApp();
    DriverGateway& drApp=systema.getDriverApp();
    cout <<"Now you launch the program second time< let's see saved information from previous launch."<<endl;
    cout <<"Names and surnames:"<<endl;
    mobApp.logIn(mobApp.searchBySurname("Kuzmickiy"));
    drApp.logIn(drApp.searchBySurname("Pasynkov"));
    cout <<mobApp.currentPassenger().getName()<<" "<<mobApp.currentPassenger().getSurname()<<endl;
    cout <<drApp.currentDriver().getName()<<" "<<drApp.currentDriver().getSurname()<<endl;
    cout <<"Now let's add new persons and give some orders"<<endl;
    mobApp.addPassenger(Passenger("Anton","kirilin",3,cash));
    mobApp.addPassenger(Passenger("Lev","Kozlov",5,creditCard));
    order orderToAdd(coordinate(),coordinate(3,4),Business);
    mobApp.logIn(0);// logIn as Andrey( he is the first person
    orderToAdd.setPayment(mobApp.currentPassenger().getPayMethod());// update payments( by default they are cash)
    orderToAdd.setPassenger(mobApp.currentPassenger().getSurname());// add details to order
    mobApp.currentPassenger().addOrderToHistory(orderToAdd); // add order to order of history< notice that it has bool variable for compliting
    mobApp.orderRide(orderToAdd);// push order to our system
    cout <<"Now we added order to Andrey, he wants to go on car with type ";
    cout <<orderToAdd.getCarType()<<" which means business type(45 is its speed in enum)"<<endl;
    cout <<"Move from coordinates "<<orderToAdd.getFromPlace().getXCoord()<<" "<<orderToAdd.getFromPlace().getYCoord()<<endl;
    cout <<"To coordinates "<<orderToAdd.getToPlace().getXCoord()<<" "<<orderToAdd.getToPlace().getYCoord()<<endl;
    cout <<"He'll need to pay "<<orderToAdd.getCost()<<" and will come in "<<orderToAdd.getTime()<<" seconds or something"<<endl;
    cout <<"Now we'll log into another account(me) and add next order"<<endl;
    mobApp.logIn(1);
    orderToAdd=order(coordinate(),coordinate(14,48),ComfortPlus);
    orderToAdd.setPayment(mobApp.currentPassenger().getPayMethod());
    orderToAdd.setPassenger(mobApp.currentPassenger().getSurname());
    mobApp.currentPassenger().addOrderToHistory(orderToAdd);
    mobApp.orderRide(orderToAdd);
    cout <<"We added this order, now let's add new drivers and give to them my order,that satisfy carType"<<endl;
    Car comfor("BMW",Comfort);
    Car super("Tank",ComfortPlus);
    Driver driver("Andrey","Vagin",comfor,3,0);
    drApp.addDriver(driver);
    drApp.addDriver(Driver("Artem","Voronov",super,4,1));
    drApp.logIn(2);
    drApp.updateOrders(mobApp.getOrders());
    orderToAdd=drApp.acceptOrder(1);//not honest matching, but 1(second) order is satisfy comfortPlus
    mobApp.logIn(1);
    mobApp.currentPassenger().getOrder(0).completeOrder();
    orderToAdd.setDriver(drApp.currentDriver().getSurname());
    drApp.currentDriver().addOrderToHistory(orderToAdd);
    cout <<"Now Artem voronov on the Tank accepted my order, so this is the end for this launch -> check Data.txt"<<endl;
    cout <<"And rerun program";
    return;
}
void example2(){
    System systema;
    PassengerGateway& mobApp=systema.getPassengersApp();
    DriverGateway& drApp=systema.getDriverApp();
    cout <<"This is the 3rd launch of program, Let's check unaccepted orders"<<endl;
    vector<order> orders=mobApp.getOrders();
    for (order curOrder:orders){
        cout <<"From coordinates X:"<<curOrder.getFromPlace().getXCoord()<<" Y:"<<curOrder.getFromPlace().getYCoord()<<endl;
        cout <<"To coordinates X:"<<curOrder.getToPlace().getXCoord()<<" Y:"<<curOrder.getToPlace().getYCoord()<<endl;
        cout <<"Cost of the ride "<<curOrder.getCost()<<" expected time "<<curOrder.getTime()<<endl;
        cout <<"Surnames of the passenger and driver are respectively:"<<endl;
        cout <<curOrder.getPassengerSurname()<<" "<<curOrder.getDriverSurname()<<endl;
    }
    cout <<"As you can see, because no one took this order, we don't have drivers name(noname)"<<endl;
    cout <<"Now let's check whether users can see price and time without ordering"<<endl;
    cout <<"because we have already one order in process,compare with it"<<endl;
    drApp.logIn(2);
    cout<<"Time: "<<mobApp.seeTime(orders.back().getFromPlace(),orders.back().getToPlace(),orders.back().getCarType());
    cout<<" cost: "<<mobApp.seePrice(orders.back().getFromPlace(),orders.back().getToPlace(),orders.back().getCarType())<<endl;
    cout <<"They are the same and we don't create any new order "<<endl;
    cout <<"That all for examples"<<endl;
    return;
}
void defaultCase(){
    System systema;
    PassengerGateway& mobApp=systema.getPassengersApp();
    DriverGateway& drApp=systema.getDriverApp();
    cout <<"All examples are ended, now you can just see, that data.txt is saving"<<endl;
    cout <<"If you want to restart examples-> change value in Example.txt to 0 and run the program"<<endl;
    cout <<"Let's just print all users"<<endl;
    for (Passenger curPass:mobApp.getPassengers()){
        cout <<curPass.getName()<<" "<<curPass.getSurname()<<endl;

    }
    for (Driver curDriver : drApp.getDrivers()){
        cout <<curDriver.getName()<<" "<<curDriver.getSurname()<<endl;
    }
    return;
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
        case 0:
            example0();
            break;
        case 1:
            example1();
            break;
        case 2:
            example2();
            break;
        default:
            defaultCase();
            break;
    }
fout <<caseof+1;
    fout.close();
    return 0;
}
