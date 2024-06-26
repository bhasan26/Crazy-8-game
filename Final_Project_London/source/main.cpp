
//sources/copyright: Introduction to Programming with c++, Y. Daniel Lang
////////////////////////
#include <iostream>
#include <algorithm>
#include <iterator>
#include <ctime>
using namespace std;

//initiealizing constants
const int INITIAL_CARDS = 52; // in the beginning of the game
const string suits[4] = {"Spades", "Hearts", "Diamonds", "Clubs"};
const string ranks[13] = {"Ace", "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King"}; 

//
//
// defining class Deck
// deck can be populated and hold all the cards, can shuffle cards, allows cards to be removed or added 
class Deck{
  /// Attributes
  public:
        int number_of_cards; //keeps track of the amount of cards in the deck
        int decks[INITIAL_CARDS]; //make a deck list out of just numbers that helps us shuffle the deck
        string full_deck[INITIAL_CARDS]; //holds all the cards as strings in the deck
        string name; //name to be used as an identifier(mostly for the user decks)
       

  ///////////// Data field

      // Constructing the deck of cards (Default) 
      Deck(){ 
        name = " "; //no name
        number_of_cards = INITIAL_CARDS; //makes number of cards 52
        for (int i = 0; i < number_of_cards; i++){ //runs through the whole deck assigning numbers to indices
          decks[i] = i;
        }  
      }

      // Non default constructor
      //takes in a specified amount of cards, a unique name, and the placeholder that the deck will be filled with
      Deck(int numCards, string placeholder, string playerName) {
        name = playerName;
        number_of_cards = numCards;
        //fills the deck full of whatever placeholder is chosen
        for (int i = 0; i < INITIAL_CARDS; i++){
          full_deck[i] = placeholder;
        }
      }
      ///// when we remove cards from deck


      // Shuffle behaviour
      //
      // shuffles deck of 52 cards randomly
      void shuffle (){
        for (int i = 0; i < number_of_cards; i++){
            // Generate an index randomly
            int index = rand() % number_of_cards;
            int temp = decks[i];
            decks[i] = decks[index];
            decks[index] = temp;
        }
      }
      // fill the deck with cards
      void populate_deck (){
        for (int i = 0; i < 52; i++){
          string suit = suits[decks[i] / 13];
          string rank = ranks[decks[i] % 13];
          full_deck[i] = rank + " of " + suit;
          }
      }
      
    //
    //
    //remove card function, manipulates array to remove a card after the user plays it from their hand
    //input: which players hand, and what card they played
    //void remCard(string player[], string card);
    void remCard(string deck[INITIAL_CARDS], string card){
      for(int i = 0; i < INITIAL_CARDS; i++){
        if(card == deck[i]){
          deck[i] = " ";
        }
      }
  number_of_cards--;
  }

//
//
//
    //behaviour that adds card to a deck
    void addCard(string deck[INITIAL_CARDS], string card){
        int temp = 1;
        
         for (int i = 0; i < INITIAL_CARDS; i++){//runs through every slot in the deck
            if(deck[i] == " " and temp == 1){//checks to see if the slot is empty and if temp still equals one (if temp = 0 that means the card has already been added)
                deck[i] = card;//the card is added and temp is decreased
                temp--;
            } 
         }
         if (temp == 1){ //if a card never gets added to the deck it should trigger this error
            cout << endl << "Error---Deck Full!" << endl;
         }else {
            number_of_cards++;
         }
    }  

//
//
//behaviour that arranges the deck so that all the indices with actual cards are in front of all the indices with " "
void arrangeDeck(){
  string tempHolder;
  for(int i = 0; i < INITIAL_CARDS; i++){ //iterates through the whole deck 
    int temp = 1;
    if(full_deck[i] == " "){ //if an empty space is found
      for(int x = i; x < INITIAL_CARDS; x++){ //iterate through the deck starting from the empty space
        if(full_deck[x] != " " and temp == 1){ //if it finds a card and temp has a value of 1
          full_deck[i] = full_deck[x];//the space will now equal the card
          full_deck[x] = " ";//the old card will equal a space
          temp--; //make temp 0 so it only happens once per empty space
        }
      }
    }
  }
}  
};


