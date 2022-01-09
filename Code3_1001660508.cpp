//Anjal Parikh 1001660508

#include<iostream>
#include<string>
#include<fstream>
#include<stdexcept>
#include<iomanip>
#include<vector>

#include "SnackMachine.h"
#include "SnackMachine.cpp"
#include "SnackLib.h"

using namespace std;

/*
void displayMenuOnScreen(int& choice)
{
	cout<<"0.	Walk away "<<endl;
	cout<<"1.	Buy a snack "<<endl;
	cout<<"2.	Restock the Machine "<<endl;
	cout<<"3.	Add Change "<<endl;
	cout<<"4.	Display Machine Info "<<endl;
	cout<<"5.	Update Machine Name "<<endl;
	cout<<"6.	Update Snack Price "<<endl;
	cin>>choice;
	
	// checking for bounds and invalid inputs
	while (!cin) 
	{
        cin.clear();
		cin.ignore(50, '\n');
		cout << "\nInput must be a numerical value";
		cin >>choice;
	}
    while (choice > 6 || choice < 0) 
	{
        cout << "\nThe option you chose is out of bounds. Please re-enter the choice\n";
        cout << "\nChoice: ";
        cin >> choice;
    }
}
*/
void get_command_line_params(int argc, char *argv[], string &inputFile, string &outputFile)
{
	if(argc!=3)
	{
		throw invalid_argument("Missing command line parameters – - Usage : input^filename output^filename");
	}
	else
	{
		inputFile = argv[1];
		outputFile = argv[2];
	}
}	

