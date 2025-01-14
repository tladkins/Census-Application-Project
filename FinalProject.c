// --------------------------------------------------------------------------------
// Name: Tanner Adkins
// Class: SET-151-400
// Abstract: Final Project
// --------------------------------------------------------------------------------
#define _CRT_SECURE_NO_WARNINGS
// --------------------------------------------------------------------------------
// Includes – built-in libraries of functions
// --------------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
// --------------------------------------------------------------------------------
// Constants
// --------------------------------------------------------------------------------
const int intARRAY_SIZE = 100;
#define true 1
#define false 0
// --------------------------------------------------------------------------------
// User Defined Types (UDT)
// --------------------------------------------------------------------------------
typedef int boolean;

typedef struct
{
	int intRowID;
	int intDate;
	int intState;
	int intCounty;
	int intRace;
	int intNumberinHousehold;
	float sngYearlyIncome;
} udtCensusType;

// --------------------------------------------------------------------------------
// Prototypes
// --------------------------------------------------------------------------------
int GetMode();
void GetAndValidate(int* pintDate, int* pintState, int* pintCounty, int* pintRace, int* pintNumberinHousehold, float* psngYearlyIncome);
void GetAndValidateDate(int* pintDate);
void GetAndValidateStateAndCounty(int* pintState, int* pintCounty);
void GetAndValidateRace(int* pintRace);
void GetAndValidateHousehold(int* pintNumberinHousehold);
void GetAndValidateIncome(int* psngYearlyIncome);
void AddDataToFile(int intNextRow, int intDate, int intState, int intCounty, int intRace, int intNumberinHousehold, float sngYearlyIncome);
int ContinueDataEntry();
char GetInputSelection();
void InitializeCensusList(udtCensusType audtCensusList[]);
void InitializeCensus(udtCensusType* pudtCensuses);
void PopulateCensusList(udtCensusType audtCensusList[]);
void PrintCensusList(udtCensusType audtCensusList[]);
void PrintCensus(int intIndex, udtCensusType udtCensus);
void AddCensusToArray(char strCensus[], udtCensusType* pudtCensuses);
void GetNextField(char strNextField[], char strCensus[], char chrCharacterToAppend);
void Trim(char strSource[]);
void DoNeededCalculations(audtCensusList, intInputCount);
void CalculateTotalHouseholdsPerCounty(udtCensusType audtCensusList[], int intInputCount);
void CalculateTotalHouseholdByRace(udtCensusType audtCensusList[], int intInputCount);
void CalculateAverageHouseholdIncome(udtCensusType audtCensusList[], int intInputCount);
void PrintByRace(int intCaucasian, int intAfricanAmerican, int intHispanic, int intAsian, int intOther);
void PrintByStateAndCounty(int intOhioValue, int intHamCountyValue, int intButCountyValue, int intKentuckyValue, int intBooCountyValue, int intKentCountyValue);
void CalculateAverageIncomeByCounty(udtCensusType audtCensusList[], int intInputCount);
void FloatPrintByStateAndCounty(float sngOhio, float sngHamCounty, float sngButCounty, float sngKentucky, float sngBooCounty, float sngKentCounty);
void FloatPrintByRace(float sngCaucasian, float sngAfricanAmerican, float sngHispanic, float sngAsian, float sngOther);
void CalculateAverageIncomeByRace(udtCensusType audtCensusList[], int intInputCount);
void CalculatePercentageBelowPoverty(udtCensusType audtCensusList[], int intInputCount);
void PrintPercentageBelowPoverty(int intPovertyCount);
void CalculatePercentageBelowPovertyByCounty(udtCensusType audtCensusList[], int intInputCount);
int SeeIfInPoverty(float sngIncome, int intHouseholdSize);
void FloatPrintPercentByStateAndCounty(float sngOhio, float sngHamCounty, float sngButCounty, float sngKentucky, float sngBooCounty, float sngKentCounty);
void CalculatePercentageBelowPovertyByRace(udtCensusType audtCensusList[], int intInputCount);
void FloatPrintPercentByRace(float sngCaucasianPercentage, float sngAfricanAmericanPercentage, float sngHispanicPercentage, float sngAsianPercentage, float sngOtherPercentage);
// --------------------------------------------------------------------------------
// Name: main
// Abstract: This is where the program starts
// --------------------------------------------------------------------------------
int main()
{
	int intDate = 0;
	int intState = 0;
	int intCounty = 0;
	int intRace = 0;
	int intNumberinHousehold = 0;
	float sngYearlyIncome = 0;
	int intNextRow = 0;
	int intMode = 1;
	int intContinue = 0;
	char chrInputSelection = 0;
	int intInputCount = 0;

	//Get the mode for the appliction
	intMode = GetMode();

	while (intMode != 3)
	{
		//If Write Mode was selected
		if (intMode == 1)
		{
			do
			{
				GetAndValidate(&intDate, &intState, &intCounty, &intRace, &intNumberinHousehold, &sngYearlyIncome);

				AddDataToFile(intNextRow, intDate, intState, intCounty, intRace, intNumberinHousehold, sngYearlyIncome);

				//Increment to the next row
				intNextRow += 1;

				//Count the number of inputs to be used later
				intInputCount += 1;

				intContinue = ContinueDataEntry();
				//Yes = 1
				//No  = 2
			} while (intContinue != 2);
		}
		else
		{
			chrInputSelection = GetInputSelection();

			udtCensusType audtCensusList[100];

			InitializeCensusList(audtCensusList);

			PopulateCensusList(audtCensusList);

			DoNeededCalculations(audtCensusList, intInputCount, chrInputSelection);

		}
		intMode = GetMode();
	}
	
	system("pause");
	return 0;
}

