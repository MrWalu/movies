#include <iostream>
#include <cstdlib>
#include <string>
#include <cstddef>

using namespace std;

//Struktura "Film"
struct Movie{
public:
    string title;
    string main_actors[2];
    int prod_year, time;

    //Metoda "poka¿Film()" wyœwietla dane o stworzonym filmie.
    void showMovie(){
        cout<<"Movie title: "<<title<<endl;
        for(int i=0;i<2;i++){
            cout<<"Main actors: "<<main_actors[i]<<endl;
        }
        cout<<"Year of production: "<<prod_year<<endl;
        cout<<"Lenght: "<<time<<" minutes"<<endl<<endl;
    }
};

//Klasa "Klient"
class Client{
private:
    string name, secName;
    int min_limit;
    const int movies_limit=3;
    Movie** bor_movies;
public:
    //Konstruktor z list¹ inicjalizatorów.
    Client(string n="", string sN="", int minl=500, int movl=3){
            this->name=n;
            this->secName=sN;
            this->min_limit=minl;
            bor_movies=new Movie*[movl];
            for(int i=0;i<movl;i++){
                bor_movies[i]=NULL;
            }
        }
    //Metoda "pokazInfo()" wyœwietla informacje o obiekcie klasy "Klient".
    void showInfo(){
        cout<<"Info about the client:"<<endl;
        cout<<"Name: "<<name<<endl;
        cout<<"Second name: "<<secName<<endl;
        cout<<"Limit of minutes: "<<min_limit<<endl;
        cout<<"Limit of movies: "<<movies_limit<<endl;
        cout<<"Borrowed movies: "<<endl;
        //Pêtla 'for' wyœwietla tytu³y filmów z tablicy do momentu, a¿ napotka puste miejsce w tablicy.
        for(int i=0;i<movies_limit;i++){
            if(bor_movies[i]!=NULL){
                cout<<bor_movies[i]->title<<endl;
            }
        }
    }
    //Metoda "zmienDane()" zmienia imiê i nazwisko klienta, na którym zosta³a wywo³ana.
    //Je¿eli w miejscu którejœ z danych wpisany jest znak "-", to taka dana nie zostaje zmieniona.
    void changeData(string n, string s){
        if(n!="-"){
            name=n;
        }
        if(s!="-"){
            secName=s;
        }
    }
    void setLimit(int l){
        min_limit=l;
    }
    //Metoda "wypozyczFilm()" przyjmuje za argument obiekt klasy "Film".
    //Przy wypo¿yczeniu sprawdza, czy nie przekroczony zostaje dopuszczalny limit minut.
    //Je¿eli nie, to przypisuje dany film klientowi i odejmuje czas jego trwania od dotychczasowego limitu.
    //Je¿eli limit zosta³by przekroczony, to film nie zostaje przypisany.
    void borrowMovie(Movie* m){
        int l=min_limit;
        int d=m->time;
        int n=0;
        for(int i=0;i<this->movies_limit;i++){
            if(this->bor_movies[i]!=NULL){
                n++;
            }
        }
        if(l>=d&&n+1<=this->movies_limit){
            bor_movies[n]=m;
            l-=d;
            setLimit(l);
        }
        else
            cout<<"You've reached your limit"<<endl<<endl;
    }
    //Metoda "zwrotFilmu()" bierze za argument obiekt klasy Film.
    //Odwrotnie do metody "wypozyczFilm()" "oddaje ona minuty" do limitu.
    void movieRet(Movie* m){
        string x=m->title;
        for(int i=0;i<movies_limit;i++){
            string y=bor_movies[i]->title;
            if(x==y){
                bor_movies[i]=NULL;
                int z=m->time;
                int q=min_limit;
                q+=z;
                setLimit(q);
                cout<<"The movie has been returned"<<endl<<endl;
            }
        }
    }
     ~Client(){
        delete[] bor_movies;
    }
};

int main()
{
    Movie f1{"GoodFellas",{"Ray Liotta","Joe Pesci"},1990,145};
    Movie tabm[4]={{"Titanic",{"Leonardo Di Caprio","Kate Winslet"},1997,194},
                {"The Irishman",{"Al Pacino","Robert De Niro"},2019,207},
                {"The Godfather",{"Al Pacino","Marlon Brando"},1972,178},
                {"Fast and Furious",{"Paul Walker","Vin Diesel"},2001,106}};
    f1.showMovie();
    for(int i=0;i<4;i++){
        tabm[i].showMovie();
    };

    Client tabc[2]={Client("Michael","Surtees",500,5),
                    Client("Adam","Smith",700,3)};

    tabc[0].showInfo();
    cout<<"No movies borrowed yet"<<endl<<endl;
    tabc[1].showInfo();
    cout<<"No movies borrowed yet"<<endl<<endl;

    tabc[1].changeData("-","Freeman");
    tabc[1].showInfo();
    cout<<"No movies borrowed yet"<<endl<<endl;

    cout<<"Borrowing movies"<<endl;
    tabc[1].borrowMovie(&f1);
    tabc[1].borrowMovie(&tabm[1]);
    tabc[1].borrowMovie(&tabm[2]);
    tabc[1].showInfo();
    cout<<endl;

    tabc[1].movieRet(&f1);
    tabc[1].showInfo();

    return 0;
}
