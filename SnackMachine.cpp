//Anjal Parikh 1001660508
//SnackMachine.cpp 

#include "SnackMachine.h"

std::string SnackMachine::getMachineName()
{
	return machineName;
}

bool SnackMachine::buyASnack(int payment, std::string& change, int& status)
{
	if(getInventoryLevel() == 0)
	{
		status = notEnoughInventory;
		return false;
	}
	else if(getInventoryLevel() > 0)
	{
		int storeChange;
		storeChange = payment - SnackPrice;
		
		if(payment == SnackPrice)
		{
			inventoryLevel = inventoryLevel-1;
			changeLevel = changeLevel + payment;
			status = soldWithoutChange;
			return true;
		}
		else if(payment >SnackPrice && changeLevel > storeChange)
		{
			inventoryLevel = inventoryLevel - 1;
			changeLevel = changeLevel + SnackPrice;
			change = displayMoney(storeChange);
			status = soldWithChange;
			return true;
		}
		else if(changeLevel < storeChange)
		{
			status = notEnoughChange;
			return false;
		}
		else if(payment < SnackPrice)
		{
			status = insufficentFunds;
			return false;
		}
	}
	
}

int SnackMachine::getInventoryLevel()
{
	return inventoryLevel;
}

int SnackMachine::getMaxInventoryCapacity()
{
	return maxInventoryCapacity;
}

bool SnackMachine::incrementInventory(int amountToAdd)
{
	int tempVal = 0;
	
	tempVal = amountToAdd + inventoryLevel;
	
	if(tempVal <= maxInventoryCapacity)
	{
		inventoryLevel = inventoryLevel + amountToAdd;
		return true;
	}
	else
		return false;
	
}

std::string SnackMachine::getChangeLevel()
{
	return displayMoney(changeLevel);
}

bool SnackMachine::incrementChangeLevel(int amountToAdd)
{
	int tempVar = 0;
	
	tempVar = amountToAdd + changeLevel;
	
	if(tempVar <= maxChangeCapacity)
	{
		changeLevel = changeLevel + amountToAdd;
		return true;
	}
	else
		return false;
}

std::string SnackMachine::getMaxChangeCapacity()
{
	return displayMoney(maxChangeCapacity); 
}

std::string SnackMachine::getSnackPrice()
{
	return displayMoney(SnackPrice);
}

std::string SnackMachine::displayMoney(int amount)
{
	std::string dollars{std::to_string(amount / 100) };
	std::string cents{std::to_string(abs(amount % 100)) };

	return "$" + dollars + "." + (cents.size() == 1 ? "0" : "") + cents;
}

void SnackMachine::setMachineName(std::string newMachineName)
{
	machineName = newMachineName;
}

void SnackMachine::setSnackPrice(int newSnackPrice)
{
	SnackPrice = newSnackPrice;
}

std::ostream &operator<<( std::ostream &output, const SnackMachine &machine)
{
	output<<"Current Inventory Level:	"<<machine.inventoryLevel<<std::endl;
	output<<"Max Inventory Capacity:	"<<machine.maxInventoryCapacity<<std::endl;
	output<<"Current Change Level:	"<<machine.changeLevel<<std::endl;
	output<<"Max Change Capacity:	"<<machine.maxChangeCapacity<<std::endl;
	output<<"Current Snack Price:	"<<machine.SnackPrice<<std::endl;
	
	return output;
}

std::string CreateSnackOutputLine(SnackMachine get)
{
	std::ostringstream writeOut;
	writeOut << get.machineName << "|"
	 << get.SnackPrice << "|"
	 << get.changeLevel << "|"
	 <<get.inventoryLevel;

	return writeOut.str();
}
