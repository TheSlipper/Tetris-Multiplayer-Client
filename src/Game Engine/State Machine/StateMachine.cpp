////////////////////////////////////////////////////////////
/// Tetris Multiplayer Game - PvP Tetris Experience
/// Copyright (C) 2019 Kornel Domeradzki
///
/// This program is free software; you can redistribute it and/or
/// modify it under the terms of the GNU General Public License
/// as published by the Free Software Foundation; either version 2
/// of the License, or (at your option) any later version.
///
/// This program is distributed in the hope that it will be useful,
/// but WITHOUT ANY WARRANTY; without even the implied warranty of
/// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
/// GNU General Public License for more details.
///
/// You should have received a copy of the GNU General Public License
/// along with this program; if not, write to the Free Software
/// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "StateMachine.hpp"

namespace ArktisEngine
{
    ////////////////////////////////////////////////////////////
    void StateMachine::AddState(StateRef newState, bool isReplacing)
    {
        this->_isAdding = true;
        this->_isReplacing = isReplacing;
        
        this->_newState = std::move(newState);
    }
    
    ////////////////////////////////////////////////////////////
    void StateMachine::RemoveState()
    {
        this->_isRemoving = true;
    }
    
    ////////////////////////////////////////////////////////////
    void StateMachine::ProcessStateChanges()
    {
        if (this->_isRemoving && !this->_states.empty())
        {
            this->_states.pop();
            
            if (!this->_states.empty())
                this->_states.top()->Resume();
            
            this->_isRemoving = false;
        }
        
        if (this->_isAdding)
        {
            if (!this->_states.empty())
            {
                if (this->_isReplacing)
                    this->_states.pop();
                else
                    this->_states.top()->Pause();
            }
            
            this->_states.push(std::move(this->_newState));
            this->_states.top()->Init();
            this->_isAdding = false;
        }
    }
    
    ////////////////////////////////////////////////////////////
    StateRef &StateMachine::GetActiveState()
    {
        return this->_states.top();
    }
}