//remove card function, manipulates array to remove a card after the user plays it from their hand
//input: which players hand, and what card they played
//void remCard(string player[], string card);

//function that takes cards from a main deck and deals 8 cards to each players hand
//inputs: a main deck to take the cards from, 2 player decks that need cards added to them
void dealCards(Deck& mainDeck, Deck& playerDeck1, Deck& playerDeck2);

//
//
// draws a card from the main deck, removes that card from main, then adds that card to desired players hand
void drawCard(Deck& mainDeck, Deck& playerDeck);

//
//
// drawCardx2
void draw2Cards(Deck& mainDeck, Deck& playerDeck);

//
//
// removes card from players hand and adds it to the pile
void playCard(Deck& playerDeck, Deck& pile, string card);

//
//
// simulates one turn, cout the cards in players hand, takes user input to get what card they want to play, plays that card
void sim1Turn(Deck& player, Deck& main, Deck& pile);

//
//
// checks to see if the suits of two cards match
bool isMatchingSuit(string card, string currCard);

//
//
// checks to see if the rank of two cards match
bool isMatchingRank(string card, string currCard);

//
//
// checks to see if the rank of the card is 8
bool isEight(string card);

//
//
// checks to see if the rank of the card is 2
bool isTwo(string card);

//
//
// checks to see if the card is a jack, which is the skip card
bool isSkip(string card);

//
//
// checks to see if the card either an 8, 2, or Jack
bool isSpecial(string card);

//
//
// checks to see if the card can be played on current card
bool checkCards(string card, string currCard);

//
//
// checks to see if the player is out of cards(they have won)
bool isWinner(int playerCards);

