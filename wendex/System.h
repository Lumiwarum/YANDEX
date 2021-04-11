#ifndef WENDEX_SYSTEM_H
#define WENDEX_SYSTEM_H
#include "Persons.h"
using namespace std;

class PassengerGateway{
private:
    vector<Passenger> passengers;
    int currentUser;
    vector<order> currentOrders;
    bool logged;
public:
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
        return (int)(From.Distance(To)*type/100);
    }
    int seeTime(coordinate From,coordinate To,carType type){
        return (int)(From.Distance(To)/type);
    }
    void orderRide(coordinate From,coordinate To,carType type){
        order NewOrder(From,To,type);
        NewOrder.setPayment(passengers[currentUser].getPayMethod());
        currentOrders.push_back(NewOrder);
    }
    Passenger& currentPassenger(){
       if (logged) return passengers[currentUser];
    }
    vector<Passenger> getPassengers(){
        return passengers;
    }
};
class DriverGateway{

};
#endif //WENDEX_SYSTEM_H
