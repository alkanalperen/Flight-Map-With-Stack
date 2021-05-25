//
// Created by Alperen Alkan on 27.12.2020.
//

#include "FlightMap.h"
#include "Stack.h"
#include <iostream>
#include <sstream>

FlightMap::FlightMap(const string cityFile, const string flightFile) {
    city = 0;
    // Create a text string, which is used to output the text file
    string myCities;
    string myFlights;

    // Read from the text file
    ifstream readCity;
    ifstream readFlight;
    readCity.open( cityFile.c_str(), ios_base::in );
    readFlight.open( flightFile.c_str(), ios_base::in );

    headC = NULL;

    // Use a while loop together with the getline() function to read the file line by line
    while ( readCity.eof() == false) {
        getline (readCity, myCities, '\n');
        //create the city linked list
        cityNode *newPtr = new cityNode() ;
        newPtr->item = myCities;
        newPtr->nextD = NULL;
        newPtr->nextR = NULL;

        if(headC == NULL) {
            headC = newPtr;
        }
        else{
            cityNode *cur = headC;
            while(cur->nextR != NULL){
                cur = cur->nextR;
            }
            cur->nextR = newPtr;
        }
        //delete newPtr;
    }
    int cnt = 0;
    while(readFlight.eof() == false) {
        cnt++;
        getline (readFlight, myFlights,'\n');
        for (cityNode *cur = headC; cur != NULL; cur = cur->nextR) {
            if (myFlights.substr(0, 1) == cur->item) {
                //cout << cur->item <<endl;
                cityNode *newPtr = new cityNode();
                newPtr->nextD = NULL;
                newPtr->nextR = NULL;
                newPtr->item = myFlights.substr(2, 1);
                if(cnt < 10) {
                    int prize =0;
                    sscanf(myFlights.substr(6, 3).c_str(), "%d", &prize);
                    newPtr->prize =prize;
                    int fNu2 =0;
                    sscanf(myFlights.substr(4, 1).c_str(), "%d", &fNu2);
                    newPtr->fNu = fNu2;
                }
                else {
                    int prize =0;
                    sscanf(myFlights.substr(7, 3).c_str(), "%d", &prize);
                    newPtr->prize = prize;
                    int fNu2 =0;
                    sscanf(myFlights.substr(4, 2).c_str(), "%d", &fNu2);
                    newPtr->fNu = fNu2;
                    }
                newPtr->mark=false;
                cityNode *cur2;
                for (cur2 = cur; cur2->nextD != NULL; cur2 = cur2->nextD);
                cur2->nextD = newPtr;

            }
        }
    }

    readCity.close();
    readFlight.close();

}

 FlightMap::~FlightMap(){
cityNode* current = headC;
while( current != NULL ) {
    cityNode* current2 = current->nextD;
    while(current2 != NULL ){
        cityNode* next2 = current2->nextD;
        delete current2;
        current2 = next2;
    }
    cityNode* next = current->nextR;
    delete current;
    current = next;
}
 }

void FlightMap::displayAllCities() const {
    for (cityNode *cur = headC; cur->nextR != NULL; cur = cur->nextR)
        cout << cur->item << ", ";
}

void FlightMap::displayFlightMap() const {
    for (cityNode *cur = headC; cur != NULL; cur = cur->nextR) {
        cout <<cur->item << "->";
        for (cityNode *cur2 = cur->nextD; cur2!= NULL; cur2 = cur2->nextD)
            cout << cur2->item << " ";
        cout << endl;
    }
}
void FlightMap::displayAdjacentCities(const string cityName) const {
    for (cityNode *cur = headC; cur != NULL; cur = cur->nextR) {
        if(cur->item == cityName) {
            cout <<cur->item << "->";
            for (cityNode *cur2 = cur->nextD; cur2 != NULL; cur2 = cur2->nextD)
                cout << cur2->item << " ";
        }
    }
}

int FlightMap::getPrice(const string c1,const string c2) const {
    for (cityNode *cur = headC; cur != NULL; cur = cur->nextR) {
        if( cur->item == c1)
            for (cityNode *cur2 = cur->nextD; cur2 != NULL; cur2 = cur2->nextD)
                if (cur2->item == c2 ) {
                    return cur2->prize;
            }
    }
    return 0;
}

