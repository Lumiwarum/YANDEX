#include <iostream>
#include "System.h"
/* Yandex Taxi
 *
 * @author Kirilin Anton
 * @version 1.1
 * @since 26.04.2021
 */
void example0(){
    System systema;
    PassengerGateway& mobApp=systema.getPassengersApp();
    DriverGateway& drApp=systema.getDriverApp();
    AdminGateway& adminApp=systema.getAdminsApp();
    cout <<"This is the first launch of the program"<<endl;
    Passenger passenger("Andrey","Kuzmickiy",5,cash);
    mobApp.addPassenger(passenger);
    Car waterSupply("waterTruck",ComfortPlus);
    Driver driver("Sergey","Pasynkov",5,0);
    driver.addNewCar(waterSupply);
    drApp.addDriver(driver);
    cout <<"Lets add an Admin to our system"<<endl;
    Admin admin("Fedor","Krasilnikov");
    adminApp.addAdmin(admin);
    cout <<"Now let's approve first car"<<endl;
    drApp.logIn(0);
    drApp.currentDriver().validateCar(admin,0);
    cout <<"At this time we added one passenger,one admin and one driver."<<endl;
    cout <<"Their names Andrey,Fedor and Sergey,You can see their data saved in Data.txt"<<endl;
}
void example1(){
    System systema;
    PassengerGateway& mobApp=systema.getPassengersApp();
    DriverGateway& drApp=systema.getDriverApp();
    AdminGateway& adminApp=systema.getAdminsApp();
    cout <<"Now you launch the program second time< let's see saved information from previous launch."<<endl;
    cout <<"Names and surnames:"<<endl;
    mobApp.logIn(mobApp.searchBySurname("Kuzmickiy"));
    drApp.logIn(drApp.searchBySurname("Pasynkov"));
    adminApp.logIn(0);//let's just use at as one admin
    cout <<mobApp.currentPassenger().getName()<<" "<<mobApp.currentPassenger().getSurname()<<endl;
    cout <<drApp.currentDriver().getName()<<" "<<drApp.currentDriver().getSurname()<<endl;
    cout <<"Now let's add new persons and give some orders"<<endl;
    mobApp.addPassenger(Passenger("Anton","kirilin",3,cash));
    mobApp.addPassenger(Passenger("Lev","Kozlov",5,creditCard));
    order orderToAdd(coordinate(),coordinate(3,4),Business);
    mobApp.logIn(0);// logIn as Andrey( he is the first person)
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
    Driver driver("Andrey","Vagin",3,0);
    driver.addNewCar(comfor);
    drApp.addDriver(driver);
    cout <<"Also we need to approve this cars befoe the first ride"<<endl;
    drApp.logIn(drApp.searchBySurname("Vagin"));
    drApp.currentDriver().validateCar(adminApp.getCurrentAdmin(),0);
    driver=Driver("Artem","Voronov",4,1);
    driver.addNewCar(super);
    drApp.addDriver(driver);
    drApp.logIn(2);
    drApp.currentDriver().validateCar(adminApp.getCurrentAdmin(),0);
    drApp.updateOrders(mobApp.getOrders());
    orderToAdd=drApp.acceptOrder(1);//not honest matching, but 1(second) order is satisfy comfortPlus
    mobApp.logIn(1);
    mobApp.currentPassenger().getOrder(0).completeOrder();
    orderToAdd.setDriver(drApp.currentDriver().getSurname());
    cout <<"Now Artem Voronov on the Tank accepted my order, so this is the end for this launch -> check Data.txt"<<endl;
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
    cout <<"That all for examples of version 1.0 (except admin features)"<<endl;
    return;
}
void example3(){
    System systema;
    DriverGateway& dApp=systema.getDriverApp();
    PassengerGateway& pApp=systema.getPassengersApp();
    AdminGateway& adminApp=systema.getAdminsApp();
    cout <<"Now you can see new cases, that show new features of version 1.1"<<endl;
    cout <<"Let's add new cars to the drivers and block some functions"<<endl;
    dApp.logIn(dApp.searchBySurname("Voronov"));
    adminApp.logIn(0);//login as Fedor
    Car carToAdd("ferrari",ComfortPlus);
    dApp.currentDriver().addNewCar(carToAdd);
    dApp.currentDriver().forbidAddingCars(adminApp.getCurrentAdmin());
    cout <<"Now i've added new car to Artem Voronov and block fo him add new ones"<<endl;
    cout <<"Restart program to see new changes"<<endl;
}
void example4(){
    System systema;
    DriverGateway& dApp=systema.getDriverApp();
    PassengerGateway& pApp=systema.getPassengersApp();
    AdminGateway& adminApp=systema.getAdminsApp();
    cout <<"Now Artem will try to add new machine"<<endl;
    dApp.logIn(dApp.searchBySurname("Voronov"));
    adminApp.logIn(0);//login as Fedor
    Car carToAdd("mersedes",Economy);
    dApp.currentDriver().addNewCar(carToAdd);
    cout <<"He cannot, but admin can let him to add it"<<endl;
    cout <<"Let him try to change his accesss"<<endl;
    dApp.currentDriver().letAddingCars(dApp.currentDriver());
    cout <<"System printed warning message,now admin will let him to add new cars and validate others"<<endl;
    dApp.currentDriver().letAddingCars(adminApp.getCurrentAdmin());
    dApp.currentDriver().addNewCar(carToAdd);//add mersedes,that won't be accepted
    dApp.currentDriver().validateCar(adminApp.getCurrentAdmin(),0);//validate first car(ferrari)
    cout <<"That's all for key features of the program,that were added in version 1.1"<<endl;
    cout <<"As you cn see now admins can block some functions for user and check cars before riding"<<endl;
}
void defaultCase(){
    System systema;
    PassengerGateway& mobApp=systema.getPassengersApp();
    DriverGateway& drApp=systema.getDriverApp();
    AdminGateway& adminApp=systema.getAdminsApp();
    cout <<"All examples are ended, now you can just see, that data.txt is saving"<<endl;
    cout <<"If you want to restart examples-> change value in Example.txt to 0 and run the program"<<endl;
    cout <<"Let's just print all users"<<endl;
    for (Passenger curPass: mobApp.getPassengers()){
        cout <<curPass.getName()<<" "<<curPass.getSurname()<<endl;

    }
    for (Driver curDriver : drApp.getDrivers()){
        cout <<curDriver.getName()<<" "<<curDriver.getSurname()<<endl;
    }
    cout <<"Also there is an admin"<<endl;
    for (Admin curAdmin:adminApp.getAdmins()){
        cout <<curAdmin.getName()<<" "<<curAdmin.getSurname()<<endl;
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
        case 3:
            example3();
            break;
        case 4:
            example4();
            break;
        default:
            defaultCase();
            break;
    }
    fout <<caseof+1;
    fout.close();
    return 0;
}
