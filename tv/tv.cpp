#include <iostream>

#include "tv.h"


bool Tv::volup() {
	if (volume < MaxVal) {
		volume++;
		return true;
	} else {
		return false;
	}

}
bool Tv::voldown() {
	if (volume > MinVal) {
		volume--;
		return true;
	} else {
		return false;
	}

}
void Tv::chanup()
{
	if (channel < maxchannel) {
		channel++;
	} else {
		channel = 1 ;
	}

}
void Tv::chandown()
{
	if ( channel  > 1) {
		channel--;
	} else {
		channel = maxchannel;
	}
}


void Tv::setting() const
{
	using  std::cout;
	using  std:: endl;
	cout << "TV is " << ( (state == On) ? "On" : "Off") << endl;
	if (state == On)
	{
		cout << "Volume Setting = " << volume << endl;
		cout << "Channel Setting = " << channel << endl;
		cout << "Mode = " << (( mode == Antenna) ? "Antenna" : "Cable" ) << endl;
		cout << "Input = " << ((input == TV) ? "TV" : "VCR") << endl;
	}

}