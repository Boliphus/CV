#include <iostream>
#include <ctime>
using namespace std;

/* -------------------------------------------------------------- */
/* This part serves as a pseudo random number generator for auto grade purpose only */
/* You are suggested not to refer to these codes in this assignment. */
/* You are not allowed to use global variables in this course. */
unsigned int next_num = 1; // Here we initiate an unsigned integer to be used in the following functions.

unsigned int pa1_rand() // This function is used to return a pseudo random number from 0 to 32767.
{
    next_num = next_num * 1103515245 + 2011;
    return static_cast<unsigned int>(next_num / 65536) % 32768;
}
void pa1_srand(unsigned int seed) // This function is used to set a seed of the pseudo random number generator.
{
    next_num = seed;
}
/* Everytime you call pa1_rand(), you will get a new pseudo random number. For the same seed, the sequence of pseudo 
   random number is fixed. For example, when seed = 3, the sequence of pseudo random number is fixed to be [17746, 
   30897, 9622, 18921, 4034, 17510, 24152, 14388, 23665, 31532, ...]. When seed = 5, the sequence of pseudo random 
   number is fixed to be [18655, 32247, 9873, 9718, 26373, 27678, 5314, 22512, 31845, 22885, ...] */
/* -------------------------------------------------------------- */



const int MAX_BOXES = 1000; // This constant stores the largest length of boxes[]. You can use it in your code.

// This function is used to fill the 1D array with a random sequence of unique numbers from 1 to the user input for the number of prisoners
void placeSlips(int boxes[], int num_prisoners)
{
    for (int i = 0; i < num_prisoners; i++)
        boxes[i] = -1;
    int counter = 0;
    while (counter < num_prisoners)
    {
        int num = pa1_rand() % (num_prisoners);
        if (boxes[num] == -1)
        {
            boxes[num] = counter;
            counter++;
        }
    }
}

// TASK 1: Simulate an actual riddle room
bool simulateRoom(const int boxes[], int num_prisoners, int num_trials)
{
int count[num_prisoners]={};
    int longest=0;
    int remain=num_prisoners;
    int alive=num_prisoners;
    int counting_now=0;
    int compare=0;
    int total=0;
    int total_loop[num_prisoners]={};
    for(int c=0;c<num_prisoners;c++){
        total_loop[c]=c;
    }
    int longest_sequence[num_prisoners]={};
    int temp[num_prisoners]={};
    int shortest=num_prisoners;
    for(int i=0;i<num_prisoners;i++){
        
        int nextbox=i;
        //cout<<"current prisoner"<<" "<<nextbox+1<<endl;
        for(int j=0;j<num_prisoners;j++){
            if(boxes[nextbox]==i){
                temp[j]=nextbox;
                //cout<<"found it"<<endl;
                count[i]=j+1;
                break;
                }
            else{
                //cout<<"not found"<<endl;
                temp[j]=nextbox;
                nextbox=boxes[nextbox];
                //cout<<"next box is "<<nextbox<<endl;
                
            }
        

        }
        if(count[i]>longest){
            longest=count[i];
            for(int h=0;h<longest;h++){
                longest_sequence[h]=temp[h];
            }

        }
        if(count[i]<shortest){
            shortest=count[i];
        }
        if(count[i]>num_trials&&counting_now!=count[i]){
            counting_now=count[i];
            alive-=counting_now;
        }
        for(int s=0;s<count[i];s++){
            if(total_loop[temp[s]]!=-1){
                total_loop[temp[s]]=-1;
                if(s==count[i]-1){
                    total+=1;
                }
            }
        }

    }
    if(longest>num_trials){
        return 0;
    }
    else{
        return 1;
    }
}

