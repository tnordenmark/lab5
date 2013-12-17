// lab5_upg2.cpp
// Program för att utföra binärsökning på en array
// Thomas Nordenmark 2013-12-12
// Ver 0.1
//------------------------------------------------------------------------------
#include <random> // default_random_engine
#include <functional> // bind
#include <iostream> // cin, cout
using namespace std;

// ======================
// Funktionsdeklarationer
// ======================
void bubbleSort(int arr[], int max); // Bubble sort
int binSearch(int arr[], int key, int max);

// ============
// Huvudprogram
// ============
int main()
{
    int max; // Arraystorlek
    int range; // Maxtalet för slumpgeneratorn

    // Fråga efter och läs in arrayens storlek och maxtalet för slumpgeneratorn
    cout << "Mata in önskad arraystorlek: ";
    cin >> max;
    cout << "Mata in maxtalet för slumpgeneratorn: ";
    cin >> range;

    // Initiera slumpdistributörsobjektet generator
    default_random_engine generator(static_cast<unsigned>(time(0)));
    uniform_int_distribution<int> random(1, range); // Slumpa i itervallet 1-6
    // Slå ihop slumpgeneratorn till en funktion för enklare användning
    auto slumpaTal = bind(random, generator);

    int arr[max]; // Arrayen
    int i; // Iterator för loopar
    int key; // Det eftersökta talet
    int index; // Det eftersökta talets plats i arrayen

    cout << endl << "Arrayen osorterad:" << endl;
    for(i = 0; i < max; i++)
    {
        arr[i] = slumpaTal();
        cout << "a[" << i <<"] = " << arr[i] << endl;
    }


    // Sortera arrayen, en förutsättning för binärsökning
    bubbleSort(arr, max);


    // Skriv ut arrayen efter sortering
    cout << endl << "Arrayen sorterad i stigande ordning:" << endl;

    for(i = 0; i < max; i++)
    {
        cout << "a[" << i <<"] = " << arr[i] << endl;
    }


    // Fråga efter och läs in nummer att söka efter
    cout << endl << "Mata in ett nummer att söka efter mellan 1 och " << range << ": ";
    cin >> key;

    // Anropa binärsökningsfunktionen med array, sökord och storlek som parametrar
    index = binSearch(arr, key, max);


    // Presentera resultatet av binärsökningen
    if(index != -1)
        cout << "Det eftersökta numret finns på index: " << index << endl;
    else
        cout << "Det eftersökta numret hittades inte." << endl;


    return 0;
}


// =====================
// Funktionsdefinitioner
// =====================

// Bubble sort
void bubbleSort(int arr[], int max)
{
    int i, j; // Iteratorer för looparna
    int temp; // Temporär lagringsplats för sortering

    // Yttre loop
    for(i = 0; i < max; i++)
    {
        // Inre loop
        for(j = 0; j < max - 1; j++)
        {
            if(arr[j] > arr[j + 1])
            {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Binär sökning
int binSearch(int arr[], int key, int max)
{
    int low = 0;
    int high = max - 1;
    int middle;

    while(low <= high)
    {
        middle = low + (high - low)/2; // Hitta arrayens mittenvärde

        // Om det eftersöka numret är högre än mittenvärdet, sök i den högre halvan
        if(key > arr[middle])
            low = middle + 1;
        // Om det eftersökta numret är lägre än mittenvärdet, sök i lägre halvan
        else if(key < arr[middle])
            high = middle - 1;
        // Om det eftersökta talet är mittenvärdet, returnera det
        else
            return middle;
    }

    return -1;
}
