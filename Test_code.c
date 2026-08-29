#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/* Name/ID: James Kilbane - A00023043
Date 02/04/2026 - 12/04/2026
Program Description: Smart Warehouse monitoring system */

#define SIZEOFDATA 9
struct time //Structure for the time stamp
{
    int hour; 
    int minute;
    int second;
};

struct inbound_data  //structure for the record (inbound data)
{
    int container_id;
    struct time TIMESTAMP;
    int weight;
    int product_code;
    int temperature;
    int courier_ID;
};
//Function declarations
void filled_in_data_randomely(struct inbound_data stores_data[], int function_number);
void printing_unsorted_data(struct inbound_data data);
void printing_unsorted_data_2(struct inbound_data array[], int size);
void merge(struct inbound_data arr[], int left, int mid, int right);
void merge_sort(struct inbound_data arr[], int left, int right);
int compare_times(struct time value1, struct time value2);
void printed_sorted_data(struct inbound_data data);
void printed_sorted_data_2(struct inbound_data array[], int size);
void merge_1_and_2(struct inbound_data arr1[], struct inbound_data arr2[], struct inbound_data final[], int NUM, int MUM, int *final_NUM);
void merge_all_teams (struct inbound_data team1[],struct inbound_data team2[], struct inbound_data team3[], struct inbound_data team4[], struct inbound_data final[], int team_size1, int team_size2, int team_size3, int team_size4, int *final_size);
int binary (struct inbound_data array[], int left, int right, struct time N );
void container_count(struct inbound_data array[], int size);

int main()
{
    srand(time(NULL)); //inatlising the random number generator

    //Declaring arrays for each team
    struct inbound_data team1[SIZEOFDATA];
    struct inbound_data team2[SIZEOFDATA];
    struct inbound_data team3[SIZEOFDATA];
    struct inbound_data team4[SIZEOFDATA];
    struct inbound_data temp[SIZEOFDATA *2]; //declaring temporary for merging team1 and team2 data
    struct inbound_data full_sorted_data[SIZEOFDATA * 4]; //declaring dispatch list with all teams merged
    struct time N; //varibale to store user input for binary search
    
    //initilsing team sizes.
    int temp_size; //size of temp array
    int team1_size = SIZEOFDATA;
    int team2_size = SIZEOFDATA;
    int team3_size = SIZEOFDATA;
    int team4_size  = SIZEOFDATA;
    int final_size = SIZEOFDATA * 4; //Final array 4 times the size of defined size

    //calling each team with randomly generated data
    filled_in_data_randomely(team1, team1_size);
    filled_in_data_randomely(team2, team2_size);
    filled_in_data_randomely(team3, team3_size);
    filled_in_data_randomely(team4, team4_size);

    //printing all teams unsorted data seperatly
    printf("----------------------UNSORTED DATA -----------------------\n");
    printf("\nTeam 1 Data\n");
    printing_unsorted_data_2(team1, team1_size);

    printf("\nTeam 2 Data\n");
    printing_unsorted_data_2(team2, team2_size);

    printf("\nTeam 3 Data\n");
    printing_unsorted_data_2(team3, team3_size);

    printf("\nTeam 4 Data\n");
    printing_unsorted_data_2(team4, team4_size);
//////////////////////////////////////////////////////////////////////
   
    //sorting each team using the merge sort 
    merge_sort(team1, 0, team1_size - 1); 
    merge_sort(team2, 0, team2_size - 1); //teamNo is the array, 0 is the starting index, teamNo_size - 1 is the last index.
    merge_sort(team3, 0, team3_size - 1);
    merge_sort(team4, 0, team4_size - 1);

    //printing all teams sorted data seperatly
    printf("---------------------SORTED DATA----------------------------\n");
    printf("\nTeam 1 Sorted Data\n");
    printed_sorted_data_2(team1, team1_size);

    printf("\nTeam 2 Sorted Data\n");
    printed_sorted_data_2(team2, team2_size);

    printf("\nTeam 3 Sorted Data\n");
    printed_sorted_data_2(team3, team3_size);

    printf("\nTeam 4 Sorted Data\n");
    printed_sorted_data_2(team4, team4_size);

    //calling team1 and team2 merged data
    merge_1_and_2(team1, team2, temp, team1_size, team2_size, &temp_size);
    printf("\n--------------Merged Team1 and Team2------------\n");
    printed_sorted_data_2(temp, temp_size); // printing merged team1 and team2 sorted data by printing the temp array and size

    //calling all teams merged data into one final dispatch list
    merge_all_teams(team1, team2, team3, team4, full_sorted_data, team1_size, team2_size, team3_size, team4_size, &final_size);

    printf("\n-------------------------FULL FINAL DISPATCH LIST-------------------------------\n");
    printed_sorted_data_2(full_sorted_data, final_size); //printing dispatch list

    printf("\nEnter a time (HH:MM:SS): "); //Providing a user interface for users to search a product proccessed at a certain time
    scanf("%d:%d:%d", &N.hour, &N.minute, &N.second);

    int target = binary(full_sorted_data, 0, final_size - 1, N); //calling the binary search function and storing the result
    
    //searching for value N in full_sorted_data array and stores its index.
    if (target != -1)
    {
        printed_sorted_data(full_sorted_data[target]);
    }
    else{
        printf("\nProduct Was not processed at this time\n ");
    }

    //calling and displaying container report
    container_count(full_sorted_data, final_size);
    

    return 0;
}

