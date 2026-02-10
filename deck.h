#ifndef DECK_H
#define DECK_H

typedef enum {
    SPADES, CLUBS,
    DIAMONDS, HEARTS
} Suit;

#ifdef A14
typedef enum {
    J = 11, Q, K, A
} Rank;
#else
typedef enum {
    A = 1, J = 11, Q, K
} Rank;
#endif

typedef enum {
    BLACK, RED
} Color;

typedef struct {
    Suit suit;
    Rank rank;
} Card;

typedef struct {
    Card cards[52];
    int top; // Cards above top is the discard pile
} Deck;

static inline Color color(const Card* card) { return card->suit < DIAMONDS ? BLACK : RED; }

void print_card(const Card* card);
void print_deck(const Deck* deck);
void print_discard_pile(const Deck* deck);

void init_deck(Deck* deck);
void shuffle(Deck* deck);
Card draw(Deck* deck);
void add_bottom(Deck* deck, const Card* card);

static inline int deck_size(const Deck* deck) { return deck->top; }
static inline int is_empty(const Deck* deck) { return deck->top == 0; }

void remove_card(Deck* deck, const Card* card);

#endif // DECK_H
