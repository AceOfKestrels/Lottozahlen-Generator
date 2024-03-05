#include <iostream>
#include <iomanip>

using namespace std;

void outputDashedLine() {
    cout << endl << "----------------------------------------------------------" << endl << endl;
}

bool runAgain() {
    string input;
    cout << endl << "Noch einmal? [y/N]";
    cin >> input;
    return input == "y" || input == "Y";
}

bool contains(int arr[], int value, int count) {
    for(int i = 0; i<count; i++) {
        if(arr[i] == value) return true;
    }
    return false;
}

void generateAndOutputNumbers(string day, int gameCount) {
    int numbers[gameCount][6];
    int number;

    cout << day << ": " << endl;

    // Generate Numbers
    for(int j = 0; j<gameCount; j++) {
        for(int i = 0; i<6; i++) {
            do {
                number = ( rand() % 49 ) + 1;
            } while(contains(numbers[j], number, i));
            numbers[j][i] = number;
        }
    }

    for(int j = 0; j<gameCount; j++) {

        //Bubble Sort
        bool sorted = false;
        do {
            sorted = true;

            for(int i = 0; i<6; i++) {
                if(i!=0 && numbers[j][i]<numbers[j][i-1]) {
                    int temp = numbers[j][i];
                    numbers[j][i] = numbers[j][i-1];
                    numbers[j][i-1] = temp;
                    sorted = false;
                }
            }
        } while(!sorted);

        // Output Line
        cout << "Spiel " << (j+1) << ": ";
        for(int i = 0; i<6; i++) {
            cout << numbers[j][i] << "\t";
        }
        cout << endl;
    }
}

void calculateAndOutputPrice(int games, int weeks, bool twoDays) {
    double gesamtpreis = ((games * weeks) * 1.2);

    if((twoDays)) {
        gesamtpreis *= 2;

        if(weeks > 2) {
            gesamtpreis += 1;
        } else {
            gesamtpreis += 0.75;
        }
    }
    else if(weeks > 1) {
        gesamtpreis += 0.75;
    } else {
        gesamtpreis += 0.5;
    }

    cout << setprecision(2);
    cout << endl << "Gesamtpreis: " << gesamtpreis << "€" << endl;
}

void outputChosenOptions(int games, int weeks, bool wed, bool sat) {
    outputDashedLine();
    cout << "Gewählte Optionen:" << endl;
    cout << "Spiele pro Spieltag: " << games << endl;
    cout << "Anzahl Spielwochen:" << weeks << endl;
    
    cout << "Spieltage: ";
    if(wed && sat) {
        cout << "Mittwoch & Samstag";
    }
    else if(wed) {
        cout << "Mittwoch";
    }
    else {
        cout << "Samstag";
    }
    cout << endl;

}

int main() {
    string tage;
    int anzahlSpiele, anzahlWochen;
    bool samstag, mittwoch;

    srand(time(NULL));
    do {
        system("clear");
        cout << "Lottozahlen Generator" << endl;
        outputDashedLine();

        cout << "Wie viele Spiele sollen pro Spieltag gespielt werden? ";
        cin >> anzahlSpiele;
        if(anzahlSpiele < 1) {
            cout << endl << "Ungueltige Eingabe: " << anzahlSpiele << endl;
            continue;
        }

        cout << "An welchen Tagen soll gespielt werden? (Mi, Sa, Beide) ";
        cin >> tage;
        if(tage == "Sa") {
            samstag = true;
            mittwoch = false;
        }
        else if(tage == "Mi") {
            samstag = false;
            mittwoch = true;
        }
        else if(tage == "Beide") {
            samstag = true;
            mittwoch = true;
        }
        else {
            cout << endl << "Ungueltige Eingabe: " << tage << endl;
            continue;
        }

        cout << "Wie viele Wochen sollen gespielt werden? (1-5) ";
        cin >> anzahlWochen;
        if(anzahlWochen < 1 || anzahlWochen > 5) {
            cout << endl << "Ungueltige Eingabe: " << anzahlWochen << endl;
            continue;
        }

        for(int w = 0; w<anzahlWochen; w++) {
            outputDashedLine();
            cout << "Woche " << (w+1) << ": " << endl;

            if(mittwoch) {
                generateAndOutputNumbers("Mittwoch", anzahlSpiele);
            }
            if(samstag) {
                generateAndOutputNumbers("Samstag", anzahlSpiele);
            }
        }

        outputChosenOptions(anzahlSpiele, anzahlWochen, mittwoch, samstag);

        calculateAndOutputPrice(anzahlSpiele, anzahlWochen, (mittwoch && samstag));

    } while(runAgain());

    return 0;
}
