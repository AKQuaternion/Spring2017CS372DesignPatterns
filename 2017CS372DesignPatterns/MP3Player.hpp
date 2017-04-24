//
//  MP3Player.h
//  CS372 2015 Design Patterns
//
//  Created by Chris Hartman on 4/22/15.
//  Copyright (c) 2015 Chris Hartman. All rights reserved.
//

#ifndef __CS372_2015_Design_Patterns__MP3Player__
#define __CS372_2015_Design_Patterns__MP3Player__

#include "MP3PlayerState.hpp"

#include <iostream>
using std::cout;
#include <memory>

class MP3Player {
    friend MP3PlayerState;
public:
    MP3Player():_state(std::make_shared<StandbyState>())
    {}
    
    void pushNextButton()
    {
        _state->nextButton(this);
    }
    
    void pushSourceButton()
    {
        _state->sourceButton(this);
    }
    
private:
    void playRadio()
    {
        cout << "Playing the radio.\n";
    }
    void stopRadio()    {
        cout << "Stopping the radio.\n";
    }
    
    void nextRadioStation()    {
        cout << "Next radio station.\n";
    }
    
    void playMp3()    {
        cout << "Playing MP3.\n";
    }
    
    void stopMp3()    {
        cout << "Stopping MP3.\n";
    }
    
    void nextMp3()    {
        cout << "Next MP3.\n";
    }
    
    void setState(std::shared_ptr<MP3PlayerState> s);
    std::shared_ptr<MP3PlayerState> _state;
};
#endif /* defined(__CS372_2015_Design_Patterns__MP3Player__) */