int GetMode()
{
	int intMode = 0;
	do
	{
		printf("Please enter your numerical choice: \n");
		printf("(1)Write Mode\n");
		printf("(2)Display Mode\n");
		printf("(3)End Application\n");
		scanf(" %d", &intMode);
	} while (intMode != 1 && intMode != 2 && intMode != 3);

	return intMode;
}
void GetAndValidate(int* pintDate, int* pintState, int* pintCounty, int* pintRace, int* pintNumberinHousehold, float* psngYearlyIncome)
{
	//GetAndValidateDate();
	GetAndValidateDate(pintDate);
	GetAndValidateStateAndCounty(pintState, pintCounty);
	GetAndValidateRace(pintRace);
	GetAndValidateHousehold(pintNumberinHousehold);
	GetAndValidateIncome(psngYearlyIncome);
}

void GetAndValidateDate(int* pintDate)
{
	do
	{
		//Get input
		printf("Enter the date as 10 numbers with no spaces: \n");
		scanf("%d", pintDate);
	} while (*pintDate < 01012024);
}


void GetAndValidateStateAndCounty(int* pintState, int* pintCounty)
{
	do
	{
		printf("Enter your state: \n");
		printf("Ohio: (1)\n");
		printf("Kentucky: (2)\n");
		scanf("%d", pintState);
	} while (*pintState != 1 && *pintState != 2);

	do
	{
		printf("Enter you county: \n");

		//if Ohio, print the OH counties
		if (*pintState == 1)
		{
			printf("Hamilton: (1)\n");
			printf("Butler: (2)\n");
		}
		//if Kentucky, print the KY counties
		else
		{
			printf("Boone: (1)\n");
			printf("Kenton: (2)\n");
		}
		scanf("%d", pintCounty);

	} while (*pintCounty != 1 && *pintCounty != 2);
}


void GetAndValidateRace(int* pintRace)
{
	do
	{
		printf("Enter the race of the head of the household: \n");
		printf("(1) Caucasian\n");
		printf("(2) African American\n");
		printf("(3) Hispanic\n");
		printf("(4) Asian\n");
		printf("(5) Other\n");
		scanf("%d", pintRace);
	} while (*pintRace < 1 || *pintRace > 5);
}


void GetAndValidateHousehold(int* pintNumberinHousehold)
{
	do
	{
		printf("Enter the number of people in your household: \n");
		scanf("%d", pintNumberinHousehold);
	} while (*pintNumberinHousehold < 0);
}


void GetAndValidateIncome(float* psngYearlyIncome)
{
	do
	{
		printf("Enter the household yearly income: \n");
		scanf("%f", psngYearlyIncome);
	} while (*psngYearlyIncome < 0);
}

void AddDataToFile(int intNextRow, int intDate, int intState, int intCounty, int intRace, int intNumberinHousehold, float sngYearlyIncome)
{
	FILE* file = fopen("CensusData.csv", "a");
	if (file == NULL) {
		printf("Could not open file for writing\n");
		return 1;
	}

	// Write data row
	fprintf(file, "%d, %d, %d,%d,%d,%d,%.0f\n", intNextRow, intDate, intState, intCounty, intRace, intNumberinHousehold, sngYearlyIncome);

	// Close the file
	fclose(file);
}

int ContinueDataEntry()
{
	int intContinue = 0;

	do
	{
		printf("Continue entering data? (1)Yes (2)No\n");
		scanf("%d", &intContinue);
	} while (intContinue != 1 && intContinue != 2);

	return intContinue;
}

// --------------------------------------------------------------------------------
// Name: InitializeCensusList
// Abstract: Initialize all the censuses in the list
// --------------------------------------------------------------------------------
char GetInputSelection()
{
	char chrInputSeleciton = 0;
	do
	{
		printf("Please enter you selection as a letter.\n");
		printf("A: Total Households Surveyed: Will show the total of the overall surveyed.\n");
		printf("B: Total Households Surveyed per County: Will show the total of the overall surveyed by county and state.\n");
		printf("C: Total Households Surveyed per Race: Will show the total of the overall surveyed by reported race.\n");
		printf("D: Average Household Income: Show the overall average household income for those that are surveyed.\n");
		printf("E: Average Household Income by county and state: Will display the average household income by state and then by county.\n");
		printf("F: Average Household Income by race: Will display the average household income by race.\n");
		printf("G: Percentage below Poverty: Show the overall percentage of those below poverty based on the table below for all data collected.\n");
		printf("H: Percentage below Poverty by county and state: Show the overall percentage of those below poverty based on the table below for all data collected by county and state.\n");
		printf("I: Percentage below Poverty by race: Show the overall percentage of those below poverty based on the table below for all data collected by race.\n");
		scanf(" %c", &chrInputSeleciton);

		//Coded toupper function
		if (chrInputSeleciton > 90)
		{
			chrInputSeleciton = chrInputSeleciton - 32;
		}

	} while (chrInputSeleciton < 65 || chrInputSeleciton > 73);

	return chrInputSeleciton;
}




// --------------------------------------------------------------------------------
// Name: InitializeCensusList
// Abstract: Initialize all the censuses in the list
// --------------------------------------------------------------------------------
void InitializeCensusList(udtCensusType audtCensusList[])
{
	int intIndex = 0;

	for (intIndex = 0; intIndex < intARRAY_SIZE; intIndex += 1)
	{
		//Pass a sigle array element by pointer
		InitializeCensus(&audtCensusList[intIndex]);
	}
}