// TASK 2: Display certain statistics for a given room
void statsRoom(const int boxes[], int num_prisoners, int num_trials)
{   int count[num_prisoners]={};
    int longest=0;
    int remain=num_prisoners;
    int alive=num_prisoners;
    int counting_now=0;
    int compare=0;
    int total=0;
    int total_loop[num_prisoners]={};
    for(int c=0;c<num_prisoners;c++){
        total_loop[c]=c;
    }
    int longest_sequence[num_prisoners]={};
    int temp[num_prisoners]={};
    int shortest=num_prisoners;
    for(int i=0;i<num_prisoners;i++){
        
        int nextbox=i;
        //cout<<"current prisoner"<<" "<<nextbox+1<<endl;
        for(int j=0;j<num_prisoners;j++){
            if(boxes[nextbox]==i){
                temp[j]=nextbox;
                //cout<<"found it"<<endl;
                count[i]=j+1;
                break;
                }
            else{
                //cout<<"not found"<<endl;
                temp[j]=nextbox;
                nextbox=boxes[nextbox];
                //cout<<"next box is "<<nextbox<<endl;
                
            }
        

        }
        if(count[i]>longest){
            longest=count[i];
            for(int h=0;h<longest;h++){
                longest_sequence[h]=temp[h];
            }

        }
        if(count[i]<shortest){
            shortest=count[i];
        }
        if(count[i]>num_trials&&counting_now!=count[i]){
            counting_now=count[i];
            alive-=counting_now;
        }
        for(int s=0;s<count[i];s++){
            if(total_loop[temp[s]]!=-1){
                total_loop[temp[s]]=-1;
                if(s==count[i]-1){
                    total+=1;
                }
            }
        }
        









    }
    cout << "The number of prisoners who find their slips: " << alive /* Please replace this to your own code */ << endl;
    cout << "Number of loops: " << total /* Please replace this to your own code */ << endl;
    cout << "Smallest loop length: " << shortest /* Please replace this to your own code */ << endl;
    cout << "Longest loop length: "<<longest << endl;
    cout << "Largest loop: ";
    for(int r=0;r<longest;r++){
        cout<<longest_sequence[r]<<" ";
    }

    /* Please replace this to your own code */

    cout << endl;
}

// TASK 3: Find the number of instances in 1000 rooms when the prisoners will all be able to escape
double successRooms(int boxes[], int num_prisoners, int num_trials) //  suceess rate of 1000 rooms basically repeating it a 1000 times
{   //bool result[1000]={false};
    double survive=0;
    /* Please replace this to your own code below */
    for(int i=0;i<1000;i++){
        placeSlips(boxes,num_prisoners);
        
        if(simulateRoom(boxes,num_prisoners,num_trials)){
            survive+=1;
        }
    }
    return survive;
}

// TASK 4: Nice guard will help the prisoners to successfully leave the room by breaking any loop which is greater than the number of trials
//         Return true if the intervention was applied, else return false
bool niceGuard(int boxes[], int num_prisoners, int num_trials)
{
    /* Please replace this to your own code below */
    int count[num_prisoners]={};
    int longest=0;
    int remain=num_prisoners;
    int alive=num_prisoners;
    int counting_now=0;
    int compare=0;
    int total=0;
    int total_loop[num_prisoners]={};
    for(int c=0;c<num_prisoners;c++){
        total_loop[c]=c;
    }
    int longest_sequence[num_prisoners]={};
    int temp[num_prisoners]={};
    int shortest=num_prisoners;
    for(int i=0;i<num_prisoners;i++){
        
        int nextbox=i;
        //cout<<"current prisoner"<<" "<<nextbox+1<<endl;
        for(int j=0;j<num_prisoners;j++){
            if(boxes[nextbox]==i){
                temp[j]=nextbox;
                //cout<<"found it"<<endl;
                count[i]=j+1;
                break;
                }
            else{
                //cout<<"not found"<<endl;
                temp[j]=nextbox;
                nextbox=boxes[nextbox];
                //cout<<"next box is "<<nextbox<<endl;
                
            }
        

        }
        if(count[i]>longest){
            longest=count[i];
            for(int h=0;h<longest;h++){
                longest_sequence[h]=temp[h];
            }

        }
        if(count[i]<shortest){
            shortest=count[i];
        }
        if(count[i]>num_trials&&counting_now!=count[i]){
            counting_now=count[i];
            alive-=counting_now;
        }
        for(int s=0;s<count[i];s++){
            if(total_loop[temp[s]]!=-1){
                total_loop[temp[s]]=-1;
                if(s==count[i]-1){
                    total+=1;
                }
            }
        }

    }
    int replace=0;
    int swap1,swap2=0;   
    if(longest>num_trials){
        swap1=longest_sequence[(longest/2)-1];
        swap2=longest_sequence[(longest/2)];
        boxes[swap1]=boxes[longest_sequence[0]];
        boxes[swap2]=boxes[longest_sequence[longest-1]];
        return 1;
    }
    else{
        return false;
    }
    
}

