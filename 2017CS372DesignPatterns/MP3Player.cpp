//
//  MP3Player.cpp
//  2017CS372DesignPatterns
//
//  Created by Chris Hartman on 4/17/17.
//  Copyright © 2017 Chris Hartman. All rights reserved.
//

#include "MP3Player.hpp"

void MP3Player::setState(std::shared_ptr<MP3PlayerState> s){
    _state = s;
}
