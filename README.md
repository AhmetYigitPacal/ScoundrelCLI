# Scoundrel CLI (A Single Player Rouge-like Card Game in CLI)
A terminal based implementation of Scoundrel, a popular solo card game played with a standart 52-card deck. This project is written in C and designed to be lightweight, fast, and playable entirely from the command line.

## About the Game
Scoundrel is a single player, rouge-like dungeon-crawling card game created by Zach Gage and Kurt Bieg. You explore a deck of cards room by room, fighting monsters, looting weapons, and managing your health. This project focuses on faithfully recreating the core mechanics of the game completely in command-line interface.

## How to Play
Scondrel is played with a standart deck of playing cards with Red Face Cards and Red Aces removed. Your goal is to survive in the dungeon by clearing all the cards in the deck without your health reaching zero. You start with 20 health points and face the dungeon one room at a time.

### Rules
- The 26 **Clubs** and **Spades** in the deck are **Monsters**. Their damage is equal to their ordered value (T is 10, J is 11, Q is 12, K is 13 and A is 14).
- The 9 **Diamonds** in the deck are **Weapons**. Each weapon does as much damage as its value. All weapons in Scoundrel are binding, meaning if you pick one up, you equip it, and discard your previous weapon.
- The 9 **Hearts** int the deck are **Health Potions**. You may only use one health potion each turn, even if you pull two. The second potion you pull is simply discarded. You may not restore your life beyond your starting 20 health.
### Gameplay
There are 4 cards dealt for each **Room**. You may avoid the room by typing 'r'. If you choose to do so, the cards in the room are placed on the bottom of the deck and a new room is drawn. You can avoid as many Rooms as you like, but you cannot avoid two rooms in a row.  
If you choose not to avoid the room, one by one you must face 3 of the 4 cards it contains by typing the index of the card (1-4).
- If you choose a **Weapon**:  
The weapon will be equipped, and the previous weapon will be discarded.
- If you choose a **Health Potion**:  
Its number will be added to your health and will be discarded. Your health cannot exceed 20, and you cannot use more than one health potion per turn. If you choose two health potions in a turn the second one will simply be discarded, without healing you.
- If you choose a **Monster**:  
You can either fight with your *weapon* or can fight *barehanded* by adding a b next to your choice (for example: 2b).  
    - If you choose to fight the monster *barehanded*, its value will be substracted from your health and the card will be discarded.
    - If you choose to fight the monster with your equipped *weapon*, its value will be substracted from your equipped weapon and the remaining value will be substracted from your health. The card will be put on top of your weapon. You will retain your weapon however the weapon can then only be used against monsters of a *lower value (less than equal)* than the previous monster it had slain.
Once you have chosen 3 cards, your turn is complete. The fourth card is untouched and a new room will be drawn.
You can also refer to [Scoundrel Manual](http://www.stfj.net/art/2011/Scoundrel.pdf)
 
## Build and Run
### Requirements
- A C Compiler (GCC recommended)
### Compile
`gcc -Wall -Wextra -o scoundrel main.c deck.c`
### Run
`./scoundrel`

## Acknowledgements
Original game by Zach Gage and Kurt Bieg
