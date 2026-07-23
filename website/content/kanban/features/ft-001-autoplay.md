---
type: 'kanban'
title: "Autoplay"
description: 'Game runs on autoplay'
date: '2026-05-16T02:53:19'
lastmod: null
author: Ivan Hawkes
categories: null
tags: null
params:
  sprint: sp-001
  stage: design
  status: pending
  completed: null
  due: null
  percent: 0
  estimatedtime: 4
  actualtime: 0
  priority: 350
  dependencies: null
  references: [ep-001-minimum-viable-product]
---

The game will run with the PC controlling all of the input and gameplay.

<!--more-->

The game will be capable of running on autoplay. It doesn't require 
particularly good algorithms at the start of development, just enough 
intelligence to move the ship around and make some trades.

This should enable me to get a minimum viable product scaffolded quickly, 
without getting into the minutia of UI design. 

# Game Runs on Autoplay

- Goals
  - Ship is spawned into universe
  - Ship selects a planet at random
  - Ship moves to planet and begins orbit or docking with trading station
  - Trades happen
  - Rinse, repeat
- Acceptance Criteria
    - The MVP code can all be tested