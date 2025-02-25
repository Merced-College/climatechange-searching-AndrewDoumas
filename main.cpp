// main.cpp
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <array>
#include <string>
#include "StateClimate.h"


//function for binary search to find the index of the state
int binary_search(std::vector<StateClimate> &vec, int target_fips){

    int low = 0;
    int high = vec.size() - 1;
    int mid;

    //binary search algorithim
    while (low <= high){
        mid = (low + high) / 2;
        if (vec[mid].getFips() == target_fips){
            return mid;
        }
        else if(vec[mid].getFips() > target_fips){
            high = mid - 1;
        }
        else{
            low = mid + 1;
        }
    }
    
    

    return -1;
}

//function for linear search to find the first index of the state
int search_left(std::vector<StateClimate> &vec, int initial_fips){
    int left_fip = initial_fips;
    bool search_left = true;
    
    
    while(search_left){
        
        //std::cout<< "left_fip: " << left_fip << std::endl;

        //prevents out of bounds error
        if(left_fip == 0){
            search_left = false;
            return left_fip;
        }

        //checks if the left fips is the same as the initial fips
        else if( vec[left_fip].getFips() != vec[left_fip-1].getFips() ){
            search_left = false;
            return left_fip;
        }
        //decrement left fips
        else{
            left_fip--;
        }
    }

    return left_fip;
    }
    
    


//function for linear search to find the last index of the state
int search_right(std::vector<StateClimate> &vec, int initial_fips){
    
    int right_fip = initial_fips;
    bool search_right = true;

    
    while(search_right){
        if( (vec[right_fip].getFips() != vec[right_fip+1].getFips()) 
            && (right_fip <= vec.size()) ){
            return right_fip;
        }
        //increments right fips
        else{
            initial_fips++;
        }
    }

    return right_fip;
    
}

//function for linear search to find if the state name is in the array
int validate_name(std::string name, std::array<std::string,50>state_names){

    for(int i = 0; i < state_names.size(); i++){
        if(name == state_names[i]){
            return i;
        }
    }
    
    return -1;
}

int main() {
    std::vector<StateClimate> climateData;
    std::ifstream file("climdiv_state_year.csv");
    
    if (!file) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }

    std::string line;
    std::getline(file, line); // Skip header line
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        int fips, year;
        double temp, tempc;
        char comma;

        ss >> fips >> comma >> year >> comma >> temp >> comma >> tempc;
        climateData.emplace_back(fips, year, temp, tempc);
    }

    file.close();


    //parrallel arrays for state names and fips
    std::array<int, 50> fip_code = {1, 2, 4, 5, 6, 8, 9, 10, 12, 13, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 44, 45, 46, 47, 48, 49, 50, 51, 53, 54, 55, 56};
    std::array<std::string, 50> state_names = {"ALABAMA", "ALASKA", "ARIZONA", "ARKANSAS", "CALIFORNIA", "COLORADO", "CONNECTICUT", "DELAWARE", "FLORIDA", "GEORGIA", "HAWAII", "IDAHO", "ILLINOIS", "INDIANA", "IOWA", "KANSAS", "KENTUCKY", "LOUISIANA", "MAINE", "MARYLAND", "MASSACHUSETTS", "MICHIGAN", "MINNESOTA", "MISSISSIPPI", "MISSOURI", "MONTANA", "NEBRASKA", "NEVADA", "NEW HAMPSHIRE", "NEW JERSEY", "NEW MEXICO", "NEW YORK", "NORTH CAROLINA", "NORTH DAKOTA", "OHIO", "OKLAHOMA", "OREGON", "PENNSYLVANIA", "RHODE ISLAND", "SOUTH CAROLINA", "SOUTH DAKOTA", "TENNESSEE", "TEXAS", "UTAH", "VERMONT", "VIRGINIA", "WASHINGTON", "WEST VIRGINIA", "WISCONSIN", "WYOMING"};

    /*
    std::cout<<"fip code size: " <<fip_code.size()<<std::endl;
    std::cout<<"state names size: " <<state_names.size()<<std::endl;

    for(int i = 0; i < fip_code.size(); i++){
        std::cout<<fip_code[i]<<", "<<state_names[i]<<std::endl;
    }
    */
    
    /*
    int j = 0;
     // Display data
     for (const auto &entry : climateData) {
         std::cout<< j <<" "; 
         entry.display();
         j++;
     }
     *///for testing

    std::string target_name = "";
    bool choose_state = true;
    int index;

    while(choose_state){
        std::cout<<"Enter a state name: ";
        std::cin>>target_name;
        
        // Convert target_name to uppercase
        for (char &c : target_name) {
            c = toupper(c);
        }
        std::cout<<target_name<<std::endl;
        // Check if target_name is in state_names
        index = validate_name(target_name, state_names);

        if(index >= 0){
            choose_state = false;
        }
        else{
            std::cout<<"Invalid state name. Please try again."<<std::endl;
        }
        
    }
    
    
    
    int target_fips = fip_code[index];
    
    //std::cout << "Enter a FIPS code to search for: ";
    //std::cin>>target_fips;

    int initial_loaction = binary_search(climateData, target_fips);
    int left_fips, right_fips;

    //check if the target fips is in the vector
    if (initial_loaction != -1){
        std::cout << "Found at index: " << initial_loaction << std::endl;

        //searches through to find the first fip of the target number
        left_fips = search_left(climateData, initial_loaction);
        std::cout << "left_fips: " << left_fips << "\n";
        //std::cout<<left_fips<<std::endl;
        //std::cout<< climateData[left_fips].getFips()<<", "<< climateData[left_fips].getYear()<<", "<< climateData[left_fips].getTemp()<<", "<< climateData[left_fips].getTempC()<<std::endl;


        
        //searches through to find the last fip of the target number
        right_fips = search_right(climateData, initial_loaction);
        std::cout<<right_fips<<std::endl;
        //std::cout<< climateData[right_fips].getFips()<<", "<< climateData[right_fips].getYear()<<", "<< climateData[right_fips].getTemp()<<", "<< climateData[right_fips].getTempC()<<std::endl;

        //displays the data for the target fips
        for(int i = left_fips; i <= right_fips; i++){

            
            std::cout << target_name <<": "
                      << "FIP: " << climateData[i].getFips()
                      << ", Year: " << climateData[i].getYear()
                      << ", Temp (F): " << climateData[i].getTemp()
                      << ", Temp (C): " << climateData[i].getTempC() << std::endl;
        }

        
    }
    else{
        std::cout << "Not found" << std::endl;
    }

    return 0;
}