// --------------------------------------------------------------------------------
// Name: InitializeCensus
// Abstract: Initialize all the values in the list of censuses
// --------------------------------------------------------------------------------
void InitializeCensus(udtCensusType* pudtCensuses)
{
	pudtCensuses->intRowID = 0;
	pudtCensuses->intState = 0;
	pudtCensuses->intCounty = 0;
	pudtCensuses->intRace = 0;
	pudtCensuses->intNumberinHousehold = 0;
	pudtCensuses->sngYearlyIncome = 0;
}



// --------------------------------------------------------------------------------
// Name: PopulateCensusList
// Abstract: Load the Censuses froma file into the array
// --------------------------------------------------------------------------------
void PopulateCensusList(udtCensusType audtCensusList[])
{
	// Declare a file pointer
	FILE* pfilInput = 0;
	int intResultFlag = 0;
	char strBuffer[50] = "";
	char chrLetter = 0;
	int intIndex = 0;

	// Try to open the file for reading (notice you have to double up the backslashes)
	intResultFlag = OpenInputFile("CensusData.csv", &pfilInput);

	// Was the file opened?
	if (intResultFlag == 1)
	{

		// Yes, read in records until end of file( EOF )
		while (feof(pfilInput) == 0)
		{
			// Read next line from file
			fgets(strBuffer, sizeof(strBuffer), pfilInput);

			//Add address to array
			AddCensusToArray(strBuffer, &audtCensusList[intIndex]);

			// Read one character
			//chrLetter = fgetc( pfilInput );

			intIndex += 1;
		}
		// Clean up
		fclose(pfilInput);
	}

}



// --------------------------------------------------------------------------------
// Name: OpenInputFile
// Abstract: Open the file for reading.  Return true if successful.
// --------------------------------------------------------------------------------
int OpenInputFile(char strFileName[], FILE** ppfilInput)
{

	int intResultFlag = 0;

	// Open the file for reading
	*ppfilInput = fopen(strFileName, "rb");

	// Success?
	if (*ppfilInput != 0)
	{
		// Yes
		intResultFlag = 1;
	}
	else
	{
		// No
		printf("Error opening %s for reading!!!\n", strFileName);
	}

	return intResultFlag;

}



// --------------------------------------------------------------------------------
// Name: AddAddressToArray
// Abstract: Add address to the array
// --------------------------------------------------------------------------------
void AddCensusToArray(char strCensus[], udtCensusType* pudtCensuses)
{
	char strNextField[50] = "";

	// Append a comma so parsing last field is just like all the others
	//AppendString(strCensus, ",");

	// Record ID
	GetNextField(strNextField, strCensus, ',');
	pudtCensuses->intRowID = atol(strNextField);

	//Clear the field for the next new field
	// using memset 
	memset(strNextField, '\0', StringLength(strNextField));

	//Date 
	GetNextField(strNextField, strCensus, ',');
	pudtCensuses->intDate = atol(strNextField);

	//Clear the field for the next new field
	// using memset 
	memset(strNextField, '\0', StringLength(strNextField));

	//State
	GetNextField(strNextField, strCensus, ',');
	pudtCensuses->intState = atol(strNextField);

	//Clear the field for the next new field
	memset(strNextField, '\0', StringLength(strNextField));

	//County
	GetNextField(strNextField, strCensus, ',');
	pudtCensuses->intCounty = atol(strNextField);

	//Clear the field for the next new field
	memset(strNextField, '\0', StringLength(strNextField));

	// Race
	GetNextField(strNextField, strCensus, ',');
	pudtCensuses->intRace = atol(strNextField);

	//Clear the field for the next new field
	memset(strNextField, '\0', StringLength(strNextField));

	//Number in Household
	GetNextField(strNextField, strCensus, ',');
	pudtCensuses->intNumberinHousehold = atol(strNextField);

	//Clear the field for the next new field
	memset(strNextField, '\0', StringLength(strNextField));

	//County
	GetNextField(strNextField, strCensus, ',');
	pudtCensuses->sngYearlyIncome = atol(strNextField);
}



// --------------------------------------------------------------------------------
// Name: GetNextField
// Abstract: Get the next field in the instance of the structure
// --------------------------------------------------------------------------------
void GetNextField(char strNextField[], char strCensus[], char chrCharacterToAppend)
{
	char chrCurrentLetter = "";
	int intIndex = 0;
	int intIndex2 = 0;


	//Set the current letter
	chrCurrentLetter = strCensus[0];

	do
	{
		//Load the next field from the address array
		strNextField[intIndex] = strCensus[0];

		//Clear the character after its been moved into the field array
		for (intIndex2 = 0; intIndex2 < StringLength(strCensus); intIndex2 += 1)
		{
			strCensus[intIndex2] = strCensus[intIndex2 + 1];
		}

		intIndex += 1;

		//Set the next current letter
		chrCurrentLetter = strCensus[0];
	} while (chrCurrentLetter != ',' && chrCurrentLetter != 0);

	//Trim off the comma in the address array
	for (intIndex2 = 0; intIndex2 < StringLength(strCensus); intIndex2 += 1)
	{
		strCensus[intIndex2] = strCensus[intIndex2 + 1];
	}

	//Trim the field
	Trim(strNextField);
}



