---
type: 'kanban'
title: "Universe Generation"
description: 'Generate a universe'
date: '2026-05-16T03:18:45'
lastmod: null
author: Ivan Hawkes
categories: null
tags: null
params:
  sprint: null
  stage: design
  status: pending
  completed: null
  due: null
  percent: 0
  estimatedtime: 1
  actualtime: 0
  priority: 350
  dependencies: null
  references: [ ep-001-minimum-viable-product ]
---

Generate a playable universe with planets, economies, markets, and items for
trade.

<!--more-->

# Universe Generation

At the start of the game, the computer will generate a random universe.

**Goals**

- 100 planets
    - named
    - skinned
    - believable dispersal
    - marketplace
    - economy
    - corruption index
    - tech tree progress
    - cultural status e.g. agrarian, industrial, post-apocalyptic
- each marketplace will have a random sample of products from an item table

**Game Loop**

- a ship will be spawned at the origin point 0, 0, 0
- the ship will randomly choose a planet and start moving towards it
- once in range of the planet it will enter an orbit
- the ship may query the marketplace for goods to exchange
- the ship and merchant will exchange goods and funds in a near random manner
- the merchant, being an NPC construct will be funded by the PC in
  between turns, slowly regaining products and cash
- if the planet has spaceship fuel the ship should purchase enough to
  refill its tanks
- any actions undertaken will be written to the log file
- these steps will repeat ad infinitum

**Acceptance Criteria**

- A universe with 100 planets, economies, trade markets, and merchants
