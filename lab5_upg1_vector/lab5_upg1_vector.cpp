// lab5_upg1_vector.cpp
// Program för att utföra ett antal operationer på en vector
// Thomas Nordenmark 2013-12-012
// Ver 0.1
//------------------------------------------------------------------------------
#include <iostream> // cin, cout
#include <random> // default_random_engine
#include <iomanip> // setw, setprecision
#include <vector> // vector
#include <algorithm> // generate, sort, count etc
#include <functional> // bind
using namespace std;

// =========================
// Deklaration av konstanter
// =========================
const int MAX=600; // Max platser i vectorn
const int FREK=100; // Antal platser i frekvensvector samt slumpgeneratorns max

// ============
// Huvudprogram
// ============
int main()
{
    // Initiera slumpdistributörsobjektet generator
    default_random_engine generator(static_cast<unsigned>(time(0)));
    uniform_int_distribution<int> random(1, FREK); // Slumpa i itervallet 1-100
    // Slå ihop slumpgeneratorn till en funktion för enklare användning
    auto slumpaTal = bind(random, generator);

    // Iteratorer för loopar
    int i;
    //int j; // Behövs för utskriftsmetod 1

    // Fyll ivec1 med 600 slumpade tal mellan 1 och 100
    cout << "Slumpar 600 tal mellan 1 och 100 till ivec1." << endl << endl;
    vector<int> ivec1(MAX, 0); // Vector nr 1
    generate(ivec1.begin(), ivec1.end(), slumpaTal);


    // Kopiera ivec1 till ivec2
    vector<int> ivec2; // Kopia av ivec1
    ivec2 = ivec1;


    // Beräkna medelvärdet av alla tal i ivec2
    int sum = 0;
    for(auto i: ivec2)
        sum += i;

    double medel = 0;
    medel = (double)sum / (double)MAX; // Typecasta till double för högre precision
    cout << "Vectorns medelvärde är: " << fixed << setprecision(2) << medel << endl << endl; // Skriv ut medel med 2 decimaler


    // Sök efter minsta och största talet i ivec2
    int smallest = *(min_element(ivec2.begin(), ivec2.end()));
    int largest = *(max_element(ivec2.begin(), ivec2.end()));

    cout << "Minsta talet i vectorn är: " << smallest << endl;
    cout << "Största talet i vectorn är: " << largest << endl << endl;


    // Sök efter inmatat tal i vectorn och skriv ut antalet förekomster
    int tal = 0, counter = 0;

    cout << "Ange ett tal att söka efter: ";
    cin >> tal;

    // Sök och räkna träffar, skriv ut resultat
    counter = count(ivec2.begin(), ivec2.end(), tal);
    cout << "Talet " << tal << " fanns " << counter  << " gånger i ivec2." << endl << endl;


    // Beräkna vilket nummer som förekommer flest gånger, samt hur många gånger
    int max = 0;
    int maxindex = ivec2[0];
    int numcount = 0;

    // Kan göras effektivare med en map, men det har vi inte gått igenom än. Just nu är det O(n²) men
    // skulle gå att modifera till O(n)
    for(auto i: ivec2)
    {
        numcount = (int)count(ivec2.begin(), ivec2.end(), ivec2[i]);
        if(numcount > max)
        {
            max = numcount;
            maxindex = ivec2[i];
        }
    }
    // Skriv ut resultat
    cout << "Talet med flest förekomster är: " << maxindex << " och förekommer " << max << " gånger." << endl << endl;


    // Sortera vectorn med <algorithm>
    sort(ivec2.begin(), ivec2.end());


    // Skriv ut alla ettor på en rad, tvåor på en rad osv
    // Metod 1 känns inte riktigt rätt, så jag skickar in två olika kodsnuttar
    cout << "Skriver ut vectorn med alla siffror på separata rader: " << endl;

    // Metod 1
    // Ny vektor för att lagra förekomsten/frekvensen
    //vector<int> frek(FREK, 0);
    // Fyll vektorn med nummerfrekvenserna
    //for(auto i = 0; i < MAX; i++)
    //    frek[ivec2[i]]++;

    // Skriv ut vektorns data rad för rad
    //for(i = 1; i < FREK + 1; i++)
    //{
    //    cout << i << " ";
    //    for(j = 0; j < frek[i]; j++)
    //        cout << i << " ";
    //    cout << endl;
    //}

    // Metod 2
    for(i = 0; i < MAX; i++)
    {
        int temp = ivec2[i];

        cout << ivec2[i] << " ";

        if(ivec2[i + 1] != temp)
            cout << endl;
    }


    return 0;
}
