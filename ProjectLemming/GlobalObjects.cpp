#include "GlobalObjects.h"

#include "Element.h"
#include "Lemming.h"


void GlobalObjects::InitLevelOne()
{
    Picture picture("spriteAscii/background/background200_100.txt");
    DrawLemming::Instance().intial_level = picture;
    
    COORD centre_drop_lem{(short)(drop.get_center().X - _anims.at(2)->get_frame(0).w_picture/2), (short)(drop.get_center().Y - _anims.at(2)->get_frame(0).h_picture/2)};
    lemming.push_back( Lemming(_anims, centre_drop_lem, BOOM) );
}