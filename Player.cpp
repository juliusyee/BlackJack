//
//  Hand.cpp
//  HandHomework
//
//  Created by Howard Stahl on 4/30/15.
//  Copyright (c) 2015 Howard Stahl. All rights reserved.
//

#include "Player.h"
#include <stdexcept>


namespace cs31
{
	Player::Player()
	{
		// The Player has no Cards in his hand
		myNumberOfCards = 0;
	}

	std::ostream& operator <<(std::ostream& outs, const Player & p)
	{
		//print out all the actual cards in the array myCards
		for (int i = 0; i < p.myNumberOfCards; i++)
		{
			outs << p.getCard(i) << "\n";
		}
		return (outs);
	}

	void Player::acceptCard(Card c)
	{
		// as long as there is space, add card to myCards array
		if (myNumberOfCards < MAXCARDS)
		{
			myCards[myNumberOfCards] = c;
			myNumberOfCards++;
		}
		// if hand is full, return error
		else if (myNumberOfCards == MAXCARDS) 
		{
			//throw exception
			std::logic_error e("Max number of cards in hand");
			throw (e);
		}
	}

	Card Player::getCard(int index) const
	{
		Card c;
		if ((index >= 0) && (index < 12)) //check index is within arrray range
		{

			if (index < myNumberOfCards) //check that index matches to an index that actually contains car
			{
				c = myCards[index];
				return (c);
			}
		}
		else //throw an exception
		{
			std::logic_error e("Index was bad!");
			throw (e);
		}
	}

	int  Player::handcount() const
	{
		//Initialize some values
		int total = 0;
		Card c;
		bool multipleAces = false;
		bool isPastAceEleven = false;

		for (int i = 0; i < myNumberOfCards; i++)
		{
			c = myCards[i];
			
			//If first ace card
			if ((c.count() == 1) && (multipleAces == false))
			{
				if (total <= 10) //ace should be 10
				{
					total = total + 11;
					multipleAces = true;
					isPastAceEleven = true;
				}
				else //or else ace should be 1
				{
					total = total + c.count();
					multipleAces = true;
					isPastAceEleven = false;
				}
			}
			
			// if card is ace but there are previous aces
			else if ((c.count() == 1) && (multipleAces == true))
			{
				//if added ace causes a bust, change its value to 1
				if ((total + c.count() > 21) && (isPastAceEleven == true))
				{
					total = total + c.count() - 10;
					isPastAceEleven = false;
				}
				else
				{
					//Add new card  and simply add its blackjack vale
					total = total + c.count();
				}
			}
			//add card not ace and there are no prior aces
			else if ((c.count() != 1) && (multipleAces == false))
			{
				total = total + c.count();
			}
			//add non-ace card and hand already has an ace
			else if ((c.count() != 1) && (multipleAces == true))
			{
				//if past ace is 11 and adding one more ace makes you bust, change 11 to 1
				if ((total + c.count() > 21) && (isPastAceEleven == true))
				{
					total = total + c.count() - 10;
					isPastAceEleven = false;
				}
				else
				{
					total = total + c.count();
				}
			}
		}
		return(total);
	}

	int Player::cardCount() const
	{
		int total = 0;
		total = myNumberOfCards;
		return (total);
	}


	bool Player::hasBlackJack() const
	{
		bool result = false;
		if (myNumberOfCards == 2 && handcount() == 21)
		{
			result = true;
		}
		return(result);
	}
}