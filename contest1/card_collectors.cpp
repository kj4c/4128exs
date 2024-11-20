#include <unordered_map>
#include <iostream>
using namespace std;

int main() {
    unordered_map<int, int> umap;
    int num_friends;
    int num_cards;
    cin >> num_friends;
    cin >> num_cards;

    for (int i = 1; i <= num_cards; i++) {
        umap[i] = 0;
    }

    for (int i = 0; i < num_friends; i++) {
        int total_cards;
        cin >> total_cards;

        for (int j = 0; j < total_cards; j++) {
            int curr_card;
            cin >> curr_card;
            umap[curr_card] = umap[curr_card] + 1;
        }
    }

    int min = 0;
    if (!umap.empty()) {
        auto first_card = umap.begin();
        min = first_card->second;
    }
    for (const auto& pair : umap) {
        if (min > pair.second) {
            min = pair.second;
        }
    }
    cout << min << endl;
    return 0;
}