void FlightMap::findFlights(const string deptCity, const string destCity)const {

    string s;
    Stack aStack;
    //deptCity hasNoMarkedAdjacent
    // push origin onto aStack
    aStack.push(deptCity);

    // mark the origin as visited
    mark(deptCity);

    //clear marks
    clearM();
        while (!aStack.isEmpty() && destCity != aStack.getTop() ) {


            bool hasFlight = false;
            string nextCity;

            for (cityNode *cur = headC; cur != NULL; cur = cur->nextR) {
                if (cur->item.compare(aStack.getTop()) == 0) {
                    for (cityNode *cur2 = cur->nextD; cur2 != NULL; cur2 = cur2->nextD) {
                        if (!isMarked(cur2->item)) {
                            hasFlight = true;
                            nextCity = cur2->item;
                            break;
                        }
                    }
                }

            }
            if (!hasFlight)
                aStack.pop();    // backtrack
            else {
                //select an unvisited destination city C for a
                //flight from the city on the top of the stack
                aStack.push(nextCity);
                mark(nextCity);
            }

        }
        string s1 = "";
        int totalC = 0;
        while (!aStack.isEmpty()) {
            string s2;
            string s;
            aStack.pop(s);
            if (!aStack.isEmpty()) {
                stringstream ss;
                ss << getFNu(aStack.getTop(), s);
                string nu;
                ss>>nu;
                stringstream ss1;
                ss1 << getPrice(aStack.getTop(), s);
                string pr;
                ss1>>pr;
                totalC += getPrice(aStack.getTop(), s);
                s2 = "Flight #" + nu + " " + aStack.getTop() + " to " + s + " " +
                     pr + '\n';
                s1 = s2 + s1;
            }
        }
        cout << "Request is to fly from " << deptCity<<" to "<< destCity <<endl;
        cout << s1;
        cout << "Total cost is " << totalC<<endl ;
        // 1 way founded

    }



FlightMap::cityNode* FlightMap::findCity(const string city)const {
    for (cityNode *cur = headC; cur != NULL; cur = cur->nextR) {
            if (cur->item.compare(city )==0) {
                return cur;
            }
    }
    return NULL;
}


void FlightMap::mark( string city)const {
    findCity(city)->mark = true;
}

bool FlightMap::isMarked(string city)const  {
    return findCity(city)->mark;
}
int FlightMap::getFNu(const string cityName, const string cityName2) const {
    for (cityNode *cur = headC; cur != NULL; cur = cur->nextR) {
        if( cur->item == cityName)
            for (cityNode *cur2 = cur->nextD; cur2 != NULL; cur2 = cur2->nextD)
                if (cur2->item == cityName2 ) {
                    return cur2->fNu;
                }
    }
    return 0;
}
bool FlightMap::hasUnMarkedAdjacent(const string cityName) const {
    for (cityNode *cur = headC; cur != NULL; cur = cur->nextR) {
        if( cur->item == cityName)
            for (cityNode *cur2 = cur->nextD; cur2 != NULL; cur2 = cur2->nextD)
                if(!isMarked(cur2->item))
                    return true;
    }
    return false;
}
void FlightMap::runFlightRequests(const string requestF )const{
    string requests;
    ifstream readRequest;
    readRequest.open( requestF.c_str(), ios_base::in );

     while ( readRequest.eof() == false) {
        getline (readRequest, requests, '\n');
        string c1 = requests.substr(0, 1);
        string c2 =requests.substr(2, 1);
        findFlights(c1,c2);

     }
}
void FlightMap::clearM()const{
    for (cityNode *cur = headC; cur != NULL; cur = cur->nextR) {
            for (cityNode *cur2 = cur->nextD; cur2 != NULL; cur2 = cur2->nextD)
                findCity(cur2->item)->mark = false;
    }
}
void FlightMap::findLeastCostFlight(const string c1, const string c2)const{
cout << " This method not implemented";
}
