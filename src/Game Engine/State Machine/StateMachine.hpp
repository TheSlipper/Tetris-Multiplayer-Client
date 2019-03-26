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
#pragma once

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <memory>
#include <stack>
#include "../../Game States/State/State.hpp"

namespace ArktisEngine
{
    typedef std::unique_ptr<States::State> StateRef;    ///< Definition of pointer to a State object
    
    ////////////////////////////////////////////////////////////
    /// \brief Class that manages game's scenes
    ///
    ////////////////////////////////////////////////////////////
    class StateMachine
    {
    public:
        ////////////////////////////////////////////////////////////
        /// \brief Default constructor
        ///
        ////////////////////////////////////////////////////////////
        StateMachine() { }
        
        ////////////////////////////////////////////////////////////
        /// \brief Default destructor
        ///
        ////////////////////////////////////////////////////////////
        ~StateMachine() { }
        
        ////////////////////////////////////////////////////////////
        /// \brief Queues a state to add it
        ///
        /// \param bool isReplacing tells if the previous scene should
        ///                         be replaced
        ///
        ////////////////////////////////////////////////////////////
        void AddState(StateRef newState, bool isReplacing = true);
        
        ////////////////////////////////////////////////////////////
        /// \brief Queues a state for it's removal
        ///
        ////////////////////////////////////////////////////////////
        void RemoveState();
        
        ////////////////////////////////////////////////////////////
        /// \brief Processes all the queued state changes
        ///
        ////////////////////////////////////////////////////////////
        void ProcessStateChanges();
        
        ////////////////////////////////////////////////////////////
        /// \brief Gets the reference to the currently running state
        ///
        ////////////////////////////////////////////////////////////
        StateRef &GetActiveState();
        
    private:
        ////////////////////////////////////////////////////////////
        // Member data
        ////////////////////////////////////////////////////////////
        std::stack<StateRef> _states;   ///< Stack that contains all of the states
        
        StateRef _newState; ///< State staged for it's addition
        
        bool _isRemoving;   ///< Flag that states whether the top state should be removed
        
        bool _isAdding, _isReplacing;   ///< Flags that indicate queued state machine change
    };
}
