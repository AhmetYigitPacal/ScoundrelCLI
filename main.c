#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define A14
#include "deck.h"

int main() {
    Deck deck;
    init_deck(&deck);
    srand(time(NULL));
    shuffle(&deck);

    // Remove red face cards and aces
    for(int s = DIAMONDS; s <= HEARTS; ++s) {
        for(int r = J; r <= A; ++r) {
            Card card = { .suit = s, .rank = r };
            remove_card(&deck, &card);
        }
    }

    int health = 20;
    Card dungeon[4]; int valid[4] = {0};
    Card weapon = { .suit = DIAMONDS, .rank = 0 };
    Card defeated = { .suit = SPADES, .rank = 15 };
    int can_run = 1;
    int started = 0;
    int healed = 0;

    for(int i = 0; i < 4; ++i) {
        dungeon[i] = draw(&deck);
        valid[i] = 1;
    }
    
    while(!is_empty(&deck) && health > 0) {
        // Check if the room is cleared
        int c = 0;
        for(int i = 0; i < 4; ++i) {
            if(!valid[i]) ++c;
        }
        if(c == 3) { // Replace the cleared room
            if(is_empty(&deck)) break;
            for(int i = 0; i < 4; ++i) {
                if(!valid[i]) {
                    if(is_empty(&deck)) break;
                    dungeon[i] = draw(&deck);
                    valid[i] = 1;
                }
            }
            started = 0;
            healed = 0;
        }

        // Print status
        printf("\n=========== Status ===========\n");
        printf("Health: %d\n", health);
        printf("Weapon: ");
        if(weapon.rank) {
            print_card(&weapon);
            printf(" ");
            if(defeated.rank < 15) print_card(&defeated);
        } else { 
            printf("None");
        }
        printf("\n");
        printf("Room: ");
        for(int i = 0; i < 4; ++i) {
            if(valid[i]) print_card(&dungeon[i]);
            else printf("  ");
            printf(i == 3 ? "\n" : " ");
        }
        if(can_run) printf("Run available\n");
        else if(!started) printf("Run used\n");
        printf("Remaining cards: %d\n", deck.top);
        printf("==============================\n\n");

choose_again:
        printf("Choose a card to interact (1-4), 'r' to avoid the room, 'q' to quit: ");
        char s[4];
        scanf("%s", s);
        int choice = atoi(s);
        if(!(choice > 0 && choice <= 4 && valid[choice - 1]) && s[0] != 'r' && s[0] != 'q') {
            printf("Invalid choice!\n");
            goto choose_again;
        }

        // Quit the game
        if(s[0] == 'q') {
            printf("Quitting the game.\n");
            exit(EXIT_SUCCESS);
        }

        // Avoid the room
        if(s[0] == 'r') {
            if(can_run && !started) {
                for(int i = 0; i < 4; ++i) {
                    add_bottom(&deck, &dungeon[i]);
                    if(is_empty(&deck)) break;
                    dungeon[i] = draw(&deck);
                }
                can_run = 0;
                started = 0;
                healed = 0;
                printf("You avoided the room!\n");
            } else {
                printf("You cannot run!\n");
                goto choose_again;
            }
            continue;
        }
        can_run = 1;
        started = 1;

        Card chosen = dungeon[choice - 1];
        valid[choice - 1] = 0;

        switch(chosen.suit) {
        case SPADES: case CLUBS: // Monster
            if(weapon.suit && chosen.rank <= defeated.rank && s[1] != 'b') {
                health -= (chosen.rank > weapon.rank) ? (chosen.rank - weapon.rank) : 0;
                defeated = chosen;
                printf("You fought the monster and lost %d health!\n", 
                    (chosen.rank > weapon.rank) ? (chosen.rank - weapon.rank) : 0);
            } else {
                health -= chosen.rank;
                printf("You fought the monster and lost %d health!\n", chosen.rank);
            }
            
            break;

        case DIAMONDS: // Weapon
            weapon = chosen;
            defeated = (Card){ .suit = SPADES, .rank = 15 };
            printf("You found a weapon!\n");
            break;

        case HEARTS: // Potion
            if(healed) {
                printf("You have already used a potion!\n");
                break;
            }
            health += (int)chosen.rank;
            health = health > 20 ? 20 : health;
            healed = 1;
            printf("You drank a potion and healed %d health!\n", (int)chosen.rank);
            break;
        }
    }

    printf("\n========= Game Over ==========\n");
    if(health > 0) {
        printf("You have cleared the dungeon!\n");
        printf("Your score: %d\n", health + (deck.cards[0].suit == HEARTS ? deck.cards[0].rank : 0));
    } else {
        printf("You have been defeated in the dungeon!\n");
        int score = 0;
        for(int i = 0; i < deck.top; ++i) {
            if(deck.cards[i].suit == SPADES || deck.cards[i].suit == CLUBS) {
                score -= deck.cards[i].rank;
            }
        }
        printf("Your score: %d\n", score);
    }
    printf("==============================\n");

    return 0;
}