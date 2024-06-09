#include <iostream>
#include <string>
#include <limits>
#include<cstring>
#include <iomanip>
#include<cstdlib>
bool found = false;
using namespace std;

class Vehicle {
protected:
    string make;
    string model;
    double year;
    float price;

public:
    Vehicle(string make, string model, double year, float price)
        : make(make), model(model), year(year), price(price) {}

    void setMake(string m) { make = m; }
    void setModel(string M) { model = M; }
    void setYear(double y) { year = y; }
    void setPrice(float p) { price = p; }

    string getMake() const { return make; }
    string getModel() const { return model; }
    double getYear() const { return year; }
    float getPrice() const { return price; }

    virtual double calculateTax() const = 0;
    virtual void displayDetails() const 
    {
        cout << "Make: " << make << endl;
        cout << "Model: " << model << endl;
        cout << "Year: " << year << endl;
        cout << "Price: $" << fixed << setprecision(2) << price << endl;
    }

    virtual ~Vehicle() = default;
};

class car : public Vehicle {
protected:
    int numDoors;

public:
    car(string make, string model, double year, float price, int numDoors)
        : Vehicle(make, model, year, price), numDoors(numDoors) {}

    void setNumDoors(int num) {
        numDoors = num;
    }

    int getNumDoors() const {
        return numDoors;
    }

    double calculateTax() const override {
        return price * 0.1;
    }

    void displayDetails() const override {
        Vehicle::displayDetails();
        cout << "Number of Doors: " << numDoors << endl;
        cout << "Tax: $" << fixed << setprecision(2) << calculateTax() << endl;
    }
};

class truck : public Vehicle {
private:
    float payload;
    int towingCapacity;

public:
    truck(string make, string model, double year, float price, float payload, int towingCapacity)
        : Vehicle(make, model, year, price), payload(payload), towingCapacity(towingCapacity) {}

    void setPayload(float pay) {
        payload = pay;
    }

    void setTowingCapacity(int tow) {
        towingCapacity = tow;
    }

    float getPayload() const {
        return payload;
    }

    int getTowingCapacity() const {
        return towingCapacity;
    }

    double calculateTax() const override {
        return price * 0.12;
    }

    void displayDetails() const override {
        Vehicle::displayDetails();
        cout << "Payload: " << payload << " lbs" << endl;
        cout << "Towing Capacity: " << towingCapacity << " lbs" << endl;
        cout << "Tax: $" << fixed << setprecision(2) << calculateTax() << endl;
    }
};

void addVehicle(Vehicle* showRoom[], int& numVehicles) {
    if (numVehicles >= 100) {
        cout << "Vehicle showroom is full. Cannot add more vehicles." << endl;
        return;
    }

    string type, make, model;
    double year;
    float price;
    int numDoors = 0;
    int towingCapacity;
    float payload;

    cout << "Enter vehicle type ('car'/'truck'): ";
    cin >> type;

    cout << "Enter vehicle make: ";
    cin >> make;
    cout << "Enter vehicle model: ";
    cin >> model;
    cout << "Enter vehicle year: ";
    cin >> year;
    cout << "Enter vehicle price: ";
    cin >> price;

    if (type == "car") {
        cout << "Enter number of doors: ";
        cin >> numDoors;
        showRoom[numVehicles] = new car(make, model, year, price, numDoors);
        cout << "'Car' added to fleet." << endl;
    } else if (type == "truck") {
        cout << "Enter payload in pounds: ";
        cin >> payload;
        cout << "Enter towing capacity in pounds: ";
        cin >> towingCapacity;
        showRoom[numVehicles] = new truck(make, model, year, price, payload, towingCapacity);
        cout << "'Truck' added to fleet." << endl;
    } else {
        cout << "Invalid vehicle type." << endl;
        return;
    }

    numVehicles++;
}

