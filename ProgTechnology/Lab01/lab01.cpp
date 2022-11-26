#include <iostream>
#include <string>
using namespace std;

class Player{
public:
    //базовые атрибуты
    int id;
    string name;
    string nik;
    //Указатель на следующий элемент
    Player* next;
    Player* prev;
    //Установка следующего элемента
    void set_next(Player* next_pl){ next = next_pl;}
    //Взятие следующего элемента
    Player* get_next(){ return next;}
    //становка предыдущего элемента
    void set_prev(Player* prev_pl){ prev = prev_pl;}
    //Взятие пердыдущего элемента
    Player* get_prev(){ return prev;}
    //Конструктор
    Player(int id0 = 0, string name0 = "Unnamed", string nik0 = "Zero"){
        cout << "Player with name " << name0 << " was created!" << endl;
        id = id0;
        name = name0;
        nik = nik0;
        next = nullptr;
    }
    //Функция вывода
    void print(){ cout << id << ' ' << name << ' ' << nik << endl; }
    //Деструктор
    ~Player(){ cout << "Player with name " << name << " was destroyed!" << endl; }
    //Задаём собственный вывод
    friend ostream& operator<<(ostream& out, Player& pl)
    {
        out << pl.id << ' ' << pl.name << ' ' << pl.nik << endl;
        return out;
    }
};

class List{
    Player* head; //Создаём голову списка
    Player* tail; //Создаём хвост списка
    int k;
public:
    //создаём конструктор
    List(){ head = nullptr; tail = nullptr; k = 0;}

    void push_front(Player* new_pl){
        (*new_pl).set_next(head);
        (*new_pl).set_prev(nullptr);
        if (head != nullptr)
            (*head).set_prev(new_pl);

        if (k == 0)
            tail = head = new_pl;
        else
            head = new_pl;

        k++;
    }

    void push_back(Player* new_pl){
        (*new_pl).set_next(nullptr);
        (*new_pl).set_prev(tail);
        if(tail != nullptr)
            (*tail).set_next(new_pl);

        if (k == 0)
            tail = head = new_pl;
        else
            tail = new_pl;

        k++;
    }

    void insert(int place, Player* new_pl){
        if (head == nullptr){
            cout << "Error! List is empty!" << endl;
            return;
        }
        if(place < 0 || place >= k){
            cout << "Error! Not enough elements in list or incorrect position!" << endl;
            return;
        }
        if(place == k - 1){
            push_back(new_pl);
            return;
        }

        Player* temp = head;
        for(int i = 0; i < place; i++)
            temp = (*temp).get_next();

        (*new_pl).set_next((*temp).get_next());
        (*((*temp).get_next())).set_prev(new_pl);

        (*temp).set_next(new_pl);
        (*new_pl).set_prev(temp);

        k++;
    }

    void insert(Player* place_pl, Player* new_pl){
        if (head == nullptr){
            cout << "Error! List is empty!" << endl;
            return;
        }

        if (place_pl == tail){
            push_back(new_pl);
            return;
        }

        bool check(true);
        Player* temp = head;
        for(int i = 0; i < k; i++){
            if(temp == place_pl) {check = false; break;}
            temp = (*temp).get_next();
        }
        if(check){
            cout << "Error! This player is not in the list!" << endl;
            return;
        }

        (*new_pl).set_next((*place_pl).get_next());
        (*((*place_pl).get_next())).set_prev(new_pl);

        (*place_pl).set_next(new_pl);
        (*new_pl).set_prev(place_pl);

        k++;
    }

    void del_front(){
        if (k == 0) {
            cout << "List is empty!" << endl;
            return;
        }
        if (k == 1){
            head = tail = nullptr;
            k--;
            return;
        }
        Player* del = head;
        (*(*del).get_next()).set_prev(nullptr);
        head = (*del).get_next();
        k--;
    }

    void del_back(){
        if (k == 0) {
            cout << "List is empty!" << endl;
            return;
        }
        if (k == 1){
            head = tail = nullptr;
            k--;
            return;
        }
        Player* del = tail;
        (*(*del).get_prev()).set_next(nullptr);
        tail = (*del).get_prev();
        k--;
    }

    void del(int place){

        if(place < 0 || place >= k){
            cout << "Error! Not enough elements in list or incorrect position!" << endl;
            return;
        }
        if (k == 0){
            cout << "Error! List is empty!" << endl;
            return;
        }
        if (k == 1){
            head = tail = nullptr;
            k--;
            return;
        }

        if (place == 0){ del_front(); return;}
        if (place == k - 1){del_back(); return;}

        Player* temp = head;
        for(int i = 0; i < place; i++)
            temp = (*temp).get_next();
        (*(*temp).get_prev()).set_next((*temp).get_next());
        (*(*temp).get_next()).set_prev((*temp).get_prev());
        k--;
    }

