/**
 * Name: Jacob Cochran
 * Date: 4/25/26
 * Assignment: Sorting Algorithms in C++
 */

 #include <iostream>
 #include <cstdlib>
 #include <ctime>
 #include <fstream>
 #include <vector>
 #include <string>

void printMenu();
void randSeed();
void insertionSort();
void countingSort();

const int MAXNUMBERS = 10000;

int main()
{
    int select;
    printMenu();
    std::cin >> select;
    while(select != '0')
    {
        if(select == 1)
        {
            randSeed();
        }
        else if(select == 2)
        {
            insertionSort();
        }
        else if(select == 3)
        {
            countingSort();
        }
        else if (select == 9)
        {
            printMenu();
        }
        else if(select == 0){break;}
        else
        {
            std::cerr << "\nIncorrect option. Please try again.\n";
        }
        std::cout << "Please make another selection.\n";
        std::cin >> select;
    }
    return 0;
}

void printMenu()
{
    std::cout << "\nWelcome to the Sorting Algorithms Test!\n";
    std::cout << "Please chose one of the following options: \n";
    std::cout << "_______________________________________________\n";
    std::cout << "   1: Seed data.txt (If data.txt does not exist, a new one will be created.)\n";
    std::cout << "   2: Run Insertion Sort\n";
    std::cout << "   3: Run Counting Sort\n";
    std::cout << "   9: View the Menu\n";
    std::cout << "   0: Close program\n";
}

void randSeed()
{
    std::ofstream ofile("data.txt", std::ios::out | std::ios::trunc);
    srand(time(0));
    if(ofile.is_open())
    {
        for(int i = 0; i < MAXNUMBERS; i++)
        {
            int n = rand() % 1000;
            ofile << n << "\n";
        }
        std::cout << "The file data.txt has been seeded.\n";
        ofile.close();
        return;
    }
    else{std::cerr << "Failed to open file.\n"; return;}
}

void insertionSort()
{
    std::ifstream ifile("data.txt"); //loading up vector of ints
    if(!ifile.is_open()) {std::cerr << "Failed to open file.\n"; return;}
    std::vector<int> nums;
    std::string temp;
    int t;
    for(int i = 0; i < MAXNUMBERS; i++)
    {
        getline(ifile, temp);
        t = stoi(temp); //string to int
        nums.push_back(t);
    }
    ifile.close();
    std::cout << "File loaded. Starting Insertion Sort.\n";

    int i, j, key;
    clock_t before = clock();
    for(i = 1; i < MAXNUMBERS; i++) //insertion sort
    {
        key = nums.at(i);
        j = i - 1;
        while (j >= 0 && nums.at(j) > key)
        {
            nums.at(j + 1) = nums.at(j);
            j = j - 1;
        }
        nums.at(j + 1) = key;
    }
    clock_t duration = clock() - before;
    double time = (float)duration / CLOCKS_PER_SEC;
    std::cout << "Sort finished. Printing results.\n";

    std::ofstream ofile("result_insertion.txt", std::ios::out | std::ios::trunc); //outputting results
    if(ofile.is_open())
    {
        for(int i = 0; i < MAXNUMBERS; i++)
        {
            ofile << nums.at(i) << "\n";
        }
        ofile << "This sort took " << time << " seconds.\n";
        std::cout << "The file result_insertion.txt has been created.\n";
        return;
    }
    else{std::cerr << "Failed to open file.\n"; return;}
    ofile.close();
}

void countingSort()
{
    std::ifstream ifile("data.txt"); //loading up vector of ints
    if(!ifile.is_open()) {std::cerr << "Failed to open file.\n"; return;}
    std::vector<int> nums;
    std::string temp;
    int t;
    for(int i = 0; i < MAXNUMBERS; i++)
    {
        getline(ifile, temp);
        t = stoi(temp); //string to int
        nums.push_back(t);
    }
    ifile.close();
    std::cout << "File loaded. Starting Counting Sort.\n";

    //counting sort start
    clock_t before = clock();
    int max = nums.at(0); //finding max number
    for(int i = 1; i < MAXNUMBERS; i++)
    {
        if(nums.at(i) > max){max = nums.at(i);}
    }

    std::vector<int> count(max + 1); //creating count vector and counting distinct elements
    for(int i = 0; i < max + 1; i++){count.at(i) = 0;}
    for(int i = 0; i < MAXNUMBERS; i++)
    {
        count.at(nums.at(i))++;
    }

    for(int i = 1; i <= max; i++) //prefix sum and updating vector
    {
        count.at(i) = count.at(i) + count.at(i - 1);
    }

    std::vector<int> output(MAXNUMBERS); //storing sorted vector
    for(int i = MAXNUMBERS - 1; i >= 0; i--)
    {
        output.at(--count.at(nums.at(i))) = nums.at(i);
    }
    //end of counting sort
    clock_t duration = before - clock();
    double time = (float)duration / CLOCKS_PER_SEC;
    std::cout << "Sort finished. Printing results.\n";

    std::ofstream ofile("result_counting.txt", std::ios::out | std::ios::trunc); //outputting results
    if(ofile.is_open())
    {
        for(int i = 0; i < MAXNUMBERS; i++)
        {
            ofile << output.at(i) << "\n";
        }
        ofile << "This sort took " << time << " seconds.\n";
        std::cout << "The file result_counting.txt has been created.\n";
        return;
    }
    else{std::cerr << "Failed to open file.\n"; return;}
    ofile.close();
}