// lab5_upg1_array.cpp
// Program för att utföra ett antal operationer på en array
// Thomas Nordenmark 2013-12-12
// Ver 0.1
//------------------------------------------------------------------------------
#include <iostream> // cin, cout
#include <random> // default_random_engine
#include <iomanip> // setw, setprecision
#include <functional> // bind
using namespace std;

// =========================
// Deklaration av konstanter
// =========================
const int MAX=600; // Max platser i arrayen
const int FREK=100; // Antal platser i frekvensarray samt slumpgeneratorns max

// ======================
// Funktionsdeklarationer
// ======================
void bubbleSort(int arr[]); // Bubble sort

// ============
// Huvudprogram
// ============
int main()
{
    // Initiera slumpdistributörsobjektet generator
    default_random_engine generator(static_cast<unsigned>(time(0)));
    uniform_int_distribution<int> random(1, FREK); // Slumpa i itervallet 1-6
    // Slå ihop slumpgeneratorn till en funktion för enklare användning
    auto slumpaTal = bind(random, generator);

    int arr[MAX]; // Array med MAX antal platser
    // Iteratorer för loopar
    int i;
    //int j; // Behövs för utskriftmetod 1

    // Fyll arr[] med 600 slumpade tal mellan 1 och 100
    cout << "Slumpar 600 tal mellan 1 och 100 till arr[]." << endl << endl;
    for(i = 0; i < MAX; i++)
        arr[i] = slumpaTal(FREK);


    // Kopiera arr[] till arrcopy[]
    int arrcopy[MAX]; // Kopia av arr
    cout << "Kopierar arr[] till arrcopy[]." << endl << endl;
    for(i = 0; i < MAX; i++)
        arrcopy[i] = arr[i];


    // Beräkna medelvärdet av alla tal i arrayen
    int sum = 0; // Lagra arrayens totalsumma
    // Addera tal till totalsumman varje varv
    for(i = 0; i < MAX; i++)
        sum += arrcopy[i];

    double medel; // Lagra arrayens medelvärde
    medel = (double)sum / (double)MAX;  // Typecasta till double för högre precision
    cout << "Arrayens medelvärde är: " << fixed << setprecision(4) << medel << endl << endl; // Skriv ut medel med 2 decimaler


    // Sök efter minsta och största talet i arrayen
    int smallest = arrcopy[0]; // Sätt smallest till arrayens första element som start
    int largest = 0; // Sätt largest till 0 som utgångsläge

    // Iterera igenom arrayen, om ett tal är mindre än smallest, uppdatera smallest med det nya talet
    for(i = 1; i < MAX; i++)
    {
        if(arrcopy[i] < smallest)
            smallest = arrcopy[i];
        if(arrcopy[i] > largest)
            largest = arrcopy[i];
    }

    // Skriv ut det minsta  och största talet
    cout << "Minsta talet i arrayen är: " << smallest << endl;
    cout << "Största talet i arrayen är: " << largest << endl << endl;


    // Nu framgår det inte i vilken ordning operationerna ska utföras, själv hade jag sorterat arrayen
    // från första början för att förenkla alla andra operationer. T.ex. att hitta minsta och största
    // talet i den kommenterade koden nedan, men det känns för enkelt
    //
    //cout << "Det minsta talet är: " << arrcopy[0] << endl;
    //cout << "Det största talet är: " << arrcopy[MAX - 1] << endl;


    // Sök efter inmatat tal i arrayen och skriv ut antalet förekomster
    int tal = 0, counter = 0;
    cout << "Angel ett tal att söka efter: ";
    cin >> tal;

    // Sök efter det inmatade talet
    for(i = 0; i < MAX; i++)
        if(arrcopy[i] == tal)
            counter++;

    // Skriv ut antal förekomster för det inmatade talet
    cout << "Talet " << tal << " fanns " << counter << " gånger i arrcopy[]" << endl << endl;


    // Beräkna talens frekvens, s.k. histogram
    cout << "Beräknar sifferfrekvensen i arrcopy[]." << endl;

    // Initialisera en array frek[] med 100 platser för att lagra sifferfrekvens
    int frek[FREK];

    // Nollställ arrayen frek[] för att slippa smuts och konstiga beräkningar
    for(i = 0; i < MAX; i++)
        frek[i] = 0;

    // Iterera igenom arrcopy[] och uppdatera indexet i frek[] för varje nummer
    for(i = 0; i < MAX; i++)
        frek[arrcopy[i]]++;

    // Beräkna vilket nummer som förekommer flest gånger, samt hur många gånger
    int max = frek[0]; // Räknare för antalet förekomster
    int maxindex = 0; // Index för vilken position som innehåller det mest förekommande talet

    // Iterera igenom frekvens-arrayen
    for(i = 0; i < FREK; i++)
    {
      if(max < frek[i])
      {
        max = frek[i];
        maxindex = i;
      }
    }

    // Skriv ut tecknet med flest förekomster samt antal förekomster
    cout << "Tecknet med flest förekomster är: " << maxindex << " och förekommer " << max << " gånger." << endl << endl;


    // Sortera arrayen stigande med funktionen bubbleSort(). Jag skulle gjort det långt tidigare, för
    // att förenkla alla andra operationer, men det känns som det renderar en del av övningens moment
    // allt för enkla.
    // Med utskriftsmetod 1 nedan behövs ingen sortering alls
    cout << "Sorterar arrayen med bubble sort." << endl << endl;
    bubbleSort(arrcopy);


    // Skriv ut alla ettor på en rad, tvåor på en rad osv
    cout << "Skriver ut arrayen med alla siffror på separata rader: " << endl;

    // Metod 1 med extra array och dubbel for-loop
    //for(i = 1; i < FREK + 1; i++)
    //{
    //    cout << i << " ";
    //    for(j = 1; j < frek[i]; j++)
    //        cout << i << " ";
    //    cout << endl;
    //}

    // Metod 2 utan extra array
    for(i = 0; i < MAX; i++)
    {
        int temp = arrcopy[i];

        cout << arrcopy[i] << " ";

        if(arrcopy[i + 1] != temp)
            cout << endl;
    }

    return 0;
}

// =====================
// Funktionsdefinitioner
// =====================

// Bubble sort
void bubbleSort(int arr[])
{
    int i, j; // Iteratorer för looparna
    int temp; // Temporär lagringsplats för sortering

    // Yttre loop
    for(i = 0; i < MAX; i++)
    {
        // Inre loop
        for(j = 0; j < MAX - 1; j++)
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
