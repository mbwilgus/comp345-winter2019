#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <fstream>
#include <list>
using namespace std;

#include "Card.h"
#include "PowerplantCard.h"
#include "SummaryCard.h"
#include "Step3Card.h"
#include "Resource.h"

void shuffle(PowerplantCard cards[], int size);

int main(int argc, char *argv[])
{
    const int NUM_POWER_PLANTS = 42;
    const int MARKET_SIZE = 8;

    PowerplantCard cards[NUM_POWER_PLANTS];
    fstream input;
    int name;
    string resources;
    int powerable;
    input.open("powerplants.txt");
    int i = 0;
    while(input >> name >> resources >> powerable)
    {
        PowerplantCard c;
        int needed = stoi(resources.substr(0, 1));
        if(needed > 0)
        {
            string types[2];
            size_t size = 0;
            size_t start = 2;
            size_t end = resources.find(",");
            while(end != string::npos)
            {
                types[size++] = resources.substr(start, end - start);
                start = end + 1;
                end = resources.find(",", start);

            }
            types[size++] = resources.substr(start, end);
            if(size == 1) c = PowerplantCard(name, powerable, needed, RESOURCE_VALUES.at(types[0]));
            else if(size == 2) c = PowerplantCard(name, powerable, needed, RESOURCE_VALUES.at(types[0]), RESOURCE_VALUES.at(types[1]));
            c.store(RESOURCE_VALUES.at(types[0]));
        } else {
            c = PowerplantCard(name, powerable, needed);
        }
        cards[i++] = c;
    }
    input.close();

    PowerplantCard market[8] = {cards[0], cards[1], cards[2], cards[3], cards[4], cards[5], cards[6], cards[7]};

    const int FULL_DECK_SIZE = NUM_POWER_PLANTS - MARKET_SIZE;

    PowerplantCard deckCards[FULL_DECK_SIZE];
    for(int i = 0; i < FULL_DECK_SIZE; i++)
    {
        deckCards[i] = cards[i + MARKET_SIZE];
    }

    PowerplantCard ecoOne = cards[10];
    Step3Card s3Card;
    shuffle(deckCards, FULL_DECK_SIZE);
    list<Card*> deck;
    for(PowerplantCard& c: deckCards)
    {
        if(c == ecoOne) continue;
        deck.push_back(&c);
    }

    deck.push_front(&ecoOne);
    deck.push_back(&s3Card);

    cout << "MARKET:" << endl;

    for(int i = 0; i < MARKET_SIZE; i++)
    {
        cout << market[i].info() << endl;
    }

    cout << endl << "DECK:" << endl;

    for(Card* cPtr : deck)
    {
        cout << cPtr->info() << endl;
    }

    cout << endl << "SUMMARY:"<< endl;

    SummaryCard summary;
    cout << summary.info() << endl;

    return 0;
}

void shuffle(PowerplantCard cards[], int size)
{
    srand(time(NULL));
    int max = size - 1;
    while(max > 0) {
        int r = rand() % max ;
        PowerplantCard temp = cards[r];
        cards[r] = cards[max];
        cards[max--] = temp;
    }
}