// DO NOT WRITE ANYTHING AFTER THIS LINE. ANYTHING AFTER THIS LINE WILL BE REPLACED.

int main()
{

    int num_prisoners, num_trials, seed;
    // set boxes, priosoners

    cout << "Enter the number of prisoners (from 1 to 1000) :" << endl;
    cin >> num_prisoners;
    cout << "Enter the number of boxes each prisoner can open (from 1 to 1000) :" << endl;
    cin >> num_trials;
    cout << "Enter the seed for randomization else enter 0 and the system will randomize for you :" << endl;
    cin >> seed;

    if (seed == 0)
    {
        pa1_srand(time(NULL));
    }
    else
    {
        pa1_srand(seed);
    }

    int boxes[MAX_BOXES]; // array for the boxes
    for (int i = 0; i < MAX_BOXES; i++)
        boxes[i] = 0;

    int choice;
    cout << "Please choose an option:" << endl;
    cout << "0.Print the boxes" << endl;
    cout << "1.Simulate a room" << endl;
    cout << "2.Compute statistics of a room:" << endl;
    cout << "3.Compute success rate over 1000 rooms" << endl;
    cout << "4.Apply nice guard intervention in a room" << endl;
    cin >> choice;

    switch (choice)
    {
    case 0:
        placeSlips(boxes, num_prisoners);
        for (int i = 0; i < num_prisoners; i++)
            cout << boxes[i] << " ";
        cout << endl;
        break;
    case 1:
        placeSlips(boxes, num_prisoners);
        if (simulateRoom(boxes, num_prisoners, num_trials) == true)
        {
            cout << "Success! All prisoners found their slip." << endl;
        }
        else
        {
            cout << "Failure! Not all prisoners were able to find their slip." << endl;
        }
        break;
    case 2:
        placeSlips(boxes, num_prisoners);
        statsRoom(boxes, num_prisoners, num_trials);
        break;
    case 3:
    {

        double prisoners_left = successRooms(boxes, num_prisoners, num_trials);
        cout << "All prisoners were able to leave " << prisoners_left << "/1000 of the rooms." << endl;
    }
    break;
    case 4:
    {
        placeSlips(boxes, num_prisoners);
        int copy_arr[MAX_BOXES];
        for (int i = 0; i < num_prisoners; i++)
        {
            copy_arr[i] = boxes[i]; // copying the array for checking if no more than 2 swaps are made
        }

        bool nice_guard_val = niceGuard(boxes, num_prisoners, num_trials);

        int swap_count = 0;
        for (int j = 0; j < num_prisoners; j++)
        {
            if (copy_arr[j] != boxes[j])
            {
                swap_count++;
            }
        }
        if (swap_count > 2)
        {
            cout << "Illegal intervention as you have more than 1 swap " << endl;
        }
        else
        {
            if (nice_guard_val == false)
                cout << "No intervention needed." << endl;
            else
            {
                cout << "Intervention applied." << endl;
                // validity function
                bool prisoners_left = simulateRoom(boxes, num_prisoners, num_trials);
                // should return true
                if (prisoners_left == true)
                    cout << "All the prisoners were able to escape" << endl;
                else
                {
                    cout << "All the prisoners were not able to escape" << endl;
                }
            }
        }
    }
    break;
    }

    return 0;
}