    void del(Player* del_pl){
        if (head == nullptr){
            cout << "Error! List is empty!" << endl;
            return;
        }
        if (del_pl == tail){ del_back(); return; }
        if (del_pl == head){ del_front(); return; }

        bool check(true);
        Player* temp = head;
        for(int i = 0; i < k; i++){
            if(temp == del_pl) {check = false; break;}
            temp = (*temp).get_next();
        }
        if(check){
            cout << "Error! This player is not in the list!" << endl;
            return;
        }

        (*(*del_pl).get_prev()).set_next((*del_pl).get_next());
        (*(*del_pl).get_next()).set_prev((*del_pl).get_prev());

        k--;

    }

    void moving(int mov_pl, int place){
        if(place < 0 || place >= k){
            cout << "Error! Not enough elements in list or incorrect position!" << endl;
            return;
        }
        if(mov_pl < 0 || mov_pl >= k){
            cout << "Error! Not enough elements in list or incorrect position!" << endl;
            return;
        }
        if (k < 2){
            cout << "Error! List is empty or not enough elements!" << endl;
            return;
        }
        if (mov_pl == place) return;

        Player* temp = head;
        for(int i = 0; i < mov_pl; i++)
            temp = (*temp).get_next();

        if(place == k - 1){del(temp);push_back(temp); return;}

        del(temp);
        if(mov_pl < place) place--;
        insert(place, temp);

    }

    void swap(int pl_1, int pl_2){
        if (pl_1 == pl_2) return;
        if (pl_1 > pl_2) std::swap(pl_1, pl_2);

        if(pl_1 < 0 || pl_2 >= k){
            cout << "Error! Not enough elements in list or incorrect position!" << endl;
            return;
        }
        if (k < 2){
            cout << "Error! List is empty or not enough elements!" << endl;
            return;
        }
        moving(pl_2, pl_1);
        moving(pl_1, pl_2);

    }

    void search(int s_id){
        Player* temp = head;
        int i = 0;
        for(i; i < k; i++){
            if ((*temp).id == s_id) break;
            temp = (*temp).get_next();
        }
        cout << (*temp);
        cout << "Number in list: " << i << endl;
    }

    void search(string sch){
        Player* temp = head;
        int i = 0;
        for(i; i < k; i++){
            if ((*temp).name == sch || (*temp).nik == sch ) break;
            temp = (*temp).get_next();
        }
        cout << (*temp);
        cout << "Number in list: " << i << endl;
    }

    void print(){
        if (k == 0) {
            cout << "List is empty!" << endl;
            return;
        }
        Player* temp = head;
        while(temp != nullptr){
            cout << (*temp);
            temp = (*temp).get_next();
        }
    }

    void print_back(){
        Player* temp = tail;
        while(temp != nullptr){
            cout << (*temp);
            temp = (*temp).get_prev();
        }
    }

    void print_count(){
        cout << "Count = " << k << endl;
    }
};


int main(){
    Player  p0,
            p1(1656, "Andrey", "Cheshier"),
            p2(1353, "Sasha", "Shrek"),
            p3(1923, "Anton", "Magic"),
            p4(1743, "Alice", "Bigpons");

    //cout << p0 << p1 << p3 << p4;
    List ls;
    ls.push_front(&p0);
    ls.push_back(&p1);
    ls.push_back(&p4);
    ls.insert(1, &p2);
    ls.insert(&p2, &p3);
    ls.print();
    //ls.print_back();
    //ls.print_count();
    cout << "--------------------------------" << endl;
    ls.moving(2, 3);
    ls.moving(0, 3);
    ls.moving(3, 2);
    ls.print();
    //ls.print_back();
    cout << "--------------------------------" << endl;
    ls.swap(0,3);
    ls.swap(1,3);
    ls.print();
    //ls.print_back();
    cout << "--------------------------------" << endl;
    ls.search(1656);
    ls.search("Alice");
    ls.search("Shrek");
    cout << "--------------------------------" << endl;
    ls.del(2);
    ls.del(2);
    ls.print();
    ls.print_back();
    cout << "--------------------------------" << endl;
    ls.del(&p0);
    ls.print();
    //ls.print_back();
    cout << "--------------------------------" << endl;
    ls.del_front();
    ls.del_back();
    ls.print();
    //ls.print_back();


    return 0;
}
