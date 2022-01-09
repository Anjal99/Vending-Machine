//Anjal Parikh 1001660508
//SnackMachine.h Header file 

#ifndef SNACK_MACHINE_H
#define SNACK_MACHINE_H

#include<iostream>
#include<string>
#include<fstream>
#include<sstream>

enum reason 
{
    soldWithChange,
    soldWithoutChange,
    notEnoughInventory,
    notEnoughChange,
    insufficentFunds,
    unknownError
};

class SnackMachine
{
	friend std::ostream &operator<<(std::ostream &output, const SnackMachine &machine);
	friend std::string CreateSnackOutputLine(SnackMachine get);
	
	public:
		
		SnackMachine(std::string name="New Machine", int cost=50, int change=5000, int inventory=100)
		:machineName{name}, SnackPrice{cost}, changeLevel{change}, inventoryLevel{inventory}
		{
			
		}
		
		std::string getMachineName();
		
		bool buyASnack(int payment, std::string& change, int& status);
		
		int getInventoryLevel();
		
		int getMaxInventoryCapacity();
		
		bool incrementInventory(int amountToAdd);
		
		std::string getChangeLevel();
		
		bool incrementChangeLevel(int amountToAdd);
		
		std::string getMaxChangeCapacity();
		
		std::string getSnackPrice();
		
		std::string displayMoney(int amount);
		
		void setMachineName(std::string newMachineName);
		
		void setSnackPrice(int newSnackPrice);
		
	private:
		
		std::string machineName;
		int changeLevel{0};
		int maxChangeCapacity{5000};
		int SnackPrice{0};
		int inventoryLevel{0};
		int maxInventoryCapacity{100};

};

#endif
