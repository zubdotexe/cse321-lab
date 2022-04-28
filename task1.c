# include <stdio.h>
# include <time.h>

int main()
{
    int n = 5, m = 4; // Number of processes and number of resources respectively

    int alloc[5][4] = {
        {0, 1, 0, 3}, 
        {2, 0, 0, 0}, 
        {3, 0, 2, 0}, 
        {2, 1, 1, 5}, 
        {0, 0, 2, 2}
    };

    int max[5][4] = {
        {6, 4, 3, 4}, 
        {3, 2, 2, 1}, 
        {9, 1, 2, 6}, 
        {2, 2, 2, 8}, 
        {4, 3, 3, 7}
    };

    int available[4] = {3, 3, 2, 1};
    int need[5][4];

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++) 
        {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }

    int finish[5] = {0, 0, 0, 0, 0};

    int count = 0;
    time_t start, end;
    start = clock();

    while(count < n)
    {
        for(int i = 0; i < n; i++)
        {
            if(finish[i] != 1) // checking if a proc has been finished 
            {   
                int lessThanAvail = 0;

                /* 
                this for loop on line 62 and the if statement on line 70 together check if need <= avail 
                
                for loop for seeing the relationship ('>' or '<' etc) between all the indices of need and all the indices of avail 
                and we are storing the info in lessThanAvail var

                if statement is for checking if each of the indices of need is less than each of the indices of avail by 
                using lessThanAvail var which will be equal to m if all of need indices are less than avail's
                and if the condition is true we turn the process in finish array to 'True' 
                and we increase the avail array by the amount of need[i][j] array 
                and we increase the count var by 1
                */

                for(int j = 0; j < m; j++) 
                {
                    if(need[i][j] <= available[j])
                    {
                        lessThanAvail += 1;
                    }
                }

                if(lessThanAvail == m)
                {
                    for(int j = 0; j < m; j++)
                    {
                        available[j] += alloc[i][j];
                    }
                    finish[i] = 1;
                    count += 1;
                }
            }
        }

        /*
        this end is amount of clocks since the program has started executing
        if there is a deadlock the while loop won't stop running. To prevent that from happening we are limiting the 
        amount of time this program will run
        */

        end = clock();
        if(end >= 100){ // ekhane end - start >= 50 dibo
            break;
        }
    }

    if(count == n)
    {
        printf("Safe here\n");
    }
    else
    {
        printf("Deadlock ahead");
    }
    return 0;
}