// --------------------------------------------------------------------------------
// Name: StringLength
// Abstract: Return the string length
// --------------------------------------------------------------------------------
int StringLength(char strSource[])
{
	int intIndex = 0;
	int intLength = 0;

	// Pre-test because string may be empty
	while (strSource[intIndex] != 0)
	{
		intIndex += 1;
	}

	intLength = intIndex;

	return intLength;
}


// --------------------------------------------------------------------------------
// Name: StringCopy
// Abstract: Copy the source to the destination
// --------------------------------------------------------------------------------
void StringCopy(char strDestination[], char strSource[])
{
	int intIndex = 0;

	// Copy each character
	while (strSource[intIndex] != 0)
	{
		strDestination[intIndex] = strSource[intIndex];
		intIndex += 1;
	}

	// Terminate
	strDestination[intIndex] = 0;

}


// --------------------------------------------------------------------------------
// Name: AppendString
// Abstract: Append the source to the end of the destinatoin.
// --------------------------------------------------------------------------------
void AppendString(char strDestination[], char strSource[])
{
	int intDestinationLength = 0;
	int intIndex = 0;

	// Find the length
	intDestinationLength = StringLength(strDestination);

	// Copy each character
	while (strSource[intIndex] != 0)
	{
		strDestination[intDestinationLength + intIndex] = strSource[intIndex];

		intIndex += 1;
	}

	// Terminate
	strDestination[intDestinationLength + intIndex] = 0;

}


// --------------------------------------------------------------------------------
// Name: FindLetterIndex
// Abstract: Find first occurence of letter (case-sensitive) from left to right.
// --------------------------------------------------------------------------------
int FindLetterIndex(char strSource[], char chrLetterToFind)
{
	int intLetterToFindIndex = -1;
	int intIndex = 0;

	// Check character
	while (strSource[intIndex] != 0)
	{
		// Is this the character for which we are looking
		if (strSource[intIndex] == chrLetterToFind)
		{
			// Yes, save the index
			intLetterToFindIndex = intIndex;

			// Stop searching
			break;
		}
		intIndex += 1;
	}

	return intLetterToFindIndex;
}



// --------------------------------------------------------------------------------
// Name: Trim
// Abstract: Remove leading and trailing whitespace (space, tab or newline)
// --------------------------------------------------------------------------------
void Trim(char strSource[])
{

	int intIndex = 0;
	int intFirstNonWhitespaceIndex = -1;
	int intLastNonWhitespaceIndex = 0;
	int intSourceIndex = 0;
	int intDestinationIndex = 0;

	// Default first non-whitespace character index to end of string in case string is all whitespace
	// Bug fix.  Not in video.
	intFirstNonWhitespaceIndex = StringLength(strSource);

	// Find first non-whitespace character
	while (strSource[intIndex] != 0)
	{
		// Non-whitespace character?
		if (IsWhiteSpace(strSource[intIndex]) == false)
		{
			// Yes, save the index
			intFirstNonWhitespaceIndex = intIndex;

			// Stop searching!
			break;
		}

		// Next character
		intIndex += 1;
	}

	// Find the last non-whitespace character
	while (strSource[intIndex] != 0)
	{
		// Non-whitespace character?
		if (IsWhiteSpace(strSource[intIndex]) == false)
		{
			// Yes, save the index
			intLastNonWhitespaceIndex = intIndex;
		}

		// Next character
		intIndex += 1;
	}

	// Any non-whitepsace characters?
	if (intFirstNonWhitespaceIndex >= 0)
	{
		// Yes, copy everything in between
		for (intSourceIndex = intFirstNonWhitespaceIndex; intSourceIndex <= intLastNonWhitespaceIndex; intSourceIndex += 1)
		{
			// Copy next character
			strSource[intDestinationIndex] = strSource[intSourceIndex];

			intDestinationIndex += 1;
		}
	}

	// Terminate 
	strSource[intDestinationIndex] = 0;
}



// --------------------------------------------------------------------------------
// Name: IsWhiteSpace
// Abstract: Return true if letter is a space, tab, newline or carriage return
// --------------------------------------------------------------------------------
boolean IsWhiteSpace(char chrLetterToCheck)
{
	boolean blnIsWhiteSpace = false;

	// Space
	if (chrLetterToCheck == ' ') blnIsWhiteSpace = true;

	// Tab
	if (chrLetterToCheck == '\t') blnIsWhiteSpace = true;

	// Carriarge return
	if (chrLetterToCheck == '\r') blnIsWhiteSpace = true;

	// Line feed
	if (chrLetterToCheck == '\n') blnIsWhiteSpace = true;

	return blnIsWhiteSpace;
}



// --------------------------------------------------------------------------------
// Name: DoNeededCalculations
// Abstract: Return true if letter is a space, tab, newline or carriage return
// --------------------------------------------------------------------------------
void DoNeededCalculations(udtCensusType audtCensusList[], int intInputCount, char chrInputSelection)
{
	switch (chrInputSelection)
	{
	case 'A':
		printf("Total Households Surveyed: %d\n", intInputCount);
		break;
	case 'B':
		CalculateTotalHouseholdsPerCounty(audtCensusList, intInputCount);
		break;
	case 'C':
		CalculateTotalHouseholdByRace(audtCensusList, intInputCount);
		break;
	case 'D':
		CalculateAverageHouseholdIncome(audtCensusList, intInputCount);
		break;
	case 'E':
		CalculateAverageIncomeByCounty(audtCensusList, intInputCount);
		break;
	case 'F':
		CalculateAverageIncomeByRace(audtCensusList, intInputCount);
		break;
	case 'G': 
		CalculatePercentageBelowPoverty(audtCensusList, intInputCount);
		break;
	case 'H':
		CalculatePercentageBelowPovertyByCounty(audtCensusList, intInputCount);
		break;
	case 'I':
		CalculatePercentageBelowPovertyByRace(audtCensusList, intInputCount);
	}
}


