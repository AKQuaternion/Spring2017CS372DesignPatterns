//
//  MP3PlayerState.hpp
//  2017CS372DesignPatterns
//
//  Created by Chris Hartman on 4/17/17.
//  Copyright © 2017 Chris Hartman. All rights reserved.
//

#ifndef MP3PlayerState_hpp
#define MP3PlayerState_hpp
#include <memory>
class MP3Player;

class MP3PlayerState {
public:
    virtual ~MP3PlayerState() = default;
    virtual void nextButton(MP3Player *context) const = 0;
    virtual void sourceButton(MP3Player *context) const = 0;
protected:
    void playRadio(MP3Player *context) const ;
    void stopRadio(MP3Player *context) const ;
    void nextRadioStation(MP3Player *context) const ;
    void playMp3(MP3Player *context) const ;
    void stopMp3(MP3Player *context) const ;
    void nextMp3(MP3Player *context) const ;
    void setState(MP3Player *context, std::shared_ptr<MP3PlayerState> s) const ;

private:
    
};

class StandbyState : public MP3PlayerState
{
public:
    void nextButton(MP3Player *context) const override;
    void sourceButton(MP3Player *context) const override;
};

class PlaylistState : public MP3PlayerState
{
public:
    void nextButton(MP3Player *context) const override;
    void sourceButton(MP3Player *context) const override;
};

class RadioState : public MP3PlayerState
{
public:
    void nextButton(MP3Player *context) const override;
    void sourceButton(MP3Player *context) const override;
};


#endif /* MP3PlayerState_hpp */
