#pragma once

#include <vector>

#include "StateMachine.h"
#include "GameState.h"

void StateMachine::changeState(GameState* pState) {
	if (!m_states.empty()) {
		if (m_states.back()->getStateID() == pState->getStateID()) {
			return;
		}
		if (m_states.back()->onExit()) {
			delete m_states.back();
			m_states.pop_back();
		}
	}

	m_states.push_back(pState);
	m_states.back()->onEnter();
}

void StateMachine::pushState(GameState* pState) {
	m_states.push_back(pState);
	m_states.back()->onEnter();
}

void StateMachine::popState() {
	if (!m_states.empty()) {
		if (m_states.back()->onExit()) {
			delete m_states.back();
			m_states.pop_back();
		}
	}
}

void StateMachine::update() {
	if (!m_states.empty()) {
		m_states.back()->update();
	}
}

void StateMachine::render() {
	if (!m_states.empty()) {
		m_states.back()->render();
	}
}