// --------------------------------------------------------------------------------
// Name: CalculateTotalHouseholdsPerCounty
// Abstract: Total the households surveyed by county 
// --------------------------------------------------------------------------------
void CalculateTotalHouseholdsPerCounty(udtCensusType audtCensusList[], int intInputCount)
{
	int intIndex = 0;
	int intState = 0;
	int intCounty = 0;
	int intOhio = 0;
	int intKentucky = 0;
	int intHamCounty = 0;
	int intButCounty = 0;
	int intBooCounty = 0;
	int intKentCounty = 0;

	for (intIndex = 0; intIndex <= intInputCount; intIndex += 1)
	{
		intCounty = audtCensusList[intIndex].intCounty;

		intState = audtCensusList[intIndex].intState;


		switch (intState)
		{
		case 1: 
			if (intCounty == 1)
			{
				intHamCounty += 1;
				intOhio += 1;
				break;
			}
			else
			{
				intButCounty += 1;
				intOhio += 1;
				break;
			}
		case 2: 
			if (intCounty == 1)
			{
				intBooCounty += 1;
				intKentucky += 1;
				break;
			}
			else
			{
				intKentCounty += 1;
				intKentucky += 1;
				break;
			}
		}
	}
	//give a space to the output
	printf("\n");

	//print a descriptor line
	printf("Number in households by county: \n");

	PrintByStateAndCounty(intOhio, intHamCounty, intButCounty, intKentucky, intBooCounty, intKentCounty);
}



// --------------------------------------------------------------------------------
// Name: CalculateTotalHouseholdByRace
// Abstract: Calculate the total households by race
// --------------------------------------------------------------------------------
void CalculateTotalHouseholdByRace(udtCensusType audtCensusList[], int intInputCount)
{
	int intIndex = 0;
	int intRace = 0;
	int intCaucasian = 0;
	int intAfricanAmerican = 0;
	int intHispanic = 0;
	int intAsian = 0;
	int intOther = 0;

	for (intIndex = 0; intIndex <= intInputCount; intIndex += 1)
	{
		intRace = audtCensusList[intIndex].intRace;

		switch (intRace)
		{
		case 1:
			intCaucasian += 1;
			break;
		case 2:
			intAfricanAmerican += 1;
			break;
		case 3:
			intHispanic += 1;
			break;
		case 4:
			intAsian += 1;
			break;
		case 5:
			intOther += 1;
			break;
		}
	}
	//give a space to the output
	printf("\n");

	//print a descriptor line
	printf("Number in households by race: \n");

	PrintByRace(intCaucasian, intAfricanAmerican, intHispanic, intAsian, intOther);
}



// --------------------------------------------------------------------------------
// Name: CalculateAverageHouseholdIncome
// Abstract: Calculate the average income of all of the households
// --------------------------------------------------------------------------------
void CalculateAverageHouseholdIncome(udtCensusType audtCensusList[], int intInputCount)
{
	float sngTotalIncome = 0;
	float sngAverageIncome = 0;
	int intIndex = 0;

	//Calculate Average
	for (intIndex = 0; intIndex <= intInputCount; intIndex += 1)
	{
		sngTotalIncome += audtCensusList[intIndex].sngYearlyIncome;
	}
	sngAverageIncome = sngTotalIncome / intInputCount;

	//print average
	printf("Average Household Income: $%.2f\n", sngAverageIncome);
}



// --------------------------------------------------------------------------------
// Name: PrintByStateAndCounty
// Abstract: Procedure to print by state and county
// --------------------------------------------------------------------------------
void PrintByStateAndCounty(int intOhioValue, int intHamCountyValue, int intButCountyValue, int intKentuckyValue, int intBooCountyValue, int intKentCountyValue)
{
	printf("Ohio:\t\t %d\n", intOhioValue);
	printf("  Hamilton:\t %d\n", intHamCountyValue);
	printf("  Butler:\t %d\n", intButCountyValue);
	printf("Kentucky:\t %d\n", intKentuckyValue);
	printf("  Boone:\t %d\n", intBooCountyValue);
	printf("  Kenton:\t %d\n", intKentCountyValue);
	printf("\n");
}


// --------------------------------------------------------------------------------
// Name: PrintByRace
// Abstract: Procedure to print by race
// --------------------------------------------------------------------------------
void PrintByRace(int intCaucasian, int intAfricanAmerican, int intHispanic, int intAsian, int intOther)
{
	printf("Caucasian: \t %d\n", intCaucasian);
	printf("African American:%d\n", intAfricanAmerican);
	printf("Hispanic: \t %d\n", intHispanic);
	printf("Asian:\t\t %d\n", intAsian);
	printf("Other:\t\t %d\n", intOther);
	printf("\n");
}