void filled_in_data_randomely(struct inbound_data stores_data[], int function_number) //Function to assign random generated data between a speicifc range to each piece of data in the record
{
    int i;

    for (i = 0; i < function_number; i++) //Go's through each postion in array and assign each label random data.
    {
       stores_data[i].container_id = (rand() % 25) + 1; //Gives container ID random data from 1 to 25
       stores_data[i].TIMESTAMP.hour = 8 + rand() % 9; //Gives hour random data between 8-17
       stores_data[i].TIMESTAMP.minute = rand() % 60; //Gives mintue random data between 0-59
       stores_data[i].TIMESTAMP.second = rand() % 60; //gives second random data between 0-59
       stores_data[i].weight = rand() %500; //gives weight random data from 0-499
       stores_data[i].product_code = rand() % 9999; //gives product code random data from 0-9998
       stores_data[i].temperature = rand() % 37; //gives temperature random data from 0-36
       stores_data[i].courier_ID = (rand() % 4) + 1; //gives courier id random data from 1-4
    }
}

void printing_unsorted_data(struct inbound_data data) //Function to print teams heading and one record for its unsorted data
{
        printf("Container ID: %d", data.container_id); //printing the container id of the current record
            printf("\n"); //printing a newline after every heading
        printf("Time HH:MM:SS: %02d:%02d:%02d\n", data.TIMESTAMP.hour, data.TIMESTAMP.minute, data.TIMESTAMP.second);
        printf("Weight: %d", data.weight);
            printf("\n");
        printf("Product Code: %d", data.product_code);
            printf("\n");
        printf("Temp: %d", data.temperature);
            printf("\n");
        printf("Courier ID: %d", data.courier_ID);
            printf("\n");

}

void printing_unsorted_data_2(struct inbound_data array[], int size) //Function prints multiple record by using calling the single print function
{
    int i;

    for (i = 0; i < size; i++) //loop goes through each element in array which is the list of records.
    {
        //calling the single print function for element
        printing_unsorted_data(array[i]); //array stores each teams data, 
    }
}

int compare_times(struct time value1, struct time value2) //This function compares two timestamp and checks to see which one comes before or after the other on.
{
    //compares hours
    if (value1.hour != value2.hour) 
    {   
        return value1.hour - value2.hour; //return the difference if two values are not equal
    }                                     // A postivie result will mean value1 is later, and vice versa

    //compares minutes
    else if (value1.minute != value2.minute) //A repeat of hours
    {
        return value1.minute - value2.minute;
    }
    //compares seconds
    else
    {
        return value1.second - value2.second;
    }
}

void merge(struct inbound_data arr[], int left, int mid, int right) //This function takes two arrays and merges them into one sorted section of the array based on its timestamp. 
{
    //loop counters used for left,right, and merged array
    int i,j,k;
    
    //size of left array
    int n1 = mid - left + 1;

    //size of right array
    int n2 = right - mid;

    struct inbound_data temp_left_array[n1], temp_right_array[n2]; // temp arrays for storing split data before actually merging

    for ( i = 0; i < n1; i++)
    {
        temp_left_array[i] = arr[left + i]; //copy left half of main array into temp left array
    }

    for (j = 0; j < n2; j++)
    {
        temp_right_array[j] = arr[mid + 1 + j]; //copy right half of main array into temp right array
    }

    //resarts i,j,k
    i = 0; //left array
    j = 0; //right array
    k = left; //merged postion.

    while (i < n1 && j < n2)
    {
        //uses compare_times function to ensure they stay in sorted order
        if (compare_times(temp_left_array[i].TIMESTAMP, temp_right_array[j].TIMESTAMP) <= 0)
        {
            arr[k] = temp_left_array[i]; //gets elements in left array if time is equal.
            i++;
        }
        else{
            arr[k] = temp_right_array[j]; // gets element from right array
            j++;
        }
        k++; //moves to next position
    }

    while ( i < n1)
    {
        arr[k] = temp_left_array[i]; //Copies rest of the element from left array
        i++;
        k++;
    }

    while ( j < n2)
    {
        arr[k] = temp_right_array[j]; //copies rest of the element from right array
        j++;
        k++;
    }
}

