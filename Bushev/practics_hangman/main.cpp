#include <iostream>
#include <fstream>
#include <sstream>

#include <string>
#include <vector>
#include <ctime>

#include <windows.h>

#include <SFML/System.hpp>
#include <SFML/Network.hpp>

using namespace sf;
using namespace std;

const char* SERVER_ADDR = "http://t96138jk.bget.ru/";
const char* SERVER_HASH = "HCXt7xC47HGvVwo_68XX25Tgs789XBZ4fhsP0";

const char* LOADING = "-\\|/";
const int LOADING_TIME = 45;
const int LOADING_PING = 50;

const int MIN_NICK_LENGTH = 3;
const int MAX_NICK_LENGTH = 15;

const int MIN_WORD_LENGTH = 3;
const int MAX_WORD_LENGTH = 15;

const int ONLINE_WAIT = 15;

void show_online_menu(int error);

void console_clear(){
    system("cls");
}

char c_lower(char c){
    return c < '�' ? c + 32 : c;
}

bool s_lower(string &str){
    for(unsigned int i = 0; i < str.size(); i++){
        if(str[i] < '�' || str[i] > '�') return 1;
        else str[i] = c_lower(str[i]);
    }

    return 0;
}

bool check_letter(string str, string &ans, char letter){
    bool correct = 0;

    for(unsigned int s = 0; s < str.size(); s++){
        if(str[s] == letter){
            ans[s] = letter;
            correct = 1;
        }
    }

    return correct;
}

void show_intro(){
    cout << "����� ���������� � ���� �������� (����� - exit)\n\n";
    cout << "�� ������ ������� ��������� ������� ����\n������� pve ��� pvp ��� ������ ���������������� ������: ";
}

void show_online_intro(string name){
    cout << "����� ���������� � ������ ������ ��������";

    if(name != "") cout << ", " << name;
    cout << "!" << endl;

    cout << "\n������ ��������� �������: " << endl;
    cout << "\ncreate <name> - ������� ����� ����" << endl;
    cout << "list - ������� ������ ��������� ���" << endl;
    cout << "connect <id> - ������������ � ����" << endl;
    cout << "set <name> - ������� ���" << endl;
    cout << "exit - ����� � ������� ����\n\n";

    if(name != "") cout << "������� �������: ";
    else cout << "������� ���� ���, ����� ����������: ";
}

void show_man(int mmax){
    console_clear();

    string val = "O/|\\/\\";
    for(int i = mmax; i < 6; i++) val[i] = ' ';

    cout << "_____" << endl;
    cout << "|   |" << endl;
    cout << "|   " << val[0] << endl;
    cout << "|  " << val[1] << val[2] << val[3] << endl;
    cout << "|  " << val[4] << " " << val[5] << endl;
    cout << "|" << endl;
}

int start_game(string str){
    string ans = str;
    string stream;
    bool correct = 0;

    for(unsigned int i = 1; i < ans.size()-1; i++) ans[i] = '*';
    check_letter(str, ans, ans[0]);
    check_letter(str, ans, ans[ans.size()-1]);

    for(int i = 0; i < 6; i++){
        show_man(i);

        correct = 0;

        cout << endl << "��� ����� ������� �����: " << ans << endl;
        cout << "������� �����: "; cin >> stream;
        correct = check_letter(str, ans, c_lower(stream[0]));

        if(ans == str){
            show_man(i);

            cout << endl << "��� ����� ������� �����: " << ans << endl;
            cout << "\n�����������, �� ��������! ����� ��������!" << endl;
            cout << "������ ������� ��� ���? -> "; cin >> stream;
            return stream[0] == 'y' || stream[0] == '�';
        }

        if(correct) i--;
    }

    show_man(6);

    cout << endl << "��� ����� ������� �����: " << ans << endl;
    cout << "\n� ���������, �� �� ������ ������� �����. ���������: " << str << endl;
    cout << "������ ������� ��� ��� (y - ��)? -> "; cin >> stream;

    return stream[0] == 'y' || stream[0] == '�';
}

int start_pve(){
    ifstream fin("words.txt");

    string str;
    int words = 0;
    vector<string> svector;

    while(fin >> str){
        ++words;
        svector.push_back(str);
    }

    if(words == 0) return -1;

    srand(time(NULL));
    str = svector[rand() % words];

    return start_game(str);
}

string perform_request(Http::Request request){
    Http http(SERVER_ADDR);
    Http::Response response = http.sendRequest(request);
    return response.getStatus() == Http::Response::Ok ? response.getBody() : "#������ �����������, ��������� ����������";
}