// --------------------------------------------------------------------------------
// Name: CalculateAverageIncomeByCounty
// Abstract: Collect and average each value by county
// --------------------------------------------------------------------------------
void CalculateAverageIncomeByCounty(udtCensusType audtCensusList[], int intInputCount)
{
	int intIndex = 0;

	//Holder variables
	int intState = 0;
	int intCounty = 0;
	float sngIncome = 0;

	//Income variables
	float sngOhio = 0;
	float sngKentucky = 0;
	float sngHamCounty = 0;
	float sngButCounty = 0;
	float sngBooCounty = 0;
	float sngKentCounty = 0;

	//Total variables
	int intOhio = 0;
	int intKentucky = 0;
	int intHamCounty = 0;
	int intButCounty = 0;
	int intBooCounty = 0;
	int intKentCounty = 0;

	//Averages Variables
	float sngOhioAverage = 0;
	float sngKentuckyAverage = 0;
	float sngHamCountyAverage = 0;
	float sngButCountyAverage = 0;
	float sngBooCountyAverage = 0;
	float sngKentCountyAverage = 0;

	for (intIndex = 0; intIndex <= intInputCount; intIndex += 1)
	{
		intCounty = audtCensusList[intIndex].intCounty;

		intState = audtCensusList[intIndex].intState;

		sngIncome = audtCensusList[intIndex].sngYearlyIncome;


		switch (intState)
		{
		case 1:
			if (intCounty == 1)
			{
				sngHamCounty += sngIncome;
				sngOhio += sngIncome;
				intOhio += 1;
				intHamCounty += 1;
				break;
			}
			else
			{
				sngButCounty += sngIncome;
				sngOhio += sngIncome;
				intButCounty += 1;
				intOhio += 1;
				break;
			}
		case 2:
			if (intCounty == 1)
			{
				sngBooCounty += sngIncome;
				sngKentucky += sngIncome;
				intBooCounty += 1;
				intKentucky += 1;
				break;
			}
			else
			{
				sngKentCounty += sngIncome;
				sngKentucky += sngIncome;
				intKentCounty += 1;
				intKentucky += 1;
				break;
			}
		}
	}

	//Calculate averages
	sngOhioAverage = sngOhio / intOhio;
	sngKentuckyAverage = sngKentucky / intKentucky;
	sngHamCountyAverage = sngHamCounty / intHamCounty;
	sngButCountyAverage = sngButCounty / intButCounty;
	sngBooCountyAverage = sngBooCounty / intBooCounty;
	sngKentCountyAverage = sngKentCounty / intKentCounty;

	//give a space to the output
	printf("\n");

	//print a descriptor line
	printf("Average income by county: \n");

	FloatPrintByStateAndCounty(sngOhioAverage, sngHamCountyAverage, sngButCountyAverage, sngKentuckyAverage, sngBooCountyAverage, sngKentCountyAverage);
}



// --------------------------------------------------------------------------------
// Name: FloatPrintByStateAndCounty
// Abstract: Procedure to print by state and county
// --------------------------------------------------------------------------------
void FloatPrintByStateAndCounty(float sngOhio, float sngHamCounty, float sngButCounty, float sngKentucky, float sngBooCounty, float sngKentCounty)
{
	printf("Ohio:\t\t %.2f\n", sngOhio);
	printf("  Hamilton:\t %.2f\n", sngHamCounty);
	printf("  Butler:\t %.2f\n", sngButCounty);
	printf("Kentucky:\t %.2f\n", sngKentucky);
	printf("  Boone:\t %.2f\n", sngBooCounty);
	printf("  Kenton:\t %.2f\n", sngKentCounty);
	printf("\n");
}


// --------------------------------------------------------------------------------
// Name: CalculateAverageIncomeByRace
// Abstract: Calculate the total households by race
// --------------------------------------------------------------------------------
void CalculateAverageIncomeByRace(udtCensusType audtCensusList[], int intInputCount)
{
	int intIndex = 0;
	//Holder values
	int intRace = 0;
	float sngIncome = 0;
	//Tally values
	int intCaucasian = 0;
	int intAfricanAmerican = 0;
	int intHispanic = 0;
	int intAsian = 0;
	int intOther = 0;
	//Income Totals
	float sngCaucasian = 0;
	float sngAfricanAmerican = 0;
	float sngHispanic = 0;
	float sngAsian = 0;
	float sngOther = 0;
	//Averages variables
	float sngCaucasianAverage = 0;
	float sngAfricanAmericanAverage = 0;
	float sngHispanicAverage = 0;
	float sngAsianAverage = 0;
	float sngOtherAverage = 0;

	for (intIndex = 0; intIndex <= intInputCount; intIndex += 1)
	{
		intRace = audtCensusList[intIndex].intRace;
		sngIncome = audtCensusList[intIndex].sngYearlyIncome;

		switch (intRace)
		{
		case 1:
			intCaucasian += 1;
			sngCaucasian += sngIncome;
			break;
		case 2:
			intAfricanAmerican += 1;
			sngAfricanAmerican += sngIncome;
			break;
		case 3:
			intHispanic += 1;
			sngHispanic += sngIncome;
			break;
		case 4:
			intAsian += 1;
			sngAsian += sngIncome;
			break;
		case 5:
			intOther += 1;
			sngOther += sngIncome;
			break;
		}
	}

	//Calculate the averages
	sngCaucasianAverage = sngCaucasian / intCaucasian;
	sngAfricanAmericanAverage = sngAfricanAmerican / intAfricanAmerican;
	sngHispanicAverage = sngHispanic / intHispanic;
	sngAsianAverage = sngAsian / intAsian;
	sngOtherAverage = sngOther / intOther;

	//give a space to the output
	printf("\n");

	//print a descriptor line
	printf("Average income by race: \n");

	FloatPrintByRace(sngCaucasianAverage, sngAfricanAmericanAverage, sngHispanicAverage, sngAsianAverage, sngOtherAverage);
}


