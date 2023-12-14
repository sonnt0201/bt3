#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>

using namespace std;

double generateRandomValue()
{
    
    return ((rand()) % 3999990 + 10) / 100.0;
}

// function to create csv file data
void generate_sensor_data(int num_sensors, int sampling_time, int simulation_interval)
{
    time_t current_time = time(nullptr) - simulation_interval * 3600;
    ofstream outfile("lux_sensor.csv");

    if (!outfile)
    {
        cerr << "Error" << endl;
        return;
    }

    outfile << " id,time,value" << endl;
    int sensor_id = 1;
    for (int i = 1; i <= num_sensors; i++)
    {
        while (current_time < time(nullptr))
        {
            tm *tm_time = localtime(&current_time);
            char timestamp[20];
            strftime(timestamp, sizeof(timestamp), "%Y:%m:%d %H:%M:%S", tm_time);

            outfile << sensor_id << "," << timestamp << "," << generateRandomValue() << endl;
            sensor_id = (sensor_id % num_sensors) + 1;
            current_time += sampling_time;
        }
    }

    outfile.close();
}



   
   

int main(int argc, char *argv[])
{
    int num_sensors = 1;
    int sampling_time = 60;
    int simulation_interval = 24;

   
        for (int i = 0; i < argc; i++)
        {
            string arg = argv[i];
            if (arg == "-n")
            {
                num_sensors = stoi(argv[i + 1]);
            }
            else if (arg == "-st")
            {
                sampling_time = stoi(argv[i + 1]);
            }
            else if (arg == "-si")
            {
                simulation_interval = stoi(argv[i + 1]);
            }
        
    }
  
  
    srand(time(0));
    generate_sensor_data(num_sensors, sampling_time, simulation_interval);
    return 0;
}