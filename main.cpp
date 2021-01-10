#include<iostream>
#include<fstream>
#include<string>
#include<cstdlib>
#include<sstream>
#include<iomanip>
#include<vector>
#include<ctime>

using namespace std;

typedef struct ele{ //struct to keep data
	string country;
	string item_type;
	string order_id;
	int units_sold;
	float total_profit;
}Element;

int divide(vector<Element*> &v, int begin, int end) //sorts and divides to 2 parts tha array according to pivot (pivot is always dalst element)
{
	int tail = begin - 1;
	for(int traverse = begin; traverse < end; traverse++) //iterates from begin to end
	{
		if(v[traverse]->country.compare(v[end]->country) < 0) //compares the country names of data.
		{
			tail++;
			swap(v[tail],v[traverse]); //swaps the tail and traverse
		}
		else if(v[traverse]->country.compare(v[end]->country) == 0) //if the country names are same
		{
			if(v[traverse]->total_profit < v[end]->total_profit) //compare profits
			{
				tail++;
			    swap(v[tail],v[traverse]); //swaps the tail and traverse
			}
		}
	}
	tail++;
	swap(v[tail],v[end]); //swaps the tail with pivot
	return (tail); //returns pivot's position
}

void quicksort(vector<Element*> &v, int begin, int end)
{
	if(begin<end)
	{
		int pivot = divide(v,begin,end); //divide the array to 2 parts and return pivot
		quicksort(v,begin,pivot - 1); //sort left array
		quicksort(v,pivot + 1, end); //sort right array
	}
}

void delete_vector(vector<Element*> &v) //deletes dynamic variables to prevent memory leak
{
	for(int i = 0; i < v.size(); i++)
	{
		delete v[i];
	}
}

/*void print_vector(vector<Element*> &v) //prints vector
{
	for(int i = 0; i < v.size(); i++)
	{
		cout << v[i]->country + "\t" + v[i]->item_type + "\t" + v[i]->order_id + "\t" << v[i]->units_sold << "\t" << fixed << setprecision(2) << v[i]->total_profit << endl;
	}
}*/

int main(int argc, char *argv[]){
	
	vector<Element*> elementList; 
	clock_t time_req;
	
	ifstream file;
	file.open("sales.txt");
	
	if (!file){
		cerr << "File cannot be opened!";
		exit(1);
	}
	
	stringstream d(argv[1]);
	int N = 0; //you should read value of N from command line
	d >> N;
	
	string line;
	
	getline(file, line); //this is the header line
	for(int i = 0; i<N; i++){
		Element* new_element = new Element; //initializing data variable
		getline(file, line, '\t'); //country (string)
		new_element->country = line; //assign country
		getline(file, line, '\t'); //item type (string)
		new_element->item_type = line;//assign item type
		getline(file, line, '\t'); //order id (string)
		new_element->order_id = line;//assign order id
		file >> line; //units sold (integer)
		stringstream dummy1(line);
		int units_sold = 0;
		dummy1 >> units_sold; //converts string to int
		new_element->units_sold = units_sold; //assign unit sold
		file >> line; //total profit (float)
		stringstream dummy2(line);
		float profit = 0.0;
		dummy2 >> profit; //converts string to float
		new_element->total_profit = profit;//assign profit
		elementList.push_back(new_element); //add do vector
	    getline(file, line, '\n'); //this is for reading the \n character into dummy variable.
	}
	file.close();
	
	time_req = clock(); //start timer
	quicksort(elementList,0,elementList.size()-1); //sort the vector
	time_req = clock() - time_req; //finish timer
	cout << fixed << setprecision(20) << (float)time_req/(float)CLOCKS_PER_SEC << " seconds" << endl; //prints time
	
	ofstream filew;
	filew.open("sorted.txt");
	
	if (!filew){
		cerr << "File cannot be opened!";
		exit(1);
	}
	
	filew << "Country\tItem Type\tOrder Id\tUnits Sold\tTotal Profit\n"; //writes headers
	for(int i = 0; i < N; i++) //writes vector to the file
	{
		filew << elementList[i]->country + '\t';
		filew << elementList[i]->item_type + '\t';
		filew << elementList[i]->order_id + '\t';
		filew << elementList[i]->units_sold << '\t';
		filew << fixed << setprecision(5) << elementList[i]->total_profit << '\n';
	}
	filew.close();
	
	delete_vector(elementList);
	return 0;
}