void removeVehicle(Vehicle* showRoom[], int& numVehicles) {
    system("clear");
    if (numVehicles == 0) {
        cout << "No vehicles to remove." << endl;
        return;
    }
    string make, model;
    cout << "Enter vehicle make: ";
    cin >> make;
    cout << "Enter vehicle model: ";
    cin >> model;
    for (int i = 0; i < numVehicles; i++) {
        if (showRoom[i]->getMake() == make && showRoom[i]->getModel() == model) {
            delete showRoom[i];
            for (int j = i; j < numVehicles - 1; j++) {
                showRoom[j] = showRoom[j + 1];
            }
            numVehicles--;
            cout << "Vehicle removed from fleet." << endl;
            return;
        }
    }
    cout << "Vehicle not found." << endl;
}

void searchVehicle(Vehicle* showRoom[], int& numVehicles) {
    system("clear");

    string make, model;
   
    cout << "Enter vehicle make: ";
    cin >> make;
    cout << "Enter vehicle model: ";
    cin >> model;
    for (int i = 0; i < numVehicles; i++) {
        if (showRoom[i]->getMake() == make && showRoom[i]->getModel() == model) {
            found = true;
            cout << "Vehicle Information:" << endl;
            showRoom[i]->displayDetails();
            break;
        }
    }
    if (!found) {
        cout << "Vehicle not found." << endl;
    }
}
void summaryVehicle(Vehicle* showRoom[], int& numVehicles)
{
   system("clear");
   float sum =0;
   cout<<"The total number of vehicles in the fleet is : "<<numVehicles<<endl;
   for(int i=0;i<numVehicles; i++)
   {
    sum = sum+showRoom[i]->getPrice();
   }
   cout<<"The sum of price of all the vehicles in the fleet  is :  "<<sum<<endl;
   cout<<"The average price of the vehicles in the fleet is : ";
   cout<<(sum/numVehicles)<<endl;
  
}

void filterVehicle(Vehicle* showRoom[], int& numVehicles)
{
    string make, model;
     system("clear");
    cout << "Enter vehicle make: ";
    cin >> make;
    cout << "Enter vehicle model: ";
    cin >> model;
     for(int i=0;i<numVehicles-1;i++)
     {
        for(int j = i+1; j< numVehicles;j++)
     {
        if(strcmp(showRoom[i]->getMake().c_str(),showRoom[j]->getMake().c_str()) ==0)
        {
             found = true;
            cout << setw(30)<<"Vehicle Information:" << endl<<endl;
            showRoom[i]->displayDetails();
            break;
        }
     }
    
     }
     if (!found) {
        cout << "Vehicle not found." << endl;
    }
    
}

int main() {
    Vehicle* showRoom[100];
    int numVehicles = 0;
    int choice;
    bool running = true;
    cout << setw(30)<<"Welcome to the Vehicle Management System! " << endl;
    while (running) {
        cout << "Menu" << endl;
        cout << "1. Add Vehicle" << endl;
        cout << "2. Remove Vehicle" << endl;
        cout << "3. Search for Vehicle" << endl;
        cout << "4. Summary of the fleet"<<endl;
        cout << "5. Filter the fleet "<<endl;
        cout << "6. Exit" << endl;

        cout << "Enter your choice: ";
        cin >> choice;
        system("clear");

        switch (choice) {
            case 1:
                addVehicle(showRoom, numVehicles);              
                break;

            case 2:
                removeVehicle(showRoom, numVehicles);                 
                break;

            case 3:
                searchVehicle(showRoom, numVehicles);                
                break;
            
            case 4:
                 summaryVehicle(showRoom, numVehicles);
                 break;
            
            case 5:
                 filterVehicle(showRoom, numVehicles);
                 break;

            case 6:
                cout << "Exiting Program " << endl;
                running = false;
                break;

            default:
                cout << "\nChoose a valid option." << endl;
        }
    }

    for (int i = 0; i < numVehicles; i++) {
        delete showRoom[i];
    }
    return 0;
}