int main() {
  srand(time(NULL));

//initiallizing decks
Deck main; //main deck, this will be the deck we deal cards and draw from
main.shuffle();
main.populate_deck();

//initializing player hands
Deck player1(0, " ", " ");

Deck player2(0, " ", " ");

//initialize pile which will be the pile that gets played on by the players
Deck pile(-1, " ", "pile");



//introducing the game and getting player names
char startCon = 'a';

while (startCon == 'a') {

//printing rules and introduction
cout << "Welcome to Crazy 8!" << endl;
cout << "Here are the rules: " << endl;
cout << "The goal of the game is to run out of cards, you can only play cards that match either suit or rank of the top card." << endl;
cout << "8's are wild cards and can be played whenever, 2's make the opponent draw 2 cards, Jack's skip opponents turn." << endl;
cout << "Have Fun!!" << endl;

//getting player names for users
cout << endl;
cout << "Enter player 1's name: ";
cin >> player1.name;

cout <<"Enter player 2's name: ";
cin >> player2.name;

cout << endl;
cout << "Enter any key to start!(except for '.') ";
cin >> startCon;
//initializing variables, currCount
if (startCon != '.'){
  int curr_count = (rand() % 2) + 1;
  int curr2Count = 0;
  int temp2Count = 0;
//need to deal cards before game starts
  dealCards(main,player1,player2);
//creating the top card of the pile
  main.arrangeDeck();
  int tempForPile = 1;
  for(int i = 0; i < INITIAL_CARDS; i++){ //runs through the whole deck
    if(!isSpecial(main.full_deck[i]) and tempForPile == 1){ //if isSpecial returns false and temp still == 1, play the card into pile
      playCard(main, pile, main.full_deck[i]);
      tempForPile--;
    }
  }
//while all players still have cards in their hands game will run
  while((isWinner(player1.number_of_cards)) == false and (isWinner(player2.number_of_cards) == false)){
    cout << endl;
    string currCard;
    string lastCard;
    
    if(curr_count == 1){//determining whose turn it is
      cout << endl << "The current card is: " << pile.full_deck[pile.number_of_cards] << endl;
      sim1Turn(player1, pile, main);
      // checking if draw two or skip has been played and responding accordingly
      currCard = pile.full_deck[pile.number_of_cards]; //this is part of the solution for the tutu problem
      lastCard = pile.full_deck[pile.number_of_cards-1]; //this is part of the solution for part of the tutu problem
      if((currCard[0]!= '2') and (lastCard[0] == '2')){ //checks if the card has changed from a 2 to something else or a 2 was played on a 2
        temp2Count++;
      }
      if(isTwo(pile.full_deck[pile.number_of_cards]) and (curr2Count == temp2Count)){ //checks if draw two has been played last
        draw2Cards(main, player2); //calls special card function to add 2 cards to opposing player
        curr2Count++;
        cout << player2.name << " drew 2 cards!" << endl;
      }else if((currCard[0] == '2' and lastCard[0] == '2') and (curr2Count != temp2Count)){
        draw2Cards(main, player2);
        curr2Count++;
        cout << player2.name << " drew 2 cards!" << endl;
      }
      if(isSkip(pile.full_deck[pile.number_of_cards]) == false){
        curr_count = 2;
      } else{
        cout << player2.name << " got skipped!" << endl;
      }

    } else{
      cout << endl << "The current card is: " << pile.full_deck[pile.number_of_cards] << endl;
      sim1Turn(player2, pile, main);
      currCard = pile.full_deck[pile.number_of_cards];
      lastCard = pile.full_deck[pile.number_of_cards-1];
      if((currCard[0]!= '2') and (lastCard[0] == '2')){ //checks if the card has changed from a 2 to something else or a 2 was played on a 2
        temp2Count++;
      }
      if(isTwo(pile.full_deck[pile.number_of_cards]) and (curr2Count == temp2Count)){
        draw2Cards(main, player1);
        curr2Count++;
        cout << player1.name << " drew 2 cards!" << endl;
      } else if((currCard[0] == '2' and lastCard[0] == '2') and (curr2Count != temp2Count)){
        draw2Cards(main, player1);
        curr2Count++;
        cout << player1.name << " drew 2 cards!" << endl;
      }

      if(isSkip(pile.full_deck[pile.number_of_cards]) == false){
        curr_count = 1;
      } else{
        cout << player1.name << " got skipped!" << endl;
      }
    }
  
  //refilling main once it runs out of cards
  if(main.number_of_cards == 0){
  for(int i = 0; i < pile.number_of_cards; i++){
    main.full_deck[i] = pile.full_deck[i]; //fills main with all the cards in the pile
  }
  main.number_of_cards = pile.number_of_cards + 1; //resets mains number of cards to the right amount
  pile.arrangeDeck(); //
  pile.number_of_cards = 1;
  }

} // end of while loop that runs game
}
  //Examines player with no cards showcasing victory screen
  if(isWinner(player1.number_of_cards)){
    cout << endl;
    cout << endl;
    cout << "Congratulations " << player1.name << "! You have won!!  -You still don't get a breakfast burrito though :(" << endl;
    } else {
    cout << endl;
    cout << endl;
    cout << "Congratulations " << player2.name << "! You have won!!  -You still don't get a breakfast burrito though :(" << endl;
    }
    //Optional replayable feature 
    cout<<" Do you want to play again? \na) yes       b) no";
    cout << endl;
    
    cin >> startCon;
    
    if (startCon == 'b') {
        cout << "Thank you for playing the Game of Crazy Eight!" << endl;
        cout << "A JCM production" << endl;
} 

} // end of second while that ask if the player wants to play again


} // end of int main

//
//      
// dealCards function
void dealCards(Deck& mainDeck, Deck& playerDeck1, Deck& playerDeck2){
    // Player 1
    for (int i = 0; i < 8; i++){
        playerDeck1.addCard(playerDeck1.full_deck, mainDeck.full_deck[i]);
        mainDeck.remCard(mainDeck.full_deck, mainDeck.full_deck[i]);
    }

    // Player 2
    for (int i = 8; i < 16; i++){
        playerDeck2.addCard(playerDeck2.full_deck, mainDeck.full_deck[i]);
        mainDeck.remCard(mainDeck.full_deck, mainDeck.full_deck[i]);
    }
    return;
}

//
//
//
// Removes card from deck adding to players hand 
void drawCard(Deck& mainDeck, Deck& playerDeck){
  int temp = 1;
  for (int i = 0; i < INITIAL_CARDS; i++){
    if ((temp == 1) and (mainDeck.full_deck[i] != " ")){
      playerDeck.addCard(playerDeck.full_deck, mainDeck.full_deck[i]);
      mainDeck.remCard(mainDeck.full_deck, mainDeck.full_deck[i]);
      temp--;
    }
  }
  return;
}

