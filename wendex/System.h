#ifndef YANDEX_SYSTEM_H
#define YANDEX_SYSTEM_H
#include "Persons.h"
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
        NewOrder.setPayment(passengers[currentUser].getPayMethod());
        currentOrders.push_back(NewOrder);
    }
    Passenger& currentPassenger(){
        if (logged) return passengers[currentUser];
    }
    vector<Passenger> getPassengers(){
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
    vector<Driver> getDrivers(){
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
        order retOrder=currentOrders[i];
        currentOrders.erase(currentOrders.begin()+i);
        return retOrder;
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
class System{
private:
    PassengerGateway pApp;
    DriverGateway dApp;
public:
    System(){
        vector<Passenger> passengers;
        ifstream fin("../Data.txt");
        int n=0,rate,pay,orders; string name,surname;
        bool completed;
        vector<order> currOrders;
        int x,y,type; coordinate from,to;
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
        }
        fin >>n; bool isDriving;int carNumber;string model;
        vector<Driver> drivers;
        for (int i = 0;i<n;i++){
            fin >>name>>surname>>rate>>isDriving>>carNumber>>model>>type;
            switch (type) {
                case 10:{
                    Driver driver(name,surname,Car(model,Economy),rate,isDriving);
                    drivers.push_back(driver);
                    break;
                }
                case 20:{
                    Driver driver(name,surname,Car(model,Comfort),rate,isDriving);
                    drivers.push_back(driver);
                    break;
                }
                case 25:{
                    Driver driver(name,surname,Car(model,ComfortPlus),rate,isDriving);
                    drivers.push_back(driver);
                    break;
                }
                case 40:{
                    Driver driver(name,surname,Car(model,Business),rate,isDriving);
                    drivers.push_back(driver);
                    break;
                }
            }
            fin >>orders;
            for (int j=0;j<orders;j++){
                fin >>x>>y; from=coordinate(x,y);
                fin >>x>>y; to=coordinate(x,y);
                fin >>pay>>surname>>completed;
                order orderToAdd(from,to,drivers.back().getCar().getCarType());
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
        }
        PassengerGateway mobApp(passengers);
        DriverGateway drApp(drivers);
        mobApp.ordersFromData(currOrders);
        drApp.updateOrders(currOrders);
        pApp= mobApp;
        dApp=drApp;
    }
    PassengerGateway& getPassengersApp(){
        return pApp;
    }
    DriverGateway& getDriverApp(){
        return dApp;
    }
    ~System(){
        ofstream fout;
        fout.open("../Data.txt");
        vector<Passenger> passengers=pApp.getPassengers();
        vector<order> curOrders;
        fout <<passengers.size()<<endl;
        for(Passenger curPassenger : passengers){
            fout<<curPassenger.getName()<<" "<<curPassenger.getSurname()<<" "<<curPassenger.getRating()<<" ";
            fout<<curPassenger.getPayMethod()<<" ";
            curOrders=curPassenger.getOrderHistory();
            fout <<curOrders.size()<<endl;
            for (order curOrder: curOrders ){
                fout <<curOrder.getFromPlace().getXCoord()<<" "<<curOrder.getFromPlace().getYCoord()<<" ";
                fout <<curOrder.getToPlace().getXCoord()<<" "<<curOrder.getToPlace().getYCoord()<<" ";
                fout <<curOrder.getPayMethod()<<" "<<curOrder.getDriverSurname()<<" "<<curOrder.isCompleted();
                fout <<" "<<curOrder.getCarType()<<endl;
            }
        }
        vector<Driver> drivers= dApp.getDrivers();
        fout <<drivers.size()<<endl;
        for (Driver curDriver : drivers){
            Car curCar=curDriver.getCar();
            fout<<curDriver.getName()<<" "<<curDriver.getSurname()<<" "<<curDriver.getRating()<<" ";
            fout<<curDriver.isDriving()<<" "<<curCar.getCarNumber()<<" "<<curCar.getModel()<<" ";
            fout<<curCar.getCarType()<<" ";
            curOrders=curDriver.getOrderHistory();
            fout <<curOrders.size()<<endl;
            for (order curOrder: curOrders){
                fout <<curOrder.getFromPlace().getXCoord()<<" "<<curOrder.getFromPlace().getYCoord()<<" ";
                fout <<curOrder.getToPlace().getXCoord()<<" "<<curOrder.getToPlace().getYCoord()<<" ";
                fout <<curOrder.getPayMethod()<<" "<<curOrder.getPassengerSurname()<<" "<<curOrder.isCompleted()<<endl;
            }
        }
        fout.close();
    }
};
#endif //YANDEX_SYSTEM_H