// --------------------------------------------------------------------------------
// Name: FloatPrintByRace
// Abstract: Procedure to print by race
// --------------------------------------------------------------------------------
void FloatPrintByRace(float sngCaucasian, float sngAfricanAmerican, float sngHispanic, float sngAsian, float sngOther)
{
	printf("Caucasian: \t %.2f\n", sngCaucasian);
	printf("African American:%.2f\n", sngAfricanAmerican);
	printf("Hispanic: \t %.2f\n", sngHispanic);
	printf("Asian:\t\t %.2f\n", sngAsian);
	printf("Other:\t\t %.2f\n", sngOther);
	printf("\n");
}



// --------------------------------------------------------------------------------
// Name: PercentageBelowPoverty
// Abstract: Calculate the percentage below poverty
// --------------------------------------------------------------------------------
void CalculatePercentageBelowPoverty(udtCensusType audtCensusList[], int intInputCount)
{
	int intIndex = 0;
	
	//Holder Variables
	float sngIncome = 0;
	int intHouseholdSize = 0;

	int intPovertyCount = 0;
	float sngPercentInPoverty = 0;

	for (intIndex = 0; intIndex <= intInputCount; intIndex += 1)
	{
		intHouseholdSize = audtCensusList[intIndex].intNumberinHousehold;
		sngIncome = audtCensusList[intIndex].sngYearlyIncome;

		if (SeeIfInPoverty(sngIncome, intHouseholdSize) == 1)
		{
			intPovertyCount += 1;
		}
	}
	sngPercentInPoverty = ((float)intPovertyCount / (float)intInputCount) * (float)100;

	printf("Average percentage below poverty: \n");
	printf("\n");
	printf("%.2f%% of households are in poverty.\n", sngPercentInPoverty);
}



// --------------------------------------------------------------------------------
// Name: CalculateAverageIncomeByCounty
// Abstract: Collect and average each value by county
// --------------------------------------------------------------------------------
void CalculatePercentageBelowPovertyByCounty(udtCensusType audtCensusList[], int intInputCount)
{
	int intIndex = 0;
	int intFlag = 0;

	//Holder variables
	int intState = 0;
	int intCounty = 0;
	int intNumberInHousehold = 0;
	float sngIncome = 0;

	//Number in poverty variables
	int intOhio = 0;
	int intKentucky = 0;
	int intHamCounty = 0;
	int intButCounty = 0;
	int intBooCounty = 0;
	int intKentCounty = 0;

	//Total variables
	int intOhioP = 0;
	int intKentuckyP = 0;
	int intHamCountyP = 0;
	int intButCountyP = 0;
	int intBooCountyP = 0;
	int intKentCountyP = 0;

	//Percentages Variables
	float sngOhioPercentage = 0;
	float sngKentuckyPercentage = 0;
	float sngHamCountyPercentage = 0;
	float sngButCountyPercentage = 0;
	float sngBooCountyPercentage = 0;
	float sngKentCountyPercentage = 0;

	for (intIndex = 0; intIndex <= intInputCount; intIndex += 1)
	{
		intCounty = audtCensusList[intIndex].intCounty;

		intState = audtCensusList[intIndex].intState;

		sngIncome = audtCensusList[intIndex].sngYearlyIncome;

		intNumberInHousehold = audtCensusList[intIndex].intNumberinHousehold;

		//No  = 0
		//Yes = 1
		intFlag = SeeIfInPoverty(sngIncome, intNumberInHousehold);

		//Using that flag, sort the household in poverty into their respective county
		switch (intState)
		{
		case 1:
			if (intCounty == 1)
			{
				intOhio += 1;
				intHamCounty += 1;
				if (intFlag == 1)
				{
					intOhioP += 1;
					intHamCountyP += 1;
				}
				break;
			}
			else
			{
				intButCounty += 1;
				intOhio += 1;
				if (intFlag == 1)
				{
					intOhioP += 1;
					intButCountyP += 1;
				}
				break;
			}
		case 2:
			if (intCounty == 1)
			{
				intBooCounty += 1;
				intKentucky  += 1;
				if (intFlag == 1)
				{
					intBooCountyP += 1;
					intKentuckyP += 1;
				}
				break;
			}
			else
			{
				intKentCounty += 1;
				intKentucky += 1;
				if (intFlag == 1)
				{
					intKentCountyP += 1;
					intKentuckyP += 1;
				}
				break;
			}
			//Reset the flag
			intFlag = 0;
		}
	}
	//Calculate percentages
	sngOhioPercentage = ((float)intOhioP / intOhio) * 100;
	sngKentuckyPercentage = ((float)intKentuckyP / intKentucky) * 100;
	sngHamCountyPercentage = ((float)intHamCountyP / intHamCounty) * 100;
	sngButCountyPercentage = ((float)intButCountyP / intButCounty) * 100;
	sngBooCountyPercentage = ((float)intBooCountyP / intBooCounty) * 100;
	sngKentCountyPercentage = ((float)intKentCountyP / intKentCounty) * 100;

	//give a space to the output
	printf("\n");

	//print a descriptor line
	printf("Percentage Below Poverty By County: \n");

	FloatPrintPercentByStateAndCounty(sngOhioPercentage, sngHamCountyPercentage, sngButCountyPercentage, sngKentuckyPercentage, sngBooCountyPercentage, sngKentCountyPercentage);
}



