//
//  MP3PlayerState.cpp
//  2017CS372DesignPatterns
//
//  Created by Chris Hartman on 4/17/17.
//  Copyright © 2017 Chris Hartman. All rights reserved.
//

#include "MP3PlayerState.hpp"
#include "MP3Player.hpp"
#include <memory>
using std::shared_ptr;
using std::make_shared;

void MP3PlayerState::playRadio(MP3Player *context) const {
    context->playRadio();
}
void MP3PlayerState::stopRadio(MP3Player *context) const {
    context->stopRadio();
}

void MP3PlayerState::nextRadioStation(MP3Player *context) const {
    context->nextRadioStation();
}

void MP3PlayerState::playMp3(MP3Player *context) const {
    context->playMp3();
}

void MP3PlayerState::stopMp3(MP3Player *context) const {
    context->stopMp3();
}

void MP3PlayerState::nextMp3(MP3Player *context) const {
    context->nextMp3();
}
void MP3PlayerState::setState(MP3Player *context, std::shared_ptr<MP3PlayerState> s) const {
    context->setState(s);
}


void StandbyState::sourceButton(MP3Player *context) const {
    setState(context,make_shared<PlaylistState>());
    playMp3(context);
}

void PlaylistState::sourceButton(MP3Player *context) const {
    setState(context,make_shared<RadioState>());
    stopMp3(context);
    playRadio(context);
}

void RadioState::sourceButton(MP3Player *context) const {
    setState(context,make_shared<StandbyState>());
    stopRadio(context);
}

void StandbyState::nextButton(MP3Player *context) const {
    
}

void PlaylistState::nextButton(MP3Player *context) const {
    nextMp3(context);
}

void RadioState::nextButton(MP3Player *context) const {
    nextRadioStation(context);
}
