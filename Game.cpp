//
//  Game.cpp
//  HandHomework
//
//  Created by Howard Stahl on 12/6/15.
//  Copyright © 2015 Howard Stahl. All rights reserved.
//

#include "Game.h"
#include <iostream>

namespace cs31
{

	Game::Game(): mOutcome(NOOUTCOME), mPlayerStood(false)
	{
		//constructor
	}

	Game::Game(Player player, Player dealer)
	{
		//constructor
		mPlayer = player;
		mDealer = dealer;
		mOutcome = NOOUTCOME;
		mPlayerStood = false;
	}

	// did the Player win?
	bool Game::playerWon()
	{
		return(mOutcome == PLAYERWON);
	}

	// did the Player lose?
	bool Game::playerLost()
	{
		return(mOutcome == PLAYERLOST);
	}

	// did the Player and the Dealer tie?
	bool Game::playerTied()
	{
		return(mOutcome == TIED);
	}

	void Game::deal()
	{
		//First shuffle the deck
		mDeck.shuffleDeck();

		//Deal two cards 
		Card c1;
		c1 = mDeck.dealCard();
		Card c2;
		c2 = mDeck.dealCard();

		//Player accepts both cards
		mPlayer.acceptCard(c1);
		mPlayer.acceptCard(c2);

		//Deal two more cards
		Card c3;
		c3 = mDeck.dealCard();
		Card c4;
		c4 = mDeck.dealCard();

		//Dealer accepts both cards
		mDealer.acceptCard(c3);
		mDealer.acceptCard(c4);
	}

	void Game::playerHits()
	{
		//Deal another card to the player
		Card c5;
		c5 = mDeck.dealCard();
		mPlayer.acceptCard(c5);
		
	}

	// let the Game know that the Player's turn is over
	void Game::playerStands()
	{
		mPlayerStood = true;
	}

	// has the Player's turn ended?
	bool Game::playerStood() const
	{
		return(mPlayerStood);
	}

	void Game::dealerHits()
	{
		//Deal another card to the dealer
		Card c6;
		c6 = mDeck.dealCard();
		mDealer.acceptCard(c6);
	}

	void Game::dealerStands()
	{
		//If dealer busts and player doesn't bust
		if (dealerBusted() && !playerBusted())
		{
			mOutcome = PLAYERWON;
		}
		//if player busts
		else if (playerBusted())
		{
			mOutcome = PLAYERLOST;
		}
		//if player's hand is greater than dealer's
		else if (mPlayer.handcount() > mDealer.handcount())
		{
			mOutcome = PLAYERWON;
		}
		//if dealer's hand is greater than player's
		else if (mPlayer.handcount() < mDealer.handcount())
		{
			mOutcome = PLAYERLOST;
		}
		//if player and dealer's hands are equal
		else if (mPlayer.handcount() == mDealer.handcount())
		{
			mOutcome = TIED;
		}

	}

	bool Game::dealerBusted() const
	{
		bool result = false;

		//if dealer's hand is greater than 21 --> bust
		if (mDealer.handcount() > 21)
		{
			result = true;
		}

		return(result);
	}

	bool Game::playerBusted() const
	{
		bool result = false;

		//if player's hand is greater than 21 --> bust
		if (mPlayer.handcount() > 21)
		{
			result = true;
		}

		return(result);
	}

	void Game::dealerPlays()
	{
		//dealer will deal and accept a card as long as his/her hand is less than 17
		while (mDealer.handcount() < 17)
		{
			Card c7;
			c7 = mDeck.dealCard();
			mDealer.acceptCard(c7);
		}

		// let the Game know that play has ended
		dealerStands();
	}

	bool Game::playerHasBlackJack() const
	{
		bool result = false;

		//if player has blackjack
		if (mPlayer.hasBlackJack())
		{
			result = true;
		}

		return(result);
	}

	bool Game::dealerHasBlackJack() const
	{
		bool result = false;

		//if dealer has blackjack
		if (mDealer.hasBlackJack())
		{
			result = true;
		}

		return(result);
	}

	//
	// ALL THE CODE BELOW THIS POINT SHOULD NOT BE CHANGED!
	//
	void Game::display(std::string s, bool allCards)
	{
		// when allCards is true  --> show all dealer cards
		// otherwise just show the one turned up dealer card
		// and then display the passed message at the bottom of the screen, if supplied
		using namespace std;
		int dealerCount = mDealer.handcount();
		int playerCount = mPlayer.handcount();
		cout << "DEALER'S HAND:" << endl;
		if (allCards)
		{
			cout << mDealer << endl;
		}
		else
		{
			cout << mDealer.getCard(0) << endl;
		}
		if (dealerBusted())
		{
			cout << "          --->dealer busted!" << endl;
		}
		else if (allCards)
		{
			cout << "          --->" << dealerCount << endl;
		}
		cout << endl;
		cout << "PLAYER'S HAND:" << endl;
		cout << mPlayer << endl;
		if (playerBusted())
		{
			cout << "          --->player busted!" << endl;
		}
		else if (allCards)
		{
			cout << "          --->" << playerCount << endl;
		}

		if (s != "")
			cout << s << endl;
	}
}