void merge_sort(struct inbound_data arr[], int left, int right) //This function splits the two arrays into small parts,sorts each part and them merges them together.
{
    if (left < right) //
    {
        int mid = left + (right - left) / 2; //Fidning the middle point

        merge_sort(arr, left, mid); //sorts left half
        merge_sort(arr, mid + 1, right); //sorts right half

        merge(arr, left, mid, right); //then merges sorted halves together
    }
}

void printed_sorted_data(struct inbound_data data) //Function prints sorted data
{
    printf("Container ID: %d", data.container_id);
            printf("\n");
        printf("Time HH:MM:SS: %02d:%02d:%02d\n", data.TIMESTAMP.hour, data.TIMESTAMP.minute, data.TIMESTAMP.second);
        printf("Weight: %d", data.weight);
            printf("\n");
        printf("Product Code: %d", data.product_code);
            printf("\n");
        printf("Temp: %d", data.temperature);
            printf("\n");
        printf("Courier ID: %d", data.courier_ID);
            printf("\n");
}

void printed_sorted_data_2(struct inbound_data array[], int size)
{
    int i;

    for ( i = 0; i < size; i++)
    {
        printed_sorted_data(array[i]);
    }
}

void merge_1_and_2(struct inbound_data arr1[], struct inbound_data arr2[], struct inbound_data final[], int NUM, int MUM, int *final_NUM) //function merges team1 and team2 sorted data into one array.
{
    //Use malloc to dynamically allocate memory to temporarily store merged results
    struct inbound_data *merged = malloc((NUM + MUM) * sizeof(struct inbound_data));

    int i = 0, j = 0, k = 0; //I = index for arr1, j = index for arr2, k = index for merged array

    while (i < NUM && j < MUM)
    {
        //using compare time function to compare timestamps from both arrays to make sure they are still sorted 
        if (compare_times(arr1[i].TIMESTAMP, arr2[j].TIMESTAMP) <=0)
        {
            merged[k++] = arr1[i++]; //takes element from arr1 if time is equal
        }
        else{
            merged[k++] = arr2[j++]; //takes element from arr2 if time is equal
        }
    }

    while (i < NUM) 
    {
        merged[k++] = arr1[i++]; //copies any remaining element from arr1
    }

    while ( j < MUM)
    {
        merged[k++] = arr2[j++]; //copies any remaining element from arr2
    }

    for (i = 0; i < k; i++)
    {
        final[i] = merged[i]; //copies merged result into a final output array
    }

    *final_NUM = k; //stores size of final output array

    free(merged);
}

void merge_all_teams (struct inbound_data team1[],struct inbound_data team2[], struct inbound_data team3[], struct inbound_data team4[], struct inbound_data final[], int team_size1, int team_size2, int team_size3, int team_size4, int *final_size)
//merges all four team into a dispatch list
{
    //temporary arrays to store merged result of teams
    struct inbound_data *merged1 = malloc((team_size1 + team_size2 + team_size3 + team_size4) * sizeof(struct inbound_data));
    struct inbound_data *merged2 = malloc((team_size1 + team_size2 + team_size3 + team_size4) * sizeof(struct inbound_data));

    int A, B; //A = size of merged 1, B = size of merged 2

    //merges team1 and team2 into merged one
    merge_1_and_2(team1, team2, merged1, team_size1, team_size2, &A);
    //merges team3 and team4 into merged 2
    merge_1_and_2(team3, team4, merged2, team_size3, team_size4, &B);
    //merges both temporary arrays into final dispatch list
    merge_1_and_2(merged1, merged2, final, A, B, final_size);

    free(merged1);
    free(merged2);

}

int binary (struct inbound_data array[], int left, int right, struct time N ) //Function uses binary search to take input and search for the earliest occurence in that eneterd time.
{
    int index = -1; //stores earliest occurence
    while (left <= right)
    {
        int mid = left + (right - left)/2; //calculates middle index

        int answer = compare_times(array[mid].TIMESTAMP, N); //compares middle timestamp with the enterd time

        if (answer == 0)
        {
            index = mid; //if found store index
            right = mid - 1; //will keep looking in the left side
        }
        else if (answer < 0)
        {
            left = mid + 1; //means mid time is earlier then answer, keep looking in the right half
        }
        else
        {
            right = mid - 1;//mid is later then asnwer, search lef half
        }
    }
    return index; 
}

void container_count(struct inbound_data array[], int size)
{
    int count[26] = {0}; //this array stores the amount of times a container ID is displayed
    int i;

    for (i = 0; i < size; i++)
    {
        count[array[i].container_id]++;
        //increment the count for the container ID in each record
    }

    for (i = 0; i < 26; i ++)//loops through all possible container IDs
    {
        if (count[i] > 0)
        {
            printf("Container_id: %d has %d product in it\n", i, count[i]);
        }
    }
}