void close_game(int gid){
    Http::Request request("/9_hangman_backend/close.php", Http::Request::Post);
    ostringstream stream;
    stream << "hash=" << SERVER_HASH << "&gid=" << gid;
    request.setBody(stream.str());
    perform_request(request);
}

bool error_connection(string &ans, int gid){
    if(ans[0] == '#' || ans[ans.size()-1] == '9'){
        console_clear();
        cout << "���������� ��������..." << endl << endl;
        close_game(gid);
        system("pause");
        return 1;
    }else if(ans.size() >= 1) ans.erase(ans.size()-1, 1);

    return 0;
}

bool start_online(string host, string player, int gid, bool role){
    Http::Request request("/9_hangman_backend/score.php", Http::Request::Post);
    ostringstream stream;
    stream << "hash=" << SERVER_HASH << "&gid=" << gid;
    request.setBody(stream.str());
    string ans = perform_request(request);
    if(error_connection(ans, gid)) return 0;

    int lsec = 0, sec;
    Clock clock;

    console_clear();

    cout << "������� ���� #" << gid << endl << endl;
    cout << "����" << (!role ? " (!): " : ": " ) << host << endl;
    cout << "�������������"<< (role ? " (!): " : ": " ) << player << endl << endl;

    cout << "�������� ����: " << ans << endl;
    cout << "�� ������ ����� ���� ��������: " << ONLINE_WAIT;

    while(true){
        sec = clock.getElapsedTime().asSeconds();

        if(lsec < sec){
            cout << "\b\b";

            lsec = sec;

            if(ONLINE_WAIT-lsec < 10){
                cout << "0";
            }

            cout << ONLINE_WAIT-lsec;
        }

        if(clock.getElapsedTime().asSeconds() >= ONLINE_WAIT){
            cout << endl << endl;
            request.setUri("/9_hangman_backend/mover.php");
            ans = perform_request(request);
            if(error_connection(ans, gid)) return 0;

            int tries = 6;
            string word, progress;

            if((role && ans[0] == '1') || (!role && ans[0] == '0')){
                while(true){
                    cout << "��������� ����� ��� ������ �����������: ";
                    cin >> word;

                    if(s_lower(word) || word.size() < MIN_WORD_LENGTH || word.size() > MAX_WORD_LENGTH){
                        cout << "\n��������� ������ ������� ����� � ������ [" << MIN_WORD_LENGTH << ", " << MAX_WORD_LENGTH << "] ����\n";
                    }else break;
                }

                progress = word;
                for(unsigned int i = 1; i < progress.size()-1; i++) progress[i] = '*';
                check_letter(word, progress, progress[0]);
                check_letter(word, progress, progress[progress.size()-1]);

                stream << "&word=" << word << "&progress=" << progress << "&tries=6";
                request.setBody(stream.str());
                request.setUri("/9_hangman_backend/set_word.php");

                ans = perform_request(request);
                if(error_connection(ans, gid)) return 0;

                stream.str("");
                stream.clear();

                stream << "hash=" << SERVER_HASH << "&gid=" << gid;
                request.setBody(stream.str());
                request.setUri("/9_hangman_backend/status.php");

                int end_type = 0;

                while(true){
                    console_clear();

                    ans = perform_request(request);
                    if(error_connection(ans, gid)) return 0;

                    tries = ans[ans.size()-1] - '0';
                    ans.erase(ans.size()-1, 1);

                    show_man(6 - tries);

                    if(ans[ans.size()-1] == '*'){
                        ans.erase(ans.size()-1, 1);
                        end_type = 1;
                    }else if(ans[ans.size()-1] == '#'){
                        ans.erase(ans.size()-1, 1);
                        end_type = -1;
                    }

                    cout << endl << "��������� ��������� �����: " << ans[ans.size()-1] << endl;
                    ans.erase(ans.size()-1, 1);

                    cout << endl << "�� �������� �����: " << word << endl;
                    cout << "�������� ��������: " << ans << endl;

                    if(end_type == 1){
                        cout << "\n�� ��������! ���������� ����� �� ���������!" << endl;
                        break;
                    }else if(end_type == -1){
                        cout << "\n�� ���������! �������� �������� ���� �����!" << endl;
                        break;
                    }

                    Sleep(1000);
                }

                request.setUri("/9_hangman_backend/letter.php");

                ans = perform_request(request);
                if(error_connection(ans, gid)) return 0;
            }else{
                cout << "��� ���������� ���������� �����..." << endl;
                request.setUri("/9_hangman_backend/word.php");

                while(true){
                    ans = perform_request(request);
                    if(error_connection(ans, gid)) return 0;
                    if(ans.size() > MIN_WORD_LENGTH) break;
                }

                word = ans;

                while(tries > 0){
                    console_clear();

                    stream.str("");
                    stream.clear();

                    stream << "hash=" << SERVER_HASH << "&gid=" << gid;
                    request.setBody(stream.str());
                    request.setUri("/9_hangman_backend/status.php");

                    ans = perform_request(request);
                    if(error_connection(ans, gid)) return 0;

                    tries = ans[ans.size()-1] - '0';
                    ans.erase(ans.size()-1, 1);

                    show_man(6 - tries);

                    cout << endl << "��������� ��������� �����: " << ans[ans.size()-1] << endl;
                    ans.erase(ans.size()-1, 1);

                    progress = ans;

                    cout << endl << "��� ����� ������� �����: " << progress << endl;
                    cout << "������� �����: "; cin >> ans;

                    if(!check_letter(word, progress, c_lower(ans[0]))) tries--;

                    if(progress == word){
                        show_man(6 - tries);

                        cout << endl << "��� ����� ������� �����: " << word << endl;
                        cout << "\n�����������, �� ��������! ����� ��������!" << endl;

                        stream << "&win=1";
                    }else if(tries <= 0){
                        show_man(6);

                        cout << endl << "��� ����� ������� �����: " << progress << endl;
                        cout << "\n� ���������, �� �� ������ ������� �����. ���������: " << word << endl;

                        stream << "&lost=1";
                    }

                    stream << "&progress=" << progress << "&letter=" << c_lower(ans[0]) << "&tries=" << tries << "&role=" << role;
                    request.setUri("/9_hangman_backend/update_word.php");
                    request.setBody(stream.str());
                    ans = perform_request(request);
                    if(error_connection(ans, gid)) return 0;

                    if(progress == word) break;
                }
            }

            cout << "������ ������� ��� ��� (y - ��)? -> "; cin >> ans;
            return ans[0] == 'y' || ans[0] == '�';
        }
    }
}

