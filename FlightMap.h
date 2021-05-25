//
// Created by Alperen Alkan on 27.12.2020.
#include <iostream>
#include <fstream>
#include "Stack.h"
using namespace std;

#ifndef STACK_FLIGHTMAP_H
#define STACK_FLIGHTMAP_H


class FlightMap {
public:
    FlightMap( const string cityFile, const string flightFile );
    ~FlightMap();
    void displayAllCities() const;
    void displayAdjacentCities( const string cityName ) const;
    void displayFlightMap() const;
    int getPrice( const string cityName,const string cityName2) const;
    int getFNu(const string cityName,const string cityName2)const;
    void findFlights( const string deptCity, const string destCity)const;
    void findLeastCostFlight( const string deptCity, const string destCity )
    const;
    void runFlightRequests( const string requestFile ) const;
    bool hasUnMarkedAdjacent(const string cityName )const;
private:
    struct cityNode{
        string item;
        cityNode *nextR;
        cityNode *nextD;
        int prize;
        bool mark;
        int fNu;
    };
    cityNode *headC;
    cityNode *findCity(const string city)const;
    void mark(string city)const;
    void clearM()const;
    bool isMarked(string city)const;
    int city;
    void addElement();
};

#endif //STACK_FLIGHTMAP_H
