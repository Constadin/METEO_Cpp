// meteo

#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>
#include <ctime>
#include <cstdlib>

using namespace std;

const string DAYS[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
const string MONTHS[] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

void write_data() {
    float temperature, humidity, wind_speed;
    ofstream sensor_file;
    
    sensor_file.open("sensor_data.txt", ios::app);

    temperature = (rand() % 100) / 10.0f;
    humidity = (rand() % 100) / 10.0f;
    wind_speed = (rand() % 100) / 10.0f;

    time_t now = time(0);
    struct tm *tm_struct = localtime(&now);
    int year = tm_struct->tm_year + 1900;
    string day = DAYS[tm_struct->tm_wday];
    string month = MONTHS[tm_struct->tm_mon];
    int day_num = tm_struct->tm_mday;
    int hour = tm_struct->tm_hour;
    int minute = tm_struct->tm_min;
    int second = tm_struct->tm_sec;

    sensor_file << year << " " << month << " " << day_num << " " << day << " " << hour << " " << minute << " " << second << " ";
    sensor_file << temperature << " " << humidity << " " << wind_speed << "\n";
    sensor_file.close();
}

void display_data() {
    float temperature, humidity, wind_speed;
    int year, day_num;
    string day, month;
    int hour, minute, second;
    ifstream sensor_file;
    
    sensor_file.open("sensor_data.txt");

    if (sensor_file.is_open()) {
        while (sensor_file >> year >> month >> day_num >> day >> hour >> minute >> second >> temperature >> humidity >> wind_speed) {
            cout << "Year: " << year << endl;
            cout << "Month: " << month << endl;
            cout << "Day: " << day_num << " " << day << endl;
            cout << "Time: " << hour << ":" << minute << ":" << second << endl;
            cout << "Temperature: " << temperature << endl;
            cout << "Humidity: " << humidity << endl;
            cout << "Wind speed: " << wind_speed << endl;
            cout << endl;
        }
    } else {
        cout << "Unable to open sensor data file." << endl;
    }
}

int main() {
    srand(time(0));

    while (true) {
        write_data();
        display_data();
        this_thread::sleep_for(chrono::seconds(3));
    }

    return 0;
}