void open_connection(string player, int gid){
    console_clear();

    Http::Request request("/9_hangman_backend/connect.php", Http::Request::Post);
    ostringstream stream;
    stream << "hash=" << SERVER_HASH << "&gid=" << gid << "&player=" << player;
    request.setBody(stream.str());

    string ans = perform_request(request);

    if(ans[0] != '#') while(start_online(ans, player, gid, 1)){ }
    else{
        cout << endl << endl << ans << endl << endl;
        system("pause");
    }
}

void waiting_player(string name, int gid){
    console_clear();

    Clock clock;
    int sec = 0, ms = 0, lsec = 0, lms = 0, lstate = 0;

    cout << "�������� ��������� ��� ������ ����... " << LOADING[0] << endl;
    cout << "�������� ������� �� �����: " << LOADING_TIME - sec;

    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

    while(sec < LOADING_TIME){
        ms = clock.getElapsedTime().asMilliseconds();
        sec = clock.getElapsedTime().asSeconds();

        if(lms < ms){
            SetConsoleCursorPosition(h, {39, 0});

            cout << "\b" << LOADING[lstate++ % 4];
            lms = ms + LOADING_PING;
        }

        if(lsec < sec){
            SetConsoleCursorPosition(h, {29, 1});

            cout << "\b\b";

            if(lsec > LOADING_TIME - 11) cout << "0";
            cout << LOADING_TIME - sec;

            lsec = sec;

            Http::Request request("/9_hangman_backend/check.php", Http::Request::Post);
            ostringstream stream;
            stream << "hash=" << SERVER_HASH << "&gid=" << gid;
            request.setBody(stream.str());
            string ans = perform_request(request);

            if(ans.size() >= MIN_NICK_LENGTH && ans[0] != '#'){
                srand(time(NULL));
                stream << "&rand=" << rand() % 2;

                request.setUri("/9_hangman_backend/start.php");
                request.setBody(stream.str());
                perform_request(request);

                while(start_online(name, ans, gid, 0)){ }
                return;
            }else if(ans[0] == '#'){
                cout << "\n\n" << ans << "\n\n";
                system("pause");
                close_game(gid);
                return;
            }
        }
    }

    cout << "\n\n����� �������� �������. ���������� ��������? -> ";
    string str; cin >> str;

    if(str[0] == 'y' || str[0] == '�') waiting_player(name, gid);
    else close_game(gid);
}

