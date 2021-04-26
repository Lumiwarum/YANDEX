#ifndef YANDEX2_SYSTEM_H
#define YANDEX2_SYSTEM_H
#include "persons.h"
#include <fstream>
using namespace std;

class PassengerGateway{
private:
    vector<Passenger> passengers;
    int currentUser;
    vector<order> currentOrders;
    bool logged;
public:
    PassengerGateway(){}
    PassengerGateway(vector<Passenger> passengers){
        this->passengers=passengers;


    }
    bool isLogged(){
        return logged;
    }
    void addPassenger(Passenger pers){
        passengers.push_back(pers);
    }
    int searchForPerson(Passenger stranger){
        for (int i = 0;i<passengers.size();i++){
            if ((stranger.getName()==passengers[i].getName())&&(stranger.getSurname()==passengers[i].getSurname())){
                return i;
            }
        }
        return -1;
    }
    void logIn(int i){
        if ((i>-1)&&(i<passengers.size())){
            currentUser=i;
            logged= true;
        }
    }
    void logOut(){
        logged=false;
    }
    int seePrice(coordinate From,coordinate To,carType type){
        return (int)(From.Distance(To)*100/type);
    }
    int seeTime(coordinate From,coordinate To,carType type){
        return (int)(From.Distance(To)/type);
    }
    void orderRide(order NewOrder){
        try {
            if (!logged){throw "exception";}
            if (!passengers[currentUser].canOrder()){throw -1;}
        NewOrder.setPayment(passengers[currentUser].getPayMethod());
        currentOrders.push_back(NewOrder);}
        catch (string name){
            cout <<"SYSTEM: No logged user"<<endl;
        }
        catch (int i){
            cout <<"SYSTEM: Current user "<<passengers[currentUser].getName()<<" "<<passengers[currentUser].getSurname()<<" ";
            cout <<"cannot order a ride"<<endl;
        }
    }
    Passenger& currentPassenger(){
        if (logged) return passengers[currentUser];
    }
    vector<Passenger>& getPassengers(){
        return passengers;
    }
    void orderAccepted(order orderToRemove){
        for (int i=0;i<currentOrders.size();i++){
            if (currentOrders[i].getPassengerSurname()==orderToRemove.getPassengerSurname()){
                currentOrders.erase(currentOrders.begin()+i);
            }
        }
    }
    void ordersFromData(vector<order> addOrders){
        currentOrders=addOrders;
    }
    int searchBySurname(string surname){
        for (int i=0;i<passengers.size();i++){
            if(surname==passengers[i].getSurname()){
                return i;
            }
        }
        return -1;
    }
    vector<order> getOrders(){
        return currentOrders;
    }
};
class DriverGateway{
private:
    vector<Driver> drivers;
    int currentUser;
    vector<order> currentOrders;
    bool logged;
public:
    DriverGateway(){}
    DriverGateway(vector<Driver> drivers){
        this->drivers=drivers;
        logged = false;
    }
    vector<Driver>& getDrivers(){
        return drivers;
    }
    Driver& currentDriver(){
        if (logged) return drivers[currentUser];
    }
    void addNewOrder(order orderToAdd){
        currentOrders.push_back(orderToAdd);
    }
    vector<order> seeOrders(){
        return currentOrders;
    }
    order acceptOrder(int i){
        try{
            if (!logged) throw "exception";
            if (!currentDriver().canAccept()){
                throw -1;
            }
        order retOrder=currentOrders[i];
        currentOrders.erase(currentOrders.begin()+i);
        currentDriver().addOrderToHistory(retOrder);
        return retOrder;}
        catch (string ex){
            cout <<"SYSTEM: no driver is logged"<<endl;
        }
        catch (int i){
            cout <<"SYSTEM: current driver cannot accept an order"<<endl;
        }
    }
    void addDriver(Driver newDriver){
        drivers.push_back(newDriver);
    }
    void updateOrders(vector<order> update){
        currentOrders=update;
    }
    int searchForPerson(Driver stranger){
        for (int i=0;i<drivers.size();i++){
            if ((stranger.getName()==drivers[i].getName())&&(stranger.getSurname()==drivers[i].getSurname())){
                return i;
            }
        }
        return -1;
    }
    int searchBySurname(string surname){
        for (int i=0;i<drivers.size();i++){
            if (surname==drivers[i].getSurname()){
                return i;
            }
        }
        return -1;
    }
    void logIn(int i){
        if ((i>-1)&&(i<drivers.size())){
            currentUser=i;
            logged= true;
        }
    }
    void logOut(){
        logged=false;
    }

};
class AdminGateway{
private:
    DriverGateway* driverApp;
    PassengerGateway* passengerApp;
    vector<Admin> admins;
    int currentAdmin;
    bool logged;
public:
    AdminGateway()=default;
    void addInformation(PassengerGateway* ptr1, DriverGateway* ptr2, vector<Admin> admins) {
        driverApp = ptr2;
        passengerApp = ptr1;
        this->admins = admins;
    }
    void logIn(int i){
        if ((i>-1)&&(i<admins.size())){
            currentAdmin=i;
            logged= true;
        }
    }
    vector<Passenger>& getPassengers(){
        return passengerApp->getPassengers();
    }
    vector<Driver>& getDrivers(){
        return driverApp->getDrivers();
    }
    void logOut(){
        logged=false;
    }
    vector<Admin> getAdmins(){
        return admins;
    }
    void addAdmin(Admin admin){
        admins.push_back(admin);
    }
    Admin& getCurrentAdmin(){
        if (logged){return admins[currentAdmin];}
    }
};
class System{
private:
    PassengerGateway pApp;
    DriverGateway dApp;
    AdminGateway adminApp;
public:
    System(){
        Admin admin("Noname","Noname");
        vector<Passenger> passengers;
        ifstream fin("../Data.txt");
        int n=0,rate,pay,orders; string name,surname;
        bool completed,can1,can2;
        vector<order> currOrders;
        int x,y,type,phones;
        coordinate from,to;
        Phone phoneToAdd;
        if (fin.peek()!='\0'){fin >>n;}
        for (int i = 0;i<n;i++){
            fin >>name>>surname>>rate>>pay>>can1>>can2;
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
            fin >>orders;
            for (int j=0;j<orders;j++){
                fin >>x>>y; from=coordinate(x,y);
                fin >>x>>y; to=coordinate(x,y);
                fin >>pay>>surname>>completed>>type;
                order orderToAdd;
                switch (type) {
                    case 10:{
                        orderToAdd=order(from,to,Economy);
                        break;
                    }
                    case 20:{
                        orderToAdd=order(from,to,Comfort);
                        break;
                    }
                    case 25:{
                        orderToAdd=order(from,to,ComfortPlus);
                        break;
                    }
                    case 40:{
                        orderToAdd=order(from,to,Business);
                        break;
                    }
                }
                orderToAdd.setDriver(surname);
                orderToAdd.setPassenger(passengers.back().getSurname());
                switch (pay+1){
                    case 1:
                        orderToAdd.setPayment(cash);
                        break;
                    case 2:
                        orderToAdd.setPayment(creditCard);
                        break;
                    case 3:
                        orderToAdd.setPayment(cheque);
                        break;
                }
                if (completed){orderToAdd.completeOrder();} else {
                    currOrders.push_back(orderToAdd);
                }
                passengers.back().addOrderToHistory(orderToAdd);
            }
            fin >>phones;
            for (int j=0;j<phones;j++){
                fin >>name>>completed;
                phoneToAdd=Phone(name);
                if (completed){phoneToAdd.turnOn();}
                passengers.back().addPhone(phoneToAdd);
            }

            if(!can1){passengers.back().forbidOrderingRide(admin);}
            if(!can2){passengers.back().forbidChangingPayments(admin);}
        }

        fin >>n; bool isDriving;int carNumber,carsQuantity;string model;
        Car carToAdd;
        vector<Driver> drivers;
        for (int i = 0;i<n;i++){
            fin >>name>>surname>>rate>>isDriving>>can1>>can2;
            drivers.push_back(Driver(name,surname,rate,isDriving));
            fin >>carsQuantity;
            for (int j=0;j<carsQuantity;j++) {
                fin >>model>>type;
                switch (type) {
                    case 10: {
                        carToAdd=Car(model,Economy);
                        drivers.back().addNewCar(carToAdd);
                        break;
                    }
                    case 20: {
                        carToAdd=Car(model,Comfort);
                        drivers.back().addNewCar(carToAdd);
                        break;
                    }
                    case 25: {
                        carToAdd=Car(model,ComfortPlus);
                        drivers.back().addNewCar(carToAdd);
                        break;
                    }
                    case 40: {
                        carToAdd=Car(model,Business);
                        drivers.back().addNewCar(carToAdd);
                        break;
                    }
                }
            }
            fin >>carsQuantity;
            int numberOfCars=drivers.back().getNonValidateCars().size();
            for (int j=0;j<carsQuantity;j++) {
                fin >>model>>type;
                switch (type) {
                    case 10: {
                        drivers.back().addNewCar(Car(model,Economy));
                        drivers.back().validateCar(admin,numberOfCars);
                        break;
                    }
                    case 20: {
                        drivers.back().addNewCar(Car(model,Comfort));
                        drivers.back().validateCar(admin,numberOfCars);
                        break;
                    }
                    case 25: {
                        drivers.back().addNewCar(Car(model,ComfortPlus));
                        drivers.back().validateCar(admin,numberOfCars);
                        break;
                    }
                    case 40: {
                        drivers.back().addNewCar(Car(model,Business));
                        drivers.back().validateCar(admin,numberOfCars);
                        break;
                    }
                }
            }
            fin >>orders;
            for (int j=0;j<orders;j++){
                fin >>x>>y; from=coordinate(x,y);
                fin >>x>>y; to=coordinate(x,y);
                fin >>pay>>surname>>completed;
                order orderToAdd(from,to,drivers.back().getCar(0).getCarType());
                orderToAdd.setDriver(drivers.back().getSurname());
                orderToAdd.setPassenger(surname);
                switch (pay+1){
                    case 1:
                        orderToAdd.setPayment(cash);
                        break;
                    case 2:
                        orderToAdd.setPayment(creditCard);
                        break;
                    case 3:
                        orderToAdd.setPayment(cheque);
                        break;
                }
                if (completed){orderToAdd.completeOrder();}
                drivers.back().addOrderToHistory(orderToAdd);
            }
            if(!can1){drivers.back().forbidAcceptingOrders(admin);}
            if(!can2){drivers.back().forbidAddingCars(admin);}
        }
        //Admin data getting
        fin >>n;
        vector<Admin> admins;
        for (int i=0;i<n;i++){
            fin >>name>>surname;
            admins.push_back(Admin(name,surname));
        }

        PassengerGateway mobApp(passengers);
        DriverGateway drApp(drivers);
        mobApp.ordersFromData(currOrders);
        drApp.updateOrders(currOrders);
        pApp= mobApp;
        dApp=drApp;
        adminApp.addInformation(&pApp,&dApp,admins);
        fin.close();
    }
    PassengerGateway& getPassengersApp(){
        return pApp;
    }
    DriverGateway& getDriverApp(){
        return dApp;
    }
    AdminGateway& getAdminsApp(){
        return adminApp;
    }
    ~System(){
        ofstream fout;
        fout.open("../Data.txt");
        vector<Passenger> passengers=pApp.getPassengers();
        vector<order> curOrders;
        vector<Phone> curPhones;
        fout <<passengers.size()<<endl;
        for(Passenger curPassenger : passengers){
            fout<<curPassenger.getName()<<" "<<curPassenger.getSurname()<<" "<<curPassenger.getRating()<<" ";
            fout<<curPassenger.getPayMethod()<<" "<<curPassenger.canOrder()<<" "<<curPassenger.canChange()<<endl;
            curOrders=curPassenger.getOrderHistory();
            fout <<curOrders.size()<<endl;
            for (order curOrder: curOrders ){
                fout <<curOrder.getFromPlace().getXCoord()<<" "<<curOrder.getFromPlace().getYCoord()<<" ";
                fout <<curOrder.getToPlace().getXCoord()<<" "<<curOrder.getToPlace().getYCoord()<<" ";
                fout <<curOrder.getPayMethod()<<" "<<curOrder.getDriverSurname()<<" "<<curOrder.isCompleted();
                fout <<" "<<curOrder.getCarType()<<endl;
            }
            curPhones=curPassenger.getPhones();
            fout <<curPhones.size()<<endl;
            for (Phone curPhone: curPhones){
                fout <<curPhone.getModel()<<" "<<curPhone.active()<<endl;
            }
        }

        vector<Driver> drivers= dApp.getDrivers();
        fout <<drivers.size()<<endl;
        for (Driver curDriver : drivers){

            vector<Car> curCars=curDriver.getNonValidateCars();
            fout<<curDriver.getName()<<" "<<curDriver.getSurname()<<" "<<curDriver.getRating()<<" ";
            fout<<curDriver.isDriving()<<" "<<curDriver.canAccept()<<" "<<curDriver.canAdd()<<endl;

            fout <<curCars.size()<<endl;
            for (Car curCar: curCars){
               fout  <<curCar.getModel()<<" ";
                fout <<curCar.getCarType()<<endl;
            }
            curCars=curDriver.getCars();
            fout <<curCars.size()<<endl;
            for (Car curCar: curCars){
                fout  <<curCar.getModel()<<" ";
                fout <<curCar.getCarType()<<endl;
            }
            curOrders=curDriver.getOrderHistory();
            fout <<curOrders.size()<<endl;
            for (order curOrder: curOrders){
                fout <<curOrder.getFromPlace().getXCoord()<<" "<<curOrder.getFromPlace().getYCoord()<<" ";
                fout <<curOrder.getToPlace().getXCoord()<<" "<<curOrder.getToPlace().getYCoord()<<" ";
                fout <<curOrder.getPayMethod()<<" "<<curOrder.getPassengerSurname()<<" "<<curOrder.isCompleted()<<endl;
            }
        }
        vector<Admin> admins=adminApp.getAdmins();
        fout <<admins.size()<<endl;
        for (int i=0;i<admins.size();i++){
            fout <<admins[i].getName()<<" "<<admins[i].getSurname()<<endl;
        }
        fout.close();
    }
};
#endif //YANDEX2_SYSTEM_H