// --------------------------------------------------------------------------------
// Name: SeeIfInPoverty
// Abstract: Function to determine if each household is inpoverished
// --------------------------------------------------------------------------------
int SeeIfInPoverty(float sngIncome, int intHouseholdSize)
{
	int intFlag = 0;
	

	if (intHouseholdSize == 1 && sngIncome < 12000)
	{
		intFlag = 1;
	}
	else if (intHouseholdSize == 2 && sngIncome < 18000)
	{
		intFlag = 1;
	}
	else if (intHouseholdSize == 3 && sngIncome < 25000)
	{
		intFlag = 1;
	}
	else if (intHouseholdSize == 4 && sngIncome < 30000)
	{
		intFlag = 1;
	}
	else if (intHouseholdSize >= 5 && sngIncome < 40000)
	{
		intFlag = 1;
	}

	return intFlag;
}



// --------------------------------------------------------------------------------
// Name: FloatPrintPercentByStateAndCounty
// Abstract: Procedure to print by state and county
// --------------------------------------------------------------------------------
void FloatPrintPercentByStateAndCounty(float sngOhio, float sngHamCounty, float sngButCounty, float sngKentucky, float sngBooCounty, float sngKentCounty)
{
	printf("Ohio:\t\t %.2f%%\n", sngOhio);
	printf("  Hamilton:\t %.2f%%\n", sngHamCounty);
	printf("  Butler:\t %.2f%%\n", sngButCounty);
	printf("Kentucky:\t %.2f%%\n", sngKentucky);
	printf("  Boone:\t %.2f%%\n", sngBooCounty);
	printf("  Kenton:\t %.2f%%\n", sngKentCounty);
	printf("\n");
}


// --------------------------------------------------------------------------------
// Name: CalculateAverageIncomeByRace
// Abstract: Calculate the total households by race
// --------------------------------------------------------------------------------
void CalculatePercentageBelowPovertyByRace(udtCensusType audtCensusList[], int intInputCount)
{
	int intIndex = 0;
	int intFlag = 0;

	//Holder values
	int intRace = 0;
	float sngIncome = 0;
	int intHouseholdSize = 0;
	//Tally values
	int intCaucasian = 0;
	int intAfricanAmerican = 0;
	int intHispanic = 0;
	int intAsian = 0;
	int intOther = 0;
	//Poverty Totals
	int intCaucasianP = 0;
	int intAfricanAmericanP = 0;
	int intHispanicP = 0;
	int intAsianP = 0;
	int intOtherP = 0;
	//Percentage variables
	float sngCaucasianPercentage = 0;
	float sngAfricanAmericanPercentage = 0;
	float sngHispanicPercentage = 0;
	float sngAsianPercentage = 0;
	float sngOtherPercentage = 0;

	for (intIndex = 0; intIndex <= intInputCount; intIndex += 1)
	{
		intRace = audtCensusList[intIndex].intRace;
		sngIncome = audtCensusList[intIndex].sngYearlyIncome;
		intHouseholdSize = audtCensusList[intIndex].intNumberinHousehold;

		//No  = 0
		//Yes = 1
		intFlag = SeeIfInPoverty(sngIncome, intHouseholdSize);

		switch (intRace)
		{
		case 1:
			intCaucasian += 1;
			if (intFlag == 1)
			{
				intCaucasianP += 1;
			}
			break;
		case 2:
			intAfricanAmerican += 1;
			if (intFlag == 1)
			{
				intAfricanAmericanP += 1;
			}
			break;
		case 3:
			intHispanic += 1;
			if (intFlag == 1)
			{
				intHispanicP += 1;
			}
			break;
		case 4:
			intAsian += 1;
			if (intFlag == 1)
			{
				intAsianP += 1;
			}
			break;
		case 5:
			intOther += 1;
			if (intFlag == 1)
			{
				intOtherP += 1;
			}
			break;
		}
	}

	//Calculate the percentages
	sngCaucasianPercentage = ((float)intCaucasianP / intCaucasian) * 100;
	sngAfricanAmericanPercentage = ((float)intAfricanAmericanP / intAfricanAmerican) * 100;
	sngHispanicPercentage = ((float)intHispanicP / intHispanic) * 100;
	sngAsianPercentage = ((float)intAsianP / intAsian) * 100;
	sngOtherPercentage = ((float)intOtherP / intOther) * 100;

	//give a space to the output
	printf("\n");

	//print a descriptor line
	printf("Percentage Below Poverty By Race: \n");

	FloatPrintPercentByRace(sngCaucasianPercentage, sngAfricanAmericanPercentage, sngHispanicPercentage, sngAsianPercentage, sngOtherPercentage);
}



// --------------------------------------------------------------------------------
// Name: FloatPrintPercentByRace
// Abstract: Procedure to print by race
// --------------------------------------------------------------------------------
void FloatPrintPercentByRace(float sngCaucasianPercentage, float sngAfricanAmericanPercentage, float sngHispanicPercentage, float sngAsianPercentage, float sngOtherPercentage)
{
	printf("Caucasian: \t %.2f%%\n", sngCaucasianPercentage);
	printf("African American:%.2f%%\n", sngAfricanAmericanPercentage);
	printf("Hispanic: \t %.2f%%\n", sngHispanicPercentage);
	printf("Asian:\t\t %.2f%%\n", sngAsianPercentage);
	printf("Other:\t\t %.2f%%\n", sngOtherPercentage);
	printf("\n");
}