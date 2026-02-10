#include <stdio.h>
#include <stdlib.h>
#include "deck.h"

const char* ANSI_RESET = "\033[0m";
const char* ANSI_RED = "\033[31m";
const char* ANSI_BLACK = "\033[30m";
const char* ANSI_BACK = "\033[47m";

const char* suits[] = {"♠", "♣", "♦", "♥"};
const char* ranks[] = {
    "i", "A", "2", "3", "4", "5", "6", "7", "8", "9", "T", "J", "Q", "K", "A" 
};

void print_card(const Card* card) {
    const char* color_code = color(card) == RED ? ANSI_RED : ANSI_BLACK;
    printf("%s%s%s%s%s", ANSI_BACK, color_code, ranks[card->rank], suits[card->suit], ANSI_RESET);
}

void print_deck(const Deck* deck) {
    for(int i = 0; i < deck->top; ++i) {
        print_card(&deck->cards[i]);
        printf(i == deck->top - 1 ? "\n" : " ");
    }
}

void print_discard_pile(const Deck* deck) {
    for(int i = deck->top; i < 52; ++i) {
        print_card(&deck->cards[i]);
        printf(i == 51 ? "\n" : " ");
    }
}

void init_deck(Deck* deck) {
    deck->top = 52;
    for(int i = 0; i < 4; ++i) {
        for(int j = 0; j < 13; ++j) {
            deck->cards[13 * i + j] = (Card){.suit = i, .rank = j + 2};
        }
    }
}

void shuffle(Deck* deck) {
    deck->top = 52;
    for(int i = 0; i < 52; ++i) {
        int j = rand() % 52;
        Card temp = deck->cards[i];
        deck->cards[i] = deck->cards[j];
        deck->cards[j] = temp;
    }
}

Card draw(Deck* deck) {
    if(deck->top == 0) {
        fprintf(stderr, "No more cards in the deck!\n");
        exit(EXIT_FAILURE);
    }
    return deck->cards[--deck->top];
}

void add_bottom(Deck* deck, const Card* card) {
    if(deck->top >= 52) {
        fprintf(stderr, "Deck is full, cannot add more cards!\n");
        exit(EXIT_FAILURE);
    }
    for(int i = deck->top; i > 0; --i) {
        deck->cards[i] = deck->cards[i - 1];
    }
    deck->cards[0] = *card;
    deck->top++;
}

void remove_card(Deck* deck, const Card* card) {
    for(int i = 0; i < deck->top; ++i) {
        if(deck->cards[i].suit == card->suit && deck->cards[i].rank == card->rank) {
            Card temp = deck->cards[i];
            deck->cards[i] = deck->cards[--deck->top];
            deck->cards[deck->top] = temp;
            return;
        }
    }
}