int main(int argc, char *argv[])
{
//	SnackMachine MySnackMachine{"New Machine", 50, 500, 100};
	int choice;
	int getPayment = 0;
	int newSnackPrice = 0;
	string getChange = "";
	int status = 0;
	bool returnVal;
	bool checkIf;
	int amountToAdd =0;
	int changeToAdd =0;
	string newMachineName;
	string inputFile, outputFile;
	string SnackMachineLine;
	bool decision;
	int machineChoice;
	int i;
	int progEnd;
	
	vector<SnackMachine> SetOfSnackMachines;
	vector<string> ConstructorValues(4);
	
	try
	{
		get_command_line_params(argc,argv,inputFile,outputFile);
	}
	catch(invalid_argument &ex)
	{
		cout<<"An exception occured: "<<ex.what()<<endl;
	}
	
	
	ifstream SnackInputFile(inputFile);
	ofstream SnackOutputFile(outputFile, ios::out);
	
	if(SnackInputFile.is_open())
	{
		while(getline(SnackInputFile, SnackMachineLine))
		{
			decision = ParseSnackLine(SnackMachineLine, ConstructorValues);
			
			if(decision = true)
			{
				SnackMachine temp{ConstructorValues[0],stoi(ConstructorValues[1]),stoi(ConstructorValues[2]),stoi(ConstructorValues[3])};
				SetOfSnackMachines.push_back(temp);
			}
		}
	}
	else
	{
		cout<<"Unable to open the file"<<endl;
		exit(0);
	}
	
	do
	{
		cout<<"Pick a Machine"<<endl;
	
		cout<<"0.	Exit"<<endl;
	
		for(i = 0; i<SetOfSnackMachines.size(); i++)
		{
			cout<<(i+1)<<".	"<<SetOfSnackMachines.at(i).getMachineName()<<endl;
		}
		
		
		if(i+1)
		{
			cout<<(i+1)<<"	"<<"Add a Machine"<<endl;
		}
		
		cout<<"Choice is:	"<<endl;
		cin>>machineChoice;
		
		//cout<<"Machine: "<<machineChoice;
		
		if(machineChoice == 0)
		{
			for(int j = 0; j<SetOfSnackMachines.size();j++)
			{
				SnackOutputFile<<CreateSnackOutputLine(SetOfSnackMachines.at(j))<<endl;
			}
		}
		else if((machineChoice +1) == (i+1))
		{
			SnackMachine temp;
			SetOfSnackMachines.push_back(temp);
			cout<<"New Machine was Added "<<endl;
		}
		else
		{
			machineChoice -=1;

			cout<<endl;
			do
			{
				cout<<SetOfSnackMachines.at(machineChoice).getMachineName()<<endl;
				
				cout<<"0.	Walk away "<<endl;
				cout<<"1.	Buy a snack "<<endl;
				cout<<"2.	Restock the Machine "<<endl;
				cout<<"3.	Add Change "<<endl;
				cout<<"4.	Display Machine Info "<<endl;
				cout<<"5.	Update Machine Name "<<endl;
				cout<<"6.	Update Snack Price "<<endl;
				cin>>choice;
				
				// checking for bounds and invalid inputs
				while (cin.fail()) 
				{
					cin.clear();
					cin.ignore(50, '\n');
					cout << "\nInput must be a numerical value";
					cin >>choice;
				}
				while (choice > 6 || choice < 0) 
				{
					cout << "\nThe option you chose is out of bounds. Please re-enter the choice\n";
					cout << "\nChoice: ";
					cin >> choice;
				}
								
				switch(choice)
				{
					case 0:
						cout<<"Are you sure you aren't really HUNGRY and need a Snack?"<<endl;
						break;
					
					case 1:
						//use get snackPrice to print snack price.
						cout<<"A snack costs "<<SetOfSnackMachines.at(machineChoice).getSnackPrice()<<endl;
						cout<<"Insert Cash ";
						
						//bool buyASnack
						cin>>getPayment;
						
						while (!cin) 
						{
							cin.clear();
							cin.ignore(50, '\n');
							cout << "\nInput must be a numerical value";
							cin >>getPayment;
						}
						while(getPayment < 0)
						{
							cout<<"Please enter a value above 0"<<endl;
							cin>>getPayment;
						}
						
						returnVal = SetOfSnackMachines.at(machineChoice).buyASnack(getPayment,getChange,status);
						
						if(returnVal == true && status == soldWithoutChange)
						{
							cout<<"Thank you for purchasing with exact change "<<endl ;
						}
						else if(returnVal == true && status == soldWithChange)
						{
							cout<<"Change to be given "<<getChange<<endl;
						}
						else if(returnVal == false && status == insufficentFunds)
						{
							cout<<"Insufficent Payment so no Snack For you "<<endl;
						}
						else if(returnVal == false && status == notEnoughChange)
						{
							cout<<"The snack Machine doesnt have enough change"<<endl;
						}
						else if(returnVal == false && status == notEnoughInventory)
						{
							cout<<"There is no Inventory left "<<endl;
						}
						else
							cout<<"Unknown Error "<<endl;
						
						break;
						
					case 2:
						cout<<"Please enter amount to restock the Inventory"<<endl;
						cin>>amountToAdd;
						
						while (!cin) 
						{
							cin.clear();
							cin.ignore(50, '\n');
							cout << "\nInput must be a numerical value";
							cin >>amountToAdd;
						}
						while(amountToAdd < 0)
						{
							cout<<"The input must be positive"<<endl;
							cin>>amountToAdd;
						}
					
						checkIf = SetOfSnackMachines.at(machineChoice).incrementInventory(amountToAdd);
						if(checkIf == true)
						{
							cout<<"Adding Inventory"<<endl;
							cout<<"Your inventory level is:"<<SetOfSnackMachines.at(machineChoice).getInventoryLevel()<<endl;
						}
						else
						{
							cout<<"I cant add any inventory"<<endl;
							cout<<"Your inventory level is:"<<SetOfSnackMachines.at(machineChoice).getInventoryLevel()<<endl;
						}
						
						break;
						
					case 3:
						cout<<"Please enter the Amount you want to add in change "<<endl;
						cin>>changeToAdd;
						
						while (!cin) 
						{
							cin.clear();
							cin.ignore(50, '\n');
							cout << "\nInput must be a numerical value";
							cin >>amountToAdd;
						}
						while(changeToAdd <0)
						{
							cout<<"The input must be positive"<<endl;
							cin>>changeToAdd;
						}
						
						checkIf = SetOfSnackMachines.at(machineChoice).incrementChangeLevel(changeToAdd);
						if(checkIf == true)
						{
							cout<<"Adding Change "<<endl;
						}
						else
						{
							cout<<"I cant add any change"<<endl;
						}
						
						break;
					
					case 4:
						cout<<SetOfSnackMachines.at(machineChoice)<<endl;
						
						break;
						
					case 5:
						cin.ignore(50,'\n');
						cout<<"Enter a new Machine Name:	";
						
						getline(cin,newMachineName);

						SetOfSnackMachines.at(machineChoice).setMachineName(newMachineName);
						cout<<"Machine name has been updated"<<endl;
						
						break;
						
					case 6:
						cout<<"Enter a new Snack Price: "<<endl;
						cin>>newSnackPrice;
						SetOfSnackMachines.at(machineChoice).setSnackPrice(newSnackPrice);
						cout<<"Snack has been updated"<<endl;
						
						break;
						
				}
				
			}
			while(choice!=0);
		
		}	
		
	}
	while(machineChoice!=0);
	
	//writing to the File 
	
	
	SnackInputFile.close();
	SnackOutputFile.close();

	return 0;
}