//
//
//Special card that adds more cards to opposing player
void draw2Cards(Deck& mainDeck, Deck& playerDeck){
  for(int i = 0; i < 2; i++){
    drawCard(mainDeck, playerDeck);
  }
  return;
}

//
//
//Adds card to pile and removes card from hand
void playCard(Deck& playerDeck, Deck& pile, string card){
  pile.addCard(pile.full_deck, card);
  playerDeck.remCard(playerDeck.full_deck, card);
  }

//
//
//Checks to see if suits of pile match with chosen hand before replacing pile with hand card
bool isMatchingSuit(string card, string currCard){
  //Initializing placement holder for card and currcard
  string card1 = card;
  string card2 = currCard; 
    //Extracting length of card to use as a letter location indicator
    int endcard1 = card1.length();
    int endcard2 = card2.length();
    int posf1, posf2;
    string suit1, suit2;
    //Ignores letters prior to "of" to obtain suit letters
    for (int i = 0; i < endcard1; i++) {
        if (card1[i] == 'f'){
          posf1 = i;
        }
      }
      
    for (int i = 0; i < endcard2; i++) {
        if (card2[i] == 'f'){
          posf2 = i;
        }
      } 
//Combines the letters from previous for loop into a single string
  for (int x = posf1 + 2; x < endcard1;x++) {
    suit1 = suit1 + card1[x];
  }
  
  for (int x = posf2 + 2; x < endcard2;x++) {
    suit2 = suit2 + card2[x];
  }
  
// Compares values to determine if they are equal
  if (suit1 == suit2) {
    return true;
  } else {
    return false;
  }
}

//
//
// Similar to Suit but comparing rank
bool isMatchingRank(string card, string currCard){
  char user_card, curr_card;
//only using 0 in array space for rank
  user_card = card[0];
  curr_card = currCard[0];
//compares rank of hand and pile
  if (user_card == curr_card){
    return true;
  } else{
    return false;
  }
}

//
//
// checks if the card is an 8, which is the wild card
bool isEight(string card){
  char fChar;
  fChar = card[0];

  if(fChar == '8'){
    return true;
  } else {
    return false;
  }
}

//
//
// Checks if the card is playable on the current card
bool checkCards (string card, string currCard) {
  if(isMatchingRank(card, currCard) || isMatchingSuit(card, currCard) || (isEight(card))){
    return true;
  } else {
    return false;
  }
}

//
//
// checks if the players number of cards is at 0, which is the win condition
bool isWinner(int playerCards){
  if(playerCards == 0){
    return true;
  } else{
    return false;
  }
}

//
//
// simulates one round in the game, takes in which player's turn it is, and plays one round
void sim1Turn(Deck& player, Deck& pile, Deck& main){
  player.arrangeDeck();
  int playerChoice;
//Display choice and card options
  cout << player.name << " it is your turn! Here is your hand: " << endl;
  for (int i = 0; i < INITIAL_CARDS; i++){
    if(player.full_deck[i] != " "){
      cout << "Card " << i + 1 << ": " << player.full_deck[i] << endl;
    }
  }
//Provokes for user input 
  cout << "Which card would you like to play? If you want to draw a card instead enter 0: ";
  cin >> playerChoice;
  playerChoice--;
  cout << endl;
  if(playerChoice == -1){
          drawCard(main, player);
  } else{
    if (checkCards(player.full_deck[playerChoice], pile.full_deck[pile.number_of_cards])){
      playCard(player, pile, player.full_deck[playerChoice]);
    } else{
      cout << "Oops! Can't play that card, you draw a card instead!" << endl << endl;
      drawCard(main, player);
    }
  return;
  }
}

//
//
// takes in a card and checks if it is a 2
bool isTwo(string card){
  char fChar;
  fChar = card[0];

  if(fChar == '2'){
    return true;
  } else {
    return false;
  }
}

//
//
// takes in a card and checks if it is a jack
bool isSkip(string card){
  char fChar;
  fChar = card[0];

  if(fChar == 'J'){
    return true;
  } else {
    return false;
  }
}

//
//
// checks if the card is a jack, 2, or 8
bool isSpecial(string card){
  if(isEight(card) || isTwo(card) || isSkip(card)){
    return true;
  } else{
    return false;
  }
}