void create_game(string name){
    Http::Request request("/9_hangman_backend/create.php", Http::Request::Post);
    ostringstream stream;
    stream << "hash=" << SERVER_HASH << "&host=" << name;
    request.setBody(stream.str());
    string ans = perform_request(request);
    cout << endl << ans;

    if(ans[0] == '#'){
        cout << endl << endl;
        system("pause");
        return;
    }

    request.setUri("/9_hangman_backend/id.php");
    ans = perform_request(request);

    int gid;
    istringstream mstream(ans);
    if(!(mstream >> gid)) gid = 0;

    if(!gid){
        cout << endl << endl;
        system("pause");
        cout << "\n\n�� ������� ������������ � ��������� ����\n\n";
    }else{
        cout << gid << endl << endl;
        system("pause");
        waiting_player(name, gid);
    }
}

void show_game_list(){
    Http::Request request("/9_hangman_backend/list.php", Http::Request::Post);
    ostringstream stream;
    stream << "hash=" << SERVER_HASH;
    request.setBody(stream.str());
    string ans = perform_request(request);
    if(ans != "") cout << endl << ans << endl;
    else cout << "\n�� ������ ������ ��� ��������� ���\n\n";
    system("pause");
}

int set_name(string &name){
    if(name.size() < MIN_NICK_LENGTH){
        name = "";
        return 3;
    }

    for(unsigned int i = 0; i < name.size(); i++){
        if(!( (name[i] >= 'A' && name[i] <= 'z')
        || (name[i] >= '�' && name[i] <= '�')
        || (name[i] >= '0' && name[i] <= '9') )
        && name[i] != '_' && name[i] != '-' ){
            name = "";
            return 2;
        }
    }

    return 0;
}

void show_online_menu(string name, int error){
    if(error == 1) cout << "������, ������ ������� �� ����������, ��������� ����: ";
    else if(error == 2) cout << "��� �������� ������ �����, �����, _ � -, ��������� ����: ";
    else if(error == 3) cout << "��� ������ �������� �� " << MIN_NICK_LENGTH << " �� " << MAX_NICK_LENGTH << " ����: ";
    else{
        console_clear();
        show_online_intro(name);
    }

    int code = 0;
    string str; cin >> str;

    if(name == "" || str == "set" || str == "���"){
        if(name != "") cin >> str;

        code = set_name(str); name = str;
        show_online_menu(name, code);
        return;
    }else if(str == "create" || str == "�������") create_game(name);
    else if(str == "connect" || str == "����"){
        cin >> str; int gid;
        istringstream mstream(str);
        if(!(mstream >> gid)) gid = 0;
        if(gid > 0) open_connection(name, gid);
    }else if(str == "list" || str == "������") show_game_list();
    else if(str != "exit" && str != "�����") code = 1;

    show_online_menu(name, code);
}

int start_pvp(){
    cout << "��������� ����� ��� ������ �����������: ";
    string str; cin >> str;

    if(s_lower(str) || str.size() < MIN_WORD_LENGTH || str.size() > MAX_WORD_LENGTH){
        cout << "\n��������� ������ ������� ����� � ������ [" << MIN_WORD_LENGTH << ", " << MAX_WORD_LENGTH << "] ����\n";
        return start_pvp();
    }

    return start_game(str);
}

int choose_pvp(){
    cout << "\n�� ������ ������ ���� �� ���������? (��� - offline): ";
    string str; cin >> str;

    if(str[0] == 'y' || str[0] == '�'){
        show_online_menu("", 0);
        return 1;
    }
    return start_pvp();
}

int main(){
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    show_intro();

    string uans;
    while(cin >> uans){
        if(uans == "exit" || uans == "�����") break;
        else if(uans == "pve" || uans == "���"){
            switch(start_pve()){
                case 0: return 0;
                case -1:{
                    cout << "������, �� ������� ������ ����. �������� ����� ��������: ";
                    break;
                }default:{
                    console_clear();
                    show_intro();
                    break;
                }
            }
        }
        else if(uans == "pvp" || uans == "���"){
                if(!choose_pvp()) return 0;
                else{
                    console_clear();
                    show_intro();
                }
        }
        else cout << "������, ��� ������ ���� ������� pve ��� pvp: ";
    }

    return 0;
}
