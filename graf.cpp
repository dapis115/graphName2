#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

class SocialGraph {
private:
    map<string, set<string>> friends;

public:
    void addFriendship(const string& person1, const string& person2) {
        friends[person1].insert(person2);
        friends[person2].insert(person1);
    }

    bool areFriends(const string& person1, const string& person2) {
        return friends[person1].count(person2) > 0;
    }

    vector<string> getAllPeople() {
        vector<string> people;
        for (const auto& entry : friends) {
            people.push_back(entry.first);
        }
        return people;
    }

    vector<pair<string, string>> findThreeHandshakes() {
        vector<pair<string, string>> result;
        vector<string> people = getAllPeople();

        for (size_t i = 0; i < people.size(); ++i) {
            for (size_t j = i + 1; j < people.size(); ++j) {
                const string& person1 = people[i];
                const string& person2 = people[j];

                if (areFriends(person1, person2)) continue;

                // Проверяем все пути длиной 3
                for (const string& friend1 : friends[person1]) {
                    for (const string& friend2 : friends[friend1]) {
                        if (friend2 == person1) continue;

                        for (const string& friend3 : friends[friend2]) {
                            if (friend3 == person2) {
                                result.emplace_back(person1, person2);
                                goto next_pair;
                            }
                        }
                    }
                }
            next_pair:;
            }
        }

        return result;
    }
};

int main() {
    SocialGraph graph;

    // Добавляем связи между людьми (пример)
    graph.addFriendship("Настя", "Олег");
    graph.addFriendship("Олег", "Женя");
    graph.addFriendship("Женя", "Никита");
    graph.addFriendship("Никита", "Ваня");
    graph.addFriendship("Ваня", "Настя");

    // Находим пары, знакомые через три рукопожатия
    auto pairs = graph.findThreeHandshakes();

    // Выводим результат
    cout << "Пары, знакомые через три рукопожатия:\n";
    for (const auto& pair : pairs) {
        cout << pair.first << " и " << pair.second << endl;
    }

    return 0;
}