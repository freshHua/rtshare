
#include <iostream>
#include "tv.h"

int main()
{
	using  std::cout;
	Tv s27;
	cout << "Initial Setting for 27\" TV:\n";
	s27.setting();
	s27.onoff();
	s27.chanup();
	cout <<"\nAjusted Setting for 27\" TV:\n";
	s27.setting();

	Remote grep;
	grep.set_chan(s27,10);
	grep.volup(s27);
	grep.volup(s27);
	cout<<"\n27\" settings after remote :\n";
	s27.setting();

	Tv s32(Tv::On);
	s32.set_mode();
	grep.set_chan(s32,28);
	cout << "\n32\" settings:\n";
	s32.setting();
	return 0;
}